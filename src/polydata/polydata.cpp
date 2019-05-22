/**
  * 6.1.2 polydata
 */
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkPolygon.h>
#include <vtkTriangle.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderWindow.h>

#define NEW_VTK(type, name) vtkSmartPointer<type> name =  vtkSmartPointer<type>::New()

int main(){
    //定义点集合
    NEW_VTK(vtkPoints, points);
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 1.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);
    points->InsertNextPoint(2.0, 0.0, 0.0);

    //定义多边形拓扑单元
    NEW_VTK(vtkPolygon, polygon);
    polygon->GetPointIds()->SetNumberOfIds(4);
    polygon->GetPointIds()->SetId(0, 0);
    polygon->GetPointIds()->SetId(1, 1);
    polygon->GetPointIds()->SetId(2, 2);
    polygon->GetPointIds()->SetId(3, 3);

    //定义三角形拓扑单元
    NEW_VTK(vtkTriangle, triangle);
    triangle->GetPointIds()->SetId(0, 1);
    triangle->GetPointIds()->SetId(1, 2);
    triangle->GetPointIds()->SetId(2, 4);

    //定义单元集合
    NEW_VTK(vtkCellArray, cells);
    cells->InsertNextCell(polygon);
    cells->InsertNextCell(triangle);

    //定义polydata
    NEW_VTK(vtkPolyData, polygonPolyfata);
    polygonPolyfata->SetPoints(points);
    polygonPolyfata->SetPolys(cells);

    //模型映射
    NEW_VTK(vtkPolyDataMapper, modelMapper);
    modelMapper->SetInput(polygonPolyfata);

    //模型演员
    NEW_VTK(vtkActor, modelActor);
    modelActor->SetMapper(modelMapper);

    //模型的渲染器
    NEW_VTK(vtkRenderer, rendererModel);
    rendererModel->SetBackground(0.5,0.5,0.5);
    rendererModel->ResetCamera();
    rendererModel->AddActor(modelActor);

    //渲染窗口
    NEW_VTK(vtkRenderWindow, renderWindow);
    renderWindow->SetSize(512, 512);
    renderWindow->AddRenderer(rendererModel);

    //交互器
    NEW_VTK(vtkRenderWindowInteractor, interactor);
    NEW_VTK(vtkInteractorStyleTrackballCamera, style);
    interactor->SetRenderWindow(renderWindow);
    interactor->SetInteractorStyle(style);
    interactor->Initialize();
    interactor->Start();

}
