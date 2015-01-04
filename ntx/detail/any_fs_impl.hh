#pragma once

#include <string>
#include <utility> // forward

#include <boost/container/flat_set.hpp>

#include "ntx/types.hh"
#include "ntx/detail/normalize_utf8.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

/// @internal
class any_file_impl
{
private:

  std::string name_;
  std::size_t size_;
  md5_digest_type md5_;

public:

  any_file_impl(const std::string& name, std::size_t size, const md5_digest_type& md5)
    : name_{normalize_utf8(name)}, size_{size}, md5_(md5)
  {}

  const auto& name() const noexcept {return name_;}
        auto  size() const noexcept {return size_;}
  const auto& md5()  const noexcept {return md5_;}
};

/*------------------------------------------------------------------------------------------------*/

/// @internal
template <typename Folder, typename File>
class any_folder_impl
{
private:

  std::string name_;
  boost::container::flat_set<File> files_;
  boost::container::flat_set<Folder> folders_;

public:

  any_folder_impl(const std::string& name)
    : name_{normalize_utf8(name)}, files_{}, folders_{}
  {}

  const auto& name()    const noexcept {return name_;}
  const auto& files()   const noexcept {return files_;}
  const auto& folders() const noexcept {return folders_;}

  template <typename F>
  void
  add_file(F&& f)
  {
    files_.emplace(std::forward<F>(f));
  }

  template <typename F, typename... Fs>
  void
  add_file(F&& f, Fs&&... fs)
  {
    files_.emplace(std::forward<F>(f));
    add_file(std::forward<Fs>(fs)...);
  }

  template <typename F>
  void
  add_folder(F&& f)
  {
    folders_.emplace(std::forward<F>(f));
  }

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
