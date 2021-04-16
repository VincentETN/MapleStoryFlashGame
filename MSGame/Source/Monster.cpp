#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPlayer.h"
#include "Monster.h"

namespace game_framework {
	Monster::Monster(int id, int x, int y)
	{
		monsterID = id;
		this->x = x;
		this->y = y;
		HP = 2;
	}
	int Monster::GetX1()
	{
		return x;
	}
	int Monster::GetY1()
	{
		return y;
	}
	bool Monster::HittingPlayer(CPlayer *player)
	{
		return false;
	}
	bool Monster::IsHurt()
	{
		return false;
	}
	bool Monster::IsAlive()
	{
		return false;
	}
	void Monster::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}
	void Monster::LoadBitmap()
	{
	}
	void Monster::OnMove()
	{
	}
	void Monster::OnShow()
	{
	}
}