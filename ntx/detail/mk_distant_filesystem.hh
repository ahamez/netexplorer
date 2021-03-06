#pragma once

#include "ntx/configuration.hh"
#include "ntx/distant_filesystem.hh"
#include "ntx/session.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Create a filesystem from a distant NetExplorer storage.
distant_folder
mk_distant_folder(const configuration&, const session&, id_type);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
