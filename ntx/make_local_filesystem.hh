#pragma once

#include "ntx/configuration.hh"
#include "ntx/local_filesystem.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

local_folder
make_local_filesystem(const configuration&);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
