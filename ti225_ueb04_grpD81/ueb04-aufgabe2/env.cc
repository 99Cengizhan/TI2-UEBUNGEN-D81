#include <cstdlib>
#include <iostream>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "env.hh"

namespace ti2 {
/* name of the environment variable that stores the PATH */
const std::string envPath = "PATH";

/* a single character used in ENV_PATH as separator */
const char pathDelim = ':';

std::string getenv(const char *varname) {
  const char *result;
  result = ::getenv(varname);
  return result ? result : "";
}

bool searchCommand(const std::string &cmd, std::string &result) {
  result.clear();
  if (cmd.find_first_of('/') != std::string::npos) {
    /* return true only if cmd exists */
    if (struct stat st; stat(cmd.c_str(), &st) == 0) {
      result = cmd;
      return true;
    } else {
      return false;
    }
  }

  /* used to create the full path of a possible command on the fly */
  std::string p = getenv(envPath);
  if (!p.empty()) {
    std::string cmd_path;
    std::string path = p;
    std::string::size_type pos = 0, oldpos;

    do {
      oldpos = pos;
      pos = path.find_first_of(pathDelim, oldpos);

      if (pos == std::string::npos) {
        cmd_path = path.substr(oldpos, pos) + '/' + cmd;
      } else {
        cmd_path = path.substr(oldpos, pos - oldpos) + '/' + cmd;
        pos++;
      }

      struct stat st;
      if (stat(cmd_path.c_str(), &st) == 0) {
        result = cmd_path;
        return true;
      }

    } while (pos != std::string::npos);
  }

  return false;
}
}
