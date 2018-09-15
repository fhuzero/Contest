#pragma once


#include "CNC.h"


#include <fstream>
#include <string>


using namespace std;

// the state of RGV: (init), stop, run, load, unload, clean
// when loading, unloading and cleaning, RGV cannot move
// wait is similar to stop, but the task has been distributed
enum RGVStateT { Stop, Wait, Waitclean, Run, Load, Unload, Clean };

struct Material
{
	int no;
	int pos;
	int startLoadTime;
	int endLoadTime;
	int startProcessTime;
	int endProcessTime;
	int startUnloadTime;
	int endUnloadTime;
	string toString()
	{
		// 加工物料序号	加工CNC编号	上料开始时间	下料开始时间
		return to_string(no) + "," + to_string(pos) + "," + to_string(startLoadTime) + ","
			+ to_string(startUnloadTime) + "\n";
	}

	void clear()
	{
		no = pos = startLoadTime = endLoadTime = startProcessTime = endProcessTime
			= startProcessTime = endProcessTime = startUnloadTime = endLoadTime
			= -1;

	}
};


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
	int currentTime;

	list<CNC*>* waitLoadList;
	list<CNC*>* processList;
	list<CNC*>* waitUnloadList;

	ofstream file;
	int materialNumber;
	vector<Material> currentMaterials;
	

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
		file.open("data.csv", ios::out);
		materialNumber = 0;
		currentMaterials = vector<Material>(9);
		for (auto m : currentMaterials)
			m.clear();
	}

	void startWork();

	void endWork()
	{
		if (workRemainTime == 0) {

			

			switch (state)
			{
			case Stop: case Wait:
				break;

			case Run:
				cout << "[" << currentTime << "]" << "[RGV]";
				endRun();
				break;

			case Load:
				cout << "[" << currentTime << "]" << "[RGV]";
				endLoad();
				break;

			case Clean:
				cout << "[" << currentTime << "]" << "[RGV]";
				endClean();
				break;

			case Unload:
				cout << "[" << currentTime << "]" << "[RGV]";
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
		if (workRemainTime == 0) {
			cout << "[" << currentTime << "]";
			endRun();
		}
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
		cout << "[" << currentTime << "]";
		dest->startLoad();
		workRemainTime = dest->workRemainTime;
		state = Load;
		
		currentMaterials[dest->Pos].startLoadTime = currentTime;

	}

	void endLoad()
	{
		cout << "end load" << endl;
		state = Stop;
	}

	void startUnload()
	{
		cout << "start unload" << endl;
		cout << "[" << currentTime << "]";


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