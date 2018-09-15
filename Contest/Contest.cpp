// Contest.cpp: 定义控制台应用程序的入口点。
//



#include "stdafx.h"


#include "RGV.h"

using namespace std;

const int TotalTime = 28800;	// 8h
const int ShortTotalTime = 3600;	// 1h


// get random integer in [min_value, max_value]
int getRand(int min_value, int max_value)
{
	return rand() % (max_value - min_value + 1) + min_value;
}


int main()
{

	list<CNC*> waitLoadList, processList;

	int currentTime;

	vector<int> RGVMoveTime(4);

	int CNCProcessTime_1;
	int CNCProcessTime_2_part1;
	int CNCProcessTime_2_part2;
	int OddCNCLoadTime;
	int EvenCNCLoadTime;
	int CleanTime;
	vector<CNC> vcnc(9);	// vcnc[0] will not be not used
	RGV rgv;


	srand((unsigned int)time(NULL));
	RGVMoveTime[0] = 0;

	RGVMoveTime[1] = 20;
	RGVMoveTime[2] = 33;
	RGVMoveTime[3] = 46;
	CNCProcessTime_1 = 560;
	CNCProcessTime_2_part1 = 400;
	CNCProcessTime_2_part2 = 378;
	OddCNCLoadTime = 28;
	EvenCNCLoadTime = 31;
	CleanTime = 25;



	for (int i = 1; i <= 8; ++i) {
		// Case 1
		// 1#, 3#, 5#, 7#
		if (i % 2 == 1) {
			vcnc[i].init(i, OddCNCLoadTime, CNCProcessTime_1, &waitLoadList, &processList);

		}
		// 2#, 4#, 6#, 8#

		else {
			vcnc[i].init(i, EvenCNCLoadTime, CNCProcessTime_1, &waitLoadList, &processList);
		}
	}



	rgv.init(RGVMoveTime, CleanTime, &waitLoadList, &processList);

	cout << endl;

	for (currentTime = 0; currentTime < TotalTime; ++currentTime) {

		rgv.currentTime = currentTime;
		for (CNC& cnc : vcnc)
			cnc.currentTime = currentTime;

		rgv.endWork();
		for (CNC& cnc : vcnc)
			cnc.endWork();


		// cout << '[' << currentTime << ']';

		rgv.startWork();



		// update state and go to next second

		rgv.updateRemainTime();

		for (CNC& cnc : vcnc)
			cnc.updateRemainTime();

		// cout << endl;

	}


	system("pause");
	return 0;
}

