#pragma once

#include <memory>
#include <utility>     // forward
#include <type_traits> // enable_if

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
template <bool Cond, typename Ret>
using enable_if_t = typename std::enable_if<Cond, Ret>::type;

/*------------------------------------------------------------------------------------------------*/

/// @internal
template <typename T, typename... Args>
std::unique_ptr<T>
make_unique(Args&&... args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
