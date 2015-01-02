#include <fstream>
#include <iosfwd>
#include <iterator>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#define BOOST_NETWORK_ENABLE_HTTPS
#include <boost/network/protocol/http/client.hpp>
#include <boost/range/algorithm/copy.hpp>

#include "pull.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;
using namespace boost::network;

/*------------------------------------------------------------------------------------------------*/

pull::pull(const configuration& conf, const session& s)
  : conf_{conf}, session_{s}, async_{conf_.max_dl_tasks()}
{}

/*------------------------------------------------------------------------------------------------*/

void
pull::operator()(ntx::id_type parent_id, const ntx::folder& f, const fs::path& parent_path)
{
  std::cout << "[pull] folder " << f.name() << " @ " << parent_path.string()
            << " (parent_id = " << parent_id << ")\n";

  // No need to download anything.
  fs::create_directory(parent_path / fs::path{f.name()});

  for (const auto& sub_file : f.files())
  {
    (*this)(*f.id(), sub_file, parent_path / fs::path{f.name()});
  }

  for (const auto& sub_folder : f.folders())
  {
    (*this)(*f.id(), sub_folder, parent_path / fs::path{f.name()});
  }
}

/*------------------------------------------------------------------------------------------------*/

void
pull::operator()(ntx::id_type parent_id, const ntx::file& f, const fs::path& parent_path)
{
  std::cout << "[pull] file " << f.name() << " @ " << parent_path.string()
            << " (parent_id = " << parent_id << ")\n";

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

    const auto file_path = parent_path / fs::path{f.name()};
    auto&& file = fs::ofstream{file_path, std::ios::binary};
    if (not file.is_open())
    {
      throw std::runtime_error("Can't write to " + file_path.string());
    }
    auto fstream = std::ostreambuf_iterator<char>{file};

    /// @todo Erase file if any error happen.w
    const auto response = http::client{}.get( request
                                            , [&](const auto& range, const auto& /*error*/)
                                              {
                                                boost::copy(range, fstream);
                                              });
    if (status(response) != 200u)
    {
      throw std::runtime_error("Can't download " + f.name());
    }
  });
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
