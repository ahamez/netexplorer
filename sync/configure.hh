#pragma once

#include <boost/optional.hpp>

#include "ntx/configuration.hh"

/*------------------------------------------------------------------------------------------------*/

boost::optional<ntx::configuration>
configure(int argc, const char** argv);

/*------------------------------------------------------------------------------------------------*/
