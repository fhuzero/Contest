#include "stdafx.h"
#include "RGV.h"
#include "scheduling.h"
inline void RGV::startWork()
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
		cout << "[" << currentTime << "]" << "[RGV]";
		switch (dest->state)
		{
		case Waitload:
			startLoad();
			break;

		case Waitunload:
			startUnload();
			break;

		case Process: case CNCLoad: case CNCUnload: default:
			break;
		}
	}
}
