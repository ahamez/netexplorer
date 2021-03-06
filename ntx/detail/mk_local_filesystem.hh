#pragma once

#include <boost/filesystem.hpp>

#include "ntx/local_filesystem.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Create a filesystem from a local path.
local_folder
mk_local_folder(const boost::filesystem::path&);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
