#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H
#include <windows.h>
#include <time.h>
#include "state.h"
#include "snake.h"
#include "grafx_defs.h"
#include "you_dead_state.h"

class PlayingState : public State {
	public:
		PlayingState(int width, int height);
		virtual void draw(HDC& hdc);
		virtual std::unique_ptr<State> update();
		virtual bool quit();
	private:
		void handle_input();
		void position_food();
		bool is_in_bounds(Point p);
		Snake _snake;
		Point _food;
		bool _quit;
		bool _complete;
};

#endif
