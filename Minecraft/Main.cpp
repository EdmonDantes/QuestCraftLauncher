#include "Main.h"
using namespace Gdiplus;
#pragma comment(lib,"Gdiplus.lib")

int WINAPI WinMain(HINSTANCE hIns, HINSTANCE prevHINS, LPSTR lpCmdLine, int nCmdShow) {

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize main form

	MSG msg;
	WNDCLASSEX wc;
	HINSTANCE glhinst = hIns;
	
	wc.cbSize = sizeof(wc);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "minecraftLauncherQuestCraftMainForm";
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	auto icon = LoadIcon(hIns, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIcon = icon;
	wc.hIconSm = icon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	wc.hInstance = hIns;


	// Check class
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "ERROR ¹1", "Error", MB_OK);
		return NULL;
	}

	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	HWND hMainWnd = CreateWindowEx(WS_EX_LAYERED, "minecraftLauncherQuestCraftMainForm", "QuestCraft	", WS_OVERLAPPED | WS_SYSMENU | WS_POPUP, (int)(rect.right - rect.left) / 2 - 848 / 2, (int)(rect.bottom - rect.top) / 2 - 480 / 2, 848, 480, HWND(NULL), NULL, HINSTANCE(hIns), NULL);


	if (!hMainWnd) {
		MessageBox(NULL, "ERROR ¹2", "Error", MB_OK);
		return NULL;
	}

	ShowWindow(hMainWnd, nCmdShow);

	//UpdateWindow(hMainWnd);

	SetLayeredWindowAttributes(hMainWnd, RGB(0, 0, 255), 0, LWA_COLORKEY);
	SetLayeredWindowAttributes(hMainWnd, RGB(0, 0xAA, 0xF1), 0, LWA_COLORKEY);


	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	GdiplusShutdown(gdiplusToken);

	return int(msg.wParam);
}

int index = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	std::cout << "Wnd: " << index++ << '\n';
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}