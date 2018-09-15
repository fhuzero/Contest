#pragma once

#include <vector>
#include <list>
#include "CNC.h"


// the state of RGV: (init), stop, run, load, unload, clean
// when loading, unloading and cleaning, RGV cannot move
// wait is similar to stop, but the task has been distributed
enum RGVStateT { Stop, Wait, Waitclean, Run, Load, Unload, Clean };

class RGV
{
private:


public:
	int pos; // position
	RGVStateT state;
	int workRemainTime;
	CNC* dest;
	vector<int> RGVMoveTime;
	int CleanTime;

	list<CNC*>* waitLoadList;
	list<CNC*>* processList;
	list<CNC*>* waitUnloadList;


	void init(vector<int> RGVmovetime, int cleantime, 
		list<CNC*>* _waitLoadList, list<CNC*>* _processList, list<CNC*>* _waitUnloadList)
	{
		RGVMoveTime = RGVmovetime;
		CleanTime = cleantime;
		pos = 1;
		state = Stop;
		workRemainTime = 0;
		dest = nullptr;
		waitLoadList = _waitLoadList;
		processList = _processList;
		waitUnloadList = _waitUnloadList;
	}

	void startWork();

	void endWork()
	{
		if (workRemainTime == 0) {

			cout << "[" << currentTime << "]" << "[RGV]";

			switch (state)
			{
			case Stop: case Wait:
				break;

			case Run:

				endRun();
				break;

			case Load:
				endLoad();
				break;

			case Clean:
				endClean();
				break;

			case Unload:
				endUnload();
				break;

			default:
				break;
			}
		}
	}

	void startRun()
	{
		cout << "start run, pos:" << pos << ", dest pos:" << dest->Pos << endl;
		int truePos = (pos - 1) / 2;
		int trueDestPos = (dest->Pos - 1) / 2;
		int dist = abs(truePos - trueDestPos);

		workRemainTime = RGVMoveTime[dist];
		state = Run;

		// pos == destpos
		if (workRemainTime == 0)
			endRun();
	}

	void endRun()
	{
		pos = dest->Pos;
		cout << "end run, pos:" << pos << endl;
		state = Wait;
	}

	void startClean()
	{
		cout << "start clean" << endl;
		workRemainTime = CleanTime;
		state = Clean;
	}

	void endClean()
	{
		cout << "end clean" << endl;
		state = Stop;
	}

	void startLoad()
	{
		cout << "start load" << endl;
		dest->startLoad();
		workRemainTime = dest->workRemainTime;
		state = Load;
	}

	void endLoad()
	{
		cout << "end load" << endl;
		state = Stop;
	}

	void startUnload()
	{
		cout << "start unload" << endl;
		dest->startUnload();
		workRemainTime = dest->workRemainTime;
		state = Unload;

	}

	void endUnload()
	{
		cout << "end unload" << endl;
		state = Waitclean;
	}

	void updateState()
	{

		--workRemainTime;


	}
};