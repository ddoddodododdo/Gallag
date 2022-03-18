﻿
// GallagDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Gallag.h"
#include "GallagDlg.h"
#include "afxdialogex.h"

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



CGallagDlg::CGallagDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GALLAG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	player.posX = 100;
	player.posY = 100;
	player.sizeX = 50;
	player.sizeY = 50;


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

void CGallagDlg::OnPaint()
{
	CPaintDC dc(this);

	ControllPlayer();

	DrawObject(dc);
	SetTimer(1000, 1000 / 60, NULL);
}

void CGallagDlg::ControllPlayer() {
	double moveX = (InputKey.isRight - InputKey.isLeft) * PLAYER_SPEED;
	double moveY = (InputKey.isDown - InputKey.isUp) * PLAYER_SPEED;

	player.posX += moveX;
	player.posY += moveY;

}

void CGallagDlg::DrawObject(CPaintDC& dc) {

	//Draw Player
	dc.Rectangle(player.posX - player.sizeX * 0.5, player.posY - player.sizeY * 0.5
		, player.posX + player.sizeX * 0.5, player.posY + player.sizeY * 0.5);
};



HCURSOR CGallagDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

