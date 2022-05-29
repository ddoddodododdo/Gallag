﻿
// GallagDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Gallag.h"
#include "GallagDlg.h"
#include "afxdialogex.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGallagDlg 대화 상자


//생성자
CGallagDlg::CGallagDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GALLAG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	nowGameState = GameState::Home;

	srand((unsigned int)time(NULL));
}

void CGallagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGallagDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
//	ON_WM_CTLCOLOR()
//ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CGallagDlg 메시지 처리기

BOOL CGallagDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	//gameImage.Load(L"Galaga.png");
	gameImage.LoadFromResource(AfxGetInstanceHandle(), IDB_GAME);

	//창 크기 조절
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(rect.left, rect.top, BOARD_SIZE_X, BOARD_SIZE_Y);


	SetTimer(1000, 1000 / 30, NULL);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGallagDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CGallagDlg::OnTimer(UINT_PTR nIDEvent)
{

	Invalidate();
}

BOOL CGallagDlg::PreTranslateMessage(MSG* pMsg) {
	//AfxMessageBox(TEXT("눌림"));

	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam)
		{
			case VK_LEFT:
				InputKey.isLeft = true;
				break;
			case VK_RIGHT:
				InputKey.isRight = true;
				break;
			case VK_UP:
				InputKey.isUp = true;
				break;
			case VK_DOWN:
				InputKey.isDown = true;
				break;
			default:
				break;
		}
		if (pMsg->wParam == VK_RETURN) {
			if (nowGameState == Home) {
				GameStart();
			}
			return true;
		}
	}

	if (pMsg->message == WM_KEYUP) {
		switch (pMsg->wParam)
		{
			case VK_LEFT:
				InputKey.isLeft = false;
				break;
			case VK_RIGHT:
				InputKey.isRight = false;
				break;
			case VK_UP:
				InputKey.isUp = false;
				break;
			case VK_DOWN:
				InputKey.isDown = false;
				break;
			default:
				break;
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

bool CGallagDlg::IsInGameBoard(GameObj obj) {
	bool flag1 = obj.posX > -100 && obj.posY > -100;
	bool flag2 = obj.posX < BOARD_SIZE_X + 100 && obj.posY < BOARD_SIZE_Y + 100;

	return flag1 && flag2;
}

void CGallagDlg::OnPaint()
{
	CPaintDC dc(this);

	//BackGround
	gameImage.StretchBlt(dc, 0, 0, BOARD_SIZE_X, BOARD_SIZE_Y, 0, 0, 1, 1);

	
	if (nowGameState == Home) {
		DrawHome(dc);
	}
	else if (nowGameState == Play) {
		ControllPlayer();
		ControllEnemy();
		Collision();
	
		DrawObject(dc);
		DrawScore(dc);

		gameScore++;
	}

	
}

void CGallagDlg::ControllPlayer() {
	//Player Move
	double moveX = (InputKey.isRight - InputKey.isLeft);
	double moveY = (InputKey.isDown - InputKey.isUp);

	if (abs(moveX) + abs(moveY) >= 2) {
		moveX *= 0.707;
		moveY *= 0.707;
	}

	player.posX += moveX * player.speed;
	player.posY += moveY * player.speed;

	if (player.posX < 0) player.posX = 0;
	else if (player.posX > BOARD_SIZE_X) player.posX = BOARD_SIZE_X;
	if (player.posY < 0) player.posY = 0;
	else if (player.posY > BOARD_SIZE_Y - 50) player.posY = BOARD_SIZE_Y - 50;


	//Make Player Bullet
	if (++player.bulletMaker.count > player.bulletMaker.max) {
		GameObj bullet{ player.posX, player.posY, 0, 10};
		bullet.velocityX = 0;
		bullet.velocityY = -20;
		playerBullets.push_back(bullet);
		player.bulletMaker.count = 0;
	}

	//Player Bullet Move
	for (auto iter = playerBullets.begin(); iter != playerBullets.end();) {
		iter->posY += iter->velocityX;
		iter->posY += iter->velocityY;

		if (!IsInGameBoard(*iter)) {
			iter = playerBullets.erase(iter);
		}
		else 
			iter++;
	}

}


void CGallagDlg::ControllEnemy() {
	//Make Enemy
	if (++enemyMaker.count > enemyMaker.max) {
		Enemy enemy;
		enemy.posY = rand() % (int)(BOARD_SIZE_Y * 0.5) - 50;
		enemy.posX = GetRandomX(enemy.posY);
		enemy.sizeX = 20;
		enemy.sizeY = 20;
		SetVelocityFromTarget(&enemy, BOARD_SIZE_X * 0.5, BOARD_SIZE_Y * 0.25, 5);

		enemy.hp = 3;
		enemy.bulletMaker.max = 30;
		enemys.push_back(enemy);
		enemyMaker.count = 0;
	}

	//Enemy Move & Make bullet
	for (auto iter = enemys.begin(); iter != enemys.end();) {
		//Make bullet
		if (++iter->bulletMaker.count > iter->bulletMaker.max) {
			GameObj bullet{ iter->posX, iter->posY};
			SetVelocityFromTarget(&bullet, player.posX, player.posY, 10);

			enemyBullets.push_back(bullet);
			iter->bulletMaker.count = 0;
		}

		//Move Enemy
		iter->posX += iter->velocityX;
		iter->posY += iter->velocityY;
		if (!IsInGameBoard(*iter)) {
			iter = enemys.erase(iter);
		}
		else 
			iter++;
	}

	//Move Enemy Bullet
	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end();) {
		iter->posX += iter->velocityX;
		iter->posY += iter->velocityY;

		if (!IsInGameBoard(*iter))
			iter = enemyBullets.erase(iter);
		else
			iter++;
	}
}

void CGallagDlg::SetVelocityFromTarget(GameObj *obj, int targetX, int targetY, double speed) {
	obj->velocityX = targetX - obj->posX;
	obj->velocityY = targetY - obj->posY;
	
	double sum = (abs(obj->velocityX) + abs(obj->velocityY)) / speed;
	obj->velocityX /= sum;
	obj->velocityY /= sum;
}

void CGallagDlg::Collision()
{
	//player bullet ㅡ enemy
	for (auto bIter = playerBullets.begin(); bIter != playerBullets.end();) {
		for (auto eIter = enemys.begin(); eIter != enemys.end();) {
			bool xFlag = (eIter->posX - eIter->sizeX) <= bIter->posX
						&& bIter->posX <= (eIter->posX + eIter->sizeX);
			bool yFlag = (eIter->posY - eIter->sizeY) <= bIter->posY
						&& bIter->posY <= (eIter->posY + eIter->sizeY);
			if (xFlag && yFlag) {

				eIter->hp--;
				if (eIter->hp <= 0) {
					eIter = enemys.erase(eIter);
					gameScore += 100;
				}

				bIter = playerBullets.erase(bIter);
				goto doubleBreak;
			}
			else
				eIter++;
		}
		bIter++;
		doubleBreak:;
	}


	//enemy bullet - player
	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end();) {
		bool xFlag = (player.posX - player.sizeX*0.5 <= iter->posX)
					&& (iter->posX <= player.posX + player.sizeX*0.5);
		bool yFlag = (player.posY - player.sizeY*0.5 <= iter->posY)
			&& (iter->posY <= player.posY + player.sizeY*0.5);

		if (xFlag && yFlag) {
			iter = enemyBullets.erase(iter);
			player.hp--;
			if (player.hp < 0) {
				GameOver();
			}
		}
		else
			iter++;
	}

}

void CGallagDlg::DrawObject(CPaintDC& dc) {
	int drawStartX;
	int drawStartY;

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//DrawEnemy
	for (int i = 0; i < enemys.size(); i++) {
		drawStartX = enemys[i].posX - enemys[i].sizeX;
		drawStartY = enemys[i].posY - enemys[i].sizeY;

		int sizeY = enemys[i].sizeY * 2;
		/*gameImage.StretchBlt(dc, drawStartX, drawStartY + sizeY, enemys[i].sizeX * 2, -sizeY
			, 16 + 24 * 6, 55 + 24 * 2, 16, 16);*/
		gameImage.TransparentBlt(dc, drawStartX, drawStartY, enemys[i].sizeX * 2, sizeY
			, 16 + 24 * 7, 55 + 24 * 2, 16, 16);
	}

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//DrawEnemyBullets
	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end(); iter++) {
		dc.Ellipse(iter->posX + 3, iter->posY + 3, iter->posX - 3, iter->posY - 3);

	}

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//Draw Player
	drawStartX = player.posX - player.sizeX;
	drawStartY = player.posY - player.sizeY;
	gameImage.TransparentBlt(dc, drawStartX, drawStartY, player.sizeX*2, player.sizeY*2
							, 16 + 24*6, 55, 16, 16);
	
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ	
	//Draw Player Bullet
	for (auto iter = playerBullets.begin(); iter != playerBullets.end(); iter++) {
		gameImage.StretchBlt(dc, iter->posX - 4, iter->posY + 16
			, 6, -16, 374, 51, 3, 8);
	}

	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ
	//Draw Player Hp
	for (int i = 0; i < player.hp; i++) {
		gameImage.TransparentBlt(dc, player.sizeX * i * 2, BOARD_SIZE_Y - player.sizeY * 2 - 48, player.sizeX * 2, player.sizeY * 2
			, 16 + 24 * 6, 55, 16, 16);
	}


	//맨 왼쪽 시작점(16, 55)
	//이미지 간격 24(8 + 16), 이미지 크기(16, 16)
	//gameImage.StretchBlt(dc, 32, 32, 32, 32, 16, 55, 16, 16);
	//gameImage.TransparentBlt(dc, 0, 0, BOARD_SIZE_X, BOARD_SIZE_Y, 0, 0, 100, 100, RGB(0,0,0));
}
void CGallagDlg::DrawHome(CPaintDC& dc)
{
	homeTextBlink++;
	if (homeTextBlink < 10) {
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255, 255, 255));
		dc.SetTextAlign(TA_CENTER);
		dc.TextOutW(BOARD_SIZE_X * 0.5, BOARD_SIZE_Y * 0.75, _T("Press Enter Key To Start"));
	}

	if (homeTextBlink >= 20) 
		homeTextBlink = 0;
}

void CGallagDlg::DrawScore(CPaintDC& dc)
{
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetTextAlign(TA_LEFT);
	dc.TextOutW(0, 0, _T("Score"));
	
	CString gameScoreStr;
	gameScoreStr.Format(_T("%d"), gameScore);
	dc.TextOutW(0, 15, gameScoreStr);
}

void CGallagDlg::GameStart()
{
	nowGameState = Play;
	
	player.posX = BOARD_SIZE_X * 0.5;
	player.posY = BOARD_SIZE_Y * 0.8;
	player.sizeX = 20;
	player.sizeY = 20;
	player.speed = 10;
	player.hp = 3;
	player.bulletMaker.max = 3;

	enemyMaker.max = 20;

	vector<GameObj>().swap(enemys);
	list<GameObj>().swap(playerBullets);
	list<GameObj>().swap(enemyBullets);

}
void CGallagDlg::GameOver()
{
	nowGameState = Home;

	gameScore = 0;
}


double CGallagDlg::GetRandomX(int posY)
{
	double num = rand() % (BOARD_SIZE_X - 50) + 50;
	if (posY > 0)
		num = num > BOARD_SIZE_X * 0.5 ? BOARD_SIZE_X + 50 : -50;

	return num;
}
;



HCURSOR CGallagDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


