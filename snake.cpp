#include "snake.h"

Snake::Snake(int x, int y) :
	_grow(false),
	_direction(Direction::Up)
{
	Point start { x, y };
	_body.push_back(start);

	for (int i = 0; i < 3; i++) {
		_body.push_back(Point {start.x + (i+1)*BLOCK_WIDTH, start.y} );
	}
	_grow = false;
}

void Snake::eat()
{
	_grow = true;
}

void Snake::update() 
{
	Point new_head;
	auto current_head = _body[0];
	switch(_direction) {
		case Direction::Down:
			new_head.x = current_head.x;
			new_head.y = current_head.y + BLOCK_WIDTH;
			break;
		case Direction::Up:
			new_head.x = current_head.x;
			new_head.y = current_head.y - BLOCK_WIDTH;
			break;
		case Direction::Right:
			new_head.x = current_head.x + BLOCK_WIDTH;
			new_head.y = current_head.y;
			break;
		case Direction::Left:
			new_head.x = current_head.x - BLOCK_WIDTH;
			new_head.y = current_head.y;
			break;
	}
	_body.push_front(new_head);

	if (_grow) {
		_grow = false;
	} else {
		// remove the tail
		_body.pop_back();
	}
}

void Snake::move(Direction d)
{
	// prevent movement in opposite direction
	switch (d) {
		case Direction::Down:
			_direction = _direction == Direction::Up ? _direction : d;
			break;
		case Direction::Up:
			_direction = _direction == Direction::Down ? _direction : d;
			break;
		case Direction::Left:
			_direction = _direction == Direction::Right ? _direction : d;
			break;
		case Direction::Right:
			_direction = _direction == Direction::Left ? _direction : d;
			break;
	}
}
bool Snake::is_in_body(Point p)
{
	auto len = _body.size();
	for (int i = 1; i < len; i++) {
		if (p == _body[i])
			return true;
	}
	return false;
}

void Snake::draw(HDC &hdc)
{
	for ( auto &p : _body) {
		Rectangle(hdc, p.x, p.y, p.x + BLOCK_WIDTH, p.y + BLOCK_WIDTH);
	}
}
Point Snake::head()
{
	return _body[0];
}
