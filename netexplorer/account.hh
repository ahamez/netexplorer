#pragma once

#include <boost/container/flat_set.hpp>

#include "configuration.hh"
#include "session.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

class account
{
private:

  boost::container::flat_set<unsigned long> roots_;

public:

  account(const configuration&, const session&);

  const auto& roots() const noexcept {return roots_;}
};

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
