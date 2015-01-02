#include <fstream>
#include <iosfwd>
#include <iterator>

#include "ntx/conflict.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

bool
conflict::operator()(const ntx::file& lhs, const ntx::file& rhs)
const noexcept
{
  return lhs.size() != rhs.size() or lhs.md5() != rhs.md5();
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
