#include <chrono>
#include <functional> // function
#include <iostream>
#include <thread>     // sleep_for

#include "ntx/detail/async.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

async::async(std::size_t max_tasks)
  : max_tasks_{max_tasks}
{}

/*------------------------------------------------------------------------------------------------*/

async::~async()
{
  for (auto& t : futures_)
  {
    try
    {
      t.get();
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
}

/*------------------------------------------------------------------------------------------------*/

void
async::operator()(const std::function<void (void)>& t)
{
  std::lock_guard<std::mutex> lock{mutex_};
  if (futures_.size() >= max_tasks_)
  {
    // Remove all finished tasks.
    for (auto it = begin(futures_); it != end(futures_); ++it)
    {
      if (it->wait_for(std::chrono::nanoseconds{0}) == std::future_status::ready)
      {
        try
        {
          it->get();
        }
        catch (const std::exception& e)
        {
          std::cerr << e.what() << '\n';
        }
        const auto to_erase = it++;
        futures_.erase(to_erase);
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds{50});
  }
  futures_.emplace_back(std::async(std::launch::async, t).share());
} // lock released

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
