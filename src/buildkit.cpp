#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include <folly/json.h>
#include <folly/dynamic.h>

#include <folly/Format.h>
#include <folly/FileUtil.h>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

folly::dynamic project_spec = nullptr;

std::string getcwd_string(void)
{
  char buff[PATH_MAX];
  getcwd(buff, PATH_MAX);
  std::string cwd(buff);
  return cwd;
}

void check_and_set_spec(const std::string project_path)
{
  if (project_spec == nullptr) {

    std::string load_pkg_desc;
    std::string full_path =
      folly::sformat("{}/{}", getcwd_string(), project_path);

    if (!folly::readFile(full_path.data(), load_pkg_desc)) {
      exit(-1);
    }
    project_spec = folly::parseJson(load_pkg_desc);
  }
}

namespace logos
{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  struct directives_ : qi::symbols<char, std::string>
  {
    directives_()
    {
      add
	("C"    , "1234")
	("CM"   , "1235")
	("CM"   , "1235")

	;
    }

  } directives;
}



// And now we talk to Make

extern "C" {

#include <gnumake.h>

  int plugin_is_GPL_compatible;

  // We give back null to each of these because they are just for side
  // effects
  char *build(const char *, int, char **argv)
  {
    check_and_set_spec(std::string(*argv));
    return NULL;
  }

  char *package(const char *func_name, int argc, char **argv)
  {
    check_and_set_spec(std::string(*argv));
    return NULL;
  }

  char *deploy(const char *func_name, int argc, char **argv)
  {
    check_and_set_spec(std::string(*argv));
    return NULL;
  }

  int buildkit_gmk_setup()
  {
    gmk_add_function("tweak_builder", (gmk_func_ptr)build, 1, 1, 0);
    gmk_add_function("tweak_package", (gmk_func_ptr)package, 1, 1, 0);
    gmk_add_function("tweak_deploy", (gmk_func_ptr)deploy, 1, 1, 0);
    return 1;
  }

}
