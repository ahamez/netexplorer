set(
  NTX_SOURCES
  automatic_session.cc
  make_distant_filesystem.cc
  make_local_filesystem.cc
  session.cc
  synchronize.cc
  detail/async.cc
  detail/conflict.cc
  detail/handle_conflict.cc
  detail/md5.cc
  detail/pull.cc
  detail/push.cc
  detail/mk_local_filesystem.cc
  detail/mk_distant_filesystem.cc
)

add_library(ntx STATIC ${NTX_SOURCES})
add_dependencies(ntx cpp-netlib)
