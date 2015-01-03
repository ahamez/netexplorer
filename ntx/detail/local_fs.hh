#pragma once

#include "ntx/local_filesystem_fwd.hh"
#include "ntx/detail/any_fs_impl.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
struct local_file_impl_specific
{};

/*------------------------------------------------------------------------------------------------*/

/// @internal
struct local_folder_impl_specific
{};

/*------------------------------------------------------------------------------------------------*/

using local_file_impl = any_file_impl<local_file_impl_specific>;
using local_folder_impl = any_folder_impl<local_folder_impl_specific, local_folder, local_file>;

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
