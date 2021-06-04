#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "StageMap.h"

namespace game_framework {
	
	StageMap::StageMap() {
		monsters1.reserve(10);
		monsters2.reserve(10);
	}

	void StageMap::MapInit() {
		stage = 1;
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

	void StageMap::ChangeStage(int s)
	{
		stage = s;
	}

	void StageMap::CreatePlatform() {
		//stage 1 map
		plat1.add(make_tuple("f", 380, 460, 600, 480));		//f1
		plat1.add(make_tuple("s", 310, 417, 380, 460));		//s1
		plat1.add(make_tuple("f", 40, 420, 315, 480));		//f2
		plat1.add(make_tuple("f", 355, 387, 430, 397));		//f3
		plat1.add(make_tuple("f", 430, 355, 600, 365));		//f4
		plat1.add(make_tuple("f", 320, 284, 600, 294));		//f5
		plat1.add(make_tuple("f", 40, 284, 290, 294));		//f6
		plat1.add(make_tuple("f", 40, 177, 145, 187));		//f7
		plat1.add(make_tuple("f", 170, 177, 465, 187));		//f8
		plat1.add(make_tuple("f", 495, 177, 565, 187));		//f9
		plat1.add(make_tuple("f", 320, 74, 600, 84));		//f10
		plat1.add(make_tuple("f", 40, 74, 285, 84));		//f11
		//stage 2 map
		plat2.add(make_tuple("f", 40, 460, 600, 480));		//f1
		plat2.add(make_tuple("s", 75, 460, 183, 388));		//s1
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
		//stage 3 map
		plat3.add(make_tuple("f", 40, 460, 600, 480));		//f1
		plat3.add(make_tuple("f", 40, 360, 150, 370));		//f2
		plat3.add(make_tuple("f", 40, 285, 600, 295));		//f3
		plat3.add(make_tuple("f", 40, 180, 600, 190));		//f4
		plat3.add(make_tuple("f", 40, 75, 600, 85));		//f5
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
		// stage 3 ladders
		ladder3.add(make_tuple(437, 300, 447, 440));	//
		ladder3.add(make_tuple(402, 300, 412, 440));	//
		ladder3.add(make_tuple(367, 300, 377, 440));	//
		ladder3.add(make_tuple(334, 300, 344, 440));	//
		ladder3.add(make_tuple(299, 300, 309, 440));	//
		ladder3.add(make_tuple(263, 300, 273, 440));	//
		ladder3.add(make_tuple(229, 300, 239, 440));	//
		ladder3.add(make_tuple(195, 300, 205, 440));	//
		ladder3.add(make_tuple(158, 300, 168, 440));	//
		ladder3.add(make_tuple(117, 285, 137, 340));	//f2 to f3
		ladder3.add(make_tuple(468, 180, 488, 263));	//f3 to f4
		ladder3.add(make_tuple(538, 75, 558, 160));		//f4 to f5
	}

	void StageMap::CreateMonsters()
	{
		monsters1.push_back(Monster(1, 1, 40, 315, 200, 383));		//f2
		//monsters1.push_back(Monster(1, 2, 320, 600, 350, 244));	//f5
		//monsters1.push_back(Monster(1, 3, 40, 290, 50, 244));		//f6
		//monsters1.push_back(Monster(1, 4, 170, 465, 400, 137));	//f8
		//monsters1.push_back(Monster(1, 5, 320, 600, 350, 34));		//f10
		//monsters1.push_back(Monster(1, 40, 285, 60, 34));		//f11

		monsters2.push_back(Monster(1, 1, 40, 600, 380, 420));		//f1
		//monsters2.push_back(Monster(1, 2, 180, 250, 210, 350));	//f2
		//monsters2.push_back(Monster(1, 3, 40, 400, 180, 245));		//f7
		//monsters2.push_back(Monster(1, 4, 40, 230, 190, 140));		//f8
		//monsters2.push_back(Monster(1, 5, 250, 600, 500, 140));		//f9

		monsters3.push_back(Monster(1, 1, 40, 600, 380, 420));		//f1
	}

	Platform* StageMap::GetPlatform() {
		switch (stage)
		{
		case 1:
			return &plat1;
		case 2:
			return &plat2;
		case 3:
			return &plat3;
		default:
			return &plat1;
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
		case 3:
			return &ladder3;
		default:
			return &ladder1;
		}
		//return lpointer;
	}
	vector<Monster>* StageMap::GetMonsters()
	{
		if (stage == 1)
			return &monsters1;
		else if (stage == 2)
			return &monsters2;
		else if (stage == 3)
			return &monsters3;
		else
			return &monsters1;
		//return mpointer;
	}
	
	void StageMap::LoadBitmap()
	{
		background1.LoadBitmap(stage1_background);
		background1.SetTopLeft(40, 0);
		background2.LoadBitmap(stage2_background);
		background2.SetTopLeft(40, 0);
		background3.LoadBitmap(stage3_background);
		background3.SetTopLeft(40, 0);
	}

	void StageMap::LoadMonsterBitmap()
	{
		for (size_t i = 0; i < monsters1.size(); i++) {
			monsters1.at(i).LoadBitmap();
		}
		for (size_t i = 0; i < monsters2.size(); i++) {
			monsters2.at(i).LoadBitmap();
		}
		for (size_t i = 0; i < monsters3.size(); i++) {
			monsters3.at(i).LoadBitmap();
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
		case 3:
			background3.ShowBitmap();
			break;
		default:
			break;
		}
	}
}