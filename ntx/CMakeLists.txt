set( NTX_SOURCES
     automatic_session.cc
     conflict.cc
     distant_filesystem.cc
     local_filesystem.cc
     main.cc
     pull.cc
     push.cc
     session.cc
     detail/mk_local_filesystem.cc
     detail/mk_distant_filesystem.cc
     )

add_executable(ntx ${NTX_SOURCES})

target_link_libraries (ntx ${CPPNETLIB_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
