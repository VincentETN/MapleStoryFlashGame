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
		ladders.reserve(10);
		//ladders.push_back(tuple<int, int, int, int>(400, 387, 420, 450));		//f1 to f3
		//ladders.push_back(tuple<int, int, int, int>(539, 284, 559, 345));
		//ladders.push_back(tuple<int, int, int, int>(83, 177, 103, 274));		//f6 to f7
		//ladders.push_back(tuple<int, int, int, int>(432, 74, 452, 167));		//f8 to f10
	}

	int Ladder::getX1() {
		return get<0>(onThisLadder);
	}

	int Ladder::getY1() {
		return get<1>(onThisLadder);
	}

	int Ladder::getX2() {
		return get<2>(onThisLadder);
	}

	int Ladder::getY2() {
		return get<3>(onThisLadder);
	}

	void Ladder::add(tuple<int, int, int, int> ladder)
	{
		ladders.push_back(ladder);
	}

	void Ladder::setXY(int nx1, int ny1, int nx2, int ny2) {
		x1 = nx1;
		y1 = ny1;
		x2 = nx2;
		y2 = ny2;
	}

	bool Ladder::isLadder(int tx, int ty) {
		for (int i = 0; i < int(ladders.size()); i++) {
			if (tx >= get<0>(ladders[i]) && tx <= get<2>(ladders[i]) && ty >= get<1>(ladders[i]) && ty <= get<3>(ladders[i])) {
				onThisLadder = ladders[i];
				return true;
			}
		}
		//onThisLadder = make_tuple(NULL, NULL, NULL, NULL);
		return false;
	}
	bool Ladder::onTheTop(int ty)
	{
		if (ty <= getY1()) {
			return true;
		}
		else {
			return false;
		}
	}
	bool Ladder::atTheBottom(int ty)
	{
		if (ty >= getY2()) {
			return true;
		}
		else {
			return false;
		}
	}
}