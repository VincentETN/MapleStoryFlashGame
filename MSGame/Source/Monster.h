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
		bool isCollision(int tx1, int ty1, int tx2, int ty2);	//�O�_�Ptarget�I��
		bool IsAlive();											// �O�_����
		bool IsDisappear();										// ����
		void SetXY(int nx, int ny);
		void LoadBitmap();
		void OnMove();
		void OnShow();
		/****�K�ޥ�****/
		void zeroHP();
	private:
		CAnimation moveLeft, moveRight, getHurtLeft, getHurtRight, dyingLeft, dyingRight;
		int monsterID, number;
		int leftBound, rightBound;
		int x, y;
		int HP;
		int step;
		bool isHurt;				// �Q����
		bool isAlive;				// �O�_����
		bool isMovingLeft;
		bool isMovingRight;
		bool isFacingRight;			// ���V�k��true ���V����false
		bool isDisappear;
	};
}