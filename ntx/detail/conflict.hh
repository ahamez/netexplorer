#pragma once

#include "ntx/fs.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Check if two files conflict.
struct conflict final
{
  bool
  operator()(const ntx::file&, const ntx::file&) const noexcept;
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
