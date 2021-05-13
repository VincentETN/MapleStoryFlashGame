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
		monsters1.reserve(10);
		monsters2.reserve(10);
	}

	void StageMap::MapInit() {
		CreatePlatform();
		CreateLadder();
		CreateMonsters();
		ppointer = &plat1;
		lpointer = &ladder1;
		mpointer = &monsters1;
	}

	int StageMap::GetStage()
	{
		return stage;
	}

	void StageMap::ChangeStage()
	{
		stage += 1;
	}

	void StageMap::CreatePlatform() {
		//stage 1 map
		plat1.add(make_tuple("f", 380, 460, 600, 480));		//f1
		plat1.add(make_tuple("s", 313, 418, 382, 462));		//s1
		plat1.add(make_tuple("f", 40, 420, 315, 480));		//f2
		plat1.add(make_tuple("f", 355, 387, 430, 397));		//f3
		plat1.add(make_tuple("f", 430, 355, 600, 365));		//f4
		plat1.add(make_tuple("f", 325, 284, 600, 294));		//f5
		plat1.add(make_tuple("f", 40, 284, 285, 294));		//f6
		plat1.add(make_tuple("f", 40, 177, 142, 187));		//f7
		plat1.add(make_tuple("f", 175, 177, 465, 187));		//f8
		plat1.add(make_tuple("f", 495, 177, 565, 187));		//f9
		plat1.add(make_tuple("f", 323, 74, 600, 84));		//f10
		plat1.add(make_tuple("f", 40, 74, 283, 84));		//f11
		//stage 2 map
		plat2.add(make_tuple("f", 40, 459, 600, 480));		//f1
		plat2.add(make_tuple("s", 73, 461, 182, 388));		//s1
		plat2.add(make_tuple("f", 178, 390, 250, 400));		//f2
		plat2.add(make_tuple("f", 280, 390, 365, 400));		//f3
		plat2.add(make_tuple("f", 385, 390, 470, 400));		//f4
		plat2.add(make_tuple("f", 490, 390, 600, 400));		//f5
		plat2.add(make_tuple("f", 420, 285, 600, 295));		//f6
		plat2.add(make_tuple("f", 40, 285, 400, 295));		//f7
		plat2.add(make_tuple("f", 40, 180, 230, 190));		//f8
		plat2.add(make_tuple("f", 250, 180, 600, 190));		//f9
		plat2.add(make_tuple("f", 490, 75, 600, 85));		//f10
		plat2.add(make_tuple("f", 385, 75, 465, 85));		//f11
		plat2.add(make_tuple("f", 280, 75, 365, 85));		//f12
		plat2.add(make_tuple("f", 175, 75, 260, 85));		//f13
		plat2.add(make_tuple("f", 40, 75, 150, 85));		//f14
	}

	void StageMap::CreateLadder()
	{
		// stage 1 ladders
		ladder1.add(make_tuple(400, 387, 420, 450));		//f1 to f3
		ladder1.add(make_tuple(539, 284, 559, 345));
		ladder1.add(make_tuple(83, 177, 103, 274));		//f6 to f7
		ladder1.add(make_tuple(432, 74, 452, 167));		//f8 to f10
		// stage 2 ladders
		ladder2.add(make_tuple(537, 285, 557, 370));	//f5 to f6
		ladder2.add(make_tuple(82, 180, 102, 265));		//f7 to f8
		ladder2.add(make_tuple(572, 75, 592, 165));		//f9 to f10
	}

	void StageMap::CreateMonsters()
	{
		monsters1.push_back(Monster(1, 40, 315, 200, 385));

		monsters2.push_back(Monster(1, 40, 600, 200, 425));
	}

	Platform* StageMap::GetPlatform() {
		switch (stage)
		{
		case 1:
			return &plat1;
		case 2:
			return &plat2;
		default:
			return &plat2;
		}
		//return ppointer;
	}
	Ladder * StageMap::GetLadder()
	{
		switch (stage)
		{
		case 1:
			return &ladder1;
		case 2:
			return &ladder2;
		default:
			return &ladder2;
		}
		//return lpointer;
	}
	vector<Monster>* StageMap::GetMonsters()
	{
		if (stage == 1)
			return &monsters1;
		else if (stage == 2)
			return &monsters2;
		else
			return &monsters2;
		//return mpointer;
	}
	
	void StageMap::LoadBitmap()
	{
		background1.LoadBitmap(stage1_background);
		background1.SetTopLeft(40, 0);
		background2.LoadBitmap(stage2_background);
		background2.SetTopLeft(40, 0);
	}

	void StageMap::LoadMonsterBitmap()
	{
		for (size_t i = 0; i < monsters1.size(); i++) {
			monsters1.at(i).LoadBitmap();
		}
		for (size_t i = 0; i < monsters2.size(); i++) {
			monsters2.at(i).LoadBitmap();
		}
	}

	void StageMap::OnShow()
	{
		switch (stage)
		{
		case 1:
			background1.ShowBitmap();
			break;
		case 2:
			background2.ShowBitmap();
			break;
		default:
			break;
		}
	}
}