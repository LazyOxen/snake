#ifndef GRAFX_DEFS_H
#define GRAFX_DEFS_H

#define BLOCK_WIDTH 10
struct Point {
	int x,y;
	bool operator==(Point o) { return this->x == o.x && this->y == o.y; }
};

enum Direction {
	Up,
	Down,
	Left,
	Right,
};

#endif
