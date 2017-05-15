#include "StageData.h"

StageData::StageData()
{
}

StageData::StageData(bool _isclear, std::vector<bool> _isgetitem)
{
	isclear = _isclear;
	isgetitem = _isgetitem;
}

bool StageData::getIsClear()
{
	return isclear;
}

std::vector<bool> StageData::getIsItem()
{
	return isgetitem;
}
