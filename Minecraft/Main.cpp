#include "Main.h"
#include "Window.h"
using namespace Gdiplus;
using namespace MLQC;
#pragma comment(lib,"Gdiplus.lib")

Application* app;

int WINAPI WinMain(HINSTANCE hIns, HINSTANCE prevHINS, LPSTR lpCmdLine, int nCmdShow) {

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	// Initialize main applications class 
	Application::init(&hIns);
	app = Application::getInstance();

	// Get size of monitor
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);

	// Create window
	Window* w = app->createWindow("main", (rect.right - rect.left) / 2 - 848 / 2, (rect.bottom - rect.top) / 2 - 480 / 2, 848, 480);
	w->onCreate();

	// Show window
	w->show();
	SetLayeredWindowAttributes(*w->getHWND(), RGB(0, 0xAA, 0xF1), 0, LWA_COLORKEY);
	

	MSG msg;
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	GdiplusShutdown(gdiplusToken);

	delete app;

	return int(msg.wParam);
}