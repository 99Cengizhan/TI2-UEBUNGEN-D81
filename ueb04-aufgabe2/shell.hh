#ifndef SHELL_HH
#define SHELL_HH

#include <string>
#include <utility>
#include <vector>

#include "parser.hh"

namespace ti2 {

class Shell {
public:

  /**
   * A structure containing the command line input parsed into tokens.
   * The flag background is set if '&' has been specified at the end of
   * the line. The contents of argv are suitable to be passed to
   * execv().
   */
  typedef struct Command Command;

  static std::pair<std::string, std::unique_ptr<Command>> readCommand(void);

};

} // namespace ti2

/**
 * Calls ::execv() with the given command name in @p path with the
 * contents of @p argv as argument vector.
 */
int execv(const std::string &path, const std::unique_ptr<ti2::Shell::Command> &cmd);

#endif /* SHELL_HH */
