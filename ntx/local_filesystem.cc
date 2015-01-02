#include "ntx/local_filesystem.hh"
#include "ntx/detail/mk_local_filesystem.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

folder
get_local_filesystem(const configuration& conf)
{
  return detail::mk_local_folder(conf.local_root());
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
