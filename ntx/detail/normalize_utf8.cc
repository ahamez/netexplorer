#include <unilib/uninorms.h>
#include <unilib/utf8.h>

#include "ntx/detail/normalize_utf8.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

std::string
normalize_utf8(const std::string& s)
{
  auto copy = s;
  auto tmp = std::u32string{};
  tmp.reserve(s.size());
  ufal::unilib::utf8::decode(copy, tmp);
  ufal::unilib::uninorms::nfc(tmp);
  ufal::unilib::utf8::encode(tmp, copy);
  return copy;
}

/*------------------------------------------------------------------------------------------------*/

std::string&
normalize_utf8(std::string&& s)
{
  auto tmp = std::u32string{};
  tmp.reserve(s.size());
  ufal::unilib::utf8::decode(s, tmp);
  ufal::unilib::uninorms::nfc(tmp);
  ufal::unilib::utf8::encode(tmp, s);
  return s;
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
