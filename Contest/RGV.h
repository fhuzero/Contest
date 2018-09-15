#pragma once

#include <list>
#include <iostream>
#include <cmath>

using namespace std;

// the state of CNC: waiting for loading, loading, processing, waiting for unloading, unloading
enum CNCStateT { Waitload, CNCLoad, Process, Waitunload, CNCUnload };

class CNC;

list<CNC*> waitLoadList, processList, waitUnloadList;

class CNC
{

public:

	int Pos; // position
	int LoadTime; // load and unload time
	int ProcessTime;
	int workRemainTime;
	CNCStateT state;


	void init(int pos, int loadtime, int processtime)
	{
		Pos = pos;
		LoadTime = loadtime;
		ProcessTime = processtime;
		workRemainTime = 0;
		endUnload();  // init
	}


	void updateState()
	{

		--workRemainTime;

		switch (state)
		{
		case Waitload:case Waitunload:
			break;

		case CNCLoad:

			if (workRemainTime == 0) {
				endLoad();
			}
			break;

		case Process:
			if (workRemainTime == 0) {
				endProcess();
			}

			break;

		case CNCUnload:
			if (workRemainTime == 0) {
				endUnload();
			}
			break;

		default:
			break;
		}
	}


	void startLoad()
	{
		cout << "[CNC" << Pos << "]start load; ";
		workRemainTime = LoadTime;
		state = CNCLoad;
		waitLoadList.remove(this);
	}

	void endLoad()
	{
		cout << "[CNC" << Pos << "]end load; ";

		// after loading, start processing immediately
		startProcess();
		processList.push_back(this);
	}

	void startProcess()
	{
		cout << "[CNC" << Pos << "]start process; ";
		workRemainTime = ProcessTime;
		state = Process;
		processList.remove(this);
	}

	void endProcess()
	{
		cout << "[CNC" << Pos << "]end process; ";
		state = Waitunload;
		processList.remove(this);
		//waitLoadList.push_back(this);
	}

	void startUnload()
	{
		cout << "[CNC" << Pos << "]start unload; ";
		if (state != Waitunload)
			cout << "Error!";
		workRemainTime = LoadTime;
		state = CNCUnload;

	}

	void endUnload()
	{
		cout << "[CNC" << Pos << "]end unload; ";
		state = Waitload;
		//waitUnloadList.push_back(this);
		waitLoadList.push_back(this);
	}
};

// the state of RGV: (init), stop, run, load, unload, clean
// when loading, unloading and cleaning, RGV cannot move
// wait is similar to stop, but the task has been distributed
enum RGVStateT { Stop, Wait, Run, Load, Unload, Clean };

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



	void init(vector<int> RGVmovetime, int cleantime)
	{
		RGVMoveTime = RGVmovetime;
		CleanTime = cleantime;
		pos = 1;
		state = Stop;
		workRemainTime = 0;
		dest = nullptr;
	}


	void startRun()
	{
		cout << "[RGV]start run, pos:" << pos << ", dest pos:" << dest->Pos << "; ";
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
		cout << "[RGV]end run, pos:" << pos << "; ";
		state = Wait;
	}

	void startClean()
	{
		cout << "[RGV]start clean; ";
		workRemainTime = CleanTime;
		state = Clean;
	}

	void endClean()
	{
		cout << "[RGV]end clean; ";
		state = Stop;
	}

	void startLoad()
	{
		dest->startLoad();
		workRemainTime = dest->workRemainTime;
		state = Load;
	}

	void endLoad()
	{
		state = Stop;
	}



	void startUnload()
	{
		dest->startUnload();
		workRemainTime = dest->workRemainTime;
		state = Unload;

	}

	void endUnload()
	{
		// after unload, start clean immediately

		startClean();

	}

	void updateState()
	{

		switch (state)
		{
		case Stop:
			break;

		case Run:
			--workRemainTime;
			if (workRemainTime == 0)
				endRun();
			break;

		case Wait:
			break;

		case Load:
			--workRemainTime;
			if (workRemainTime == 0)
				endLoad();
			break;

		case Clean:
			--workRemainTime;
			if (workRemainTime == 0)
				endClean();
			break;

		case Unload:
			--workRemainTime;
			if (workRemainTime == 0)
				endUnload();
			break;

		default:
			break;
		}



	}
};