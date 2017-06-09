#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\Ray.h"
class CollisionManager {
public:
	static CollisionManager& getCollision() {
		static CollisionManager collision;
		return collision;
	}
	bool isCirclePoint(const ci::Vec2f pointpos, const ci::Vec2f circlepos, const float circlesize);
	bool isBoxPoint(const ci::Vec2f pointpos, const ci::Vec2f boxpos, const ci::Vec2f boxsize);
	bool isBoxBox(const ci::Vec2f pos1,const ci::Vec2f pos2,const ci::Vec2f size1,const ci::Vec2f size2);
	bool isAABBAABB(const ci::AxisAlignedBox3f& a, const ci::AxisAlignedBox3f& b);
	bool isSphereSphere(const ci::Vec3f pos1, const ci::Vec3f pos2, const float r_1, const float r_2);
	float getIntersectZaabb(const ci::Ray& ray, ci::AxisAlignedBox3f& aabb);
};
#define CollisionM (CollisionManager::getCollision().getCollision())