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
		void Initialize();				// �]�w���l����l��
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
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		bool isInTheAir();
		bool isOnTheGround();
		void SetIsClimbing(bool flag);

	protected:
		CAnimation idleLeft, idleRight, lieLeft, lieRight, jumpLeft, jumpRight, walkLeft, walkRight, climb;		// ���l���ʵe
		int x, y;			// ���a���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isFacingLeft;			
		bool isFacingRight;
		bool isJumping;
		bool isClimbing;
		int fl;
		bool rising;			// true��W�ɡBfalse��U��
		int initialVel;	// �_����l�t��
		int instantVelY;	// ���b�Ť��ɪ��t��
		int g;	//�[�t��
		Platform floors;
		Ladder ladder;
	};
}