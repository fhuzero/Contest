#pragma once

#include <list>

using namespace std;

// the state of CNC: waiting for loading, loading, processing, waiting for unloading, unloading
enum CNCStateT { Waitload, CNCLoad, Waitprocess, Process, Waitunload, CNCUnload };

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
	list<CNC*>* waitUnloadList;
	int currentTime;


	void init(int pos, int loadtime, int processtime, 
		list<CNC*>* _waitLoadList, list<CNC*>* _processList, list<CNC*>* _waitUnloadList)
	{
		Pos = pos;
		LoadTime = loadtime;
		ProcessTime = processtime;
		workRemainTime = 0;
		waitLoadList = _waitLoadList;
		processList = _processList;
		waitUnloadList = _waitUnloadList;
		endUnload();  // init

	}


	void updateState()
	{
		--workRemainTime;
	}

	void endWork();


	void startLoad();

	void endLoad();

	void startProcess();

	void endProcess();

	void startUnload();

	void endUnload();
};


