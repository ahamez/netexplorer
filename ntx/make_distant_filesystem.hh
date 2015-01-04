#pragma once

#include "ntx/configuration.hh"
#include "ntx/distant_filesystem.hh"
#include "ntx/session.hh"
#include "ntx/types.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Return the distant filesystem for a session and a folder id.
///
/// Default to root folder.
distant_folder
make_distant_filesystem(const configuration&, const session&, id_type = 1u);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
