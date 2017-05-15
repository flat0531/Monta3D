#pragma once
#include"../../Scene/SceneBase.h"
#include"cinder/app/App.h"
#include"cinder/Camera.h"
#include "cinder/MayaCamUI.h"
#include"../../EditerObject/CubeObject.h"
#include"../../UI/Range.h"
#include <vector>
#include<memory>
#include"cinder/Ray.h"
class TextureObj;
enum MapChipType;

class CourseEditer :public SceneBase {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void draw2D() override;
	void shift() override;
private:
	enum UpdateType {
		CUBE_UPDATE,MAP2D_UPDATE,UPDATETYPE_MAX
	};
	//std::string texturetype[TEXTURE_TYPE_MAX];
	std::vector<std::string> texturetype;
	std::vector<bool>textureisalphas;
	struct Buttuon
	{
		ci::Vec2f pos;
		ci::Vec2f size;
	};
	UpdateType updatetype = CUBE_UPDATE;
	int selecttexture = 0;
	ci::CameraPersp camera;
	ci::Vec3f camerapos;
	ci::Vec3f cameraseteyepoint;
	ci::Vec2f prevmousepos;
	ci::CameraOrtho ortho;
	std::vector<std::vector<std::shared_ptr<CubeObject>>> mapfront;
	std::vector<std::shared_ptr<TextureObj>> textureobjects;
	MapChipType select_mapchip_type;
	ci::Font font;
	Range scale_x_range;Range scale_y_range;Range scale_z_range;
	Range rotate_x_range;Range rotate_y_range;Range rotate_z_range;
	Buttuon buttons[6];
	int worldnum = 1;
	int stagenum = 1;
	int floornum = 1;
	int selecttexturenum = 0;
	int addvalue = 1;
	void CubeDraw();
	void CreateFrontMap();
	void updateCamera();
	void setCubeType();
	ci::Ray getCameraRay();
	void setCube(std::shared_ptr<CubeObject> _cubeobj,MapChipType type);
	void ChangeSelectCubeType();
	void ChangeCubeVector();
	void CubeXVectorUp();
	void CubeXVectorDown();
	void CubeYVectorUp();
	void CubeYVectorDown();
	void saveCubes();
	void RoadCubes();
	void drawWindow();
	void ChangeUpdate();
	void PushTextureObj();
	void drawTextureObj();
	void ChangeSelectTextureObject();
	void EraseTextureObj();
	void updateRange();
	void drawRange();
	void setValueSeletTextureObj();
	void trancerateSelectTextureObj();
	void drawtrancerateSelectTextureObjButton();
	void drawSelectTextureValue();
	void ChangeAddValue();
	void setSelectRange();
	void drawSelectTexture();
	void CreateTextureTypeString();
	void setTextureSelectTextureObj();
	void selectTextureType();
	void writeMap2dObjct();
	void roadMap2dObject();
	std::string getPath();
	void drawStageNum();
	void changeStageNum();
};