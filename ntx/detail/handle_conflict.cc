#include <iostream>

#include <boost/filesystem.hpp>

#include "ntx/detail/handle_conflict.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;

/*------------------------------------------------------------------------------------------------*/

handle_conflict::handle_conflict(const configuration& conf, const session& s)
  : conf_{conf}, session_{s}
{}

/*------------------------------------------------------------------------------------------------*/

void
handle_conflict::operator()(ntx::id_type parent_id, const ntx::file& f, const fs::path& parent_path)
{
  std::cout << "[conflict] file " << f.name() << " @ " << parent_path.string()
            << " (parent_id = " << parent_id << ")\n";
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
