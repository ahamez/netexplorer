#pragma once

#include <memory>  // unique_ptr
#include <string>
#include <utility> // forward

#include "ntx/types.hh"
#include "ntx/detail/distant_fs_impl.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a distant file.
class distant_file final
{
private:

  std::unique_ptr<detail::distant_file_impl> ptr_;

public:

  template <typename String, typename MD5>
  distant_file(id_type id, String&& name, std::size_t size, MD5&& md5)
    : ptr_{std::make_unique<detail::distant_file_impl>( id, std::forward<String>(name), size
                                                      , std::forward<MD5>(md5))}
  {}

  /// @brief Copy
  distant_file(const distant_file& rhs)
    : ptr_{std::make_unique<detail::distant_file_impl>(rhs.id(), rhs.name(), rhs.size(), rhs.md5())}
  {}

  /// @brief Copy
  distant_file&
  operator=(const distant_file& rhs)
  {
    if (&rhs != this)
    {
      ptr_ = std::make_unique<detail::distant_file_impl>( rhs.id(), rhs.name(), rhs.size()
                                                        , rhs.md5());
    }
    return *this;
  }

  /// @brief Move.
  distant_file(distant_file&&) = default;

  /// @brief Move.
  distant_file& operator=(distant_file&&) = default;

  const std::string&     name() const noexcept {return ptr_->name();}
        id_type          id()   const noexcept {return ptr_->id();}
        std::size_t      size() const noexcept {return ptr_->size();}
  const md5_digest_type& md5()  const noexcept {return ptr_->md5();}

  friend
  bool
  operator<(const distant_file& lhs, const distant_file& rhs)
  noexcept
  {
    return lhs.name() < rhs.name();
  }
};

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a distant folder.
class distant_folder final
{
private:

  std::unique_ptr<detail::distant_folder_impl> ptr_;

public:

  template <typename String>
  distant_folder(id_type id, String&& name)
    : ptr_{std::make_unique<detail::distant_folder_impl>(id, std::forward<String>(name))}
  {}

  const std::string& name() const noexcept {return ptr_->name();}
        id_type      id()   const noexcept {return ptr_->id();}

  /// @brief Deep copy.
  distant_folder(const distant_folder& rhs)
    : ptr_{std::make_unique<detail::distant_folder_impl>(rhs.id(), rhs.name())}
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
  distant_folder&
  operator=(const distant_folder& rhs)
  {
    if (&rhs != this)
    {
      ptr_ = std::make_unique<detail::distant_folder_impl>(rhs.id(), rhs.name());
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
  distant_folder(distant_folder&&) = default;

  /// @brief Move.
  distant_folder& operator=(distant_folder&&) = default;

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
  operator<(const distant_folder& lhs, const distant_folder& rhs)
  noexcept
  {
    return lhs.name() < rhs.name();
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
