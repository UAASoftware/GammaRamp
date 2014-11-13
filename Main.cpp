/*

The MIT License(MIT)

Copyright(c) 2014 Xi (Ma) Chen <hypernewbie@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <windows.h>
#include <cstdio>
#include "GammaRamp.h"
#include "resource.h"

#define DEFAULT_BRIGHTNESS 128
#define HELP_TEXT \
	"GammaRamp is active!\n"\
	"Keys:\n" \
	"    Increase brightness = Left Ctrl + Left Shift + Numpad Add\n" \
	"    Decrease brightness = Left Ctrl + Left Shift + Numpad Subtract\n" \
	"    Reset brightness = Left Ctrl + Left Shift + Numpad Multiply\n" \
	"    Exit = Left Ctrl + Left Shift + Numpad Divide\n"

int screenBrightness = DEFAULT_BRIGHTNESS;
bool ext = false;

void capBrightness() {
	if (screenBrightness < 0) screenBrightness = 0;
	if (screenBrightness > 255) screenBrightness = 255;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int cmdShow) {
	CGammaRamp gammaRamp;
	MessageBox(NULL, HELP_TEXT, "GammaRamp Help", MB_OK);

	while (!ext) {
		gammaRamp.SetBrightness(NULL, screenBrightness);
		if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(VK_LSHIFT)) {
			if (GetAsyncKeyState(VK_ADD)) {
				screenBrightness += 16;
				capBrightness();
				gammaRamp.SetBrightness(NULL, screenBrightness);
			}
			if (GetAsyncKeyState(VK_SUBTRACT)) {
				screenBrightness -= 16;
				capBrightness();
				gammaRamp.SetBrightness(NULL, screenBrightness);
			}
			if (GetAsyncKeyState(VK_MULTIPLY)) {
				screenBrightness = DEFAULT_BRIGHTNESS;
				capBrightness();
				gammaRamp.SetBrightness(NULL, screenBrightness);
			}
			if (GetAsyncKeyState(VK_DIVIDE)) {
				ext = true;
				break;
			}
		}
		Sleep(400);
	}

	gammaRamp.SetBrightness(NULL, DEFAULT_BRIGHTNESS);
	MessageBox(NULL, "GammaRamp has stopped.\nThanks for using!", "GammaRamp", MB_OK);
	return 0;
}