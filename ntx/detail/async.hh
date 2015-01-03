#pragma once

#include <chrono>
#include <future>
#include <functional> // function
#include <thread>
#include <vector>

#include "ntx/configuration.hh"
#include "ntx/session.hh"
#include "ntx/fs.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Handle asynchronous tasks.
class async final
{
private:

  std::vector<std::future<void>> futures_;

public:

  async() = default;

  ~async()
  {
    for (auto& t : futures_)
    {
      t.get();
    }
  }

  async(const async&) = delete;
  async& operator= (const async&) = delete;

  async(async&&) = default;
  async& operator= (async&&) = default;

  void
  operator()(const std::function<void (void)>& t)
  {
    while (futures_.size() >= 8)
    {
      for (auto it = begin(futures_); it != end(futures_); ++it)
      {
        if (it->wait_for(std::chrono::nanoseconds{0}) == std::future_status::ready)
        {
          it->get();
          futures_.erase(it);
          break;
        }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds{50});
    }
    futures_.emplace_back(std::async(std::launch::async, t));
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
