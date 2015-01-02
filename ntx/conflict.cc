#include <fstream>
#include <iosfwd>
#include <iterator>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include "ntx/conflict.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;
using namespace boost::network;

/*------------------------------------------------------------------------------------------------*/

conflict::conflict(const configuration& conf, const session& s)
  : conf_{conf}, session_{s}
{}

/*------------------------------------------------------------------------------------------------*/

void
conflict::operator()(ntx::id_type parent_id, const ntx::file& f, const fs::path& parent_path)
{
  std::cout << "[conflict] file " << f.name() << " @ " << parent_path.string()
            << " (parent_id = " << parent_id << ")\n";
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
