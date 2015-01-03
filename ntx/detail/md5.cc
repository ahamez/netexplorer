#include <array>
#include <algorithm> // copy
#include <fstream>
#include <iomanip>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include <openssl/md5.h>

#include "ntx/detail/md5.hh"

namespace ntx {
namespace detail {

namespace fs = boost::filesystem;

/*------------------------------------------------------------------------------------------------*/

/// @todo Use a better ('C++-ier') MD5.
md5_digest_type
md5(const boost::filesystem::path& p)
{
  static constexpr auto buffer_size = 4096u;

  const auto sz = file_size(p);

  auto md5 = std::array<unsigned char, MD5_DIGEST_LENGTH>{};
  auto buffer = std::array<char, buffer_size>{};

  auto&& file  = fs::ifstream{p, std::ios::binary};
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

  return ss.str();
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
