#include <iostream>

#include "automatic_session.hh"
#include "distant_root.hh"
#include "fs.hh"
#include "local_root.hh"
#include "push.hh"
#include "synchronize.hh"

/*------------------------------------------------------------------------------------------------*/

struct tmp
{
  std::string prefix;

  void
  operator()(ntx::id_type parent_id, const ntx::folder& f, const boost::filesystem::path& path)
  const
  {
//    std::cout << '[' << prefix << "] folder " << f.name() << " @ " << path.string() << '\n';
  }

  void
  operator()(ntx::id_type parent_id, const ntx::file& f, const boost::filesystem::path& path)
  const
  {
//    std::cout << '[' << prefix << "] file " << f.name() << " @ " << path.string() << '\n';
  }
};

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
    const auto distant_root = ntx::get_distant_root(conf, session, 1ul);
    const auto local_root   = ntx::get_local_root(conf);

    ntx::synchronize( distant_root, local_root, conf.local_root()
                    , tmp{"pull"}, ntx::push{conf, session}, tmp{"conflict"});
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}

/*------------------------------------------------------------------------------------------------*/
