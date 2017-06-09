#include "UIObject.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
UIObject::UIObject()
{

}

UIObject::UIObject(ci::JsonTree json)
{
	pos = JsonM.getVec2(json, "pos");
	size = JsonM.getVec2(json, "size");
	rotate = json.getValueForKey<float>("rotate");
	color = JsonM.getColor(json,"color");
	tex = TextureM.CreateTexture(json.getValueForKey<std::string>("texture"));
}

void UIObject::draw()
{
	DrawM.drawTextureBox(pos, size, rotate, tex, color);
}
