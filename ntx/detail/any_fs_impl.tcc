#pragma once

#include <utility> // forward

#include "ntx/types.hh"
#include "ntx/detail/normalize_utf8.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

template <typename String, typename MD5>
any_file_impl::any_file_impl(String&& name, std::size_t size, MD5&& md5)
    : name_{normalize_utf8(std::forward<String>(name))}, size_{size}, md5_(std::forward<MD5>(md5))
{}

/*------------------------------------------------------------------------------------------------*/

const std::string&
any_file_impl::name()
const noexcept
{
  return name_;
}

/*------------------------------------------------------------------------------------------------*/

std::size_t
any_file_impl::size()
const noexcept
{
  return size_;
}

/*------------------------------------------------------------------------------------------------*/

const md5_digest_type&
any_file_impl::md5()
const noexcept
{
  return md5_;
}

/*------------------------------------------------------------------------------------------------*/

template <typename Folder, typename File>
template <typename String>
any_folder_impl<Folder, File>::any_folder_impl(String&& name)
  : name_{normalize_utf8(std::forward<String>(name))}, files_{}, folders_{}
{}

/*------------------------------------------------------------------------------------------------*/

template <typename Folder, typename File>
const std::string&
any_folder_impl<Folder, File>::name()
const noexcept
{
  return name_;
}

/*------------------------------------------------------------------------------------------------*/

template <typename Folder, typename File>
const typename any_folder_impl<Folder, File>::files_set&
any_folder_impl<Folder, File>::files()
const noexcept
{
  return files_;
}

/*------------------------------------------------------------------------------------------------*/

template <typename Folder, typename File>
const typename any_folder_impl<Folder, File>::folders_set&
any_folder_impl<Folder, File>::folders()
const noexcept
{
  return folders_;
}

/*------------------------------------------------------------------------------------------------*/

template <typename Folder, typename File>
template <typename F>
void
any_folder_impl<Folder, File>::add_file(F&& f)
{
  files_.emplace(std::forward<F>(f));
}

/*------------------------------------------------------------------------------------------------*/

template <typename Folder, typename File>
template <typename F, typename... Fs>
void
any_folder_impl<Folder, File>::add_file(F&& f, Fs&&... fs)
{
  files_.emplace(std::forward<F>(f));
  add_file(std::forward<Fs>(fs)...);
}

/*------------------------------------------------------------------------------------------------*/

template <typename Folder, typename File>
template <typename F>
void
any_folder_impl<Folder, File>::add_folder(F&& f)
{
  folders_.emplace(std::forward<F>(f));
}

/*------------------------------------------------------------------------------------------------*/

template <typename Folder, typename File>
template <typename F, typename... Fs>
void
any_folder_impl<Folder, File>::add_folder(F&& f, Fs&&... fs)
{
  folders_.emplace(std::forward<F>(f));
  add_folder(std::forward<Fs>(fs)...);
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
