#pragma once
#include "stdafx.h"

namespace MLQC {
	class View;
	class ViewGroup;
	class Window;

	class Application {
	private:
		static Application* INSTANCE;
		HINSTANCE* instance;
		std::vector<Window*> windows;

		Application(HINSTANCE*);
	public:
		static void init(HINSTANCE*);
		static Application* getInstance();


		void onCreate();
		void onStart();
		void onStop();

		static LRESULT CALLBACK onAction(HWND, UINT, WPARAM, LPARAM);

		HICON loadIcon(int);
		HICON loadSystemIcon(int);
		virtual Window* createWindow(std::string, int, int, int, int);
		virtual std::vector<Window*> getWindows();
		virtual Window* getWindow(HWND);
		virtual void removeWindow(Window*);
		~Application();
	};
}