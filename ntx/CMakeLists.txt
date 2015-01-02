set( NTX_SOURCES
     automatic_session.cc
     conflict.cc
     distant_root.cc
     local_root.cc
     main.cc
     pull.cc
     push.cc
     session.cc)

add_executable(ntx ${NETEXPLORER_SOURCES})

target_link_libraries (ntx ${CPPNETLIB_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
