#include "ntx/make_local_filesystem.hh"
#include "ntx/detail/mk_local_filesystem.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

local_folder
make_local_filesystem(const configuration& conf)
{
  return detail::mk_local_folder(conf.local_path());
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
