SET(ex00 helloVTK)
project(${ex00})
add_executable(${ex00} "helloVTK.cpp")
target_link_libraries(${ex00} ${VTK_LIBRARIES})
