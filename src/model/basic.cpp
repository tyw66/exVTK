/** ************************
  * VTK简单程序-渲染管线
  * 2017.11.22 - tyw
 ***************************/
// for vtk 8.1 use :
//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkInteractionStyle)
//VTK_MODULE_INIT(vtkRenderingFreeType)
//VTK_MODULE_INIT(vtkRenderingOpenGL2)
////////////////////////////////////////////

#include "vtkSmartPointer.h"
#include "vtkCylinderSource.h"
#include <vtkPolyDataMapper.h>
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkLight.h"

#include "vtkCellType.h"
#include "vtkCellData.h"
#include"vtkTexture.h"
#include"vtkBMPReader.h"

#include"vtkDataSet.h"
#include<vtkImageData.h>
#include<vtkAlgorithmOutput.h>

int main()
{
    //数据源
    vtkSmartPointer<vtkCylinderSource> cylinder=vtkSmartPointer<vtkCylinderSource>::New();
    cylinder->SetResolution(10);//分辨率
    cylinder->SetHeight(20);
    cylinder->SetRadius(5);

    //模型映射 渲染几何数据
    vtkSmartPointer<vtkPolyDataMapper> cylinderMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());

    //演员
    vtkSmartPointer<vtkActor> cylinderActor=vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    //    cylinderActor->GetProperty()->SetColor(1,0,0);
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(0.0);
    cylinderActor->RotateZ(45.0);

    //模型纹理
    vtkSmartPointer<vtkBMPReader> reader =vtkSmartPointer<vtkBMPReader> ::New();
    reader->SetFileName("./lego.bmp");
    vtkSmartPointer<vtkTexture> texture =vtkSmartPointer<vtkTexture> ::New();
    texture->SetInputConnection(reader->GetOutputPort());
    //    cylinderActor->SetTexture(texture);


    //渲染器
    vtkSmartPointer<vtkRenderer>renderer=vtkSmartPointer<vtkRenderer>::New();
    renderer->SetBackground(0.8,0.8,0.8);
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Zoom(1.5);
    renderer->AddActor(cylinderActor);


    //渲染窗口
    vtkSmartPointer<vtkRenderWindow>renderWindow=vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize(500,500);
    renderWindow->SetWindowName("Basic Drawing");
    renderWindow->AddRenderer(renderer);

    //光源
    vtkSmartPointer<vtkLight>myLight_green = vtkSmartPointer<vtkLight>::New();
    myLight_green->SetColor(0,1,0);
    myLight_green->SetPosition(0,0,1);
    myLight_green->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    renderer->AddLight(myLight_green);

    vtkSmartPointer<vtkLight>myLight_blue = vtkSmartPointer<vtkLight>::New();
    myLight_blue->SetColor(0,0,1);
    myLight_blue->SetPosition(0,0,-1);
    myLight_blue->SetFocalPoint(renderer->GetActiveCamera()->GetFocalPoint());
    renderer->AddLight(myLight_blue);

//    myLight_green->SwitchOff();
//    myLight_blue->SwitchOff();


    //相机
    vtkSmartPointer<vtkCamera> myCamera = vtkSmartPointer<vtkCamera>::New();
    myCamera->SetClippingRange(0.5,10);
    //  myCamera->SetFocalPoint(.....);//todo


    //交互器
    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =   vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);
    interactor->Start();


    return EXIT_SUCCESS;

}
