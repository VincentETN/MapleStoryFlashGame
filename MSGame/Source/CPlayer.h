namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// 這個class提供可以用鍵盤或滑鼠控制的擦子
	// 看懂就可以改寫成自己的程式了
	/////////////////////////////////////////////////////////////////////////////

	class CPlayer
	{
	public:
		CPlayer();
		int  GetX1();					// 玩家左上角 x 座標
		int  GetY1();					// 玩家左上角 y 座標
		int  GetX2();					// 玩家右下角 x 座標
		int  GetY2();					// 玩家右下角 y 座標
		int  GetXFeet();	            // 玩家腳底 x 座標
		int  GetYFeet();				// 玩家腳底 y 座標
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();					// 移動擦子
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetFacingLeft(bool flag);	
		void SetFacingRight(bool flag); 
		void SetJumping(bool flag);
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
	protected:
		CAnimation idleLeft, idleRight, lieLeft, lieRight, jumpLeft, jumpRight, walkLeft, walkRight;		// 擦子的動畫
		int x, y;			// 玩家左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isFacingLeft;			
		bool isFacingRight;
		bool isJumping;
		int floor;
		bool rising;			// true表上升、false表下降
		int initialVel;	// 起跳初始速度
		int jumpingVel;	// 跳在空中時的速度
		int g = 4;	//加速度
	};
}