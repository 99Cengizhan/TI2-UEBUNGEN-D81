#include <cstring>
#include <unistd.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <regex>

#include "parser.hh"

using namespace std;

namespace ti2 {
static ostream &
prompt(ostream &os) {
  return os << "ti2sh$ " << flush;
}

unique_ptr<Command>
read_command_line(void) {
  string input;
  unique_ptr<Command> cmd;
  const regex ws_re("\\s+");

  while (true) {
    prompt(cout);
    if (!getline(cin, input)) {
      /* set command to exit to force the shell to quit */
      cmd = make_unique<Command>(); /* may throw bad_alloc exception */
      cmd->argv.push_back("exit");
      break;
    }

    cmd = make_unique<Command>(); /* may throw bad_alloc exception */

    /* TODO: handle quoted strings */
    /* see http://en.cppreference.com/w/cpp/regex/regex_token_iterator
     * for splitting a string by regex */
    copy(sregex_token_iterator(input.begin(), input.end(), ws_re, -1),
         sregex_token_iterator(),
         inserter(cmd->argv, cmd->argv.end()));

    /* Check & for background process; trailing whitespace and empty
     * elements are removed. */
    cmd->background = false;
    if (!cmd->argv.empty()) {
      string &arg = cmd->argv.back();
      if (arg.back() == '&') {
        cmd->background = true;
        arg.pop_back();

        string::size_type p = arg.find_last_not_of(" \t");
        if ((p != string::npos) && (p < arg.length() - 2)) {
          arg.erase(p + 1, arg.length() - p - 1);
        }

        if (arg.empty()) {
          cmd->argv.pop_back();
        }

      }
    }

    /* Remove empty leading elements. */
    while (!cmd->argv.empty() && cmd->argv.front().empty()) {
      cmd->argv.erase(cmd->argv.begin(), next(cmd->argv.begin()));
    }

    /* Return cmd only if not empty, otherwise proceed with next line. */
    if (!cmd->argv.empty())
      break;
    else
      cmd.reset();
  }
  return cmd;
}

}
