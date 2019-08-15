#include "ViewGroup.h"

namespace MLQC {
	void ViewGroup::setFocus(bool) {
		this->focus = false;
	}

	void ViewGroup::setParent(ViewGroup* parent) {
		this->parent = parent;
	}

	void ViewGroup::setWindow(Window* window) {
		this->window = window;
		for (View* tmp : childs)
			tmp->setWindow(window);
	}

	ViewGroup::ViewGroup() : View() {}
	void ViewGroup::onCreate(Window* window) {
		for (View* view : childs)
			if (view != NULL)
				view->onCreate(window);
	}

	void ViewGroup::onStart(Window* window) {
		for (View* view : childs)
			if (view != NULL)
				view->onStart(window);
	}

	void ViewGroup::onPrePaint(HDC* hdc) {
		for (View* view : childs)
			if (view->visible)
				view->onPrePaint(hdc);
	}

	void ViewGroup::onPaint(Gdiplus::Graphics* g) {
		for (View* view : childs)
			if (view->visible)
				view->onPaint(g);
	}

	void ViewGroup::onDestroy(Window* window) {
		for (View* view : childs) {
			if (view != nullptr && view != NULL)
				view->onDestroy(window);
		}
	}

	bool ViewGroup::onAction(MLQCAction e) {
		auto iterator = childs.end();
		bool _tmp = false;

		do {
			iterator--;
			if (*iterator != NULL) {
				if (e.type > 1) {
					View* tmp = *iterator;
					if (e.type == 5)
						tmp->focus = false;

					int _x = GET_X_LPARAM(e.lParam);
					int _y = GET_Y_LPARAM(e.lParam);

					if (_x >= tmp->getX() && _x <= tmp->getX() + tmp->getWidth() && _y >= tmp->getY() && _y <= tmp->getY() + tmp->getHeight()) {
						if (e.type == 5) {
							if (tmp->focusable) {
								tmp->setFocus(!_tmp);
								_tmp = true;
							}
							if (tmp->clickable)
								if (!tmp->onAction(e))
									break;
						}
						else if (!tmp->onAction(e))
							break;
					}
				}
				else if (!(*iterator)->onAction(e))
					break;
			}
			
		} while (iterator > childs.begin());
		return iterator == childs.begin();
	}

	void ViewGroup::addChild(View* view) {
		if (view != nullptr && view != NULL && view->parent == NULL && view->getX() >= this->x && view->getY() >= this->y && view->getX() + view->getWidth() <= this->x + this->w && view->getY() + view->getHeight() <= this->y + this->h) {
			view->setParent(this);
			view->setWindow(window);
			childs.push_back(view);
		}
	}
	
	std::vector<View*>::const_iterator ViewGroup::getChilds() const {
		return childs.begin();
	}

	void ViewGroup::removeChild(View* view) {
		auto iterator = childs.begin();
		while (iterator != childs.end() && (((*iterator) == NULL && (*iterator) == nullptr)) || (*iterator)->getId() != view->getId())
			iterator++;
		if (iterator != childs.end()) {
			(*iterator)->onDestroy(window);
			delete (*iterator);
			childs.erase(iterator);
		}
	}

	void ViewGroup::removeAllChilds() {
		for (View* view : childs) {
			if (view != NULL) {
				view->onDestroy(window);
				delete view;
			}
		}
		childs.clear();
	}

	ViewGroup::~ViewGroup() {
		removeAllChilds();
	}


}