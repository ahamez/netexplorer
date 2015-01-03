#pragma once

#include "ntx/types.hh"
#include "ntx/distant_filesystem_fwd.hh"
#include "ntx/detail/any_fs.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
class distant_file_impl_specific
{
private:

  id_type id_;

public:

  distant_file_impl_specific(id_type id)
    : id_{id}
  {}

  id_type id() const noexcept {return id_;}
};

/*------------------------------------------------------------------------------------------------*/

/// @internal
class distant_folder_impl_specific
{
private:

  id_type id_;

public:

  distant_folder_impl_specific(id_type id)
    : id_{id}
  {}

  id_type id() const noexcept {return id_;}
};

/*------------------------------------------------------------------------------------------------*/

using distant_file_impl = any_file_impl<distant_file_impl_specific>;
using distant_folder_impl
  = any_folder_impl<distant_folder_impl_specific, distant_folder, distant_file>;

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
