#ifndef ENV_HH
#define ENV_HH

#include <string>

namespace ti2 {

/**
 * Tries to find @p cmd in the system's search path unless @p cmd
 * already contains a '/'. This function returns true if a file with
 * name @p cmd was found, false otherwise. On success, the result
 * parameter @p result is set to a path suitable as input for execv.
 */
bool searchCommand(const std::string &cmd, std::string &result);

/**
 * Returns a string object containing the contents of the environment
 * variable @p varname. If @p varname is not set, the returned string
 * will be empty.
 */
std::string getenv(const char *varname);

static inline std::string getenv(const std::string &varname) {
  return getenv(varname.c_str());
}

} // namespace ti2

#endif /* ENV_HH */
