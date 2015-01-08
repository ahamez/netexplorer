#pragma once

#include <utility> // forward

#include <boost/filesystem/fstream.hpp>

#include "ntx/distant_filesystem.hh"
#include "ntx/local_filesystem.hh"

namespace ntx {
namespace detail {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;

/*------------------------------------------------------------------------------------------------*/

template <typename Pull, typename Push, typename Conflict, typename HandleConflict>
void
synchronize( const distant_folder& distant_f, const local_folder& local_f
           , const fs::path& local_path, Pull&& pull, Push&& push, Conflict&& conflict
           , HandleConflict&& handle_conflict)
{
  // Files.
  {
    // Nested files are sorted by name, we can thus iterate on both sides comparing names
    // to detect different and similar files.
    auto distant_cit = begin(distant_f.files());
    auto local_cit   = begin(local_f.files());

    while (distant_cit != end(distant_f.files()) and local_cit != end(local_f.files()))
    {
      const auto& distant = *distant_cit;
      const auto& local   = *local_cit;

      if (distant.name() == local.name())
      {
        if (conflict(distant, local))
        {
          handle_conflict(distant_f.id(), distant, local, local_path);
        }
        ++distant_cit;
        ++local_cit;
      }
      else if (distant.name() < local.name())
      {
        pull(distant_f.id(), distant, local_path);
        ++distant_cit;
      }
      else // (distant.name() > local.name())
      {
        push(distant_f.id(), local, local_path);
        ++local_cit;
      }
    }
    for (; distant_cit != end(distant_f.files()); ++distant_cit)
    {
      pull(distant_f.id(), *distant_cit, local_path);
    }
    for (; local_cit != end(local_f.files()); ++local_cit)
    {
      push(distant_f.id(), *local_cit, local_path);
    }
  }

  // Folders.
  {
    // Nested folders are sorted by name, we can thus iterate on both sides comparing names
    // to detect different and similar folders.
    auto distant_cit = begin(distant_f.folders());
    auto local_cit   = begin(local_f.folders());

    while (distant_cit != end(distant_f.folders()) and local_cit != end(local_f.folders()))
    {
      const auto& distant = *distant_cit;
      const auto& local   = *local_cit;

      if (distant.name() == local.name())
      {
        synchronize( distant, local, local_path / fs::path{local.name()}
                   , std::forward<Pull>(pull), std::forward<Push>(push)
                   , std::forward<Conflict>(conflict)
                   , std::forward<HandleConflict>(handle_conflict));
        ++distant_cit;
        ++local_cit;
      }
      else if (distant.name() < local.name())
      {
        pull(distant_f.id(), distant, local_path);
        ++distant_cit;
      }
      else // (distant.name() > local.name())
      {
        push(distant_f.id(), local, local_path);
        ++local_cit;
      }
    }
    for (; distant_cit != end(distant_f.folders()); ++distant_cit)
    {
      pull(distant_f.id(), *distant_cit, local_path);
    }
    for (; local_cit != end(local_f.folders()); ++local_cit)
    {
      push(distant_f.id(), *local_cit, local_path);
    }
  }
}

/*------------------------------------------------------------------------------------------------*/

} // namespace detail
} // namespace ntx
