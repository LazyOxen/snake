#ifndef STATE_H
#define STATE_H
#include <windows.h>
#include <memory>
#include "grafx_defs.h"

class State {
	public:
		State(int width, int height): _width(width), _height(height) {}
		virtual void draw(HDC& hdc) {}
		virtual std::unique_ptr<State> update() { return std::unique_ptr<State>(new State(_width, _height)); }
		virtual bool quit() { return true; }

	protected:
		int _width;
		int _height;
};

#endif
