#pragma once
#include "cinder\Json.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class MyJson{
public:
   void Read();
   static MyJson& getJson() {
	   static MyJson myjson;
	   return myjson;
   }
   ci::Vec2f getVec2(const ci::JsonTree & _json, const std::string key);
   ci::Vec3f getVec3(const ci::JsonTree & _json, const std::string key);
   ci::Vec3i getVec3i(const ci::JsonTree & _json, const std::string key);
   ci::ColorA getColor(const ci::JsonTree & _json, const std::string key);

   ci::JsonTree Vec2fToJson(const ci::Vec2f vec, const std::string key);
   ci::JsonTree Vec3fToJson(const ci::Vec3f vec, const std::string key);
};
#define JsonM (MyJson::getJson().getJson())