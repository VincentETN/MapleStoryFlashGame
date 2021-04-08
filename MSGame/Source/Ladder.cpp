#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Ladder.h"

namespace game_framework {
	Ladder::Ladder() {
		x1 = y1 = x2 = y2 = 0;
	}

	int Ladder::getX1() {
		return x1;
	}

	int Ladder::getY1() {
		return y1;
	}

	int Ladder::getX2() {
		return x2;
	}

	int Ladder::getY2() {
		return y2;
	}

	void Ladder::setXY(int nx1, int ny1, int nx2, int ny2) {
		x1 = nx1;
		y1 = ny1;
		x2 = nx2;
		y2 = ny2;
	}
}