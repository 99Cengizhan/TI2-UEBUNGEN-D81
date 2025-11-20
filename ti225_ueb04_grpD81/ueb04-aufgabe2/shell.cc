#include <cerrno>
#include <cstring>
#include <unistd.h>

#include <algorithm>
#include <iostream>

#include "env.hh"
#include "shell.hh"

namespace ti2 {

/**
 * Outputs debug information about the given command @p cmd on the
 * standard output.
 */
static void explain(const std::unique_ptr<Command> &cmd) {
  if (!cmd)
    return;

  auto arg = cmd->argv.begin();
  std::cout << "command: " << *arg << std::endl
            << "arguments:";
  std::for_each(++arg, cmd->argv.end(),
                [] (auto const &arg) { std::cout << " " << arg; });
  std::cout << std::endl
            << "background: " << (cmd->background ? "ja" : "nein")
            << std::endl;
}

/**
 * Checks if @p cmd is a shell built-in. This function returns true if
 * the command was handled by this command and does not need any more
 * treatment. The commands "exit" and "quit" will terminate the
 * shell. "cd" invokes chdir() to change the current directory.
 */
static bool builtin(const std::unique_ptr<Command> &cmd) {
  if (!cmd || (cmd->argv[0] == "exit") || (cmd->argv[0] == "quit")) {
    exit(EXIT_SUCCESS);
  }

  if (cmd->argv[0] == "cd") {
    std::string dir;
    if (cmd->argv.size() == 1) {
      std::string path = ti2::getenv("HOME");
      if (path.empty()) {
        return true;
      } else {
        dir = path;
      }
    } else {
      dir = cmd->argv[1];
    }

    if (chdir(dir.c_str()) == -1) {
      std::cerr << strerror(errno) << std::endl;
    }
    return true;
  }
  return false;
}

std::pair<std::string, std::unique_ptr<Command>> Shell::readCommand(void) {
  std::string path;
  std::unique_ptr<Command> cmd = read_command_line();

  if (cmd) {
    ti2::explain(cmd);

    if (builtin(cmd)) {
      cmd.reset();
    } else if (!ti2::searchCommand(cmd->argv[0], path)) {
      std::cerr << cmd->argv[0] << ": command not found" << std::endl;
      cmd.reset();
      path.clear();
    }
  }
  return {path, std::move(cmd)};
}


} // namespace ti2

int execv(const std::string &path, const std::unique_ptr<ti2::Shell::Command> &cmd) {
  if (!cmd) {
    errno = 0;
    return 0;
  }

  /* create array from string vector */
  std::vector<char *> arr;

  std::transform(cmd->argv.begin(), cmd->argv.end(), inserter(arr, arr.end()),
                 [](const std::string &s) { return const_cast<char *>(s.c_str()); });

  /* execv expects a null-terminated array as second argument */
  arr.push_back(nullptr);

  return ::execv(path.c_str(), &arr[0]);
}
