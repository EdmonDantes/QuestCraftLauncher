#include "ImageView.h"

namespace MLQC {
	void ImageView::loading() {
		if (!this->loaded) {
			hbit = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(this->resId), IMAGE_BITMAP, 0, 0, 0);
			GetObject(hbit, sizeof(BITMAP), &bit);
			this->loaded = true;
		}
	}

	ImageView::ImageView() : View() {}
	

	void ImageView::onCreate(Window*) {
		loading();
	}

	void ImageView::onPrePaint(HDC* hdc) {
		loading();

		HDC imageDC = CreateCompatibleDC(*hdc);
		HANDLE deselectedImageObject = SelectObject(imageDC, hbit);

		if (w < 0 && h < 0)
			BitBlt(*hdc, x, y, bit.bmWidth, bit.bmHeight, imageDC, 0, 0, SRCCOPY);
		else
			TransparentBlt(*hdc, x, y, w, h, imageDC, 0, 0, bit.bmWidth, bit.bmHeight, RGB(255, 255, 255));

		DeleteObject(deselectedImageObject);
		DeleteDC(imageDC);
	}

	void ImageView::onDestroy(Window*) {
		if (this->loaded) {
			DeleteObject(hbit);
			this->loaded = false;
		}
	}

	void ImageView::setImageId(int resId) {
		if (this->loaded)
			DeleteObject(hbit);

		this->loaded = false;
		this->resId = resId;
	}

	int ImageView::getImageId() {
		return this->resId;
	}

	HBITMAP ImageView::getImage() {
		return hbit;
	}

	BITMAP ImageView::getImageRect() {
		return bit;
	}

	ImageView::~ImageView() {
		if (this->loaded) {
			DeleteObject(hbit);
			this->loaded = false;
		}
	}


}