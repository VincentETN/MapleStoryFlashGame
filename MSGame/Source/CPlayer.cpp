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

	void CPlayer::Initialize()
	{
		const int X_POS = 505;
		const int Y_POS = 393;
		x = X_POS;
		y = Y_POS;
		const int INITIAL_VELOCITY = 15;	// ��l�W�ɳt��
		floor = 385;
		rising = true;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		isFacingLeft = true;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isFacingRight = isJumping = false;
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

	void CPlayer::OnMove()	//����
	{
		const int STEP_SIZE = 5;
		idleLeft.OnMove();
		idleRight.OnMove();
		lieLeft.OnMove();
		lieRight.OnMove();
		walkLeft.OnMove();
		walkRight.OnMove();
		if (isMovingLeft) 
			x -= STEP_SIZE;
		if (isMovingRight) 
			x += STEP_SIZE;
		//if (isMovingUp)
		//	y -= STEP_SIZE;
		if (isMovingDown)
			y += 0;
		if (isJumping)
			if (rising) {			// �W�ɪ��A
				if (velocity > 0) {
					y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
					velocity-=g;		// �����O�v�T�A�U�����W�ɳt�׭��C
				}
				else {
					rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
					velocity = 1;	// �U������t(velocity)��1
				}
			}
			else {				// �U�����A
				if (y < floor - 1) {  // ��y�y���٨S�I��a�O
					y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
					velocity+=g;		// �����O�v�T�A�U�����U���t�׼W�[
				}
				else {
					velocity = 10;
					SetJumping(false);
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
}