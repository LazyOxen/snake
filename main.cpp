#include "game.h"

int main() 
{
	Game::create(300, 300);
	MSG msg;

	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else if (Game::instance->done_playing()) {
			break;
		} else if (Game::instance->time_to_update()) {
				Game::instance->update();
		}
	}

	return (int) msg.wParam;
}
