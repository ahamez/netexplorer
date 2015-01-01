#pragma once

#include <future>
#include <vector>

#include "configuration.hh"
#include "session.hh"
#include "fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Action to perform when a file or folder is missing on the local filesystem.
class pull final
{
private:

  const configuration& conf_;
  const session& session_;
  std::vector<std::future<void>> futures_;

public:

  pull(const configuration&, const session&);
  ~pull();

  void operator()(ntx::id_type, const ntx::folder&, const boost::filesystem::path&);
  void operator()(ntx::id_type, const ntx::file&, const boost::filesystem::path&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
