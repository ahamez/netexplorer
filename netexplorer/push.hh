#pragma once

#include "async.hh"
#include "configuration.hh"
#include "session.hh"
#include "fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Action to perform when a file or folder is missing on the distant filesystem.
class push final
{
private:

  const configuration& conf_;
  const session& session_;
  detail::async async_;

public:

  push(const configuration&, const session&);

  void operator()(ntx::id_type, const ntx::folder&, const boost::filesystem::path&);
  void operator()(ntx::id_type, const ntx::file&, const boost::filesystem::path&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
