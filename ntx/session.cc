#include <unordered_set>

#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <rapidjson/document.h>

#include "ntx/session.hh"
#include "ntx/detail/json.hh"
#include "ntx/detail/len.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

using namespace boost::network;

/*------------------------------------------------------------------------------------------------*/

/// JSON parser ("à la SAX") to get the authentication token.
struct token_parser
  : public rapidjson::BaseReaderHandler<rapidjson::UTF8<>, token_parser>
{
  bool token_found;
  std::string& token;

  token_parser(std::string& tk)
  noexcept
     : token_found{false}, token{tk}
  {}

  bool
  Key(const char* str, rapidjson::SizeType length, bool)
  noexcept
  {
    static constexpr auto token_str = "token";
    token_found = length == detail::len(token_str)
                  and std::equal(token_str, token_str + length, str);
    return true;
  }

  bool
  String(const char* str, rapidjson::SizeType length, bool)
  noexcept
  {
    if (token_found)
    {
      token.assign(str, length);
      return false; // stop parsing
    }
    return true;
  }
};

/*------------------------------------------------------------------------------------------------*/

session::session(const std::string& token)
  : token_{token}
{}

/*------------------------------------------------------------------------------------------------*/

session::session(std::string&& token)
noexcept
  : token_{std::move(token)}
{}

/*------------------------------------------------------------------------------------------------*/

session
connect(const configuration& conf, const credentials& creds)
{
  auto request = http::client::request{conf.auth_url()};
  request << header("Connection", "close")
          << header("Content-Type", "application/json");

  const auto json = detail::json_obj("user", creds.login(), "password", creds.password());
  const auto response = http::client{}.post(request, json);

  if (status(response) != 200u)
  {
    throw std::runtime_error("Cannot authenticate");
  }

  auto token = std::string{};

  const auto json_response = static_cast<std::string>(body(response));
  auto ss = rapidjson::StringStream{response.body().c_str()};
  auto h  = token_parser{token};
  /// @todo handle parse errors
  rapidjson::Reader{}.Parse(ss, h);

  return {std::move(token)};
}

/*------------------------------------------------------------------------------------------------*/

void
disconnect(const configuration& conf, const session& s)
{
  auto request = http::client::request{conf.auth_url()};
  request << header("Connection", "close") << header("Token", s.token());
  http::client{}.delete_(request);
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
