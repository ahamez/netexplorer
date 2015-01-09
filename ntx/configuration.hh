#pragma once

#include <string>

#include <boost/filesystem.hpp>

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Configure the ntx library.
class configuration final
{
public:

  /// @param base_url The NetExplorer URL.
  /// @param local_path The local folder to synchronize.
  /// @param conflict_dir Where to store conflicting files.
  configuration( const std::string& base_url, const boost::filesystem::path& local_path
               , const boost::filesystem::path& conflict_dir
               , const std::string& user, const std::string& password
               , std::size_t max_tasks);


  const boost::filesystem::path& local_path()   const noexcept;
  const boost::filesystem::path& conflict_dir() const noexcept;
  const std::string&             user()         const noexcept;
  const std::string&             password()     const noexcept;
        std::size_t              max_tasks()    const noexcept;

  /// @brief Get the authentification API url.
  std::string auth_url() const;

  /// @brief Get the folder manipulation API url.
  std::string folder_url() const;

  /// @brief Get the file manipulation API url.
  std::string file_url() const;

private:

  std::string base_url_;
  boost::filesystem::path local_path_;
  boost::filesystem::path conflict_dir_;
  std::string user_;
  std::string password_;
  std::size_t max_tasks_;
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
