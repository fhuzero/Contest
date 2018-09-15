#include "stdafx.h"
#include "CNC.h"

void CNC::endWork()
{
	if (workRemainTime == 0) {
		

		switch (state)
		{
		case Waitload:case Waitunload:
			break;

		case CNCLoad: 
			cout << "[" << currentTime << "]" << "[CNC" << Pos << "]"; 
			endLoad(); break;

		case Process: 
			cout << "[" << currentTime << "]" << "[CNC" << Pos << "]"; 
			endProcess(); break;

		case CNCUnload: 
			cout << "[" << currentTime << "]" << "[CNC" << Pos << "]"; 
			endUnload(); break;

		default:
			break;
		}
	}
}

void CNC::startLoad()
{
	cout << "[CNC" << Pos << "]start load; " << endl;


	workRemainTime = LoadTime;
	state = CNCLoad;
	waitLoadList->remove(this);
}

void CNC::endLoad()
{
	cout << "end load" << endl;
	// after loading, start processing immediately
	cout << "[" << currentTime << "]";
	startProcess();
	processList->push_back(this);


}

void CNC::startProcess()
{
	cout << "[CNC" << Pos << "]start process; " << endl;
	workRemainTime = ProcessTime;
	state = Process;
	processList->remove(this);
}

void CNC::endProcess()
{
	cout << "end process" << endl;
	state = Waitunload;
	processList->remove(this);
	//waitLoadList.push_back(this);
}

void CNC::startUnload()
{
	cout << "[CNC" << Pos << "]start unload; " << endl;
	if (state != Waitunload)
		cout << "Error!";
	workRemainTime = LoadTime;
	state = CNCUnload;

}

void CNC::endUnload()
{
	cout << "end unload; " << endl;
	state = Waitload;
	//waitUnloadList.push_back(this);
	waitLoadList->push_back(this);
}

