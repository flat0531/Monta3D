#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
#include<vector>
enum MenuType
{
	GAMESTART_MENU, CHARACTERDRAW_MENU
};
class StageSelectMenu {
public:
	StageSelectMenu();
	void update();
	void draw(const ci::Vec2f menupos);
	int getSelectNum();
private:
	struct Menu
	{
		ci::Vec2f trancepos;
		ci::Vec2f size;
		bool iscanselect;
		ci::gl::Texture tex;
	};
	std::vector<Menu>menus;
	ci::gl::Texture icontex;
	int selectnum = 0;
	void drawCursor(const ci::Vec2f menupos);
	void updateCursor();
};
