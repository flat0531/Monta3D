#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"../Top/Top.h"
#include "MapChipManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldCreater/EffectManager.h"
#include"../WorldObject/Bullet/BulletBase.h"
#include"../WorldObject/MapChip/HitBox.h"
#include"../WorldObject/MapChip/MapChipNone.h"
#include"../WorldObject/MapChip/MapChipType.h"
#include"../WorldObject/MapChip/MapChipBase.h"
#include"../WorldObject/MapChip/MapChipNormal.h"
#include"../WorldObject/MapChip/MapChipNormalNotDraw.h"
#include"../WorldObject/MapChip/MapChipHalfFloor.h"
#include"../WorldObject/MapChip/MapChipGoal.h"
#include"../WorldObject/MapChip/MapChipBreak.h"
#include"../WorldObject/MapChip/MapChipApple.h"
#include"../Top/CollisionManager.h"
#include"../Top/TextureManager.h"
#include"../Top/SoundManager.h"

using namespace ci;
using namespace ci::app;
MapChipManager::MapChipManager()
{
	TextureM.CreateTexture("Map/normalbox.png");
	TextureM.CreateTexture("Map/hulffloor.png");
	TextureM.CreateTexture("Map/renga.png");
	SoundM.CreateSE("onground.wav");
}

void MapChipManager::setup(const int worldnum, const int stagenum, const int floornum)
{
	CreateMap(worldnum, stagenum, floornum, 0);
}



void MapChipManager::update()
{
	updateMapChip();
	CollisionPlayerToMap();
	CollisionEnemysToMap();
	CollisionPlayerBulletToMap();
	CollisionEnemyBulletToMap();

}

void MapChipManager::draw()
{
	int hitscalex = 25;
	int hitscaley = 10;
	int WorldScaleInt = int(WorldScale);
	int collision_pos_y = (int(characterManagerptr->getPlayer()->getPos2f().y) / WorldScaleInt);
	int collision_pos_x = (int(-(characterManagerptr->getPlayer()->getPos2f().x)) / WorldScaleInt);

	for (int y = collision_pos_y - hitscaley;
	y <= collision_pos_y + hitscaley;y++) {
		if ((y < 0) || y >= mapchips.size())continue;
		for (int x = collision_pos_x - hitscalex;
		x <= collision_pos_x + hitscalex;x++) {
			if ((x < 0) || x >= mapchips[y].size())continue;
			mapchips[y][x]->draw();

		}

	}
}



std::vector<std::vector<MapChipType>> MapChipManager::ReadData(const int worldnum, const int stagenum, const int floornum, const int zvalue)
{
	std::vector<std::vector<MapChipType>>read_map_datas;
	std::ifstream savefile(getAssetPath(getPath(worldnum,stagenum,floornum) + "mapfront.txt").string());
	int x_size;
	int y_size;
	savefile >> x_size;
	savefile >> y_size;

	for (int y = 0;y < y_size;y++) {
		std::vector<MapChipType>x_chips;
		for (int x = 0;x < x_size;x++) {
			int maptypebuf;
			savefile >> maptypebuf;
			x_chips.push_back(MapChipType(maptypebuf));
			if (x == (x_size - 1)) {
				read_map_datas.push_back(x_chips);
				x_chips.clear();
				x_chips.shrink_to_fit();
			}

		}
	}
	return read_map_datas;
}

void MapChipManager::setBulletManagerPointer(BulletManager * _bulletmanager)
{
	bulletmanagerptr = _bulletmanager;
}

void MapChipManager::setCharacterManagerPointer(CharacterManager * _characterManager)
{
	characterManagerptr = _characterManager;
}

void MapChipManager::setEffectManagerPointer(EffectManager* _effectmanager)
{
	effectmanagerptr = _effectmanager;
}

void MapChipManager::CreateMap(const int worldnum, const int stagenum, const int floornum, const int zvalue)
{
	mapchips.clear();
	std::vector<std::vector<MapChipType>> mapdata = ReadData(worldnum, stagenum, floornum, zvalue);

	for (int y = mapdata.size() - 1;y >= 0;y--) {
		std::vector<std::shared_ptr<MapChipBase>>buf;
		for (int x = 0;x < mapdata[y].size();x++) {
			switch (mapdata[y][x])
			{
			case MapChipType::NONE_CHIP:
				buf.push_back(std::make_shared<MapChipNone>
					(Vec3f(-x, (mapdata.size() - (y + 1)), zvalue)*WorldScale, Vec3f(1, 1, 1)*WorldScale));
				break;
			case MapChipType::NORMAL_CHIP:
				buf.push_back(std::make_shared<MapChipNormal>
					(Vec3f(-x, (mapdata.size() - (y + 1)), zvalue)*WorldScale, Vec3f(1, 1, 1)*WorldScale,effectmanagerptr));
				break;
			case MapChipType::NORMAL_NOTDRAW_CHIP:
				buf.push_back(std::make_shared<MapChipNormalNotDraw>
					(Vec3f(-x, (mapdata.size() - (y + 1)), zvalue)*WorldScale, Vec3f(1, 1, 1)*WorldScale, effectmanagerptr));
				break;
			case MapChipType::Half_FLOOR_CHIP:
				buf.push_back(std::make_shared<MapChipHalfFloor>
					(Vec3f(-x, (mapdata.size() - (y + 1)), zvalue)*WorldScale, Vec3f(1, 1, 1)*WorldScale));
				break;
			case MapChipType::GOAL_CHIP:
				buf.push_back(std::make_shared<MapChipGoal>
					(Vec3f(-x, (mapdata.size() - (y + 1)), zvalue)*WorldScale, Vec3f(1, 1, 1)*WorldScale, goal));
				break;
			case MapChipType::BREAK_CHIP:
				buf.push_back(std::make_shared<MapChipBreak>
					(Vec3f(-x, (mapdata.size() - (y + 1)), zvalue)*WorldScale, Vec3f(1, 1, 1)*WorldScale,effectmanagerptr));
				break;
			case MapChipType::APPLE_CHIP:
				buf.push_back(std::make_shared<MapChipApple>
					(Vec3f(-x, (mapdata.size() - (y + 1)), zvalue)*WorldScale, Vec3f(1, 1, 1)*WorldScale));
				break;
			default:
				break;
			}
		}
		mapchips.push_back(std::move(buf));
		buf.clear();
	}
}

ci::Vec2f MapChipManager::getChipsSize()
{
	return Vec2f(mapchips[0].size(), mapchips.size());
}

void MapChipManager::setGoal(const std::function<void()> func)
{
	goal = func;
}

MapChipManager * MapChipManager::getThisPtr()
{
	return this;
}

std::vector<std::vector<std::shared_ptr<MapChipBase>>> MapChipManager::getMapChips()
{
	return mapchips;
}

void MapChipManager::updateMapChip()
{
	int hitscalex = 25;
	int hitscaley = 10;
	int WorldScaleInt = int(WorldScale);
	int collision_pos_y = (int(characterManagerptr->getPlayer()->getPos2f().y) / WorldScaleInt);
	int collision_pos_x = (int(-(characterManagerptr->getPlayer()->getPos2f().x)) / WorldScaleInt);

	for (int y = collision_pos_y - hitscaley;
	y <= collision_pos_y + hitscaley;y++) {
		if ((y < 0) || y >= mapchips.size())continue;
		for (int x = collision_pos_x - hitscalex;
		x <= collision_pos_x + hitscalex;x++) {
			if ((x < 0) || x >= mapchips[y].size())continue;
			mapchips[y][x]->update();

		}

	}
}

void MapChipManager::CollisionPlayerToMap()
{
	
	std::vector<HitBox> hitbox;
	int hitscale = 2;
	int WorldScaleInt = int(WorldScale);
	int collision_pos_y = (int(characterManagerptr->getPlayer()->getPos2f().y) / WorldScaleInt);
	int collision_pos_x = (int(-(characterManagerptr->getPlayer()->getPos2f().x)) / WorldScaleInt);

	for (int y = collision_pos_y - hitscale;
	y <= collision_pos_y + hitscale;y++) {
		if ((y < 0) || y >= mapchips.size())continue;
		for (int x = collision_pos_x - hitscale;
		x <= collision_pos_x + hitscale;x++) {
			if ((x < 0) || x >= mapchips[y].size())continue;

			if (!mapchips[y][x]->getIsCollision())continue;
			if (!mapchips[y][x]->getIsActive())continue;
			if (CollisionM.isBoxBox(characterManagerptr->getPlayer()->getPos2f(), mapchips[y][x]->getPos2f(),
				characterManagerptr->getPlayer()->getScale2f(), mapchips[y][x]->getScale2f()))
			{
				float distance = (characterManagerptr->getPlayer()->getPos().x - mapchips[y][x]->getPos2f().x)*
					(characterManagerptr->getPlayer()->getPos().x - mapchips[y][x]->getPos2f().x)
					+ (characterManagerptr->getPlayer()->getPos().y - mapchips[y][x]->getPos2f().y)*
					(characterManagerptr->getPlayer()->getPos().y - mapchips[y][x]->getPos2f().y);
				hitbox.push_back(HitBox(mapchips[y][x]->getPos2f(), mapchips[y][x]->getScale2f(), distance, mapchips[y][x]->getThisPointer()));
			}



		}

	}
	std::sort(hitbox.begin(), hitbox.end(), [&](HitBox& a, HitBox& b) {return a.getDistance() < b.getDistance();});

	for (int i = 0;i < hitbox.size();i++) {
		if (CollisionM.isBoxBox(characterManagerptr->getPlayer()->getPos2f(), hitbox[i].getPos(),
			characterManagerptr->getPlayer()->getScale2f(), hitbox[i].getSize())) {
			float angle = atan2f(characterManagerptr->getPlayer()->getPrevPos().y - hitbox[i].getPos().y,
				characterManagerptr->getPlayer()->getPrevPos().x - hitbox[i].getPos().x);
			if (angle > 2 * M_PI) {
				angle -= 2 * M_PI;
			}
			if (angle < 0) {
				angle += 2 * M_PI;
			}
			float hosei = 1.0f;
			if (angle >= (1.f / 4.f)*M_PI&&angle <= (3.f / 4.f)*M_PI) {//ã‚©‚ç“–‚½‚Á‚½ê‡
				hitbox[i].getMapChipPtr()->UpCollisionEnter(characterManagerptr->getPlayer()->getThisPointer());
			}
			if (angle >(3.f / 4.f)*M_PI&&angle < (5.f / 4.f)*M_PI) {
				hitbox[i].getMapChipPtr()->LeftCollisionEnter(characterManagerptr->getPlayer()->getThisPointer());
			}
			if (angle >= (5.f / 4.f)*M_PI&&angle <= (7.f / 4.f)*M_PI) {
				hitbox[i].getMapChipPtr()->DownCollisionEnter(characterManagerptr->getPlayer()->getThisPointer());
			}
			if ((angle >(7.f / 4.f)*M_PI&&angle < 2 * M_PI) || (angle >= 0 && angle <(1.f / 4.f)*M_PI)) {
				hitbox[i].getMapChipPtr()->RightCollisionEnter(characterManagerptr->getPlayer()->getThisPointer());
			}
			hitbox[i].getMapChipPtr()->InCollisionEnter(characterManagerptr->getPlayer()->getThisPointer());
		}
		
	
	}
	hitbox.clear();
	


}

void MapChipManager::CollisionEnemysToMap()
{
	int hitscale = 1;
	int WorldScaleInt = int(WorldScale);
	for (auto& itr : characterManagerptr->getEnemys()) {


		std::vector<HitBox> hitbox;
		
		int collision_pos_y = (int(itr->getPos2f().y) / WorldScaleInt);
		int collision_pos_x = (int(-(itr->getPos2f().x)) / WorldScaleInt);

		for (int y = collision_pos_y - hitscale;
		y <= (collision_pos_y + hitscale);y++) {
			if ((y < 0) || y >= mapchips.size())continue;
			for (int x = collision_pos_x - hitscale;
			x <= collision_pos_x + hitscale;x++) {
				if ((x < 0) || x >= mapchips[y].size())continue;

				if (!mapchips[y][x]->getIsCollision())continue;
				if (!mapchips[y][x]->getIsActive())continue;
				if (CollisionM.isBoxBox(itr->getPos2f(), mapchips[y][x]->getPos2f(),
					itr->getScale2f(), mapchips[y][x]->getScale2f()))
				{
					float distance = (itr->getPos().x - mapchips[y][x]->getPos2f().x)*
						(itr->getPos().x - mapchips[y][x]->getPos2f().x)
						+ (itr->getPos().y - mapchips[y][x]->getPos2f().y)*
						(itr->getPos().y - mapchips[y][x]->getPos2f().y);
					hitbox.push_back(HitBox(mapchips[y][x]->getPos2f(), mapchips[y][x]->getScale2f(), distance, mapchips[y][x]->getThisPointer()));
				}
			}

		}
		std::sort(hitbox.begin(), hitbox.end(), [&](HitBox& a, HitBox& b) {return a.getDistance() < b.getDistance();});

		for (int i = 0;i < hitbox.size();i++) {
			if (CollisionM.isBoxBox(itr->getPos2f(), hitbox[i].getPos(),
				itr->getScale2f(), hitbox[i].getSize())) {
				float angle = atan2f(itr->getPrevPos().y - hitbox[i].getPos().y,
					itr->getPrevPos().x - hitbox[i].getPos().x);
				if (angle > 2 * M_PI) {
					angle -= 2 * M_PI;
				}
				if (angle < 0) {
					angle += 2 * M_PI;
				}
				float hosei = 1.0f;
				if (angle >= (1.f / 4.f)*M_PI&&angle <= (3.f / 4.f)*M_PI) {//ã‚©‚ç“–‚½‚Á‚½ê‡
					hitbox[i].getMapChipPtr()->UpCollisionEnter(itr->getThisPointer());
				}
				if (angle >(3.f / 4.f)*M_PI&&angle < (5.f / 4.f)*M_PI) {
					hitbox[i].getMapChipPtr()->LeftCollisionEnter(itr->getThisPointer());
				}
				if (angle >= (5.f / 4.f)*M_PI&&angle <= (7.f / 4.f)*M_PI) {
					hitbox[i].getMapChipPtr()->DownCollisionEnter(itr->getThisPointer());
				}
				if ((angle >(7.f / 4.f)*M_PI&&angle < 2 * M_PI) || (angle >= 0 && angle <(1.f / 4.f)*M_PI)) {
					hitbox[i].getMapChipPtr()->RightCollisionEnter(itr->getThisPointer());
				}
				hitbox[i].getMapChipPtr()->InCollisionEnter(itr->getThisPointer());
			}


		}
		hitbox.clear();

	}

}

void MapChipManager::CollisionPlayerBulletToMap()
{

	int hitscale = 1;
	int WorldScaleInt = int(WorldScale);
	for (auto& itr : bulletmanagerptr->getPlayerBullets()) {


		std::vector<HitBox> hitbox;

		int collision_pos_y = (int((itr)->getPos().y) / WorldScaleInt);
		int collision_pos_x = (int(-(itr)->getPos().x) / WorldScaleInt);

		for (int y = collision_pos_y - hitscale;
		y <= (collision_pos_y + hitscale);y++) {
			if ((y < 0) || y >= mapchips.size())continue;
			for (int x = collision_pos_x - hitscale;
			x <= collision_pos_x + hitscale;x++) {
				if ((x < 0) || x >= mapchips[y].size())continue;

				if (!mapchips[y][x]->getIsCollision())continue;
				if (!mapchips[y][x]->getIsActive())continue;
				if (CollisionM.isBoxBox(Vec2f(itr->getPos().x,itr->getPos().y), mapchips[y][x]->getPos2f(),
					Vec2f(itr->getScale().x,itr->getScale().y), mapchips[y][x]->getScale2f()))
				{
					float distance = (itr->getPos().x - mapchips[y][x]->getPos2f().x)*
						(itr->getPos().x - mapchips[y][x]->getPos2f().x)
						+ (itr->getPos().y - mapchips[y][x]->getPos2f().y)*
						(itr->getPos().y - mapchips[y][x]->getPos2f().y);
					hitbox.push_back(HitBox(mapchips[y][x]->getPos2f(), mapchips[y][x]->getScale2f(), distance, mapchips[y][x]->getThisPointer()));
				}
			}

		}
		std::sort(hitbox.begin(), hitbox.end(), [&](HitBox& a, HitBox& b) {return a.getDistance() < b.getDistance();});

		for (int i = 0;i < hitbox.size();i++) {

			AxisAlignedBox3f hitbox_aabb(Vec3f(hitbox[i].getPos().x-hitbox[i].getSize().x/2.f,
				hitbox[i].getPos().y - hitbox[i].getSize().y / 2.f,
				0 - hitbox[i].getSize().x / 2.f),
				Vec3f(hitbox[i].getPos().x + hitbox[i].getSize().x / 2.f,
					hitbox[i].getPos().y + hitbox[i].getSize().y / 2.f,
					0 + hitbox[i].getSize().x / 2.f));

			if (CollisionM.isAABBAABB(itr->getAABB(),hitbox_aabb)){
				hitbox[i].getMapChipPtr()->BulletCollison(itr->getThisPointer(),true);
			}


		}
		hitbox.clear();

	}


}

void MapChipManager::CollisionEnemyBulletToMap()
{
	int hitscale = 1;
	int WorldScaleInt = int(WorldScale);
	for (auto& itr : bulletmanagerptr->getEnemyBullets()) {


		std::vector<HitBox> hitbox;

		int collision_pos_y = (int((itr)->getPos().y) / WorldScaleInt);
		int collision_pos_x = (int(-(itr)->getPos().x) / WorldScaleInt);

		for (int y = collision_pos_y - hitscale;
		y <= (collision_pos_y + hitscale);y++) {
			if ((y < 0) || y >= mapchips.size())continue;
			for (int x = collision_pos_x - hitscale;
			x <= collision_pos_x + hitscale;x++) {
				if ((x < 0) || x >= mapchips[y].size())continue;

				if (!mapchips[y][x]->getIsCollision())continue;
				if (!mapchips[y][x]->getIsActive())continue;
				if (CollisionM.isBoxBox(Vec2f(itr->getPos().x, itr->getPos().y), mapchips[y][x]->getPos2f(),
					Vec2f(itr->getScale().x, itr->getScale().y), mapchips[y][x]->getScale2f()))
				{
					float distance = (itr->getPos().x - mapchips[y][x]->getPos2f().x)*
						(itr->getPos().x - mapchips[y][x]->getPos2f().x)
						+ (itr->getPos().y - mapchips[y][x]->getPos2f().y)*
						(itr->getPos().y - mapchips[y][x]->getPos2f().y);
					hitbox.push_back(HitBox(mapchips[y][x]->getPos2f(), mapchips[y][x]->getScale2f(), distance, mapchips[y][x]->getThisPointer()));
				}
			}

		}
		std::sort(hitbox.begin(), hitbox.end(), [&](HitBox& a, HitBox& b) {return a.getDistance() < b.getDistance();});

		for (int i = 0;i < hitbox.size();i++) {

			AxisAlignedBox3f hitbox_aabb(Vec3f(hitbox[i].getPos().x - hitbox[i].getSize().x / 2.f,
				hitbox[i].getPos().y - hitbox[i].getSize().y / 2.f,
				0 - hitbox[i].getSize().x / 2.f),
				Vec3f(hitbox[i].getPos().x + hitbox[i].getSize().x / 2.f,
					hitbox[i].getPos().y + hitbox[i].getSize().y / 2.f,
					0 + hitbox[i].getSize().x / 2.f));

			if (CollisionM.isAABBAABB(itr->getAABB(), hitbox_aabb)) {
				hitbox[i].getMapChipPtr()->BulletCollison(itr->getThisPointer(), false);
			}


		}
		hitbox.clear();

	}
}

std::string MapChipManager::getPath(const int worldnum, const int stagenum, const int floornum)
{
	std::string path = "MapData/World" + std::to_string(worldnum) +
		"/Stage" + std::to_string(stagenum) +
		"/Floor" + std::to_string(floornum) + "/";
	return path;
}

