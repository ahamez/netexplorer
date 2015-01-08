#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>
#include <boost/range/algorithm/copy.hpp>

#include "ntx/detail/pull.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;
using namespace boost::network;

/*------------------------------------------------------------------------------------------------*/

pull::pull(const configuration& conf, const session& s, async& a)
  : conf_{conf}, session_{s}, async_{a}
{}

/*------------------------------------------------------------------------------------------------*/

void
pull::operator()(id_type parent_id, const distant_folder& f, const fs::path& parent_path)
{
  std::cout << "[pull] folder " << f.name() << " to " << parent_path.string() << '\n';

  // No need to download anything.
  fs::create_directory(parent_path / fs::path{f.name()});

  for (const auto& sub_file : f.files())
  {
    (*this)(f.id(), sub_file, parent_path / fs::path{f.name()});
  }

  for (const auto& sub_folder : f.folders())
  {
    (*this)(f.id(), sub_folder, parent_path / fs::path{f.name()});
  }
}

/*------------------------------------------------------------------------------------------------*/

/// @todo Try downloading some more times in case of failure.
void
pull::operator()(id_type parent_id, const distant_file& f, const fs::path& parent_path)
{
  std::cout << "[pull] file " << f.name() << " to " << parent_path.string() << '\n';

  async_([=]
  {
    try
    {
      auto parameters = uri::uri{};
      parameters << uri::path(conf_.file_url())
                 << uri::path("/")
                 << uri::path(std::to_string(f.id()))
                 << uri::path("/download");

      auto request = http::client::request{parameters};
      request << header("Connection", "close")
              << header("Token", session_.token());

      const auto file_path = parent_path / fs::path{f.name()};
      auto&& file = fs::ofstream{file_path, std::ios::binary};
      if (not file.is_open())
      {
        std::cerr << "Can't write to " << file_path.string() << '\n';
        return;
      }
      auto fstream = std::ostreambuf_iterator<char>{file};

      const auto response = http::client{}.get( request
                                                // Write to file on the fly
                                              , [&](const auto& range, const auto& /*error*/)
                                                {
                                                  boost::copy(range, fstream);
                                                });
      if (status(response) != 200u)
      {
        std::cerr << "Can't download " << f.name() << '\n';
        fs::remove(file_path);
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
