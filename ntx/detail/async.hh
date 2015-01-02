#pragma once

#include <chrono>
#include <future>
#include <vector>

#include "ntx/configuration.hh"
#include "ntx/session.hh"
#include "ntx/fs.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Handle asynchronous tasks.
/// @todo Limit the maximum number of tasks.
class async final
{
private:

  std::vector<std::future<void>> futures_;

public:

  async() = default;

  ~async()
  {
    for (auto& f : futures_)
    {
      try
      {
        f.get();
      }
      catch (std::exception& e)
      {
        /// @todo Register a callback to handle error of asynchronous tasks.
//        std::cerr << e.what() << '\n';
      }
    }
  }

  async(const async&) = delete;
  async& operator= (const async&) = delete;

  async(async&&) = default;
  async& operator= (async&&) = default;

  template <typename Task>
  void
  operator()(Task&& t)
  {
    futures_.emplace_back(std::async(std::launch::async, std::forward<Task>(t)));
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
