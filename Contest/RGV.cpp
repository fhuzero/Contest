#include "stdafx.h"
#include "RGV.h"
#include "scheduling.h"
 void RGV::startWork()
{
	if (state == Stop) {
		cout << "[" << currentTime << "]" << "[RGV]";
		// do job
		dest = getDest(*waitLoadList, *processList, *waitUnloadList);
		startRun();

	}

	if (state == Waitclean) {
		cout << "[" << currentTime << "]" << "[RGV]";
		// after unload, start clean immediately

		startClean();
	}


	if (state == Wait) {
		switch (dest->state)
		{
		case Waitload:
			cout << "[" << currentTime << "]" << "[RGV]";

			startLoad();
			break;

		case Waitunload:
			cout << "[" << currentTime << "]" << "[RGV]";

			startUnload();
			break;

		case Process: case CNCLoad: case CNCUnload: default:
			break;
		}
	}
}
