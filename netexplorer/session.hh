#pragma once

#include <string>
#include <unordered_set>

#include "configuration.hh"
#include "credentials.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// Represent a session when connected to the NetExplorer platform. Only one session for one login
/// is permitted at a time.
class session final
{
private:

  std::string token_;

  /// @brief Only connect(const configuration&, const credentials&) can create a session.
  session(std::string&& token)
    : token_(std::move(token))
  {}

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

session
connect(const configuration&, const credentials&);

/*------------------------------------------------------------------------------------------------*/

void
disconnect(const configuration&, const session&);

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
