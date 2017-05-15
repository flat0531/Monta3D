#include "MyMesh.h"
#include"cinder\ObjLoader.h"
using namespace ci;
using namespace ci::app;
MyMesh::MyMesh()
{
}

MyMesh::MyMesh(std::string name)
{
	this->name = name;
	ObjLoader loader = ObjLoader(loadAsset("Mesh/" + name));
	loader.load(&mesh,
		boost::logic::indeterminate, boost::logic::indeterminate,
		false);
}

MyMesh::~MyMesh()
{
}

ci::TriMesh const & MyMesh::getMesh()
{
	return mesh;
}
