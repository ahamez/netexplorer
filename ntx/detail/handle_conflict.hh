#pragma once

#include "ntx/configuration.hh"
#include "ntx/session.hh"
#include "ntx/distant_filesystem.hh"
#include "ntx/detail/async.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Action to perform when a file is conflicting.
class handle_conflict final
{
private:

  const configuration& conf_;
  const session& session_;
  async async_;

public:

  handle_conflict(const configuration&, const session&);

  void operator()(id_type, const distant_file&, const boost::filesystem::path&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
