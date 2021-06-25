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
		bool isCollision(int tx1, int ty1, int tx2, int ty2);	//�O�_�Ptarget�I��
		void GetHurt(int dmg);
		bool IsAlive();											// �O�_����
		bool IsDisappear();										// ����
		void SetXY(int nx, int ny);
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		/****�K�ޥ�****/
		void zeroHP();
	protected:
		CAnimation moveLeft, moveRight, getHurtLeft, getHurtRight, dyingLeft, dyingRight;
		int monsterID, number;
		int leftBound, rightBound;
		int x, y;
		int HP;
		int step;
		bool isHurt;				//�Q����
		bool isAlive;				// �O�_����
		bool isMovingLeft;
		bool isMovingRight;
		bool isFacingRight;			//���V�k��true ���V����false
	private: 
		bool isDisappear;
	};
}