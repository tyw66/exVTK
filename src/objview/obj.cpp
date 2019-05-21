/** ************************
  * VTK读取OBJ模型
  * 2017.11.22 - tyw
 ***************************/
// for vtk 8.1 use :
//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkInteractionStyle)
///VTK_MODULE_INIT(vtkRenderingFreeType)
//VTK_MODULE_INIT(vtkRenderingOpenGL2)
////////////////////////////////////////////

#include"vtkSmartPointer.h"
#include"vtkCylinderSource.h"
#include <vtkPolyDataMapper.h>
#include"vtkActor.h"
#include"vtkProperty.h"
#include"vtkRenderer.h"
#include"vtkCamera.h"
#include"vtkRenderWindow.h"
#include"vtkRenderWindowInteractor.h"
#include"vtkLight.h"
#include"vtkBMPReader.h"
#include "vtkInteractorStyleTrackballCamera.h"

#include <vtkOBJReader.h>


#include "vtkImageViewer2.h"

#define NEW_VTK(object, name) vtkSmartPointer<object> name=vtkSmartPointer<object>::New()

int main()
{
    //OBJ模型数据源
    NEW_VTK(vtkOBJReader, objReader);
    objReader->SetFileName("./res/lego.obj");
    objReader->Update();//可以省略


    //模型映射 渲染几何数据
    NEW_VTK(vtkPolyDataMapper,objMapper);
    objMapper->SetInputConnection(objReader->GetOutputPort());

    //  objMapper->Print(std::cout);

    //读贴图
    NEW_VTK(vtkBMPReader,imgReader);
    imgReader->SetFileName("./lego.bmp");


    NEW_VTK(vtkTexture,objTexture);
    objTexture->SetInputConnection(imgReader->GetOutputPort());

    //  objTexture->Print(std::cout);

    //几何数据实体
    NEW_VTK(vtkActor, objActor);
    objActor->SetMapper(objMapper);
    objActor->SetTexture(objTexture);
    objActor->GetProperty()->SetColor(1,1,1);


    //渲染器
    vtkSmartPointer<vtkRenderer>renderer=vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(objActor);
    renderer->SetBackground(0.5,0.5,0.5);
    renderer->ResetCamera();
    //  renderer->GetActiveCamera()->Zoom(1.5);

    //渲染窗口
    vtkSmartPointer<vtkRenderWindow>renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(256,256);
    renderWindow->AddRenderer(renderer);

    //交互器
    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);

    NEW_VTK(vtkInteractorStyleTrackballCamera, style);

    interactor->SetInteractorStyle(style);

    interactor->Initialize();

    //光源
    vtkSmartPointer<vtkLight>myLight_green = vtkSmartPointer<vtkLight>::New();
    myLight_green->SetColor(0,1,0);
    myLight_green->SetPosition(0,0,1);
    myLight_green->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    renderer->AddLight(myLight_green);
    myLight_green->SwitchOff();  //关灯

    vtkSmartPointer<vtkLight>myLight_blue = vtkSmartPointer<vtkLight>::New();
    myLight_blue->SetColor(0,0,1);
    myLight_blue->SetPosition(0,0,-1);
    myLight_blue->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    renderer->AddLight(myLight_blue);
    myLight_blue->SwitchOff();

    //相机
    vtkSmartPointer<vtkCamera> myCamera = vtkSmartPointer<vtkCamera>::New();
    myCamera->SetClippingRange(0.5,10);
    //  myCamera->SetFocalPoint(.....);//to be countinued


    //    //贴图查看
    //    NEW_VTK(vtkImageViewer2,imgViewer);
    //    NEW_VTK(vtkRenderWindowInteractor,textureInteractor);
    //    imgViewer->SetInputConnection(imgReader->GetOutputPort());
    //    imgViewer->SetupInteractor(textureInteractor);
    //    imgViewer->Render();




    interactor->Start();

    return EXIT_SUCCESS;


}
