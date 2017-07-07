#pragma once
#include<memory>
#include"SceneBase.h"
class SceneManager {
public:
   template<class T>
   static void createScene(T&);
   static void setup();
   static void update();
   static void draw2D();//////UI�Ȃǂ̂Q�����`��
   static void draw();//////�R�����`��
   static void shift();
private:
	static std::shared_ptr<SceneBase> scene;
};
//////�V�[���𐶐�
template<class T>
static void SceneManager::createScene(T& new_scene)
{
	scene = std::make_shared<T>(new_scene);
	scene->setup();
}
