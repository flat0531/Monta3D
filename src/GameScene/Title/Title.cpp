#include "Title.h"
#include"../../Top/Top.h"
#include"../CourseEditer/CourseEditer.h"
#include"../Draw/Draw.h"
#include"../../Input/KeyManager.h"
#include"../../Scene/SceneManager.h"
#include"../../Top/SoundManager.h"
#include"../../Top/DrawManager.h"
#include"../../Top/TextureManager.h"
#include"../EffectEdit/EffectEdit.h"
#include"../../WorldCreater/MapManager.h"
#include"../../Top/MyJson.h"
#include"cinder\Rand.h"
#include"../../Top/FadeManager.h"
#include"../GameMain/GameMain.h"
#include"../StageSelect/StageSelect.h"
using namespace ci;
using namespace ci::app;
void Title::setup()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
		60.0f,
		0.1f, 1000.0f);
	camera.setEyePoint(Vec3f(0, 0, -5));
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000));
	ortho = CameraOrtho(0, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0,
		1, 101);

	skyrotate = Vec3f(0, 0, 0);
	skypos = Vec3f(0,0,0);
	TextureM.CreateTexture("titlesky.png");
	//SoundM.PlayBGM("title.wav",0.5f);
	//SoundM.SetLoopTimeBGM("title.wav", 11.670, 58.266);
	CreateMap2d();
	for (int i = 0;i < testtexturenum;i++) {
		TextureM.CreateTexture("Draw/slime/slimecolorplay"+std::to_string(i)+".png");
	}
	gl::Texture effecttex = TextureM.CreateTexture("Draw/slime/slimecolorplay0.png");
	surfaceeffect= SurfaceEffect(effecttex, effecttex.getSize() / 7.f, effecttex.getSize()*(1.f - (1.f / 7.f)),
		Vec3f(-6.9, 2, 9.85), Vec3f(0, 8, 8), Vec3f(90, 15, -50),
		EasingManager::EasType::Linear, EasingManager::EasType::Return, 70.f,
		-M_PI / 4.f, 0.0f, 0.2f, effecttex.getSize().x*0.4f*1.414f, 2.0f);

	gl::Texture backeefect= TextureM.CreateTexture("Draw/white.png");
	backsurface = SurfaceEffect(backeefect, backeefect.getSize() / 7.f, backeefect.getSize()*(1.f - (1.f / 7.f)),
		Vec3f(-6.9, 2, 9.9), Vec3f(0, 8, 8), Vec3f(90, 15, -50),
		EasingManager::EasType::Linear, EasingManager::EasType::Return, 70.f,
		-M_PI / 4.f, 0.0f, 0.2f, backeefect.getSize().x*0.4f*1.414f, 2.0f,0.0f,ColorA(0,1,0,0.5f));

	gl::Texture frameeffect = TextureM.CreateTexture("Draw/slime/slimeframe.png");
	framesurface = SurfaceEffect(frameeffect, frameeffect.getSize() / 7.f, frameeffect.getSize()*(1.f - (1.f / 7.f)),
		Vec3f(-6.9, 2, 9.8), Vec3f(0, 8, 8), Vec3f(90, 15, -50),
		EasingManager::EasType::Linear, EasingManager::EasType::Return, 70.f,
		-M_PI / 4.f, 0.0f, 0.2f, frameeffect.getSize().x*0.4f*1.414f, 2.0f);
	delaycount = 0;
}

void Title::update()
{
	updateSky();
	for (auto& itr : map2d) {
		itr.update();
	}
	for (auto& itr : map2dfront) {
		itr.update();
	}
	surfaceeffect.update();
	backsurface.update();
	framesurface.update();
	if (surfaceeffect.isEnd()) {
		delaycount++;
		if (delaycount >= delay) {
			surfaceeffect.setIs(!surfaceeffect.getIsUp());
			backsurface.setIs(!backsurface.getIsUp());
			framesurface.setIs(!framesurface.getIsUp());
			if (surfaceeffect.getIsUp()) {
				testtexturecount++;
				testtexturecount = testtexturecount%testtexturenum;
				backsurface.ChangeColor(ColorA(randFloat(0.0f,1.0f), randFloat(0.0f, 1.0f), randFloat(0.0f, 1.0f),0.3f));
				surfaceeffect.ChangeTexture(TextureM.getTexture("Draw/slime/slimecolorplay" + std::to_string(testtexturecount)+".png"));
				backsurface.ChangeTexture(TextureM.getTexture("Draw/white.png"));
				framesurface.ChangeTexture(TextureM.getTexture("Draw/slime/slimeframe.png"));
			}
			delaycount = 0;
		}
		
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_g)&&(!FadeM.getIsFading())) {
		FadeM.StartFadeIn();
	}
}

void Title::draw()
{
	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

	gl::setMatrices(camera);
	gl::pushModelView();
	
	drawSky();
	drawmap2d();
	backsurface.draw();
	surfaceeffect.draw();
	framesurface.draw();
	drawmap2dFront();
	gl::popModelView();
}

void Title::draw2D()
{
	gl::setMatrices(ortho);
	gl::pushModelView();


	gl::popModelView();
}

void Title::shift()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_c)) {
		//SoundM.eraseBGM("title.wav");
		SceneManager::createScene(CourseEditer());
	}
	if (FadeM.getIsfadeinEnd()) {
		//SoundM.eraseBGM("title.wav");
		SceneManager::createScene(StageSelect());
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_q)) {
		//SoundM.eraseBGM("title.wav");
		SceneManager::createScene(Draw());
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_e)) {
		//SoundM.eraseBGM("title.wav");
		SceneManager::createScene(EffectEdit());
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_s)) {
		SceneManager::createScene(StageSelect());
	}
}

void Title::updateSky()
{

}

void Title::drawSky()
{
	Vec3f pos = Vec3f(0, 0, 95);
	Vec3f size = Vec3f(205,205 * float(WINDOW_HEIGHT) / float(WINDOW_WIDTH), 1);
	Vec3f rotate(0,0,180);
	DrawM.drawTextureCube(pos, size, rotate,TextureM.getTexture("titlesky.png"),ColorA(1,1,1,1));
}

void Title::CreateMap2d()
{
	std::string path = "Json/Title/";
	JsonTree map2djson(loadAsset(path + "map2d.json"));
	for (int i = 0;i < map2djson.getNumChildren();i++) {
		JsonTree childmap2d = map2djson.getChild(i);
		Vec3f pos = MyJson::getJson().getVec3(childmap2d, "pos");
		Vec3f scale = MyJson::getJson().getVec3(childmap2d, "scale");
		Vec3f rotate = MyJson::getJson().getVec3(childmap2d, "rotate");
		ColorA color = MyJson::getJson().getColor(childmap2d, "color");
		std::string texturepath = childmap2d.getValueForKey<std::string>("texture");
		bool isfront = childmap2d.getValueForKey<bool>("front");

		if (!isfront) {
			map2d.push_back(Map2d(pos, scale, rotate, color, texturepath));
			if (childmap2d.hasChild("trancerate")) {
				Vec3f trancerate = MyJson::getJson().getVec3(childmap2d, "trancerate");
				map2d[map2d.size() - 1].setuptrancerate(trancerate);
			}
			if (childmap2d.hasChild("isrotate")) {
				Vec3f rotation = MyJson::getJson().getVec3(childmap2d, "isrotate");
				map2d[map2d.size() - 1].setupRotate(rotation);
			}
			if (childmap2d.hasChild("circle")) {
				Vec3f circle = MyJson::getJson().getVec3(childmap2d, "circle");
				map2d[map2d.size() - 1].setupCircle(Vec2f(circle.x, circle.y), circle.z);
			}
			if (childmap2d.hasChild("returnrotate")) {
				auto value = childmap2d["returnrotate"];
				Vec3f centerpos;
				centerpos.x = value.getValueAtIndex<float>(0);
				centerpos.y = value.getValueAtIndex<float>(1);
				centerpos.z = value.getValueAtIndex<float>(2);
				float maxrotate = value.getValueAtIndex<float>(3);
				float rotatespeed = value.getValueAtIndex<float>(4);
				float startrotate = value.getValueAtIndex<float>(5);
				map2d[map2d.size() - 1].setupRotateReturn(centerpos, maxrotate, rotatespeed,startrotate);
			}
		}
		else {
			map2dfront.push_back(Map2d(pos, scale, rotate, color, texturepath));
			if (childmap2d.hasChild("trancerate")) {
				Vec3f trancerate = MyJson::getJson().getVec3(childmap2d, "trancerate");
				map2dfront[map2dfront.size()-1].setuptrancerate(trancerate);
			}
			if (childmap2d.hasChild("isrotate")) {
				Vec3f rotation = MyJson::getJson().getVec3(childmap2d, "isrotate");
				map2dfront[map2dfront.size() - 1].setupRotate(rotation);
			}
			if (childmap2d.hasChild("circle")) {
				Vec3f circle = MyJson::getJson().getVec3(childmap2d, "circle");
				map2dfront[map2dfront.size() - 1].setupCircle(Vec2f(circle.x, circle.y), circle.z);
			}
			if (childmap2d.hasChild("returnrotate")) {
				auto value = childmap2d["returnrotate"];
				Vec3f centerpos;
				centerpos.x = value.getValueAtIndex<float>(0);
				centerpos.y = value.getValueAtIndex<float>(1);
				centerpos.z = value.getValueAtIndex<float>(2);
				float maxrotate= value.getValueAtIndex<float>(3);
				float rotatespeed = value.getValueAtIndex<float>(4);
				float startrotate = value.getValueAtIndex<float>(5);
				map2dfront[map2dfront.size() - 1].setupRotateReturn(centerpos, maxrotate,rotatespeed,startrotate);
			}
		}
	}
}

void Title::drawmap2d()
{
	for (auto itr : map2d) {
		itr.draw();
	}
}

void Title::drawmap2dFront()
{
	for (auto itr : map2dfront) {
		itr.draw();
	}
}
