#pragma once

namespace game_framework {

	class Monster {

	public:
		Monster(int id);
		bool HitPlayer(CPlayer *player);						// �O�_�I�����l
		bool IsAlive();											// �O�_����
		void LoadBitmap();										// ���J�ϧ�
		void OnMove();											// ����
		void OnShow();											// �N�ϧζK��e��
		void SetXY(int nx, int ny);
	protected:
		int x, y;
		int monsterID;
		bool is_alive;				// �O�_����
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// �O�_�I��Ѽƽd�򪺯x�� 
	};
}