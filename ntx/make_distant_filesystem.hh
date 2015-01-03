#pragma once

#include "ntx/configuration.hh"
#include "ntx/distant_filesystem.hh"
#include "ntx/session.hh"
#include "ntx/types.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

distant_folder
make_distant_filesystem(const configuration&, const session&, id_type root);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
