#include <chrono>
#include <functional> // function
#include <thread>     // sleep_for

#include "ntx/detail/async.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

async::~async()
{
  for (auto& t : futures_)
  {
    t.get();
  }
}

/*------------------------------------------------------------------------------------------------*/

void
async::operator()(const std::function<void (void)>& t)
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

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
