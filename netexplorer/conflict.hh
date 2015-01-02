#pragma once

#include "configuration.hh"
#include "session.hh"
#include "fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Action to perform when a file or folder is missing on the local filesystem.
class conflict final
{
private:

  const configuration& conf_;
  const session& session_;

public:

  conflict(const configuration&, const session&);

  void operator()(ntx::id_type, const ntx::file&, const boost::filesystem::path&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
