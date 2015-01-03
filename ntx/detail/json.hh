#pragma once

#include <sstream>
#include <string>
#include <type_traits> // enable_if, is_integral
#include <utility>     //forward

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

template <typename Key, typename Value>
std::enable_if_t<not std::is_integral<Value>::value, void>
key_value(std::stringstream& ss, Key&& key, Value&& value)
{
  ss << '\"' << key << '\"' << ':' << '\"' << value << '\"';
}


template <typename Key, typename Value>
std::enable_if_t<std::is_integral<Value>::value, void>
key_value(std::stringstream& ss, Key&& key, Value&& value)
{
  ss << '\"' << key << '\"' << ':' << std::to_string(value);
}

/*------------------------------------------------------------------------------------------------*/

/// @internal
template <typename Key, typename Value>
void
json_obj_impl(std::stringstream& ss, Key&& key, Value&& value)
{
  key_value(ss, std::forward<Key>(key), std::forward<Value>(value));
}

/// @internal
template <typename Key, typename Value, typename... Args>
void
json_obj_impl(std::stringstream& ss, Key&& key, Value&& value, Args&&... args)
{
  key_value(ss, std::forward<Key>(key), std::forward<Value>(value));
  ss << ',';
  json_obj_impl(ss, std::forward<Args>(args)...);
}

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief Create a JSON representation of a sequence of key-values.
template <typename... Args>
std::string
json_obj(Args&&... args)
{
  static_assert(sizeof...(Args) % 2 == 0, "Invalid number of arguments");
  auto ss = std::stringstream{};
  ss << "{";
  json_obj_impl(ss, std::forward<Args>(args)...);
  ss << "}";
  return ss.str();
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
