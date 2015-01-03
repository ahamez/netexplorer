#include "ntx/session.hh"
#include "ntx/configuration.hh"
#include "ntx/detail/conflict.hh"
#include "ntx/detail/handle_conflict.hh"
#include "ntx/detail/pull.hh"
#include "ntx/detail/push.hh"
#include "ntx/detail/synchronize.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

void
synchronize( const configuration& conf, const session& s, const distant_folder& distant
           , const local_folder& local)
{
  detail::synchronize( distant, local, conf.local_root()
                     , detail::pull{conf, s}, detail::push{conf, s}
                     , detail::conflict{}, detail::handle_conflict{conf, s});
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
