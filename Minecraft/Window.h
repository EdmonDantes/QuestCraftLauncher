#pragma once
#include "stdafx.h"
#include "Application.h"
#include "MLQCAction.h";

namespace MLQC {

	struct MovableAttributes {
		int x, y;
		POINT point;
		bool move = false;
	};

	struct RegisterWindowClassException : public std::exception {
		const char* what() const throw() {
			return "Register window class exception";
		}
	};

	struct CreateWindowException : public std::exception {
		const char* what() const throw() {
			return "Create window exception";
		}
	};

	class Window {
		friend Application;
	private:
		static unsigned int nextId;
		Application* app;
		Window* parent;
		HWND* hwnd;
		COLORREF alpha;

		int id, x, y, w, h;
		char* title;
		char* className;
		HINSTANCE inst;

		ViewGroup* root;
		bool needUpdate;

		bool showed;
		bool movable;
		bool clickable;
		bool minimizable;

		MovableAttributes leftAttr;
		MovableAttributes rightAttr;
	public:
		Window(Application*, std::string, WNDCLASSEX*, COLORREF) throw(RegisterWindowClassException);
		Window(const Window&);
		virtual void onCreate() throw(CreateWindowException);
		virtual void onStart();
		virtual void paint();
		virtual void onPrePaint(HDC*);
		virtual void onPaint(Gdiplus::Graphics*);
		virtual void onDestroy();

		virtual void onAction(MLQCAction);

		void setTitle(std::string);
		void setTitle(char*);
		void setX(int);
		void setY(int);
		void setWidth(int);
		void setHeight(int);
		void setSize(RECT);
		void setSize(int, int);
		void setSize(int, int, int, int);
		void setContentView(ViewGroup*);
		void setParent(Window*);
		void setMovable(bool);
		void setClickable(bool);

		std::string getTitle() const;
		int getId() const;
		int getX() const;
		int getY() const;
		int getWidth() const;
		int getHeight() const;
		RECT getSize() const;
		ViewGroup* getContentView() const;
		HWND* getHWND() const;
		Window* getParent() const;
		bool isMovable() const;
		bool isClickable() const;
		bool isShowed() const;
		bool isMinimizate() const;

		


		virtual void show();
		virtual void update();
		virtual void minimazate();
		virtual void maximizate();
		virtual void resize();
		virtual bool isNeedUpdate();

		~Window();
	};
}

