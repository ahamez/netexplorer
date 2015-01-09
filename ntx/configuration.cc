#include <boost/filesystem.hpp>

#include "ntx/configuration.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

configuration::configuration( const std::string& base_url, const boost::filesystem::path& local_path
                            , const boost::filesystem::path& conflict_dir
                            , const std::string& user, const std::string& password
                            , std::size_t max_tasks)
    : base_url_{base_url}, local_path_{local_path}, conflict_dir_{conflict_dir}, user_{user}
    , password_{password}, max_tasks_{max_tasks}
  {}

/*------------------------------------------------------------------------------------------------*/

const boost::filesystem::path&
configuration::local_path()
const noexcept
{
  return local_path_;
}

/*------------------------------------------------------------------------------------------------*/

const boost::filesystem::path&
configuration::conflict_dir()
const noexcept
{
  return conflict_dir_;
}

/*------------------------------------------------------------------------------------------------*/

const std::string&
configuration::user()
const noexcept
{
  return user_;
}

/*------------------------------------------------------------------------------------------------*/

const std::string&
configuration::password()
const noexcept
{
  return password_;
}

/*------------------------------------------------------------------------------------------------*/

std::size_t
configuration::max_tasks()
const noexcept
{
  return max_tasks_;
}

/*------------------------------------------------------------------------------------------------*/

std::string
configuration::auth_url()
const
{
  return base_url_ + "/auth";
}

/*------------------------------------------------------------------------------------------------*/

std::string
configuration::folder_url()
const
{
  return base_url_ + "/folder";
}

/*------------------------------------------------------------------------------------------------*/

std::string
configuration::file_url()
const
{
  return base_url_ + "/file";
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
