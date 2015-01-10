#include "ntx/distant_filesystem.hh"
#include "ntx/detail/c++14.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

distant_file::distant_file( id_type id, const std::string& name, std::size_t size
                          , const md5_digest_type& md5)
  : ptr_{detail::make_unique<detail::distant_file_impl>(id, name, size, md5)}
{}

/*------------------------------------------------------------------------------------------------*/

distant_file::distant_file(id_type id, std::string&& name, std::size_t size, md5_digest_type&& md5)
  : ptr_{detail::make_unique<detail::distant_file_impl>(std::move(id), name, size, std::move(md5))}
{}

/*------------------------------------------------------------------------------------------------*/

distant_file::distant_file(const distant_file& rhs)
  : ptr_{detail::make_unique<detail::distant_file_impl>(rhs.id(), rhs.name(), rhs.size(), rhs.md5())}
{}

/*------------------------------------------------------------------------------------------------*/

distant_file&
distant_file::operator=(const distant_file& rhs)
{
  if (&rhs != this)
  {
    ptr_
      = detail::make_unique<detail::distant_file_impl>(rhs.id(), rhs.name(), rhs.size(), rhs.md5());
  }
  return *this;
}

/*------------------------------------------------------------------------------------------------*/

const std::string&
distant_file::name()
const noexcept
{
  return ptr_->name();
}

/*------------------------------------------------------------------------------------------------*/

id_type
distant_file::id()
const noexcept
{
  return ptr_->id();
}

/*------------------------------------------------------------------------------------------------*/

std::size_t
distant_file::size()
const noexcept
{
  return ptr_->size();
}

/*------------------------------------------------------------------------------------------------*/

const md5_digest_type&
distant_file::md5()
const noexcept
{
  return ptr_->md5();
}

/*------------------------------------------------------------------------------------------------*/

bool
operator<(const distant_file& lhs, const distant_file& rhs)
noexcept
{
  return lhs.name() < rhs.name();
}

/*------------------------------------------------------------------------------------------------*/

distant_folder::distant_folder(id_type id, const std::string& name)
  : ptr_{detail::make_unique<detail::distant_folder_impl>(id, name)}
{}

/*------------------------------------------------------------------------------------------------*/

distant_folder::distant_folder(id_type id, std::string&& name)
  : ptr_{detail::make_unique<detail::distant_folder_impl>(id, std::move(name))}
{}

/*------------------------------------------------------------------------------------------------*/

distant_folder::  distant_folder(const distant_folder& rhs)
  : ptr_{detail::make_unique<detail::distant_folder_impl>(rhs.id(), rhs.name())}
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

distant_folder&
distant_folder::operator=(const distant_folder& rhs)
{
  if (&rhs != this)
  {
    ptr_ = detail::make_unique<detail::distant_folder_impl>(rhs.id(), rhs.name());
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
distant_folder::name()
const noexcept
{
  return ptr_->name();
}

/*------------------------------------------------------------------------------------------------*/

id_type
distant_folder::id()
const noexcept
{
  return ptr_->id();
}

/*------------------------------------------------------------------------------------------------*/

const distant_folder::files_set&
distant_folder::files()
const noexcept
{
  return ptr_->files();
}

/*------------------------------------------------------------------------------------------------*/

const distant_folder::folders_set&
distant_folder::folders()
const noexcept
{
  return ptr_->folders();
}

/*------------------------------------------------------------------------------------------------*/

void
distant_folder::add(const distant_file& f)
{
  ptr_->add_file(f);
}

/*------------------------------------------------------------------------------------------------*/

void
distant_folder::add(distant_file&& f)
{
  ptr_->add_file(std::move(f));
}

/*------------------------------------------------------------------------------------------------*/

void
distant_folder::add(const distant_folder& f)
{
  ptr_->add_folder(f);
}

/*------------------------------------------------------------------------------------------------*/

void
distant_folder::add(distant_folder&& f)
{
  ptr_->add_folder(std::move(f));
}

/*------------------------------------------------------------------------------------------------*/

bool
operator<(const distant_folder& lhs, const distant_folder& rhs)
noexcept
{
  return lhs.name() < rhs.name();
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
