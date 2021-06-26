#pragma once

namespace game_framework {

	class Monster {
	public:
		Monster(int id, int num, int lb, int rb, int x, int y);
		void initialize();
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		void GetHurt(int dmg);
		bool isCollision(int tx1, int ty1, int tx2, int ty2);	//是否與target碰撞
		bool IsAlive();											// 是否活著
		bool IsDisappear();										// 消失
		void SetXY(int nx, int ny);
		void LoadBitmap();
		void OnMove();
		void OnShow();
		/****密技用****/
		void zeroHP();
	private:
		CAnimation moveLeft, moveRight, getHurtLeft, getHurtRight, dyingLeft, dyingRight;
		int monsterID, number;
		int leftBound, rightBound;
		int x, y;
		int HP;
		int step;
		bool isHurt;				// 被攻擊
		bool isAlive;				// 是否活著
		bool isMovingLeft;
		bool isMovingRight;
		bool isFacingRight;			// 面向右為true 面向左為false
		bool isDisappear;
	};
}