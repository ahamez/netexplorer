#pragma once

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

constexpr
inline
std::size_t
len(const char* str, std::size_t i = 0)
noexcept
{
  return str[i] == '\0' ? 0 : 1 + len(str, i + 1);
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
