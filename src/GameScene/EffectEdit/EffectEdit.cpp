#include "EffectEdit.h"
#include"../../Top/Top.h"
#include"../../Top/DrawManager.h"
#include"../../Top/SortManager.h"
#include"../../Top/TextureManager.h"
#include"../../Input/KeyManager.h"
#include"../../Scene/SceneManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../Input/MouseMamager.h"
#include"../../Top/CollisionManager.h"

using namespace ci;
using namespace ci::app;

void EffectEdit::setup()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
		60.0f,
		0.1f, 1000.0f);
	camera.setEyePoint(Vec3f(0, 0, 0));
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000));
	ortho = CameraOrtho(0, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0,
		1, 101);
	//createname = "nurie.png";
	//TextureM.CreateTexture(createname);
	//texturesize = TextureM.getTexture(createname).getSize();

	//surface = Surface(texturesize.x, texturesize.y, true);
	//for (int y = 0; y <texturesize.y; y++)
	//{
	//	for (int x = 0; x < texturesize.x; x++)
	//	{
	//		surface.setPixel(Vec2i(x, y), ColorA(1, 1, 1, 0.2f));
	//	}
	//}
	//texturesurface = Surface(TextureM.getTexture(createname));
	//for (int y = 0; y <texturesize.y; y++)
	//{
	//	for (int x = 0; x < texturesize.x; x++)
	//	{
	//		surface.setPixel(Vec2i(x, y), ColorA(1, 1, 1, 0.2f));
	//	}
	//}
	//replaycount = 0;
}

void EffectEdit::update()
{
	/*updateSurface();
	if (!isreplay&&KeyManager::getkey().isPush(KeyEvent::KEY_s)){
		startReplay();
	}
	if (isreplay) {
		ReplayEffect();
	}
	if ((!issaving)&&MouseManager::getMouse().isPush(MouseEvent::LEFT_DOWN)) {
		saveStart();
	}
	if ((issaving) && MouseManager::getMouse().isPush(MouseEvent::RIGHT_DOWN)) {
		saveStop();
	}
	if ((!issaving) && KeyManager::getkey().isPush(KeyEvent::KEY_r)) {
		resetSurface();
	}
	if ((!issaving) && KeyManager::getkey().isPush(KeyEvent::KEY_w)) {
		writeMousepos();
	}
	if ((!issaving) && KeyManager::getkey().isPush(KeyEvent::KEY_l)) {
		loadMousePos();
	}
	if ((!issaving) && KeyManager::getkey().isPush(KeyEvent::KEY_p)) {
		for (int i = 0;i < savepos.size();i++) {
			console() << savepos[i].pos.x << "x" << i << std::endl;
			console() << savepos[i].pos.y << "y" << i << std::endl;
			console() << savepos[i].ispress << "is" << i << std::endl;
		}
	}*/
	
}

void EffectEdit::draw()
{
	gl::setMatrices(camera);
	gl::pushModelView();

	gl::popModelView();
}

void EffectEdit::draw2D()
{
	gl::setMatrices(ortho);
	gl::pushModelView();

	Drawsurface();

	gl::popModelView();
}

void EffectEdit::shift()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_t)) {
		SceneManager::createScene(Title());
	}
}

void EffectEdit::baseDraw()
{
	//DrawM.drawTextureBoxEdge(Vec2f(0,0), texturesize, TextureM.getTexture(createname),ColorA(1,1,1,0.5f));
}

void EffectEdit::Drawsurface()
{
	//DrawM.drawSurface(Vec2f(0,0),texturesize, surface);
}

void EffectEdit::updateSurface()
{
	if (!issaving)return;
	Vec2i pos = MouseManager::getMouse().getmousepos();
	MousePosPress buf;
	buf.pos = pos;
	buf.ispress= MouseManager::getMouse().isPress(MouseEvent::LEFT_DOWN);
	savepos.push_back(buf);
	for (int y = 0;y < 2 * pixceldrawsize;y++) {
		for (int x = 0;x < 2 * pixceldrawsize;x++) {
			Vec2f setpos = pos - Vec2f(pixceldrawsize, pixceldrawsize) + Vec2f(x, y);
			if (setpos.x < 0)continue;
			if (setpos.y < 0)continue;
			if (setpos.x >= texturesize.x)continue;
			if (setpos.y >= texturesize.y)continue;
			if (CollisionM.isCirclePoint(setpos, pos, pixceldrawsize)) {
				surface.setPixel(setpos, texturesurface.getPixel(setpos));
			}
		}
	}
}
void EffectEdit::loadMousePos()
{
	std::string str = "EffectPoss/nurieposs.txt";
	std::ifstream savefile(getAssetPath(str).string());
	assert(!savefile.fail());
	savepos.clear();
	while (!savefile.eof()) {
		MousePosPress buf;
		int x;
		int y;
		bool is;
		savefile >> x;
		savefile >> y;
		savefile >> is;
		buf.pos.x = x;
		buf.pos.y = y;
		buf.ispress = is;
		savepos.push_back(buf);
	}
}
void EffectEdit::writeMousepos()
{
	std::string str = "EffectPoss/nurieposs.txt";
	std::ofstream savefile(getAssetPath(str).string());
	assert(!savefile.fail());
	for (int i = 0;i < savepos.size();i++) {

		savefile << savepos[i].pos.x << " " << savepos[i].pos.y << " " << savepos[i].ispress << "\n";
	}
	
}

void EffectEdit::startReplay()
{
	isreplay = true;
	replaycount = 0;
}

void EffectEdit::ReplayEffect()
{
	if (!isreplay)return;
	Vec2f pos = savepos[replaycount].pos;
	for (int y = 0;y < 2 * pixceldrawsize;y++) {
		for (int x = 0;x < 2 * pixceldrawsize;x++) {
			Vec2f setpos = pos - Vec2f(pixceldrawsize, pixceldrawsize) + Vec2f(x, y);
			if (setpos.x < 0)continue;
			if (setpos.y < 0)continue;
			if (setpos.x >= texturesize.x)continue;
			if (setpos.y >= texturesize.y)continue;
			if (CollisionM.isCirclePoint(setpos, pos, pixceldrawsize)) {
				surface.setPixel(setpos, texturesurface.getPixel(setpos));
			}
		}
	}
	replaycount++;
	if (replaycount == savepos.size()) {
		isreplay = false;
		replaycount = 0;
	}
}

void EffectEdit::resetSurface()
{
	for (int y = 0; y <texturesize.y; y++)
	{
		for (int x = 0; x < texturesize.x; x++)
		{
			surface.setPixel(Vec2i(x, y), ColorA(1, 1, 1, 0.2f));
		}
	}
}

void EffectEdit::saveStart()
{
	issaving = true;
	savepos.clear();
}

void EffectEdit::saveStop()
{
	issaving = false;
}


