#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPlayer.h"
#include "Monster.h"

namespace game_framework {
	Monster::Monster(int id, int lb, int rb, int y)
	{
		monsterID = id;
		leftBound = lb;
		rightBound = rb;
		this->y = y;
		HP = 2;
		step = 1;
		isMovingLeft = isMovingRight = false;
		isFacingRight = false;
	}

	int Monster::GetX1()
	{
		return x;
	}

	int Monster::GetY1()
	{
		return y;
	}

	/*bool Monster::HittingPlayer(CPlayer *player)
	{
		return false;
	}*/

	bool Monster::GetHurt(CPlayer *player)
	{
		return false;
	}

	bool Monster::IsAlive()
	{
		return HP > 0;
	}

	void Monster::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	void Monster::LoadBitmap()
	{
		moveLeft.AddBitmap(IDB_S_WL1, RGB(255, 0, 255));
		moveLeft.AddBitmap(IDB_S_WL2, RGB(255, 0, 255));
		moveLeft.AddBitmap(IDB_S_WL3, RGB(255, 0, 255));
		moveRight.AddBitmap(IDB_S_WR1, RGB(255, 0, 255));
		moveRight.AddBitmap(IDB_S_WR2, RGB(255, 0, 255));
		moveRight.AddBitmap(IDB_S_WR3, RGB(255, 0, 255));
	}

	void Monster::OnMove()
	{
		moveLeft.OnMove();
		moveRight.OnMove();
		srand((unsigned int) time(NULL));
		int randStatus = rand() % 3;
		if (randStatus == 0 && x > leftBound) {
			isMovingLeft = true;
			isMovingRight = false;
			isFacingRight = false;
		}
		else if (randStatus == 1 && x+moveRight.Width() < rightBound) {
			isMovingLeft = false;
			isMovingRight = true;
			isFacingRight = true;
		}
		else {
			isMovingLeft = false;
			isMovingRight = false;
		}
		
		if (isMovingLeft) {
			x -= step;
		}
		else if (isMovingRight) {
			x += step;
		}
	}

	void Monster::OnShow()
	{
		if (isFacingRight) {
			moveRight.SetTopLeft(x, y);
			moveRight.SetDelayCount(5);
			moveRight.OnShow();
		}
		else {
			moveLeft.SetTopLeft(x, y);
			moveLeft.SetDelayCount(5);
			moveLeft.OnShow();
		}
	}
}