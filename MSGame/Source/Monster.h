#pragma once

namespace game_framework {

	class Monster {
	public:
		Monster(int id, int lb, int rb, int y);
		int GetX1();
		int GetY1();
		int GetX2();
		int GetY2();
		bool isCollision(int tx1, int ty1, int tx2, int ty2);	//�O�_�Ptarget�I��
		void GetHurt(int dmg);
		bool IsAlive();											// �O�_����
		void SetXY(int nx, int ny);
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
	protected:
		CAnimation moveLeft, moveRight;
		int monsterID;
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
	};
}