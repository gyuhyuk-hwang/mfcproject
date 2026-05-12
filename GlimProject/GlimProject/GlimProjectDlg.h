
// GlimProjectDlg.h: 헤더 파일
//

#pragma once
#include "PaintDlg.h"

// CGlimProjectDlg 대화 상자
class CGlimProjectDlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CPaintDlg* m_pPaintDlg;
	int m_nStaticID[3] = { IDC_STATIC_P1, IDC_STATIC_P2, IDC_STATIC_P3 };
	bool m_bStopThread = false;
	
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEditRadius();
	afx_msg void OnEnChangeEditEdge();
	afx_msg void OnBnClickedBtnRandom();
	afx_msg void OnDestroy();
	void UpdatePoint(int id, CString m_pt);
	afx_msg void OnStnClickedStaticP1();

};
