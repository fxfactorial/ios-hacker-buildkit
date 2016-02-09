#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include <folly/json.h>
#include <folly/dynamic.h>

#include <folly/Format.h>
#include <folly/FileUtil.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

namespace logos
{
  namespace qi = boost::spirit::qi;
  namespace ascii = boost::spirit::ascii;

  struct class_hook
  {
    std::string class_name;
    std::string method_signature;
    std::string method_body;
  };

  template <typename Iterator>
  struct class_hook_parser : qi::grammar<Iterator, class_hook(), ascii::space_type>
  {
    class_hook_parser() : class_hook_parser::base_type(start)
    {
      using qi::int_;
      using qi::lit;
      using qi::double_;
      using qi::lexeme;
      using ascii::char_;

      quoted_string %= lexeme['"' >> +(char_ - '"') >> '"'];

      start %=
	lit("%hook")
	>>  *(char_)
	>> '-'
	;

    }
    qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
    qi::rule<Iterator, class_hook_parser(), ascii::space_type> start;

  };

}

BOOST_FUSION_ADAPT_STRUCT(logos::class_hook,
			  (std::string, class_name)
			  (std::string, method_signature)
			  (std::string, method_body))

namespace buildkit {

  namespace impl {
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
  }
  char *build(const char *, int, char **argv)
  {
    impl::check_and_set_spec(std::string(*argv));
    return NULL;
  }

  char *package(const char *func_name, int argc, char **argv)
  {
    impl::check_and_set_spec(std::string(*argv));
    return NULL;
  }

  char *deploy(const char *func_name, int argc, char **argv)
  {
    impl::check_and_set_spec(std::string(*argv));
    return NULL;
  }

}

// And now we talk to Make
extern "C" {

#include <gnumake.h>

  int plugin_is_GPL_compatible;

  // This convention does matter, func name ought to end with
  // gmk_setup
  int buildkit_gmk_setup()
  {
    // We say that we our builtin make functions shall take a min
    // number of 1 argments and a max of 1 arguments, aka I really
    // want that package.json to be there.
    gmk_add_function("tweak_builder",
		     (gmk_func_ptr)buildkit::build, 1, 1, 0);
    gmk_add_function("tweak_package",
		     (gmk_func_ptr)buildkit::package, 1, 1, 0);
    gmk_add_function("tweak_deploy",
		     (gmk_func_ptr)buildkit::deploy, 1, 1, 0);
    return 1;
  }

}
