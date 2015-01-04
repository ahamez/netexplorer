#include <utf8proc/utf8proc.h>

#include "ntx/detail/normalize_utf8.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

std::string
normalize_utf8(const std::string& s)
{
  uint8_t* dst;
  const auto len = utf8proc_map( reinterpret_cast<const uint8_t*>(s.c_str()), 0, &dst
                               , UTF8PROC_NULLTERM | UTF8PROC_COMPOSE);
  if (len < 0)
  {
    throw std::runtime_error("Can't normalize UTF8 string");
  }
  auto res = std::string{};
  res.reserve(len);
  res.assign(reinterpret_cast<char*>(dst));
  free(dst); // dst has been allocated with malloc() by utf8proc_map
  return res;
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
