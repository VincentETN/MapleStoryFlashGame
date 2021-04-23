#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Monster.h"
//#include "CPlayer.h"

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
		isHurt = false;
	}

	int Monster::GetX1()
	{
		return x;
	}

	int Monster::GetY1()
	{
		return y;
	}

	int Monster::GetX2()
	{
		return x + moveRight.Width();
	}

	int Monster::GetY2()
	{
		return y + moveRight.Height();
	}

	bool Monster::isCollision(int tx1, int ty1, int tx2, int ty2)
	{
		if (GetX1() <= tx2 && GetY1() <= ty2 && GetX2() >= tx1 && GetY2() >= ty1)
			return true;
		else
			return false;
	}

	void Monster::GetHurt(int dmg)
	{
		HP -= dmg;
		isHurt = true;
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
		getHurtLeft.AddBitmap(IDB_S_HL, RGB(255, 0, 255));
		getHurtRight.AddBitmap(IDB_S_HR, RGB(255, 0, 255));
		dyingLeft.AddBitmap(IDB_S_DL1, RGB(255, 0, 255));
		dyingLeft.AddBitmap(IDB_S_DL2, RGB(255, 0, 255));
		dyingLeft.AddBitmap(IDB_S_DL3, RGB(255, 0, 255));
		dyingRight.AddBitmap(IDB_S_DR1, RGB(255, 0, 255));
		dyingRight.AddBitmap(IDB_S_DR2, RGB(255, 0, 255));
		dyingRight.AddBitmap(IDB_S_DR3, RGB(255, 0, 255));
	}

	void Monster::OnMove()
	{
		moveLeft.OnMove();
		moveRight.OnMove();
		dyingLeft.OnMove();
		dyingRight.OnMove();
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
		if (!isHurt) {
			if (isMovingLeft) {
				x -= step;
			}
			else if (isMovingRight) {
				x += step;
			}
		}
	}

	void Monster::OnShow()
	{
		if (IsAlive()) {
			if (isFacingRight) {
				if (isHurt) {
					getHurtRight.SetTopLeft(x, y);
					getHurtRight.SetDelayCount(5);
					getHurtRight.OnShow();
					isHurt = false;
				}
				else {
					moveRight.SetTopLeft(x, y);
					moveRight.SetDelayCount(5);
					moveRight.OnShow();
				}

			}
			else {
				if (isHurt) {
					getHurtLeft.SetTopLeft(x, y);
					getHurtLeft.SetDelayCount(5);
					getHurtLeft.OnShow();
					isHurt = false;
				}
				else {
					moveLeft.SetTopLeft(x, y);
					moveLeft.SetDelayCount(5);
					moveLeft.OnShow();
				}
			}
		}
		else {
			if (isFacingRight) {
				dyingRight.SetTopLeft(x, y);
				dyingRight.OnShow();
			}
			else {
				dyingLeft.SetTopLeft(x, y);
				dyingLeft.OnShow();
			}
		}
	}
}