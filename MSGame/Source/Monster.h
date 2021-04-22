#pragma once

namespace game_framework {

	class Monster {
	public:
		Monster(int id, int lb, int rb, int y);
		int GetX1();
		int GetY1();
		//bool HittingPlayer(CPlayer *player);						// 是否碰到玩家
		bool GetHurt(CPlayer *player);
		bool IsAlive();											// 是否活著
		void SetXY(int nx, int ny);
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
	protected:
		CAnimation moveLeft, moveRight;
		int monsterID;
		int leftBound, rightBound;
		int x, y;
		int HP;
		int step;
		bool isHurt;				//被攻擊
		bool isAlive;				// 是否活著
		bool isMovingLeft;
		bool isMovingRight;
		bool isFacingRight;			//面向右為true 面向左為false
	private: 
	};
}