#include "you_dead_state.h"

YouDeadState::YouDeadState(int width, int height) :
	State(width, height)
{

	_quit_time = GetTickCount() + 3000; // quit in 3 seconds from now
}

void YouDeadState::draw(HDC& hdc)
{

	HBRUSH background = CreateSolidBrush(RGB(144, 184, 112));
	SelectObject(hdc, background);
	Rectangle(hdc, 0, 0, State::_width, State::_height);
	DeleteObject(background);

	auto msg = L"You dead brah =("; 

	TEXTMETRIC tm;
	GetTextMetrics(hdc, &tm);
	auto avg_char_width = tm.tmAveCharWidth;
	auto caps_width = ( tm.tmPitchAndFamily & 1 ? 3 : 2 ) * avg_char_width / 2;
	auto total_line_height = tm.tmHeight + tm.tmExternalLeading;
	HBRUSH textbrush = CreateSolidBrush(RGB(51, 204, 204));
	SelectObject(hdc, textbrush);
	auto xstart = (_width - avg_char_width*lstrlen(msg)) / 2;
	auto ystart = (_height - total_line_height) / 2;
	TextOut(hdc, xstart, ystart, msg, lstrlen(msg));
	DeleteObject(textbrush);
}

std::unique_ptr<State> YouDeadState::update()
{
	if (GetTickCount() > _quit_time)
		return std::unique_ptr<GreetingState>(new GreetingState(_width, _height));
	return std::unique_ptr<YouDeadState>(new YouDeadState(*this));
}

bool YouDeadState::quit()
{
	return false;
}
