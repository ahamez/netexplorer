#pragma once

#include <chrono>
#include <iosfwd>
#include <future>
#include <vector>

#include "ntx/configuration.hh"
#include "ntx/session.hh"
#include "ntx/fs.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Launch a maximum number of asynchronous tasks.
class async final
{
private:

  /// @todo Use this information
  std::size_t max_concurrent_tasks_;
  std::vector<std::future<void>> futures_;

public:

  async(std::size_t max_concurrent_tasks)
    : max_concurrent_tasks_{max_concurrent_tasks}, futures_{}
  {}

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
        std::cerr << e.what() << '\n';
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
