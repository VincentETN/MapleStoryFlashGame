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
		floor.push_back(tuple<int, int, int, int>(40, 460, 600, 480));
		floor.push_back(tuple<int, int, int, int>(40, 420, 315, 480));
		floor.push_back(tuple<int, int, int, int>(355, 387, 430, 395));
		onThisFloor = tuple<int, int, int, int>(40, 480, 600, 480);
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
	bool Platform::isFloor(int tx, int ty)
	{
		for (int i = 0; i < int(floor.size()); i++) {
			if (tx >= get<0>(floor[i]) && tx <= get<2>(floor[i]) && ty >= get<1>(floor[i])-5 && ty <= get<3>(floor[i])) {
				onThisFloor = floor[i];
				return true;
			}
		}
		onThisFloor = tuple<int, int, int, int>(40, 480, 600, 480);
		return false;
	}
}