#pragma once

#include <list>

using namespace std;

// the state of CNC: waiting for loading, loading, processing
enum CNCStateT { Waitload, CNCLoad, Waitprocess, Process};

class CNC
{

public:

	int Pos; // position
	int LoadTime; // load and unload time
	int ProcessTime;
	int workRemainTime;
	CNCStateT state;
	list<CNC*>* waitLoadList;
	list<CNC*>* processList;
	int currentTime;


	void init(int pos, int loadtime, int processtime, 
		list<CNC*>* _waitLoadList, list<CNC*>* _processList)
	{
		Pos = pos;
		LoadTime = loadtime;
		ProcessTime = processtime;
		workRemainTime = 0;
		waitLoadList = _waitLoadList;
		processList = _processList;

		// init
		state = Waitload;  
		waitLoadList->push_back(this);

	}


	void updateRemainTime()
	{
		--workRemainTime;
	}

	void endWork();


	void startLoad();

	void endLoad();

	void startProcess();

	void endProcess();

};


