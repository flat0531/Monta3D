#include "Player.h"
#include"../Top/Top.h"
#include"../Input/KeyManager.h"
#include"../CharacterAction/ActionBase.h"
#include"../CharacterAction/SlimeAction.h"
#include"../CharacterAction/CatAction.h"
#include"../WorldObject/PlayerDirection.h"
#include"../Top/EasingManager.h"
#include"../WorldCreater/ShadowManager.h"
using namespace ci;
using namespace ci::app;
Player::Player()
{
	
}

Player::Player(ci::Vec3f _pos, ActionType _actiontype, ShadowManager * _shadowmanager)
{
	pos = _pos;
	speed = Vec3f(0, 0, 0);
	drawpos = pos;
	scale = Vec3f(1, 1, 1)*WorldScale;
	rotate = Vec3f(0, -180, 0);
	easing_start_rotate = 0.0f;
	playerdirection = PlayerDirection::RIGHT_DIRECTION;
	canjump = false;
	jumpcount = 0;
	jumpping = false;
	charactertype = CharacterType::CHARACTER_PLAYER;
	actiontype = _actiontype;
	direction_t = 0.0f;
	isoperate = true;
	maxhp = 75;
	hp = maxhp;
	shadowmanager = _shadowmanager;
}

void Player::update()
{
	prevpos = pos;


	if (isoperate&&(!isstun)) {
		PlayerDirection buf = playerdirection;
		playerdirection = disideDirection();
		if (buf != playerdirection) {
			direction_t = 0.0f;
			easing_start_rotate = rotate.y;
		}
	}
	RotateEasing();
	
	EasingManager::tCount(direction_t, 0.4f);
	jumpcount++;



	updateStun();
	if (KeyManager::getkey().isPush(KeyEvent::KEY_y)) {
		hp = 0.0f;
	}
	if (pos.y <= -WorldScale*5.f) {
		hp = 0.0f;
	}
	action->update();

	pos += speed;
	drawpos = pos;
}

void Player::draw()
{
	action->draw();
}

void Player::setup(ci::Vec3f _pos)
{
	
}

void Player::Reset(ci::Vec3f rotate)
{
	action->setup(rotate);
}

bool Player::IsJumpping()
{
	return jumpping;
}


int Player::getjumpCount()
{
	return jumpcount;
}


void Player::setJumming(const bool is)
{
	jumpping = is;
}

void Player::RotateEasing()
{
	rotate.y = EasingCubicOut(direction_t, easing_start_rotate, getAttackRotate());
}



void Player::CanJumpCountUp()
{
	jumpcount++;
}

PlayerDirection Player::getplayerdirection()
{
	return playerdirection;
}

void Player::setPlayerDirection(PlayerDirection _playerdirection)
{
	playerdirection = _playerdirection;
}

float Player::getAttackRotate()
{
	switch (playerdirection)
	{
	case PlayerDirection::LEFT_DIRECTION:
		return 0.0f;
	case PlayerDirection::LEFT_UP_DIRECTION:
		return -45.f;
	case PlayerDirection::RIGHT_DIRECTION:
		return -180;
	case PlayerDirection::RIGHT_UP_DIRECTION:
		return -135.f;
	case PlayerDirection::UP_DIRECTION:
		return -90.f;
	case PlayerDirection::NONE_DIRECTION:
		return getRotate().y;
	}
	return getRotate().y;
}

void Player::setT(const float t)
{
	direction_t = t;
}

bool Player::GetIsOperate()
{
	return isoperate;
}

void Player::SetIsOpetate(const bool is)
{
	isoperate = is;
}

PlayerDirection Player::disideDirection()
{
	bool isleft = KeyManager::getkey().isPress(KeyEvent::KEY_a);
	bool isright = KeyManager::getkey().isPress(KeyEvent::KEY_d);
	bool isup = KeyManager::getkey().isPress(KeyEvent::KEY_w);

	
	if (isright) {
		return PlayerDirection::RIGHT_DIRECTION;
	}
	if (isleft) {
		return PlayerDirection::LEFT_DIRECTION;
	}
	if (isup) {
		return PlayerDirection::UP_DIRECTION;
	}
	
	return playerdirection;
}