#ifndef GAME_H
#define GAME_H
#include <windows.h>
#include <memory>
#include <time.h>
#include "snake.h"
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
		void handle_input();
		void set_active();
		void set_inactive();
		void position_food();
		bool is_in_bounds(Point p);
		bool _quit;
		bool _active;
		Snake _snake;
		Point _food;
		int _width;
		int _height;
		DWORD _timestamp;
		ULONGLONG _next_update_time;
		HINSTANCE _hInstance;
		HWND _hwnd;
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

};

#endif
