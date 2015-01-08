#pragma once

#include <boost/filesystem.hpp>

#include "ntx/distant_filesystem.hh"
#include "ntx/local_filesystem.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Synchronize a distant and a local filesystem.
/// @param pull Function object called when a file is missing in the local filesystem.
/// @param push Function object called when a file is missing in the distant filesystem.
/// @param conflict Function object called to check if two files conflict.
/// @param handle_conflict Function object called when a file exists on both filesystem with
/// different contents.
template <typename Pull, typename Push, typename Conflict, typename HandleConflict>
void
synchronize( const distant_folder& distant_f, const local_folder& local_f
           , const boost::filesystem::path& local_path, Pull&& pull
           , Push&& push, Conflict&& conflict, HandleConflict&& handle_conflict);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx

#include "ntx/detail/synchronize.tcc"
