set(
  NTX_SOURCES
  main.cc
  automatic_session.cc
  distant_filesystem.cc
  local_filesystem.cc
  session.cc
  synchronize.cc
  detail/async.cc
  detail/conflict.cc
  detail/handle_conflict.cc
  detail/pull.cc
  detail/push.cc
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
