#pragma once
#include "Platform.h"
#include "Ladder.h"

namespace game_framework {

	class StageMap {
	public:
		StageMap();
		void MapInit();
		void CreatePlatform();
		void CreateLadder();
		Platform* GetPlatform();
		Ladder* GetLadder();

	private:
		int stage;
		Platform plat1;
		Ladder ladder1;
	};
}