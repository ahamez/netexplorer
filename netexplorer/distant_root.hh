#pragma once

#include "configuration.hh"
#include "fs.hh"
#include "session.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

folder
get_distant_root(const configuration&, const session&);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
