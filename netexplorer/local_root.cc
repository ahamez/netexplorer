#include <array>
#include <fstream>
#include <iomanip>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <openssl/md5.h>

#include "local_root.hh"

namespace ntx {
namespace /*anonymous*/ {

namespace fs = boost::filesystem;

/*------------------------------------------------------------------------------------------------*/

/// @todo Use a better ('C++-ier') MD5.
file
mk_file(const fs::path& p)
{
  auto buffer = std::array<char, 4096>{};
  auto md5 = std::array<unsigned char, 16>{};

  auto ctx = MD5_CTX{};
  MD5_Init(&ctx);

  auto&& file = fs::ifstream{p, std::ios::binary};
  auto fstream = std::istreambuf_iterator<char>{file};

  const auto sz = file_size(p);
  auto nb_loops = sz / 4096;
  const auto rem = sz - (nb_loops * 4096);

  while (nb_loops--)
  {
    std::copy_n(fstream, 4096, begin(buffer));
    ++fstream;
    MD5_Update(&ctx, buffer.data(), 4096);
  }
  std::copy_n(++fstream, rem, begin(buffer));
  MD5_Update(&ctx, buffer.data(), rem);
  MD5_Final(md5.data(), &ctx);

  // create hexadecimal version
  std::stringstream ss;
  for (auto c : md5)
  {
    ss << std::hex <<  std::setw(2) << std::setfill('0') << +c;
  }

  return {p.filename().string(), ss.str()};
}

/*------------------------------------------------------------------------------------------------*/

folder
mk_folder(const fs::path& p)
{
  auto res = folder(basename(p));
  for (auto cit = fs::directory_iterator{p}; cit != fs::directory_iterator{}; ++cit)
  {
    if (is_regular_file(*cit))
    {
      res.add_file(mk_file(*cit));
    }
    else if (is_directory(*cit))
    {
      res.add_folder(mk_folder(*cit));
    }
  }
  return res;
}

/*------------------------------------------------------------------------------------------------*/

} // namespace anonymous

/*------------------------------------------------------------------------------------------------*/

folder
get_local_root(const configuration& conf)
{
  return mk_folder(conf.local_root());
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
