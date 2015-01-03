#pragma once

#include <string>

#include <boost/filesystem.hpp>

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

struct configuration final
{
private:

  std::string base_url_;
  boost::filesystem::path local_root_;
  std::string user_;
  std::string password_;

public:

  configuration( const std::string& base_url, const boost::filesystem::path& local_root
               , const std::string& user, const std::string& password)
    : base_url_{base_url}, local_root_{local_root}, user_{user}, password_{password}
  {}

  auto account_url() const {return base_url_ + "/account";}
  auto auth_url()    const {return base_url_ + "/auth";}
  auto folder_url()  const {return base_url_ + "/folder";}
  auto file_url()    const {return base_url_ + "/file";}

  const auto& base_url()   const noexcept {return base_url_;}
  const auto& local_root() const noexcept {return local_root_;}
  const auto& user()       const noexcept {return user_;}
  const auto& password()   const noexcept {return password_;}
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx

