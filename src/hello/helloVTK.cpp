/** ************************
  * VTK简单程序 可用于检查VTK是否安装好
  * 2017.11.22 - tyw
 ***************************/
// for vtk 8.1 use :
//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkInteractionStyle)
//VTK_MODULE_INIT(vtkRenderingFreeType)
//VTK_MODULE_INIT(vtkRenderingOpenGL2)

#include <vtkRenderWindow.h>
#include <vtkSmartPointer.h>
int main(){
    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
    renWin->Render();

    std::cin.get();
    return 0;
}


