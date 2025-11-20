#ifndef PARSER_HH
#define PARSER_HH

#include <memory>
#include <string>
#include <vector>

namespace ti2 {

struct Command {
  std::vector<std::string> argv;
  bool background;
};

/**
 * Reads a line from STDIN and returns pointer to a newly created
 * Command structure on success. On error, a nullptr is returned.
 */
std::unique_ptr<Command> read_command_line(void);

} // namespace ti2

#endif /* PARSER_HH */
