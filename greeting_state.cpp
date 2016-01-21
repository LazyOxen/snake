#include "greeting_state.h"

GreetingState::GreetingState(int width, int height) : 
	State(width, height),
	_quit_chosen(false),
	_complete(false)
{}

void GreetingState::draw(HDC& hdc)
{
	HBRUSH background = CreateSolidBrush(RGB(144, 184, 0));
	SelectObject(hdc, background);
	Rectangle(hdc, 0, 0, _width, _height);
	DeleteObject(background);

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	auto avg_char_width = tm.tmAveCharWidth;
	auto caps_width = ( tm.tmPitchAndFamily & 1 ? 3 : 2 ) * avg_char_width / 2;
	auto total_line_height = tm.tmHeight + tm.tmExternalLeading;
	HBRUSH textbrush = CreateSolidBrush(RGB(51, 204, 204));
	SelectObject(hdc, textbrush);
	
	auto play = L"Play!";
	auto quit = L"Quit :(";

	auto xstart = (_width - avg_char_width*lstrlen(play)) / 2;
	auto ystart = (_height - total_line_height) / 2;
	TextOut(hdc, xstart, ystart, play, lstrlen(play));

	ystart += total_line_height;
	TextOut(hdc, xstart, ystart, quit, lstrlen(quit));
	
	xstart -= 3*caps_width;
	ystart = _quit_chosen ? ystart : ystart - total_line_height;
	TextOut(hdc, xstart, ystart, L"->", 2);
	DeleteObject(textbrush);
}

std::unique_ptr<State> GreetingState::update()
{
	if (GetAsyncKeyState(VK_UP) < 0) 
		_quit_chosen = false;
	else if (GetAsyncKeyState(VK_DOWN) < 0)
		_quit_chosen = true;
	else if (GetAsyncKeyState(VK_RETURN) < 0)
		_complete = true;

	if (_complete && !_quit_chosen)
		return std::unique_ptr<PlayingState>(new PlayingState(State::_width, State::_height));
	return std::unique_ptr<GreetingState>(new GreetingState(*this));
}

bool GreetingState::quit()
{
	return _complete && _quit_chosen;
}
