
// GlimProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimProject.h"
#include "GlimProjectDlg.h"
#include "afxdialogex.h"
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
#define DEFAULT 0
#define DEFAULT_STR L"(0, 0)"
#define WM_RANDOM_UPDATE (WM_USER+1)

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


// CGlimProjectDlg 대화 상자



CGlimProjectDlg::CGlimProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMPROJECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CGlimProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGlimProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RESET, &CGlimProjectDlg::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CGlimProjectDlg::OnBnClickedBtnRandom)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGlimProjectDlg 메시지 처리기

BOOL CGlimProjectDlg::OnInitDialog()
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
	m_pPaintDlg = new CPaintDlg;
	m_pPaintDlg->Create(IDD_PaintDlg, this);
	m_pPaintDlg->ShowWindow(SW_SHOW);

	int nRadius = 10;
	int nEdge = 1000;
	CString str;

	//초기값 설정
	str.Format(_T("%d"), nRadius);
	SetDlgItemText(IDC_EDIT_RADIUS, str);
	str.Format(_T("%d"), nEdge);
	SetDlgItemText(IDC_EDIT_EDGE, str);

	//입력 상한선 설정
	((CEdit*)GetDlgItem(IDC_EDIT_RADIUS))->SetLimitText(2);
	((CEdit*)GetDlgItem(IDC_EDIT_EDGE))->SetLimitText(4);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGlimProjectDlg::OnBnClickedBtnReset()
{
	for (int i = 0; i < 3; i++) {
		UpdatePoint(m_nStaticID[i], DEFAULT_STR);
		m_pPaintDlg->m_PointArray[i] = CPoint(0, 0);
	}

	m_pPaintDlg->m_count = DEFAULT;
	m_pPaintDlg->InitImage();
}

UINT RandomThread(LPVOID param)
{

	CPaintDlg* pPaintDlg = (CPaintDlg*) param;

	int nWidth = 640;
	int nHeight = 480;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 3; j++) {
			pPaintDlg->m_PointArray[j].x = rand() % nWidth;
			pPaintDlg->m_PointArray[j].y = rand() % nHeight;
		}
		
		pPaintDlg->PostMessage(WM_RANDOM_UPDATE);

		Sleep(500);
	}
	return 0;
}

void CGlimProjectDlg::OnBnClickedBtnRandom()
{
	AfxBeginThread(RandomThread , m_pPaintDlg);
}

void CGlimProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_pPaintDlg;
}

void CGlimProjectDlg::UpdatePoint(int id, CString m_pt)
{	
	SetDlgItemText(id, m_pt);
}


