#pragma once

namespace game_framework {
	//�H����Ϊ�ܥ��x�M�שY

	class Platform {
	public:
		Platform();
		//int getX1();	//����
		//int getY1();
		//int getX2();	//�k��
		//int getY2();
		int getStandPointY(int tx);
		int movingSpeed();	//tell player step
		bool isFloor(int tx, int ty, int vy);	//vy�Ψӹw�� = velocity of y
	protected:
		string getType();
		void assignXY();
	private:
		vector<tuple<string, int, int, int, int>> floors;
		tuple<string, int, int, int, int> onThisFloor;
		int x1, y1, x2, y2;		//���W�M�k�U�A�Y�O�שY�h�O���ݩM�k��
	};
}