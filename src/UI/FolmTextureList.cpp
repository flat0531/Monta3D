#include "FolmTextureList.h"
#include"../Top/MyJson.h"
#include"../Top/Top.h"
#include"../Top/FadeManager.h"
#include"../Input/KeyManager.h"
#include"../Top/TextureManager.h"
#include"../Top/DrawManager.h"
#include"../Top/DataManager.h"
#include"../Top/SoundManager.h"
#include <filesystem>
using namespace ci;
using namespace ci::app;
FolmTextureList::FolmTextureList()
{
	CreateFolmTextures();
	CreatePlayTextures();
	cursortex = TextureM.CreateTexture("UI/uzu.png");
	SoundM.CreateSE("stagecursor.wav");
	
}

void FolmTextureList::update()
{
	selectFolm();
}

void FolmTextureList::draw()
{
	for (int i = 0;i < folmtextures.size();i++) {
		folmtextures[i]->draw(Vec2f(0,0));
	}
	for (int i = 0;i < playtextures.size();i++) {
		playtextures[i]->draw();
	}
	drawCursor();
}

void FolmTextureList::CreateFolmTextures()
{
	std::string path = "SaveData/Folm/releasefolm.json";
	JsonTree folm(loadAsset(path));
	for (int i = 0;i < folm.getNumChildren();i++) {
		JsonTree child = folm.getChild(i);
		if (child.getValueForKey<bool>("candraw")) {
			folmtextures.push_back(std::make_shared<FolmTexture>
				(Vec2f(200 + 230.f*((folmtextures.size()) % 3), WINDOW_HEIGHT / 3.f + 230.f*((folmtextures.size()) / 3)), child.getValueForKey<std::string>("name"),
					child.getValueForKey<bool>("release"), folmtextures.size()));
		}
	}
}


void FolmTextureList::CreatePlayTextures()
{
	playtextures.clear();
	int createnum = 0;
	std::string name = folmtextures[selectnum]->getName();
	for (std::tr2::sys::directory_iterator it(app::getAssetPath("Texture/UserPlay/" + name).string()), end; it != end; it++)
	{
		createnum++;
	}
	for (int i = 0;i < createnum;i++) {
		Vec2f size = Vec2f(175, 175);
		Vec2f pos = Vec2f(900 + i % 4 * size.x, 115 + i / 4 * size.y);
		std::string path = "UserPlay/" + name + "/play" + std::to_string(i + 1) + ".png";
		playtextures.push_back(std::make_shared<FolmScenePlayTexture>(pos, size, path,name));
	}
}

bool FolmTextureList::getIsrelease()
{
	return folmtextures[selectnum]->getIsRelease();
}

void FolmTextureList::selectFolm()
{
	if (!FadeM.getIsFading()) {
		if (KeyManager::getkey().isPush(KeyEvent::KEY_a)&&(!((selectnum%3)==0))) {
			selectnum--;
			SoundM.PlaySE("stagecursor.wav");
			DataM.setSelectActionName(folmtextures[selectnum]->getName());
			CreatePlayTextures();
		}
		if (KeyManager::getkey().isPush(KeyEvent::KEY_d) && (!((selectnum % 3) == 2))&& (selectnum + 1) <= (int(folmtextures.size() - 1))) {
			selectnum++;
			SoundM.PlaySE("stagecursor.wav");
			DataM.setSelectActionName(folmtextures[selectnum]->getName());
			CreatePlayTextures();
		}
		if (KeyManager::getkey().isPush(KeyEvent::KEY_w) && ((selectnum - 3) >= 0)) {
			selectnum -= 3;
			SoundM.PlaySE("stagecursor.wav");
			DataM.setSelectActionName(folmtextures[selectnum]->getName());
			CreatePlayTextures();
		}
		if (KeyManager::getkey().isPush(KeyEvent::KEY_s) && (selectnum +3)<= (int(folmtextures.size()-1))) {
			selectnum += 3;
			SoundM.PlaySE("stagecursor.wav");
			DataM.setSelectActionName(folmtextures[selectnum]->getName());
			CreatePlayTextures();
		}
	}
}

void FolmTextureList::drawCursor()
{
	DrawM.drawTextureBox(folmtextures[selectnum]->getPos() + Vec2f(0, 50), Vec2f(100, 100), 0.0f, cursortex, ColorA(1, 1, 1, 1));
}
