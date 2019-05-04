#include <Windows.h>
#include <iostream>
#include <WinUser.h>
#include <stdlib.h>
#include <stdio.h>
#include <windef.h>

/* Globals */
int ScreenX = 0;
int ScreenY = 0;
BYTE* ScreenData = 0;




void ScreenCap()
{
	HDC hScreen = GetDC(GetDesktopWindow());
	ScreenX = GetDeviceCaps(hScreen, HORZRES);
	ScreenY = GetDeviceCaps(hScreen, VERTRES);

	HDC hdcMem = CreateCompatibleDC(hScreen);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, ScreenX, ScreenY);
	HGDIOBJ hOld = SelectObject(hdcMem, hBitmap);
	BitBlt(hdcMem, 0, 0, ScreenX, ScreenY, hScreen, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hOld);

	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biWidth = ScreenX;
	bmi.biHeight = -ScreenY;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;// 3 * ScreenX * ScreenY;

	if (ScreenData)
		free(ScreenData);
	ScreenData = (BYTE*)malloc(4 * ScreenX * ScreenY);

	GetDIBits(hdcMem, hBitmap, 0, ScreenY, ScreenData, (BITMAPINFO*)& bmi, DIB_RGB_COLORS);

	ReleaseDC(GetDesktopWindow(), hScreen);
	DeleteDC(hdcMem);
	DeleteObject(hBitmap);
}

inline int PosB(int x, int y)
{
	return ScreenData[4 * ((y * ScreenX) + x)];
}

inline int PosG(int x, int y)
{
	return ScreenData[4 * ((y * ScreenX) + x) + 1];
}

inline int PosR(int x, int y)
{
	return ScreenData[4 * ((y * ScreenX) + x) + 2];
}


bool ButtonPress(int Key)
{
	bool button_pressed = false;

	while (GetAsyncKeyState(Key))
		button_pressed = true;

	return button_pressed;
}

int main()
{
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	while (true) {
		if (ButtonPress(VK_SPACE)) {
			while (true)
			{
				POINT p;
				ScreenCap();
				p.x = 875;
				p.y = 745;
				int r = PosR(p.x, p.y);
				int g = PosG(p.x, p.y);
				int b = PosB(p.x, p.y);
				std::cout << "Bitmap: r: " << PosR(p.x, p.y) << " g: " << PosG(p.x, p.y) << " b: " << PosB(p.x, p.y) << "\n";
				if (r == 74 && g == 0 && b == 138) {
					// Press the "2" key
					ip.ki.wVk = 0x32; // virtual-key code for the "2" key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));

					// Release the "2" key
					ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					SendInput(1, &ip, sizeof(INPUT));
				}
				else if (r == 25 && g == 65 && b == 30) {
					// Press the "1" key
					ip.ki.wVk = 0x31; // virtual-key code for the "1" key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));

					// Release the "1" key
					ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					SendInput(1, &ip, sizeof(INPUT));
				}
				else if (r == 47 && g == 4 && b == 8) {
					// Press the "4" key
					ip.ki.wVk = 0x34; // virtual-key code for the "4" key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));

					// Release the "4" key
					ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					SendInput(1, &ip, sizeof(INPUT));
				}
				else if (r == 254 && g == 253 && b == 179) {
					// Press the "3" key
					ip.ki.wVk = 0x33; // virtual-key code for the "3" key
					ip.ki.dwFlags = 0; // 0 for key press
					SendInput(1, &ip, sizeof(INPUT));

					// Release the "3" key
					ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
					SendInput(1, &ip, sizeof(INPUT));
				}

				if (ButtonPress(VK_ESCAPE))
				{
					printf("Quit\n");
					break;
				}
			}

		}
	}




	/*
	while (true)
	{

		if (ButtonPress(VK_SPACE))
		{

			// Print out current cursor position
			POINT p;
			GetCursorPos(&p);
			printf("X:%d Y:%d \n", p.x, p.y);
			// Print out RGB value at that position
			std::cout << "Bitmap: r: " << PosR(p.x, p.y) << " g: " << PosG(p.x, p.y) << " b: " << PosB(p.x, p.y) << "\n";

		}
		else if (ButtonPress(VK_ESCAPE))
		{
			printf("Quit\n");
			break;
		}
		else if (ButtonPress(VK_SHIFT))
		{
			ScreenCap();
			printf("Captured\n");
		}
	}
	*/

	system("PAUSE");
	return 0;
}