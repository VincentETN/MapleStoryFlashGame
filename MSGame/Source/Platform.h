#pragma once

namespace game_framework {
	//�H�@���u��ܥ��x�A���F�שY�Ay1==y2

	class Platform {
	public:
		Platform();
		int getX1();	//����
		int getY1();
		int getX2();	//�k��
		int getY2();
		void setXY(int nx1, int ny1, int nx2, int ny2);
		int movingSpeed();	//tell player step
	protected:
		int x1, y1, x2, y2;
	};
}