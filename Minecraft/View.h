#pragma once
#include "stdafx.h"
#include "MLQCAction.h"
#include "Window.h"


namespace MLQC {
	class View {
		friend ViewGroup;
	protected:
		static unsigned int nextId;

		int id;
		Window* window;
		ViewGroup* parent;
		int x, y, w, h;
		bool focus, visible, clickable, focusable;

		virtual void setFocus(bool);
		virtual void setParent(ViewGroup*);
		virtual void setWindow(Window*);
	public:
		View();
		View(int, int, int, int);
		View(RECT);

		virtual void onCreate(Window*);
		virtual void onStart(Window*);
		virtual void onPrePaint(HDC*);
		virtual void onPaint(Gdiplus::Graphics*);
		virtual void onDestroy(Window*);

		virtual bool onAction(MLQCAction);

		virtual void setX(int);
		virtual void setY(int);
		virtual void setWidth(int);
		virtual void setHeight(int);
		virtual void setSize(int, int);
		virtual void setSize(int, int, int, int);
		virtual void setSize(RECT);
		virtual void setClickable(bool);
		virtual void setVisible(bool);
		virtual void setFocusable(bool);

		virtual int getId() const;
		virtual int getX() const;
		virtual int getY() const;
		virtual int getWidth() const;
		virtual int getHeight() const;
		virtual ViewGroup* getParent() const;
		virtual bool isFocus() const;
		virtual bool isClickable(bool);
		virtual bool isVisible(bool);
		virtual bool isFocusable(bool);

		~View();
	};
}

