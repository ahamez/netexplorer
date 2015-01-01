#include "automatic_session.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

automatic_session::automatic_session(const configuration& conf, const credentials& creds)
  : conf_{conf}, session_{connect(conf, creds)}
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

/// @brief Usable as a session.
automatic_session::operator const session& () const noexcept
{
  return session_;
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
