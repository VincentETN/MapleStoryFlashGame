#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Player.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Player: Player class
	/////////////////////////////////////////////////////////////////////////////
	Player::Player()
	{
	}

	int Player::GetX1()
	{
		return x;
	}

	int Player::GetY1()
	{
		return y;
	}

	int Player::GetX2()
	{
		return x + idleLeft.Width();
	}

	int Player::GetY2()
	{
		return y + idleLeft.Height();
	}
	
	int Player::GetMidX()
	{
		return x + idleLeft.Width()/2;
	}

	int Player::GetMidY()
	{
		return y + idleLeft.Height()/2;
	}

	void Player::Initialize()
	{
		const int X_POS = 504;
		const int Y_POS = 380;
		x = X_POS;
		y = Y_POS;
		g = 3;
		jumpVel = -12;
		instantVelX = 0;
		instantVelY = 0;
		isFacingLeft = isOnTheGround = true;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = false;
		isJumping = isClimbing = false;
		attackKeyDown = isAttacking = false;
		isHurt = false;
		superState = false;
		hp = 3;
	}

	void Player::LoadBitmap()
	{
		idleLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		idleRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		lieLeft.AddBitmap(character_left_lie, RGB(255, 0, 255));
		lieRight.AddBitmap(character_right_lie, RGB(255, 0, 255));
		jumpLeft.AddBitmap(character_left_jump, RGB(255, 0, 255));
		jumpRight.AddBitmap(character_right_jump, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_walk1, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_walk1, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_walk1, RGB(255, 0, 255));
		walkLeft.AddBitmap(character_left_walk2, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_walk1, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_walk1, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_walk1, RGB(255, 0, 255));
		walkRight.AddBitmap(character_right_walk2, RGB(255, 0, 255));
		climb.AddBitmap(character_climb1, RGB(255, 0, 255));
		climb.AddBitmap(character_climb2, RGB(255, 0, 255));
		ladderIdle.AddBitmap(character_climb1, RGB(255, 0, 255));

		attackLeft.AddBitmap(character_left_attack1_1, RGB(255, 0, 255));
		attackLeft.AddBitmap(character_left_attack1_2, RGB(255, 0, 255));
		attackLeft.AddBitmap(character_left_attack1_2, RGB(255, 0, 255));	//判斷用，不會顯示
		attackRight.AddBitmap(character_right_attack1_1, RGB(255, 0, 255));
		attackRight.AddBitmap(character_right_attack1_2, RGB(255, 0, 255));
		attackRight.AddBitmap(character_right_attack1_2, RGB(255, 0, 255));	//判斷用，不會顯示

		dieLeft.LoadBitmap(character_left_die2, RGB(255, 0, 255));
		dieRight.LoadBitmap(character_right_die2, RGB(255, 0, 255));

		hp_3.LoadBitmap(hp3, RGB(255, 0, 255));
		hp_2.LoadBitmap(hp2, RGB(255, 0, 255));
		hp_1.LoadBitmap(hp1, RGB(255, 0, 255));
		hp_0.LoadBitmap(hp0, RGB(255, 0, 255));
	}		

	void Player::OnMove()	//移動
	{
		int STEP_SIZE = floors->movingSpeed();
		if (IsAlive()) {
			if (GetMidX() + instantVelX > 40 && GetMidX() + instantVelX < 600) {
				x += instantVelX;
			}
			y += instantVelY;

			if (isMovingLeft) {
				if (!isAttacking) {
					SetFacingLeft(true);
					if (IsInTheAir() && instantVelX >= 0) {
						instantVelX -= 1;
					}
					else if (isOnTheGround) {
						if (isMovingRight) {
							instantVelX = 0;
						}else if (!isHurt) {
							walkLeft.OnMove();
							instantVelX = -STEP_SIZE;
						}
					}
				}
			}

			if (isMovingRight) {
				if (!isAttacking) {
					SetFacingLeft(false);
					if (isInTheAir && instantVelX <= 0) {
						instantVelX += 1;
					}
					else if (isOnTheGround) {
						if (isMovingLeft) {
							instantVelX = 0;
						}else if (!isHurt) {
							walkRight.OnMove();
							instantVelX = STEP_SIZE;
						}
					}
				}
			}

			if (IsInTheAir()) {
				if (instantVelY < 20) {
					instantVelY += g;		// 受阻力影響，掉落速度不超過20左右
				}
			}
			else if (isClimbing) {
				climb.OnMove();
				instantVelX = 0;
				if (isJumping && isMovingLeft) {
					instantVelX = -STEP_SIZE;
					instantVelY = -10;
					SetIsClimbing(false);
				}else if (isJumping && isMovingRight) {
					instantVelX = STEP_SIZE;
					instantVelY = -10;
					SetIsClimbing(false);
				}
			}

			if (IsOnTheGround()) {
				instantVelY = 0;
				y = floors->getStandPointY(GetMidX()) - idleLeft.Height();
				if (!isMovingLeft && !isMovingRight) {
					instantVelX = 0;
				}
			}

			if (isMovingUp) {
				if (ladder->isLadder(GetMidX(), GetMidY())) {
					SetIsClimbing(true);
					x = (ladder->getX1() + ladder->getX2()) / 2 - idleLeft.Width() / 2;
					y -= 4;
					instantVelY = 0;
				}
				else if (isClimbing && ladder->onTheTop(GetMidY())) {
					SetIsClimbing(false);
					y = ladder->getY1() - idleLeft.Height();
				}
			}

			if (isMovingDown) {
				if (ladder->isLadder(GetMidX(), GetY2())) {
					SetIsClimbing(true);
					x = (ladder->getX1() + ladder->getX2()) / 2 - idleLeft.Width() / 2;
					y += 4;
					instantVelY = 0;
				}
				else if (isClimbing && ladder->atTheBottom(GetY2())) {
					SetIsClimbing(false);
				}
			}

			if (isJumping) {
				if (IsOnTheGround()) {
					instantVelY = jumpVel;
					y += instantVelY;
				}
			}

			if (isHurt) {
				superState = true;
				superStateCounter = superStateCount;
				if (!isClimbing) {
					instantVelY = -10;
					if (isFacingLeft) {
						instantVelX = 7;
					}
					else {
						instantVelX = -7;
					}
				}
				hp -= 1;
			}

			if (superState) {
				isHurt = false;
			}

			if (--superStateCounter <= 0) {
				superState = false;
			}

			if (isAttacking) {
				if (isFacingLeft) {
					attackLeft.OnMove();
				}
				else {
					attackRight.OnMove();
				}
				if (isOnTheGround) {
					instantVelX = 0;
				}
			}
		}
	}

	void Player::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Player::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Player::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}
	
	void Player::SetFacingLeft(bool flag)
	{
		isFacingLeft = flag;
	}
	
	void Player::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}
	
	void Player::SetJumping(bool flag)
	{
		isJumping = flag;
	}

	void Player::SetAttackKey(bool flag)
	{
		attackKeyDown = flag;
	}

	void Player::SetAttacking(bool flag)
	{
		isAttacking = flag;
	}

	void Player::SetGetHurt(bool flag)
	{
		isHurt = flag;
	}

	void Player::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Player::OnShow()
	{
		if (!IsAlive()) {
			hp_0.SetTopLeft(50, 455);
			hp_0.ShowBitmap();
			if (isFacingLeft) {
				dieLeft.SetTopLeft(x, y+18);
				dieLeft.ShowBitmap();
			}
			else {
				dieRight.SetTopLeft(x, y+18);
				dieRight.ShowBitmap();
			}
		}
		else {
			if (hp == 3) {
				hp_3.SetTopLeft(50, 455);
				hp_3.ShowBitmap();
			}
			else if (hp == 2) {
				hp_2.SetTopLeft(50, 455);
				hp_2.ShowBitmap();
			}
			else if (hp == 1) {
				hp_1.SetTopLeft(50, 455);
				hp_1.ShowBitmap();
			}
			if (isInTheAir) {
				if (isFacingLeft) {
					jumpLeft.SetTopLeft(x, y);
					jumpLeft.OnShow();
				}
				else {
					jumpRight.SetTopLeft(x, y);
					jumpRight.OnShow();
				}
			}
			else if (isClimbing) {
				if (isMovingUp || isMovingDown)
				{
					climb.SetTopLeft(x, y);
					climb.OnShow();
				}
				else {
					ladderIdle.SetTopLeft(x, y);
					ladderIdle.OnShow();
				}
			}
			else if(isOnTheGround){
				if (isAttacking) {
					if (isFacingLeft) {
						attackLeft.SetTopLeft(x-40, y+5);
						attackLeft.SetDelayCount(10);
						attackLeft.OnShow();
						if (!attackKeyDown && attackLeft.IsFinalBitmap()) {
							SetAttacking(false);
						}
						if (attackLeft.IsFinalBitmap()) {
							attackLeft.Reset();
						}
					}
					else {
						attackRight.SetTopLeft(x+10, y+5);
						attackRight.SetDelayCount(10);
						attackRight.OnShow();
						if (!attackKeyDown && attackRight.IsFinalBitmap()) {
							SetAttacking(false);
						}
						if (attackRight.IsFinalBitmap()) {
							attackRight.Reset();
						}
					}
				}
				else if (isMovingLeft) {
					walkLeft.SetTopLeft(x, y);
					walkLeft.OnShow();
				}
				else if (isMovingRight) {
					walkRight.SetTopLeft(x, y);
					walkRight.OnShow();
				}
				else if (isMovingDown) {	
					if (isFacingLeft) {
						lieLeft.SetTopLeft(x, y + 25 );
						lieLeft.OnShow();
					}
					else {
						lieRight.SetTopLeft(x, y + 25);
						lieRight.OnShow();
					}
				}
				else if (isFacingLeft) {
					idleLeft.SetTopLeft(x, y);
					idleLeft.OnShow();
				}
				else {
					idleRight.SetTopLeft(x, y);
					idleRight.OnShow();
				}
			}
		}
	}

	bool Player::IsOnTheGround()
	{
		isOnTheGround = floors->isFloor(GetMidX(), GetY2(), instantVelY);
		return isOnTheGround;
	}
	
	void Player::SetIsClimbing(bool flag) 
	{
		isClimbing = flag;
	}

	bool Player::IsInSuperState()
	{
		return superState;
	}

	bool Player::IsAlive()
	{
		return hp > 0;
	}
	
	bool Player::IsInTheAir()
	{
		isInTheAir = !(IsOnTheGround() || isClimbing);
		return isInTheAir;
	}

	bool Player::IsAttacking() {
		return isAttacking;
	}

	tuple<int, int, int, int> Player::GetAttackRange()
	{
		if (isAttacking) {
			if (isFacingLeft) {
				return make_tuple(x-30, y+30, x, y+60);
			}
			else {
				return make_tuple(GetX2(), y + 30, GetX2()+30, y + 60);
			}
		}
		else {
			return make_tuple(NULL, NULL, NULL, NULL);
		}
	}

	void Player::SetMap(Platform *plat, Ladder *lad)
	{
		floors = plat;
		ladder = lad;
	}
}