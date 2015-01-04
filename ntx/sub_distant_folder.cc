#include <algorithm> // find_if
#include <stdexcept>

#include "ntx/sub_distant_folder.hh"
#include "ntx/detail/normalize_utf8.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

namespace /* anonymous */ {

distant_folder
sub_folder_impl(const distant_folder& f, const boost::filesystem::path& path)
{
  if (path.empty())
  {
    throw std::runtime_error("Invalid empty path");
  }

  auto cit = path.begin();
  if (cit->has_root_path())
  {
    ++cit;
  }

  const auto current_name = detail::normalize_utf8(cit->string());
  const auto search = std::find_if( begin(f.folders()), end(f.folders())
                                  , [&](const auto& sub){return sub.name() == current_name;});

  if (search == end(f.folders()))
  {
    throw std::runtime_error(path.string() + " not found on distant account.");
  }

  if (std::distance(cit, path.end()) == 1)
  {
    return *search;
  }

  auto sub = boost::filesystem::path{};
  for (++cit; cit != path.end(); ++cit)
  {
    sub /= *cit;
  }
  return sub_folder_impl(*search, sub);
}

} // namespace anonymous

/*------------------------------------------------------------------------------------------------*/

distant_folder
sub_folder(const distant_folder& f, const boost::filesystem::path& path)
{
  if (path.empty() or path == boost::filesystem::path{"/"})
  {
    return f;
  }
  return sub_folder_impl(f, path);
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
