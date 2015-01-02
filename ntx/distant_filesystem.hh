#pragma once

#include "ntx/configuration.hh"
#include "ntx/fs.hh"
#include "ntx/session.hh"
#include "ntx/types.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

folder
get_distant_filesystem(const configuration&, const session&, id_type root);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx