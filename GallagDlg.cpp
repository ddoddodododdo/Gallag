
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
//콘솔창 띄우기
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

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

	//gameImage.Load(L"Galaga.png");
	gameImage.LoadFromResource(AfxGetInstanceHandle(), IDB_GAME);
	
	
	//창 크기 조절
	CRect rect;
	GetWindowRect(&rect);
	MoveWindow(rect.left, rect.top, BOARD_SIZE_X, BOARD_SIZE_Y);

	CFile file;
	if (file.Open(_T("score.txt"), CFile::modeRead)) {
		file.Read(&bestScore, sizeof(bestScore));
		file.Close();
	}

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

	inputKey.SetInputInfo(pMsg);

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		if (nowGameState == Home) {
			GameStart();
		}
		return true;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.


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
		ControllItem();
		Collision();
	
		DrawObject(dc);

		gameScore++;
	}
	DrawScore(dc);

	
}

void CGallagDlg::ControllPlayer() {
	//Player Move
	player.Move(inputKey);

	//Make Player Bullet
	if (player.bulletMaker.CanMake()) {
		int itemVal = player.itemTime > 0;
		if (itemVal) {
			int posX = player.posX - 12;
			for (int i = 0; i <= itemVal; i++) {
				GameObj bullet{ posX += 8 , player.posY };
				bullet.velocityY = -20;
				playerBullets.push_back(bullet);
			}
		}
		else {
			GameObj bullet{ player.posX  , player.posY };
			bullet.velocityY = -20;
			playerBullets.push_back(bullet);
		}
	}

	//Player Bullet Move
	for (auto iter = playerBullets.begin(); iter != playerBullets.end();) {
		if (iter->Move()) 
			iter = playerBullets.erase(iter);
		else
			iter++;
	}

}


void CGallagDlg::ControllEnemy() {
	//Make Enemy
	if (enemyMaker.CanMake()) {
		Enemy enemy;
		enemy.SetVelocityFromTarget(BOARD_SIZE_X * 0.5, BOARD_SIZE_Y * 0.25);
		enemys1.push_back(enemy);
	}
	if (enemy2Maker.CanMake()) {
		Enemy2 enemy;
		enemy.SetVelocityFromTarget(BOARD_SIZE_X * 0.5, BOARD_SIZE_Y * 0.25);
		enemys2.push_back(enemy);
	}

	//Ememy1
	for (auto iter = enemys1.begin(); iter != enemys1.end();) {
		//Make bullet
		if (iter->bulletMaker.CanMake()) {
			GameObj bullet{ iter->posX, iter->posY };
			bullet.speed = 10;
			bullet.SetVelocityFromTarget(player.posX, player.posY);
			enemyBullets.push_back(bullet);
		}

		//Move Enemy
		if (iter->Move())
			iter = enemys1.erase(iter);
		else
			iter++;
	}

	//Enemy2
	for (auto iter = enemys2.begin(); iter != enemys2.end();) {
		//Make bullet
		if (iter->bulletMaker.CanMake()) {
			GameObj bullet{ iter->posX, iter->posY };
			bullet.speed = 30;
			bullet.SetVelocityFromTarget(player.posX, player.posY);
			enemyBullets.push_back(bullet);
		}

		//Move Enemy
		if (iter->Move())
			iter = enemys2.erase(iter);
		else
			iter++;
	}

	//Move Enemy Bullet
	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end();) {
		if (iter->Move())
			iter = enemyBullets.erase(iter);
		else
			iter++;

	}
}


void CGallagDlg::ControllItem()
{
	if (itemMaker.CanMake()) {
		GameObj item;
		item.posX = rand() % (BOARD_SIZE_X - 50) + 50;
		item.posY = 0;
		item.velocityY = 5;
		items.push_back(item);
		
	}

	cout << items.size() << endl;
	for (auto iter = items.begin(); iter != items.end();) {
		if (iter->Move())
			iter = items.erase(iter);
		else
			iter++;
	}
}


void CGallagDlg::Collision()
{
	//player bullet ㅡ enemy
	for (auto bIter = playerBullets.begin(); bIter != playerBullets.end();) {
		for (auto eIter = enemys1.begin(); eIter != enemys1.end();) {
			if (eIter->CheckCollision(*bIter)) {
				if (eIter->hp <= 0) {
					eIter = enemys1.erase(eIter);
					gameScore += 100;
				}
				bIter = playerBullets.erase(bIter);
				goto doubleBreak1;
			}
			else
				eIter++;
		}
		bIter++;
		doubleBreak1:;
	}

	//player bullet ㅡ enemy
	for (auto bIter = playerBullets.begin(); bIter != playerBullets.end();) {
		for (auto eIter = enemys2.begin(); eIter != enemys2.end();) {
			if (eIter->CheckCollision(*bIter)) {
				if (eIter->hp <= 0) {
					eIter = enemys2.erase(eIter);
					gameScore += 100;
				}
				bIter = playerBullets.erase(bIter);
				goto doubleBreak2;
			}
			else
				eIter++;
		}
		bIter++;
		doubleBreak2:;
	}


	//enemy bullet - player
	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end();) {
		if (player.CheckCollision(*iter, 0.5)) {
			iter = enemyBullets.erase(iter);
			if (player.hp < 0) {
				GameOver();
			}
		}
		else
			iter++;
	}

	//item - player
	for (auto iter = items.begin(); iter != items.end();) {
		if (player.CheckGetItem(*iter)) {
			iter = items.erase(iter);
		}
		else
			iter++;
	}

}

void CGallagDlg::DrawObject(CPaintDC& dc) {
	//DrawEnemy
	for (auto iter = enemys1.begin(); iter != enemys1.end(); iter++) {
		iter->DrawObject(dc, &gameImage, GameObj::ENEMY1);
	}
	for (auto iter = enemys2.begin(); iter != enemys2.end(); iter++) {
		iter->DrawObject(dc, &gameImage, GameObj::ENEMY4);
	}

	//DrawEnemyBullets
	for (auto iter = enemyBullets.begin(); iter != enemyBullets.end(); iter++) {
		dc.Ellipse(iter->posX + 3, iter->posY + 3, iter->posX - 3, iter->posY - 3);
	}

	//Draw Item 295 319 307
	for (auto iter = items.begin(); iter != items.end(); iter++) {
		//dc.Rectangle(iter->posX - 10, iter->posY - 10, iter->posX + 20, iter->posY + 20);
		gameImage.TransparentBlt(dc, iter->posX - 20, iter->posY - 20
							, 14, 30, 360, 288, 7, 15, RGB(0, 0, 0));
	}

	//Draw Player
	player.DrawObject(dc, &gameImage, GameObj::DrawType::PLAYER1);
	
	//Draw Player Bullet
	for (auto iter = playerBullets.begin(); iter != playerBullets.end(); iter++) {
		gameImage.StretchBlt(dc, iter->posX - 4, iter->posY + 16
			, 6, -16, 374, 51, 3, 8);
	}

	//Draw Player Hp
	for (int i = 0; i < player.hp; i++) {
		gameImage.TransparentBlt(dc, player.sizeX * i * 2, BOARD_SIZE_Y - player.sizeY * 2 - 48, player.sizeX * 2, player.sizeY * 2
			, 16 + 24 * 6, 55, 16, 16, RGB(0, 0, 0));
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
	CString gameScoreStr;
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));

	if (nowGameState == Play) {
		dc.SetTextAlign(TA_LEFT);
		dc.TextOutW(0, 0, _T("Score"));

		gameScoreStr.Format(_T("%d"), gameScore);
		dc.TextOutW(0, 15, gameScoreStr);
	}

	dc.SetTextAlign(TA_RIGHT);
	dc.TextOutW(BOARD_SIZE_X-20, 0, _T("BestScore"));
	gameScoreStr.Format(_T("%d"), bestScore);
	dc.TextOutW(BOARD_SIZE_X-20, 15, gameScoreStr);

}

void CGallagDlg::GameStart()
{
	nowGameState = Play;
	
	player.Reset();

	enemyMaker.max = 30;
	enemy2Maker.max = 40;
	itemMaker.max = 150;

	//리스트 비우기
	list<Enemy>().swap(enemys1);
	list<Enemy2>().swap(enemys2);
	list<GameObj>().swap(items);
	list<GameObj>().swap(playerBullets);
	list<GameObj>().swap(enemyBullets);

}
void CGallagDlg::GameOver()
{
	nowGameState = Home;

	if (bestScore < gameScore) {
		bestScore = gameScore;

		CFile file;
		file.Open(_T("score.txt"), CFile::modeCreate | CFile::modeWrite, NULL);
		file.Write(&bestScore, sizeof(bestScore));

		file.Close();
	}
	gameScore = 0;
}


HCURSOR CGallagDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


