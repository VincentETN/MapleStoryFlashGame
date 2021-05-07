#pragma once
#include "Platform.h"
#include "Ladder.h"
#include "Monster.h"

namespace game_framework {

	class StageMap {
	public:
		StageMap();
		void MapInit();
		void CheckStage();
		void CreatePlatform();
		void CreateLadder();
		void CreateMonsters();
		Platform* GetPlatform();
		Ladder* GetLadder();
		vector<Monster>* GetMonsters();
		void LoadBitmap();
		void OnShow();

	private:
		int stage;
		CMovingBitmap background1;
		CMovingBitmap background2;
		Platform plat1;
		Ladder ladder1;
		vector<Monster> monsters;
	};
}