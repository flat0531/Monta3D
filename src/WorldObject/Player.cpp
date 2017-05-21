#include "Player.h"
#include"../Top/Top.h"
#include"../Input/KeyManager.h"
#include"../CharacterAction/ActionBase.h"
#include"../CharacterAction/SlimeAction.h"
#include"../CharacterAction/CatAction.h"
#include"../WorldObject/PlayerDirection.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
Player::Player()
{
	
}

Player::Player(ci::Vec3f _pos, ActionType _actiontype)
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
	maxhp = 100;
	hp = maxhp;
}

void Player::update()
{
	prevpos = pos;
	
	pos += speed;

	if (isoperate&&(!isstun)) {
		PlayerDirection buf = playerdirection;
		playerdirection = disideDirection();
		if (buf != playerdirection) {
			direction_t = 0.0f;
			easing_start_rotate = rotate.y;
		}
	}
	
	rotate.y = EasingLinear(direction_t, easing_start_rotate, getAttackRotate());
	EasingManager::tCount(direction_t, 0.15f);
	jumpcount++;
	drawpos = pos;


	updateStun();
	if (pos.y <= -WorldScale*5.f) {
		hp = 0.0f;
	}
	action->update();
}

void Player::draw()
{
	action->draw();
}

void Player::setup(ci::Vec3f _pos)
{
	
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

	if (isup&&isright&&isleft) {
		return PlayerDirection::UP_DIRECTION;
	}
	if (isright&&isup) {
		return PlayerDirection::RIGHT_UP_DIRECTION;
	}
	if (isleft&&isup) {
		return PlayerDirection::LEFT_UP_DIRECTION;
	}
	if (isup) {
		return PlayerDirection::UP_DIRECTION;
	}
	if (isright) {
		return PlayerDirection::RIGHT_DIRECTION;
	}
	
	if (isleft) {
		return PlayerDirection::LEFT_DIRECTION;
	}
	return PlayerDirection::NONE_DIRECTION;
}











//std::string run = "Armature|run", walk = "walk.001";
//if (KeyManager::getkey().isPress(KeyEvent::KEY_a)) {
//	player_p->speed += Vec3f(speed, 0, 0);
//	player_p->rotate.y -= 10.0f;
//	player_p->rotate.y = std::max(player_p->rotate.y, -180.f);
//	if (current_animation_stack_string != run) {
//		setAnimation(run);
//	}
//	//console() << player_p->rotate.y << std::endl;
//}
//
//if ((!KeyManager::getkey().isPress(KeyEvent::KEY_a)) && (!KeyManager::getkey().isPress(KeyEvent::KEY_d))) {
//	if (current_animation_stack_string != walk) {
//		setAnimation(walk);
//	}
//}
//
//if (KeyManager::getkey().isPress(KeyEvent::KEY_d)) {
//	player_p->rotate.y += 10.0f;
//	player_p->rotate.y = std::min(player_p->rotate.y, 0.f);
//	player_p->speed += Vec3f(-speed, 0, 0);
//	//console() << player_p->rotate.y << std::endl;
//	if (current_animation_stack_string != run) {
//		setAnimation(run);
//	}
//}