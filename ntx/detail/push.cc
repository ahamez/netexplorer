#include <algorithm> // copy
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <rapidjson/document.h>

#include "ntx/detail/json_object.hh"
#include "ntx/detail/push.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;
using namespace boost::network;

/*------------------------------------------------------------------------------------------------*/

push::push(const configuration& conf, const session& s, async& a)
  : conf_{conf}, session_{s}, async_{a}
{}

/*------------------------------------------------------------------------------------------------*/

void
push::operator()(id_type parent_id, const local_folder& f, const fs::path& parent_path)
{
  std::cout << "[push] folder " << f.name() << " from " << parent_path.string() << '\n';

  auto request = http::client::request{conf_.folder_url()};
  request << header("Connection", "close")
          << header("Token", session_.token())
          << header("Content-Type", "application/json");

  const auto json = json_object("name", f.name(), "parent_id", parent_id);

  const auto response = http::client{}.post(request, json);
  if (status(response) != 201u)
  {
    throw std::runtime_error("Cannot create distant folder " + f.name());
  }

  const auto new_id = [&]
  {
    auto d = rapidjson::Document{};
    if (d.Parse<0>(response.body().c_str()).HasParseError())
    {
      throw std::runtime_error("Distant folder " + f.name() + " creation: can't read response");
    }
    return d["id"].GetUint64();
  }();

  for (const auto& sub_file : f.files())
  {
    (*this)(new_id, sub_file, parent_path / fs::path{f.name()});
  }

  for (const auto& sub_folder : f.folders()) // recurse in sub folders
  {
    (*this)(new_id, sub_folder, parent_path / fs::path{f.name()});
  }
}

/*------------------------------------------------------------------------------------------------*/

void
push::operator()(id_type parent_id, const local_file& f, const fs::path& parent_path)
{
  std::cout << "[push] file " << f.name() << " from " << parent_path.string() << '\n';

  async_([=]
  {
    try
    {
      // Create distant placeholder.
      const auto file_id = [&]
      {
        auto request = http::client::request{conf_.file_url()};
        request << header("Connection", "close")
                << header("Token", session_.token())
                << header("Content-Type", "application/json");

        const auto json = json_object("name", f.name(), "parent_id", parent_id, "hash", f.md5());

        const auto response = http::client{}.post(request, json);
        if (status(response) != 201u)
        {
          throw std::runtime_error( "Cannot create distant file " + f.name() + "(status="
                                  + std::to_string(status(response)) + ")");
        }

        auto d = rapidjson::Document{};
        if (d.Parse<0>(response.body().c_str()).HasParseError())
        {
          throw std::runtime_error("Distant file " + f.name() + " creation: can't read response");
        }
        return d["id"].GetUint64();
      }();

      // Effectively upload file.
      {
        auto parameters = uri::uri{conf_.file_url()};
        parameters << uri::path("/")
                   << uri::path(std::to_string(file_id))
                   << uri::path("/upload");

        auto request = http::client::request{parameters};
        request << header("Connection", "close")
                << header("Token", session_.token())
                << header("Content-Length", std::to_string(f.size()));

        const auto file_path = parent_path / fs::path{f.name()};
        auto&& file = fs::ifstream{file_path, std::ios::binary};
        if (not file.is_open())
        {
          throw std::runtime_error("Can't read file to be uploaded " + file_path.string());
        }
        auto str = std::string{};
        str.reserve(f.size());
        std::copy( std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{}
                 , std::back_inserter(str));

        const auto response = http::client{}.put(request, str);
        if (status(response) != 200u)
        {
          throw std::runtime_error( "Cannot upload file " + file_path.string() + " status = "
                                  + std::to_string(status(response)));
        }
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  });
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
