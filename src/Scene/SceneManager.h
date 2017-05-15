#pragma once
#include<memory>
#include"SceneBase.h"
class SceneManager {
public:
   template<class T>
   static void createScene(T&);
   static void setup();
   static void update();
   static void draw2D();
   static void draw();
   static void shift();
private:
	static std::shared_ptr<SceneBase> scene;
};

template<class T>
static void SceneManager::createScene(T& new_scene)
{
	scene = std::make_shared<T>(new_scene);
	scene->setup();
}
