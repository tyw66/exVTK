##----------------------------------------------------------------------------------------------------------
## 学习VTK
## Created in 2019/05/21
##----------------------------------------------------------------------------------------------------------
#工程名
project(exVTK)

#版本
cmake_minimum_required(VERSION 2.8)

#引入VTK
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

#设置VTK变量
#注："VTK_DIR"是文件"VTKConfig.cmake"所在的文件夹路径，
#      "VTK_USE_FILE"是文件"UseVTK.cmake"所在的全路径，
#       对于v5.10来说，都在VTK安装目录的lib下，
#       在qtcreator中直接项目->builde中设置VTK_DIR变量
#SET(VTK_DIR "/home/tyw/tyw66/intallVTK/VTK5.10.1/lib/vtk-5.10")
#SET(VTK_USE_FILE "/home/tyw/tyw66/intallVTK/VTK5.10.1/lib/vtk-5.10/UseVTK.cmake")

#添加项目
ADD_EXECUTABLE(HelloVTK helloVTK.cpp)
TARGET_LINK_LIBRARIES(HelloVTK ${VTK_LIBRARIES})


#引入子工程
ADD_SUBDIRECTORY(./2d)
ADD_SUBDIRECTORY(./3d)
ADD_SUBDIRECTORY(./advance)
ADD_SUBDIRECTORY(./objview)

