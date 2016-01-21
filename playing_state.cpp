#include "playing_state.h"

PlayingState::PlayingState(int width, int height) :
	State(width, height),
	_snake(width/2, height/2),
	_quit(false),
	_complete(false)
{
	_food.x = ((width*3u>>2) % BLOCK_WIDTH)*BLOCK_WIDTH;
	_food.y = ((height*3u>>2) % BLOCK_WIDTH)*BLOCK_WIDTH;
	srand( time(nullptr) );
}

void PlayingState::draw(HDC& hdc)
{
	_snake.draw(hdc);
	Rectangle(hdc, _food.x, _food.y, _food.x + BLOCK_WIDTH, _food.y + BLOCK_WIDTH);
}

std::unique_ptr<State> PlayingState::update()
{
	handle_input();
	_snake.update();

	if (_snake.head() == _food) {
		_snake.eat();
		position_food();
	} else if (_snake.is_in_body(_snake.head()) || !is_in_bounds(_snake.head())) {
		_complete = true;
	}

	if (_complete)
		return std::unique_ptr<YouDeadState>(new YouDeadState(State::_width, State::_height));

	return std::unique_ptr<PlayingState>(new PlayingState(*this));
}

void PlayingState::handle_input()
{
	if (GetAsyncKeyState(VK_UP) < 0)
		_snake.move(Direction::Up);
	else if (GetAsyncKeyState(VK_DOWN) < 0)
		_snake.move(Direction::Down);
	else if (GetAsyncKeyState(VK_LEFT) < 0)
		_snake.move(Direction::Left);
	else if (GetAsyncKeyState(VK_RIGHT) < 0)
		_snake.move(Direction::Right);
	else if (GetAsyncKeyState(VK_ESCAPE) < 0)
		_complete = true;
}

void PlayingState::position_food()
{
	while (_food == _snake.head() || _snake.is_in_body(_food)) {
		_food.x = (rand() % ((_width-BLOCK_WIDTH)/BLOCK_WIDTH))*BLOCK_WIDTH;
		_food.y = (rand() % ((_height-BLOCK_WIDTH)/BLOCK_WIDTH))*BLOCK_WIDTH;
	}
}

bool PlayingState::is_in_bounds(Point p)
{
	return (0 <= p.x && p.x + BLOCK_WIDTH < _width) &&
	       (0 <= p.y && p.y + BLOCK_WIDTH < _height);
}

bool PlayingState::quit() 
{
	return _quit;
}
