#include "CourseEditer.h"
#include"../../Top/Top.h"
#include"../../Input/KeyManager.h"
#include"../../Scene/SceneManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../EditerObject/NoneCube.h"
#include"../../EditerObject/NormalCube.h"
#include"../../EditerObject/NormalNotDrawCube.h"
#include"../../EditerObject/HulfFllorCube.h"
#include"../../EditerObject/GoalCube.h"
#include"../../EditerObject/BreakCube.h"
#include"../../EditerObject/AppleCube.h"
#include"../../EditerObject/ColoedCube.h"
#include"../../Top/DrawManager.h"
#include"../../Input/MouseMamager.h"
#include"../../Input/KeyManager.h"
#include"../../Top/CollisionManager.h"
#include"../../WorldObject/MapChip/MapChipType.h"
#include"../../Top/TextureManager.h"
#include"../../EditerObject/TextureObj.h"
#include"../../Top/MyJson.h"
using namespace ci;
using namespace ci::app;
void CourseEditer::setup()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
		60.0f,
		1.0f*WorldScale, 1000.f*WorldScale);
	camerapos = Vec3f(0, 0, -10 * WorldScale);
	cameraseteyepoint = Vec3f(0, 0, 10 * WorldScale);
	camera.setCenterOfInterestPoint(camerapos);
	ortho = CameraOrtho(0, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0,
		1,101);

	ortho.setEyePoint(Vec3f(0.0f, 0.0f, 0.0f));
	ortho.setCenterOfInterestPoint(Vec3f(0.0f, 0.0f, -1000.0f));

	font = Font("Comic Sans MS", 50.0f);

	select_mapchip_type = MapChipType::NORMAL_NOTDRAW_CHIP;
	prevmousepos = MouseManager::getMouse().getmousepos();
	CreateTextureTypeString();
	CreateFrontMap();
	createVar();
	setUpButtons();

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void CourseEditer::update()
{
	ChangeUpdate();
	updateCamera();
	switch (updatetype)
	{
	case CourseEditer::CUBE_UPDATE:
		changeStageNum();
		setCubeType();
		ChangeSelectCubeType();
		ChangeCubeVector();
		if (KeyManager::getkey().isPush(KeyEvent::KEY_s)) {
			saveCubes();
		}
		if (KeyManager::getkey().isPush(KeyEvent::KEY_r)) {
			RoadCubes();
		}
		break;
	case CourseEditer::MAP2D_UPDATE:
		if (KeyManager::getkey().isPush(KeyEvent::KEY_p)) {
			PushTextureObj();
		}
		setTextureSelectTextureObj();
		selectTextureType();
		EraseTextureObj();
		ChangeSelectTextureObject();
		updateRange();
		setValueSeletTextureObj();
		trancerateSelectTextureObj();
		ChangeAddValue();
		ViewNowTextureObject();
		roadMap2dObject();
		writeMap2dObjct();
		break;
	case CourseEditer::UPDATETYPE_MAX:
		break;
	default:
		break;
	}

}

void CourseEditer::draw()
{
	camera.setEyePoint(camerapos);
	camera.setCenterOfInterestPoint(cameraseteyepoint);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enable(GL_CULL_FACE);
	gl::enableAlphaBlending();

	gl::setMatrices(camera);

	gl::pushModelView();

	CubeDraw();
	drawTextureObj();
	gl::popModelView();
}

void CourseEditer::draw2D()
{
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	gl::setMatrices(ortho);
	drawWindow();
	switch (updatetype)
	{
	case CourseEditer::CUBE_UPDATE:
		break;
	case CourseEditer::MAP2D_UPDATE:
		drawRange();
		drawtrancerateSelectTextureObjButton();
		drawSelectTextureValue();
		drawSelectTexture();
		break;
	case CourseEditer::UPDATETYPE_MAX:
		break;
	default:
		break;
	}
	drawStageNum();
}

void CourseEditer::shift()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_t)) {
		SceneManager::createScene(Title());
	}
}

void CourseEditer::CubeDraw()
{
	for (int y = 0;y < mapfront.size();y++) {
		for (int x = 0;x < mapfront[y].size();x++) {
			mapfront[y][x]->draw();
		}
	}
}

void CourseEditer::CreateFrontMap()
{
	int y_size = 10;
	int x_size = 20;
	for (int y = 0;y < y_size;y++) {
		std::vector<std::shared_ptr<CubeObject>>buf;
		for (int x = 0;x < x_size;x++) {
			buf.push_back(std::make_shared<CubeObject>(CubeObject(Vec3f(-x*WorldScale, y*WorldScale, 0), Vec3f(1, 1, 1)*WorldScale)));
		}
		mapfront.push_back(std::move(buf));
		buf.clear();
	}

	for (int y = 0;y < mapfront.size();y++) {
		for (int x = 0;x < mapfront[y].size();x++) {
			mapfront[y][x]->setMapChipType(MapChipType::NONE_CHIP);
			mapfront[y][x]->setCubeType(NoneCube(mapfront[y][x]->getThisPtr()));
		}
	}



}

void CourseEditer::updateCamera()
{
	camerapos.z += MouseManager::getMouse().getWheelIncrement()*WorldScale;

	if (MouseManager::getMouse().isPress(MouseEvent::RIGHT_DOWN)) {
		Vec2f trancepos = (MouseManager::getMouse().getmousepos()-prevmousepos);
		float trancevalue = std::abs((camerapos.z/WorldScale)/10.f);
		camerapos += Vec3f(trancepos.x*trancevalue, trancepos.y*trancevalue, 0);
		cameraseteyepoint = Vec3f(camerapos.x,camerapos.y,10*WorldScale);
	}
	if (updatetype == CourseEditer::MAP2D_UPDATE) {
		if (textureobjects.size() != 0) {
			cameraseteyepoint = textureobjects[selecttexturenum]->getPos();
		}
	}
	prevmousepos = MouseManager::getMouse().getmousepos();
}

void CourseEditer::setCubeType()
{
	if (MouseManager::getMouse().getmousepos().x >= (WINDOW_WIDTH - 300))return;
	if (MouseManager::getMouse().getmousepos().y >= (WINDOW_HEIGHT - 200))return;
	if (MouseManager::getMouse().isPress(MouseEvent::LEFT_DOWN)) {
		Ray ray = getCameraRay();
		bool ishit = false;
		float click_z = std::numeric_limits<float>::max();
		int index_x = -1;
		int index_y = -1;
		for (int y = 0;y < mapfront.size();y++) {
			for (int x = 0;x < mapfront[y].size();x++) {
				AxisAlignedBox3f aabb = mapfront[y][x]->getAABB();
				if (aabb.intersects(ray)) {
					ishit = true;
					float z = CollisionM.getIntersectZaabb(ray, aabb);
					if (z < click_z) {
						click_z = z;
						index_x = x;
						index_y = y;
					}
				}
			}
		}
		if(ishit){
			setCube(mapfront[index_y][index_x],select_mapchip_type);
		}
	}
}

ci::Ray CourseEditer::getCameraRay()
{
	Vec2f  mousepos = MouseManager::getMouse().getmousepos();
	float x = mousepos.x / float(WINDOW_WIDTH);
	float y = 1.0f - mousepos.y / float(WINDOW_HEIGHT);
	Ray ray = camera.generateRay(x, y, camera.getAspectRatio());
	return ray;
}

void CourseEditer::setCube(std::shared_ptr<CubeObject> _cubeobj, MapChipType type)
{
	_cubeobj->setMapChipType(type);

	switch (type)
	{
	case NONE_CHIP:
		_cubeobj->setCubeType(NoneCube(_cubeobj->getThisPtr()));
		break;
	case NORMAL_CHIP:
		_cubeobj->setCubeType(NormalCube(_cubeobj->getThisPtr()));
		break;
	case NORMAL_NOTDRAW_CHIP:
		_cubeobj->setCubeType(NormalNotDrawCube(_cubeobj->getThisPtr()));
		break;
	case Half_FLOOR_CHIP:
		_cubeobj->setCubeType(HulfFllorCube(_cubeobj->getThisPtr()));
		break;
	case GOAL_CHIP:
		_cubeobj->setCubeType(GoalCube(_cubeobj->getThisPtr()));
		break;
	case BREAK_CHIP:
		_cubeobj->setCubeType(BreakCube(_cubeobj->getThisPtr()));
		break;
	case APPLE_CHIP:
		_cubeobj->setCubeType(AppleCube(_cubeobj->getThisPtr()));
		break;
	case COLORED_CHIP:
		_cubeobj->setCubeType(ColoredCube(_cubeobj->getThisPtr()));
		break;
	case MAP_CHIP_MAX:
		break;
	default:
		break;
	}
}

void CourseEditer::ChangeSelectCubeType()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_RIGHT)) {
		int buf= int(select_mapchip_type);
		buf++;
		select_mapchip_type = MapChipType(buf%MapChipType::MAP_CHIP_MAX);
	}
}

void CourseEditer::ChangeCubeVector()
{
	CubeXVectorUp();
	CubeYVectorUp();
	CubeXVectorDown();
	CubeYVectorDown();
}

void CourseEditer::CubeXVectorUp()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_3))
	{

		for (int y = 0;y < mapfront.size();y++) {
			std::shared_ptr<CubeObject> buf = std::make_shared<CubeObject>(CubeObject(Vec3f(-(mapfront[y].size()*WorldScale), y*WorldScale, 0), Vec3f(1, 1, 1)*WorldScale));
			mapfront[y].push_back(std::move(buf));
		}
		for (int y = 0;y < mapfront.size();y++) {
			mapfront[y][mapfront[y].size() - 1]->setCubeType(NoneCube(mapfront[y][mapfront[y].size() - 1]->getThisPtr()));
			mapfront[y][mapfront[y].size() - 1]->setMapChipType(MapChipType::NONE_CHIP);
		}
	}
}

void CourseEditer::CubeXVectorDown()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_4))
	{
		for (int y = 0;y < mapfront.size();y++) {
			mapfront[y].pop_back();
		}
	}
}

void CourseEditer::CubeYVectorUp()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_1))
	{
		if (mapfront.size() != 0) {
			std::vector<std::shared_ptr<CubeObject>>buf;
			for (int x = 0;x < mapfront[mapfront.size() - 1].size();x++) {
				buf.push_back(std::make_shared<CubeObject>(CubeObject(Vec3f(-x*WorldScale, mapfront.size()*WorldScale, 0), Vec3f(1, 1, 1)*WorldScale)));
			}
			mapfront.push_back(std::move(buf));
			buf.clear();
			for (int x = 0;x < mapfront[mapfront.size() - 1].size();x++) {
				mapfront[mapfront.size() - 1][x]->setCubeType(NoneCube(mapfront[mapfront.size() - 1][x]->getThisPtr()));
				mapfront[mapfront.size() - 1][x]->setMapChipType(MapChipType::NONE_CHIP);
			}
		}
		else {
			std::vector<std::shared_ptr<CubeObject>>buf;
			int createnum = 10;
			for (int x = 0;x < createnum;x++) {
				buf.push_back(std::make_shared<CubeObject>(CubeObject(Vec3f(-x*WorldScale, mapfront.size()*WorldScale, 0), Vec3f(1, 1, 1)*WorldScale)));
			}
			mapfront.push_back(std::move(buf));
			buf.clear();
			for (int x = 0;x < createnum;x++) {
				mapfront[mapfront.size() - 1][x]->setCubeType(NoneCube(mapfront[mapfront.size() - 1][x]->getThisPtr()));
				mapfront[mapfront.size() - 1][x]->setMapChipType(MapChipType::NONE_CHIP);
			}
		}

	}
}

void CourseEditer::CubeYVectorDown()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_2))
	{
		if (mapfront.size() != 0) {
			mapfront.pop_back();
		}
	}
}

void CourseEditer::saveCubes()
{
	int x_num = mapfront[0].size();
	int y_num = mapfront.size();
	
	std::ofstream savefile(getAssetPath(getPath() + "mapfront.txt").string());
	savefile << x_num << " ";
	savefile << y_num << "\n";
	for (int y = y_num - 1;y >= 0;y--) {
		for (int x = 0;x < x_num;x++) {
			int buf = int(mapfront[y][x]->getMapChiptype());
			if (x == (x_num - 1)) {
				if (y == 0) {
					savefile << buf;
				}
				else
				{
					savefile << buf << "\n";
				}
			}
			else
			{
				savefile << buf << " ";
			}
		}
	}
}

void CourseEditer::RoadCubes()
{
	mapfront.clear();
	std::ifstream savefile(getAssetPath(getPath() + "mapfront.txt").string());
	int x_num;
	int y_num;
	savefile >> x_num;
	savefile >> y_num;
	for (int y = 0;y < y_num;y++) {
		std::vector<std::shared_ptr<CubeObject>>bufobject;
		for (int x = 0;x < x_num;x++) {
			bufobject.push_back(std::make_shared<CubeObject>(CubeObject(Vec3f(-x*WorldScale, y*WorldScale, 0), Vec3f(1, 1, 1)*WorldScale)));
		}
		mapfront.push_back(std::move(bufobject));
		bufobject.clear();
	}
	for (int y = mapfront.size()-1;y >=0;y--) {
		for (int x = 0;x < mapfront[y].size();x++) {
			int buf;
			savefile >> buf;
			MapChipType type = MapChipType(buf);
			setCube(mapfront[y][x],type);
		}
	}

}

void CourseEditer::drawWindow()
{
	{
		Vec2f size(300, WINDOW_HEIGHT);
		Vec2f pos(WINDOW_WIDTH - size.x, 0);
		DrawM.drawBoxEdge(pos, size, ColorA(0.5, 0.5, 0.5, 1));
	}
	
	{
		ColorA color;
		switch (updatetype)
		{
		case CourseEditer::CUBE_UPDATE:
			color = ColorA(0.5, 1, 1, 1);
			break;
		case CourseEditer::MAP2D_UPDATE:
			color = ColorA(1, 1, 0.5, 1);
			break;
		case CourseEditer::UPDATETYPE_MAX:
			break;
		default:
			break;
		}
		Vec2f size(WINDOW_WIDTH, 200);
		Vec2f pos(0, WINDOW_HEIGHT - size.y);
		DrawM.drawBoxEdge(pos, size,color);
	}

}

void CourseEditer::ChangeUpdate()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_z)) {
		int buf = int(updatetype);
		buf++;
		buf = buf%UpdateType::UPDATETYPE_MAX;
		updatetype = UpdateType(buf);
	}
}

void CourseEditer::PushTextureObj()
{
	if (textureobjects.size() == 0) {
		textureobjects.push_back(std::make_shared<TextureObj>(TextureObj(Vec3f(0, 0, 0)*WorldScale, Vec3f(1, 1, 1)*WorldScale, Vec3f(0, 0, 0), texturetype[selecttexture], textureisalphas[selecttexture])));
	}
	else {
		textureobjects.push_back(std::make_shared<TextureObj>(TextureObj(textureobjects[selecttexturenum]->getPos(),textureobjects[selecttexturenum]->getScale(),textureobjects[selecttexturenum]->getRotate(), texturetype[selecttexture], textureisalphas[selecttexture])));
	}
	for (int i = 0;i < textureobjects.size();i++) {
		textureobjects[i]->setColor(ColorA(1, 1, 1, 1));
	}
	camerapos = Vec3f(textureobjects[textureobjects.size()-1]->getPos().x,
		textureobjects[textureobjects.size() - 1]->getPos().y,
		-10 * WorldScale);
	cameraseteyepoint = Vec3f(textureobjects[textureobjects.size() - 1]->getPos().x,
		textureobjects[textureobjects.size() - 1]->getPos().y,
		10 * WorldScale);
	selecttexturenum = textureobjects.size() - 1;
}

void CourseEditer::drawTextureObj()
{
	std::vector<TextureObj> buf;
	for (int i = 0;i < textureobjects.size();i++) {
		buf.push_back(*textureobjects[i]);
	}
	//ƒRƒs[‚µ‚Ä•À‚×‘Ö‚¦‚Ü‚·
	auto cemeravec = gl::getModelView().transformVec(Vec3f::zAxis());


	std::sort(buf.begin(), buf.end(), [&](TextureObj& left, TextureObj& right) 
	{
		bool isleftalpha=left.getIsAlpha();
		bool isrightalpha=right.getIsAlpha();
		if ((!isleftalpha)&&isrightalpha) {
			return true;
		}
		if (isleftalpha&&(!isrightalpha)) {
			return false;
		}
		if (cemeravec.z >= 0) {
			return left.getPos().z <right.getPos().z;
		}
		else {
			return left.getPos().z >right.getPos().z;
		}
		}
	);
	for (int i = 0;i < buf.size();i++) {
		buf[i].draw();
	}
	gl::enableAlphaBlending();
	buf.clear();
}


void CourseEditer::ChangeSelectTextureObject()
{
	if (textureobjects.size() == 0)return;
	if (KeyManager::getkey().isPush(KeyEvent::KEY_d)) {
		selecttexturenum++;
		selecttexturenum = std::min(selecttexturenum,int(textureobjects.size())-1);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_a)) {
		selecttexturenum--;
		selecttexturenum = std::max(selecttexturenum, 0);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_d) || KeyManager::getkey().isPush(KeyEvent::KEY_a)) {
		setSelectRange();
		camerapos = Vec3f(textureobjects[selecttexturenum]->getPos().x,
			textureobjects[selecttexturenum]->getPos().y,
			-10 * WorldScale);
		cameraseteyepoint = Vec3f(textureobjects[selecttexturenum]->getPos().x,
			textureobjects[selecttexturenum]->getPos().y,
			10 * WorldScale);
		for (int i = 0;i < textureobjects.size();i++) {
			textureobjects[i]->setColor(ColorA(1, 1, 1, 1));
		}
	}
	
}

void CourseEditer::EraseTextureObj()
{
	if (textureobjects.size() == 0)return;
	if (KeyManager::getkey().isPush(KeyEvent::KEY_o)){
		textureobjects.erase(textureobjects.begin() + selecttexturenum);
		if (selecttexturenum == textureobjects.size()) {
			selecttexturenum--;
		}
		if (textureobjects.size() == 0) {
			selecttexturenum = 0;
		}
		else {
			setSelectRange();
			camerapos = Vec3f(textureobjects[selecttexturenum]->getPos().x,
				textureobjects[selecttexturenum]->getPos().y,
				-10 * WorldScale);
			cameraseteyepoint = Vec3f(textureobjects[selecttexturenum]->getPos().x,
				textureobjects[selecttexturenum]->getPos().y,
				10 * WorldScale);
			for (int i = 0;i < textureobjects.size();i++) {
				textureobjects[i]->setColor(ColorA(1, 1, 1, 1));
			}
		}
	}

}

void CourseEditer::updateRange()
{
	if (MouseManager::getMouse().isPush(MouseEvent::LEFT_DOWN)) {
		Vec2f mousepos = MouseManager::getMouse().getmousepos();
		if (CollisionM.isBoxPoint(mousepos, scale_x_range.getIconLeftUpPos(), scale_x_range.getIconSize())) {
			scale_x_range.setIsTouch(true);
		}
		if (CollisionM.isBoxPoint(mousepos, scale_y_range.getIconLeftUpPos(), scale_y_range.getIconSize())) {
			scale_y_range.setIsTouch(true);
		}
		if (CollisionM.isBoxPoint(mousepos, scale_z_range.getIconLeftUpPos(), scale_z_range.getIconSize())) {
			scale_z_range.setIsTouch(true);
		}
		if (CollisionM.isBoxPoint(mousepos, rotate_x_range.getIconLeftUpPos(), rotate_x_range.getIconSize())) {
			rotate_x_range.setIsTouch(true);
		}
		if (CollisionM.isBoxPoint(mousepos, rotate_y_range.getIconLeftUpPos(), rotate_y_range.getIconSize())) {
			rotate_y_range.setIsTouch(true);
		}
		if (CollisionM.isBoxPoint(mousepos, rotate_z_range.getIconLeftUpPos(), rotate_z_range.getIconSize())) {
			rotate_z_range.setIsTouch(true);
		}
	}
	if (MouseManager::getMouse().isPull(MouseEvent::LEFT_DOWN)) {
		scale_x_range.setIsTouch(false);
		scale_y_range.setIsTouch(false);
		scale_z_range.setIsTouch(false);
		rotate_x_range.setIsTouch(false);
		rotate_y_range.setIsTouch(false);
		rotate_z_range.setIsTouch(false);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_5)) {
		rotate_x_range.AddRangevalue(1.f / 360.f);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_6)) {
		rotate_y_range.AddRangevalue(1.f / 360.f);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_7)) {
		rotate_z_range.AddRangevalue(1.f / 360.f);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_8)) {
		scale_x_range.AddRangevalue(1.f/ 1200.f);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_9)) {
		scale_y_range.AddRangevalue(1.f / 1200.f);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_0)) {
		scale_z_range.AddRangevalue(1.f / 1200.f);
	}
	scale_x_range.update();
	scale_y_range.update();
	scale_z_range.update();
	rotate_x_range.update();
	rotate_y_range.update();
	rotate_z_range.update();


}

void CourseEditer::drawRange()
{
	scale_x_range.draw();
	scale_y_range.draw();
	scale_z_range.draw();
	rotate_x_range.draw();
	rotate_y_range.draw();
	rotate_z_range.draw();
}

void CourseEditer::setValueSeletTextureObj()
{
	if (textureobjects.size() == 0)return;
	textureobjects[selecttexturenum]->setScale(Vec3f(scale_x_range.getIconValue()*WorldScale, 
		scale_y_range.getIconValue()*WorldScale, 
		scale_z_range.getIconValue()*WorldScale));

	textureobjects[selecttexturenum]->setRotate(Vec3f(int(rotate_x_range.getIconValue()),
		int(rotate_y_range.getIconValue()),
		int(rotate_z_range.getIconValue())));
}

void CourseEditer::trancerateSelectTextureObj()
{
	if (textureobjects.size() == 0)return;
	Vec2f mousepos = MouseManager::getMouse().getmousepos();
	if (MouseManager::getMouse().isPush(MouseEvent::LEFT_DOWN)&& KeyManager::getkey().isPress(KeyEvent::KEY_x)) {

		for (int i = 0;i < 6;i++) {
			if (CollisionM.isBoxPoint(mousepos, buttons[i].pos, buttons[i].size)) {
				if (i == 0) {
					textureobjects[selecttexturenum]->setPosX(textureobjects[selecttexturenum]->getPos().x + addvalue);
				}
				if (i == 1) {
					textureobjects[selecttexturenum]->setPosX(textureobjects[selecttexturenum]->getPos().x - addvalue);
				}
				if (i == 2) {
					textureobjects[selecttexturenum]->setPosY(textureobjects[selecttexturenum]->getPos().y - addvalue);
				}
				if (i == 3) {
					textureobjects[selecttexturenum]->setPosY(textureobjects[selecttexturenum]->getPos().y + addvalue);
				}
				if (i == 4) {
					textureobjects[selecttexturenum]->setPosZ(textureobjects[selecttexturenum]->getPos().z - addvalue);
				}
				if (i == 5) {
					textureobjects[selecttexturenum]->setPosZ(textureobjects[selecttexturenum]->getPos().z + addvalue);
				}
			}
		}
		return;
	}
	if ((!MouseManager::getMouse().isPress(MouseEvent::LEFT_DOWN))|| (KeyManager::getkey().isPress(KeyEvent::KEY_x)))return;
	
	
	for (int i = 0;i < 6;i++) {
		if(CollisionM.isBoxPoint(mousepos, buttons[i].pos, buttons[i].size)){
			if (i == 0) {
				textureobjects[selecttexturenum]->setPosX(textureobjects[selecttexturenum]->getPos().x + addvalue);
			}
			if (i == 1) {
				textureobjects[selecttexturenum]->setPosX(textureobjects[selecttexturenum]->getPos().x - addvalue);
			}
			if (i == 2) {
				textureobjects[selecttexturenum]->setPosY(textureobjects[selecttexturenum]->getPos().y - addvalue);
			}
			if (i == 3) {
				textureobjects[selecttexturenum]->setPosY(textureobjects[selecttexturenum]->getPos().y + addvalue);
			}
			if (i == 4) {
				textureobjects[selecttexturenum]->setPosZ(textureobjects[selecttexturenum]->getPos().z - addvalue);
			}
			if (i == 5) {
				textureobjects[selecttexturenum]->setPosZ(textureobjects[selecttexturenum]->getPos().z + addvalue);
			}
		}
	}
}

void CourseEditer::drawtrancerateSelectTextureObjButton()
{
	for (int i = 0;i < 6;i++) {
		DrawM.drawBoxEdge(buttons[i].pos,buttons[i].size,ColorA(1,1,1,1));
	}
}

void CourseEditer::drawSelectTextureValue()
{
	if (textureobjects.size() == 0)return;
	DrawM.drawFont(std::to_string(-int(textureobjects[selecttexturenum]->getPos().x)),
		Vec2f(1430.0f, 445.0f),Vec2f(1,1),0.0f, ColorA(1.0f, 1.0f, 1.0f, 1.0f), font);
	DrawM.drawFont(std::to_string(int(textureobjects[selecttexturenum]->getPos().y)),
		Vec2f(1430.0f, 545.0f), Vec2f(1, 1), 0.0f, ColorA(1.0f, 1.0f, 1.0f, 1.0f), font);
	DrawM.drawFont(std::to_string(int(textureobjects[selecttexturenum]->getPos().z)),
		Vec2f(1430.0f, 645.0f), Vec2f(1, 1), 0.0f, ColorA(1.0f, 1.0f, 1.0f, 1.0f), font);
	DrawM.drawFont(std::to_string(int(textureobjects[selecttexturenum]->getScale().x)),
		Vec2f(700.0f, 715.0f), Vec2f(1, 1), 0.0f, ColorA(0.0f, 0.0f, 0.0f, 1.0f), font);
	DrawM.drawFont(std::to_string(int(textureobjects[selecttexturenum]->getScale().y)),
		Vec2f(700.0f, 775.0f), Vec2f(1, 1), 0.0f, ColorA(0.0f, 0.0f, 0.0f, 1.0f), font);
	DrawM.drawFont(std::to_string(int(textureobjects[selecttexturenum]->getScale().z)),
		Vec2f(700.0f, 835.0f), Vec2f(1, 1), 0.0f, ColorA(0.0f, 0.0f, 0.0f, 1.0f), font);
	DrawM.drawFont(std::to_string(int(textureobjects[selecttexturenum]->getRotate().x)),
		Vec2f(1430.0f, 100.0f), Vec2f(1, 1), 0.0f, ColorA(1.0f, 1.0f, 1.0f, 1.0f), font);
	DrawM.drawFont(std::to_string(int(textureobjects[selecttexturenum]->getRotate().y)),
		Vec2f(1430.0f, 200.0f), Vec2f(1, 1), 0.0f, ColorA(1.0f, 1.0f, 1.0f, 1.0f), font);
	DrawM.drawFont(std::to_string(int(textureobjects[selecttexturenum]->getRotate().z)),
		Vec2f(1430.0f, 300.0f), Vec2f(1, 1), 0.0f, ColorA(1.0f, 1.0f, 1.0f, 1.0f), font);

	DrawM.drawFont(std::to_string(int(addvalue)),
		Vec2f(1310.0f, 400.0f), Vec2f(1, 1), 0.0f, ColorA(0.0f, 0.0f, 0.0f, 1.0f), font);
}

void CourseEditer::ChangeAddValue()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_UP)) {
		addvalue += 1;
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_DOWN)) {
		addvalue -= 1;
		if (addvalue <= 1)
			addvalue = 1;
	}
}

void CourseEditer::setSelectRange()
{
	scale_x_range.setRangeValue(textureobjects[selecttexturenum]->getScale().x/(12.f*WorldScale));
	scale_y_range.setRangeValue(textureobjects[selecttexturenum]->getScale().y / (12.f*WorldScale));
	scale_z_range.setRangeValue(textureobjects[selecttexturenum]->getScale().z / (12.f*WorldScale));
	rotate_x_range.setRangeValue(textureobjects[selecttexturenum]->getRotate().x / 360.f);
	rotate_y_range.setRangeValue(textureobjects[selecttexturenum]->getRotate().y / 360.f);
	rotate_z_range.setRangeValue(textureobjects[selecttexturenum]->getRotate().z / 360.f);

}

void CourseEditer::drawSelectTexture()
{
	Vec2f pos = Vec2f(100,WINDOW_HEIGHT-100);
	Vec2f size = Vec2f(100,100);
	DrawM.drawTextureBox(pos, size, 0, TextureM.getTexture(texturetype[selecttexture]), ColorA(1, 1, 1, 1));
}

void CourseEditer::CreateTextureTypeString()
{
	JsonTree maptree(loadAsset("Json/Editer/texturetype.json"));
	JsonTree maptexturetype = maptree["maptexture"];
	for (int i = 0;i < maptexturetype.getNumChildren();i++) {
		JsonTree child= maptexturetype.getChild(i);
		std::string name= child.getValueForKey<std::string>("texturename");
		std::string path = "Map/" + name;
		texturetype.push_back(path);
		textureisalphas.push_back(child.getValueForKey<bool>("isalpha"));
	}

	for (int i = 0;i < texturetype.size();i++) {
		TextureM.CreateTexture(texturetype[i]);
	}

}

void CourseEditer::setTextureSelectTextureObj()
{
	if (textureobjects.size() == 0)return;
	if (KeyManager::getkey().isPush(KeyEvent::KEY_l)) {
		textureobjects[selecttexturenum]->setPath(texturetype[selecttexture]);
		textureobjects[selecttexturenum]->setIsAlpha(textureisalphas[selecttexture]);
	}
}

void CourseEditer::selectTextureType()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_RIGHT)) {
		selecttexture++;
		selecttexture = selecttexture%texturetype.size();
	}
}

void CourseEditer::writeMap2dObjct()
{
	if (textureobjects.size() == 0)return;
	if (KeyManager::getkey().isPush(KeyEvent::KEY_s)) {
		std::vector<JsonTree>jsons;
		JsonTree kansei;
		for (int i = 0;i < textureobjects.size();i++)
		{
			JsonTree buf;
			buf.pushBack(JsonM.Vec3fToJson(textureobjects[i]->getPos(), "pos"));
			buf.pushBack(JsonM.Vec3fToJson(textureobjects[i]->getScale(), "scale"));
			buf.pushBack(JsonM.Vec3fToJson(textureobjects[i]->getRotate(), "rotate"));
			buf.pushBack(JsonTree("texturename", textureobjects[i]->getPath()));
			buf.pushBack(JsonTree("isalpha", textureobjects[i]->getIsAlpha()));
			jsons.push_back(buf);
		}
		for (int i = 0;i < jsons.size();i++) {
			kansei.pushBack(jsons[i]);
		}
		std::string path = "../assets/Json/Stage/World" + std::to_string(worldnum)
			+ "/Stage"+ std::to_string(stagenum)
			+"/Floor"+ std::to_string(floornum)
			+"/map2d.json";
		kansei.write(path);
	}
}

void CourseEditer::roadMap2dObject()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_r)) {
		textureobjects.clear();
		std::string jsonpath = "Json/Stage/World" + std::to_string(worldnum)
			+ "/Stage" + std::to_string(stagenum)
			+ "/Floor" + std::to_string(floornum)
			+ "/map2d.json";

		JsonTree maptree(loadAsset(jsonpath));

		for (int i = 0;i < maptree.getNumChildren();i++) {
			JsonTree child = maptree.getChild(i);
			std::string name = child.getValueForKey<std::string>("texturename");
			Vec3f pos = JsonM.getVec3(child,"pos");
			Vec3f scale = JsonM.getVec3(child, "scale");
			Vec3f rotate = JsonM.getVec3(child, "rotate");
			bool alptha = child.getValueForKey<bool>("isalpha");
			textureobjects.push_back(std::make_shared<TextureObj>(pos,scale,rotate,name,alptha));
		}
		selecttexturenum = 0;
		setSelectRange();
	}

}


std::string CourseEditer::getPath()
{
	std::string path = "MapData/World" + std::to_string(worldnum) +
		"/Stage" + std::to_string(stagenum) +
		"/Floor" + std::to_string(floornum)+"/";
	return path;
}

void CourseEditer::drawStageNum()
{
	ColorA color = ColorA(1, 1, 1, 1);
	DrawM.drawFont("w "+std::to_string(worldnum), Vec2f(0, 0), Vec2f(1,1), 0, color, font);
	DrawM.drawFont("s "+std::to_string(stagenum), Vec2f(100, 0), Vec2f(1,1), 0, color, font);
	DrawM.drawFont("f "+std::to_string(floornum), Vec2f(200, 0), Vec2f(1,1), 0, color, font);
}

void CourseEditer::changeStageNum()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_5)) {
		worldnum++;
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_6)) {
		worldnum--;
		worldnum = std::max(worldnum, 1);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_7)) {
		stagenum++;
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_8)) {
		stagenum--;
		stagenum = std::max(stagenum, 1);
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_9)) {
		floornum++;
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_0)) {
		floornum--;
		floornum = std::max(floornum, 1);
	}
}

void CourseEditer::createVar()
{
	TextureM.CreateTexture("UI/bar.png");
	TextureM.CreateTexture("UI/circlrepoint.png");
	float centerx = WINDOW_WIDTH - 150.f;
	float length = 250.f;
	float space = 100;
	Vec2f iconsize = Vec2f(40, 40);

	rotate_x_range = Range(Vec2f(centerx, space), length, iconsize, "UI/bar.png", "UI/circlrepoint.png", 0.f, 360.f, 0.0f);
	rotate_y_range = Range(Vec2f(centerx, space * 2), length, iconsize, "UI/bar.png", "UI/circlrepoint.png", 0.f, 360.f, 0.0f);
	rotate_z_range = Range(Vec2f(centerx, space * 3), length, iconsize, "UI/bar.png", "UI/circlrepoint.png", 0.f, 360.f, 0.0f);
	float centerscalepos = WINDOW_WIDTH - 600;
	float scalelength = 1200;
	float scalespace = 60.f;
	scale_x_range = Range(Vec2f(centerscalepos, WINDOW_HEIGHT - 3 * scalespace), scalelength, iconsize, "UI/bar.png", "UI/circlrepoint.png", 0.f, 12.f, 1.f / 12.f);
	scale_y_range = Range(Vec2f(centerscalepos, WINDOW_HEIGHT - 2 * scalespace), scalelength, iconsize, "UI/bar.png", "UI/circlrepoint.png", 0.f, 12.f, 1.f / 12.f);
	scale_z_range = Range(Vec2f(centerscalepos, WINDOW_HEIGHT - 1 * scalespace), scalelength, iconsize, "UI/bar.png", "UI/circlrepoint.png", 0.f, 12.f, 1.f / 12.f);
}

void CourseEditer::setUpButtons()
{
	for (size_t i = 0; i < 6; i++)
	{
		if (i % 2 == 0) {
			buttons[i].pos = Vec2f(WINDOW_WIDTH - 225, 400 + 100 * (i / 2));
		}
		else
		{
			buttons[i].pos = Vec2f(WINDOW_WIDTH - 125, 400 + 100 * (i / 2));
		}
		buttons[i].size = Vec2f(50, 50);
	}
}

void CourseEditer::ViewNowTextureObject()
{
	if (!(textureobjects.size() == 0)) {
		ColorA color;
		if (KeyManager::getkey().isPress(KeyEvent::KEY_q))color = ColorA(0.5, 0.5, 0.5, 1);
		else color = ColorA(1, 1, 1, 1);
		textureobjects[selecttexturenum]->setColor(color);
	}
}
