#include "ViewGroup.h"
namespace MLQC {

	unsigned int View::nextId = 0;

	void View::setFocus(bool focus) {
		this->focus = focus;
	}

	void View::setParent(ViewGroup* parent) {
		this->parent = parent;
	}

	void View::setWindow(Window* window) {
		this->window = window;
	}

	View::View() {
		this->id = View::nextId++;
		this->visible = true;
		this->clickable = true;
		this->focusable = true;
		this->focus = false;
	}

	View::View(int x, int y, int w, int h) : View() {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}

	View::View(RECT rect) : View(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top) {}

	void View::onCreate(Window*) {}
	void View::onStart(Window *) {}
	void View::onPrePaint(HDC *) {}
	void View::onPaint(Gdiplus::Graphics *) {}
	void View::onDestroy(Window *) {}

	bool View::onAction(MLQCAction) {
		return true;
	}

	void View::setX(int x) {
		this->x = x;
		if (window != NULL && visible)
			window->update();
	}

	void View::setY(int y) {
		this->y = y;
		if (window != NULL && visible)
			window->update();
	}

	void View::setWidth(int w) {
		this->w = w;
		if (window != NULL && visible)
			window->update();
	}

	void View::setHeight(int h) {
		this->h = h;
		if (window != NULL && visible)
			window->update();
	}

	void View::setSize(int w, int h) {
		this->w = w;
		this->h = h;
		if (window != NULL && visible)
			window->update();
	}

	void View::setSize(int x, int y, int w, int h) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		if (window != NULL && visible)
			window->update();
	}

	void View::setSize(RECT rect) {
		View::setSize(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	}

	void View::setClickable(bool clickable) {
		this->clickable = clickable;
	}

	void View::setVisible(bool visible) {
		this->visible = visible;
		if (window != NULL && visible)
			window->update();
	}

	void View::setFocusable(bool focusable) {
		if (!(this->focusable = focusable))
			this->focus = false;
	}



	int View::getId() const {
		return id;
	}

	int View::getX() const {
		return x;
	}

	int View::getY() const {
		return y;
	}

	int View::getWidth() const {
		return w;
	}

	int View::getHeight() const {
		return h;
	}

	ViewGroup* View::getParent() const {
		return parent;
	}

	bool View::isFocus() const {
		return focus;
	}

	bool View::isClickable(bool) {
		return clickable;
	}

	bool View::isVisible(bool) {
		return visible;
	}

	bool View::isFocusable(bool) {
		return focusable;
	}

	View::~View() {}


}