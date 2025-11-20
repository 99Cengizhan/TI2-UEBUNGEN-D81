#ifndef SIGHND_HH
#define SIGHND_HH

#include <unistd.h>

namespace ti2 {

class SignalHandler {
public:
  /**
   * Installs a signal handler for SIGCHLD. This function throws
   * std::runtime_error if the signal handler was not installed
   * properly.
   */
  static void install(void);

  static void block(pid_t pid);
};

}

#endif /* SIGHND_HH */
