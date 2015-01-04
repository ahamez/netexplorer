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

  // The shared_future is important: as futures are borrowed from other threads.
  std::list<std::shared_future<void>> futures_;
  std::mutex mutex_;
  std::size_t max_tasks_;

public:

  async(std::size_t max_tasks);
  ~async();

  async(const async&) = delete;
  async& operator= (const async&) = delete;

  async(async&&) = default;
  async& operator= (async&&) = default;

  /// @brief Add a task to be eventually performed.
  void
  operator()(const std::function<void (void)>&);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
