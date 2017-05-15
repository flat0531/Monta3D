#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"      // テクスチャ機能 
#include"cinder\TriMesh.h"
class MyMesh {
public:
	MyMesh();
	MyMesh(std::string name);
	~MyMesh();
	ci::TriMesh const& getMesh();
	void Clear();
	void Set(const std::string name);
private:
	std::string name;
	ci::TriMesh mesh;
};