#pragma once

#include <string>

#include <boost/filesystem.hpp>

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

class configuration final
{
private:

  std::string base_url_;
  boost::filesystem::path local_root_;
  std::size_t max_ul_tasks_;
  std::size_t max_dl_tasks_;

public:

  configuration(const std::string& base_url, const boost::filesystem::path& local_root)
    : base_url_{base_url}, local_root_{local_root}, max_ul_tasks_{2}, max_dl_tasks_{4}
  {}

  auto account_url() const {return base_url_ + "/account";}
  auto auth_url()    const {return base_url_ + "/auth";}
  auto folder_url()  const {return base_url_ + "/folder";}
  auto file_url()    const {return base_url_ + "/file";}

  const auto& base_url()   const noexcept {return base_url_;}
  const auto& local_root() const noexcept {return local_root_;}

  auto max_ul_tasks() const noexcept {return max_ul_tasks_;}
  auto max_dl_tasks() const noexcept {return max_dl_tasks_;}

  friend
  bool
  operator==(const configuration& lhs, const configuration& rhs)
  noexcept
  {
    return lhs.base_url_ == rhs.base_url_;
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx

