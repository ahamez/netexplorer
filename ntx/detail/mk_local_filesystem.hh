#pragma once

#include <boost/filesystem.hpp>

#include "ntx/fs.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Create a filesystem from a local path.
folder
mk_local_folder(const boost::filesystem::path&);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
