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
  boost::filesystem::path conflict_dir_;
  std::string user_;
  std::string password_;
  std::size_t max_tasks_;

public:

  configuration( const std::string& base_url, const boost::filesystem::path& local_root
               , const boost::filesystem::path& conflict_dir
               , const std::string& user, const std::string& password
               , std::size_t max_tasks)
    : base_url_{base_url}, local_root_{local_root}, conflict_dir_{conflict_dir}, user_{user}
    , password_{password}, max_tasks_{max_tasks}
  {}

  std::string account_url() const {return base_url_ + "/account";}
  std::string auth_url()    const {return base_url_ + "/auth";}
  std::string folder_url()  const {return base_url_ + "/folder";}
  std::string file_url()    const {return base_url_ + "/file";}

  const std::string&             base_url()     const noexcept {return base_url_;}
  const boost::filesystem::path& local_root()   const noexcept {return local_root_;}
  const boost::filesystem::path& conflict_dir() const noexcept {return conflict_dir_;}
  const std::string&             user()         const noexcept {return user_;}
  const std::string&             password()     const noexcept {return password_;}
        std::size_t              max_tasks()    const noexcept {return max_tasks_;}
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
