#pragma once
#include "Window.h"
class View
{
private:
	Window* window;
	View* parent;
	float x, y, w, h;
public:
	View();
	View(float, float, float, float);
	View(Window, float, float, float, float);
	View(View, float, float, float, float);
	View(Window, View, float, float, float, float);
	void onCreate(Window);
	void paint(Window);
	void onDestroy(Window);
	float getX();
	float getY();
	float getWidth();
	float getHeight();
	~View();
};

