#pragma once

#include <string>

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Normalize an UTF-8 string.
std::string
normalize_utf8(const std::string&);

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Normalize an UTF-8 temporary string.
std::string&
normalize_utf8(std::string&&);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
