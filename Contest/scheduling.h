#pragma once

#include "RGV.h"
#include <list>

using namespace std;

CNC* getDest(list<CNC*> waitLoadList, list<CNC*> processList, list<CNC*> waitUnloadList)
{
	//initial value
	int max_waitCNC = (*waitLoadList.begin())->workRemainTime,
		max_Pos = (*waitLoadList.begin())->Pos;  //actually the minimum value


	CNC *ret_CNC = *waitLoadList.begin();
	for (auto iter = waitLoadList.begin(); iter != waitLoadList.end(); iter++)
	{
		if ((*iter)->workRemainTime < max_waitCNC)
		{
			max_waitCNC = (*iter)->workRemainTime;
			//max_Pos = *iter->Pos;
			ret_CNC = *iter;
		}
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
	for (auto iter = waitUnloadList.begin(); iter != waitUnloadList.end(); iter++)
	{
		if ((*iter)->workRemainTime < max_waitCNC)
		{
			max_waitCNC = (*iter)->workRemainTime;
			//max_Pos = *iter->Pos;
			ret_CNC = *iter;
		}
	}
	return ret_CNC;
}