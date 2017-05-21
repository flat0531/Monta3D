#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <cinder/AxisAlignedBox.h>
#include"../CharacterAction/ActionBase.h"
#include<memory>
enum CharacterType {
	CHARACTER_PLAYER,CHARACTER_ENEMY,CHARACTER_GIMMICK,CHARACTER_NONE
};
class BulletManager;
class CharacterManager;
class CharacterBase {
public:
	CharacterBase();
	virtual void update() {};
	virtual void draw() {};
	virtual void setup(ci::Vec3f _pos) {};
	int getHp();
	int getMaxHp();
	int getId();
	ci::Vec3f getPos();
	ci::Vec2f getPos2f();
	ci::Vec3f getSpeed();
	ci::Vec3f getScale();
	ci::Vec2f getScale2f();
	ci::Vec3f getRotate();
	ci::Vec3f getDrawPos();
	ci::Vec3f getPrevPos();
	std::string getName();
	bool getIsAlive();
	void setHp(int _hp);
	void setMaxHp(int _maxhp);
	void addHpValue(int value);
	void setPos(const ci::Vec3f _pos);
	void setPosX(const float posx);
	void setPosY(const float posy);
	void setPosZ(const float posz);
	void setDrawPos(const ci::Vec3f _pos);
	void setDrawPosX(const float posx);
	void setDrawPosY(const float posy);
	void setPrevPos(const ci::Vec3f _pos);
	void setRotate(const ci::Vec3f _rotate);
	void setRotateX(const float rotatex);
	void setRotateY(const float rotatey);
	void setRotateZ(const float rotatez);
	void rotation(const ci::Vec3f _rotate);
	void setSpeed(const ci::Vec3f _speed);
	void setSpeedX(const float speedx);
	void setSpeedY(const float speedy);
	void setSpeedZ(const float speedz);
	void setScale(const ci::Vec3f _scale);
	void setName(const std::string _name);
	void AddForth(const ci::Vec3f _forth);
	void setCanJumpCount(const int count);
	void decideAction(ActionType folm);
	void SetBulletManagerPointer(BulletManager* _bulletmanager);
	void setActionType(ActionType _actiontype);
	void setCharacterManagerPointer(CharacterManager* charactermanager);
	void setQuat(ci::Quatf _quat);
	void setBulletQuat(ci::Quatf _quat);
	void setJumpPower();
	void RsetDeathColorT();
	void updateDeath(float time);
	CharacterManager* getCharacterManager();
	BulletManager* getBulletManagerPointer();
	CharacterType getCharacterType();
	ci::AxisAlignedBox3f getAABB();
	CharacterBase* getThisPointer();
	ActionType getActiontype();
	ci::Quatf getQuat();
	ci::Quatf getBulletQuat();
	bool getIsStan();
	bool updateDeathEnd();
	void setIsStun(const bool is);
	void setIsinvincible(const bool is);
	bool getIsInvincible();
	void setDefalutColor(const ci::ColorA _color);
	void setColor(const ci::ColorA _color);
	ci::ColorA getColor();
	ci::ColorA getUniqueColor();
	ci::ColorA getDefaultColor();
	void setUniqueColor(ci::ColorA _color);
	bool getCanJump();
	void setCanJump(const bool is);
	template<class T>
	void setCharacterAction(T);
protected:
	ci::Vec3f pos;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	ci::Vec3f prevpos;
	ci::Vec3f drawpos;
	ci::Vec3f speed;
	ci::Quatf quat;
	ci::Quatf bulletquat;
	std::string name;
	int hp = 100;
	int maxhp = 100;
	bool isalive = true;
	bool isclear = false;
	bool isstun = false;
	bool issnvincible = false;
	bool canjump = true;
	float death_color_t = 0.0f;
	int invinciblecount = 0;
	int stuncount = 0;
	int jumpcount = 0;
	int id = 0;//éØï î‘çÜ
	ci::ColorA color;
	ci::ColorA defaultcolor;
	ci::ColorA uniquecolor;//ÇªÇÃÉLÉÉÉâÇÃë„ñºéåìIÇ»êF
	BulletManager* bulletmanager;
	ActionType playerfolm = NONE;
	CharacterType charactertype= CHARACTER_NONE;
	std::shared_ptr<ActionBase> action;
	ci::AxisAlignedBox3f aabbbox;
	ActionType actiontype;
	CharacterManager* charactermanagerptr;
	void updateStun();
};

template<class T>
inline void CharacterBase::setCharacterAction(T)
{
	action = std::make_shared<T>(this);
}
