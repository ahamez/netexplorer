#pragma once

#include <future>
#include <functional> // function
#include <vector>

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
