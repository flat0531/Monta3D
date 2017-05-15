#include "MapManager.h"
#include"../Top/Top.h"
#include"../Top/MyJson.h"
#include"../Top/TextureManager.h"
#include"../EditerObject/TextureObj.h"
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
	//CreateLine(linejson);
	//CreateLineWall(linejson);
	//CreateLineSlope(linejson);
	CreateWorld(worldjson);
	CreateTexutreObj(mapjson);
	//JsonTree texture2d_j= json["texture2d"];
	//console() << texture2d_j << std::endl;
	/*int ggg = 0;
	for (int i = 0;i < jsons.getNumChildren();i++) {
		JsonTree jsonss = jsons.getChild(i);
		if (jsonss.hasChild("oko")) {
			console() << "oko" + jsonss.getValueForKey<std::string>("oko") << std::endl;
			ggg++;
		}
		int a = jsonss.getValueForKey<int>("map");
		console() << a << std::endl;
	}*/
}



void MapManager::Create2dMap(const ci::JsonTree& _json)
{
	JsonTree map2djson = _json["map2d"];
	for (int i = 0;i < map2djson.getNumChildren();i++) {
		JsonTree childmap2d = map2djson.getChild(i);
		Vec3f pos = getVec3(childmap2d, "pos");
		Vec3f scale = getVec3(childmap2d, "scale");
		Vec3f rotate = getVec3(childmap2d, "rotate");
		ColorA color = getColor(childmap2d, "color");
		std::string texturepath = childmap2d.getValueForKey<std::string>("texture");
		bool isfront= childmap2d.getValueForKey<bool>("front");
		if (!isfront)
			map2dobj.push_back(Map2d(pos*WorldScale, scale*WorldScale, rotate, color, texturepath));
		else
			map2frontobj.push_back(Map2d(pos*WorldScale, scale*WorldScale, rotate, color, texturepath));
	}
}



void MapManager::CreateWorld(const ci::JsonTree& _json)
{
	CreateSky(_json);
	//Create2dMap(_json);
	//Vec3f pos = getVec3(skyjson, "pos");
	/*auto pos = skyjson["pos"];
	float pos_[3];
	for (int i = 0;i < 3;i++) {
		pos_[i] = pos.getValueAtIndex<float>(i);
		console() << pos_[i] << std::endl;
	}*/
	//console() << skyjson << std::endl;

	/*console() << skyjson.getValueForKey<float>("pos") << std::endl;
	console() << skyjson.getValueForKey("pos")[1] << std::endl;
	console() << skyjson.getValueForKey("pos")[2] << std::endl;*/
	//for (int i = 0;i < skyjson.getNumChildren();i++) {
	//	JsonTree childsky = skyjson.getChild(i);
	//	float a = (float)childsky.getValueForKey("pos")[0];
	//	float b = (float)childsky.getValueForKey("pos")[1];
	//	float c = (float)childsky.getValueForKey("pos")[2];
	//	//console() << a << std::endl;
	//	//console() << b << std::endl;
	//	//console() << c << std::endl;
	//	/*JsonTree jsonss = jsons.getChild(i);
	//	if (jsonss.hasChild("oko")) {

	//		ggg++;
	//	}*/
	//}
}

void MapManager::CreateSky(const ci::JsonTree& _json)
{
	JsonTree skyjson = _json["sky"];
	skyobj.clear();
	for (int i = 0;i < skyjson.getNumChildren();i++) {
		JsonTree childsky = skyjson.getChild(i);
		Vec3f pos = getVec3(childsky, "pos");
		Vec3f scale = getVec3(childsky, "scale");
		Vec3f rotate = getVec3(childsky, "rotate");
		std::string texturepath = childsky.getValueForKey<std::string>("texture");
		ColorA color = getColor(childsky, "color");
		bool isrotate = childsky.getValueForKey<bool>("update");
		skyobj.push_back(Sky(pos*WorldScale, scale*WorldScale, rotate, color, texturepath));
		skyobj[i].setIsRotate(isrotate);
	}
}

void MapManager::CreateLine(const ci::JsonTree & _json)
{
	JsonTree map2djson = _json["line"];
	for (int i = 0;i < map2djson.getNumChildren();i++) {
		JsonTree childmap2d = map2djson.getChild(i);
		Vec3f pos1 = getVec3(childmap2d, "pos1");
		Vec3f pos2 = getVec3(childmap2d, "pos2");
		lines.push_back(Line(Vec2f(pos1.x,pos1.y)*WorldScale, Vec2f(pos2.x, pos2.y)*WorldScale));
		Vec3f scale = getVec3(childmap2d, "scale");
		ColorA color = getColor(childmap2d, "color");
		std::string texturepath = childmap2d.getValueForKey<std::string>("texture");
		map2dobj.push_back(Map2d(lines[lines.size()-1].getCenterpos(), Vec3f(lines[lines.size()-1].getScale().x,0, scale.z*WorldScale), lines[lines.size() - 1].getRotate(), color, texturepath));
	}
	
}

void MapManager::CreateLineWall(const ci::JsonTree & _json)
{
	JsonTree map2djson = _json["lineandwall"];
	for (int i = 0;i < map2djson.getNumChildren();i++) {
		JsonTree childmap2d = map2djson.getChild(i);
		Vec3f pos1 = getVec3(childmap2d, "pos1");
		Vec3f pos2 = getVec3(childmap2d, "pos2");
		lines.push_back(Line(Vec2f(pos1.x, pos1.y)*WorldScale, Vec2f(pos2.x, pos2.y)*WorldScale));
		Vec3f scale = getVec3(childmap2d, "scale");
		ColorA color = getColor(childmap2d, "color");
		std::string texturepath = childmap2d.getValueForKey<std::string>("texture");

		map2dobj.push_back(Map2d(lines[lines.size() - 1].getCenterpos(), Vec3f(lines[lines.size() - 1].getScale().x,
			0, scale.z*WorldScale), lines[lines.size() - 1].getRotate(),
			color, texturepath));

		std::string walltexturepath = childmap2d.getValueForKey<std::string>("walltexture");
		ColorA wallcolor = getColor(childmap2d, "wallcolor");
		map2dobj.push_back(Map2d(lines[lines.size() - 1].getCenterpos()-Vec3f(0,scale.y/2.f*WorldScale,scale.z/2.f*WorldScale),
			Vec3f(lines[lines.size() - 1].getScale().x, scale.y*WorldScale, 0), Vec3f(0,0,180),
			color, walltexturepath));
	}
}

void MapManager::CreateLineSlope(const ci::JsonTree & _json)
{
	JsonTree map2djson = _json["lineslope"];
	for (int i = 0;i < map2djson.getNumChildren();i++) {
		JsonTree childmap2d = map2djson.getChild(i);
		Vec3f pos1 = getVec3(childmap2d, "pos1");
		Vec3f pos2 = getVec3(childmap2d, "pos2");
		lines.push_back(Line(Vec2f(pos1.x, pos1.y)*WorldScale, Vec2f(pos2.x, pos2.y)*WorldScale));
		Vec3f scale = getVec3(childmap2d, "scale");
		ColorA color = getColor(childmap2d, "color");
		std::string texturepath = childmap2d.getValueForKey<std::string>("texture");

		map2dobj.push_back(Map2d(lines[lines.size() - 1].getCenterpos(), Vec3f(lines[lines.size() - 1].getScale().x,
			0, scale.z*WorldScale), lines[lines.size() - 1].getRotate(),
			color, texturepath));


		std::string slopetexturepath = childmap2d.getValueForKey<std::string>("slopetexture");
		ColorA slopecolor = getColor(childmap2d, "slopecolor");
		map2frontobj.push_back(Map2d(lines[lines.size() - 1].getCenterpos() - Vec3f(lines[lines.size() - 1].getScale().x*sin(lines[lines.size() - 1].getRotate().z*(M_PI / 180.f))/2.f,
			-lines[lines.size() - 1].getScale().x*cos(lines[lines.size() - 1].getRotate().z*(M_PI/180.f)) / 2.f,
			0),
			Vec3f(lines[lines.size() - 1].getScale().x, lines[lines.size() - 1].getScale().x, scale.z*WorldScale), Vec3f(0, 0, lines[lines.size()-1].getRotate().z),
			slopecolor, slopetexturepath));




		std::string walltexturepath = childmap2d.getValueForKey<std::string>("walltexture");
		ColorA wallcolor = getColor(childmap2d, "wallcolor");
		map2dobj.push_back(Map2d(lines[lines.size() - 1].getCenterpos() - Vec3f(0, std::abs(pos2.y - pos1.y)*WorldScale/2.f+ scale.y*WorldScale/2.f, scale.z / 2.f*WorldScale),
			Vec3f(std::abs(pos2.x - pos1.x)*WorldScale, scale.y*WorldScale, 0), Vec3f(0, 0, 180),
			wallcolor, walltexturepath));
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

void MapManager::drawMap2d()
{
	for (auto itr : map2dobj) {
		itr.draw();
	}
}

void MapManager::drawMap2dFront()
{
	for (auto itr : map2frontobj) {
		itr.draw();
	}
}

void MapManager::drawTexureObjct()
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
		textureobject[i]->draw();
	}
}

ci::Vec3f MapManager::getVec3(const ci::JsonTree & _json, const std::string key)
{
	auto vec = _json[key];
	Vec3f vec3;
	vec3.x = vec.getValueAtIndex<float>(0);
	vec3.y = vec.getValueAtIndex<float>(1);
	vec3.z = vec.getValueAtIndex<float>(2);
	return vec3;
}

ci::ColorA MapManager::getColor(const ci::JsonTree & _json, const std::string key)
{
	auto vec = _json[key];
	ci::ColorA vec4;
	vec4.r = vec.getValueAtIndex<float>(0);
	vec4.g = vec.getValueAtIndex<float>(1);
	vec4.b = vec.getValueAtIndex<float>(2);
	vec4.a = vec.getValueAtIndex<float>(3);
	return vec4;
}
