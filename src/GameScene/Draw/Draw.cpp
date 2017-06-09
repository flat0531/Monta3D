#include "Draw.h"
#include"../../Top/Top.h"
#include"../../Top/DrawManager.h"
#include"../../Top/SortManager.h"
#include"../../Top/TextureManager.h"
#include"../../Input/KeyManager.h"
#include"../../Input/MouseMamager.h"
#include"../../Scene/SceneManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../Input/MouseMamager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/EasingStream.h"
#include"../../Top/CollisionManager.h"
#include"../../Top/SoundManager.h"
#include<vector>
using namespace ci;
using namespace ci::app;

Draw::Draw()
{

}

void Draw::setup()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
		60.0f,
		0.1f, 1000.0f);
	camera.setEyePoint(Vec3f(0,0,0));
	camera.setCenterOfInterestPoint(Vec3f(0,0,1000));
	ortho = CameraOrtho(0, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0,
		1, 101);
	SoundM.PlayBGM("drawscene.wav", 0.3f);

	charactername = "slime";

	framepath = "Draw/frame.png";
	characterframepath = "Draw/" + charactername + "/frame.png";
	charactercoloredpath = "Draw/" + charactername + "/" + charactername + "color.png";
	characterplaypath = "Draw/" + charactername + "/" + "default.png";
	TextureM.CreateTexture(framepath);
	
	TextureM.CreateTexture(charactercoloredpath);
	TextureM.CreateTexture(characterplaypath);
	TextureM.CreateTexture("Draw/white.png");
	gl::Texture effecttex = TextureM.getTexture(characterplaypath);
	gl::Texture effecttex2 = TextureM.getTexture("Draw/white.png");

	TextureM.CreateTexture("UI/canvas.png");
	TextureM.CreateTexture("UI/nuriemode.png");
	TextureM.CreateTexture("UI/book.png");
	TextureM.CreateTexture("UI/bar.png");
	Vec2f playercanvaspos = Vec2f(WINDOW_WIDTH / 2 + WINDOW_WIDTH / 18-256, WINDOW_HEIGHT /2.0-256);
	playercanvas.setup(playercanvaspos, Vec2f(512, 512), charactername);

	uifront.CreateUI("Json/UI/drawscenefront.json");
	uiback.CreateUI("Json/UI/drawsceneback.json");
}
void Draw::update()
{
	drawmenu.update();

	drawpointer.update();

	palletmanager.update();
	drawpointer.setCircleSize(drawmenu.getSizeRangeValue());
	
	drawpointer.setCircleColor(palletmanager.getSelectcolor());
	drawmenu.setCircleColor(palletmanager.getSelectcolor());
	drawmenu.setSampleCircleSize(drawpointer.getCircleSize());
	drawpointer.setIsCircledraw(CollisionM.isBoxPoint(drawpointer.getPos(),playercanvas.getPos(),playercanvas.getSIze()));
	if (MouseManager::getMouse().isPress(MouseEvent::RIGHT_DOWN)) {
		playercanvas.updateCanvas(ColorA(1,1,1,0), drawpointer.getPos(), drawpointer.getCircleSize());
	}
	if (MouseManager::getMouse().isPress(MouseEvent::LEFT_DOWN)) {
		playercanvas.updateCanvas(palletmanager.getSelectcolor(), drawpointer.getPos(), drawpointer.getCircleSize());
	}
	testup();
	check();
}

void Draw::draw()
{
	gl::setMatrices(camera);
	gl::pushModelView();

	gl::popModelView();
}

void Draw::draw2D()
{
	gl::setMatrices(ortho);
	gl::pushModelView();
	uiback.draw();
	drawmenu.draw();
	drawSample();
	playercanvas.draw();
	palletmanager.draw();
	drawpointer.draw();
	drawcheckpoint();
	uifront.draw();
	gl::popModelView();
}

void Draw::shift()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_t)) {
		SceneManager::createScene(Title());
	}
}




bool Draw::isCirclePointvalue(ci::Vec2f circlepos, ci::Vec2f pointpos, float circlesize, float & value, float underlimit)
{

	float kyori = (circlepos.x - pointpos.x)*(circlepos.x - pointpos.x) + (circlepos.y - pointpos.y)*(circlepos.y - pointpos.y);

	if (kyori <= (circlesize*circlesize)) {
		float _value = kyori / (circlesize*circlesize);
		if (_value < underlimit) {
			value = 0.0f;
		}
		else {
			value = _value;
		}
		
		return true;
	}
	return false;
}

void Draw::drawSample()
{
	Vec2f pos = Vec2f(WINDOW_WIDTH / 4.5, WINDOW_HEIGHT / 2.f);
	Vec2f size = Vec2f(512, 512);
	Vec2f pos2 = Vec2f(WINDOW_WIDTH / 2+ WINDOW_WIDTH / 18, WINDOW_HEIGHT / 1.8);
	DrawM.drawTextureBox(pos, size, 0, TextureM.getTexture(charactercoloredpath), ColorA(1, 1, 1, 1));
	//DrawM.drawTextureBox(pos2, size, 0, TextureM.getTexture(characterframepath), ColorA(1, 1, 1, 1));
}
void Draw::drawColorPallet()
{
	
}

void Draw::testup()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_u)) {
		Surface test;
		Vec2i texturesize = TextureM.getTexture(characterplaypath).getSize();
		test = Surface(TextureM.getTexture(characterplaypath));
		std::vector<Vec4i>colors;
		for (int y = 0; y <texturesize.y; y++)
		{
			for (int x = 0; x < texturesize.x; x++)
			{
				int buf[4];
				buf[0] = test.getPixel(Vec2i(x, y)).r;
				buf[1] = test.getPixel(Vec2i(x, y)).g;
				buf[2] = test.getPixel(Vec2i(x, y)).b;
				buf[3] = test.getPixel(Vec2i(x, y)).a;
				bool isnew = true;
				for (int i = 0;i < colors.size();i++) {
					bool check[4];
					for (int j = 0;j < 4;j++) {
						check[j] = (colors[i][j] == buf[j]);
					}
					if (check[0] && check[1] && check[2] && check[3]) {
						isnew = false;
						break;
					}
				}
				if (isnew)colors.push_back(Vec4i(buf[0], buf[1], buf[2], buf[3]));
				//console() << test.getPixel(Vec2i(x, y)) << std::endl;
			}
		}
		colors.clear();
	}
}

void Draw::check()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_c)) {
		Surface sample;
		Vec2i texturesize = TextureM.getTexture(characterplaypath).getSize();
		sample = Surface(TextureM.getTexture(characterplaypath));
		Surface playersurface(playercanvas.getSurface());
		int clearcount = 0;
		
		for (int y = 0; y <texturesize.y; y++)
		{
			for (int x = 0; x < texturesize.x; x++)
			{
				if (sample.getPixel(Vec2i(x, y)).a == 0) {
					clearcount++;
					continue;
				}
			}
		}
			int checkcount = 0;
		
		for (int y = 0; y <texturesize.y; y++)
		{
			for (int x = 0; x < texturesize.x; x++)
			{
				if (sample.getPixel(Vec2i(x, y)).a == 0) {
					continue;
				}
				if (sample.getPixel(Vec2i(x, y)).r == playersurface.getPixel(Vec2i(x, y)).r
					&&sample.getPixel(Vec2i(x, y)).g == playersurface.getPixel(Vec2i(x, y)).g
					&&sample.getPixel(Vec2i(x, y)).b == playersurface.getPixel(Vec2i(x, y)).b
					&&sample.getPixel(Vec2i(x, y)).a == playersurface.getPixel(Vec2i(x, y)).a)
				{
					checkcount++;
					continue;
				}
			}
		}
		const int max = texturesize.x *texturesize.y - clearcount;
		console() << float(checkcount)/float(max) << std::endl;
		float correction_value = 1.02f;
		check_rate_value = std::min((float(checkcount) / float(max))*correction_value,1.0f);

		console() << check_rate_value << std::endl;
	}
}

void Draw::drawcheckpoint()
{
	Vec2f backpos(WINDOW_WIDTH/2-300, 50);
	Vec2f maxsize(500, 50);
	DrawM.drawTextureBoxEdge(backpos,maxsize,
		TextureM.getTexture("UI/bar.png"));
	DrawM.drawTextureBoxEdge(backpos, Vec2f(check_rate_value*maxsize.x,maxsize.y), 
		TextureM.getTexture("UI/bar.png"),ColorA(0,1,0,1));
}
