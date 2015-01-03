#pragma once

#include <memory>  // shared_ptr
#include <string>
#include <utility> // forward

#include "ntx/types.hh"
#include "ntx/detail/distant_fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a distant file.
class distant_file final
{
private:

  std::shared_ptr<detail::distant_file_impl> ptr_;

public:

  distant_file(id_type id, const std::string& name, std::size_t size, const md5_digest_type& md5)
    : ptr_{std::make_shared<detail::distant_file_impl>(id, name, size, md5)}
  {}

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

  std::shared_ptr<detail::distant_folder_impl> ptr_;

public:

  distant_folder(id_type id, const std::string& name)
    : ptr_{std::make_shared<detail::distant_folder_impl>(id, name)}
  {}

  const std::string& name() const noexcept {return ptr_->name();}
        id_type      id()   const noexcept {return ptr_->id();}

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
  operator<(const distant_folder& lhs, const distant_folder& rhs)
  noexcept
  {
    return lhs.name() < rhs.name();
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
