#include "MyJson.h"
using namespace ci;
using namespace ci::app;
void MyJson::Read()
{

}

ci::Vec2f MyJson::getVec2(const ci::JsonTree & _json, const std::string key)
{
	auto vec = _json[key];
	Vec2f vec2;
	vec2.x = vec.getValueAtIndex<float>(0);
	vec2.y = vec.getValueAtIndex<float>(1);
	return vec2;
}

ci::Vec3f MyJson::getVec3(const ci::JsonTree & _json, const std::string key)
{
	auto vec = _json[key];
	Vec3f vec3;
	vec3.x = vec.getValueAtIndex<float>(0);
	vec3.y = vec.getValueAtIndex<float>(1);
	vec3.z = vec.getValueAtIndex<float>(2);
	return vec3;
}
ci::ColorA MyJson::getColor(const ci::JsonTree & _json, const std::string key)
{
	auto vec = _json[key];
	ci::ColorA vec4;
	vec4.r = vec.getValueAtIndex<float>(0);
	vec4.g = vec.getValueAtIndex<float>(1);
	vec4.b = vec.getValueAtIndex<float>(2);
	vec4.a = vec.getValueAtIndex<float>(3);
	return vec4;
}

ci::JsonTree MyJson::Vec2fToJson(const ci::Vec2f vec, const std::string key)
{
	JsonTree jsonx = JsonTree("", vec.x);
	JsonTree jsony = JsonTree("", vec.y);
	JsonTree json= JsonTree::makeObject(key);
	json.pushBack(jsonx);json.pushBack(jsony);
	return json;
}

ci::JsonTree MyJson::Vec3fToJson(const ci::Vec3f vec, const std::string key)
{
	JsonTree jsonx = JsonTree("", vec.x);
	JsonTree jsony = JsonTree("", vec.y);
	JsonTree jsonz= JsonTree("", vec.z);
	JsonTree json = JsonTree::makeObject(key);
	json.pushBack(jsonx);json.pushBack(jsony);json.pushBack(jsonz);
	return json;
}

void MyJson::test()
{
	JsonTree a;
	std::vector<JsonTree>jsons;
	JsonTree kansei;
	for (int i = 0;i < 3;i++)
	{
		JsonTree buf;
		buf.pushBack(JsonM.Vec3fToJson(Vec3f(50, 60, 50), "pos"));
		buf.pushBack(JsonM.Vec3fToJson(Vec3f(50, 50, 70), "rotate"));
		buf.pushBack(JsonTree("texture", "uuuu.png"));
		jsons.push_back(buf);
	}
	for (int i = 0;i < jsons.size();i++) {
		kansei.pushBack(jsons[i]);
	}
	//a.write("");
	//struct MyStruct
	//{

	//};
	//a.pushBack(JsonM.Vec3fToJson(Vec3f(50,50,50),"pos"));
	//a.pushBack(JsonM.Vec3fToJson(Vec3f(150, 50, 150.1f), "rotate"));
	//a.addChild(JsonTree("texture","uuuu.png"));

	//kansei.pushBack(a);
	//kansei.pushBack(a);

	//kansei.write("../assets/Json/test2.json");
}
