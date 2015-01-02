#include <iostream>

#include "ntx/automatic_session.hh"
#include "ntx/conflict.hh"
#include "ntx/distant_filesystem.hh"
#include "ntx/fs.hh"
#include "ntx/local_filesystem.hh"
#include "ntx/pull.hh"
#include "ntx/push.hh"
#include "ntx/synchronize.hh"

/*------------------------------------------------------------------------------------------------*/

int
main()
{
  /// @todo Read configuration from a file and verify it
  const auto conf = ntx::configuration{ "https://ahamez.netexplorer.pro/api"
                                      , "/Users/hal/Desktop/NetExplorer"};

  try
  {
    const auto session = [&]
    {
      /// @todo Read from OS's secure storage (like Mac OS X 's Keychain Access)
      const auto credentials = ntx::credentials{"alexandre.hamez", "qptt5zwn"};
      return ntx::automatic_session{conf, credentials};
    }(); // credentials scrambled here

    /// @todo Select distant folder from one of the account's roots
    const auto distant_fs = ntx::get_distant_filesystem(conf, session, 1ul /* root */);
    const auto local_fs   = ntx::get_local_filesystem(conf);

    ntx::synchronize( distant_fs, local_fs, conf.local_root()
                    , ntx::pull{conf, session}, ntx::push{conf, session}
                    , ntx::conflict{conf, session});
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}

/*------------------------------------------------------------------------------------------------*/
