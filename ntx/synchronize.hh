#pragma once

#include <utility> // forward

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#include "ntx/fs.hh"

namespace ntx {

/*------------------------------------------------------------------------------------------------*/

namespace fs = boost::filesystem;

/*------------------------------------------------------------------------------------------------*/

/// @brief Synchronize a distant and a local filesystem.
/// @arg pull Function object called when a file is missing in the local filesystem. 
/// @arg push Function object called when a file is missing in the distant filesystem.
/// @arg push Function object called when a file exists on both filesystem with different contents.
template <typename Pull, typename Push, typename Conflict>
void
synchronize( const folder& distant_folder, const folder& local_folder, const fs::path& local_path
           , Pull&& pull, Push&& push, Conflict&& conflict)
{
  // Files.
  {
    // Nested files are sorted by name, we can thus iterate on both sides comparing names
    // to detect different and similar files.
    auto distant_cit = begin(distant_folder.files());
    auto local_cit   = begin(local_folder.files());

    while (distant_cit != end(distant_folder.files()) and local_cit != end(local_folder.files()))
    {
      const auto& distant = *distant_cit;
      const auto& local   = *local_cit;

      if (distant.name() == local.name())
      {
        if (distant.size() != local.size() or distant.md5() != local.md5())
        {
          conflict(*distant_folder.id(), distant, local_path);
        }
        ++distant_cit;
        ++local_cit;
      }
      else if (distant.name() < local.name())
      {
        pull(*distant_folder.id(), distant, local_path);
        ++distant_cit;
      }
      else // (distant.name() > local.name())
      {
        push(*distant_folder.id(), local, local_path);
        ++local_cit;
      }
    }
    while (distant_cit != end(distant_folder.files()))
    {
      pull(*distant_folder.id(), *distant_cit, local_path);
      ++distant_cit;
    }
    while (local_cit != end(local_folder.files()))
    {
      push(*distant_folder.id(), *local_cit, local_path);
      ++local_cit;
    }
  }

  // Folders.
  {
    // Nested folders are sorted by name, we can thus iterate on both sides comparing names
    // to detect different and similar folders.
    auto distant_cit = begin(distant_folder.folders());
    auto local_cit   = begin(local_folder.folders());

    while (distant_cit != end(distant_folder.folders()) and local_cit != end(local_folder.folders()))
    {
      const auto& distant = *distant_cit;
      const auto& local   = *local_cit;
      if (distant.name() == local.name())
      {
        synchronize( distant, local, local_path / fs::path{local.name()}
                   , std::forward<Pull>(pull), std::forward<Push>(push)
                   , std::forward<Conflict>(conflict));
        ++distant_cit;
        ++local_cit;
      }
      else if (distant.name() < local.name())
      {
        pull(*distant_folder.id(), distant, local_path);
        ++distant_cit;
      }
      else // (distant.name() > local.name())
      {
        push(*distant_folder.id(), local, local_path);
        ++local_cit;
      }
    }
    while (distant_cit != end(distant_folder.folders()))
    {
      pull(*distant_folder.id(), *distant_cit, local_path);
      ++distant_cit;
    }
    while (local_cit != end(local_folder.folders()))
    {
      push(*distant_folder.id(), *local_cit, local_path);
      ++local_cit;
    }
  }
}

/*------------------------------------------------------------------------------------------------*/

} // namespace ntx
