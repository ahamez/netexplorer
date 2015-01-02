#pragma once

#include "ntx/configuration.hh"
#include "ntx/fs.hh"
#include "ntx/session.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @brief Create a filesystem from a distant NetExplorer storage.
folder
mk_distant_folder(const configuration&, const session&, unsigned long root);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
