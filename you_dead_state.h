#ifndef YOU_DEAD_STATE_H
#define YOU_DEAD_STATE_H
#include <windows.h>
#include <memory>
#include "greeting_state.h"

class YouDeadState : public State {
	public:
		YouDeadState(int width, int height);
		virtual void draw(HDC& hdc);
		virtual std::unique_ptr<State> update();
		virtual bool quit();
	private:
		DWORD _quit_time;

};

#endif
