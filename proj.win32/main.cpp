#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("MyFlappyBird");
    //eglView->setFrameSize(768/2., 1280/2.);
	//s3
	eglView->setFrameSize( 720/3,1280/3);
	//note3 1920*1080
	//eglView->setFrameSize( 320,480);
	//eglView->setFrameSize( 1080/3,1920/3);
    return CCApplication::sharedApplication()->run();
}
