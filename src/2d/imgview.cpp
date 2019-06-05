/** *****************************************************
 *
 * VTK图像学习：1、直接对像素画图；2、用两种方式显示图像
 * By : tyw66  - 2019/01/16
 *
 * ******************************************************/
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageViewer2.h>

#define W 256
#define H 256

/**
 * @brief 圆形方孔钱
 * @param ptr
 * @return
 */
bool drawCoin(unsigned char *ptr){
    for(int i = 0; i < W*H*1; i++)
    {
        int col = i/W - W*0.5;
        int row = i%H - H*0.5;

        if(col*col+row*row < 4000 &     //圆形内
                !(col < 20 & col > -20 & row < 20 & row > -20)){//方孔外
            //金色
            *(ptr++) = 200;
            *(ptr++) = 200;
            *(ptr++) = 0;
        }
        else {
            //背景色
            *(ptr++) = 100;
            *(ptr++) = 125;
            *(ptr++) = 128;
        }

    }
    return true;
}



int main()
{
    //数据源
    vtkSmartPointer<vtkImageData> img =  vtkSmartPointer<vtkImageData>::New();
    img->SetDimensions(W,H,1);
    img->SetScalarTypeToUnsignedChar();
    img->SetNumberOfScalarComponents(3);
    img->AllocateScalars();

    unsigned char *ptr = (unsigned char*)img->GetScalarPointer();
    if(!drawCoin(ptr)){//img赋值 填充像素画图
        return -1;
    }

    /*
    ////////////////////////////////////////////////////////////
    ///1 使用管线显示图像
    ////////////////////////////////////////////////////////////
    //演员
    vtkSmartPointer<vtkImageActor> redActor = vtkSmartPointer<vtkImageActor>::New();
    redActor->SetInput(img);

    //渲染器
    double redViewport[4] = {0.0, 0.0, 1.0, 1.0};
    vtkSmartPointer<vtkRenderer> redRenderer = vtkSmartPointer<vtkRenderer>::New();
    redRenderer->SetBackground(1.0, 1.0, 1.0);
    redRenderer->ResetCamera();
    redRenderer->SetViewport(redViewport);
    redRenderer->AddActor(redActor);

    //渲染窗口
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->SetSize( 256, 256 );
    renderWindow->SetWindowName("Image Data");
    renderWindow->AddRenderer(redRenderer);

    //交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style =  vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();
*/

    ////////////////////////////////////////////////////////////
    ///2 使用ImageViewer类显示图像
    ////////////////////////////////////////////////////////////
    //设置ImageViewer
    vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2> ::New();
    viewer->SetColorLevel(127.5);//窗位
    viewer->SetColorWindow(255);//窗宽
    viewer->SetInput(img);
    viewer->SetSlice(30);
    viewer->SetSliceOrientationToXY();
    //设置交互器
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleImage> style =  vtkSmartPointer<vtkInteractorStyleImage>::New();
    renderWindowInteractor->SetInteractorStyle(style);
    viewer->SetupInteractor(renderWindowInteractor);
    viewer->Render();
    renderWindowInteractor->Start();



    return EXIT_SUCCESS;
}
