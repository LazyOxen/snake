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
	_active(true)
{
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
	_state = std::unique_ptr<State>(new GreetingState(_width, _height));
}

void Game::update() {
	if (!_active)
		return;

	_state = _state->update();
	// update next target frame update time
	_next_update_time += FRAME_DELAY;
	// force redraw
	InvalidateRect(_hwnd, nullptr, TRUE);
	// yield the cpu for a bit
	Sleep(FRAME_DELAY/2);
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
	return _state->quit();
}

void Game::redraw() 
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(_hwnd, &ps);

	_state->draw(hdc);

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
