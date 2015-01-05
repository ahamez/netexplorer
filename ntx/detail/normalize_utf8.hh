#pragma once

#include <string>

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
std::string
normalize_utf8(const std::string&);

/// @internal
std::string&
normalize_utf8(std::string&&);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
