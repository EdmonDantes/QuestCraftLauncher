#pragma once
#include "stdafx.h"

namespace MLQC {

	#define MLQC_ACTION_KEY_DOWN 0
	#define MLQC_ACTION_KEY_UP 1
	#define MLQC_ACTION_MOUSE_DOWN_LEFT 2
	#define MLQC_ACTION_MOUSE_UP_LEFT 3
	#define MLQC_ACTION_MOUSE_MOVE 4
	#define MLQC_ACTION_MOUSE_CLICK_LEFT 5
	#define MLQC_ACTION_MOUSE_CLICK_RIGHT 6
	#define MLQC_ACTION_MOUSE_DOWN_RIGHT 7
	#define MLQC_ACTION_MOUSE_UP_RIGHT 7

	struct MLQCAction {
		int type;
		WPARAM wParam;
		LPARAM lParam;
	};

	typedef bool(*onActionEvent)(MLQCAction);
}