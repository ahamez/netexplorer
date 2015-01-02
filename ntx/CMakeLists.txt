set(
  NTX_SOURCES
  automatic_session.cc
  conflict.cc
  distant_filesystem.cc
  handle_conflict.cc
  local_filesystem.cc
  main.cc
  pull.cc
  push.cc
  session.cc
  detail/mk_local_filesystem.cc
  detail/mk_distant_filesystem.cc
)

add_executable(ntx ${NTX_SOURCES})
add_dependencies(ntx cpp-netlib)

target_link_libraries(
  ntx
  cppnetlib-client-connections
  cppnetlib-server-parsers
  cppnetlib-uri
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${OPENSSL_LIBRARIES}
)
