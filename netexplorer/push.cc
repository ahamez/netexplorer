#include <chrono>
#include <fstream>
#include <iosfwd>
#include <iterator>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>

#include <rapidjson/document.h>

#include "push.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;
using namespace boost::network;

/*------------------------------------------------------------------------------------------------*/

push::push(const configuration& conf, const session& s)
  : conf_{conf}, session_{s}
{}

/*------------------------------------------------------------------------------------------------*/

push::~push()
{
  for (auto& f : futures_)
  {
    try
    {
      f.get();
    }
    catch (std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
}

/*------------------------------------------------------------------------------------------------*/

void
push::operator()(ntx::id_type parent_id, const ntx::folder& f, const fs::path& parent_path)
{
  std::cout << "[push] folder " << f.name() << " @ " << parent_path.string()
            << " (parent_id = " << parent_id << ")\n";

  auto request = http::client::request{conf_.folder_url()};
  request << header("Connection", "close")
          << header("Token", session_.token())
          << header("Content-Type", "application/json");

  const auto json
    = "{\"name\":\"" + f.name() + "\",\"parent_id\":\"" + std::to_string(parent_id) + "\"}";

  const auto response = http::client{}.post(request, json);
  if (status(response) != 201u)
  {
    throw std::runtime_error("Cannot create distant folder " + f.name());
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
    (*this)(new_id, sub_file, parent_path / fs::path{f.name()});
  }

  for (const auto& sub_folder : f.folders())
  {
    (*this)(new_id, sub_folder, parent_path / fs::path{f.name()});
  }
}

/*------------------------------------------------------------------------------------------------*/

void
push::operator()(ntx::id_type parent_id, const ntx::file& f, const fs::path& parent_path)
{
  std::cout << "[push] file " << f.name() << " @ " << parent_path.string()
            << " (parent_id = " << parent_id << ")\n";

  auto future = std::async(std::launch::async, [=,&f]
  {
    // Create distant placeholder.
    const auto file_id = [&]
    {
      auto request = http::client::request{conf_.file_url()};
      request << header("Connection", "close")
              << header("Token", session_.token())
              << header("Content-Type", "application/json");

      const auto json
        = "{\"name\":\"" + f.name() + "\",\"parent_id\":\"" + std::to_string(parent_id)
        + "\",\"hash\":\"" + f.md5() + "\"}";

      const auto response = http::client{}.post(request, json);
      if (status(response) != 201u)
      {
        throw std::runtime_error( "Cannot create distant file " + f.name() + ": "
                                + std::to_string(status(response)));
      }

      auto file_id = 0ul;
      auto d = rapidjson::Document{};
      if (not d.Parse<0>(response.body().c_str()).HasParseError())
      {
        file_id = d["id"].GetUint();
      }
      else
      {
        throw std::runtime_error("Distant file " + f.name() + " creation: can't read response");
      }
      return file_id;
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
        std::cerr << "'" <<file_path.string() << "'\n";
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
  });

  // Cheap way of limiting the maximum number of concurrent uploads.
  while (futures_.size() >= conf_.max_ul_tasks())
  {
    for (auto it = begin(futures_); it != end(futures_); ++it)
    {
      if (it->wait_for(std::chrono::milliseconds(100)) == std::future_status::ready)
      {
        try
        {
          it->get();
        }
        catch (std::exception& e)
        {
          std::cerr << e.what() << '\n';
        }
        futures_.erase(it);
        break;
      }
    }
  }
  futures_.emplace_back(std::move(future));
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
