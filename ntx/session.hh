#pragma once

#include <string>
#include <unordered_set>

#include "ntx/configuration.hh"
#include "ntx/credentials.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Represent a session when connected to the NetExplorer platform.
///
/// Only connect(const configuration&, const credentials&) can create a session.
class session final
{
private:

  std::string token_;

  session(const std::string& token);
  session(std::string&& token) noexcept;

public:

  // Cannot copy a session.
  session(const session&)                = delete;
  session& operator=(const session&)     = delete;

  // Can move a session.
  session(session&&)            noexcept = default;
  session& operator=(session&&) noexcept = default;

  /// @internal
  const std::string& token() const noexcept {return token_;}

  /// @internal
  friend session connect(const configuration&, const credentials&);
};

/*------------------------------------------------------------------------------------------------*/

/// @
session
connect(const configuration&, const credentials&);

/*------------------------------------------------------------------------------------------------*/

void
disconnect(const configuration&, const session&);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
