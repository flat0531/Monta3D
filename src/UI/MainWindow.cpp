#include "MainWindow.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/Top.h"
#include"../WorldCreater/CharacterManager.h"
#include"../WorldObject/Player.h"
#include"../WorldObject/Enemy.h"
#include"../Top/EasingManager.h"
#include <filesystem>
using namespace ci;
using namespace ci::app;
MainWindow::MainWindow()
{
	backgroundpath = "UI/mainwindowback.png";
	TextureM.CreateTexture(backgroundpath);
	TextureM.CreateTexture("UI/hpbar.png");
	TextureM.CreateTexture("UI/hpbarframe.png");
	TextureM.CreateTexture("UI/hpbarframered.png");
	TextureM.CreateTexture("UI/hpbarframebase.png");
	font = Font("Comic Sans MS", 65.0f);
	easing_hp_rate = 1.0f;
	prevhp_rate = 1.0f;
}

void MainWindow::draw()
{
	drawBackGround();
	drawPlayerTexture();
	drawPlayerStatus();
	drawPlayerHp();
	if (enemyid == 0)return;
	drawEnemyTexture();
	drawEnemyName();
	drawEnemyHp();
}

void MainWindow::setup()
{
	enemyid = 0;
	enemymaxhp = 0;
	enemyprevhp = 0;
}

void MainWindow::setCharacterManagerPtr(CharacterManager * _charactermanager)
{
	charactermanager = _charactermanager;
}

void MainWindow::setSelectTextureNum(const int num)
{
	TextureM.eraseTexture(playertexturepath);
	selecttexturenum = num;
	std::string name = charactermanager->getPlayer()->getName();
	playertexturepath = "Draw/" + name + "/play/play" + std::to_string(selecttexturenum)+".png";
	TextureM.CreateTexture(playertexturepath);
}

void MainWindow::setEnemyStatuts(std::string _enemyname, int _maxhp, int _hp, int id, ci::ColorA _uniquecolor)
{

	enemytexturepath = "Snap/" + _enemyname + "snap.png";
	enemyname = _enemyname;
	enemyid = id;
	enemymaxhp = _maxhp;
	enemyhp = _hp;
	enemy_hp_t = 0.0f;
	begin_enemy_hp_rate = (float(enemyprevhp) / float(enemymaxhp));
	end_enemy_hp_rate = std::max(float(enemyhp) / float(enemymaxhp),0.0f);
	enemyuniquecolor = _uniquecolor;
	TextureM.CreateTexture(enemytexturepath);
}

void MainWindow::update()
{
	updatePlayerHpBar();
	updateEnemyHpBar();
}

void MainWindow::updatePlayerHpBar()
{
	float _hp_rate = float(charactermanager->getPlayer()->getHp()) / float(charactermanager->getPlayer()->getMaxHp());
	if (_hp_rate != prevhp_rate) {
		playerhp_t = 0.0f;
		begin_hprate = prevhp_rate;
		end_hprate = std::max(_hp_rate,0.0f);
		delay_t = 0.0f;
	}
	EasingManager::tCount(delay_t, 1.0f);
	if (EasingManager::tCountEnd(delay_t)) {
		easing_hp_rate = EasingCircOut(playerhp_t, begin_hprate, end_hprate);
		EasingManager::tCount(playerhp_t, 1.0f);
	}
	prevhp_rate = _hp_rate;

}

void MainWindow::updateEnemyHpBar()
{
	
	if (!EasingManager::tCountEnd(enemy_hp_t)) {
		easing_enemy_hp_rate = EasingCircOut(enemy_hp_t, begin_enemy_hp_rate, end_enemy_hp_rate);
		EasingManager::tCount(enemy_hp_t, 1.0f);
	}
}

void MainWindow::setEnemyHp(const int _hp)
{
	enemyhp = _hp;
	enemy_hp_t = 0.0f;
	begin_enemy_hp_rate = (float(enemyprevhp) / float(enemymaxhp));
	end_enemy_hp_rate = std::max(float(enemyhp) / float(enemymaxhp),0.0f);
}

void MainWindow::setPrevEnemyHp(const int hp)
{
	enemyprevhp = hp;
}



MainWindow * MainWindow::getThisPtr()
{
	return this;
}

int MainWindow::getEnemyId()
{
	return enemyid;
}

void MainWindow::drawBackGround()
{
	Vec2f size = Vec2f(WINDOW_WIDTH, 230);
	Vec2f pos = Vec2f(0, WINDOW_HEIGHT-size.y);
	DrawM.drawTextureBoxEdge(pos, size,TextureM.getTexture(backgroundpath), ColorA(1, 1, 1, 1));
}

void MainWindow::drawPlayerTexture()
{
	Vec2f size = Vec2f(200, 200);
	Vec2f pos = Vec2f(10, WINDOW_HEIGHT - size.y);
	DrawM.drawTextureBoxEdge(pos, size, TextureM.getTexture(playertexturepath), ColorA(1, 1, 1, 1));
}
void MainWindow::drawEnemyTexture()
{
              //�G�l�~�[���N���o�^����ĂȂ���΃��^�[��
	Vec2f size = Vec2f(180, 180);
	Vec2f pos = Vec2f(WINDOW_WIDTH-515, WINDOW_HEIGHT - size.y-20);
	DrawM.drawTextureBoxEdge(pos, size, TextureM.getTexture(enemytexturepath), ColorA(1, 1, 1, 1));
}
void MainWindow::drawEnemyName()
{
	Vec2f pos = Vec2f(1270, WINDOW_HEIGHT - 180);
	Vec2f size = Vec2f(1, 1);
	DrawM.drawFont(enemyname, pos + Vec2f(1.5, -1.5), size, 0.0f, ColorA(0, 0, 0, 1), font);
	DrawM.drawFont(enemyname, pos, size, 0.0f, enemyuniquecolor, font);

}
void MainWindow::drawEnemyHp()
{
	Vec2f pos = Vec2f(1270, WINDOW_HEIGHT - 50);
	Vec2f scale = Vec2f(0.5, 0.6);
	float hp_rate = std::max(float(enemyhp) / float(enemymaxhp),0.0f);

	DrawM.drawTextureArea(pos, scale,
		TextureM.getTexture("UI/hpbarframebase.png"), Area(Vec2i(0, 0),
			Vec2i(TextureM.getTexture("UI/hpbarframebase.png").getSize())), 1.0f);

	DrawM.drawTextureArea(pos, scale,
		TextureM.getTexture("UI/hpbarframered.png"), Area(Vec2i(0, 0),
			Vec2i(TextureM.getTexture("UI/hpbarframered.png").getSize())), easing_enemy_hp_rate);

	DrawM.drawTextureArea(pos, scale,
		TextureM.getTexture("UI/hpbar.png"), Area(Vec2i(0, 0),
			Vec2i(TextureM.getTexture("UI/hpbar.png").getSize())), hp_rate);

	DrawM.drawTextureArea(pos, scale,
		TextureM.getTexture("UI/hpbarframe.png"), Area(Vec2i(0, 0),
			Vec2i(TextureM.getTexture("UI/hpbarframe.png").getSize())), 1.0f);


}
void MainWindow::drawPlayerStatus()
{
	Vec2f pos = Vec2f(220,WINDOW_HEIGHT-210);
	Vec2f size = Vec2f(1,1);
	DrawM.drawFont(charactermanager->getPlayer()->getName(), pos + Vec2f(1.5, -1.5), size, 0.0f, ColorA(0, 0, 0, 1), font);
	DrawM.drawFont(charactermanager->getPlayer()->getName(), pos, size, 0.0f, charactermanager->getPlayer()->getUniqueColor(), font);

	


}
void MainWindow::drawPlayerHp()
{
	Vec2f pos = Vec2f(230, WINDOW_HEIGHT - 80);
	Vec2f scale = Vec2f(0.8,0.8);
	DrawM.drawTextureArea(pos, scale,
		TextureM.getTexture("UI/hpbarframebase.png"), Area(Vec2i(0, 0),
			Vec2i(TextureM.getTexture("UI/hpbarframebase.png").getSize())), 1.0f);

	DrawM.drawTextureArea(pos,scale,
		TextureM.getTexture("UI/hpbarframered.png"), Area(Vec2i(0, 0),
			Vec2i(TextureM.getTexture("UI/hpbarframered.png").getSize())), easing_hp_rate);

	DrawM.drawTextureArea(pos, scale,
		TextureM.getTexture("UI/hpbar.png"), Area(Vec2i(0, 0),
			Vec2i(TextureM.getTexture("UI/hpbar.png").getSize())), std::max(prevhp_rate,0.0f));

	DrawM.drawTextureArea(pos, scale,
		TextureM.getTexture("UI/hpbarframe.png"), Area(Vec2i(0, 0),
			Vec2i(TextureM.getTexture("UI/hpbarframe.png").getSize())),1.0f);

	
}
//int num = 0;
//for (std::tr2::sys::directory_iterator it("../assets/Texture/Draw/"+
//	charactermanager->getPlayer()->getName()+"/play"), end; it != end; it++)
//{
//	num++;
//}