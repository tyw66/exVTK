/** ************************
 * 第3章 - 数据集
 *
 ***************************/
/*
// for vtk 8.1 use :
//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkInteractionStyle)
//VTK_MODULE_INIT(vtkRenderingFreeType)
//VTK_MODULE_INIT(vtkRenderingOpenGL2)
*/


#include "vtkSmartPointer.h"
#include "vtkPoints.h"
#include "vtkPolyData.h"
#include "vtkLine.h"

#include "vtkPolyDataWriter.h"

#include"vtkDataSet.h"

#include "vtkImageData.h"

#define NEW_VTK(type, name) vtkSmartPointer<type> name =  vtkSmartPointer<type>::New()
int main()
{
    NEW_VTK(vtkPoints, points);
    points->InsertNextPoint(1.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 1.0, 0.0);

    //SetId( 线段的一个端点的ID, 连接的点的ID );
    NEW_VTK(vtkLine, line1);
    line1->GetPointIds()->SetId(0,0);
    line1->GetPointIds()->SetId(1,1);

    NEW_VTK(vtkLine, line2);
    line2->GetPointIds()->SetId(0,1);
    line2->GetPointIds()->SetId(1,2);

    NEW_VTK(vtkLine, line3);
    line3->GetPointIds()->SetId(0,2);
    line3->GetPointIds()->SetId(1,0);

    vtkIdType pid[1];
    NEW_VTK(vtkCellArray, lines);
    lines->InsertNextCell(line1);
    lines->InsertNextCell(line2);
    lines->InsertNextCell(line3);

    //最终是去填充vtkPolyData数据集
    NEW_VTK(vtkPolyData, polyData);
    polyData->SetPoints(points);
    polyData->SetLines(lines);




/*
  NEW_VTK(vtkPoints, points);
  points->InsertNextPoint(1.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 0.0, 0.0);
  points->InsertNextPoint(0.0, 1.0, 0.0);

  NEW_VTK(vtkPolyData, polyData);
  polyData->SetPoints(points);

//  NEW_VTK(vtkPolyDataWriter, writer);
//  writer->SetFileName("triangle.vtk");
//  writer->SetInput(polyData);
//  writer->Write();
*/

    //////////////////////////////////////////

    NEW_VTK(vtkImageData,img);
    img->SetDimensions(10,10,10);
//    img->SetScalarType(VTK_UNSIGNED_CHAR);
//    img->SetNumberOfScalarComponents(1);
//    img->AllocateScalars();//根据前面的设置分配内存

unsigned char *ptr = (unsigned char*)img->GetScalarPointer();
for(int i=0; i<10*10*10;i++){
    *ptr ++ = i%256;
}
  return EXIT_SUCCESS;
}
