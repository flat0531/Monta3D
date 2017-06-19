#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"../CharacterAction/ActionBase.h"
#include"cinder\gl\Texture.h"
#include<vector>
enum SceneType {
	NULL_SCENE, TITLE_SCENE,GANEMAIN_SCENE,STAGESELECT_SCENE,DRAW_SCENE,FOLMSELECT_SCENE,FREE_DRAW_SCENE
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
	void releaseCharacter(const std::string name,const std::string type,const bool is);
	void roadGetItems(int worldnum,int stagenum);
	void saveGetItems(int worldnum, int stagenum, std::vector<bool>_getitems);
	void saveStageData(int worldnum, int stagenum,bool is);
	void saveColorRelease(const std::string name,const bool is);
	bool isCheckFolm(const std::string name,const std::string type);
	void WriteImage(const ci::Surface surface,const std::string name);
	ci::ColorA getColor(const std::string name);
	std::vector<bool>getItems();
	std::vector<bool>diffGetItems();
	std::string getSelectActionName();
	void setSelectActionName(const std::string name);
	ActionType stringToActionType(const std::string name);
	bool getIsTutorial(const std::string name);
	void saveIsTutorial(const std::string name);
	ci::gl::Texture getLastSaveTexture(const std::string name);
private:
	int worldnum = 1;
	int stagenum = 1;
	std::string stagename;
	std::string selectactionname;
	SceneType prevscene = SceneType::NULL_SCENE;
	SceneType nextscene = SceneType::NULL_SCENE;
	std::vector<bool>getitems;
	
};
#define DataM (DataManager::getData().getData())
