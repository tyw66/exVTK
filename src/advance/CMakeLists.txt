PROJECT(advance)

ADD_EXECUTABLE(callback callback.cpp)
TARGET_LINK_LIBRARIES(callback ${VTK_LIBRARIES})

ADD_EXECUTABLE(command command.cpp)
TARGET_LINK_LIBRARIES(command ${VTK_LIBRARIES})
