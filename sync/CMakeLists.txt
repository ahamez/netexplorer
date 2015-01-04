set(
  SYNC_SOURCES
  main.cc
  configure.cc
)

add_executable(sync ${SYNC_SOURCES})
add_dependencies(sync ntx)
if(UNIX AND NOT APPLE)
  target_link_libraries(sync rt)
endif()

target_link_libraries(
  sync
  ntx
  cppnetlib-client-connections
  cppnetlib-server-parsers
  cppnetlib-uri
  ${Boost_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${OPENSSL_LIBRARIES}
)
