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
		floors.reserve(20);
		//floors.push_back(make_tuple("f", 380, 460, 600, 480));		//f1
		//floors.push_back(make_tuple("s", 315, 420, 380, 460));
		//floors.push_back(make_tuple("f", 40, 420, 315, 480));		//f2
		//floors.push_back(make_tuple("f", 355, 387, 430, 397));		//f3
		//floors.push_back(make_tuple("f", 430, 355, 600, 365));		//f4
		//floors.push_back(make_tuple("f", 325, 284, 600, 294));		//f5
		//floors.push_back(make_tuple("f", 40, 284, 285, 294));		//f6
		//floors.push_back(make_tuple("f", 40, 177, 142, 187));		//f7
		//floors.push_back(make_tuple("f", 175, 177, 465, 187));		//f8
		//floors.push_back(make_tuple("f", 495, 177, 565, 187));		//f9
		//floors.push_back(make_tuple("f", 323, 74, 600, 84));		//f10
		//floors.push_back(make_tuple("f", 40, 74, 283, 84));			//f11
	}

	void Platform::add(tuple<string, int, int, int, int> plat)
	{
		floors.push_back(plat);
	}

	int Platform::getStandPointY(int tx) {
		assignXY();
		if (getType() == "s") {
			return y1 + (y2 - y1)*(tx - x1) / (x2 - x1);
		}
		else {
			return y1;
		}
	}

	int Platform::movingSpeed() {
		//向右走為正
		assignXY();
		if (getType() == "s") {
			return 4;
		}
		else {
			return 5;
		}
	}

	bool Platform::isFloor(int tx, int ty, int vy)
	{
		for (int i = 0; i < int(floors.size()); i++) {
			if (getType() == "f") {
				if (tx >= get<1>(floors[i]) && tx <= get<3>(floors[i]) && ty >= get<2>(floors[i]) - vy && ty <= get<4>(floors[i])) {
					onThisFloor = floors[i];
					return true;
				}
			}
			else if (getType() == "s") {
				onThisFloor = floors[i];
				assignXY();
				if (tx >= x1 && tx <= x2 && ty >= (y1 + (y2 - y1)*(tx - x1) / (x2 - x1)) - vy) {
					if (y2 > y1 && ty <= y2) {
						return true;
					}
					else if (y1 > y2 && ty <= y1) {
						return true;
					}
				}
			}
		}
		onThisFloor = make_tuple("f", 40, 480, 600, 480);
		return false;
	}

	Platform::~Platform()
	{
	}

	string Platform::getType() {
		return get<0>(onThisFloor);
	}

	void Platform::assignXY() {
		x1 = get<1>(onThisFloor);
		y1 = get<2>(onThisFloor);
		x2 = get<3>(onThisFloor);
		y2 = get<4>(onThisFloor);
	}

}