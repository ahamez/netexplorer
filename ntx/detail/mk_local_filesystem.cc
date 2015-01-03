#include "ntx/detail/md5.hh"
#include "ntx/detail/mk_local_filesystem.hh"

namespace ntx {
namespace detail {

namespace fs = boost::filesystem;

/*------------------------------------------------------------------------------------------------*/

namespace /* anonymous */ {

file
mk_local_file(const fs::path& p)
{
  return {p.filename().string(), file_size(p), md5(p)};
}

} // namespace anonymous

/*------------------------------------------------------------------------------------------------*/

folder
mk_local_folder(const fs::path& p)
{
  auto res = folder{p.filename().string()};
  for (auto cit = fs::directory_iterator{p}; cit != fs::directory_iterator{}; ++cit)
  {
    if (is_regular_file(*cit))
    {
      res.add_file(mk_local_file(*cit));
    }
    else if (is_directory(*cit))
    {
      res.add_folder(mk_local_folder(*cit));
    }
  }
  return res;
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
