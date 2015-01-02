#pragma once

#include "ntx/configuration.hh"
#include "ntx/session.hh"
#include "ntx/fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Action to perform when a file or folder is missing on the local filesystem.
class handle_conflict final
{
private:

  const configuration& conf_;
  const session& session_;

public:

  handle_conflict(const configuration&, const session&);

  void operator()(ntx::id_type, const ntx::file&, const boost::filesystem::path&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
