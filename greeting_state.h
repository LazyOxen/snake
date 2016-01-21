#ifndef GREETING_STATE_H
#define GREETING_STATE_H
#include <windows.h>
#include <string.h>
#include <memory>
#include "state.h"
#include "playing_state.h"
class GreetingState : public State {
	public:
		GreetingState(int width, int height);
		virtual void draw(HDC& hdc);
		virtual std::unique_ptr<State> update();
		virtual bool quit();
	private:
		void handle_input();
		bool _quit_chosen;
		bool _complete;
};

#endif
