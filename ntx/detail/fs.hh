#pragma once

#include <string>
#include <utility> // forward

#include <boost/container/flat_set.hpp>
#include <boost/optional.hpp>

#include "ntx/fs_fwd.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
/// @brief The real file in a virtual system.
class file_impl final
{
private:

  std::string name_;
  boost::optional<id_type> id_;
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
  const auto& id()   const noexcept {return id_;}
        auto  size() const noexcept {return size_;}
  const auto& md5()  const noexcept {return md5_;}
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

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
