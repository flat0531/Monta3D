#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include<memory>
#include<list>
#include"../WorldObject/ItemObject.h"
#include"cinder\Camera.h"
class CharacterManager;
class EffectManager;
class BulletManager;
class ItemManager {
public:
	ItemManager();
	void update(const ci::CameraPersp& camera);
	void draw();
	void CreateItem(int worldnum,int stagenum,int floornum);
	ItemManager* getThisPointer() {
		return this;
	}
	std::vector<ItemObject> getIteObjects();
	void SetCharacterManagerPtr(CharacterManager* charactermanager);
	void SetBulletManagerPtr(BulletManager* bulletmanager);
	void SetEffectManagerPtr(EffectManager*  effectmanager);

	void ItemInit();
	void saveItems(int worldnum, int stagenum);
	std::vector<bool>& const isGetItem();
private:
	CharacterManager* charactermanagerptr;
	EffectManager* effectmanagerptr;
	BulletManager* bulletmanagerptr;
	void CollisionItemToPlayer(const ci::CameraPersp& camera);
	void CollisionItemToBullet(const ci::CameraPersp& camera);
	std::vector<bool>isgetitem;
	std::vector<ItemObject>itemobjects;
};
