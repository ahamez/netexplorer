set(NETEXPLORER_SOURCES automatic_session.cc
                        conflict.cc
                        distant_root.cc
                        local_root.cc
                        main.cc
                        pull.cc
                        push.cc
                        session.cc)

add_executable(netexplorer ${NETEXPLORER_SOURCES})

target_link_libraries (netexplorer ${CPPNETLIB_LIBRARIES} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
