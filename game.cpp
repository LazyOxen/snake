#include "game.h"

std::unique_ptr<Game> Game::instance = nullptr;

static bool run_already = false;
void Game::create(unsigned int width, unsigned int height)
{
	if (!run_already) {
		instance = std::unique_ptr<Game>(new Game(width, height));
		run_already = true;
	}
}

Game::Game(unsigned int width, unsigned int height) : 
	_width(width),
	_height(height),
	_active(true),
	_quit(false),
	_snake(width/2, height/2)
{
	_food.x = ((width*3u>>2) % BLOCK_WIDTH)*BLOCK_WIDTH;
	_food.y = ((height*3u>>2) % BLOCK_WIDTH)*BLOCK_WIDTH;

	_hInstance =  GetModuleHandle( nullptr );

	WNDCLASSW wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Snake!";
	wc.hInstance = _hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassW(&wc);
	_hwnd = CreateWindowW(wc.lpszClassName, L"Snake!",
	           WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	           0, 0, width, height, NULL, NULL, _hInstance, NULL);

	ShowWindow(_hwnd, SW_SHOWDEFAULT);
	UpdateWindow(_hwnd);
	initialize_timestamp();

	// adjust paint area to width and height
	// and center the window on the screen
	RECT r;
	GetClientRect(_hwnd, &r);
	int width_adj = width - r.right;
	int height_adj = height - r.bottom;
	GetWindowRect(_hwnd, &r);
	MoveWindow(_hwnd, 
	           (GetSystemMetrics(SM_CXSCREEN) - r.right)/2, 
	           (GetSystemMetrics(SM_CYSCREEN) - r.bottom)/2,
	           width + width_adj, 
	           height + height_adj, 
	           TRUE);

	srand( time(nullptr) );
}

void Game::update() {
	if (!_active)
		return;

	handle_input();

	_snake.update();

	if (_snake.head() == _food) {
		_snake.eat();
		position_food();
	} else if (_snake.is_in_body(_snake.head()) || !is_in_bounds(_snake.head())) {
		_quit = true;
	}

	// update next target frame update time
	_next_update_time += FRAME_DELAY;
	// force redraw
	InvalidateRect(_hwnd, nullptr, TRUE);
	// yield the cpu for a bit
	Sleep(FRAME_DELAY/2);
}

bool Game::is_in_bounds(Point p)
{
	return (0 <= p.x && p.x + BLOCK_WIDTH < _width) &&
	       (0 <= p.y && p.y + BLOCK_WIDTH < _height);
}
void Game::initialize_timestamp()
{
	_timestamp = GetTickCount();
	_next_update_time = _timestamp + FRAME_DELAY;
	// in the off chance of overflow
	if (_next_update_time < _timestamp) {
		_timestamp = 0;
	}
}

void Game::set_active()
{
	initialize_timestamp();
	_active = true;
}

void Game::set_inactive()
{
	_active = false;
}

bool Game::time_to_update()
{
	return _next_update_time <= GetTickCount();
}

bool Game::done_playing() 
{
	return _quit;
}

void Game::handle_input() {
		if (GetAsyncKeyState(VK_UP) < 0)
			_snake.move(Direction::Up);
		else if (GetAsyncKeyState(VK_DOWN) < 0)
			_snake.move(Direction::Down);
		else if (GetAsyncKeyState(VK_LEFT) < 0)
			_snake.move(Direction::Left);
		else if (GetAsyncKeyState(VK_RIGHT) < 0)
			_snake.move(Direction::Right);
		else if (GetAsyncKeyState(VK_ESCAPE) < 0)
			_quit = true;
}

void Game::position_food()
{
	while (_food == _snake.head() || _snake.is_in_body(_food)) {
		_food.x = (rand() % ((_width-BLOCK_WIDTH)/BLOCK_WIDTH))*BLOCK_WIDTH;
		_food.y = (rand() % ((_height-BLOCK_WIDTH)/BLOCK_WIDTH))*BLOCK_WIDTH;
	}
}

void Game::redraw() 
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(_hwnd, &ps);

	_snake.draw(hdc);
	Rectangle(hdc, _food.x, _food.y, _food.x + BLOCK_WIDTH, _food.y + BLOCK_WIDTH);

	EndPaint(_hwnd, &ps);
}

LRESULT CALLBACK Game::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		case WM_SETFOCUS:
		{
			Game::instance->set_active();
			return 0;
		}
		case WM_KILLFOCUS:
		{
			Game::instance->set_inactive();
			return 0;
		}
		case WM_PAINT:
		{
			Game::instance->redraw();
			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
