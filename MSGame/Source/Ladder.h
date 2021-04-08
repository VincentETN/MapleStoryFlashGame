#pragma once
//#include "Platform.h"

namespace game_framework {
	class Ladder {
	public:
		Ladder();
		int getX1();	//¥ª¤W
		int getY1();
		int getX2();	//¥k¤U
		int getY2();
		void setXY(int nx1, int ny1, int nx2, int ny2);
		//int movingSpeed();	//tell player step
	protected:
		int x1, y1, x2, y2;
		//Platform *top;
	};
}