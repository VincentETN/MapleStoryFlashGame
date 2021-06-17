#pragma once

namespace game_framework {
	class Player
	{
	public:
		Player();
		/***************遊戲進行***************/
		void initialize();				// 設定初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動
		void OnShow();					// 將圖形貼到畫面
		/***************取得屬性 get function***************/
		int getX1();					// 玩家左上角 x 座標
		int getY1();					// 玩家左上角 y 座標
		int getX2();					// 玩家右下角 x 座標
		int getY2();					// 玩家右下角 y 座標
		int getMidX();					// 玩家中心 x 座標
		int getMidY();					// 玩家中心 y 座標
		int getHP();
		tuple<int, int, int, int> getAttackRange();
		/***************取得狀態 is function***************/
		//bool isAttacking();
		/***************狀態設定 set function***************/
		void setXY(int nx, int ny);		// 設定左上角座標
		void setSpeed(int nspeed);		// 設定移動速度
		void setMovingLeft(bool flag);	// 設定是否正在往左移動
		void setMovingRight(bool flag); // 設定是否正在往右移動
		void setMovingUp(bool flag);	// 設定是否正在往上移動
		void setMovingDown(bool flag);	// 設定是否正在往下移動
		void setJumping(bool flag);
		void setAttacking(bool flag);
		void setClimbing(bool flag);
		void setOnTheGround(bool flag);
		void setInTheAir(bool flag);

		//void setAttackKey(bool flag);
		//void setGetHurt(bool flag);


		//void SetMap(Platform *plat, Ladder *lad);

	protected:
		/***************被動狀態設定 set function***************/
		void setFacingLeft(bool flag);

	private:
		/**************玩家屬性**************/
		int x, y;					// 玩家左上角座標
		int speed;					// 移動速度
		int hp;						// 生命
		int instantVX;				// x軸瞬時速度
		int instantVY;				// y軸瞬時速度
		const int g = 3;			// 重力加速度
		const int jumpInitV = -12;	// 起跳初始速度
		/**************玩家動畫**************/
		CAnimation idleLeft, idleRight;
		CAnimation lieLeft, lieRight;
		CAnimation jumpLeft, jumpRight;
		CAnimation walkLeft, walkRight;
		CAnimation climb, climbIdle;
		CAnimation attackLeft, attackRight;
		/**************玩家狀態**************/
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isMovingDown;			// 是否正在往下移動
		bool isJumping;
		bool isAttacking;
		bool isFacingLeft;
		bool isClimbing;
		bool isOnTheGround;
		bool isInTheAir;
		bool isInSuperState;
		const int superStateCount = 50;	// 無敵狀態時間
		int superStateCounter;		// 無敵狀態計時
		//bool attackKeyDown;
		//bool rising;			// true表上升、false表下降
		//bool isHurt;

		//Platform *floors;
		//Ladder *ladder;

	};
}