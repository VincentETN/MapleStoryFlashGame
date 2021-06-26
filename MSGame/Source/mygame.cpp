/*
 * mygame.cpp: ���ɮ��x�C��������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress. 
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"


namespace game_framework {
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(0);	// �@�}�l��loading�i�׬�0%
	//
	// �}�l���J���
	//
	menu_bg.LoadBitmap(menu_background);
	menu_bg1.LoadBitmap(menu_background1);
	menu_bg2.LoadBitmap(menu_background2);
	about1.LoadBitmap(about_window1, 0x00FF00FF);
	about2.LoadBitmap(about_window2, 0x00FF00FF);
	start.LoadBitmap(start_button, 0x00FF00FF);
	start2.LoadBitmap(start_button2, 0x00FF00FF);
	
	ShowInitProgress(60);
	//
	// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 27;
	if (nChar == KEY_ESC)								// Demo �����C������k
		PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �����C��
}

void CGameStateInit::OnLButtonUp(UINT nFlags, CPoint point)
{
	isLButtonUp = true;
	if (isOnStartButton)
		GotoGameState(GAME_STATE_RUN);
	if (!isAboutOpen) {
		if(isOnAboutButton)
			isAboutOpen = true;
	}
	else {
		if (isOnBackButton)
			isAboutOpen = false;
	}

}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	isLButtonUp = false;
}

void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!isAboutOpen) {
		if (point.x > 420 && point.x < 500 && point.y > 415 && point.y < 435)
			isOnStartButton = true;
		else
			isOnStartButton = false;

		if (point.x > 105 && point.x < 160 && point.y > 420 && point.y < 440)
			isOnAboutButton = true;
		else
			isOnAboutButton = false;
	}

	if (isAboutOpen){
		if (point.x > 275 && point.x < 335 && point.y > 255 && point.y < 280)
			isOnBackButton = true;
		else
			isOnBackButton = false;
	}

}

void CGameStateInit::OnShow()
{
	menu_bg1.SetTopLeft(40, 0);
	menu_bg2.SetTopLeft(40, 0);
	about1.SetTopLeft(155, 125);
	about2.SetTopLeft(155, 125);
	start.SetTopLeft(424, 419);
	start2.SetTopLeft(424, 419);



	if (isAboutOpen) {
		menu_bg1.ShowBitmap();
		about1.ShowBitmap();
		if (isOnBackButton) {
			menu_bg1.ShowBitmap();
			about2.ShowBitmap();
		}			
	}
	else if(isOnAboutButton) {
			menu_bg2.ShowBitmap();
	}
	else
			menu_bg1.ShowBitmap();

	if (isOnStartButton)
		start.ShowBitmap();
	else
		start2.ShowBitmap();
}								

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;
	if (counter < 0)
		GotoGameState(GAME_STATE_INIT);
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 3; // 5 seconds
}

void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	success_bg.LoadBitmap(success_background);
	fail_bg.LoadBitmap(gameover_background);
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	if (SUCCESS) {
		success_bg.SetTopLeft(40, 0);
		success_bg.ShowBitmap();
	}
	else {
		fail_bg.SetTopLeft(40, 0);
		fail_bg.ShowBitmap();
	}
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
: CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
	const int BACKGROUND_X = 40;
	const int ANIMATION_SPEED = 15;
	map.ChangeStage(1);
	monsters = map.GetMonsters();
	player.SetMap(map.GetPlatform(), map.GetLadder());
	player.Initialize();
	map.MonsterInit();
	monsterIsAllDead = false;
	delayCounter = 30;
	trick1 = 0;
	trick2 = false;
}

void CGameStateRun::OnMove()							// ���ʹC������
{
	// �p�G�Ʊ�ק�cursor���˦��A�h�N�U���{����commment�����Y�i
	//
	// SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
	//
	CheckStage();
	if (map.GetStage() == 3 && monsterIsAllDead) {
		delayCounter--;
		if (delayCounter < 0) {
			SUCCESS = true;
			GotoGameState(GAME_STATE_OVER);
		}
	}
	else if (!player.IsAlive()) {
		delayCounter--;
		if (delayCounter < 0) {
			SUCCESS = false;
			GotoGameState(GAME_STATE_OVER);
		}
	}
	map.OnMove();
	player.OnMove();
	for (vector<Monster>::iterator m = monsters->begin(); m != monsters->end(); m++) {
		m->OnMove();
	}
	PlayerMonsterInteraction(&player, monsters);

	if (trick1 == 2) {
		for (size_t i = 0; i < monsters->size(); i++) {
			monsters->at(i).zeroHP();
		}
		CAudio::Instance()->Play(AUDIO_DEAD);
		trick1 = 0;
	}
}

void CGameStateRun::OnInit()  								// �C������Ȥιϧγ]�w
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	player.LoadBitmap();
	map.MapInit();
	map.LoadBitmap();
	map.LoadMonsterBitmap();
	player.SetMap(map.GetPlatform(), map.GetLadder());
	monsters = map.GetMonsters();
	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	//
	// �~����J��L���
	//									
	CAudio::Instance()->Load(AUDIO_HIT,  "sounds\\hit.wav");
	CAudio::Instance()->Load(AUDIO_DEAD, "sounds\\dead.wav");
	CAudio::Instance()->Load(AUDIO_HURT, "sounds\\hurt.wav");
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_SPACE = 0x20;
	const char KEY_Z	 = 0x5A;
	const char KEY_SHIFT = 0x10;
	const char KEY_S	 = 0x53;
	
	if (nChar == KEY_LEFT) {
		player.SetMovingLeft(true);
	}
	if (nChar == KEY_RIGHT) {
		player.SetMovingRight(true);
	}
	if (nChar == KEY_UP)
		player.SetMovingUp(true);
	if (nChar == KEY_DOWN)
		player.SetMovingDown(true);
	if (nChar == KEY_SPACE) {
		if(!player.IsInTheAir())
			player.SetJumping(true);
	}
	if (nChar == KEY_Z) {
		player.SetAttackKey(true);
		player.SetAttacking(true);
	}

	if (nChar == KEY_SHIFT) {
		trick1++;
	}

	if (trick1 == 1) {
		if (nChar == KEY_Z) {
			trick1++;
		}
	}

	if (nChar == KEY_S) {
		trick2 = !trick2;
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT  = 0x25; // keyboard���b�Y
	const char KEY_UP    = 0x26; // keyboard�W�b�Y
	const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
	const char KEY_DOWN  = 0x28; // keyboard�U�b�Y
	const char KEY_SPACE = 0x20;
	const char KEY_Z	 = 0x5A;
	const char KEY_SHIFT = 0x10;

	if (nChar == KEY_LEFT) {
		player.SetMovingLeft(false);
	}
	if (nChar == KEY_RIGHT) {
		player.SetMovingRight(false);
	}
	if (nChar == KEY_UP)
		player.SetMovingUp(false);
	if (nChar == KEY_DOWN)
		player.SetMovingDown(false);
	if (nChar == KEY_SPACE)
		player.SetJumping(false);
	if (nChar == KEY_Z) {
		player.SetAttackKey(false);
		if (trick1 > 0)
			trick1--;
	}
	if (nChar == KEY_SHIFT) {
		if(trick1 > 0)
			trick1--;
	}
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	// �S�ơC�p�G�ݭn�B�z�ƹ����ʪ��ܡA�gcode�b�o��
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
{
	
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
{
	
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	map.OnShow();
	player.OnShow();
	for (size_t i = 0; i < monsters->size(); i++) {
		monsters->at(i).OnShow();
	}
}

void CGameStateRun::CheckStage()
{
	for (auto m = monsters->begin(); m != monsters->end(); m++) {
		if (!m->IsDisappear()) {
			monsterIsAllDead = false;
			break;
		}
		else {
			monsterIsAllDead = true;
		}
	}
	if (monsterIsAllDead && map.GetStage() < 3) {
		map.ChangeStage(map.GetStage()+1);
		monsters = map.GetMonsters();
		player.SetMap(map.GetPlatform(), map.GetLadder());
		player.SetXY(504, 380);
		monsterIsAllDead = false;
	}
}

void CGameStateRun::PlayerMonsterInteraction(Player * player, vector<Monster>* monsters)
{
	tuple<int, int, int, int> playerAR = player->GetAttackRange();
	for (auto m = monsters->begin(); m != monsters->end(); m++) {
		if (!player->IsInSuperState() && !trick2) {
			if (m->isCollision(player->GetX1(), player->GetY1(), player->GetX2(), player->GetY2())) {
				player->SetGetHurt(true);
				CAudio::Instance()->Play(AUDIO_HURT);
			}
		}
		if (player->IsAttacking()) {
			if (m->isCollision(get<0>(playerAR), get<1>(playerAR), get<2>(playerAR), get<3>(playerAR))) {
				m->GetHurt(1);
				CAudio::Instance()->Play(AUDIO_HIT);
				if (!m->IsAlive() && !m->IsDisappear()) {
					CAudio::Instance()->Play(AUDIO_DEAD);
				}
			}
		}
	}
}
}