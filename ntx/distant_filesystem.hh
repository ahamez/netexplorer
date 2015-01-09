#pragma once

#include <memory>  // unique_ptr
#include <string>

#include "ntx/types.hh"
#include "ntx/detail/distant_fs_impl.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a distant file.
class distant_file final
{
public:

  /// @brief Constructor.
  /// @param id Unique identifier on the NetExplorer platform.
  /// @param name File name.
  /// @param size File size (bytes).
  /// @param md5 MD5 checksum digest
  distant_file(id_type id, const std::string& name, std::size_t size, const md5_digest_type& md5);

  /// @brief Constructor.
  /// @param id Unique identifier on the NetExplorer platform.
  /// @param name File name.
  /// @param size File size (bytes).
  /// @param md5 MD5 checksum digest
  distant_file(id_type id, std::string&& name, std::size_t size, md5_digest_type&& md5);

  /// @brief Copy
  distant_file(const distant_file&);

  /// @brief Copy
  distant_file& operator=(const distant_file& rhs);

  /// @brief Move.
  distant_file(distant_file&&) = default;

  /// @brief Move.
  distant_file& operator=(distant_file&&) = default;

  const std::string&     name() const noexcept;
        id_type          id()   const noexcept;
        std::size_t      size() const noexcept;
  const md5_digest_type& md5()  const noexcept;

private:

  std::unique_ptr<detail::distant_file_impl> ptr_;
};

/*------------------------------------------------------------------------------------------------*/

/// @brief Compare two distant_file using their names.
/// @related distanf_file
bool operator<(const distant_file&, const distant_file&) noexcept;

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a distant folder.
class distant_folder final
{
public:

  /// @brief A set of files.
  using files_set = detail::distant_folder_impl::files_set;

  /// @brief A set of folders.
  using folders_set = detail::distant_folder_impl::folders_set;

  distant_folder(id_type id, const std::string& name);
  distant_folder(id_type id, std::string&& name);

  const std::string& name() const noexcept;
        id_type      id()   const noexcept;

  /// @brief Deep copy.
  distant_folder(const distant_folder& rhs);

  /// @brief Deep copy.
  distant_folder& operator=(const distant_folder& rhs);

  /// @brief Move.
  distant_folder(distant_folder&&) = default;

  /// @brief Move.
  distant_folder& operator=(distant_folder&&) = default;

  /// @brief Return the iterable set of contained files.
  const files_set& files() const noexcept;

  /// @brief Return the iterable set of contained folders.
  const folders_set& folders() const noexcept;

  /// @brief Add a file to this folder.
  ///
  /// Unicity of added file is ensured (using name).
  void add(const distant_file&);

  /// @brief Add a temporary file to this folder.
  ///
  /// Unicity of added file is ensured (using name).
  void add(distant_file&&);

  /// @brief Add a folder to this folder.
  ///
  /// Unicity of added folder is ensured (using name).
  void add(const distant_folder&);

  /// @brief Add a temporary folder to this folder.
  ///
  /// Unicity of added folder is ensured (using name).
  void add(distant_folder&&);

private:

  std::unique_ptr<detail::distant_folder_impl> ptr_;
};

/*------------------------------------------------------------------------------------------------*/

/// @brief Compare two distant_folder using their names.
/// @related distant_folder
bool operator<(const distant_folder&, const distant_folder&) noexcept;

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
