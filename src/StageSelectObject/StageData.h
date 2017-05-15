#pragma once
#include<vector>
class StageData {
public:
	StageData();
	StageData(bool _isclear,std::vector<bool> _isgetitem);
	bool getIsClear();
	std::vector<bool> getIsItem();
private:
	bool isclear;
	std::vector<bool> isgetitem;
};