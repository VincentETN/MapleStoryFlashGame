#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "StageMap.h"

namespace game_framework {
	
	StageMap::StageMap() {
		stage = 1;
		monsters.reserve(10);
	}

	void StageMap::MapInit() {
		CreatePlatform();
		CreateLadder();
		CreateMonsters();
	}

	void StageMap::CheckStage()
	{
		bool isAllDead = false;
		for (auto m = monsters.begin(); m != monsters.end(); m++) {
			if (!m->IsDead()) {
				isAllDead = false;
				break;
			}
			else {
				isAllDead = true;
			}
		}
		if (isAllDead) {
			stage = 2;
		}
	}

	void StageMap::CreatePlatform() {
		//stage 1 map
		plat1.add(make_tuple("f", 380, 460, 600, 480));		//f1
		plat1.add(make_tuple("s", 315, 420, 380, 460));		//s1
		plat1.add(make_tuple("f", 40, 420, 315, 480));		//f2
		plat1.add(make_tuple("f", 355, 387, 430, 397));		//f3
		plat1.add(make_tuple("f", 430, 355, 600, 365));		//f4
		plat1.add(make_tuple("f", 325, 284, 600, 294));		//f5
		plat1.add(make_tuple("f", 40, 284, 285, 294));		//f6
		plat1.add(make_tuple("f", 40, 177, 142, 187));		//f7
		plat1.add(make_tuple("f", 175, 177, 465, 187));		//f8
		plat1.add(make_tuple("f", 495, 177, 565, 187));		//f9
		plat1.add(make_tuple("f", 323, 74, 600, 84));		//f10
		plat1.add(make_tuple("f", 40, 74, 283, 84));			//f11
	}

	void StageMap::CreateLadder()
	{
		ladder1.add(make_tuple(400, 387, 420, 450));		//f1 to f3
		ladder1.add(make_tuple(539, 284, 559, 345));
		ladder1.add(make_tuple(83, 177, 103, 274));		//f6 to f7
		ladder1.add(make_tuple(432, 74, 452, 167));		//f8 to f10
	}

	void StageMap::CreateMonsters()
	{
		monsters.push_back(Monster(1, 40, 315, 385));
	}

	Platform* StageMap::GetPlatform() {
		switch (stage)
		{
		case 1:
			return &plat1;
		default:
			return &plat1;
		}
	}
	Ladder * StageMap::GetLadder()
	{
		switch (stage)
		{
		case 1:
			return &ladder1;
		default:
			return &ladder1;
		}
	}
	vector<Monster>* StageMap::GetMonsters()
	{
		return &monsters;
	}
	
	void StageMap::LoadBitmap()
	{
		background1.LoadBitmap(stage1_background);
		background1.SetTopLeft(40, 0);
		background2.LoadBitmap(stage2_background);
		background2.SetTopLeft(40, 0);
	}

	void StageMap::OnShow()
	{
		switch (stage)
		{
		case 1:
			background1.SetTopLeft(40, 0);
			background1.ShowBitmap();
			break;
		case 2:
			background2.SetTopLeft(40, 0);
			background2.ShowBitmap();
			break;
		default:
			break;
		}
	}
}