#pragma once

#include "ntx/configuration.hh"
#include "ntx/session.hh"
#include "ntx/fs.hh"
#include "ntx/detail/async.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Action to perform when a file or folder is missing on the distant filesystem.
class push final
{
private:

  const configuration& conf_;
  const session& session_;
  async async_;

public:

  push(const configuration&, const session&);

  void operator()(id_type, const folder&, const boost::filesystem::path&);
  void operator()(id_type, const file&, const boost::filesystem::path&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
