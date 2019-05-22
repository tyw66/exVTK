####################################################
## 学习VTK
## Created in 2019/05/21
####################################################
#版本
cmake_minimum_required(VERSION 2.8)

#引入VTK
FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

#设置变量
#注："VTK_DIR"是文件"VTKConfig.cmake"所在的文件夹路径，
#      "VTK_USE_FILE"是文件"UseVTK.cmake"所在的全路径，
#       对于v5.10来说，都在VTK安装目录的lib下，
#       在qtcreator中直接项目->builde中设置VTK_DIR变量
#SET(VTK_DIR "/home/tyw/tyw66/intallVTK/VTK5.10.1/lib/vtk-5.10")
#SET(VTK_USE_FILE "/home/tyw/tyw66/intallVTK/VTK5.10.1/lib/vtk-5.10/UseVTK.cmake")

#引入子工程
ADD_SUBDIRECTORY(./hello)
ADD_SUBDIRECTORY(./callback)
ADD_SUBDIRECTORY(./command)
ADD_SUBDIRECTORY(./image)
ADD_SUBDIRECTORY(./model)
ADD_SUBDIRECTORY(./objview)
#ADD_SUBDIRECTORY(./line)
ADD_SUBDIRECTORY(./polydata)
