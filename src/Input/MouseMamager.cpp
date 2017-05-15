#include"MouseMamager.h"
#include"../Top/Top.h"
using namespace ci;
using namespace ci::app;
void MouseManager::registerDown(ci::app::MouseEvent & _event)
{
	if (_event.isLeft()) {
		press.insert(ci::app::MouseEvent::LEFT_DOWN);
		push.insert(ci::app::MouseEvent::LEFT_DOWN);
	}
	if (_event.isRight()) {
		press.insert(ci::app::MouseEvent::RIGHT_DOWN);
		push.insert(ci::app::MouseEvent::RIGHT_DOWN);
	}
	if (_event.isMiddle()) {
		press.insert(ci::app::MouseEvent::MIDDLE_DOWN);
		push.insert(ci::app::MouseEvent::MIDDLE_DOWN);
	}
}

void MouseManager::registerUp(ci::app::MouseEvent & _event)
{
	if (_event.isLeft()) {
		press.erase(ci::app::MouseEvent::LEFT_DOWN);
		pull.insert(ci::app::MouseEvent::LEFT_DOWN);
	}
	if (_event.isRight()) {
		press.erase(ci::app::MouseEvent::RIGHT_DOWN);
		pull.insert(ci::app::MouseEvent::RIGHT_DOWN);
	}
	if (_event.isMiddle()) {
		press.erase(ci::app::MouseEvent::MIDDLE_DOWN);
		pull.insert(ci::app::MouseEvent::MIDDLE_DOWN);
	}
}

void MouseManager::registerEnd()
{
	push.clear();
	pull.clear();
	wheel_increment = 0;
}

void MouseManager::registerMove(ci::app::MouseEvent & _event)
{
	mousepos = _event.getPos();
}

void MouseManager::registerWheel(ci::app::MouseEvent & _event)
{
	wheel_increment = _event.getWheelIncrement();
}

bool MouseManager::isPress(const int & _event)
{
	return press.find(_event) != press.end();
}

bool MouseManager::isPush(const int & _event)
{
	return push.find(_event) != push.end();
}

bool MouseManager::isPull(const int & _event)
{
	return pull.find(_event) != pull.end();
}

cinder::Vec2i MouseManager::getmousepos()
{
	float rate_x = ((float)WINDOW_WIDTH)/ ((float)getWindowSize().x);
	float rate_y = ((float)WINDOW_HEIGHT)/ ((float)getWindowSize().y);
	return Vec2f(mousepos.x*rate_x, mousepos.y*rate_y);
}

float MouseManager::getWheelIncrement()
{
	return wheel_increment;
}
