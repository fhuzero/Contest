// Contest.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"


using namespace std;

int currentTime;
const int TotalTime = 28800;	// 8h
const int ShortTotalTime = 3600;	// 1h





									// get random integer in [min_value, max_value]
int getRand(int min_value, int max_value)
{
	return rand() % (max_value - min_value + 1) + min_value;
}


int chooseTask(vector<CNC>& vcnc)
{

}


int main()
{
	vector<int> RGVMoveTime(4);
	int oddCNCLoadTime;
	int RGVProcessTime_1;
	int RGVProcessTime_2_part1;
	int RGVProcessTime_2_part2;
	int OddCNCLoadTime;
	int EvenCNCLoadTime;
	int CleanTime;
	vector<CNC> vcnc(9);	// vcnc[0] will not be not used
	RGV rgv;
	int dest;
	int choosedIndex;

	srand((unsigned int)time(NULL));


	RGVMoveTime[1] = 20;
	RGVMoveTime[2] = 33;
	RGVMoveTime[3] = 46;
	RGVProcessTime_1 = 560;
	RGVProcessTime_2_part1 = 400;
	RGVProcessTime_2_part2 = 378;
	OddCNCLoadTime = 28;
	EvenCNCLoadTime = 31;
	CleanTime = 25;


	for (int i = 0; i <= 8; ++i) {
		vcnc[i].setPos(i);
	}

	// Case 1
	// 1#, 3#, 5#, 7#
	for (int i : { 1, 3, 5, 7 }) {
		vcnc[i].setTime(OddCNCLoadTime, RGVProcessTime_1);
	}
	// 2#, 4#, 6#, 8#
	for (int i : {2, 4, 6, 8}) {
		vcnc[i].setTime(EvenCNCLoadTime, RGVProcessTime_1);
	}


	for (currentTime = 0; currentTime < ShortTotalTime; ++currentTime) {

		if (rgv.state == Stop) {

			// do job
			choosedIndex = chooseTask(vcnc);
			rgv.setNextDest(vcnc[choosedIndex]);
		}

		// update state and go to next second

		rgv.updateState();

		for (CNC& cnc : vcnc)
			cnc.updateState();

	}


	system("pause");
	return 0;
}

