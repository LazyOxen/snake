#ifndef GAME_H
#define GAME_H
#include <windows.h>
#include <memory>
#include "snake.h"
#include "greeting_state.h"
#include "playing_state.h"
#include "grafx_defs.h"

#define FRAME_DELAY 50
class Game {
	public:
		static std::unique_ptr<Game> instance;
		static void create(unsigned int width, unsigned int height);
		bool done_playing();
		bool time_to_update();
		void update();
	private:
		Game(unsigned int width, unsigned int height);
		void initialize_timestamp();
		void redraw();
		void set_active();
		void set_inactive();
		std::unique_ptr<State> _state;
		bool _active;
		int _width;
		int _height;
		DWORD _timestamp;
		// TODO: fix this
		ULONGLONG _next_update_time;
		HINSTANCE _hInstance;
		HWND _hwnd;
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

};

#endif
