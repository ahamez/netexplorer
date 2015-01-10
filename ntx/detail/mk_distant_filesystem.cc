#include <stdexcept>

#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <rapidjson/document.h>

#include "ntx/detail/mk_distant_filesystem.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

namespace /*anonymous*/ {

/*------------------------------------------------------------------------------------------------*/

distant_file
mk_file(const rapidjson::Value& v)
{
  return {v["id"].GetUint64(), v["name"].GetString(), v["size"].GetUint64(), v["hash"].GetString()};
}

/*------------------------------------------------------------------------------------------------*/

distant_folder
mk_folder(const rapidjson::Value& v)
{
  const auto& contents = v["content"];

  auto res = distant_folder{v["id"].GetUint64(), v["name"].GetString()};

  const auto& files = contents["files"];
  for (auto cit = files.Begin(); cit != files.End(); ++cit)
  {
    res.add(mk_file(*cit));
  }

  const auto& folders = contents["folders"];
  for (auto cit = folders.Begin(); cit != folders.End(); ++cit)
  {
    res.add(mk_folder(*cit));
  }

  return res;
}

/*------------------------------------------------------------------------------------------------*/

} // namespace anonymous

/*------------------------------------------------------------------------------------------------*/

distant_folder
mk_distant_folder(const configuration& conf, const session& s, id_type id)
{
  using namespace boost::network;

  auto parameters = uri::uri{conf.folder_url() + "/" + std::to_string(id)};
  parameters << uri::query("depth", uri::encoded("-1"));

  auto request = http::client::request{parameters};
  request << header("Connection", "close")
          << header("Token", s.token());

  const auto response = http::client{}.get(request);
  if (status(response) != 200u)
  {
    throw std::runtime_error("Can't get root folder");
  }

  auto d = rapidjson::Document{};
  if (d.Parse<0>(response.body().c_str()).HasParseError())
  {
    throw std::runtime_error("mk_distant_folder: can't read response");
  }
  return mk_folder(d);
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
