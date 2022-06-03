﻿	
// GallagDlg.h: 헤더 파일
//

#pragma once
#include <vector>
#include <list>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GameObj.h"
#include "Enemy.h"
#include "InputKey.h"

using namespace std;

// CGallagDlg 대화 상자
class CGallagDlg : public CDialogEx
{
// 생성입니다.
public:
	CGallagDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	const int BOARD_SIZE_X = 600;
	const int BOARD_SIZE_Y = 800;
	int homeTextBlink = 0;
	int gameScore = 0;
	int bestScore = 0;

	CImage gameImage;

	InputKey inputKey;
	GameObj player;

	vector<Enemy> enemys;
	list<GameObj> playerBullets;
	list<GameObj> enemyBullets;

	ObjMaker enemyMaker;

	enum GameState { Home, Play };
	GameState nowGameState;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GALLAG_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	void ControllPlayer();
	void ControllEnemy();
	void Collision();

	void DrawObject(CPaintDC& dc);
	void DrawHome(CPaintDC& dc);
	void DrawScore(CPaintDC& dc);

	void GameStart();
	void GameOver();

	BOOL PreTranslateMessage(MSG* pMsg);


	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
