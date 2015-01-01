#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <rapidjson/document.h>

#include "account.hh"
#include "len.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// JSON parser ("à la SAX") to read an account.
struct account_parser
  : public rapidjson::BaseReaderHandler<rapidjson::UTF8<>, account_parser>
{
  enum class state_type {other, roots, roots_array} state;
  boost::container::flat_set<unsigned long>& roots;

  account_parser(boost::container::flat_set<unsigned long>& r)
  noexcept
    : state(state_type::other), roots(r)
  {}

  bool
  Key(const char* str, rapidjson::SizeType length, bool)
  noexcept
  {
    static constexpr auto roots_str = "roots";
    if (length == detail::len(roots_str) and std::equal(roots_str, roots_str + length, str))
    {
      state = state_type::roots;
    }
    return true;
  }

  bool
  StartArray()
  noexcept
  {
    if (state == state_type::roots)
    {
      state = state_type::roots_array;
    }
    return true;
  }

  bool
  Uint(unsigned x)
  const
  {
    if (state == state_type::roots_array)
    {
      roots.insert(x);
    }
    return true;
  }

  bool Default()
  {
    state = state_type::other;
    return true;
  }
};

/*------------------------------------------------------------------------------------------------*/

account::account(const configuration& conf, const session& s)
  : roots_{/*will be updated in the constructor body*/}
{
  using namespace boost::network;
  auto client  = http::client{};
  auto request = http::client::request{conf.account_url()};
  request << header("Connection", "close")
          << header("Token", s.token());

  const auto response = client.get(request);
  if (status(response) != 200u)
  {
    throw std::runtime_error("Can't read account");
  }

  const auto json_response = static_cast<std::string>(body(response));
  auto ss = rapidjson::StringStream{json_response.c_str()};
  auto h  = account_parser{roots_};
  /// @todo handle parse errors
  rapidjson::Reader{}.Parse(ss, h); // will update roots_
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
