#pragma once

#include "ntx/fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Synchronize a distant and a local filesystem.
void
synchronize( const configuration& conf, const session& s, const folder& distant_folder
           , const folder& local_folder);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
