SET(projectName model)
project(${projectName})

ADD_EXECUTABLE(basic basic.cpp)
TARGET_LINK_LIBRARIES(basic ${VTK_LIBRARIES})

ADD_EXECUTABLE(obj obj.cpp)
TARGET_LINK_LIBRARIES(obj ${VTK_LIBRARIES})
