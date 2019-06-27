/**
  *cube
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
#include <vtkMaskPoints.h>
#include <vtkArrowSource.h>
#include <vtkGlyph3D.h>

#include <vtkProperty.h>

#define NEW_VTK(type, name) vtkSmartPointer<type> name =  vtkSmartPointer<type>::New()


int main(){
    ///            2 -------------1
    ///         /  |             /  |
    ///      /     |          /     |
    ///   3 ------|----- 0       |
    ///   |         6  ----|----- 5
    ///   |     /           |    /
    ///   |  /              | /
    ///  7 -------------4

    //定义点集合
    NEW_VTK(vtkPoints, points);
    points->InsertNextPoint(1.0, 1.0, 1.0); //0
    points->InsertNextPoint(1.0, 0.0, 1.0); //1
    points->InsertNextPoint(0.0, 0.0, 1.0);
    points->InsertNextPoint(0.0, 1.0, 1.0);
    points->InsertNextPoint(1.0, 1.0, 0.0);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);

    //定义多边形拓扑单元
    NEW_VTK(vtkPolygon, polygon01);
    polygon01->GetPointIds()->SetNumberOfIds(4);
    polygon01->GetPointIds()->SetId(0, 0);
    polygon01->GetPointIds()->SetId(1, 1);
    polygon01->GetPointIds()->SetId(2, 2);
    polygon01->GetPointIds()->SetId(3, 3);
    NEW_VTK(vtkPolygon, polygon02);
    polygon02->GetPointIds()->SetNumberOfIds(4);
    polygon02->GetPointIds()->SetId(0, 0);
    polygon02->GetPointIds()->SetId(1, 4);
    polygon02->GetPointIds()->SetId(2, 5);
    polygon02->GetPointIds()->SetId(3, 1);
    NEW_VTK(vtkPolygon, polygon03);
    polygon03->GetPointIds()->SetNumberOfIds(4);
    polygon03->GetPointIds()->SetId(0, 0);
    polygon03->GetPointIds()->SetId(1, 3);
    polygon03->GetPointIds()->SetId(2, 7);
    polygon03->GetPointIds()->SetId(3, 4);
    NEW_VTK(vtkPolygon, polygon04);
    polygon04->GetPointIds()->SetNumberOfIds(4);
    polygon04->GetPointIds()->SetId(0, 2);
    polygon04->GetPointIds()->SetId(1, 6);
    polygon04->GetPointIds()->SetId(2, 7);
    polygon04->GetPointIds()->SetId(3, 3);
    NEW_VTK(vtkPolygon, polygon05);
    polygon05->GetPointIds()->SetNumberOfIds(4);
    polygon05->GetPointIds()->SetId(0, 1);
    polygon05->GetPointIds()->SetId(1, 5);
    polygon05->GetPointIds()->SetId(2, 6);
    polygon05->GetPointIds()->SetId(3, 2);
    NEW_VTK(vtkPolygon, polygon06);
    polygon06->GetPointIds()->SetNumberOfIds(4);
    polygon06->GetPointIds()->SetId(0, 7);
    polygon06->GetPointIds()->SetId(1, 6);
    polygon06->GetPointIds()->SetId(2, 5);
    polygon06->GetPointIds()->SetId(3, 4);


    //定义单元集合
    NEW_VTK(vtkCellArray, cells);
    cells->InsertNextCell(polygon01);
    cells->InsertNextCell(polygon02);
    cells->InsertNextCell(polygon03);
    cells->InsertNextCell(polygon04);
    cells->InsertNextCell(polygon05);
    cells->InsertNextCell(polygon06);

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
    normalFilter->SetComputePointNormals(0);
    normalFilter->SetComputeCellNormals(1);
    normalFilter->Update();

    NEW_VTK(vtkMaskPoints, mask);
    mask->SetInput(normalFilter->GetOutput());
    mask->SetMaximumNumberOfPoints(300);
    mask->RandomModeOn();
    mask->Update();

    NEW_VTK(vtkArrowSource, arrow);
    NEW_VTK(vtkGlyph3D, glyph);
    glyph->SetInput(mask->GetOutput());
    glyph->SetSource(arrow->GetOutput());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleFactor(0.5);

    //模型映射
    NEW_VTK(vtkPolyDataMapper, modelMapper);
    modelMapper->SetInput(polygonPolydata);

    //
    NEW_VTK(vtkPolyDataMapper, vectorMapper);
    vectorMapper->SetInput(glyph->GetOutput());


    //--可视化管线结束--

    //模型演员
    NEW_VTK(vtkActor, modelActor);
    modelActor->SetMapper(modelMapper);

    NEW_VTK(vtkActor, normalActor);
    normalActor->SetMapper(vectorMapper);
    normalActor->GetProperty()->SetColor(1.0,1.0,1.0);

    //模型的渲染器
    NEW_VTK(vtkRenderer, rendererModel);
    rendererModel->SetBackground(0.5,0.5,0.5);
    rendererModel->ResetCamera();
    rendererModel->AddActor(modelActor);
    rendererModel->AddActor(normalActor);

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
