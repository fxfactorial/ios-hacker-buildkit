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

class Spec {
private:
  folly::dynamic project_spec = nullptr;
};

class Builder : Spec {

};

class Packager : Spec {

};

class Deployer : Spec {

};

extern "C" {

#include <gnumake.h>

  int plugin_is_GPL_compatible;

  // We give back null to each of these because they are just for side
  // effects
  char *build(const char *func_name, int argc, char **argv)
  {
    std::cout << "Called build function\n";
    return NULL;
  }

  char *package(const char *func_name, int argc, char **argv)
  {
    std::cout << "Called package function\n";
    return NULL;
  }

  char *deploy(const char *func_name, int argc, char **argv)
  {
    std::cout << "Called deploy function\n";
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
