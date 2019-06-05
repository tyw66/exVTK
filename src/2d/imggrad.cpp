/** *****************************************************
 *
 * VTK图像学习：边缘检测
 * By : tyw66  - 2019/01/17
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

#include<vtkImageGradient.h>
#include<vtkImageMagnitude.h>
#include<vtkImageShiftScale.h>

#include<vtkJPEGReader.h>
#include<vtkImageLuminance.h>

#define W 256
#define H 256
#define NEW_VTK(obj, name) vtkSmartPointer<obj> name = vtkSmartPointer<obj>::New()


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
    //数据源输入
    NEW_VTK(vtkImageData, img);
    img->SetDimensions(W,H,1);
    img->SetScalarTypeToUnsignedChar();
    img->SetNumberOfScalarComponents(3);
    img->AllocateScalars();

    unsigned char *ptr = (unsigned char*)img->GetScalarPointer();
    if(!drawCoin(ptr)){//img赋值 填充像素画图
        return -1;
    }


//    NEW_VTK(vtkJPEGReader, jpgReader);
//    jpgReader->SetFileName("..//data//lego.jpg");
//    jpgReader->Update();


    //图像处理部分
    //转为灰度图
    NEW_VTK(vtkImageLuminance, luminanceFilter);
    luminanceFilter->SetInput(img);
    luminanceFilter->Update();


    //计算梯度
    NEW_VTK(vtkImageGradient, gradFilter);
    gradFilter->SetDimensionality(2);//二维
    gradFilter->SetInputConnection(luminanceFilter->GetOutputPort()); //img图像
//    gradFilter->SetInputConnection(jpgReader->GetOutputPort()); //JPG图像

    //求梯度的模
    NEW_VTK(vtkImageMagnitude, magFilter);
    magFilter->SetInputConnection(gradFilter->GetOutputPort());
    magFilter->Update();
    double range[2];
    magFilter->GetOutput()->GetScalarRange(range);    //求梯度的最大值用于缩放

    //数据缩放
    NEW_VTK(vtkImageShiftScale, shiftScale);
    shiftScale->SetOutputScalarTypeToChar();
    shiftScale->SetScale(255/range[1]);
    shiftScale->SetShift(0);
//    std::cout<<range[0]<<"   "<<range[1]<<std::endl;;
    shiftScale->SetInputConnection(magFilter->GetOutputPort());
    shiftScale->Update();

    //演员
    NEW_VTK(vtkImageActor, redActor);
    redActor->SetInput(shiftScale->GetOutput());

    //渲染器
    NEW_VTK(vtkRenderer, redRenderer);
    redRenderer->SetBackground(1.0, 1.0, 1.0);
    redRenderer->ResetCamera();
    redRenderer->SetViewport(0.0, 0.0, 1.0, 1.0);
    redRenderer->AddActor(redActor);

    //渲染窗口
    NEW_VTK(vtkRenderWindow, renderWindow);
    renderWindow->SetSize( 256, 256 );
    renderWindow->SetWindowName("Image Data");
    renderWindow->AddRenderer(redRenderer);

    //交互器
    NEW_VTK(vtkRenderWindowInteractor, renderWindowInteractor);
    NEW_VTK(vtkInteractorStyleTrackballCamera, style);
    renderWindowInteractor->SetInteractorStyle(style);
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindowInteractor->Initialize();
    renderWindowInteractor->Start();


    //    ////////////////////////////////////////////////////////////
    //    ///2 使用ImageViewer类显示图像
    //    ////////////////////////////////////////////////////////////
    //    //设置ImageViewer
    //    vtkSmartPointer<vtkImageViewer2> viewer = vtkSmartPointer<vtkImageViewer2> ::New();
    //    viewer->SetColorLevel(127.5);//窗位
    //    viewer->SetColorWindow(255);//窗宽
    //    viewer->SetInput(img);
    //    viewer->SetSlice(30);
    //    viewer->SetSliceOrientationToXY();
    //    //设置交互器
    //    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //    vtkSmartPointer<vtkInteractorStyleImage> style =  vtkSmartPointer<vtkInteractorStyleImage>::New();
    //    renderWindowInteractor->SetInteractorStyle(style);
    //    viewer->SetupInteractor(renderWindowInteractor);
    //    viewer->Render();
    //    renderWindowInteractor->Start();



    return EXIT_SUCCESS;
}
