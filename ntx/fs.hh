#pragma once

#include <memory>  // shared_ptr
#include <string>
#include <utility> // forward

#include <boost/container/flat_set.hpp>
#include <boost/optional.hpp>

#include "ntx/types.hh"
#include "ntx/detail/fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a file in a virtual filesystem.
class file final
{
private:

  std::shared_ptr<detail::file_impl> ptr_;

public:

  file(const std::string& name, id_type id, std::size_t size, const md5_digest_type& md5)
    : ptr_{std::make_shared<detail::file_impl>(name, id, size, md5)}
  {}

  file(const std::string& name, std::size_t size, const md5_digest_type& md5)
    : ptr_{std::make_shared<detail::file_impl>(name, size, md5)}
  {}

  const auto& name() const noexcept {return ptr_->name();}
  const auto& id()   const noexcept {return ptr_->id();}
        auto  size() const noexcept {return ptr_->size();}
  const auto& md5()  const noexcept {return ptr_->md5();}

  friend
  bool
  operator<(const file& lhs, const file& rhs)
  noexcept
  {
    return lhs.name() < rhs.name();
  }
};

/*------------------------------------------------------------------------------------------------*/

/// @brief Describe a folder in a virtual filesystem.
class folder final
{
private:

  std::shared_ptr<detail::folder_impl> ptr_;

public:

  folder(const std::string& name, id_type id)
    : ptr_{std::make_shared<detail::folder_impl>(name, id)}
  {}

  folder(const std::string& name)
    : ptr_{std::make_shared<detail::folder_impl>(name)}
  {}

  const auto& name()    const noexcept {return ptr_->name();}
  const auto& id()      const noexcept {return ptr_->id();}
  const auto& files()   const noexcept {return ptr_->files();}
  const auto& folders() const noexcept {return ptr_->folders();}

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
  operator<(const folder& lhs, const folder& rhs)
  noexcept
  {
    return lhs.name() < rhs.name();
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
