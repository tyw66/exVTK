/** ************************
 * 第8.1.2节 - 子类化command
 *
 ***************************/
// for vtk 8.1 use :
//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkInteractionStyle)
//VTK_MODULE_INIT(vtkRenderingFreeType)
//VTK_MODULE_INIT(vtkRenderingOpenGL2)
////////////////////////////////////////////

#include<vtkCommand.h>
#include<vtkConeSource.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkInteractorStyleTrackballCamera.h>
#include<vtkSmartPointer.h>

class MyCallback
    : public vtkCommand
{
                 public:
                 static MyCallback* New(){ return new MyCallback; }
                 void setObject(vtkConeSource* cone){ m_cone = cone; }
                 virtual void Execute(vtkObject* caller, unsigned long eventId, void* callData){
                    std::cout<<"Left button pressed.\n"
                            <<"the height:"<<m_cone->GetHeight()<<"\n"
                           <<"the redius:"<<m_cone->GetRadius()<<std::endl;
                 }
                 private:
                 vtkConeSource *m_cone;
};

#define NEW_VTK(type, name) vtkSmartPointer<type> name =  vtkSmartPointer<type>::New()
int main(){
    NEW_VTK(vtkConeSource,cone);
    cone->SetRadius(10);
    cone->SetHeight(20);
    cone->SetResolution(12);

    NEW_VTK(vtkPolyDataMapper,coneMapper);
    coneMapper->SetInputConnection(cone->GetOutputPort());

    NEW_VTK(vtkActor,coneActor);
    coneActor->SetMapper(coneMapper);

    NEW_VTK(vtkRenderer,ren1);
    ren1->AddActor(coneActor);
    ren1->SetBackground(0.1,0.2,0.4);

    NEW_VTK(vtkRenderWindow,renWin);
    renWin->AddRenderer(ren1);
    renWin->SetSize(300,300);

    NEW_VTK(vtkRenderWindowInteractor,interactor);
    interactor->SetRenderWindow(renWin);

    NEW_VTK(vtkInteractorStyleTrackballCamera,style);
    interactor->SetInteractorStyle(style);

    //设置
    NEW_VTK(MyCallback,callback);
    callback->setObject(cone);

    interactor->AddObserver(vtkCommand::LeftButtonPressEvent,callback);
    interactor->Initialize();
    interactor->Start();


}
