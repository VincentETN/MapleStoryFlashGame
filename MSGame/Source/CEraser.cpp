#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CEraser.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// CEraser: Eraser class
	/////////////////////////////////////////////////////////////////////////////

	CEraser::CEraser()
	{
		Initialize();
	}

	int CEraser::GetX1()
	{
		return x;
	}

	int CEraser::GetY1()
	{
		return y;
	}

	int CEraser::GetX2()
	{
		return x + idle.Width();
	}

	int CEraser::GetY2()
	{
		return y + idle.Height();
	}

	void CEraser::Initialize()
	{
		const int X_POS = 505;
		const int Y_POS = 393;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
	}

	void CEraser::LoadBitmap()
	{
		idle.AddBitmap(IDB_C_SL, RGB(255, 0, 255));
		lie.AddBitmap(IDB_C_LIE, RGB(255, 0, 255));
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

	void CEraser::OnMove()	//²¾°Ê
	{
		const int STEP_SIZE = 5;
		idle.OnMove();
		lie.OnMove();
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
	}

	void CEraser::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void CEraser::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CEraser::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CEraser::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void CEraser::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void CEraser::OnShow()
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
			lie.SetTopLeft(x, y+25);
			lie.OnShow();
		}else {
			idle.SetTopLeft(x, y);
			idle.OnShow();
		}
	}
}