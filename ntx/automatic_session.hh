#pragma once

#include "ntx/configuration.hh"
#include "ntx/session.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Automatically connect and close a session.
class automatic_session final
{
private:

  const configuration& conf_;
  session session_;

public:

  /// @brief Connect a session.
  automatic_session(const configuration&, const credentials&);

  /// @brief Disconnect a session.
  ~automatic_session();

  /// @brief Usable as a session.
  operator const session& () const noexcept;

  // Cannot copy a automatic_session.
  automatic_session(const automatic_session&)                = delete;
  automatic_session& operator=(const automatic_session&)     = delete;

  // Can move a automatic_session.
  automatic_session(automatic_session&&)            noexcept = default;
  automatic_session& operator=(automatic_session&&) noexcept = default;
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
