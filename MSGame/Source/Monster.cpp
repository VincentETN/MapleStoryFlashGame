#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Monster.h"
//#include "CPlayer.h"

namespace game_framework {
	Monster::Monster(int id, int num, int lb, int rb, int x, int y)
	{
		monsterID = id;
		number = num;
		leftBound = lb;
		rightBound = rb;
		this->x = x;
		this->y = y;
		HP = 30;
		step = 1;
		isMovingLeft = isMovingRight = false;
		isFacingRight = false;
		isHurt = false;
		isAlive = true;
		isDead = false;
	}

	void Monster::initialize()
	{
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
		if (!IsAlive())
			return false;
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

	bool Monster::IsDead()
	{
		return isDead;
	}

	void Monster::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	void Monster::LoadBitmap()
	{
		if(monsterID == 1){
			moveLeft.AddBitmap(snail_left_walk1, RGB(255, 0, 255));
			moveLeft.AddBitmap(snail_left_walk2, RGB(255, 0, 255));
			moveLeft.AddBitmap(snail_left_walk3, RGB(255, 0, 255));
			moveRight.AddBitmap(snail_right_walk1, RGB(255, 0, 255));
			moveRight.AddBitmap(snail_right_walk2, RGB(255, 0, 255));
			moveRight.AddBitmap(snail_right_walk3, RGB(255, 0, 255));
			getHurtLeft.AddBitmap(snail_left_hurt, RGB(255, 0, 255));
			getHurtRight.AddBitmap(snail_right_hurt, RGB(255, 0, 255));
			dyingLeft.AddBitmap(snail_left_die1, RGB(255, 0, 255));
			dyingLeft.AddBitmap(snail_left_die2, RGB(255, 0, 255));
			dyingLeft.AddBitmap(snail_left_die3, RGB(255, 0, 255));
			dyingLeft.AddBitmap(snail_left_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(snail_right_die1, RGB(255, 0, 255));
			dyingRight.AddBitmap(snail_right_die2, RGB(255, 0, 255));
			dyingRight.AddBitmap(snail_right_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(snail_right_die3, RGB(255, 0, 255));
		}
		else if(monsterID == 2){
			moveLeft.AddBitmap(snake_left_walk1, RGB(255, 0, 255));
			moveLeft.AddBitmap(snake_left_walk2, RGB(255, 0, 255));
			moveLeft.AddBitmap(snake_left_walk3, RGB(255, 0, 255));
			moveRight.AddBitmap(snake_right_walk1, RGB(255, 0, 255));
			moveRight.AddBitmap(snake_right_walk2, RGB(255, 0, 255));
			moveRight.AddBitmap(snake_right_walk3, RGB(255, 0, 255));
			getHurtLeft.AddBitmap(snake_left_hurt, RGB(255, 0, 255));
			getHurtRight.AddBitmap(snake_right_hurt, RGB(255, 0, 255));
			dyingLeft.AddBitmap(snake_left_die1, RGB(255, 0, 255));
			dyingLeft.AddBitmap(snake_left_die2, RGB(255, 0, 255));
			dyingLeft.AddBitmap(snake_left_die3, RGB(255, 0, 255));
			dyingLeft.AddBitmap(snake_left_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(snake_right_die1, RGB(255, 0, 255));
			dyingRight.AddBitmap(snake_right_die2, RGB(255, 0, 255));
			dyingRight.AddBitmap(snake_right_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(snake_right_die3, RGB(255, 0, 255));
		}
		else if (monsterID == 3) {
			moveLeft.AddBitmap(mushroom_left_walk1, RGB(255, 0, 255));
			moveLeft.AddBitmap(mushroom_left_walk2, RGB(255, 0, 255));
			moveLeft.AddBitmap(mushroom_left_walk3, RGB(255, 0, 255));
			moveRight.AddBitmap(mushroom_right_walk1, RGB(255, 0, 255));
			moveRight.AddBitmap(mushroom_right_walk2, RGB(255, 0, 255));
			moveRight.AddBitmap(mushroom_right_walk3, RGB(255, 0, 255));
			getHurtLeft.AddBitmap(mushroom_left_hurt, RGB(255, 0, 255));
			getHurtRight.AddBitmap(mushroom_right_hurt, RGB(255, 0, 255));
			dyingLeft.AddBitmap(mushroom_left_die1, RGB(255, 0, 255));
			dyingLeft.AddBitmap(mushroom_left_die2, RGB(255, 0, 255));
			dyingLeft.AddBitmap(mushroom_left_die3, RGB(255, 0, 255));
			dyingLeft.AddBitmap(mushroom_left_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(mushroom_right_die1, RGB(255, 0, 255));
			dyingRight.AddBitmap(mushroom_right_die2, RGB(255, 0, 255));
			dyingRight.AddBitmap(mushroom_right_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(mushroom_right_die3, RGB(255, 0, 255));
		}
		else if (monsterID == 4) {
			moveLeft.AddBitmap(green_left_walk1, RGB(255, 0, 255));
			moveLeft.AddBitmap(green_left_walk2, RGB(255, 0, 255));
			moveLeft.AddBitmap(green_left_walk3, RGB(255, 0, 255));
			moveLeft.AddBitmap(green_left_walk4, RGB(255, 0, 255));
			moveLeft.AddBitmap(green_left_walk5, RGB(255, 0, 255));
			moveLeft.AddBitmap(green_left_walk6, RGB(255, 0, 255));
			moveLeft.AddBitmap(green_left_walk7, RGB(255, 0, 255));
			moveRight.AddBitmap(green_right_walk1, RGB(255, 0, 255));
			moveRight.AddBitmap(green_right_walk2, RGB(255, 0, 255));
			moveRight.AddBitmap(green_right_walk3, RGB(255, 0, 255));
			moveRight.AddBitmap(green_right_walk4, RGB(255, 0, 255));
			moveRight.AddBitmap(green_right_walk5, RGB(255, 0, 255));
			moveRight.AddBitmap(green_right_walk6, RGB(255, 0, 255));
			moveRight.AddBitmap(green_right_walk7, RGB(255, 0, 255));
			getHurtLeft.AddBitmap(green_left_hurt, RGB(255, 0, 255));
			getHurtRight.AddBitmap(green_right_hurt, RGB(255, 0, 255));
			dyingLeft.AddBitmap(green_left_die1, RGB(255, 0, 255));
			dyingLeft.AddBitmap(green_left_die2, RGB(255, 0, 255));
			dyingLeft.AddBitmap(green_left_die3, RGB(255, 0, 255));
			dyingLeft.AddBitmap(green_left_die4, RGB(255, 0, 255));
			dyingLeft.AddBitmap(green_left_die4, RGB(255, 0, 255));
			dyingRight.AddBitmap(green_right_die1, RGB(255, 0, 255));
			dyingRight.AddBitmap(green_right_die2, RGB(255, 0, 255));
			dyingRight.AddBitmap(green_right_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(green_right_die4, RGB(255, 0, 255));
			dyingRight.AddBitmap(green_right_die4, RGB(255, 0, 255));
		}
		else if (monsterID == 5) {
			moveLeft.AddBitmap(crab_left_walk1, RGB(255, 0, 255));
			moveLeft.AddBitmap(crab_left_walk2, RGB(255, 0, 255));
			moveLeft.AddBitmap(crab_left_walk3, RGB(255, 0, 255));
			moveLeft.AddBitmap(crab_left_walk4, RGB(255, 0, 255));
			moveRight.AddBitmap(crab_right_walk1, RGB(255, 0, 255));
			moveRight.AddBitmap(crab_right_walk2, RGB(255, 0, 255));
			moveRight.AddBitmap(crab_right_walk3, RGB(255, 0, 255));
			moveRight.AddBitmap(crab_right_walk4, RGB(255, 0, 255));
			getHurtLeft.AddBitmap(crab_left_hurt, RGB(255, 0, 255));
			getHurtRight.AddBitmap(crab_right_hurt, RGB(255, 0, 255));
			dyingLeft.AddBitmap(crab_left_die1, RGB(255, 0, 255));
			dyingLeft.AddBitmap(crab_left_die2, RGB(255, 0, 255));
			dyingLeft.AddBitmap(crab_left_die3, RGB(255, 0, 255));
			dyingLeft.AddBitmap(crab_left_die4, RGB(255, 0, 255));
			dyingLeft.AddBitmap(crab_left_die4, RGB(255, 0, 255));
			dyingRight.AddBitmap(crab_right_die1, RGB(255, 0, 255));
			dyingRight.AddBitmap(crab_right_die2, RGB(255, 0, 255));
			dyingRight.AddBitmap(crab_right_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(crab_right_die4, RGB(255, 0, 255));
			dyingRight.AddBitmap(crab_right_die4, RGB(255, 0, 255));
		}
		else if (monsterID == 6) {
			moveLeft.AddBitmap(star_left_walk1, RGB(255, 0, 255));
			moveLeft.AddBitmap(star_left_walk2, RGB(255, 0, 255));
			moveLeft.AddBitmap(star_left_walk3, RGB(255, 0, 255));
			moveLeft.AddBitmap(star_left_walk4, RGB(255, 0, 255));
			moveLeft.AddBitmap(star_left_walk5, RGB(255, 0, 255));
			moveLeft.AddBitmap(star_left_walk6, RGB(255, 0, 255));
			moveRight.AddBitmap(star_right_walk1, RGB(255, 0, 255));
			moveRight.AddBitmap(star_right_walk2, RGB(255, 0, 255));
			moveRight.AddBitmap(star_right_walk3, RGB(255, 0, 255));
			moveRight.AddBitmap(star_right_walk4, RGB(255, 0, 255));
			moveRight.AddBitmap(star_right_walk5, RGB(255, 0, 255));
			moveRight.AddBitmap(star_right_walk6, RGB(255, 0, 255));
			getHurtLeft.AddBitmap(star_left_hurt, RGB(255, 0, 255));
			getHurtRight.AddBitmap(star_right_hurt, RGB(255, 0, 255));
			dyingLeft.AddBitmap(star_left_die1, RGB(255, 0, 255));
			dyingLeft.AddBitmap(star_left_die2, RGB(255, 0, 255));
			dyingLeft.AddBitmap(star_left_die3, RGB(255, 0, 255));
			dyingLeft.AddBitmap(star_left_die4, RGB(255, 0, 255));
			dyingLeft.AddBitmap(star_left_die5, RGB(255, 0, 255));
			dyingLeft.AddBitmap(star_left_die5, RGB(255, 0, 255));
			dyingRight.AddBitmap(star_right_die1, RGB(255, 0, 255));
			dyingRight.AddBitmap(star_right_die2, RGB(255, 0, 255));
			dyingRight.AddBitmap(star_right_die3, RGB(255, 0, 255));
			dyingRight.AddBitmap(star_right_die4, RGB(255, 0, 255));
			dyingRight.AddBitmap(star_right_die5, RGB(255, 0, 255));
			dyingRight.AddBitmap(star_right_die5, RGB(255, 0, 255));
		}
	}

	void Monster::OnMove()
	{
		moveLeft.OnMove();
		moveRight.OnMove();
		dyingLeft.OnMove();
		dyingRight.OnMove();
		srand(number*(unsigned int)time(NULL));
		int randStatus = rand() % 3;
		if (IsAlive()) {
			if (randStatus == 0 && x > leftBound) {
				isMovingLeft = true;
				isMovingRight = false;
				isFacingRight = false;
			}
			else if (randStatus == 1 && x + moveRight.Width() < rightBound) {
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
			else {
				isMovingLeft = false;
				isMovingRight = false;
				isHurt = false;
			}
		}
	}

	void Monster::OnShow()
	{
		if (!isDead) {
			if (IsAlive()) {
				if (isFacingRight) {
					if (isHurt) {
						getHurtRight.SetTopLeft(x, y);
						getHurtRight.SetDelayCount(5);
						getHurtRight.OnShow();
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
					dyingRight.SetDelayCount(10);
					dyingRight.OnShow();
					if (dyingRight.IsFinalBitmap()) {
						isDead = true;
					}
				}
				else {
					dyingLeft.SetTopLeft(x, y);
					dyingLeft.SetDelayCount(10);
					dyingLeft.OnShow();
					if (dyingLeft.IsFinalBitmap()) {
						isDead = true;
					}
				}
			}
		}
	}
}