#pragma once
#include <vector>
#include "View.h"
namespace MLQC {
	class ViewGroup : public View {
	protected:
		std::vector<View*> childs = std::vector<View*>();

		friend Window;

		virtual void setFocus(bool);
		virtual void setParent(ViewGroup*);
		virtual void setWindow(Window*);
	public:
		ViewGroup();
		using View::View;

		virtual void onCreate(Window*);
		virtual void onStart(Window*);
		virtual void onPrePaint(HDC*);
		virtual void onPaint(Gdiplus::Graphics*);
		virtual void onDestroy(Window*);

		virtual bool onAction(MLQCAction);

		using View::setX;
		using View::setY;
		using View::setWidth;
		using View::setHeight;
		using View::setSize;
		using View::setClickable;
		using View::setVisible;
		using View::setFocusable;


		using View::getId;
		using View::getX;
		using View::getY;
		using View::getWidth;
		using View::getHeight;
		using View::getParent;
		using View::isFocus;
		using View::isClickable;
		using View::isVisible;
		using View::isFocusable;

		virtual void addChild(View*);
		virtual std::vector<View*>::const_iterator getChilds() const;
		virtual void removeChild(View*);
		virtual void removeAllChilds();
		
		~ViewGroup();
	};
}

