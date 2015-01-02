#include <fstream>
#include <iosfwd>
#include <iterator>

#include "ntx/detail/conflict.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

bool
conflict::operator()(const ntx::file& lhs, const ntx::file& rhs)
const noexcept
{
  return lhs.size() != rhs.size() or lhs.md5() != rhs.md5();
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
