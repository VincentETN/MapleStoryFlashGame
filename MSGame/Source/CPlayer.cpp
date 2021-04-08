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
	
	int CPlayer::GetXFeet()
	{
		return x + 27;
	}

	int CPlayer::GetYFeet()
	{
		return y + idleLeft.Height();
	}

	void CPlayer::Initialize()
	{
		const int X_POS = 504;
		const int Y_POS = 300;
		x = X_POS;
		y = Y_POS;
		//const int INITIAL_VELOCITY = 10;	// 初始上升速度
		//floor.setXY(40, 455, 600, 450);
		fl = 455;
		rising = false;
		g = 3;
		initialVel = -14;
		instantVelY = 0;
		isFacingLeft = true;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isFacingRight = isJumping = isOnTheGround = isClimbing = false;
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


	}		

	void CPlayer::OnMove()	//移動
	{
		const int STEP_SIZE = 5;
		idleLeft.OnMove();
		idleRight.OnMove();
		lieLeft.OnMove();
		lieRight.OnMove();
		walkLeft.OnMove();
		walkRight.OnMove();
		if (isInTheAir()) {  // 當y座標還沒碰到地板
			y += instantVelY;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
			instantVelY += g;		// 受重力影響，下次的下降速度增加
			if (instantVelY > 0) {
				rising = false;
			}
		}
		else {
			instantVelY = 0;
			y = floor.getY1() - idleLeft.Height();
		}
		
		if (isMovingLeft) 
			x -= STEP_SIZE;
		if (isMovingRight) 
			x += STEP_SIZE;
		//if (isMovingUp)
		//	y -= STEP_SIZE;
		if (isMovingDown)
			y += 0;
		if (isJumping) {
			instantVelY = initialVel;
			rising = true;
			y += instantVelY;
			SetJumping(false);
		}
			
		//if (isJumping) {
		//	SetJumping(false);
		//	instantVelY = initialVel;
		//	if (rising) {			// 上升狀態
		//		if (instantVelY > 0) {
		//			y -= instantVelY;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
		//			instantVelY -=g;		// 受重力影響，下次的上升速度降低
		//		}
		//		else {
		//			rising = false; // 當速度 <= 0，上升終止，下次改為下降
		//			instantVelY = 1;	// 下降的初速(velocity)為1
		//		}
		//	}
		//	else {				// 下降狀態
		//		if (isInTheAir()) {  // 當y座標還沒碰到地板
		//			y += instantVelY;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
		//			instantVelY +=g;		// 受重力影響，下次的下降速度增加
		//		}
		//		else {
		//			instantVelY = initialVel;
		//			//SetJumping(false);
		//		}
		//	}
		//}
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
				lieLeft.SetTopLeft(x, y + 25);
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
	void CPlayer::SetOnTheGround(Platform  floor)
	{

		if (GetYFeet() <= floor.getY1()) {
			isOnTheGround = true;
		}
		else {
			isOnTheGround = false;
		}
			
	}
	
	void CPlayer::SetClimbing(Ladder *ladder) 
	{

	}
	
	bool CPlayer::isInTheAir()
	{
		if (rising) {
			return(true);
		}
		return !floor.isFloor(GetXFeet(), GetYFeet());
	}
}