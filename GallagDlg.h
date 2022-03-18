	
// GallagDlg.h: 헤더 파일
//

#pragma once


// CGallagDlg 대화 상자
class CGallagDlg : public CDialogEx
{
// 생성입니다.
public:
	CGallagDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	class GameObj {
		public:
			double posX;
			double posY;
			double sizeX;
			double sizeY;
	};

	class InputKeyClass {
		public:
			bool isUp = false;
			bool isDown = false;
			bool isLeft = false;
			bool isRight = false;
	};

	const double PLAYER_SPEED = 5.0;

	InputKeyClass InputKey;
	GameObj player;

	
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
};
