#pragma once

#include <cstring>
#include <iostream>

#include <memory>  // shared_ptr
#include <string>
#include <utility> // forward

#include <boost/locale.hpp>

#include "ntx/types.hh"
#include "ntx/detail/local_fs_impl.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a local file.
class local_file final
{
private:

  std::shared_ptr<detail::local_file_impl> ptr_;

public:

  local_file(const std::string& name, std::size_t size, const md5_digest_type& md5)
    : ptr_{std::make_shared<detail::local_file_impl>(name, size, md5)}
  {}

  const std::string&     name() const noexcept {return ptr_->name();}
        std::size_t      size() const noexcept {return ptr_->size();}
  const md5_digest_type& md5()  const noexcept {return ptr_->md5();}

  friend
  bool
  operator<(const local_file& lhs, const local_file& rhs)
  noexcept
  {
    return lhs.name() < rhs.name();
  }
};

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a local folder.
class local_folder final
{
private:

  std::shared_ptr<detail::local_folder_impl> ptr_;

public:

  local_folder(const std::string& name)
    : ptr_{std::make_shared<detail::local_folder_impl>(name)}
  {}

  const std::string& name() const noexcept {return ptr_->name();}

  /// @brief Return an iterable set of contained files.
  auto files() const noexcept -> decltype(ptr_->files()) {return ptr_->files();}

  /// @brief Return an iterable set of contained folders.
  auto folders() const noexcept -> decltype(ptr_->folders()) {return ptr_->folders();}

  /// @brief Add one or more files to this folder.
  ///
  /// Unicity of added files is ensured (using name).
  template <typename... Fs>
  void
  add_file(Fs&&... fs)
  {
    ptr_->add_file(std::forward<Fs>(fs)...);
  }

  /// @brief Add one or more folders to this folder.
  ///
  /// Unicity of added folders is ensured (using name).
  template <typename... Fs>
  void
  add_folder(Fs&&... fs)
  {
    ptr_->add_folder(std::forward<Fs>(fs)...);
  }

  friend
  bool
  operator<(const local_folder& lhs, const local_folder& rhs)
  noexcept
  {
    return lhs.name() < rhs.name();
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
