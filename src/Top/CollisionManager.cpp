#include "CollisionManager.h"

bool CollisionManager::isCirclePoint(const ci::Vec2f pointpos, const ci::Vec2f circlepos, const float circlesize)
{
	float length = (circlepos.x - pointpos.x)*(circlepos.x - pointpos.x) + (circlepos.y - pointpos.y)*(circlepos.y - pointpos.y);
	if (length <= (circlesize*circlesize)) {
		return true;
	}
	return false;
}

bool CollisionManager::isBoxPoint(const ci::Vec2f pointpos, const ci::Vec2f boxpos, const ci::Vec2f boxsize)
{
	if (pointpos.x >= boxpos.x&&pointpos.x < (boxpos.x + boxsize.x)
		&& pointpos.y >= boxpos.y&&pointpos.y < (boxpos.y + boxsize.y)) {
		return true;
	}
	return false;
}

bool CollisionManager::isBoxBox(const ci::Vec2f pos1, const ci::Vec2f pos2, const ci::Vec2f size1, const ci::Vec2f size2)
{

	if (((pos1.x - (size1.x / 2.f)) < pos2.x + (size2.x / 2.f)) &&
		pos2.x - (size2.x / 2.f) < (pos1.x + (size1.x / 2.f)) &&
		(pos1.y - (size1.y / 2.f)) < pos2.y + (size2.y / 2.f) &&
		pos2.y - (size2.y / 2.f) < (pos1.y + (size1.y / 2.f))) {
		return true;
	}
	return false;
}

bool CollisionManager::isAABBAABB(const ci::AxisAlignedBox3f & a, const ci::AxisAlignedBox3f & b)
{
	const ci::Vec3f& a_min = a.getMin();
	const ci::Vec3f& a_max = a.getMax();
	const ci::Vec3f& b_min = b.getMin();
	const ci::Vec3f& b_max = b.getMax();

	// XYZの各軸ごとに領域が重なっているかを調べる
	if (a_max.x < b_min.x || a_min.x > b_max.x) return false;
	if (a_max.y < b_min.y || a_min.y > b_max.y) return false;
	if (a_max.z < b_min.z || a_min.z > b_max.z) return false;

	// 全てが重なっている→２つのAABBは交差
	return true;
}

float CollisionManager::getIntersectZaabb(const ci::Ray & ray, ci::AxisAlignedBox3f & aabb)
{

	float z[3];

	int cross = aabb.intersect(ray, z);

	float min_z = std::numeric_limits<float>::max();
	for (int i = 0; i < cross; ++i) {
		min_z = std::min(z[i], min_z);
	}
	return min_z;
}
