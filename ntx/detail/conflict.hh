#pragma once

#include "ntx/distant_filesystem.hh"
#include "ntx/local_filesystem.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Check if two files conflict.
struct conflict final
{
  bool
  operator()(const ntx::distant_file&, const ntx::local_file&) const noexcept;
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
