#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Platform.h"

namespace game_framework {
	Platform::Platform() {
		x1 = y1 = x2 = y2 = 0;
		floors.push_back(tuple<int, int, int, int>(40, 460, 600, 480));		//f1
		floors.push_back(tuple<int, int, int, int>(40, 420, 315, 480));		//f2
		floors.push_back(tuple<int, int, int, int>(355, 387, 430, 397));	//f3
		floors.push_back(tuple<int, int, int, int>(430, 355, 600, 365));	//f4
		floors.push_back(tuple<int, int, int, int>(325, 284, 600, 294));	//f5
		floors.push_back(tuple<int, int, int, int>(40, 284, 285, 294));		//f6
		floors.push_back(tuple<int, int, int, int>(40, 177, 142, 187));		//f7
		floors.push_back(tuple<int, int, int, int>(175, 177, 465, 187));	//f8
		floors.push_back(tuple<int, int, int, int>(495, 177, 565, 187));	//f9
		floors.push_back(tuple<int, int, int, int>(323, 74, 600, 84));		//f10
		floors.push_back(tuple<int, int, int, int>(40, 74, 283, 84));		//f11

		//onThisFloor = tuple<int, int, int, int>(40, 480, 600, 480);
	}

	int Platform::getX1() {
		return x1;
	}

	int Platform::getY1() {
		return get<1>(onThisFloor);
	}

	int Platform::getX2() {
		return x2;
	}

	int Platform::getY2() {
		return y2;
	}

	void Platform::setXY(int nx1, int ny1, int nx2, int ny2) {
		x1 = nx1;
		y1 = ny1;
		x2 = nx2;
		y2 = ny2;
	}

	int Platform::movingSpeed() {
		//向右走為正
		if (y1 == y2) {
			return 5, 0;
		}
		else {
			double s = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
			double cos = (x2 - x1) / s;
			double sin = (y2 - y1) / s;
			int Vx = int(round(5 * cos));
			int Vy = int(round(5 * sin));
			return Vx, Vy;
		}
	}
	bool Platform::isFloor(int tx, int ty, int vy)
	{
		for (int i = 0; i < int(floors.size()); i++) {
			if (tx >= get<0>(floors[i]) && tx <= get<2>(floors[i]) && ty >= get<1>(floors[i])-vy && ty <= get<3>(floors[i])) {
				onThisFloor = floors[i];
				return true;
			}
		}
		onThisFloor = tuple<int, int, int, int>(40, 480, 600, 480);
		return false;
	}
}