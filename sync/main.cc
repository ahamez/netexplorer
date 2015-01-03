#include <iostream>

#include "ntx/automatic_session.hh"
#include "ntx/configuration.hh"
#include "ntx/distant_filesystem.hh"
#include "ntx/local_filesystem.hh"
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
      const auto session    = ntx::automatic_session{*conf};
      const auto distant_fs = ntx::get_distant_filesystem(*conf, session, 1ul /* root */);
      const auto local_fs   = ntx::get_local_filesystem(*conf);
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
