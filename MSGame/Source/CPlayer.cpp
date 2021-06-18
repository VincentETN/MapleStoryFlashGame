#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPlayer.h"
#include "Monster.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CPlayer: Player class
	/////////////////////////////////////////////////////////////////////////////

	CPlayer::CPlayer()
	{
		//Initialize();
	}

	int CPlayer::GetX1()
	{
		return x;
	}

	int CPlayer::GetY1()
	{
		return y;
	}

	int CPlayer::GetX2()
	{
		return x + idleLeft.Width();
	}

	int CPlayer::GetY2()
	{
		return y + idleLeft.Height();
	}
	
	int CPlayer::GetMidX()
	{
		return x + idleLeft.Width()/2;
	}

	int CPlayer::GetMidY()
	{
		return y + idleLeft.Height()/2;
	}

	void CPlayer::Initialize()
	{
		const int X_POS = 504;
		const int Y_POS = 380;
		x = X_POS;
		y = Y_POS;
		rising = false;
		g = 3;
		jumpVel = -12;
		instantVelX = 0;
		instantVelY = 0;
		isFacingLeft = isOnTheGround = true;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isJumping = isClimbing = false;
		attackKeyDown = isAttacking = false;
		isHurt = false;
		superState = false;
		hp = 3;
	}

	void CPlayer::LoadBitmap()
	{
		idleLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		idleRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		lieLeft.AddBitmap(character_left_lie, RGB(255, 0, 255));
		lieRight.AddBitmap(character_right_lie, RGB(255, 0, 255));
		jumpLeft.AddBitmap(character_left_jump, RGB(255, 0, 255));
		jumpRight.AddBitmap(character_right_jump, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_walk1, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_walk1, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_walk1, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_walk2, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_walk1, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_walk1, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_walk1, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_walk2, RGB(255, 0, 255));
		climb.AddBitmap(character_climb1, RGB(255, 0, 255));
		climb.AddBitmap(character_climb2, RGB(255, 0, 255));
		ladderIdle.AddBitmap(character_climb1, RGB(255, 0, 255));

		attackLeft.AddBitmap(character_left_attack1_1, RGB(255, 0, 255));
		attackLeft.AddBitmap(character_left_attack1_2, RGB(255, 0, 255));
		attackLeft.AddBitmap(character_left_attack1_2, RGB(255, 0, 255));	//判斷用，不會顯示
		attackRight.AddBitmap(character_right_attack1_1, RGB(255, 0, 255));
		attackRight.AddBitmap(character_right_attack1_2, RGB(255, 0, 255));
		attackRight.AddBitmap(character_right_attack1_2, RGB(255, 0, 255));	//判斷用，不會顯示

		dieLeft.LoadBitmap(character_left_die2, RGB(255, 0, 255));
		dieRight.LoadBitmap(character_right_die2, RGB(255, 0, 255));
	}		

	void CPlayer::OnMove()	//移動
	{
		int STEP_SIZE = floors->movingSpeed();
		if (IsAlive()) {
			if (GetMidX() + instantVelX > 40 && GetMidX() + instantVelX < 600) {
				x += instantVelX;
			}
			y += instantVelY;

			if (IsInTheAir()) {  // 當y座標還沒碰到地板
				//y += instantVelY;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				if (instantVelY < 20) {
					instantVelY += g;		// 受重力影響，下次的下降速度增加
				}
				if (instantVelY > 0) {
					rising = false;
				}
			}
			else if (isClimbing) {
				climb.OnMove();
				instantVelX = 0;
				if (isJumping && isMovingLeft || isJumping && isMovingRight) {
					instantVelY = -10;
					SetIsClimbing(false);
				}
			}

			if (IsOnTheGround()) {
				instantVelY = 0;
				y = floors->getStandPointY(GetMidX()) - idleLeft.Height();
				if (!isMovingLeft && !isMovingRight) {
					instantVelX = 0;
				}
			}

			if (isMovingLeft) {
				SetFacingLeft(true);
				if (isInTheAir && instantVelX >= 0) {
					instantVelX -= 1;
				}
				else if (!isClimbing && !isAttacking) {
					//x -= STEP_SIZE;
					//SetFacingRight(false);
					if (!isHurt)
						walkLeft.OnMove();
						instantVelX = -STEP_SIZE;
				}
			}

			if (isMovingRight) {
				SetFacingLeft(false);
				if (isInTheAir && instantVelX <= 0) {
					instantVelX += 1;
				}
				else if (!isClimbing && !isAttacking) {
					//x += STEP_SIZE;
					//SetFacingRight(true);
					if (!isHurt)
						walkRight.OnMove();
						instantVelX = STEP_SIZE;
				}
			}

			if (isMovingUp) {
				if (ladder->isLadder(GetMidX(), GetMidY())) {
					SetIsClimbing(true);
					x = (ladder->getX1() + ladder->getX2()) / 2 - idleLeft.Width() / 2;
					y -= 4;
					instantVelY = 0;
				}
				else if (isClimbing && ladder->onTheTop(GetMidY())) {
					SetIsClimbing(false);
					y = ladder->getY1() - idleLeft.Height();
				}
			}

			if (isMovingDown) {
				//SetJumping(false);		//暫不能往下跳
				if (ladder->isLadder(GetMidX(), GetY2())) {
					SetIsClimbing(true);
					x = (ladder->getX1() + ladder->getX2()) / 2 - idleLeft.Width() / 2;
					y += 4;
					instantVelY = 0;
				}
				else if (isClimbing && ladder->atTheBottom(GetY2())) {
					SetIsClimbing(false);
				}
			}

			if (isJumping) {
				if (IsOnTheGround()) {
					instantVelY = jumpVel;
					y += instantVelY;
					rising = true;
				}
			}

			if (isHurt) {
				superState = true;
				superStateCounter = superStateCount;
				instantVelY = -10;
				//y += instantVelY;
				//rising = true;
				if (isFacingLeft) {
					instantVelX = 7;
				}
				else {
					instantVelX = -7;
				}
				hp -= 1;
			}

			if (superState) {
				isHurt = false;
			}

			if (--superStateCounter <= 0) {
				superState = false;
			}

			if (isAttacking) {
				if (isFacingLeft) {
					attackLeft.OnMove();
				}
				else {
					attackRight.OnMove();
				}
				instantVelX = 0;
			}
		}
	}

	void CPlayer::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CPlayer::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CPlayer::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	
	void CPlayer::SetFacingLeft(bool flag)
	{
		isFacingLeft = flag;
	}
	
	//void CPlayer::SetFacingRight(bool flag)
	//{
	//	isFacingRight = flag;
	//}
	
	void CPlayer::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	
	void CPlayer::SetJumping(bool flag)
	{
		isJumping = flag;
	}

	void CPlayer::SetAttackKey(bool flag)
	{
		attackKeyDown = flag;
	}

	void CPlayer::SetAttacking(bool flag)
	{
		isAttacking = flag;
	}

	void CPlayer::SetGetHurt(bool flag)
	{
		isHurt = flag;
	}

	void CPlayer::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CPlayer::OnShow()
	{
		if (!IsAlive()) {
			if (isFacingLeft) {
				dieLeft.SetTopLeft(x, y+18);
				dieLeft.ShowBitmap();
			}
			else {
				dieRight.SetTopLeft(x, y+18);
				dieRight.ShowBitmap();
			}
		}
		else if (isInTheAir) {
			if (isFacingLeft) {
				jumpLeft.SetTopLeft(x, y);
				jumpLeft.OnShow();
			}
			else {
				jumpRight.SetTopLeft(x, y);
				jumpRight.OnShow();
			}
		}
		else if (isClimbing) {
			if (isMovingUp || isMovingDown)
			{
				climb.SetTopLeft(x, y);
				climb.OnShow();
			}
			else {
				ladderIdle.SetTopLeft(x, y);
				ladderIdle.OnShow();
			}
		}
		else if(isOnTheGround){
			if (isAttacking) {
				if (isFacingLeft) {
					attackLeft.SetTopLeft(x-40, y+5);
					attackLeft.SetDelayCount(10);
					attackLeft.OnShow();
					if (!attackKeyDown && attackLeft.IsFinalBitmap()) {
						SetAttacking(false);
					}
					if (attackLeft.IsFinalBitmap()) {
						attackLeft.Reset();
					}
				}
				else {
					attackRight.SetTopLeft(x+10, y+5);
					attackRight.SetDelayCount(10);
					attackRight.OnShow();
					if (!attackKeyDown && attackRight.IsFinalBitmap()) {
						SetAttacking(false);
					}
					if (attackRight.IsFinalBitmap()) {
						attackRight.Reset();
					}
				}
			}
			else if (isMovingLeft) {
				walkLeft.SetTopLeft(x, y);
				walkLeft.OnShow();
			}
			else if (isMovingRight) {
				walkRight.SetTopLeft(x, y);
				walkRight.OnShow();
			}
			else if (isMovingDown) {	
				if (isFacingLeft) {
					lieLeft.SetTopLeft(x, y + 25 );
					lieLeft.OnShow();
				}
				else {
					lieRight.SetTopLeft(x, y + 25);
					lieRight.OnShow();
				}
			}
			else if (isFacingLeft) {
				idleLeft.SetTopLeft(x, y);
				idleLeft.OnShow();
			}
			else {
				idleRight.SetTopLeft(x, y);
				idleRight.OnShow();
			}
		}
	}

	bool CPlayer::IsOnTheGround()
	{
		isOnTheGround = floors->isFloor(GetMidX(), GetY2(), instantVelY);
		return isOnTheGround;
	}
	
	void CPlayer::SetIsClimbing(bool flag) 
	{
		isClimbing = flag;
	}

	bool CPlayer::IsInSuperState()
	{
		return superState;
	}

	bool CPlayer::IsAlive()
	{
		return hp > 0;
	}
	
	bool CPlayer::IsInTheAir()
	{
		/*if (rising) {
			return true;
		}*/
		isInTheAir = !(IsOnTheGround() || isClimbing);
		return isInTheAir;
	}

	bool CPlayer::Attacking() {
		return isAttacking;
	}
	tuple<int, int, int, int> CPlayer::GetAttackRange()
	{
		if (isAttacking) {
			if (isFacingLeft) {
				return make_tuple(x-30, y+30, x, y+60);
			}
			else {
				return make_tuple(GetX2(), y + 30, GetX2()+30, y + 60);
			}
		}
		else {
			return make_tuple(NULL, NULL, NULL, NULL);
		}
	}

	void CPlayer::SetMap(Platform *plat, Ladder *lad)
	{
		floors = plat;
		ladder = lad;
	}
}