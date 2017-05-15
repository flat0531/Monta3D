#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"MyTexture.h"
#include"MyMesh.h"
#include<map>
#include<vector>
class TextureManager{
public:
	static TextureManager& getTexture() {
		static TextureManager texture;
		return texture;
	}
	TextureManager::TextureManager();
	ci::gl::Texture const& CreateTexture(std::string name);
	ci::gl::Texture const& getTexture(std::string name);
	void eraseTexture(std::string name);
	void quickCreateTexture(std::string name);
	void Clear();

	ci::TriMesh const& CreateMesh(std::string name);
	ci::TriMesh const& getMesh(std::string name);
	void eraseMesh(std::string name);

private:

	std::map<std::string, MyTexture> texture;
	std::map<std::string, MyMesh> mesh;

};
#define TextureM (TextureManager::getTexture().getTexture())