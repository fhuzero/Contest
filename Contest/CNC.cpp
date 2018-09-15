#include "stdafx.h"
#include "CNC.h"

void CNC::endWork()
{
	if (workRemainTime == 0) {
		

		switch (state)
		{
		case Waitload:
			break;

		case CNCLoad: 
			cout << "[" << currentTime << "]" << "[CNC" << Pos << "]"; 
			endLoad(); break;

		case Process: 
			cout << "[" << currentTime << "]" << "[CNC" << Pos << "]"; 
			endProcess(); break;


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
	
}

void CNC::startProcess()
{
	cout << "[CNC" << Pos << "]start process; " << endl;
	workRemainTime = ProcessTime;
	state = Process;
	processList->push_back(this);

}

void CNC::endProcess()
{
	cout << "end process" << endl;
	state = Waitload;
	processList->remove(this);
	waitLoadList->push_back(this);
}
