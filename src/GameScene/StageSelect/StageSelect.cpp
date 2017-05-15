#include "StageSelect.h"
#include"../../Top/Top.h"
#include"../../Scene/SceneManager.h"
#include"../../Top/DrawManager.h"
#include"../../Input/KeyManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../Top/TextureManager.h"
#include"../../Top/MyJson.h"
#include"../../Top/SoundManager.h"
#include"../../Top/FadeManager.h"
using namespace ci;
using namespace ci::app;

void StageSelect::setup()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
		60.0f,
		1.0f, 1000.f);
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000));
	camera.setEyePoint(Vec3f(0, 0, -5));
	ortho = CameraOrtho(0, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0,
		1, 101);
	backgroundpath = "UI/world1.png";
	TextureM.CreateTexture(backgroundpath);
	TextureM.CreateTexture("UI/stageselect.png");
	TextureM.CreateTexture("UI/montaicon.png");
	TextureM.CreateTexture("UI/moveicon1.png");
	TextureM.CreateTexture("UI/moveicon2.png");
	SoundM.CreateSE("stagecursor.wav");
	SoundM.CreateSE("moveicon.wav");
	SoundM.PlayBGM("stageselectworld1.wav",0.3f);
	SoundM.SetLoopBGM("stageselectworld1.wav", true);
	stagenum = 1;
	worldnum = 1;
	isiconmoving = false;
	icon_move_t = 1.0f;
	is_move_to_next = false;
	is_move_to_back = false;
	roadStageData();
	createpointRoads();
	createStageIcon();
	playericonpos = stagepos[stagenum - 1];
	animation_count = 0;
	stagenameplate = StageNamePlate(worldnum, stagenum, stagedatas[stagenum - 1]);
	FadeM.StartFadeOut(false);
	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void StageSelect::update()
{
	Vec2f buffplayericonpos = playericonpos;
	for (auto& it : pointroads) {
		it.update();
	}
	for (auto&it : stageicons) {
		it.update(isiconmoving,stagenum);
	}

	selectStage();
	updatePlayerIcon();
	stagenameplate.update();


	playericonspeed = buffplayericonpos - playericonpos;
	animation_count++;
}

void StageSelect::draw()
{
	camera.setEyePoint(Vec3f(0, 0, -5));
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000));

	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

	gl::setMatrices(camera);

}

void StageSelect::draw2D()
{
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	gl::setMatrices(ortho);

	drawBackGround();
	drawTitle();
	
	for (auto it : pointroads) {
		it.draw();
	}

	drawStageIcon();
	drawPlayerIcon();
	stagenameplate.draw();

}

void StageSelect::shift()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_t)) {
		SceneManager::createScene(Title());
	}
}

void StageSelect::drawBackGround()
{
	DrawM.drawTextureBoxEdge(Vec2f(0, 0), WINDOWSIZE, TextureM.getTexture(backgroundpath));
}

void StageSelect::createpointRoads()
{
	std::string path = "Json/StageSelect/World" + std::to_string(worldnum);
	JsonTree roadpos(loadAsset(path + "/stagepos.json"));
	for (int i = 0;i < roadpos.getNumChildren();i++) {
		if (i == 0) {

		}
		else {
			if (!stagedatas[i - 1].getIsClear())break;
		}
	
		JsonTree child = roadpos.getChild(i);
		Vec2f pos = JsonM.getVec2(child, "pos");
		if (child.hasChild("easingtype")) {
			Vec2i easigtype = JsonM.getVec2(child, "easingtype");
			easingtypes.push_back(Vec2i(easigtype));
		}
		stagepos.push_back(Vec2f(pos));
	
	}
	for (int i = 0;i < (stagepos.size()-1);i++) {
		if (!stagedatas[i].getIsClear())break;
		pointroads.push_back(PointRoad(stagepos[i], stagepos[i+1],
			(EasingManager::EasType)easingtypes[i].x, (EasingManager::EasType)easingtypes[i].y));
	}
	//pointroads.push_back(PointRoad(Vec2f(100, 700), Vec2f(1100, 200),
	//	EasingManager::EasType::Linear, EasingManager::EasType::Linear));
}

void StageSelect::createStageIcon()
{
	std::string path = "Json/StageSelect/World" + std::to_string(worldnum);
	JsonTree stageicon(loadAsset(path + "/stagepos.json"));
	std::vector<ColorA> colors;
	std::vector<Vec2f>size;
	for (int i = 0;i < stageicon.getNumChildren();i++) {
		JsonTree child = stageicon.getChild(i);
		colors.push_back(JsonM.getColor(child,"color"));
		size.push_back(JsonM.getVec2(child, "size"));
		
	}
	for (int i = 0;i < stagepos.size();i++) {
		stageicons.push_back(StageIcon(stagepos[i], size[i], colors[i], stagedatas[i].getIsClear(), i + 1));
	}
}

void StageSelect::drawStageIcon()
{
	for (auto it :stageicons) {
		it.draw();
	}
}

void StageSelect::roadStageData()
{
	std::string path = "SaveData/StageSelect/World" + std::to_string(worldnum);
	JsonTree savedata(loadAsset(path + "/save.json"));
	for (int i = 0;i <savedata.getNumChildren();i++) {
		JsonTree child = savedata.getChild(i);
		bool isclear= child.getValueForKey<bool>("isclear");
		std::vector<bool>isgetitem;
		if (child.hasChild("getitem")) {
			JsonTree item = child.getChild("getitem");
			for (int i = 0;i < item.getNumChildren();i++) {
				isgetitem.push_back(item.getValueAtIndex<bool>(i));
			}
		}
		stagedatas.push_back(StageData(isclear,isgetitem));
		isgetitem.clear();
	}
}

void StageSelect::drawTitle()
{
	Vec2f pos=Vec2f(290,110);
	Vec2f size = Vec2f(500,250);
	DrawM.drawTextureBox(pos,size,0,TextureM.getTexture("UI/stageselect.png"));
}

void StageSelect::selectStage()
{
	if (FadeM.getIsFading())return;
	if (isiconmoving)return;//
	if (KeyManager::getkey().isPush(KeyEvent::KEY_d)&&(!(stagenum == stagepos.size()))) {
		easing_icon_beginpos = playericonpos;
		easing_icon_endpos = stagepos[stagenum];
		stagenum++;
		isiconmoving = true;
		is_move_to_next = true;
		icon_move_t = 0.0f;
		SoundM.PlaySE("moveicon.wav",0.5f);
		stagenameplate.SlideOut(worldnum,stagenum);
		return;
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_a) && (!(stagenum == 1))) {
		easing_icon_endpos = playericonpos;
		easing_icon_beginpos = stagepos[stagenum-2];
		stagenum--;
		isiconmoving = true;
		is_move_to_back = true;
		icon_move_t = 1.0f;
		stagenameplate.SlideOut(worldnum,stagenum);
		SoundM.PlaySE("moveicon.wav", 0.5f);
		return;
	}
}

void StageSelect::updatePlayerIcon()
{
	if (!isiconmoving)return;
	float easingtime = 1.3f;
	float slidein_time_t = 0.7f;
	if (is_move_to_next) {
		if (!EasingManager::tCountEnd(icon_move_t)) {
			EasingManager::tCount(icon_move_t, easingtime);
			playericonpos.x = EasingManager::getEas[EasingManager::EasType(easingtypes[stagenum - 2].x)](icon_move_t, easing_icon_beginpos.x, easing_icon_endpos.x);
			playericonpos.y = EasingManager::getEas[EasingManager::EasType(easingtypes[stagenum - 2].y)](icon_move_t, easing_icon_beginpos.y, easing_icon_endpos.y);
		}
		else {
			isiconmoving = false;
			is_move_to_next = false;
			SoundM.PlaySE("stagecursor.wav",0.5f);
			stagenameplate.SlideIn(worldnum, stagenum, stagedatas[stagenum - 1]);
		}
	}
	if (is_move_to_back) {
		if (!EasingManager::tCountEnd(icon_move_t,false)) {
			EasingManager::tCount(icon_move_t, -easingtime);
			playericonpos.x = EasingManager::getEas[EasingManager::EasType(easingtypes[stagenum - 1].x)](icon_move_t, easing_icon_beginpos.x, easing_icon_endpos.x);
			playericonpos.y = EasingManager::getEas[EasingManager::EasType(easingtypes[stagenum - 1].y)](icon_move_t, easing_icon_beginpos.y, easing_icon_endpos.y);
		}
		else {
			isiconmoving = false;
			is_move_to_back = false;
			SoundM.PlaySE("stagecursor.wav", 0.5f);
			stagenameplate.SlideIn(worldnum, stagenum, stagedatas[stagenum - 1]);
		}
	}
}

void StageSelect::drawPlayerIcon()
{
	if (!isiconmoving) {
		DrawM.drawTextureBox(playericonpos, Vec2f(65, 65), 0.f,
			TextureM.getTexture("UI/montaicon.png"), ColorA(1, 1, 1, 1));
		return;
	}
	int animationspeed = 10;
	int direction = 1;
	if (playericonspeed.x >= 0)direction = -1;//アイコンが右に進んでいれば逆向きに描画
	std::string texturepath = "UI/moveicon" + std::to_string(((animation_count / animationspeed) % 2) + 1) + ".png";
	DrawM.drawTextureBox(playericonpos, Vec2f(65*direction, 65), 0.f,
		TextureM.getTexture(texturepath), ColorA(1, 1, 1, 1));
}
