#include <fstream>
#include <iosfwd>
#include <iterator>

#include "ntx/detail/conflict.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

bool
conflict::operator()(const ntx::distant_file& lhs, const ntx::local_file& rhs)
const noexcept
{
  return lhs.size() != rhs.size() or lhs.md5() != rhs.md5();
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
