#include "Platform.h"
#include "Ladder.h"

namespace game_framework {
	class Player
	{
	public:
		Player();
		void Initialize();				// 初始化
		/*************get function************************/
		int  GetX1();									// 玩家左上角 x 座標
		int  GetY1();									// 玩家左上角 y 座標
		int  GetX2();									// 玩家右下角 x 座標
		int  GetY2();									// 玩家右下角 y 座標
		int  GetMidX();									// 玩家中心 x 座標
		int  GetMidY();									// 玩家中心 y 座標
		tuple<int, int, int, int> GetAttackRange();
		/*************game function***********************/
		void LoadBitmap();
		void OnMove();
		void OnShow();
		/*************set function************************/
		void SetMovingDown(bool flag);					// 設定是否正在往下移動
		void SetMovingLeft(bool flag);					// 設定是否正在往左移動
		void SetMovingRight(bool flag);					// 設定是否正在往右移動
		void SetMovingUp(bool flag);					// 設定是否正在往上移動
		void SetFacingLeft(bool flag);
		void SetJumping(bool flag);
		void SetAttackKey(bool flag);
		void SetAttacking(bool flag);
		void SetGetHurt(bool flag);
		void SetXY(int nx, int ny);						// 設定左上角座標
		void SetIsClimbing(bool flag);
		void SetMap(Platform *plat, Ladder *lad);
		/*************is function*************************/
		bool IsInTheAir();
		bool IsOnTheGround();
		bool IsAttacking();
		bool IsInSuperState();
		bool IsAlive();
	protected:
		CAnimation idleLeft, idleRight, lieLeft, lieRight, jumpLeft, jumpRight, walkLeft, walkRight, climb, ladderIdle, attackLeft, attackRight;		// 角色的動畫
		CMovingBitmap dieLeft, dieRight, hp_3, hp_2, hp_1, hp_0;
		int x, y;					// 玩家左上角座標
		int hp;
		int jumpVel;				// 起跳初始速度
		int instantVelX;			// x軸瞬時速度
		int instantVelY;			// y軸瞬時速度
		int g;						// 加速度
		const int superStateCount = 50;
		int superStateCounter;
		Platform *floors;
		Ladder *ladder;
		/*************state variable***************/
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
		bool isFacingLeft;
		bool isJumping;
		bool isClimbing;
		bool isOnTheGround;
		bool isInTheAir;
		bool attackKeyDown;
		bool isAttacking;
		bool isHurt;
		bool superState;
	};
}