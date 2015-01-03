#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>
#include <boost/range/algorithm/copy.hpp>

#include "ntx/detail/handle_conflict.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;
using namespace boost::network;

/*------------------------------------------------------------------------------------------------*/

handle_conflict::handle_conflict(const configuration& conf, const session& s)
  : conf_{conf}, session_{s}, async_{}
{}

/*------------------------------------------------------------------------------------------------*/

void
handle_conflict::operator()(id_type parent_id, const file& f, const fs::path& parent_path)
{
  std::cout << "[conflict] file " << f.name() << " @ " << parent_path.string() << '\n';

  async_([=]
  {
    auto parameters = uri::uri{};
    parameters << uri::path(conf_.file_url())
               << uri::path("/")
               << uri::path(std::to_string(*f.id()))
               << uri::path("/download");

    auto request = http::client::request{parameters};
    request << header("Connection", "close")
            << header("Token", session_.token());

    const auto conflict_folder = conf_.conflict_folder() / parent_path;
    const auto file_path = conflict_folder / fs::path{f.name()};
    if (not exists(conflict_folder))
    {
      create_directories(conflict_folder);
    }
    auto&& file = fs::ofstream{file_path, std::ios::binary};
    if (not file.is_open())
    {
      std::cerr << "Can't write to " << file_path.string() << '\n';
      return;
    }
    auto fstream = std::ostreambuf_iterator<char>{file};

    const auto response = http::client{}.get( request
                                            , [&](const auto& range, const auto& /*error*/)
                                              {
                                                boost::copy(range, fstream);
                                              });
    if (status(response) != 200u)
    {
      std::cerr << "Can't download " << f.name() << '\n';
      fs::remove(file_path);
    }
  });
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
