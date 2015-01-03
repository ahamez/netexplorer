#pragma once

#include <boost/filesystem.hpp>

#include "ntx/types.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @brief Return the MD5 digest of a file.
md5_digest_type
md5(const boost::filesystem::path&);

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
