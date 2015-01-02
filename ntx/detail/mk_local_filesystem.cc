#include <array>
#include <algorithm> // copy
#include <fstream>
#include <iomanip>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <openssl/md5.h>

#include "ntx/detail/mk_local_filesystem.hh"

namespace ntx {
namespace detail {

namespace fs = boost::filesystem;

/*------------------------------------------------------------------------------------------------*/

namespace /* anonymous */ {

/// @todo Use a better ('C++-ier') MD5.
file
mk_local_file(const fs::path& p)
{
  static constexpr auto buffer_size = 4096u;

  const auto sz = file_size(p);

  auto md5 = std::array<unsigned char, MD5_DIGEST_LENGTH>{};
  auto buffer = std::array<char, buffer_size>{};

  auto&& file  = std::ifstream{p.string(), std::ios::binary};
  auto fstream = std::istreambuf_iterator<char>{file};

  auto ctx = MD5_CTX{};
  MD5_Init(&ctx);

  auto nb_loops = sz / buffer_size;
  const auto rem = sz % buffer_size;

  while (nb_loops--)
  {
    std::copy_n(fstream, buffer_size, begin(buffer));
    ++fstream; // actual reading of the next character
    MD5_Update(&ctx, buffer.data(), buffer_size);
  }
  std::copy_n(fstream, rem, begin(buffer));
  MD5_Update(&ctx, buffer.data(), rem);
  MD5_Final(md5.data(), &ctx);

  // create hexadecimal version
  std::stringstream ss;
  for (auto c : md5)
  {
    ss << std::hex << std::setw(2) << std::setfill('0') << +c;
  }

  return {p.filename().string(), sz, ss.str()};
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
