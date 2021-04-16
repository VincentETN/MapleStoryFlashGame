#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CPlayer.h"
#include "Monster.h"

namespace game_framework {
	Monster::Monster(int id)
	{
		monsterID = id;
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