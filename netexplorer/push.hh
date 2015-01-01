#pragma once

#include "configuration.hh"
#include "session.hh"
#include "fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Action to perform when a file or folder is missing on the distant filesystem.
class push
{
private:

  const configuration& conf_;
  const session& session_;

public:

  push(const configuration& conf, const session& s)
    : conf_{conf}, session_{s}
  {}

  void operator()(ntx::id_type, const ntx::folder&, const boost::filesystem::path&) const;
  void operator()(ntx::id_type, const ntx::file&, const boost::filesystem::path&) const;
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
