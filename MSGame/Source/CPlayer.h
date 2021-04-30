#include "Platform.h"
#include "Ladder.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���ѥi�H����L�ηƹ�������l
	// �����N�i�H��g���ۤv���{���F
	/////////////////////////////////////////////////////////////////////////////

	class CPlayer
	{
	public:
		CPlayer();
		int  GetX1();					// ���a���W�� x �y��
		int  GetY1();					// ���a���W�� y �y��
		int  GetX2();					// ���a�k�U�� x �y��
		int  GetY2();					// ���a�k�U�� y �y��
		int  GetMidX();					// ���a���� x �y��
		int  GetMidY();					// ���a���� y �y��
		void Initialize();				// �]�w��l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();					// �������l
		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetFacingLeft(bool flag);	
		void SetFacingRight(bool flag); 
		void SetJumping(bool flag);
		void SetAttackKey(bool flag);
		void SetAttacking(bool flag);
		void SetGetHurt(bool flag);
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetIsClimbing(bool flag);
		bool IsInTheAir();
		void IsOnTheGround();
		bool Attacking();
	protected:
		CAnimation idleLeft, idleRight, lieLeft, lieRight, jumpLeft, jumpRight, walkLeft, walkRight, climb, ladderIdle, attackLeft, attackRight;		// ���⪺�ʵe
		int x, y;			// ���a���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isFacingLeft;			
		bool isFacingRight;
		bool isJumping;
		bool isClimbing;
		bool isOnTheGround;
		bool isInTheAir;
		bool attackKeyDown;
		bool isAttacking;
		bool rising;			// true��W�ɡBfalse��U��
		bool isHurt;
		bool superState;
		int jumpVel;		// �_����l�t��
		int instantVelX;	// x�b���ɳt��
		int instantVelY;	// y�b���ɳt��
		int g;				//�[�t��
		int superStateCount;
		int superStateCounter;
		Platform floors;
		Ladder ladder;
	};
}