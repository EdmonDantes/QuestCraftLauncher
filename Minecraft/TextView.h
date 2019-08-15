#pragma once
#include "View.h"

namespace MLQC {
	class TextView : public View
	{
	protected:
		std::wstring text;
		int cursor = 0;
		bool showCaret = true;

		virtual void setFocus(bool);
		using View::setParent;
		using View::setWindow;
	public:
		TextView();
		using View::View;
		using View::onCreate;
		using View::onStart;
		using View::onPrePaint;
		virtual void onPaint(Gdiplus::Graphics* g);
		using View::onDestroy;

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

		virtual std::wstring getText();

		~TextView();
	};
}