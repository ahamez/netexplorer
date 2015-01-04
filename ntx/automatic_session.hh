#pragma once

#include "ntx/configuration.hh"
#include "ntx/session.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief RAII-style session.
///
/// Attempt to connect to the platform at construction, then disconnect at destruction.
class automatic_session final
{
private:

  const configuration& conf_;
  session session_;

public:

  /// @brief Connect a session.
  automatic_session(const configuration&);

  /// @brief Disconnect a session.
  ~automatic_session();

  /// @brief Conversion to a session.
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
