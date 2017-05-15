#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class CharacterManager;
class MainWindow {
public:
	MainWindow();
	void draw();
	void setup();
	void setCharacterManagerPtr(CharacterManager* _charactermanager);
	void setSelectTextureNum(const int num);
	void setEnemyStatuts(std::string _enemyname, int _maxhp, int _hp, int id,ci::ColorA _uniquecolor);
	void update();
	void setEnemyHp(const int _hp);
	void setPrevEnemyHp(const int hp);
	MainWindow* getThisPtr();
	int getEnemyId();
private:
	void drawBackGround();
	int enemyid = 0;
	int enemymaxhp = 0;
	int enemyhp = 0;
	int enemyprevhp;//敵がダメージを食らう前のHP
	float enemy_hp_t = 1.0f;
	float begin_enemy_hp_rate = 1.0f;
	float easing_enemy_hp_rate = 1.0f;
	float end_enemy_hp_rate = 1.0f;
	ci::ColorA enemyuniquecolor;
	float playerhp_t = 1.0f;
	float easing_hp_rate;
	float prevhp_rate;
	float delay_t = 1.0f;
	float begin_hprate = 1.0f;
	float end_hprate = 1.0f;
	std::string backgroundpath;
	std::string enemyname;
	CharacterManager* charactermanager;
	ci::Font font;
	std::string playertexturepath = "";
	std::string enemytexturepath = "";
	void drawPlayerTexture();
	void drawEnemyTexture();
	void drawEnemyName();
	void drawEnemyHp();
	void drawPlayerStatus();
	void drawPlayerHp();
	void updatePlayerHpBar();
	void updateEnemyHpBar();
	int selecttexturenum = 1;
};