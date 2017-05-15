#pragma once
#include"cinder/app/KeyEvent.h"
#include<set>

class KeyManager {
public:
	void registerDown(ci::app::KeyEvent& _event);
	void registerUp(ci::app::KeyEvent& _event);
	void registerEnd();
	bool isPress(const int& _event);
	bool isPush(const int& _event);
	bool isPull(const int& _event);
	static KeyManager& getkey() {
		static KeyManager manager;
		return manager;
	}
private:
	std::set<int>press;
	std::set<int>push;
	std::set<int>pull;
};