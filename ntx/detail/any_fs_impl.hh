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

  template <typename String, typename MD5>
  any_file_impl(String&& name, std::size_t size, MD5&& md5);

  inline const std::string& name()    const noexcept;
  inline       std::size_t  size()    const noexcept;
  inline const md5_digest_type& md5() const noexcept;
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

  template <typename String>
  any_folder_impl(String&& name);

  inline const std::string&   name()    const noexcept;
  inline const auto&          files()   const noexcept;
  inline const auto&          folders() const noexcept;

  template <typename F>
  void
  add_file(F&& f);

  template <typename F, typename... Fs>
  void
  add_file(F&& f, Fs&&... fs);

  template <typename F>
  void
  add_folder(F&& f);

  template <typename F, typename... Fs>
  void
  add_folder(F&& f, Fs&&... fs);
};

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx

#include "ntx/detail/any_fs_impl.tcc"
