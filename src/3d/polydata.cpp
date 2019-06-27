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
#include <vtkPolyDataWriter.h>

#include <vtkPolyDataNormals.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>
#include <vtkProperty.h>

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

    //定义polydata，把点集合与单元（拓扑）集合相联系。
    NEW_VTK(vtkPolyData, polygonPolydata);
    polygonPolydata->SetPoints(points);
    polygonPolydata->SetPolys(cells);

    //导出到VTK文件
    NEW_VTK(vtkPolyDataWriter, polydatawriter);
    polydatawriter->SetFileName("./model.vtk");
    polydatawriter->SetInput(polygonPolydata);
    polydatawriter->Write();

    //计算法向量并显示
    NEW_VTK(vtkPolyDataNormals, normalFilter);
    normalFilter->SetInput(polygonPolydata);
//    normalFilter->SetComputePointNormals(0);
//    normalFilter->SetComputeCellNormals(1);
    normalFilter->Update();

    NEW_VTK(vtkArrowSource, arrow);
    NEW_VTK(vtkGlyph3D, glyph);
    glyph->SetInput(normalFilter->GetOutput());
    glyph->SetSource(arrow->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleFactor(0.2);

    //模型映射
    NEW_VTK(vtkPolyDataMapper, modelMapper);
    modelMapper->SetInput(polygonPolydata);

    //法线模型映射
    NEW_VTK(vtkPolyDataMapper, normalMapper);
    normalMapper->SetInput(glyph->GetOutput());

    //--可视化管线结束--

    //模型演员
    NEW_VTK(vtkActor, modelActor);
    modelActor->SetMapper(modelMapper);

    NEW_VTK(vtkActor, nomallActor);
    nomallActor->SetMapper(normalMapper);
    nomallActor->GetProperty()->SetColor(0.2,0.8,0.9);

    //模型的渲染器
    NEW_VTK(vtkRenderer, rendererModel);
    rendererModel->SetBackground(0.5,0.5,0.5);
    rendererModel->ResetCamera();
    rendererModel->AddActor(modelActor);
    rendererModel->AddActor(nomallActor);

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
