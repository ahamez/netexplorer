#pragma once

#include <chrono>
#include <iosfwd>
#include <future>
#include <vector>

#include "configuration.hh"
#include "session.hh"
#include "fs.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @brief Launch a maximum number of asynchronous tasks.
class async final
{
private:

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
    // Cheap way of limiting the maximum number of concurrent tasks.
    while (futures_.size() >= max_concurrent_tasks_)
    {
      for (auto it = begin(futures_); it != end(futures_); ++it)
      {
        if (it->wait_for(std::chrono::milliseconds(100)) == std::future_status::ready)
        {
          try
          {
            it->get();
          }
          catch (std::exception& e)
          {
            std::cerr << e.what() << '\n';
          }
          futures_.erase(it);
          break;
        }
      }
    }
    futures_.emplace_back(std::async(std::launch::async, std::forward<Task>(t)));
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
