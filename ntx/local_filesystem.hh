#pragma once

#include <cstring>
#include <iostream>

#include <memory>  // unique_ptr
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

  std::unique_ptr<detail::local_file_impl> ptr_;

public:


  template <typename String, typename MD5>
  local_file(String&& name, std::size_t size, MD5&& md5)
    : ptr_{std::make_unique<detail::local_file_impl>( std::forward<String>(name), size
                                                    , std::forward<MD5>(md5))}
  {}

  /// @brief Copy
  local_file(const local_file& rhs)
    : ptr_{std::make_unique<detail::local_file_impl>(rhs.name(), rhs.size(), rhs.md5())}
  {}

  /// @brief Copy
  local_file&
  operator=(const local_file& rhs)
  {
    if (&rhs != this)
    {
      ptr_ = std::make_unique<detail::local_file_impl>(rhs.name(), rhs.size(), rhs.md5());
    }
    return *this;
  }

  /// @brief Move.
  local_file(local_file&&) = default;

  /// @brief Move.
  local_file& operator=(local_file&&) = default;

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

  std::unique_ptr<detail::local_folder_impl> ptr_;

public:

  template <typename String>
  local_folder(String&& name)
    : ptr_{std::make_unique<detail::local_folder_impl>(std::forward<String>(name))}
  {}

  /// @brief Deep copy.
  local_folder(const local_folder& rhs)
    : ptr_{std::make_unique<detail::local_folder_impl>(rhs.name())}
  {
    for (const auto& f : rhs.files())
    {
      add_file(f);
    }
    for (const auto& f : rhs.folders())
    {
      add_folder(f);
    }
  }

  /// @brief Deep copy.
  local_folder&
  operator=(const local_folder& rhs)
  {
    if (&rhs != this)
    {
      ptr_ = std::make_unique<detail::local_folder_impl>(rhs.name());
      for (const auto& f : rhs.files())
      {
        add_file(f);
      }
      for (const auto& f : rhs.folders())
      {
        add_folder(f);
      }
    }
    return *this;
  }

  /// @brief Move.
  local_folder(local_folder&&) = default;

  /// @brief Move.
  local_folder& operator=(local_folder&&) = default;


  const std::string& name() const noexcept {return ptr_->name();}

  /// @brief Return the iterable set of contained files.
  auto files() const noexcept -> decltype(ptr_->files()) {return ptr_->files();}

  /// @brief Return the iterable set of contained folders.
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
