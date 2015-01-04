#pragma once

#include "ntx/configuration.hh"
#include "ntx/session.hh"
#include "ntx/distant_filesystem.hh"
#include "ntx/detail/async.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Action to perform when a file or folder is missing on the local filesystem.
class pull final
{
private:

  const configuration& conf_;
  const session& session_;
  async& async_;

public:

  pull(const configuration&, const session&, async&);

  void operator()(id_type, const distant_folder&, const boost::filesystem::path&);
  void operator()(id_type, const distant_file&, const boost::filesystem::path&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
