#pragma once

#include "CNC.h"

using namespace std;

CNC * getDest(const list<CNC*>& waitLoadList, const list<CNC*>& processList)
{
	//initial value
	int max_waitCNC, max_Pos;  //actually the minimum value
	bool flag = false;
	CNC *ret_CNC = nullptr;

	if (!waitLoadList.empty()) {
		max_waitCNC = (*waitLoadList.begin())->workRemainTime;
		max_Pos = (*waitLoadList.begin())->Pos;
		ret_CNC = *waitLoadList.begin();
		flag = true;
		for (auto iter = waitLoadList.begin(); iter != waitLoadList.end(); iter++)
		{
			if ((*iter)->workRemainTime < max_waitCNC)
			{
				max_waitCNC = (*iter)->workRemainTime;
				//max_Pos = *iter->Pos;
				ret_CNC = *iter;
			}
		}
	}
	if (!processList.empty()) {
		if (!flag) {
			max_waitCNC = (*processList.begin())->workRemainTime;
			max_Pos = (*processList.begin())->Pos;
			ret_CNC = *processList.begin();
			flag = true;
		}
		for (auto iter = processList.begin(); iter != processList.end(); iter++)
		{
			if ((*iter)->workRemainTime < max_waitCNC)
			{
				max_waitCNC = (*iter)->workRemainTime;
				//max_Pos = *iter->Pos;
				ret_CNC = *iter;
			}
		}
	}
	if (!flag) {
		cerr << "All list is empty!" << endl;
	}
	return ret_CNC;
}
