#ifndef SNAKE_H
#define SNAKE_H

#include <windows.h>
#include <deque>
#include "grafx_defs.h"


class Snake {
	public:
		Snake(int x, int y);
		void eat();
		void draw(HDC &hdc);
		void update();
		void move(Direction d);
		bool is_in_body(Point p);
		Point head();
	private:
		std::deque<Point> _body;
		bool _grow;
		Direction _direction;
};

#endif
