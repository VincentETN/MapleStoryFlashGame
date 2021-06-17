#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Player.h"

namespace game_framework {

	Player::Player()
	{
	}

	void Player::initialize()
	{
		x = 504;
		y = 380;
		hp = 3;
		instantVX = 0;
		instantVY = 0;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isJumping = isAttacking = false;
		isClimbing = isInTheAir = false;
		//isHurt = false;
		isInSuperState = false;
		isFacingLeft = isOnTheGround = true;
	}

	void Player::LoadBitmap()
	{
		idleLeft.AddBitmap(character_left_stand, RGB(255, 0, 255));
		idleRight.AddBitmap(character_right_stand, RGB(255, 0, 255));
		lieLeft.AddBitmap(character_left_lie, RGB(255, 0, 255));
		lieRight.AddBitmap(character_right_lie, RGB(255, 0, 255));
		jumpLeft.AddBitmap(character_left_jump, RGB(255, 0, 255));
		jumpRight.AddBitmap(character_right_jump, RGB(255, 0, 255));
		climbIdle.AddBitmap(character_climb1, RGB(255, 0, 255));

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

		attackLeft.AddBitmap(character_left_attack1_1, RGB(255, 0, 255));
		attackLeft.AddBitmap(character_left_attack1_2, RGB(255, 0, 255));
		attackLeft.AddBitmap(character_left_attack1_2, RGB(255, 0, 255));	//判斷用，不會顯示

		attackRight.AddBitmap(character_right_attack1_1, RGB(255, 0, 255));
		attackRight.AddBitmap(character_right_attack1_2, RGB(255, 0, 255));
		attackRight.AddBitmap(character_right_attack1_2, RGB(255, 0, 255));	//判斷用，不會顯示
	}

	void Player::OnMove()
	{
		if (getMidX() + instantVX > 40 && getMidX() + instantVX < 600) {
			x += instantVX;
		}
		y += instantVY;
		if (isMovingLeft) {
			setFacingLeft(true);
			if (isInTheAir && instantVX >= 0) {
				instantVX -= 1;
			}
			else {
				instantVX = -speed;
			}
		}

		if (isMovingRight) {
			setFacingLeft(false);
			if (isInTheAir && instantVX <= 0) {
				instantVX += 1;
			}
			else {
				instantVX = speed;
			}
		}

		if (isClimbing) {
			instantVX = 0;
			if (isJumping && isMovingLeft || isJumping && isMovingRight) {
				instantVX = speed;
				instantVY = -10;
				//SetIsClimbing(false);
			}
			if (isMovingUp) {

			}
		}

		if (isJumping) {
			if (isOnTheGround) {
				instantVY = jumpInitV;
			}
			else if (isClimbing) {
				if (isMovingLeft) {

				}
			}
		}


	}

	void Player::OnShow()
	{
	}

	int Player::getX1()
	{
		return x;
	}

	int Player::getY1()
	{
		return y;
	}

	int Player::getX2()
	{
		return x + idleLeft.Width();
	}

	int Player::getY2()
	{
		return y + idleLeft.Height();
	}

	int Player::getMidX()
	{
		return x + idleLeft.Width() / 2;
	}

	int Player::getMidY()
	{
		return y + idleLeft.Height() / 2;
	}

	void Player::setXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void Player::setSpeed(int nspeed)
	{
		speed = nspeed;
	}

	void Player::setMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Player::setMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Player::setMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Player::setMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void Player::setJumping(bool flag)
	{
		isJumping = flag;
	}

	void Player::setAttacking(bool flag)
	{
		isAttacking = flag;
	}

	void Player::setClimbing(bool flag)
	{
		isClimbing = flag;
	}

	void Player::setOnTheGround(bool flag)
	{
		isOnTheGround = flag;
	}

	void Player::setInTheAir(bool flag)
	{
		isInTheAir = flag;
	}

	void Player::setFacingLeft(bool flag)
	{
		isFacingLeft = flag;
	}
}