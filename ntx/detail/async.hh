#pragma once

#include <chrono>
#include <future>
#include <functional> // function
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
public:

  using error_callback_type = std::function<void (const std::exception&)>;

private:

  error_callback_type error_callback_;
  std::vector<std::future<void>> futures_;

public:

  async(const error_callback_type&& callback)
    : error_callback_{callback}
  {}

  ~async()
  {
    for (auto& f : futures_)
    {
      try
      {
        f.get();
      }
      catch (const std::exception& e)
      {
        error_callback_(e);
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
