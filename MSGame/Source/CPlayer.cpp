#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPlayer.h"

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
		x = X_POS;
		y = Y_POS;
		//const int INITIAL_VELOCITY = 10;	// 初始上升速度
		//floor.setXY(40, 455, 600, 450);
		//fl = 455;
		rising = false;
		g = 3;
		jumpVel = -14;
		instantVelY = 0;
		isFacingLeft = true;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isFacingRight = isJumping = isClimbing = false;
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
		attackLeft.AddBitmap(IDB_C_AL1, RGB(255, 0, 255));	
		attackLeft.AddBitmap(IDB_C_AL2, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL2, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL3, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL3, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL4, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL4, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL5, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL5, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL6, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL6, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL7, RGB(255, 0, 255));
		attackLeft.AddBitmap(IDB_C_AL7, RGB(255, 0, 255));

	}		

	void CPlayer::OnMove()	//移動
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
		if (isInTheAir()) {  // 當y座標還沒碰到地板
			y += instantVelY;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
			instantVelY += g;		// 受重力影響，下次的下降速度增加
			if (instantVelY > 0) {
				rising = false;
			}
		}
		else if(!isClimbing){
			instantVelY = 0;
			y = floors.getStandPointY(GetMidX()) - idleLeft.Height();
		}
		
		if (isMovingLeft) {
			if (!isClimbing) {
				x -= STEP_SIZE;
				SetFacingLeft(true);
				SetFacingRight(false);
			}
		}
		if (isMovingRight) {
			if (!isClimbing) {
				x += STEP_SIZE;
				SetFacingLeft(false);
				SetFacingRight(true);
			}
		}
		if (isMovingUp) {
			if (ladder.isLadder(GetMidX(), GetMidY())) {
				SetIsClimbing(true);
				x = (ladder.getX1() + ladder.getX2()) / 2 - idleLeft.Width() / 2;
				y -= 5;
			}
			else if (isClimbing && ladder.onTheTop(GetMidY())) {
				SetIsClimbing(false);
				y = ladder.getY1() - idleLeft.Height();
			}
		}
		if (isMovingDown) {
			SetJumping(false);		//暫不能往下跳
			if (ladder.isLadder(GetMidX(), GetY2())) {
				SetIsClimbing(true);
				x = (ladder.getX1() + ladder.getX2()) / 2 - idleLeft.Width() / 2;
				y += 5;
			}
			else if (isClimbing && ladder.atTheBottom(GetY2())) {
				SetIsClimbing(false);
			}
		}
		if (isJumping) {
			instantVelY = jumpVel;
			rising = true;
			y += instantVelY;
			SetJumping(false);
			SetIsClimbing(false);
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
		else {
			if (isMovingLeft) {
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
		if (rising) {
			return true;
		}
		return !(isOnTheGround() || isClimbing);
	}
}