#include "Platform.h"
#include "Ladder.h"

namespace game_framework {
	class Player
	{
	public:
		Player();
		void Initialize();				// ��l��
		/*************get function************************/
		int  GetX1();									// ���a���W�� x �y��
		int  GetY1();									// ���a���W�� y �y��
		int  GetX2();									// ���a�k�U�� x �y��
		int  GetY2();									// ���a�k�U�� y �y��
		int  GetMidX();									// ���a���� x �y��
		int  GetMidY();									// ���a���� y �y��
		tuple<int, int, int, int> GetAttackRange();
		/*************game function***********************/
		void LoadBitmap();
		void OnMove();
		void OnShow();
		/*************set function************************/
		void SetMovingDown(bool flag);					// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);					// �]�w�O�_���b��������
		void SetMovingRight(bool flag);					// �]�w�O�_���b���k����
		void SetMovingUp(bool flag);					// �]�w�O�_���b���W����
		void SetFacingLeft(bool flag);
		void SetJumping(bool flag);
		void SetAttackKey(bool flag);
		void SetAttacking(bool flag);
		void SetGetHurt(bool flag);
		void SetXY(int nx, int ny);						// �]�w���W���y��
		void SetIsClimbing(bool flag);
		void SetMap(Platform *plat, Ladder *lad);
		/*************is function*************************/
		bool IsInTheAir();
		bool IsOnTheGround();
		bool IsAttacking();
		bool IsInSuperState();
		bool IsAlive();
	protected:
		CAnimation idleLeft, idleRight, lieLeft, lieRight, jumpLeft, jumpRight, walkLeft, walkRight, climb, ladderIdle, attackLeft, attackRight;		// ���⪺�ʵe
		CMovingBitmap dieLeft, dieRight, hp_3, hp_2, hp_1, hp_0;
		int x, y;					// ���a���W���y��
		int hp;
		int jumpVel;				// �_����l�t��
		int instantVelX;			// x�b���ɳt��
		int instantVelY;			// y�b���ɳt��
		int g;						// �[�t��
		const int superStateCount = 50;
		int superStateCounter;
		Platform *floors;
		Ladder *ladder;
		/*************state variable***************/
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
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