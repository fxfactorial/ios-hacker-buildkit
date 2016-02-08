#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include <folly/json.h>
#include <folly/dynamic.h>

#include <folly/Format.h>
#include <folly/FileUtil.h>

std::string getcwd_string(void)
{
   char buff[PATH_MAX];
   getcwd(buff, PATH_MAX);
   std::string cwd(buff);
   return cwd;
}

class Project_builder {
private:

public:
  Project_builder(const std::string package_json_path)
  {

  }

  void make_merlin_file()
  {

  }

  void make_opam_file()
  {

  }

};

class Code_builder {

public:
  Code_builder(const std::string package_json_path)
  {

  }

};

extern "C" {

#include <gnumake.h>

  int plugin_is_GPL_compatible;

  char *generate_project(const char *func_name, int argc, char **argv)
  {
    std::string package_json(*argv);
    std::unique_ptr<Project_builder> builder(new Project_builder(package_json));
    std::cout << "Hello World from C++" << std::endl;
    return NULL;
  }

  char *build_project(const char *func_name, int argc, char **argv)
  {
    std::string package_json(*argv);
    std::unique_ptr<Code_builder> builder(new Code_builder(package_json));

    return NULL;
  }

  int buildkit_gmk_setup()
  {
    gmk_add_function("build_code",
		     (gmk_func_ptr)generate_project, 1, (unsigned int)1, 1);
    /*     gmk_add_function("build_project",
	   (gmk_func_ptr)build_project, 1, (unsigned int)1, 1); */
    return 1;
  }

}
