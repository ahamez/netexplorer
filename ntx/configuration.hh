#pragma once

#include <string>

#include <boost/filesystem.hpp>

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Configure the ntx library.
class configuration final
{
private:

  std::string base_url_;
  boost::filesystem::path local_path_;
  boost::filesystem::path conflict_dir_;
  std::string user_;
  std::string password_;
  std::size_t max_tasks_;

public:

  /// @param base_url The NetExplorer URL.
  /// @param local_path The local folder to synchronize.
  /// @param conflict_dir Where to store conflicting files.
  configuration( const std::string& base_url, const boost::filesystem::path& local_path
               , const boost::filesystem::path& conflict_dir
               , const std::string& user, const std::string& password
               , std::size_t max_tasks)
    : base_url_{base_url}, local_path_{local_path}, conflict_dir_{conflict_dir}, user_{user}
    , password_{password}, max_tasks_{max_tasks}
  {}

  const std::string&             base_url()     const noexcept {return base_url_;}
  const boost::filesystem::path& local_path()   const noexcept {return local_path_;}
  const boost::filesystem::path& conflict_dir() const noexcept {return conflict_dir_;}
  const std::string&             user()         const noexcept {return user_;}
  const std::string&             password()     const noexcept {return password_;}
        std::size_t              max_tasks()    const noexcept {return max_tasks_;}

  std::string account_url() const {return base_url() + "/account";}
  std::string auth_url()    const {return base_url() + "/auth";}
  std::string folder_url()  const {return base_url() + "/folder";}
  std::string file_url()    const {return base_url() + "/file";}
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
