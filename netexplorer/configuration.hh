#pragma once

#include <functional>  // hash
#include <string>
#include <type_traits> // decay

#include <boost/filesystem.hpp>

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

class configuration
{
private:

  std::string base_url_;
  boost::filesystem::path local_root_;

public:

  configuration(const std::string& base_url, const boost::filesystem::path& local_root)
    : base_url_{base_url}, local_root_{local_root}
  {}

  std::string account_url() const {return base_url_ + "/account";}
  std::string auth_url()    const {return base_url_ + "/auth";}
  std::string folder_url()  const {return base_url_ + "/folder";}

  const auto& base_url()   const noexcept {return base_url_;}
  const auto& local_root() const noexcept {return local_root_;}

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

namespace std {

/*------------------------------------------------------------------------------------------------*/

template <>
struct hash<ntx::configuration>
{
  std::size_t
  operator()(const ntx::configuration& c)
  const noexcept
  {
    return std::hash<std::decay_t<decltype(c.base_url())>>{}(c.base_url());
  }
};

/*------------------------------------------------------------------------------------------------*/

} // namespace std
