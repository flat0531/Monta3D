#include "TextureManager.h"
using namespace ci;
using namespace ci::app;
TextureManager::TextureManager()
{
}

ci::gl::Texture const& TextureManager::CreateTexture(std::string name)
{

	if (texture.find(name) == texture.end()) {
	    texture.insert(std::make_pair(name,name));//2
		//texture[name] = MyTexture(name);
	}
	else {

	}
	return getTexture(name);
}
void TextureManager::quickCreateTexture(std::string name)
{
	texture[name] = MyTexture(name);
}

ci::gl::Texture const& TextureManager::getTexture(std::string name)
{
	return texture[name].getTex();
}


void TextureManager::eraseTexture(std::string name)
{
	if (texture.find(name) == texture.end()) {

	}
	else {
		texture.erase(name);
	}
	
}


void TextureManager::Clear()
{
	texture.clear();
	mesh.clear();
}

ci::TriMesh const & TextureManager::CreateMesh(std::string name)
{
	if (mesh.find(name) == mesh.end()) {
		mesh.insert(std::make_pair(name, name));
	}
	else {

	}
	return getMesh(name);
}

ci::TriMesh const & TextureManager::getMesh(std::string name)
{
	return mesh[name].getMesh();
}



void TextureManager::eraseMesh(std::string name)
{
	mesh.erase(name);
}
