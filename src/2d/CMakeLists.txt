project(2d)

ADD_EXECUTABLE(ImageView imgview.cpp)
TARGET_LINK_LIBRARIES(ImageView ${VTK_LIBRARIES})

ADD_EXECUTABLE(ImageGrad imggrad.cpp)
TARGET_LINK_LIBRARIES(ImageGrad ${VTK_LIBRARIES})

ADD_EXECUTABLE(ImageFun imgfun.cpp)
TARGET_LINK_LIBRARIES(ImageFun ${VTK_LIBRARIES})


