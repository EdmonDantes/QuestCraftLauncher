#include "ViewGroup.h"
#include "Window.h"

namespace MLQC {

	void copyStr(char** ptr, std::string str) {
		*ptr = new char[str.length() + 1];
		for (int i = 0; i < str.length(); i++)
			ptr[0][i] = str[i];
		ptr[0][str.length()] = 0;
	}

	void copyStr(char** ptr, LPCSTR str) {
		int len = strlen(str);
		*ptr = new char[len + 1];
		for (int i = 0; i < len; i++)
			ptr[0][i] = str[i];
		ptr[0][len] = 0;
	}

	void copyStr(char** ptr, char* str) {
		if (str != NULL) {
			int len = strlen(str);
			*ptr = new char[len + 1];
			for (int i = 0; i < len; i++)
				ptr[0][i] = str[i];
			ptr[0][len] = 0;
		}
		else
			*ptr = new char[0];
	}

	unsigned int Window::nextId = 0;

	Window::Window(Application* app, std::string title, WNDCLASSEX* wndClass, COLORREF alpha) {
		this->id = Window::nextId++;

		if (!RegisterClassEx(wndClass))
			throw RegisterWindowClassException();

		copyStr(&this->className, wndClass->lpszClassName);
		copyStr(&this->title, title);
		this->app = app;
		this->inst = wndClass->hInstance;
		this->alpha = alpha;
		this->showed = false;
		this->movable = true;
		this->clickable = true;
		this->minimizable = false;
	}

	Window::Window(const Window& w) {
		this->app = w.app;
		this->inst = w.inst;
		this->parent = w.parent;
		this->hwnd = w.hwnd;
		this->alpha = w.alpha;
		this->id = w.id;
		this->x = w.x;
		this->y = w.y;
		this->w = w.w;
		this->h = w.h;
		this->root = new ViewGroup(*w.root);
		this->needUpdate = true;
		this->showed = w.showed;
		this->movable = w.movable;
		this->clickable = w.clickable;
		this->minimizable = w.minimizable;
		this->leftAttr = w.leftAttr;
		this->rightAttr = w.rightAttr;

		copyStr(&this->className, w.className);
		copyStr(&this->title, w.title);
	}

	void Window::onCreate(){
		HWND result = CreateWindowEx(WS_EX_LAYERED, className, title, WS_SYSMENU | WS_POPUP, x, y, w, h, HWND(this->parent != NULL ? *this->parent->hwnd : NULL), NULL, inst, NULL);
		this->hwnd = new HWND(result);

		if (!(*this->hwnd))
			throw CreateWindowException();
	}

	void Window::onStart() {
		if (root != NULL)
			root->onStart(this);
		this->needUpdate = true;
	}

	void Window::paint() {
		if (needUpdate) {

			PAINTSTRUCT ps;
			HDC globalDC = BeginPaint(*this->hwnd, &ps);

			HDC bufferDC = CreateCompatibleDC(globalDC);
			HBITMAP bufferBitmap = CreateCompatibleBitmap(globalDC, w, h);
			SelectObject(bufferDC, bufferBitmap);

			RECT rect;
			rect.left = rect.top = 0;
			rect.right = w;
			rect.bottom = h;

			FillRect(bufferDC, &rect, CreateSolidBrush(RGB(255, 255, 255)));

			this->onPrePaint(&bufferDC);

			BitBlt(globalDC, 0, 0, w, h, bufferDC, 0, 0, SRCCOPY);

			DeleteBitmap(bufferBitmap);
			DeleteDC(bufferDC);
			DeleteDC(globalDC);
			EndPaint(*this->hwnd, &ps);
		}
	}

	void Window::onPrePaint(HDC* hdc) {
		Gdiplus::Graphics* g = Gdiplus::Graphics::FromHDC(*hdc);

		if (root != NULL && root->visible)
			root->onPrePaint(hdc);

		this->onPaint(g);

		delete g;
	}

	void Window::onPaint(Gdiplus::Graphics* g) {
		if (root != NULL && root->visible)
			root->onPaint(g);
	}

	void Window::onDestroy() {
		if (this->root) {
			this->root->onDestroy(this);
		}
	}

	void Window::onAction(MLQCAction action) {
		if (this->root != NULL) {
			this->root->onAction(action);
		}
	}

	void Window::setTitle(std::string title) {
		copyStr(&this->title, title);
		if (this->showed)
			SetWindowTextA(*this->hwnd, title.c_str());
	}

	void Window::setTitle(char* title) {
		this->title = title;
		if (this->showed)
			SetWindowTextA(*this->hwnd, title);
	}

	void Window::setX(int x) {
		this->x = x;
		if (this->showed)
			resize();
	}

	void Window::setY(int y) {
		this->y = y;
		if (this->showed)
			resize();
	}

	void Window::setWidth(int w) {
		this->w = w;
		if (this->showed)
			resize();
	}

	void Window::setHeight(int h) {
		this->h = h;
		if (this->showed)
			resize();
	}

	void Window::setSize(RECT rect) {
		this->x = rect.left;
		this->y = rect.top;
		this->w = rect.right - rect.left;
		this->h = rect.bottom - rect.top;
		if (this->showed)
			resize();
	}

	void Window::setSize(int w, int h) {
		this->w = w;
		this->h = h;
		if (this->showed)
			resize();
	}

	void Window::setSize(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		if (this->showed)
			resize();
	}

	void Window::setContentView(ViewGroup* root) {
		if (this->root) {
			this->root->onDestroy(this);
		}
		delete this->root;
		this->root = root;
		this->root->setWindow(this);
		this->root->onCreate(this);
	}

	void Window::setParent(Window* parent) {
		this->parent = parent;
	}

	void Window::setMovable(bool movable) {
		this->movable = movable;
	}

	void Window::setClickable(bool clickable) {
		this->clickable = clickable;
	}

	std::string Window::getTitle()  const {
		return title;
	}

	int Window::getId() const {
		return id;
	}

	int Window::getX() const {
		return x;
	}

	int Window::getY() const {
		return y;
	}

	int Window::getWidth() const {
		return w;
	}

	int Window::getHeight() const {
		return h;
	}

	RECT Window::getSize() const {
		RECT tmp;
		tmp.left = x;
		tmp.top = y;
		tmp.right = x + w;
		tmp.bottom = y + h;
		return RECT();
	}

	ViewGroup* Window::getContentView() const {
		return root;
	}

	HWND* Window::getHWND() const {
		return hwnd;
	}

	Window* Window::getParent() const {
		return parent;
	}

	bool Window::isMovable() const {
		return movable;
	}

	bool Window::isClickable() const {
		return clickable;
	}

	bool Window::isShowed() const {
		return showed;
	}

	bool Window::isMinimizate() const {
		return minimizable;
	}

	void Window::show() {
		if (!showed) {
			onStart();
			ShowWindow(*this->hwnd, SW_SHOWNORMAL);
			SetLayeredWindowAttributes(*this->hwnd, this->alpha, 0, LWA_COLORKEY);
			//UpdateWindow(*this->hwnd);
			showed = true;
		}
	}

	void Window::update() {
		this->needUpdate = true;
		InvalidateRect(*this->hwnd, NULL, FALSE);
	}

	void Window::minimazate() {
		if (showed && !minimizable) {
			ShowWindowAsync(*this->hwnd, SW_MINIMIZE);
			minimizable = true;
		}
	}

	void Window::maximizate() {
		if (showed && minimizable) {
			ShowWindowAsync(*this->hwnd, SW_SHOW);
			minimizable = false;
		}
	}


	void Window::resize() {
		RECT displayRect;
		GetWindowRect(GetDesktopWindow(), &displayRect);
		MoveWindow(*this->hwnd, min(max(x, 0), displayRect.right - w), min(max(y, 0), displayRect.bottom - h), w, h, TRUE);
	}

	bool Window::isNeedUpdate() {
		return this->needUpdate;
	}

	Window::~Window() {
		if (hwnd != NULL)
			delete hwnd;

		if (this->root != NULL)
			delete this->root;

		if (this->className != NULL)
			delete this->className;

		if (this->title != NULL)
			delete this->title;
	}
}