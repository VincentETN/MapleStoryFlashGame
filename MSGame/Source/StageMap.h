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
		void ChangeStage(int s);
		void CreatePlatform();
		void CreateLadder();
		void CreateMonsters();
		void MonsterInit();
		Platform* GetPlatform();
		Ladder* GetLadder();
		vector<Monster>* GetMonsters();
		void LoadBitmap();
		void LoadMonsterBitmap();
		void OnMove();
		void OnShow();

	private:
		int stage;
		CMovingBitmap background1;
		CMovingBitmap background2;
		CMovingBitmap background3;
		CMovingBitmap stageTitle1;
		CMovingBitmap stageTitle2;
		CMovingBitmap stageTitle3;
		Platform * ppointer;
		Ladder * lpointer;
		vector<Monster> * mpointer;
		Platform plat1;
		Platform plat2;
		Platform plat3;
		Ladder ladder1;
		Ladder ladder2;
		Ladder ladder3;
		vector<Monster> monsters1;
		vector<Monster> monsters2;
		vector<Monster> monsters3;

		const int titleCount = 20;	// 2¬í
		int titleCounter;
		bool titleShow;
	};
}