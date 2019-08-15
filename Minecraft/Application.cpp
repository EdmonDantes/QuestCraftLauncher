#include "ViewGroup.h"
#include "ImageView.h"
#include "TextView.h"
#include "resource.h"

namespace MLQC {
	Application* Application::INSTANCE = NULL;

	Application::Application(HINSTANCE* ins) {
		this->instance = ins;
	}

	void Application::init(HINSTANCE* inst) {
		Application::INSTANCE = new Application(inst);
	}

	Application* Application::getInstance() {
		return Application::INSTANCE;
	}

	void Application::onCreate() {}
	void Application::onStart() {}
	void Application::onStop() {
		for (Window* window : windows) {
			if (window != NULL) {
				window->onDestroy();
				delete window;
			}
		}
	}

	LRESULT CALLBACK Application::onAction(HWND hwnd, UINT msg, WPARAM wpr, LPARAM lpr) {
		Window* window = Application::getInstance()->getWindow(hwnd);

		if (window != NULL) {
				MLQCAction __action;
				__action.wParam = wpr;
				__action.lParam = lpr;
				switch (msg) {
					case WM_SETFOCUS: //7
						window->showed = true;
						window->minimizable = window->rightAttr.move = window->leftAttr.move = false;
						break;
					case WM_ERASEBKGND: //20
						return TRUE;
					case WM_SHOWWINDOW: //24
						if (wpr) {
							window->showed = true;
							window->minimizable = false;
							window->update();
						}
						break;
					case WM_PAINT: //15
						window->paint();
						break;
					case WM_KEYDOWN: //256
						__action.type = MLQC_ACTION_KEY_DOWN;
						window->onAction(__action);
						break;
					case WM_KEYUP: //257
						__action.type = MLQC_ACTION_KEY_UP;
						window->onAction(__action);
						break;
					case WM_LBUTTONDOWN: //513
						__action.type = MLQC_ACTION_MOUSE_DOWN_LEFT;
						window->onAction(__action);

						if (window->movable || window->clickable)
							GetCursorPos(&window->leftAttr.point);

						if (window->movable) {
							window->leftAttr.x = GET_X_LPARAM(lpr);
							window->leftAttr.y = GET_Y_LPARAM(lpr);

							window->leftAttr.move = true;
							//SetCapture(*window->hwnd);
						}
						break;
					case WM_LBUTTONUP: //514
						__action.type = MLQC_ACTION_MOUSE_UP_LEFT;
						window->onAction(__action);

						if (window->movable || window->leftAttr.move) {
							window->leftAttr.move = false;
							//ReleaseCapture();
						}

						if (window->clickable) {
							POINT tmp;
							GetCursorPos(&tmp);

							if (abs(window->leftAttr.point.x - tmp.x) < 2 && (window->leftAttr.point.y - tmp.y) < 2) {
								__action.type = MLQC_ACTION_MOUSE_CLICK_LEFT;
								window->onAction(__action);
							}
						}
						break;
					case WM_MOUSEMOVE: // 512
						__action.type = MLQC_ACTION_MOUSE_MOVE;
						window->onAction(__action);

						if (window->movable && window->leftAttr.move) {

							RECT windowPos;
							GetWindowRect(*window->hwnd, &windowPos);

							RECT displayRect;
							GetWindowRect(GetDesktopWindow(), &displayRect);



							MoveWindow(
								*window->hwnd,
								window->x = min(max(windowPos.left + (GET_X_LPARAM(lpr) - window->leftAttr.x), 0), displayRect.right - window->w),
								window->y = min(max(windowPos.top + (GET_Y_LPARAM(lpr) - window->leftAttr.y), 0), displayRect.bottom - window->h),
								window->w,
								window->h,
								TRUE);
						}
						break;
					case WM_RBUTTONDOWN: //516
						__action.type = MLQC_ACTION_MOUSE_DOWN_RIGHT;
						window->onAction(__action);

						GetCursorPos(&window->rightAttr.point);
						break;
					case WM_RBUTTONUP: //517
						__action.type = MLQC_ACTION_MOUSE_UP_RIGHT;
						window->onAction(__action);

						if (window->clickable) {
							POINT tmp;
							GetCursorPos(&tmp);
							if (abs(window->rightAttr.point.x - tmp.x) < 2 && (window->rightAttr.point.y - tmp.y) < 2) {
								__action.type = MLQC_ACTION_MOUSE_CLICK_RIGHT;
								window->onAction(__action);
							}
						}

						break;
					case WM_DESTROY: //2
						Application::getInstance()->removeWindow(window);
						break;
					case WM_GETMINMAXINFO: //36
						return TRUE;
				}
		}
		return DefWindowProc(hwnd, msg, wpr, lpr);
	}

	HICON Application::loadIcon(int id) {
		return LoadIcon(*this->instance, MAKEINTRESOURCE(id));
	}

	HICON Application::loadSystemIcon(int id) {
		return LoadIcon(NULL, MAKEINTRESOURCE(id));
	}

	Window* Application::createWindow(std::string name, int x, int y, int w, int h) {
		WNDCLASSEX* winClass = NULL;
		COLORREF alpha = RGB(0, 0, 0);
		if (name == "main") {
			winClass = new WNDCLASSEX();
			winClass->cbSize = sizeof(*winClass);
			winClass->style = 0;
			winClass->lpfnWndProc = Application::onAction;
			winClass->lpszMenuName = NULL;
			winClass->lpszClassName = name.c_str();
			winClass->cbWndExtra = NULL;
			winClass->cbClsExtra = NULL;
			auto icon = loadIcon(IDI_ICON1);
			winClass->hIcon = icon;
			winClass->hIconSm = icon;
			winClass->hCursor = LoadCursor(NULL, IDC_ARROW);
			winClass->hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
			winClass->hInstance = *this->instance;
			alpha = RGB(0, 0, 255);
		}
		
		Window* result = NULL;

		try {
			result = new Window(this, name, winClass, alpha);
		}
		catch (const RegisterWindowClassException&) {
			return NULL;
		}

		if (winClass != NULL)
			delete winClass;

		if (result != NULL) {
			result->setSize(x, y, w, h);
			ViewGroup* root = new ViewGroup(0, 0, w, h);

			if (name == "main") {
				ImageView* bkgr = new ImageView(0, 0, w, h);
				bkgr->setImageId(IDB_BITMAP1);
				
				ImageView* loginView = new ImageView(32, 235, 80, 80);
				loginView->setImageId(IDB_BITMAP2);

				ImageView* passwordView = new ImageView(32, 320, 140, 80);
				passwordView->setImageId(IDB_BITMAP3);

				TextView* loginText = new TextView(32, 300, 256, 40);
				
				TextView* passwordText = new TextView(32, 380, 256, 40);

				root->addChild(bkgr);
				root->addChild(loginView);
				root->addChild(passwordView);
				root->addChild(loginText);
				root->addChild(passwordText);
			}


			result->setContentView(root);
			windows.push_back(result);
		}

		return result;
	}

	std::vector<Window*> Application::getWindows() {
		return windows;
	}

	Window * Application::getWindow(HWND hwnd) {
		if (hwnd != NULL) {
			for (Window* window : windows) {
				HWND* tmp = window->getHWND();
				if (tmp != NULL && (*tmp) == hwnd)
					return window;
					
			}
		}
		return NULL;
	}

	void Application::removeWindow(Window* window) {
		auto iterator = windows.begin();

		while (iterator < windows.end() && (((*iterator) == NULL) ||  (*iterator)->getId() != window->getId()))
			iterator++;

		if (iterator != windows.end())
			windows.erase(iterator);
	}

	Application::~Application() {
		for (Window* window : windows) {
			if (window != NULL) {
				window->onDestroy();
				delete window;
			}
		}
	}
}