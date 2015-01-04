#include <iostream>

#include "ntx/automatic_session.hh"
#include "ntx/configuration.hh"
#include "ntx/make_distant_filesystem.hh"
#include "ntx/make_local_filesystem.hh"
#include "ntx/synchronize.hh"

#include "configure.hh"

/*------------------------------------------------------------------------------------------------*/

int
main(int argc, const char** argv)
{
  try
  {
    if (const auto conf = configure(argc, argv))
    {
      if (not exists(conf->local_path()))
      {
        boost::filesystem::create_directories(conf->local_path());
      }

      const auto session    = ntx::automatic_session{*conf};
      const auto distant_fs = ntx::make_distant_filesystem(*conf, session);
      const auto local_fs   = ntx::make_local_filesystem(*conf);
      ntx::synchronize(*conf, session, distant_fs, local_fs);
    }
    // else --help
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}

/*------------------------------------------------------------------------------------------------*/
