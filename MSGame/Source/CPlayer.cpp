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
		Initialize();
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
		const int Y_POS = 400;
		superStateCount = 50;
		x = X_POS;
		y = Y_POS;
		rising = false;
		g = 3;
		jumpVel = -14;
		instantVelX = 0;
		instantVelY = 0;
		isFacingLeft = true;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isFacingRight = isJumping = isClimbing = false;
		attackKeyDown = isAttacking = false;
		isHurt = false;
		superState = false;
	}

	void CPlayer::LoadBitmap()
	{
		idleLeft.AddBitmap(IDB_C_SL, RGB(255, 0, 255));
		idleRight.AddBitmap(IDB_C_SR, RGB(255, 0, 255));
		lieLeft.AddBitmap(IDB_C_LL, RGB(255, 0, 255));
		lieRight.AddBitmap(IDB_C_LR, RGB(255, 0, 255));
		jumpLeft.AddBitmap(IDB_C_JL, RGB(255, 0, 255));
		jumpRight.AddBitmap(IDB_C_JR, RGB(255, 0, 255));
		walkLeft.AddBitmap(IDB_C_SL, RGB(255, 0, 255));
		walkLeft.AddBitmap(IDB_C_WL, RGB(255, 0, 255));
		walkLeft.AddBitmap(IDB_C_SL, RGB(255, 0, 255));
		walkLeft.AddBitmap(IDB_C_WL, RGB(255, 0, 255));
		walkLeft.AddBitmap(IDB_C_SL, RGB(255, 0, 255));
		walkLeft.AddBitmap(IDB_C_WL, RGB(255, 0, 255));
		walkLeft.AddBitmap(IDB_C_WL2, RGB(255, 0, 255));
		walkRight.AddBitmap(IDB_C_SR, RGB(255, 0, 255));
		walkRight.AddBitmap(IDB_C_WR, RGB(255, 0, 255));
		walkRight.AddBitmap(IDB_C_SR, RGB(255, 0, 255));
		walkRight.AddBitmap(IDB_C_WR, RGB(255, 0, 255));
		walkRight.AddBitmap(IDB_C_SR, RGB(255, 0, 255));
		walkRight.AddBitmap(IDB_C_WR, RGB(255, 0, 255));
		walkRight.AddBitmap(IDB_C_WR2, RGB(255, 0, 255));
		climb.AddBitmap(IDB_C_C1, RGB(255, 0, 255));
		climb.AddBitmap(IDB_C_C2, RGB(255, 0, 255));
		ladderIdle.AddBitmap(IDB_C_C1, RGB(255, 0, 255));

		attackLeft.AddBitmap(IDB_C_AL1, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL2, RGB(255, 0, 255));
		attackRight.AddBitmap(IDB_C_AR1, RGB(255, 0, 255));
		attackRight.AddBitmap(IDB_C_AR2, RGB(255, 0, 255));
	}		

	void CPlayer::OnMove()	//����
	{
		int STEP_SIZE = floors.movingSpeed();
		idleLeft.OnMove();
		idleRight.OnMove();
		lieLeft.OnMove();
		lieRight.OnMove();
		climb.OnMove();
		walkLeft.OnMove();
		walkRight.OnMove();
		attackLeft.OnMove();
		attackRight.OnMove();
		x += instantVelX;
		y += instantVelY;
		if (isInTheAir()) {  // ��y�y���٨S�I��a�O
			//y += instantVelY;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
			instantVelY += g;		// �����O�v�T�A�U�����U���t�׼W�[
			if (instantVelY > 0) {
				rising = false;
			}
		}
		else if (isClimbing) {
			instantVelX = 0;
		}
		else if(!isClimbing){
			instantVelY = 0;
			y = floors.getStandPointY(GetMidX()) - idleLeft.Height();
			if(!isMovingLeft && !isMovingRight){
				instantVelX = 0;
			}
		}

		if (isMovingLeft) {
			if (!isClimbing && !isAttacking) {
				//x -= STEP_SIZE;
				SetFacingLeft(true);
				SetFacingRight(false);
				if (!isHurt)
					instantVelX = -STEP_SIZE;
			}
		}

		if (isMovingRight) {
			if (!isClimbing && !isAttacking) {
				//x += STEP_SIZE;
				SetFacingLeft(false);
				SetFacingRight(true);
				if (!isHurt)
					instantVelX = STEP_SIZE;
			}
		}

		if (isMovingUp) {
			if (ladder.isLadder(GetMidX(), GetMidY())) {
				SetIsClimbing(true);
				x = (ladder.getX1() + ladder.getX2()) / 2 - idleLeft.Width() / 2;
				y -= 4;
				//instantVelY = -4;
			}
			else if (isClimbing && ladder.onTheTop(GetMidY())) {
				SetIsClimbing(false);
				y = ladder.getY1() - idleLeft.Height();
			}
		}

		if (isMovingDown) {
			//SetJumping(false);		//�Ȥ��੹�U��
			if (ladder.isLadder(GetMidX(), GetY2())) {
				SetIsClimbing(true);
				x = (ladder.getX1() + ladder.getX2()) / 2 - idleLeft.Width() / 2;
				y += 4;
				//instantVelY = 4;
			}
			else if (isClimbing && ladder.atTheBottom(GetY2())) {
				SetIsClimbing(false);
			}
		}

		if (isJumping) {
			if (!isClimbing) {
				instantVelY = jumpVel;
				y += instantVelY;
				//rising = true;
				SetJumping(false);
			}
			//SetIsClimbing(false);
		}

		if (!superState && isHurt) {
			superState = true;
			superStateCounter = superStateCount;
			instantVelY = -6;
			y += instantVelY;
			//rising = true;
			if (isFacingLeft) {
				instantVelX = STEP_SIZE;
			}
			else {
				instantVelX = -STEP_SIZE;
			}
		}

		if (--superStateCounter <= 0)
			superState = false;
		

		if (isAttacking) {
			instantVelX = 0;
			if (isFacingLeft) {
				if (!attackKeyDown && attackLeft.IsFinalBitmap()) {
					attackLeft.Reset();
					SetAttacking(false);
				}
			}
			else if (isFacingRight) {
				if (!attackKeyDown && attackRight.IsFinalBitmap()) {
					attackRight.Reset();
					SetAttacking(false);
				}
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
	
	void CPlayer::SetFacingRight(bool flag)
	{
		isFacingRight = flag;
	}
	
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
		if (isInTheAir()) {
			if (isFacingLeft) {
				jumpLeft.SetTopLeft(x, y);
				jumpLeft.OnShow();
			}
			else if (isFacingRight) {
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
		else if(isOnTheGround()){
			if (isAttacking) {
				if (isFacingLeft) {
					attackLeft.SetTopLeft(x, y);
					attackLeft.SetDelayCount(8);
					attackLeft.OnShow();
					/*if (!attackKeyDown && attackLeft.IsFinalBitmap()) {
						SetAttacking(false);
						attackLeft.Reset();
					}*/
				}
				else if (isFacingRight) {
					attackRight.SetTopLeft(x, y);
					attackRight.SetDelayCount(8);
					attackRight.OnShow();
					/*if (!attackKeyDown && attackRight.IsFinalBitmap()) {
						SetAttacking(false);
						attackRight.Reset();
					}*/
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
				else if (isFacingRight) {
					lieRight.SetTopLeft(x, y + 25);
					lieRight.OnShow();
				}
			}
			else if (isFacingLeft) {
				idleLeft.SetTopLeft(x, y);
				idleLeft.OnShow();
			}
			else if (isFacingRight) {
				idleRight.SetTopLeft(x, y);
				idleRight.OnShow();
			}
		}
	}

	bool CPlayer::isOnTheGround()
	{
		return floors.isFloor(GetMidX(), GetY2(), instantVelY);
	}
	
	void CPlayer::SetIsClimbing(bool flag) 
	{
		isClimbing = flag;
	}
	
	bool CPlayer::isInTheAir()
	{
		/*if (rising) {
			return true;
		}*/
		return !(isOnTheGround() || isClimbing);
	}

	bool CPlayer::Attacking() {
		return isAttacking;
	}
}