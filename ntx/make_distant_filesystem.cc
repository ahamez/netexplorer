#include "ntx/make_distant_filesystem.hh"
#include "ntx/detail/mk_distant_filesystem.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

distant_folder
make_distant_filesystem(const configuration& conf, const session& s, id_type id)
{
  return detail::mk_distant_folder(conf, s, id);
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
