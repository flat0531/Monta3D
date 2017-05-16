#include "DrawManager.h"
#include"../Top/Top.h"
#include"../Top/SortManager.h"
using namespace ci;
using namespace ci::app;
void DrawManager::drawStrokeCube(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate, const ci::ColorA color)
{
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(rotate);
	gl::scale(size);
	gl::color(color);
	gl::drawStrokedCube(Vec3f(0, 0, 0), Vec3f(1, 1, 1));
	gl::popModelView();

}
void DrawManager::drawCube(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate, const ci::ColorA color)
{
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(rotate);
	gl::scale(size);
	gl::color(color);
	gl::drawCube(Vec3f(0,0,0), Vec3f(1, 1, 1));
	gl::popModelView();
}
void DrawManager::drawColorCube(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate)
{
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(rotate);
	gl::scale(size);
	gl::drawColorCube(Vec3f(0, 0, 0), Vec3f(1, 1, 1));
	gl::popModelView();

}
void DrawManager::drawTextureCube(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate, const ci::gl::Texture & texture, const ci::ColorA color, ci::Vec3f centerpos)
{
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(rotate);
	gl::scale(size);
	gl::color(color);
	texture.enableAndBind();
	gl::drawCube(centerpos, Vec3f(1, 1, 1));
	texture.disable();
	gl::popModelView();
}

void DrawManager::drawSphere(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate, const float segment, const ci::ColorA color)
{
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(rotate);
	gl::scale(size);
	gl::color(color);
	gl::drawSphere(Vec3f(0, 0, 0), 1, segment);
	gl::popModelView();
}
void DrawManager::drawTextureSphere(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate, const float segment, const ci::gl::Texture & texture, const ci::ColorA color)
{
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(rotate);
	gl::scale(size);
	gl::color(color);
	texture.enableAndBind();
	gl::drawSphere(Vec3f(0, 0, 0), 1, segment);
	texture.disable();
	gl::popModelView();
}
void DrawManager::drawTaurus(const ci::Vec3f pos, const float sizeout, const float sizein, const ci::Vec3f rotate, const ci::ColorA color, const float segmentout, const float segmentin)
{
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(rotate);
	gl::color(color);
	gl::drawTorus(sizeout,sizein,segmentout,segmentin);
	gl::popModelView();
}
/////////////////////////////////////////////       2D        //////////////////////////////////////////////////////////////
void DrawManager::drawBox(const ci::Vec2f pos,const ci::Vec2f size, const float angle,const ci::ColorA color)
{
	float sort = SortManager::getSort().getSortCount();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x,pos.y,sort));
	gl::rotate(angle);
	gl::scale(size);
	gl::color(color);
	gl::drawSolidRect(Rectf(Vec2f(-0.5f,-0.5f),Vec2f(0.5f,0.5f)));
	gl::popModelView();
	SortManager::getSort().SortCountUp();
}

void DrawManager::drawBox(const ci::Vec2f pos,const ci::Vec2f size, const float angle,const ci::ColorA color,const float sort)
{
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y,sort));
	gl::rotate(angle);
	gl::scale(size);
	gl::color(color);
	gl::drawSolidRect(Rectf(Vec2f(-0.5f, -0.5f), Vec2f(0.5f, 0.5f)));
	gl::popModelView();
}

void DrawManager::drawBoxEdge(const ci::Vec2f pos, const ci::Vec2f size, const ci::ColorA color)
{
	float sort = SortManager::getSort().getSortCount();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	gl::scale(size);
	gl::color(color);
	gl::drawSolidRect(Rectf(Vec2f(0, 0), Vec2f(1, 1)));
	gl::popModelView();
	SortManager::getSort().SortCountUp();
}

void DrawManager::drawTextureArea(const cinder::Vec2f pos, const ci::Vec2f scale, const ci::gl::Texture & tex, cinder::Area area, float size)
{
	float sort = SortManager::getSort().getSortCount();
	gl::pushModelView();
	Vec2f trancepos = -tex.getSize() / 2.0F + pos + Vec2f(tex.getWidth() / 2.0F, -tex.getHeight() / 2.0F);
	gl::translate(Vec3f(trancepos.x,trancepos.y,sort));
	gl::scale(scale);
	gl::color(Color::white());
	gl::draw(tex,
		Area(area.x1, area.y1, area.x1 + area.x2 * size, area.y1 + area.y2),
		Rectf(area.x1, area.y1, area.x1 + area.x2 * size, area.y1 + area.y2));
	tex.unbind();
	gl::popModelView();
}

void DrawManager::drawTextureBoxBottom(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::gl::Texture & tex, const ci::ColorA color)
{
	float sort = SortManager::getSort().getSortCount();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	gl::rotate(angle);
	gl::scale(-size);
	gl::color(color);
	tex.enableAndBind();
	gl::drawSolidRect(Rectf(Vec2f(0.5f, 1.f), Vec2f(-0.5f, 0)));

	tex.disable();
	gl::popModelView();
	SortManager::getSort().SortCountUp();
}

void DrawManager::drawTextureBox(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::gl::Texture& tex, const ci::ColorA color)
{
	float sort = SortManager::getSort().getSortCount();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	gl::rotate(angle);
	gl::scale(size);
	gl::color(color);
	tex.enableAndBind();
	gl::drawSolidRect(Rectf(Vec2f(-0.5f, -0.5f), Vec2f(0.5f, 0.5f)));
	tex.disable();
	gl::popModelView();
	SortManager::getSort().SortCountUp();
}

void DrawManager::drawTextureBox(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::gl::Texture& tex, const ci::ColorA color, const float sort)
{
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	gl::rotate(angle);
	gl::scale(size);
	gl::color(color);
	tex.enableAndBind();
	gl::drawSolidRect(Rectf(Vec2f(-0.5f, -0.5f), Vec2f(0.5f, 0.5f)));
	tex.disable();
	gl::popModelView();
}


void DrawManager::drawTextureBoxEdge(ci::Vec2f pos, ci::Vec2f size,const ci::gl::Texture& tex, ci::ColorA color)
{
	float sort = SortManager::getSort().getSortCount();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	gl::scale(size);
	gl::color(color);
	tex.enableAndBind();
	gl::drawSolidRect(Rectf(Vec2f(0, 0), Vec2f(1, 1)));
	tex.disable();
	gl::popModelView();
	SortManager::getSort().SortCountUp();
}

void DrawManager::drawTextureBoxEdge(ci::Vec2f pos, ci::Vec2f size,const ci::gl::Texture& tex, ci::ColorA color, float sort)
{
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	gl::scale(size);
	gl::color(color);
	tex.enableAndBind();
	gl::drawSolidRect(Rectf(Vec2f(0, 0), Vec2f(1,1)));
	tex.disable();
	gl::popModelView();
}

void DrawManager::drawSurface(ci::Vec2f pos, ci::Vec2f size, const ci::Surface surface)
{
	float sort = SortManager::getSort().getSortCount();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	Vec2f _size = size / surface.getSize();
	gl::scale(_size);
	gl::color(ColorA(1,1,1,1));
	gl::draw(surface);
	gl::popModelView();
	SortManager::getSort().SortCountUp();
}

void DrawManager::drawSurface(ci::Vec2f pos, ci::Vec2f size, const ci::Surface surface, float sort)
{
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	Vec2f _size = size / surface.getSize();
	gl::scale(_size);
	gl::color(ColorA(1, 1, 1, 1));
	gl::draw(surface);
	gl::popModelView();
}

void DrawManager::drawCenterSurface(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::Surface surface)
{
	float sort = SortManager::getSort().getSortCount();
	Vec2f _size = size / surface.getSize();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x - size.x / 2, pos.y - size.y / 2, sort));
	gl::rotate(angle);
	gl::scale(_size);
	gl::color(ColorA(1, 1, 1, 1));
	gl::draw(surface);
	gl::popModelView();
	SortManager::getSort().SortCountUp();
}

void DrawManager::drawCenterSurface(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::Surface surface, float sort)
{
	Vec2f _size = size / surface.getSize();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x - _size.x / 2, pos.y - _size.y / 2, sort));
	gl::rotate(angle);
	gl::scale(_size);
	gl::color(ColorA(1, 1, 1, 1));
	gl::draw(surface);
	gl::popModelView();
}

void DrawManager::drawFont(const std::string text, const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::ColorA color, const ci::Font & font)
{
	float sort = SortManager::getSort().getSortCount();
	gl::pushModelView();
	gl::translate(Vec3f(pos.x, pos.y, sort));
	gl::rotate(angle);
	gl::scale(size);
	gl::drawString(text, Vec2f(0, 0), color, font);
	gl::popModelView();
	SortManager::getSort().SortCountUp();
}
