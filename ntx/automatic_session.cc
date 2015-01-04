#include "ntx/automatic_session.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

automatic_session::automatic_session(const configuration& conf)
  : conf_{conf}, session_{connect(conf)}
{}

/*------------------------------------------------------------------------------------------------*/

automatic_session::~automatic_session()
{
  try
  {
    disconnect(conf_, session_);
  }
  catch (...)
  {
    // Do nothing, we just failed to close the session. Furthermore, it avoids to have a
    // non-noexcept destructor.
  }
}

/*------------------------------------------------------------------------------------------------*/

automatic_session::operator const session& () const noexcept
{
  return session_;
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
