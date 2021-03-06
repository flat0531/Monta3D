#pragma once
#include<vector>
#include<memory>
class MapChipBase;
class CharacterManager;
class BulletManager;
class EffectManager;
enum MapChipType;
class MapChipManager {
public:
	MapChipManager();
	void setup(const int worldnum, const int stagenum,const int floornum);
	void update();
	void draw();
	std::vector<std::vector<MapChipType>> ReadData(const int worldnum, const int stagenum,const int floornum,const int zvalue);
	void setBulletManagerPointer(BulletManager* _bulletmanager);
	void setCharacterManagerPointer(CharacterManager* _CharacterManager);
	void setEffectManagerPointer(EffectManager* _effectmanager);
	void CreateMap(const int worldnum, const int stagenum,const int floornum ,const int zvalue);
	ci::Vec2f getChipsSize();
	void setGoal(const std::function<void()> func);////ゴールした時の関数をゲームメインから取得
	MapChipManager* getThisPtr();
	std::vector<std::vector<std::shared_ptr<MapChipBase>>> getMapChips();
	std::vector<std::vector<std::shared_ptr<MapChipBase>>>& getMapChipsP();
private:
	std::function<void()> goal;////ゴールした時の関数
	std::vector<std::vector<std::shared_ptr<MapChipBase>>> mapchips;
	BulletManager* bulletmanagerptr;
	CharacterManager* characterManagerptr;
	EffectManager* effectmanagerptr;
	void updateMapChip();
	void CollisionPlayerToMap();
	void CollisionEnemysToMap();
	void CollisionPlayerBulletToMap();
	void CollisionEnemyBulletToMap();
	void CollisionBossBulletToMap();
	std::string getPath(const int worldnum,const int stagenum,const int floornum);
	void createAsset();
};