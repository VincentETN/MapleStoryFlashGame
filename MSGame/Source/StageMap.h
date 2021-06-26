#pragma once
#include "Platform.h"
#include "Ladder.h"
#include "Monster.h"

namespace game_framework {

	class StageMap {
	public:
		StageMap();
		void MapInit();
		void MonsterInit();
		void ChangeStage(int s);
		/*create function*/
		void CreatePlatform();
		void CreateLadder();
		void CreateMonsters();
		/*get function*/
		int GetStage();
		Platform* GetPlatform();
		Ladder* GetLadder();
		vector<Monster>* GetMonsters();
		/*game function*/
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

		const int titleCount = 20;
		int titleCounter;
		bool titleShow;
	};
}