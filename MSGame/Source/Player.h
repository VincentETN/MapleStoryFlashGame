#pragma once

namespace game_framework {
	class Player
	{
	public:
		Player();
		/***************�C���i��***************/
		void initialize();				// �]�w��l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// ����
		void OnShow();					// �N�ϧζK��e��
		/***************���o�ݩ� get function***************/
		int getX1();					// ���a���W�� x �y��
		int getY1();					// ���a���W�� y �y��
		int getX2();					// ���a�k�U�� x �y��
		int getY2();					// ���a�k�U�� y �y��
		int getMidX();					// ���a���� x �y��
		int getMidY();					// ���a���� y �y��
		int getHP();
		tuple<int, int, int, int> getAttackRange();
		/***************���o���A is function***************/
		//bool isAttacking();
		/***************���A�]�w set function***************/
		void setXY(int nx, int ny);		// �]�w���W���y��
		void setSpeed(int nspeed);		// �]�w���ʳt��
		void setMovingLeft(bool flag);	// �]�w�O�_���b��������
		void setMovingRight(bool flag); // �]�w�O�_���b���k����
		void setMovingUp(bool flag);	// �]�w�O�_���b���W����
		void setMovingDown(bool flag);	// �]�w�O�_���b���U����
		void setJumping(bool flag);
		void setAttacking(bool flag);
		void setClimbing(bool flag);
		void setOnTheGround(bool flag);
		void setInTheAir(bool flag);

		//void setAttackKey(bool flag);
		//void setGetHurt(bool flag);


		//void SetMap(Platform *plat, Ladder *lad);

	protected:
		/***************�Q�ʪ��A�]�w set function***************/
		void setFacingLeft(bool flag);

	private:
		/**************���a�ݩ�**************/
		int x, y;					// ���a���W���y��
		int speed;					// ���ʳt��
		int hp;						// �ͩR
		int instantVX;				// x�b���ɳt��
		int instantVY;				// y�b���ɳt��
		const int g = 3;			// ���O�[�t��
		const int jumpInitV = -12;	// �_����l�t��
		/**************���a�ʵe**************/
		CAnimation idleLeft, idleRight;
		CAnimation lieLeft, lieRight;
		CAnimation jumpLeft, jumpRight;
		CAnimation walkLeft, walkRight;
		CAnimation climb, climbIdle;
		CAnimation attackLeft, attackRight;
		/**************���a���A**************/
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isMovingDown;			// �O�_���b���U����
		bool isJumping;
		bool isAttacking;
		bool isFacingLeft;
		bool isClimbing;
		bool isOnTheGround;
		bool isInTheAir;
		bool isInSuperState;
		const int superStateCount = 50;	// �L�Ī��A�ɶ�
		int superStateCounter;		// �L�Ī��A�p��
		//bool attackKeyDown;
		//bool rising;			// true��W�ɡBfalse��U��
		//bool isHurt;

		//Platform *floors;
		//Ladder *ladder;

	};
}