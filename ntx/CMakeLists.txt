set(
  NTX_SOURCES
  automatic_session.cc
  make_distant_filesystem.cc
  make_local_filesystem.cc
  session.cc
  sub_distant_folder.cc
  synchronize.cc
  detail/async.cc
  detail/conflict.cc
  detail/handle_conflict.cc
  detail/md5.cc
  detail/pull.cc
  detail/push.cc
  detail/mk_local_filesystem.cc
  detail/mk_distant_filesystem.cc
  detail/normalize_utf8.cc
  ${PROJECT_SOURCE_DIR}/ext/unilib/utf8.cpp
  ${PROJECT_SOURCE_DIR}/ext/unilib/uninorms.cpp
)

add_library(ntx STATIC ${NTX_SOURCES})
add_dependencies(ntx cpp-netlib)
