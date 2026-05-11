#pragma once
#include "afxdialogex.h"
#include "GlimProject.h"

// PaintDlg 대화 상자

class CPaintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPaintDlg)

public:
	CPaintDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPaintDlg();

	CImage m_image;
	CWnd* m_pParent;
	int m_count=0;
	int m_nStaticID[3] = { IDC_STATIC_P1, IDC_STATIC_P2, IDC_STATIC_P3 };
	CPoint m_PointArray[3];
	unsigned char* fm;
	int m_radius;
	bool isDragging = false;
	int m_index;
	CString m_pt;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PaintDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void InitImage();
	void DrawCircle();
	void DrawPoint(int x, int y);
	CPoint CalcCircle(CPoint pA, CPoint pB, CPoint pC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	LRESULT OnRandomUpdate(WPARAM wParam, LPARAM lParam);
};
