#pragma once
#include "Platform.h"
#include "Ladder.h"
#include "Monster.h"

namespace game_framework {

	class StageMap {
	public:
		StageMap();
		void MapInit();
		int GetStage();
		void ChangeStage();
		void CreatePlatform();
		void CreateLadder();
		void CreateMonsters();
		Platform* GetPlatform();
		Ladder* GetLadder();
		vector<Monster>* GetMonsters();
		void LoadBitmap();
		void LoadMonsterBitmap();
		void OnShow();

	private:
		int stage;
		CMovingBitmap background1;
		CMovingBitmap background2;
		Platform * ppointer;
		Ladder * lpointer;
		vector<Monster> * mpointer;
		Platform plat1;
		Platform plat2;
		Ladder ladder1;
		Ladder ladder2;
		vector<Monster> monsters1;
		vector<Monster> monsters2;
	};
}