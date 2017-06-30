#include "MapManager.h"
#include"../Top/Top.h"
#include"../Top/MyJson.h"
#include"../Top/TextureManager.h"
#include"../EditerObject/TextureObj.h"
#include"../Top/CollisionManager.h"
using namespace ci;
using namespace ci::app;

MapManager::MapManager()
{
}

void MapManager::ReadData(const int world, const int stage, const int floor)
{
	std::string createpath = getPath(world, stage, floor);

	JsonTree worldjson(loadAsset(createpath+"/world.json"));
	
	JsonTree linejson(loadAsset(createpath + "/line.json"));
	JsonTree mapjson(loadAsset(createpath + "/map2d.json"));
	CreateWorld(worldjson);
	CreateTexutreObj(mapjson);
}






void MapManager::CreateWorld(const ci::JsonTree& _json)
{
	CreateSky(_json);
}

void MapManager::CreateSky(const ci::JsonTree& _json)
{
	JsonTree skyjson = _json["sky"];
	skyobj.clear();
	for (int i = 0;i < skyjson.getNumChildren();i++) {
		JsonTree childsky = skyjson.getChild(i);
		Vec3f pos = JsonM.getVec3(childsky, "pos");
		Vec3f scale = JsonM.getVec3(childsky, "scale");
		Vec3f rotate = JsonM.getVec3(childsky, "rotate");
		std::string texturepath = childsky.getValueForKey<std::string>("texture");
		ColorA color = JsonM.getColor(childsky, "color");
		bool isrotate = childsky.getValueForKey<bool>("update");
		skyobj.push_back(Sky(pos*WorldScale, scale*WorldScale, rotate, color, texturepath));
		skyobj[i].setIsRotate(isrotate);
	}
}



std::string MapManager::getPath(const int world, const int stage, const int floor)
{
	std::string path = "Json/Stage/World" + std::to_string(world) +
		"/Stage" + std::to_string(stage) +
		"/Floor" + std::to_string(floor);
	return path;
}

void MapManager::CreateTexutreObj(const ci::JsonTree & _json)
{
	textureobject.clear();
	for (int i = 0;i < _json.getNumChildren();i++) {
		JsonTree child = _json.getChild(i);
		std::string name = child.getValueForKey<std::string>("texturename");
		TextureM.CreateTexture(name);
		Vec3f pos = JsonM.getVec3(child, "pos");
		Vec3f scale = JsonM.getVec3(child, "scale");
		Vec3f rotate = JsonM.getVec3(child, "rotate");
		bool alptha = child.getValueForKey<bool>("isalpha");
		textureobject.push_back(std::make_shared<TextureObj>(pos, scale, rotate, name, alptha));
	}
}

void MapManager::drawSky()
{
	for (auto itr : skyobj) {
		itr.draw();
	}
}

void MapManager::rotateSky(const ci::Vec3f _rotate)
{
	for (auto& itr : skyobj) {
		itr.Rotate(_rotate);
	}
}

void MapManager::drawTexureObjct(const ci::CameraPersp & camera)
{
	auto cemeravec = gl::getModelView().transformVec(Vec3f::zAxis());
	std::sort(textureobject.begin(), textureobject.end(), [&](std::shared_ptr<TextureObj> left, std::shared_ptr<TextureObj> right)
	{
		bool isleftalpha = left->getIsAlpha();
		bool isrightalpha = right->getIsAlpha();
		if ((!isleftalpha) && isrightalpha) {
			return true;
		}
		if (isleftalpha && (!isrightalpha)) {
			return false;
		}
		if (cemeravec.z >= 0) {
			return left->getPos().z < right->getPos().z;
		}
		else {
			return left->getPos().z > right->getPos().z;
		}
	}
	);
	for (int i = 0;i < textureobject.size();i++) {
		Vec2f screen_position = camera.worldToScreen(textureobject[i]->getPos(),
			WINDOW_WIDTH, WINDOW_HEIGHT);
		if (CollisionM.isBoxPoint(screen_position, Vec2f(-WINDOW_WIDTH*0.75f,-WINDOW_HEIGHT*0.75f), Vec2f(WINDOW_WIDTH*2.5f, WINDOW_HEIGHT*2.5f))) {
			textureobject[i]->draw();
		}
	}
}
