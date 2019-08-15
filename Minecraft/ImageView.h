#pragma once
#include "View.h"
#pragma comment(lib, "Msimg32.lib")

using namespace Gdiplus;

namespace MLQC {
	
	class ImageView : public View {
	protected:
		int resId;
		HBITMAP hbit;
		BITMAP bit;
		bool loaded = false;

		void loading();

		using View::setFocus;
		using View::setParent;
		using View::setWindow;
	public:
		ImageView();
		using View::View;
		virtual void onCreate(Window*);
		using View::onStart;
		virtual void onPrePaint(HDC*);
		using View::onPaint;
		virtual void onDestroy(Window*);

		using View::onAction;

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

		void setImageId(int);
		int getImageId();
		HBITMAP getImage();
		BITMAP getImageRect();

		~ImageView();
	};

}