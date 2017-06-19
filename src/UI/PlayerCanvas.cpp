#include "PlayerCanvas.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/CollisionManager.h"

using namespace ci;
using namespace ci::app;
PlayerCanvas::PlayerCanvas()
{
}
void PlayerCanvas::setup(ci::Vec2f _pos, ci::Vec2f _size, std::string _charactername)
{
	pos = _pos;
	size = _size;
	charactername = _charactername;
	characterframepath = "Draw/" + charactername + "/"  + "frame.png";
	TextureM.CreateTexture(characterframepath);
	SetupdrawCanvas();


}

ci::Vec2f PlayerCanvas::getPos()
{
	return pos;
}

ci::Vec2f PlayerCanvas::getSIze()
{
	return size;
}

ci::Surface PlayerCanvas::getSurface()
{
	return drawcanvas;
}

void PlayerCanvas::SetupdrawCanvas()
{
	Vec2f canvassize = Vec2f(512, 512);
	drawcanvas = Surface(canvassize.x, canvassize.y, true);
	for (int y = 0; y <canvassize.y; y++)
	{
		for (int x = 0; x < canvassize.x; x++)
		{
			drawcanvas.setPixel(Vec2i(x, y), ColorA(0, 0, 0, 0));
		}
	}
}

void PlayerCanvas::updateCanvas(const ci::ColorA _color, const ci::Vec2f pointerpos, float _circlesize)
{
	if (!CollisionM.isBoxPoint(pointerpos, pos, size)) {
		return;
	}
	Vec2i drawpos = pointerpos - pos;

	Vec2f canvassize = Vec2f(512, 512);
	for (int y = 0;y < 2 *_circlesize;y++) {
		for (int x = 0;x < 2 * _circlesize;x++) {
			Vec2f setpos = drawpos - Vec2f(_circlesize, _circlesize) + Vec2f(x, y);
			if (setpos.x < 0)continue;
			if (setpos.y < 0)continue;
			if (setpos.x >= canvassize.x)continue;
			if (setpos.y >= canvassize.y)continue;
			if (CollisionM.isCirclePoint(setpos, drawpos, _circlesize)) {
				drawcanvas.setPixel(setpos, _color);
			}
		}
	}
}


void PlayerCanvas::draw()
{
	DrawM.drawTextureBoxEdge(pos, size, TextureM.getTexture("Draw/frame.png"), ColorA(1, 1, 1, 1));
	DrawM.drawSurface(pos, size, drawcanvas);
	DrawM.drawTextureBoxEdge(pos, size, TextureM.getTexture(characterframepath), ColorA(1, 1, 1, 1));
}





