#include <iostream>

#include "account.hh"
#include "automatic_session.hh"
#include "distant_root.hh"
#include "fs.hh"
#include "local_root.hh"
#include "synchronize.hh"

/*------------------------------------------------------------------------------------------------*/

struct tmp
{
  std::string prefix;

  void
  operator()(ntx::id_type parent_id, const ntx::folder& f, const boost::filesystem::path& path)
  const
  {
    std::cout << '[' << prefix << "] folder " << f.name() << " @ " << path.string() << '\n';
  }

  void
  operator()(ntx::id_type parent_id, const ntx::file& f, const boost::filesystem::path& path)
  const
  {
    std::cout << '[' << prefix << "] file " << f.name() << " @ " << path.string() << '\n';
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

    // Check some facts about the account's roots.
    /// @todo Select distant folder from one of the roots
    const auto account = ntx::account{conf, session};
    if (account.roots().size() == 0)
    {
      throw std::runtime_error("Account with no associated roots.");
    }
    if (not account.roots().count(1ul))
    {
      throw std::runtime_error("Account doesn't have root with id '1'.");
    }

    const auto distant_root = ntx::get_distant_root(conf, session);
    const auto local_root   = ntx::get_local_root(conf);

    ntx::synchronize( distant_root, local_root, conf.local_root()
                    , tmp{"pull"}, tmp{"push"}, tmp{"conflict"});
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}

/*------------------------------------------------------------------------------------------------*/
