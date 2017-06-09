#include "ItemManager.h"
#include"CharacterManager.h"
#include"EffectManager.h"
#include"BulletManager.h"
#include"../WorldObject/Bullet/BulletBase.h"
#include"../Top/CollisionManager.h"
#include"../Top/MyJson.h"
#include"../Top/Top.h"
#include"../Top/DataManager.h"
#include"../WorldObject/Player.h"
#include"../WorldObject/Effect/EffectItem.h"
using namespace ci;
using namespace ci::app;
ItemManager::ItemManager()
{
	ItemInit();
}

void ItemManager::update(const ci::CameraPersp & camera)
{
	for (auto& it : itemobjects) {
		it.update();
	}
	CollisionItemToPlayer(camera);
	CollisionItemToBullet(camera);
}


void ItemManager::draw()
{
	for (auto it : itemobjects) {
		it.draw();
	}
}

void ItemManager::CreateItem(int worldnum, int stagenum, int floornum)
{
	itemobjects.clear();
	for (int i = 0;i < isgetitem.size();i++) {
		if (isgetitem[i])continue;
		std::string path = "Json/StageSelect/World" + std::to_string(worldnum) + "/stage"+std::to_string(stagenum)+ "item.json";
		JsonTree item(loadAsset(path));
		JsonTree child = item.getChild(i);
		int floor = child.getValueForKey<int>("floor");
		if (floornum == floor) {
			Vec3f pos = JsonM.getVec3(child,"pos");
			Vec3f scale = Vec3f(1, 1, 1)*WorldScale;
			std::string itemtype = child.getValueForKey<std::string>("type");
			std::string name = child.getValueForKey<std::string>("name");
			itemobjects.push_back(ItemObject(pos*WorldScale, scale, i, itemtype, name));
		}
	}
}

std::vector<ItemObject> ItemManager::getIteObjects()
{
	return itemobjects;
}

void ItemManager::SetCharacterManagerPtr(CharacterManager * charactermanager)
{
	charactermanagerptr = charactermanager;
}

void ItemManager::SetBulletManagerPtr(BulletManager * bulletmanager)
{
	bulletmanagerptr = bulletmanager;
}

void ItemManager::SetEffectManagerPtr(EffectManager * effectmanager)
{
	effectmanagerptr = effectmanager;
}

void ItemManager::ItemInit()
{
	isgetitem = DataM.getItems();
	
}

void ItemManager::saveItems(int worldnum, int stagenum)
{
	for (int i = 0;i < DataM.getItems().size();i++) {
		if (DataM.getItems()[i])continue;
		if (!isgetitem[i])continue;

		std::string path = "Json/StageSelect/World" + std::to_string(worldnum) + "/stage" + std::to_string(stagenum) + "item.json";
		JsonTree item(loadAsset(path));
		JsonTree child = item.getChild(i);
		std::string type = child.getValueForKey<std::string>("type");
		std::string name = child.getValueForKey<std::string>("name");
		if (type == "color") {
			DataM.saveColorRelease(name, true);
			continue;
		}
		if (type == "folm") {
			DataM.releaseCharacter(name, "candraw", true);
			continue;
		}
	}
	DataM.saveGetItems(worldnum, stagenum, isgetitem);
}

std::vector<bool>& const ItemManager::isGetItem()
{
	return isgetitem;
}

void ItemManager::CollisionItemToPlayer(const ci::CameraPersp & camera)
{
	Vec3f playerpos = charactermanagerptr->getPlayer()->getPos();
	Vec3f playersize = charactermanagerptr->getPlayer()->getScale();
	for (int i = 0;i < itemobjects.size();i++) {
		if (itemobjects[i].getIsGet())continue;
		if (CollisionM.isSphereSphere(playerpos, itemobjects[i].getPos(),
			playersize.x / 2.f, itemobjects[i].getScale().x / 2.f)) {

			itemobjects[i].setIsGet(true);
			isgetitem[itemobjects[i].getNumber()] = true;

			Vec2f pos = camera.worldToScreen(itemobjects[i].getPos(),
				WINDOW_WIDTH, WINDOW_HEIGHT);
			Vec2f endpos = Vec2f(1400, 800);
			Vec2f iconsize = Vec2f(75, 75);
			float rate = 1.3f;
			float trancex = -(float(isgetitem.size()))*(iconsize.x / 2.f)*rate + iconsize.x / 2.f*rate + itemobjects[i].getNumber()*iconsize.x*rate;
			effectmanagerptr->CreateEffect2D(EffectItem(pos,endpos+Vec2f(trancex,0),iconsize));
		}
	}
}

void ItemManager::CollisionItemToBullet(const ci::CameraPersp & camera)
{

	for (int i = 0;i < itemobjects.size();i++) {
		if (itemobjects[i].getIsGet())continue;

		for (auto it : bulletmanagerptr->getPlayerBullets()) {
			if (CollisionM.isSphereSphere(it->getPos(), itemobjects[i].getPos(), it->getScale().x / 2.f, itemobjects[i].getScale().x / 2.f)) {
				itemobjects[i].setIsGet(true);
				isgetitem[itemobjects[i].getNumber()] = true;

				Vec2f pos = camera.worldToScreen(itemobjects[i].getPos(),
					WINDOW_WIDTH, WINDOW_HEIGHT);
				Vec2f endpos = Vec2f(1400, 800);
				Vec2f iconsize = Vec2f(75, 75);
				float rate = 1.3f;
				float trancex = -(float(isgetitem.size()))*(iconsize.x / 2.f)*rate + iconsize.x / 2.f*rate + itemobjects[i].getNumber()*iconsize.x*rate;
				effectmanagerptr->CreateEffect2D(EffectItem(pos, endpos + Vec2f(trancex, 0), iconsize));
			}
		}
	}
}
