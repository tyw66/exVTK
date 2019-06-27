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
#include<vtkImageActor.h>


#include "vtkImageViewer2.h"

#include <vtkPolyDataNormals.h>
#include <vtkMaskPoints.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>

#include <vtkProperty.h>


#define NEW_VTK(object, name) vtkSmartPointer<object> name=vtkSmartPointer<object>::New()

int main()
{
    //OBJ模型数据源
    NEW_VTK(vtkOBJReader, objReader);
    objReader->SetFileName("../data/lego.obj");
    objReader->Update();//可以省略

    //计算法向量并显示
    NEW_VTK(vtkPolyDataNormals, normalFilter);
    normalFilter->SetInput(objReader->GetOutput());
    normalFilter->SetComputePointNormals(1);
    normalFilter->SetComputeCellNormals(0);
    normalFilter->Update();

    NEW_VTK(vtkMaskPoints, mask);
    mask->SetInput(normalFilter->GetOutput());
    mask->SetMaximumNumberOfPoints(1000);
    mask->RandomModeOn();
    mask->Update();

    NEW_VTK(vtkArrowSource, arrow);
    NEW_VTK(vtkGlyph3D, glyph);
    glyph->SetInput(mask->GetOutput());
    glyph->SetSource(arrow->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleFactor(5);

    //模型映射 渲染几何数据
    NEW_VTK(vtkPolyDataMapper,objMapper);
    objMapper->SetInputConnection(objReader->GetOutputPort());

    NEW_VTK(vtkPolyDataMapper,normalMapper);
    normalMapper->SetInput(glyph->GetOutput());

    //读贴图
    NEW_VTK(vtkBMPReader,imgReader);
    imgReader->SetFileName("../data/lego.bmp");


    NEW_VTK(vtkTexture,objTexture);
    objTexture->SetInputConnection(imgReader->GetOutputPort());

    //  objTexture->Print(std::cout);

    //模型演员
    NEW_VTK(vtkActor, objActor);
    objActor->SetMapper(objMapper);
    objActor->SetTexture(objTexture);
    objActor->GetProperty()->SetColor(1,1,1);

    //法线
    NEW_VTK(vtkActor, normalActor);
    normalActor->SetMapper(normalMapper);

    //贴图演员
    NEW_VTK(vtkImageActor, imgActor);
    imgActor->SetInput(imgReader->GetOutput());

    //模型的渲染器（左）
    NEW_VTK(vtkRenderer, rendererModel);
    rendererModel->SetBackground(0.5,0.5,0.5);
    rendererModel->ResetCamera();
//    rendererModel->SetViewport(0,1,0,0.5);
    rendererModel->AddActor(objActor);
    rendererModel->AddActor(normalActor);

//    //贴图的渲染器（右）
//    NEW_VTK(vtkRenderer, rendererImg);
//    rendererImg->SetBackground(0.5,0.5,0.5);
//    rendererImg->ResetCamera();
//    rendererImg->SetViewport(0,1,0.5,1.0);
//    rendererImg->AddActor(imgActor);


    //渲染窗口
    NEW_VTK(vtkRenderWindow, renderWindow);
    renderWindow->SetSize(512, 512);
//    renderWindow->AddRenderer(rendererImg);
    renderWindow->AddRenderer(rendererModel);

    //交互器
    NEW_VTK(vtkRenderWindowInteractor, interactor);
    NEW_VTK(vtkInteractorStyleTrackballCamera, style);
    interactor->SetRenderWindow(renderWindow);
    interactor->SetInteractorStyle(style);
    interactor->Initialize();

//    //光源
//    vtkSmartPointer<vtkLight>myLight_green = vtkSmartPointer<vtkLight>::New();
//    myLight_green->SetColor(0,1,0);
//    myLight_green->SetPosition(0,0,1);
//    myLight_green->SetFocalPoint(rendererModel->GetActiveCamera()->GetFocalPoint());
//    rendererModel->AddLight(myLight_green);
//    myLight_green->SwitchOff();  //关灯

//    vtkSmartPointer<vtkLight>myLight_blue = vtkSmartPointer<vtkLight>::New();
//    myLight_blue->SetColor(0,0,1);
//    myLight_blue->SetPosition(0,0,-1);
//    myLight_blue->SetFocalPoint(rendererModel->GetActiveCamera()->GetFocalPoint());
//    rendererModel->AddLight(myLight_blue);
//    myLight_blue->SwitchOff();

    //相机
//    vtkSmartPointer<vtkCamera> myCamera = vtkSmartPointer<vtkCamera>::New();
//    myCamera->SetClippingRange(0.5,10);
    //  myCamera->SetFocalPoint(.....);//to be countinued


//    //贴图查看
//    NEW_VTK(vtkImageViewer2,imgViewer);
//    imgViewer->SetInputConnection(imgReader->GetOutputPort());
//    NEW_VTK(vtkRenderWindowInteractor,textureInteractor);
//    imgViewer->SetupInteractor(textureInteractor);
//    imgViewer->Render();



    interactor->Start();
    return EXIT_SUCCESS;


}
