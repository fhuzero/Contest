#include "stdafx.h"
#include "CNC.h"

inline void CNC::endWork()
{
	if (workRemainTime == 0) {
		cout << "[" << currentTime << "]" << "[CNC" << Pos << "]";

		switch (state)
		{
		case Waitload:case Waitunload:
			break;

		case CNCLoad: endLoad(); break;

		case Process: endProcess(); break;

		case CNCUnload: endUnload(); break;

		default:
			break;
		}
	}
}

inline void CNC::startLoad()
{
	cout << "[CNC" << Pos << "]start load; ";
	workRemainTime = LoadTime;
	state = CNCLoad;
	waitLoadList->remove(this);
}

inline void CNC::endLoad()
{
	cout << "end load" << endl;

	// after loading, start processing immediately
	startProcess();
	processList->push_back(this);
}

inline void CNC::startProcess()
{
	cout << "[CNC" << Pos << "]start process; ";
	workRemainTime = ProcessTime;
	state = Process;
	processList->remove(this);
}

inline void CNC::endProcess()
{
	cout << "end process" << endl;
	state = Waitunload;
	processList->remove(this);
	//waitLoadList.push_back(this);
}

inline void CNC::startUnload()
{
	cout << "[CNC" << Pos << "]start unload; ";
	if (state != Waitunload)
		cout << "Error!";
	workRemainTime = LoadTime;
	state = CNCUnload;

}

inline void CNC::endUnload()
{
	cout << "end unload; " << endl;
	state = Waitload;
	//waitUnloadList.push_back(this);
	waitLoadList->push_back(this);
}
