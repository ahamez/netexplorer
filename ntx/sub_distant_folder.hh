#pragma once

#include "ntx/distant_filesystem.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Get a distant folder using a path relative to the distant root.
distant_folder
sub_folder(const distant_folder&, const std::string&);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
