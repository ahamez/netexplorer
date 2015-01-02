#pragma once

#include <string>

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief The informations needed to log on the NetExplorer platform.
class credentials final
{
private:

  std::string login_;
  std::string password_;

public:

  credentials(const std::string& login, const std::string& password)
    : login_{login}, password_{password}
  {}

  ~credentials()
  {
    // scramble memory
    std::fill(begin(login_), end(login_), 'x');
    std::fill(begin(password_), end(password_), 'x');
  }

  const auto& login()    const noexcept {return login_;}
  const auto& password() const noexcept {return password_;}
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
