#pragma once

namespace game_framework {

	class Monster {

	public:
		Monster(int id);
		bool HitPlayer(CPlayer *player);						// 是否碰到擦子
		bool IsAlive();											// 是否活著
		void LoadBitmap();										// 載入圖形
		void OnMove();											// 移動
		void OnShow();											// 將圖形貼到畫面
		void SetXY(int nx, int ny);
	protected:
		int x, y;
		int monsterID;
		bool is_alive;				// 是否活著
	private:
		bool HitRectangle(int tx1, int ty1, int tx2, int ty2);	// 是否碰到參數範圍的矩形 
	};
}