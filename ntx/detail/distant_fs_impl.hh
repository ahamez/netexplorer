#pragma once

#include "ntx/types.hh"
#include "ntx/distant_filesystem_fwd.hh"
#include "ntx/detail/any_fs_impl.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
class distant_file_impl_specific final
  : public any_file_impl
{
private:

  id_type id_;

public:

  template <typename... Args>
  distant_file_impl_specific(id_type id, Args&&... args)
    : any_file_impl(std::forward<Args>(args)...)
    , id_{id}
  {}

  id_type id() const noexcept {return id_;}
};

/*------------------------------------------------------------------------------------------------*/

/// @internal
template <typename Folder, typename File>
class distant_folder_impl_specific final
  : public any_folder_impl<Folder, File>
{
private:

  id_type id_;

public:

  template <typename... Args>
  distant_folder_impl_specific(id_type id, Args&&... args)
    : any_folder_impl<Folder, File>(std::forward<Args>(args)...)
    , id_{id}
  {}

  id_type id() const noexcept {return id_;}
};

/*------------------------------------------------------------------------------------------------*/

using distant_file_impl = distant_file_impl_specific;
using distant_folder_impl = distant_folder_impl_specific<distant_folder, distant_file>;

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
