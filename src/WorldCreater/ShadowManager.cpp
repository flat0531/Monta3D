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
	Vec3f centerpos = Vec3f(pos.x, pos.y, pos.z);
	Ray ray(centerpos, Vec3f(0, -WorldScale * 10, 0));

	bool ishit = false;
		
	if (index_x >= mapchipmanagerptr->getChipsSize().x - 1)return;
	if (index_x < 0)return;

		float length = std::numeric_limits<float>::max();
		int ray_y_index = -1;

		for (int y = index_y;y >= 0;y--) {
			if (!buff[y][index_x]->getIsCollision())continue;
			Vec2f pos2f = buff[y][index_x]->getPos2f();
			Vec3f pos3f = Vec3f(pos2f.x, pos2f.y, pos.z);

			Vec3f scale3f =buff[y][index_x]->getScale3f();
			AxisAlignedBox3f aabb(pos3f - scale3f / 2.f, pos3f + scale3f / 2.f);
			if (aabb.intersects(ray)){
				float z = CollisionM.getIntersectZaabb(ray, aabb);
				if (z > 1)continue;
				if (z < 0.05)break;

				if (z < length) {
					ishit = true;
					length = z;
					ray_y_index = y;
				}
			}
		}
		if (ishit) {
			if (length < 0.05)return;
			Vec2f pos2f =buff[ray_y_index][index_x]->getPos2f();
			Vec3f pos3f = Vec3f(pos.x, pos2f.y, pos.z);
			length *= 20.f;
			DrawM.drawTextureCube(pos3f + Vec3f(0, 0.51, 0)*WorldScale, Vec3f(1.3, 0, 1.3)*((0.5f*(scale.x) / length)+(0.5f*(scale.x))), Vec3f(0, 0, 0),TextureM.getTexture("UI/shadow.png"), ColorA(1, 1, 1,0.3f+0.4f*(1.f/length)));
		}

	//std::vector<Ray> rays;
	//std::vector<Vec3f> boxs;
	//std::vector<float> lengths;
	//int WorldScaleInt = int(WorldScale);
	//int collision_pos_x = (int(-(pos.x-scale.x/2.f)) / WorldScaleInt);
	//int collision_pos_y = (int(pos.y) / WorldScaleInt);
	//int raynum = (int(scale.x) / WorldScaleInt) + 2;
	//Vec3f centerpos = Vec3f((collision_pos_x)*WorldScale, pos.y, pos.z);
	//for (int i = 0;i < raynum;i++) {
	//	rays.push_back(Ray(Vec3f((((float(raynum - 1)) / 2.f)*WorldScale) - (WorldScale*i)-centerpos.x, centerpos.y, centerpos.z),
	//		Vec3f(0, -WorldScale * 10, 0)));
	//}
	//
	//for (int i = 0;i < rays.size();i++) {
	//	bool ishit = false;

	//	int index_x = collision_pos_x - float((rays.size() - 1)) / 2.f + i;
	//	
	//	if (index_x >= (mapchipmanagerptr->getChipsSize().x - 1))continue;
	//	if (index_x < 0)continue;

	//	float length = std::numeric_limits<float>::max();

	//	float ray_x_index = -1;
	//	float ray_y_index = -1;

	//	for (int y = collision_pos_y;y >= 0;y--) {
	//		if (!mapchipmanagerptr->getMapChips()[y][index_x]->getIsCollision())continue;
	//		Vec2f pos2f = mapchipmanagerptr->getMapChips()[y][index_x]->getPos2f();
	//		Vec3f pos3f = Vec3f(pos2f.x, pos2f.y, pos.z);
	//		
	//		Vec3f scale3f = mapchipmanagerptr->getMapChips()[y][index_x]->getScale3f();
	//		AxisAlignedBox3f aabb(pos3f -scale3f/2.f, pos3f + scale3f / 2.f);
	//		if (aabb.intersects(rays[i])) {
	//			ishit = true;
	//			float z = CollisionM.getIntersectZaabb(rays[i], aabb);
	//			if (z < length) {
	//				length = z;
	//				ray_x_index = index_x;
	//				ray_y_index = y;
	//			}
	//		}
	//	}
	//	if (ishit) {
	//		Vec2f pos2f = mapchipmanagerptr->getMapChips()[ray_y_index][ray_x_index]->getPos2f();
	//		Vec3f pos3f = Vec3f(pos2f.x, pos2f.y, pos.z);
	//		boxs.push_back(pos3f);
	//		lengths.push_back(-(pos3f.x - pos.x));//ÇPÇOÇOÇÃèÍçá
	//	}
	//}
	//for (int i = 0;i < boxs.size();i++) {
	//	DrawM.drawCube(boxs[i] + Vec3f(0, 0.51, 0)*WorldScale, Vec3f(0.9, 0, 0.9)*WorldScale, Vec3f(0, 0, 0),ColorA(1,0,0,1));
	//	if (lengths[i] > 0&&lengths[i]<=WorldScale) {
	//		float begin_x = lengths[i];
	//		float end_x = WorldScale;
	//	
	//		DrawM.drawTextureAreaCube(boxs[i] + Vec3f(0, 0.51, 0)*WorldScale+Vec3f(mapchipmanagerptr->getMapChips()[0][0]->getScale2f().x/2.f-lengths[i],0,0), Vec3f(lengths[i], 0, 100), Vec3f(0, 0, 0), TextureM.getTexture("UI/shadow.png"),
	//			Vec2i(begin_x, 0), Vec2i(end_x, 100));
	//	}
	//	if (lengths[i] <= 0 && lengths[i] >= -WorldScale) {
	//		float begin_x = 0;
	//		float end_x = -lengths[i];
	//		DrawM.drawTextureAreaCube(boxs[i] + Vec3f(0, 0.51, 0)*WorldScale+Vec3f(mapchipmanagerptr->getMapChips()[0][0]->getScale2f().x / 2.f - lengths[i], 0, 0), Vec3f(-lengths[i], 0, 0), Vec3f(0, 0, 0), TextureM.getTexture("UI/shadow.png"),
	//			Vec2i(begin_x, 0), Vec2i(end_x, 100));
	//	}
	//}

}

void ShadowManager::setMapChipManager(MapChipManager* mapchipmanager)
{
	mapchipmanagerptr = mapchipmanager;
}
