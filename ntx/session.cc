#include <stdexcept>
#include <unordered_set>

#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <rapidjson/document.h>

#include "ntx/session.hh"
#include "ntx/detail/json_object.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

using namespace boost::network;

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
connect(const configuration& conf)
{
  auto request = http::client::request{conf.auth_url()};
  request << header("Connection", "close")
          << header("Content-Type", "application/json");

  const auto json = detail::json_object("user", conf.user(), "password", conf.password());
  const auto response = http::client{}.post(request, json);

  if (status(response) != 200u)
  {
    throw std::runtime_error("Cannot authenticate");
  }

  auto d = rapidjson::Document{};
  if (d.Parse<0>(response.body().c_str()).HasParseError())
  {
    throw std::runtime_error("Connecting session: can't read response");
  }
  return {std::string{d["token"].GetString()}};
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
