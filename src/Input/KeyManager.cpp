#include "KeyManager.h"

void KeyManager::registerDown(ci::app::KeyEvent & _event)
{
	if (press.find(_event.getCode()) == press.end()) {
		push.insert(_event.getCode());
	}
	press.insert(_event.getCode());
}

void KeyManager::registerUp(ci::app::KeyEvent & _event)
{
	pull.insert(_event.getCode());
	press.erase(_event.getCode());
}

void KeyManager::registerEnd()
{
	push.clear();
	pull.clear();
}

bool KeyManager::isPress(const int & _event)
{
	return press.find(_event) != press.end();
}

bool KeyManager::isPush(const int & _event)
{
	return push.find(_event) != push.end();
}

bool KeyManager::isPull(const int & _event)
{
	return pull.find(_event) != pull.end();
}
