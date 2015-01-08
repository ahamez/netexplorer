#include <cstring>
#include <iostream>

#include <memory>  // unique_ptr
#include <string>
#include <utility> // forward

#include <boost/locale.hpp>

#include "ntx/local_filesystem.hh"
#include "ntx/types.hh"
#include "ntx/detail/local_fs_impl.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

local_file::local_file(const std::string& name, std::size_t size, const md5_digest_type& md5)
  : ptr_{std::make_unique<detail::local_file_impl>(name, size, md5)}
{}

/*------------------------------------------------------------------------------------------------*/

local_file::local_file(std::string&& name, std::size_t size, md5_digest_type&& md5)
  : ptr_{std::make_unique<detail::local_file_impl>(std::move(name), size, std::move(md5))}
{}

/*------------------------------------------------------------------------------------------------*/

local_file::local_file(const local_file& rhs)
  : ptr_{std::make_unique<detail::local_file_impl>(rhs.name(), rhs.size(), rhs.md5())}
{}

/*------------------------------------------------------------------------------------------------*/

local_file&
local_file::operator=(const local_file& rhs)
{
  if (&rhs != this)
  {
    ptr_ = std::make_unique<detail::local_file_impl>(rhs.name(), rhs.size(), rhs.md5());
  }
  return *this;
}

/*------------------------------------------------------------------------------------------------*/

const std::string&
local_file::name()
const noexcept
{
  return ptr_->name();
}

/*------------------------------------------------------------------------------------------------*/

std::size_t
local_file::size()
const noexcept
{
  return ptr_->size();
}

/*------------------------------------------------------------------------------------------------*/

const md5_digest_type&
local_file::md5()
const noexcept
{
  return ptr_->md5();
}

/*------------------------------------------------------------------------------------------------*/

bool
operator<(const local_file& lhs, const local_file& rhs)
noexcept
{
  return lhs.name() < rhs.name();
}

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

local_folder::local_folder(const std::string& name)
  : ptr_{std::make_unique<detail::local_folder_impl>(name)}
{}

/*------------------------------------------------------------------------------------------------*/

local_folder::local_folder(std::string&& name)
  : ptr_{std::make_unique<detail::local_folder_impl>(std::move(name))}
{}

/*------------------------------------------------------------------------------------------------*/

local_folder::local_folder(const local_folder& rhs)
  : ptr_{std::make_unique<detail::local_folder_impl>(rhs.name())}
{
  for (const auto& f : rhs.files())
  {
    add(f);
  }
  for (const auto& f : rhs.folders())
  {
    add(f);
  }
}

/*------------------------------------------------------------------------------------------------*/

local_folder&
local_folder::operator=(const local_folder& rhs)
{
  if (&rhs != this)
  {
    ptr_ = std::make_unique<detail::local_folder_impl>(rhs.name());
    for (const auto& f : rhs.files())
    {
      add(f);
    }
    for (const auto& f : rhs.folders())
    {
      add(f);
    }
  }
  return *this;
}

/*------------------------------------------------------------------------------------------------*/

const std::string&
local_folder::name()
const noexcept
{
  return ptr_->name();
}

/*------------------------------------------------------------------------------------------------*/

const local_folder::files_set&
local_folder::files()
const noexcept
{
  return ptr_->files();
}

/*------------------------------------------------------------------------------------------------*/

const local_folder::folders_set&
local_folder::folders()
const noexcept
{
  return ptr_->folders();
}

/*------------------------------------------------------------------------------------------------*/

void
local_folder::add(const local_file& f)
{
  ptr_->add_file(f);
}

/*------------------------------------------------------------------------------------------------*/

void
local_folder::add(local_file&& f)
{
  ptr_->add_file(std::move(f));
}

/*------------------------------------------------------------------------------------------------*/

void
local_folder::add(const local_folder& f)
{
  ptr_->add_folder(f);
}

/*------------------------------------------------------------------------------------------------*/

void
local_folder::add(local_folder&& f)
{
  ptr_->add_folder(std::move(f));
}

/*------------------------------------------------------------------------------------------------*/

bool
operator<(const local_folder& lhs, const local_folder& rhs)
noexcept
{
  return lhs.name() < rhs.name();
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
