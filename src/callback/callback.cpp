/** ************************
 * 第8.1.1节 - 事件回调函数
 *
 ***************************/
// for vtk 8.1 use :
//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkInteractionStyle)
//VTK_MODULE_INIT(vtkRenderingFreeType)
//VTK_MODULE_INIT(vtkRenderingOpenGL2)
////////////////////////////////////////////

#include<vtkObject.h>
#include<vtkSmartPointer.h>
#include<vtkPNGReader.h>
#include<vtkImageViewer2.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkCallbackCommand.h>

long pressCount = 0;
//事件回调函数（签名固定如下形式）
void MyCallBackFunc(vtkObject*, unsigned long eid, void* clientdata,void *calldata){
    std::cout<<"You have clicked:"<<++pressCount<<"times."<<std::endl;
}

int main(int argc, char* argv[]){
    vtkSmartPointer<vtkPNGReader> reader = vtkSmartPointer<vtkPNGReader>::New();
    reader->SetFileName(argv[1]);

    vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2>::New();
    viewer->SetInputConnection(reader->GetOutputPort());
//    vtkSmartPointer<vtkImageViewer2> viewer1 = vtkSmartPointer<vtkImageViewer2>::New();
//    viewer1=viewer;

    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    viewer->SetupInteractor(interactor);
    viewer->Render();

    vtkSmartPointer<vtkCallbackCommand> mouseCallback = vtkSmartPointer<vtkCallbackCommand>::New();
    mouseCallback->SetCallback( MyCallBackFunc );

    interactor->SetRenderWindow(viewer->GetRenderWindow());
    interactor->AddObserver(vtkCommand::LeftButtonPressEvent,mouseCallback);
    interactor->Initialize();
    interactor->Start();


    return 0;

}
