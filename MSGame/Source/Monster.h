#pragma once

namespace game_framework {

	class Monster {
	public:
		Monster(int id);
		bool HittingPlayer(CPlayer *player);						// �O�_�I�쪱�a
		bool IsHurt();
		bool IsAlive();											// �O�_����
		void SetXY(int nx, int ny);
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
	protected:
		int monsterID;
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