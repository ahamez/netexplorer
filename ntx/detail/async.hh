#pragma once

#include <future>
#include <functional> // function
#include <mutex>
#include <list>

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Handle asynchronous tasks.
class async final
{
private:

  std::list<std::future<void>> futures_;
  std::mutex mutex_;
  std::size_t max_tasks_;

public:

  async(std::size_t max_tasks);
  ~async();

  async(const async&) = delete;
  async& operator= (const async&) = delete;

  async(async&&) = default;
  async& operator= (async&&) = default;

  void
  operator()(const std::function<void (void)>&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
