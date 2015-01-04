#pragma once

#include "ntx/configuration.hh"
#include "ntx/local_filesystem.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Return the local filesystem.
local_folder
make_local_filesystem(const configuration&);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
