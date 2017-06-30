#include "ShadowManager.h"
#include"../WorldCreater/MapChipManager.h"
#include"../Top/Top.h"
#include"../Top/CollisionManager.h"
#include"../WorldObject/MapChip/MapChipBase.h"
#include"../Top/TextureManager.h"
#include"../Top/DrawManager.h"
using namespace ci;
using namespace ci::app;
ShadowManager::ShadowManager()
{
	TextureM.CreateTexture("UI/shadow.png");
}
ShadowManager * ShadowManager::getThisPtr()
{
	return this;
}

void ShadowManager::draw(const ci::Vec3f pos, const ci::Vec3f scale)
{
	std::vector<std::vector<std::shared_ptr<MapChipBase>>>buff = mapchipmanagerptr->getMapChips();
	
	int WorldScaleInt = int(WorldScale);

	int index_x = (int(-(pos.x-WorldScale/2.f)) / WorldScaleInt);
	int index_y = (int(pos.y) / WorldScaleInt);

	if (index_x >= mapchipmanagerptr->getChipsSize().x - 1)return;
	if (index_x < 0)return;
	if (index_y >= mapchipmanagerptr->getChipsSize().y - 1)return;
	if (index_y < 0)return;

	Vec3f centerpos = Vec3f(pos.x, pos.y, pos.z);
	Ray ray(centerpos, Vec3f(0, -WorldScale * 11, 0));

	bool ishit = false;


	float length = std::numeric_limits<float>::max();
	int ray_y_index = -1;

	for (int y = index_y;y >= 0;y--) {
		if (!buff[y][index_x]->getIsCollision())continue;
		Vec2f pos2f = buff[y][index_x]->getPos2f();
		Vec3f pos3f = Vec3f(pos2f.x, pos2f.y, pos.z);

		Vec3f scale3f = buff[y][index_x]->getScale3f();
		AxisAlignedBox3f aabb(pos3f - scale3f / 2.f, pos3f + scale3f / 2.f);
		if (aabb.intersects(ray)) {
			float z = CollisionM.getIntersectZaabb(ray, aabb);
			if (z > 1)continue;
			if (z < 0.045)break;

			if (z < length) {
				ishit = true;
				length = z;
				ray_y_index = y;
			}
		}
	}
	if (ishit) {
		if (length < 0.045)return;
		Vec2f pos2f = buff[ray_y_index][index_x]->getPos2f();
		Vec3f pos3f = Vec3f(pos.x, pos2f.y, pos.z);
		length *= 20.f;
		DrawM.drawTextureCube(pos3f + Vec3f(0, 0.51, 0)*WorldScale, Vec3f(1.3, 0, 1.3)*((0.5f*(scale.x) / length) + (0.5f*(scale.x))), Vec3f(0, 0, 0), TextureM.getTexture("UI/shadow.png"), ColorA(1, 1, 1, 0.3f + 0.4f*(1.f / length)));
	}

}

void ShadowManager::setMapChipManager(MapChipManager* mapchipmanager)
{
	mapchipmanagerptr = mapchipmanager;
}
