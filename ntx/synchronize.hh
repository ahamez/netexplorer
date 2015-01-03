#pragma once

#include "ntx/distant_filesystem.hh"
#include "ntx/local_filesystem.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Synchronize a distant and a local filesystem.
void
synchronize(const configuration&, const session&, const distant_folder&, const local_folder&);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
