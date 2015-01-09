#pragma once

#include <cstring>
#include <iostream>

#include <memory>  // unique_ptr
#include <string>

#include "ntx/types.hh"
#include "ntx/detail/local_fs_impl.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a local file.
class local_file final
{
public:

  /// @brief Constructor.
  /// @param name File name.
  /// @param size File size (bytes).
  /// @param md5 MD5 checksum digest
  local_file(const std::string& name, std::size_t size, const md5_digest_type& md5);

  /// @brief Constructor.
  /// @param name File name.
  /// @param size File size (bytes).
  /// @param md5 MD5 checksum digest
  local_file(std::string&& name, std::size_t size, md5_digest_type&& md5);

  /// @brief Copy constructor.
  local_file(const local_file&);

  /// @brief Copy operator.
  local_file&
  operator=(const local_file& rhs);

  /// @brief Move constructor.
  local_file(local_file&&) = default;

  /// @brief Move operator.
  local_file& operator=(local_file&&) = default;

  const std::string&     name() const noexcept;
        std::size_t      size() const noexcept;
  const md5_digest_type& md5()  const noexcept;

private:

  std::unique_ptr<detail::local_file_impl> ptr_;
};

/*------------------------------------------------------------------------------------------------*/

/// @brief Compare two local_file using their names.
/// @related local_file
bool operator<(const local_file&, const local_file&) noexcept;

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a local folder.
class local_folder final
{
public:

  /// @brief A set of files.
  using files_set = detail::local_folder_impl::files_set;

  /// @brief A set of folders.
  using folders_set = detail::local_folder_impl::folders_set;

  /// @brief Construct a folder with a given name.
  local_folder(const std::string& name);

  /// @brief Construct a folder with a given name.
  local_folder(std::string&& name);

  /// @brief Deep copy.
  local_folder(const local_folder& rhs);

  /// @brief Deep copy.
  local_folder&
  operator=(const local_folder& rhs);

  /// @brief Move.
  local_folder(local_folder&&) = default;

  /// @brief Move.
  local_folder& operator=(local_folder&&) = default;

  /// @brief Get the basename of this folder.
  const std::string& name() const noexcept;

  /// @brief Return the iterable set of contained files.
  const files_set& files() const noexcept;

  /// @brief Return the iterable set of contained folders.
  const folders_set& folders() const noexcept;

  /// @brief Add a file to this folder.
  ///
  /// Unicity of added file is ensured (using name).
  void add(const local_file&);

  /// @brief Add a temporary file to this folder.
  ///
  /// Unicity of added file is ensured (using name).
  void add(local_file&&);

  /// @brief Add a folder to this folder.
  ///
  /// Unicity of added folder is ensured (using name).
  void add(const local_folder&);

  /// @brief Add a temporary folder to this folder.
  ///
  /// Unicity of added folder is ensured (using name).
  void add(local_folder&&);

private:

  std::unique_ptr<detail::local_folder_impl> ptr_;
};

/*------------------------------------------------------------------------------------------------*/

/// @brief Compare two local_folder using their names.
/// @related local_file
bool operator<(const local_folder&, const local_folder&) noexcept;

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
