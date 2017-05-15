#include"SceneManager.h"

std::shared_ptr<SceneBase> SceneManager::scene = nullptr;

void SceneManager::setup()
{
	scene->setup();
}

void SceneManager::update()
{
	scene->update();
}

void SceneManager::draw2D()
{
	scene->draw2D();
}

void SceneManager::draw()
{
	scene->draw();
}

void SceneManager::shift()
{
	scene->shift();
}
