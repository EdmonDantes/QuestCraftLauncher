#include "TextView.h"
#include "Window.h"

namespace MLQC {

	bool TextView::onAction(MLQCAction e) {
		switch (e.type) {
			case MLQC_ACTION_KEY_DOWN:
				if (focus) {
					switch (e.wParam) {
					case VK_HOME:case VK_END:case VK_PRIOR:
					case VK_NEXT:case VK_UP:case VK_DOWN:
					case VK_SHIFT:case VK_CONTROL:
					case VK_CAPITAL:case VK_MENU:case VK_TAB:
					case VK_RETURN: case VK_SPACE:
						break;

					case VK_LEFT:
						cursor = max(cursor - 1, 0);
						if (window != NULL)
							this->window->update();
						break;
					case VK_RIGHT:
						cursor = min(cursor + 1, text.length());
						if (window != NULL)
							this->window->update();
						break;
					case VK_BACK:
						if (cursor > 0) {
							text.erase(--cursor, 1);
							if (window != NULL)
								this->window->update();
						}
						break;
					case VK_DELETE:
						if (cursor < text.length()) {
							text.erase(cursor, 1);
							if (window != NULL)
								this->window->update();
						}
						break;
					default:
						BYTE keyboardState[256];
						GetKeyboardState(keyboardState);

						WORD ascii = 0;
						const int len = ToAscii(e.wParam, (e.lParam >> 16) & 0x00ff, keyboardState, &ascii, 0);
						if (len == 1) {
							this->text.insert(cursor++, 1, ((wchar_t)ascii));
							if (window != NULL)
								this->window->update();
						}
						break;
					}
					break;
				}
		}
		return true;
	}

	using namespace Gdiplus;

	void TextView::setFocus(bool focus) {
		if (this->focus = focus && window != NULL)
			window->update();
	}

	TextView::TextView() : View() {}

	void TextView::onPaint(Gdiplus::Graphics* g) {
		Pen border(Color(0x88000000), REAL(4));
		border.SetAlignment(PenAlignmentInset);
		g->DrawRectangle(&border, x, y, w, h);

		SolidBrush textArea(Color(0xCA000000));
		g->FillRectangle(&textArea, x + 4, y + 4, w - 8, h - 8);

		cursor = min(max(cursor, 0), text.length());

		int textSize = h / 2 + h / 4;
		FontFamily textFamily(L"Times New Roman");
		Font textFont(&textFamily, textSize, FontStyleRegular, UnitPixel);
		SolidBrush textColor(Color(0xffffffff));
		PointF leftUp(x + 4, y + 1);

		RectF textBorder = RectF(x + 4, y + 1, 0, 0);
		LPCWSTR _text = text.c_str();

		if (focus) {
			LPCWSTR left = max(_text + (cursor - 1), _text);
			LPCWSTR right = _text + cursor;
			int padding = 14;

			while ((*right) != 0) {
				g->MeasureString(left, right - left, &textFont, leftUp, &textBorder);
				if (textBorder.Width < w - padding)
					right++;
				else
					break;
			}

			if (textBorder.Width >= w - padding)
				right--;

			g->MeasureString(left, right - left, &textFont, leftUp, &textBorder);

			while (left != _text) {
				g->MeasureString(left, right - left, &textFont, leftUp, &textBorder);
				if (textBorder.Width < w - padding)
					left--;
				else break;
			}

			if (textBorder.Width >= w - padding)
				if (left + 1 < _text + cursor)
					left++;
				else
					right--;

			if (showCaret) {
				g->DrawString(left, _text + cursor - left, &textFont, leftUp, &textColor);
				g->MeasureString(left, _text + cursor - left, &textFont, leftUp, &textBorder);

				Pen caretPen(Color(0xffffffff), REAL(1));
				Point tmp = Point(x + max(textBorder.Width - 4, 4), y + 5);
				g->DrawLine(&caretPen, tmp, Point(tmp.X + 8, tmp.Y));
				g->DrawLine(&caretPen, Point(tmp.X + 4, tmp.Y), Point(tmp.X + 4, tmp.Y + h - 12));
				g->DrawLine(&caretPen, Point(tmp.X, tmp.Y + h - 12), Point(tmp.X + 8, tmp.Y + h - 12));

				if ((*(_text + cursor)) != 0)
					g->DrawString(_text + cursor, right - (_text + cursor), &textFont, PointF(x + max(textBorder.Width - 2, 4), y + 1), &textColor);
			}
			else {
				g->DrawString(left, right - left, &textFont, leftUp, &textColor);
			}
		} else {
			do {
				g->MeasureString(_text, -1, &textFont, leftUp, &textBorder);
				if (textBorder.Width > w - 4)
					_text++;
				else
					break;
			} while ((*_text) != 0);
			g->DrawString(_text, -1, &textFont, leftUp, &textColor);
		}
	}

	std::wstring TextView::getText() {
		return text;
	}

	TextView::~TextView() {}

}
