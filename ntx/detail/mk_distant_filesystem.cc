#include <cassert>
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
  assert(v.IsObject());
  assert(v.HasMember("name"));
  assert(v.HasMember("id"));
  assert(v.HasMember("size"));
  assert(v.HasMember("hash"));

  if (v["hash"].GetStringLength() != 32)
  {
    throw std::runtime_error("Invalid hash on server");
  }

  return { v["id"].GetUint64()
         , std::string{v["name"].GetString(), v["name"].GetStringLength()}
         , v["size"].GetUint64()
         , std::string{v["hash"].GetString(), v["hash"].GetStringLength()}};
}

/*------------------------------------------------------------------------------------------------*/

distant_folder
mk_folder(const rapidjson::Value& v)
{
  assert(v.IsObject());
  assert(v.HasMember("content"));

  const auto& contents = v["content"];
  assert(contents.IsObject());
  assert(contents.HasMember("files"));
  assert(contents.HasMember("folders"));

  auto res = distant_folder{v["id"].GetUint64(), v["name"].GetString()};

  const auto& files = contents["files"];
  assert(files.IsArray());
  for (auto cit = files.Begin(); cit != files.End(); ++cit)
  {
    res.add_file(mk_file(*cit));
  }

  const auto& folders = contents["folders"];
  assert(folders.IsArray());
  for (auto cit = folders.Begin(); cit != folders.End(); ++cit)
  {
    res.add_folder(mk_folder(*cit));
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

  const auto json_response = static_cast<std::string>(body(response));

  rapidjson::Document d;
  d.Parse<0>(&json_response[0]);
  return mk_folder(d);
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
