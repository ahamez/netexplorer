#pragma once

#include "ntx/local_filesystem_fwd.hh"
#include "ntx/detail/any_fs_impl.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
struct local_file_impl_specific final
  : public any_file_impl
{
  using any_file_impl::any_file_impl; // inherit constructors
};

/*------------------------------------------------------------------------------------------------*/

/// @internal
template <typename Folder, typename File>
struct local_folder_impl_specific final
  : public any_folder_impl<Folder, File>
{
  using parent_type = any_folder_impl<Folder, File>;
  using parent_type::parent_type; // inherit constructors
};

/*------------------------------------------------------------------------------------------------*/

using local_file_impl = local_file_impl_specific;
using local_folder_impl = local_folder_impl_specific<local_folder, local_file>;

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
