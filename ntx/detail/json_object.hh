#pragma once

#include <string>

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Create a JSON representation of a sequence of key-values.
template <typename... Args>
std::string
json_object(Args&&... args);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx

#include "ntx/detail/json_object.tcc"
