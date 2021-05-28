#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Platform.h"

namespace game_framework {
	Platform::Platform() {
		onThisFloor = make_tuple("f", 40, 480, 600, 480);;
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
		//�V�k������
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
			if (get<0>(floors[i]) == "f") {
				if (ty <= get<2>(floors[i])) {
					if (tx >= get<1>(floors[i]) && tx <= get<3>(floors[i]) && ty+vy >= get<2>(floors[i])) {
						onThisFloor = floors[i];
						return true;
					}
				}
			}
			else if (get<0>(floors[i]) == "s") {
				if (tx >= get<1>(floors[i]) && tx <= get<3>(floors[i]) && ty+vy >= -4+(get<2>(floors[i]) + (get<4>(floors[i]) - get<2>(floors[i]))*(tx - get<1>(floors[i])) / (get<3>(floors[i]) - get<1>(floors[i])))) {
					if (get<4>(floors[i]) > get<2>(floors[i]) && ty <= 4+(get<2>(floors[i]) + (get<4>(floors[i]) - get<2>(floors[i]))*(tx - get<1>(floors[i])) / (get<3>(floors[i]) - get<1>(floors[i])))) {
						onThisFloor = floors[i];
						return true;
					}
					else if (get<2>(floors[i]) > get<4>(floors[i]) && ty <= 4+(get<2>(floors[i]) + (get<4>(floors[i]) - get<2>(floors[i]))*(tx - get<1>(floors[i])) / (get<3>(floors[i]) - get<1>(floors[i])))) {
						onThisFloor = floors[i];
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