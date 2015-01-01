#pragma once

#include <array>
#include <memory>  // shared_ptr
#include <string>
#include <utility> // forward

#include <boost/container/flat_set.hpp>
#include <boost/optional.hpp>

namespace ntx {

/// @todo Should have two distinct types for local and distant filesystems (for instance, local
/// folders don't have an id, it should not appear in their interface).

/*------------------------------------------------------------------------------------------------*/

// Forward declarations for recursive data structures.
class file;
class folder;

/*------------------------------------------------------------------------------------------------*/

using id_type  = unsigned long;
using md5_digest_type = std::string;

/*------------------------------------------------------------------------------------------------*/

namespace detail {

/// @internal
/// @brief The real file in a virtual system.
class file_impl final
{
private:

  std::string name_;
  boost::optional<id_type> id_; // A local file doesn't have an id.
  std::size_t size_;
  md5_digest_type md5_;

public:

  file_impl(const std::string& name, id_type id, std::size_t size, const md5_digest_type& md5)
    : name_{name}, id_{id}, size_{size}, md5_(md5)
  {}

  file_impl(const std::string& name, std::size_t size, const md5_digest_type& md5)
    : name_{name}, id_{}, size_{size}, md5_(md5)
  {}

  const auto& name() const noexcept {return name_;}
  const auto& id()      const noexcept {return id_;}
        auto  size() const noexcept {return size_;}
  /// @todo Lazy md5 computation for local files.
  const auto&  md5() const noexcept {return md5_;}
};

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief The real folder in a virtual system.
class folder_impl final
{
private:

  std::string name_;
  boost::optional<id_type> id_; // A local folder doesn't have an id.
  boost::container::flat_set<file> files_;
  boost::container::flat_set<folder> folders_;

public:

  folder_impl(const std::string& name, id_type id)
    : name_{name}, id_{id}, files_{}, folders_{}
  {}

  folder_impl(const std::string& name)
    : name_{name}, id_{}, files_{}, folders_{}
  {}

  const auto& name()    const noexcept {return name_;}
  const auto& id()      const noexcept {return id_;}
  const auto& files()   const noexcept {return files_;}
  const auto& folders() const noexcept {return folders_;}

  /// @todo Check that F is always a file.
  template <typename F>
  void
  add_file(F&& f)
  {
    files_.emplace(std::forward<F>(f));
  }

  /// @todo Check that F is always a file.
  template <typename F, typename... Fs>
  void
  add_file(F&& f, Fs&&... fs)
  {
    files_.emplace(std::forward<F>(f));
    add_file(std::forward<Fs>(fs)...);
  }

  /// @todo Check that F is always a folder.
  template <typename F>
  void
  add_folder(F&& f)
  {
    folders_.emplace(std::forward<F>(f));
  }

  /// @todo Check that F is always a folder.
  template <typename F, typename... Fs>
  void
  add_folder(F&& f, Fs&&... fs)
  {
    folders_.emplace(std::forward<F>(f));
    add_folder(std::forward<Fs>(fs)...);
  }
};

} // namespace detail

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
