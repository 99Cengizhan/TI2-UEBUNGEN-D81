#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <atomic>
#include <stdexcept>

#include "sighnd.hh"

namespace ti2 {

/* pid of a foreground process (the value 0 means that no forground
 * process is being executed */
static std::atomic<pid_t> fg_child = 0;

/* signal handler function for SIGCHLD. This function checks if the
 * signal was really SIGCHLD and then collects the terminated child
 * process by invoking wait(). When the forground processes has
 * finished, the variable fg_child is reset to zero.
 */
static void
handle_sigchld(int num, siginfo_t *info, void *context) {
  (void)context; // suppress warnings for unused parameter

  if (num == SIGCHLD && info->si_code == CLD_EXITED) {
    if (wait(0) == fg_child) {
      fg_child = 0;
    }
  }
}

static void
handle_sigint(int num, siginfo_t *, void *) {
  if (num == SIGINT)
    exit(EXIT_SUCCESS);
}

void SignalHandler::install(void) {
  struct sigaction act;

  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_RESTART;
  act.sa_sigaction = handle_sigint;

  /* install our own signal handler or exit with error */
  if (sigaction(SIGINT, &act, NULL) < 0) {
    throw std::runtime_error{"sigaction: cannot set signal handler for SIGINT"};
  }

  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO | SA_RESTART;
  act.sa_sigaction = handle_sigchld;

  /* install our own signal handler or exit with error */
  if (sigaction(SIGCHLD, &act, NULL) < 0) {
    throw std::runtime_error{"sigaction: cannot set signal handler for SIGCHLD"};
  }
}

void SignalHandler::block(pid_t pid) {
  fg_child = pid;

  /* wait for foreground process to be terminated */
  while (fg_child) {
    pause();
  }
  fg_child = 0;
}

} // namespace ti2
