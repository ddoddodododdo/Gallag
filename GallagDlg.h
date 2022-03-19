	
// GallagDlg.h: 헤더 파일
//

#pragma once
#include <vector>

using namespace std;

// CGallagDlg 대화 상자
class CGallagDlg : public CDialogEx
{
// 생성입니다.
public:
	CGallagDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	const int BOARD_SIZE_X = 600;
	const int BOARD_SIZE_Y = 800;
	int temp = 0;

	class GameObj {
		public:

		public:
			double posX;
			double posY;
			double sizeX;
			double sizeY;
			double velocityX;
			double velocityY;
			double speed;
	};

	class InputKeyClass {
		public:
			bool isUp = false;
			bool isDown = false;
			bool isLeft = false;
			bool isRight = false;
	};


	InputKeyClass InputKey;
	GameObj player;

	vector<GameObj> playerBullets;
	int bulletDelay = 0;

	
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

	void DrawObject(CPaintDC& dc);

	BOOL PreTranslateMessage(MSG* pMsg);


	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
};
