#pragma once

#include "ntx/fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Check if two files conflict.
struct conflict final
{
  bool
  operator()(const ntx::file&, const ntx::file&) const noexcept;
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
