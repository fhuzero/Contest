#pragma once

#include <list>
#include <iostream>

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

	// CNC(int pos, int loadtime, int processtime) : Pos(pos), LoadTime(loadtime), ProcessTime(processtime) {}

	void init(int pos, int loadtime, int processtime) {
		Pos = pos;
		LoadTime = loadtime;
		ProcessTime = processtime;
	}

	void setPos(int pos)
	{
		Pos = pos;
	}

	void setTime(int loadtime, int processtime) {
		LoadTime = loadtime;
		ProcessTime = processtime;
	}

	void updateState()
	{
		if (workRemainTime < 0)
			cout << "Error!";

		switch (state)
		{
		case Waitload:
			break;

		case CNCLoad:
			--workRemainTime;
			if (workRemainTime == 0) {
				endLoad();
			}
			break;

		case Process:
			--workRemainTime;
			if (workRemainTime == 0) {

			}

			break;

		case Waitunload:
			break;

		case CNCUnload:
			--workRemainTime;
			if (workRemainTime == 0) {
				state = Waitload;
				//waitUnloadList.push_back(this);
			}
			break;

		default:
			break;
		}
	}


	int startLoad(int startTime)
	{
		if (state != Waitload)
			cout << "Error!";
		workRemainTime = LoadTime;
		state = CNCLoad;
	}

	int endLoad()
	{
		// after loading, start processing immediately
		startProcess();
		//processList.push_back(this);
	}

	int startProcess()
	{
		if (state != CNCLoad)
			cout << "Error!";
		workRemainTime = ProcessTime;
	}

	int endProcess()
	{
		state = Waitunload;
		//waitLoadList.push_back(this);
	}

	int startUnload()
	{
		if (state != Waitunload)
			cout << "Error!";
		workRemainTime = LoadTime;
	}

	int endUnload()
	{

	}
};

// the state of RGV: stop, run, load, unload, clean
// when loading, unloading and cleaning, RGV cannot move
// wait is similar to stop, but the task has been distributed
enum RGVStateT { Stop, Wait, Run, Load, Unload, Clean };

class RGV
{
public:
	int pos; // position
	RGVStateT state;
	int workRemainTime;
	int nextDestPos;
	CNCStateT nextDestState;

	void setPos(int _pos)
	{
		pos = _pos;
	}

	void updateState()
	{

	}

	void setNextDest(const CNC& cnc)
	{
		nextDestPos = cnc.Pos;
		switch (cnc.state)
		{
		case Waitload:
			break;

		case CNCLoad:
			--workRemainTime;
			if (workRemainTime == 0)
				// after loading, start processing immediately
				startProcess();
			break;

		case Process:
			--workRemainTime;
			if (workRemainTime == 0)
				state = Waitunload;
			break;

		case Waitunload:
			break;

		case CNCUnload:
			--workRemainTime;
			if (workRemainTime == 0)
				state = Waitload;
			break;

		default:
			break;
		default:
			break;
		}

	}
};