#pragma once

namespace game_framework {
	//以長方形表示平台，三角形表示斜坡
	class Platform {
	public:
		Platform();
		void add(tuple<string, int, int, int, int> plat);
		int getStandPointY(int tx);
		int movingSpeed();						//tell player step
		bool isFloor(int tx, int ty, int vy);	//vy用來預測 = velocity of y
		~Platform();
	protected:
		string getType();
		void assignXY();		// 使用x1 y1等縮短字數
	private:
		vector<tuple<string, int, int, int, int>> floors;
		tuple<string, int, int, int, int> onThisFloor;
		int x1, y1, x2, y2;		// 左上和右下，若是斜坡則是左端和右端
	};
}