#include <iostream>

#include <boost/filesystem.hpp>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <rapidjson/document.h>

#include "push.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;
using namespace boost::network;

/*------------------------------------------------------------------------------------------------*/

void
push::operator()(ntx::id_type parent_id, const ntx::folder& f, const fs::path& path)
const
{
  std::cout << "[push] folder " << f.name() << " @ " << path.string()
            << " (parent_id = " << parent_id << ")\n";

  auto request = http::client::request{conf_.folder_url()};
  request << header("Connection", "close")
          << header("Token", session_.token())
          << header("Content-Type", "application/json");

  const auto json
    = "{\"name\":\"" + f.name() + "\",\"parent_id\":\"" + std::to_string(parent_id) + "\"}";

  const auto response = http::client{}.post(request, json);
  if (status(response) != 200u)
  {
    // Creation fails on first call???
    const auto response2 = http::client{}.post(request, json);
    if (status(response2) != 200u)
    {
      throw std::runtime_error("Cannot create distant folder " + f.name());
    }
  }

  const auto new_id = [&]
  {
    auto new_id = 0ul;
    auto d = rapidjson::Document{};
    if (not d.Parse<0>(response.body().c_str()).HasParseError())
    {
      new_id = d["id"].GetUint();
    }
    else
    {
      throw std::runtime_error("Distant folder " + f.name() + " creation: can't read response");
    }
    return new_id;
  }();

  for (const auto& sub_file : f.files())
  {
    (*this)(new_id, sub_file, path / fs::path{f.name()});
  }

  for (const auto& sub_folder : f.folders())
  {
    (*this)(new_id, sub_folder, path / fs::path{f.name()});
  }
}

/*------------------------------------------------------------------------------------------------*/

void
push::operator()(ntx::id_type, const ntx::file& f, const fs::path& path)
const
{
  std::cout << "[push] file " << f.name() << " @ " << path.string() << '\n';
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx

