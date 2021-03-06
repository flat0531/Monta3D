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
	if (key == "") {
		Vec3f vec3;
		vec3.x = _json.getValueAtIndex<float>(0);
		vec3.y = _json.getValueAtIndex<float>(1);
		vec3.z = _json.getValueAtIndex<float>(2);
		return vec3;
	}
	else {
		auto vec = _json[key];
		Vec3f vec3;
		vec3.x = vec.getValueAtIndex<float>(0);
		vec3.y = vec.getValueAtIndex<float>(1);
		vec3.z = vec.getValueAtIndex<float>(2);
		return vec3;
	}
	
}
ci::Vec3i MyJson::getVec3i(const ci::JsonTree & _json, const std::string key)
{
	if (key == "") {
		Vec3i vec3;
		vec3.x = _json.getValueAtIndex<int>(0);
		vec3.y = _json.getValueAtIndex<int>(1);
		vec3.z = _json.getValueAtIndex<int>(2);
		return vec3;
	}
	else {
		auto vec = _json[key];
		Vec3i vec3;
		vec3.x = vec.getValueAtIndex<int>(0);
		vec3.y = vec.getValueAtIndex<int>(1);
		vec3.z = vec.getValueAtIndex<int>(2);
		return vec3;
	}
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

