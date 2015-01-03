#include <iostream>

#include <boost/algorithm/string/join.hpp>
#include <boost/program_options.hpp>

#include "configure.hh"

/*------------------------------------------------------------------------------------------------*/

namespace po = boost::program_options;

/*------------------------------------------------------------------------------------------------*/

boost::optional<ntx::configuration>
configure(int argc, const char** argv)
{
  po::options_description general_options("Options");
  general_options.add_options()
    ("help"       , "Show this help")
  ;

  po::options_description hidden_options("Hidden input options");
  hidden_options.add_options()
    ("local"   , po::value<std::string>(), "The local file to synchronize")
    ("distant" , po::value<std::string>(), "The distant account to synchronize")
  ;

  po::positional_options_description p;
  p.add("local", 1)
   .add("distant", 2);

  po::options_description cmdline_options;
  cmdline_options.add(general_options)
                 .add(hidden_options);

  po::variables_map vm;
  po::parsed_options parsed = po::command_line_parser(argc, argv).options(cmdline_options)
                                                                 .positional(p)
                                                                 .allow_unregistered()
                                                                 .run();
  po::store(parsed, vm);
  po::notify(vm);

  std::vector<std::string> unrecognized
    = po::collect_unrecognized(parsed.options, po::exclude_positional);

  if (not unrecognized.empty() or not vm.count("local") or not vm.count("distant"))
  {
    if (not unrecognized.empty())
    {
      std::cerr << "Unknown option(s): " << boost::algorithm::join(unrecognized, " ") << "\n\n";
    }
    if (not vm.count("local"))
    {
      std::cerr << "No local folder specified\n\n";
    }
    if (not vm.count("distant"))
    {
      std::cerr << "No distant account specified\n\n";
    }

    std::cout << "Usage: " << argv[0] << " [options] local distant\n\n"
              << general_options << '\n';

    if (vm.count("help"))
    {
      return {};
    }
    else
    {
      throw po::error("Invalid options");
    }
  }

  return ntx::configuration{ vm["distant"].as<std::string>()
                           , vm["local"].as<std::string>()};
}

/*------------------------------------------------------------------------------------------------*/
