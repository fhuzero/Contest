#pragma once

#include "RGV.h"
#include <list>

using namespace std;

CNC* getDest(list<CNC*> waitLoadList, list<CNC*> processList, list<CNC*> waitUnloadList)
{
	//initial value
	int max_waitCNC, max_Pos;  //actually the minimum value
	bool flag = false;

	if(!waitLoadList.empty()){
		max_waitCNC = (*waitLoadList.begin())->workRemainTime；
		max_Pos = (*waitLoadList.begin())->Pos;
		CNC *ret_CNC = *waitLoadList.begin();
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
	if(!processList.empty()){
		if(!flag){
			max_waitCNC = (*processList.begin())->workRemainTime；
			max_Pos = (*processList.begin())->Pos;
			CNC *ret_CNC = *processList.begin();
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
	if(!waitUnloadList.empty()){
		if(!flag){
			max_waitCNC = (*waitUnloadList.begin())->workRemainTime；
			max_Pos = (*waitUnloadList.begin())->Pos;
			CNC *ret_CNC = *waitUnloadList.begin();
			flag = true;
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
	}
	if(!flag){
		cerr<< "All list is empty!" <<endl;
	}
	return ret_CNC;
}
