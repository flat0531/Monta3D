#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"CubeBase.h"
#include<memory>
enum MapChipType;
class CubeObject {
public:
	CubeObject();
	CubeObject(const ci::Vec3f _pos,const ci::Vec3f _scale);
	ci::AxisAlignedBox3f getAABB();
	CubeObject* getThisPtr();
	void draw();
	template<class T>
	void setCubeType(T);
	ci::Vec3f getPos();
	ci::Vec3f getScale();
	void setScale(const ci::Vec3f _scale);
	void setMapChipType(const MapChipType _mapchiptype);
	MapChipType getMapChiptype();
private:
	ci::Vec3f pos;
	ci::Vec3f scale;
	std::shared_ptr<CubeBase>cube;
	MapChipType mapchiptype;
};

template<class T>
inline void CubeObject::setCubeType(T)
{
	cube = std::make_shared<T>(this);
}
