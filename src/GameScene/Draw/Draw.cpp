#include "Draw.h"
#include"../../Top/Top.h"
#include"../../Top/DrawManager.h"
#include"../../Top/SortManager.h"
#include"../../Top/TextureManager.h"
#include"../../Input/KeyManager.h"
#include"../../Input/MouseMamager.h"
#include"../../Scene/SceneManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../GameScene/FolmSelect/FolmSelect.h"
#include"../../GameScene/StageSelect/StageSelect.h"
#include"../../Input/MouseMamager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/EasingStream.h"
#include"../../Top/CollisionManager.h"
#include"../../Top/SoundManager.h"
#include"../../Top/FadeManager.h"
#include"../../Top/DataManager.h"
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
	successrate = 0.95f;
	SoundM.PlayBGM("drawscene.wav", 0.3f);
	SoundM.SetLoopBGM("drawscene.wav", true);

	FadeM.StartFadeOut(false);
	istutorial = DataM.getIsTutorial("draw");

	charactername = DataM.getSelectActionName();

	CreateAssets();
	

	
	Vec2f playercanvaspos = Vec2f(WINDOW_WIDTH / 2 + WINDOW_WIDTH / 18-256, WINDOW_HEIGHT /2.0-256);
	playercanvas.setup(playercanvaspos, Vec2f(512, 512), charactername);

	uifront.CreateUI("Json/UI/drawscenefront.json");
	uiback.CreateUI("Json/UI/drawsceneback.json");
}
void Draw::update()
{
	if (FadeM.getIsFading())return;
	updateMouseClick();
	if (ismousewindow)return;
	drawmenu.update();
	if (!ischeck&&(!isclear)) {
		updateTutorialButton();
	}
	
	drawpointer.update();
	updateCheck();
	palletmanager.update();
	drawpointer.setCircleSize(drawmenu.getSizeRangeValue());
	
	drawpointer.setCircleColor(palletmanager.getSelectcolor());
	drawmenu.setCircleColor(palletmanager.getSelectcolor());
	drawmenu.setSampleCircleSize(drawpointer.getCircleSize());
	drawpointer.setIsCircledraw(CollisionM.isBoxPoint(drawpointer.getPos(),playercanvas.getPos(),playercanvas.getSIze()));
	updateEraceCanvas();
	updateDrawCanvas();
	ClearedShiftStart();
	BackShiftStart();
	
	
	testup();
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
	drawTutorialButton();
	drawpointer.draw();
	drawcheckpoint();
	uifront.draw();
	drawTutorialTextures();
	drawClearWindow();
	drawMouseClick();
	gl::popModelView();
}

void Draw::shift()
{
	if (isshift&&FadeM.getIsfadeinEnd()) {
		DataM.setPrevScene(SceneType::DRAW_SCENE);
		if (DataM.getNextscene() == SceneType::STAGESELECT_SCENE) {
			SceneManager::createScene(StageSelect());
		}
		if (DataM.getNextscene() == SceneType::FOLMSELECT_SCENE) {
			SceneManager::createScene(FolmSelect());
		}
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

float Draw::check()
{
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
	console() << float(checkcount) / float(max) << std::endl;
	float correction_value = 1.1f;
	check_rate_value = std::min((float(checkcount) / float(max))*correction_value, 1.0f);

	console() << check_rate_value << std::endl;
	return  check_rate_value;
}

void Draw::drawcheckpoint()
{
	if (ischeck) {
		Vec2f backpos(WINDOW_WIDTH / 2 - 200, 50);
		Vec2f maxsize(500, 50);
		DrawM.drawTextureBoxEdge(backpos, maxsize,
			TextureM.getTexture("UI/hpbarframebase.png"));
		DrawM.drawBoxEdge(backpos, Vec2f(easing_checkrate*maxsize.x, maxsize.y),
			ColorA(0, 1, 0, 1));
		DrawM.drawTextureBoxEdge(backpos, maxsize,
			TextureM.getTexture("UI/hpbarframe.png"));

	}

}

void Draw::drawMouseClick()
{
	if (ismousewindow) {
		mouseclickpos = Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f;
		mouseclicksize = Vec2f(800, 500);
		DrawM.drawTextureBox(mouseclickpos, mouseclicksize, 0.0f, TextureM.getTexture("UI/mausudesousasitene.png"));
		DrawM.drawTextureBox(mouseclickpos + Vec2f(0, 180), Vec2f(200, 100), 0.0f, TextureM.getTexture("UI/Button/click_ui.png"));
	}

}

void Draw::updateEraceCanvas()
{
	if (MouseManager::getMouse().isPress(MouseEvent::RIGHT_DOWN)) {
		if (!ischeck&&!isclear) {
			playercanvas.updateCanvas(ColorA(1, 1, 1, 0), drawpointer.getPos(), drawpointer.getCircleSize());
		}

	}
}

void Draw::updateDrawCanvas()
{
	if (MouseManager::getMouse().isPress(MouseEvent::LEFT_DOWN)) {
		if (!ischeck&&!isclear) {
			playercanvas.updateCanvas(palletmanager.getSelectcolor(), drawpointer.getPos(), drawpointer.getCircleSize());
		}

	}
}

void Draw::ClearedShiftStart()
{
	if (isclear) {
		if (!FadeM.getIsFading() && MouseManager::getMouse().isPush(MouseEvent::LEFT_DOWN)) {
			isshift = true;
			FadeM.StartFadeIn();
			SoundM.FadeNowBGM(0.0f, 1.5f, true);
			DataM.setNextScene(SceneType::STAGESELECT_SCENE);
		}
	}
}

void Draw::BackShiftStart()
{
	if (CollisionM.isBoxPoint(MouseManager::getMouse().getmousepos(), Vec2f(1400, 670) - Vec2f(100, 50), Vec2f(200, 100))) {
		if (!FadeM.getIsFading() && MouseManager::getMouse().isPull(MouseEvent::LEFT_DOWN) && (!ischeck) && (!isclear)) {
			isshift = true;
			FadeM.StartFadeIn();
			SoundM.FadeNowBGM(0.0f, 1.5f, true);
			DataM.setNextScene(SceneType::FOLMSELECT_SCENE);
		}

	}
}

void Draw::drawClearWindow()
{
	if (isclear) {
		Vec2f pos = Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f;
		Vec2f size = Vec2f(1000,700);
		DrawM.drawTextureBox(pos, size, 0.0f, TextureM.getTexture("UI/informationreleasefolm.png"), ColorA(1, 1, 1, 1));
		DrawM.drawTextureBox(pos+Vec2f(0,-100),Vec2f(350,350), 0.0f, TextureM.getTexture("Draw/" + DataM.getSelectActionName() + "/" + DataM.getSelectActionName() + "color.png"), ColorA(1, 1, 1, 1));
	}
}

void Draw::updateMouseClick()
{
	if (!FadeM.getIsFading()) {
		if (MouseManager::getMouse().isPull(MouseEvent::LEFT_DOWN)) {
			if (CollisionM.isBoxPoint(MouseManager::getMouse().getmousepos(), mouseclickpos - mouseclicksize / 2.f, mouseclicksize)) {
				ismousewindow = false;
			}
		}
	}
}

void Draw::updateTutorialButton()
{
	if (istutorial) {
		tutorialsinangle = 0.0f;
	}
	else {
		tutorialsinangle += 0.05f;
		if (tutorialsinangle >= M_PI*2.f) {
			tutorialsinangle -= M_PI*2.f;
		}
	}
	if (tutorialcount >= 1) {
		if (MouseManager::getMouse().isPush(MouseEvent::LEFT_DOWN)) {
			tutorialcount++;
			tutorialcount = tutorialcount % (tutorialtextures.size() + 1);
		}
	}


	if (tutorialcount == 0) {
		if (MouseManager::getMouse().isPush(MouseEvent::LEFT_DOWN)) {
			if (CollisionM.isBoxPoint(MouseManager::getMouse().getmousepos(), Vec2f(1450, 70) - Vec2f(130, 130) / 2.f, Vec2f(130, 130))) {
				tutorialcount = 1;
				if (!DataM.getIsTutorial("draw")) {
					DataM.saveIsTutorial("draw");
					istutorial = true;
					tutorialsinangle = 0.0f;
				}
			}
		}
	}

}

void Draw::updateCheck()
{
	if (!(tutorialcount == 0))return;
	if (!ischeck) {

		if (MouseManager::getMouse().isPull(MouseEvent::LEFT_DOWN)) {
			Vec2f pos = Vec2f(1400, 500);
			Vec2f size = Vec2f(170, 100);
			if (CollisionM.isBoxPoint(MouseManager::getMouse().getmousepos(), pos - size / 2.f, size)) {
				ischeck = true;
				SoundM.PlaySE("result.wav");
				check_t = 0.0f;
				checkendvalue = check();
			}
		}

	}
	if (ischeck) {
		EasingManager::tCount(check_t, 3.0f);
		easing_checkrate = EasingLinear(check_t, 0.0f, checkendvalue);
		if (EasingManager::tCountEnd(check_t)) {
			EasingManager::tCount(check_delay_t, 0.5f);
		}
		if (EasingManager::tCountEnd(check_delay_t)) {
			ischeck_end = true;
			if (checkendvalue>successrate) {
				isclear = true;
				ischeck = false;
				check_t = 0.0f;
				check_delay_t = 0.0f;
				SoundM.PlaySE("fanfare.wav");
				DataM.releaseCharacter(DataM.getSelectActionName(), "release", true);
				DataM.WriteImage(playercanvas.getSurface(), DataM.getSelectActionName());
			}
			else {
				SoundM.PlaySE("cancel.wav");
				check_t = 0.0f;
				check_delay_t = 0.0f;
				ischeck = false;
				isclear = false;
			}
		}
	}
}

void Draw::drawTutorialButton()
{
	Vec2f pos = Vec2f(1450,70);
	Vec2f size = Vec2f(130, 130);
	DrawM.drawTextureBox(pos,size*(0.95f+0.05f*sin(tutorialsinangle)), 0.0f, TextureM.getTexture("UI/Button/help.png"));
}

void Draw::drawTutorialTextures()
{
	if (tutorialcount >= 1) {
		Vec2f pos = Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f;
		Vec2f size=Vec2f(1000,700);
		DrawM.drawBoxEdge(Vec2f(0, 0), Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT), ColorA(0, 0, 0, 0.5f));
		DrawM.drawTextureBox(pos, size, 0.0f, tutorialtextures[tutorialcount - 1]);
	}
}

void Draw::CreateAssets()
{
	CreateSound();
	CreateTexture();
}

void Draw::CreateSound()
{
	SoundM.CreateSE("result.wav");
	SoundM.CreateSE("fanfare.wav");
	SoundM.CreateSE("cancel.wav");
}

void Draw::CreateTexture()
{
	tutorialtextures.push_back(TextureM.CreateTexture("UI/Button/helpmane.png"));
	tutorialtextures.push_back(TextureM.CreateTexture("UI/Button/helpIro.png"));
	tutorialtextures.push_back(TextureM.CreateTexture("UI/Button/helpcheck.png"));
	TextureM.CreateTexture("UI/canvas.png");
	TextureM.CreateTexture("UI/nuriemode.png");
	TextureM.CreateTexture("UI/book.png");
	TextureM.CreateTexture("UI/bar.png");
	TextureM.CreateTexture("UI/hpbarframe.png");
	TextureM.CreateTexture("UI/hpbarframebase.png");
	TextureM.CreateTexture("UI/mausudesousasitene.png");
	TextureM.CreateTexture("UI/Button/click_ui.png");
	TextureM.CreateTexture("UI/Button/help.png");
	TextureM.CreateTexture("UI/informationreleasefolm.png");
	TextureM.CreateTexture("Draw/" + DataM.getSelectActionName() + "/" + DataM.getSelectActionName() + "color.png");
	TextureM.CreateTexture("Draw/white.png");
	gl::Texture effecttex = TextureM.getTexture(characterplaypath);
	gl::Texture effecttex2 = TextureM.getTexture("Draw/white.png");
	framepath = "Draw/frame.png";
	characterframepath = "Draw/" + charactername + "/frame.png";
	charactercoloredpath = "Draw/" + charactername + "/" + charactername + "color.png";
	characterplaypath = "Draw/" + charactername + "/" + "default.png";
	TextureM.CreateTexture(framepath);

	TextureM.CreateTexture(charactercoloredpath);
	TextureM.CreateTexture(characterplaypath);
}

