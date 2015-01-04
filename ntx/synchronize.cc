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
  // Pull, push, etc. share the same task manager.
  auto&& async = detail::async{conf.max_tasks()};
  detail::synchronize( distant, local, conf.local_path()
                     , detail::pull{conf, s, async}, detail::push{conf, s, async}
                     , detail::conflict{}, detail::handle_conflict{conf, s, async});
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
