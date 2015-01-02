#pragma once

#include "ntx/configuration.hh"
#include "ntx/fs.hh"
#include "ntx/session.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

folder
get_distant_root(const configuration&, const session&, unsigned long root);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
