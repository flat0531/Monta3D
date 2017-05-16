#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
enum SceneType {
	NULL_SCENE, TITLE_SCENE,GANEMAIN_SCENE,STAGESELECT_SCENE,DRAW_SCENE
};
class DataManager {
public:
	static DataManager& getData() {
		static DataManager data;
		return data;
	}
	DataManager::DataManager();
	int getWorldNum();
	int getStageNum();
	std::string getStageName();
	void ReadNowData();
	void setWorldNum(const int _worldnum);
	void setStageNum(const int _stagenum);
	void setStageName(const std::string _stagename);
	SceneType getPrevscene();
	SceneType getNextscene();
	void setPrevScene(const SceneType _prevscene);
	void setNextScene(const SceneType _nextscene);
private:
	int worldnum = 1;
	int stagenum = 1;
	std::string stagename;
	SceneType prevscene = SceneType::NULL_SCENE;
	SceneType nextscene = SceneType::NULL_SCENE;
};
#define DataM (DataManager::getData().getData())
