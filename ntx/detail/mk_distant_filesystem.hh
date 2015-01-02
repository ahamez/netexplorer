#pragma once

#include "ntx/configuration.hh"
#include "ntx/fs.hh"
#include "ntx/session.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Create a filesystem from a distant NetExplorer storage.
folder
mk_distant_folder(const configuration&, const session&, id_type);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
