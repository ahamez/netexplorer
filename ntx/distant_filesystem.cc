#include "ntx/distant_filesystem.hh"
#include "ntx/detail/mk_distant_filesystem.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

folder
get_distant_filesystem(const configuration& conf, const session& s, id_type root)
{
  return detail::mk_distant_folder(conf, s, root);
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
