// PaintDlg.cpp: 구현 파일
//

#include "pch.h"
#include "GlimProject.h"
#include "afxdialogex.h"
#include "PaintDlg.h"
#include "GlimProjectDlg.h"


#define WIDTH 640
#define HEIGHT 480
#define WM_RANDOM_UPDATE (WM_USER+1)

// PaintDlg 대화 상자

IMPLEMENT_DYNAMIC(CPaintDlg, CDialogEx)

CPaintDlg::CPaintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PaintDlg, pParent)
{
}

CPaintDlg::~CPaintDlg()
{
}

void CPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPaintDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_RANDOM_UPDATE, &CPaintDlg::OnRandomUpdate)
END_MESSAGE_MAP()


// PaintDlg 메시지 처리기

BOOL CPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	MoveWindow(0, 0, WIDTH, HEIGHT);

	InitImage();

	//부모 값 입력
	m_pParent = (CGlimProjectDlg*)GetParent();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPaintDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_image) {
		m_image.Draw(dc, 0, 0);
	}

}

void CPaintDlg::InitImage()
{
	if (m_image) {
		memset(fm, 0xff, WIDTH * HEIGHT);
		Invalidate();
	}
	else {
		int nBpp = 8;

		m_image.Create(WIDTH, -HEIGHT, nBpp);
		if (nBpp == 8) {
			static RGBQUAD rgb[256];
			for (int i = 0; i < 256; i++)
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
			m_image.SetColorTable(0, 256, rgb);
		}

		fm = (unsigned char*)m_image.GetBits();

		memset(fm, 0xff, WIDTH * HEIGHT);
	}
}

void CPaintDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonDown(nFlags, point);
	CGlimProjectDlg* pDlg = (CGlimProjectDlg*)m_pParent;

	if (m_count < 3) {

		m_pt.Format(L"(%d, %d)", point.x, point.y);

		pDlg-> UpdatePoint(m_nStaticID[m_count], m_pt);
		DrawPoint(point.x, point.y);
		m_PointArray[m_count] = point;

		m_count++;

	}

	if (m_count == 3) {
		for (int i = 0; i < 3; i++) {
			int dx = point.x - m_PointArray[i].x;
			int dy = point.y - m_PointArray[i].y;

			if (dx * dx + dy * dy <= m_radius*m_radius) {
				
				isDragging = true;
				m_index = i;
			
				break;
			}

		}
	}

}

void CPaintDlg::DrawPoint(int x, int y)
{
	int nPitch = m_image.GetPitch();
	fm = (unsigned char*)m_image.GetBits();
	CGlimProjectDlg* pDlg = (CGlimProjectDlg*)m_pParent;
	
	CString r;
	pDlg -> GetDlgItemText(IDC_EDIT_RADIUS, r);
	m_radius = _ttoi(r);

	for (int j = y - m_radius; j <= y + m_radius; j++) {
		for (int i = x - m_radius; i <= x + m_radius; i++) {
			if (i < 0 || j < 0 || i >= WIDTH || j >= HEIGHT) {
				continue;
			}
			int dx = i - x;
			int dy = j - y;

			if (dx * dx + dy * dy <= m_radius * m_radius) {
				fm[j * nPitch + i] = 0;
			}
		}

	}

	Invalidate();

}

void CPaintDlg::DrawCircle()
{
	CGlimProjectDlg* pDlg = (CGlimProjectDlg*)m_pParent;

	CString edge;
	pDlg -> GetDlgItemText(IDC_EDIT_EDGE, edge);

	int nPitch = m_image.GetPitch();
	fm = (unsigned char*)m_image.GetBits();

	CPoint center = CalcCircle(m_PointArray[0], m_PointArray[1], m_PointArray[2]);
	int y = center.y;
	int x = center.x;
	int r = sqrt((x- m_PointArray[0].x)* (x - m_PointArray[0].x) + (y- m_PointArray[0].y)* (y - m_PointArray[0].y));

	for (int j = y - r; j <= y + r; j++) {
		for (int i = x - r; i <= x + r; i++) {
			if (i < 0 || j < 0 || i >= WIDTH || j >= HEIGHT) {
				continue;
			}
			int dx = i - x;
			int dy = j - y;

			int dist = dx * dx + dy * dy;
			int area = r * r;

			if (abs(dist-area) <= _ttoi(edge)) {
				fm[j * nPitch + i] = 0;
			}
		}

	}

	Invalidate();

}

CPoint CPaintDlg::CalcCircle(CPoint pA, CPoint pB, CPoint pC) {
	CPoint pt;

	double x1 = pB.x - pA.x;
	double y1 = pB.y - pA.y;
	
	double x2 = pC.x - pA.x;
	double y2 = pC.y - pA.y;
		
	double dir1 = x1*(pA.x+pB.x) + y1*(pA.y+pB.y);
	double dir2 = x2 * (pA.x + pC.x) + y2 * (pA.y + pC.y);
	double dir3 = 2.0*(x1 * (pC.y - pB.y) - y1 * (pC.x - pB.x));

	if (dir3 == 0.0) {
		return CPoint(-1, -1);
	}

	pt.x = (int) ((y2*dir1-y1*dir2)/dir3);
	pt.y = (int) ((x1*dir2-x2*dir1)/dir3);

	return pt;
}

void CPaintDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CGlimProjectDlg* pDlg = (CGlimProjectDlg*)m_pParent;

	CDialogEx::OnMouseMove(nFlags, point);

	unsigned char* fm = (unsigned char*)m_image.GetBits();

	if (isDragging) {
		m_PointArray[m_index] = point;
		m_pt.Format(L"(%d, %d)", point.x, point.y);
		pDlg->UpdatePoint(m_nStaticID[m_index], m_pt);

		memset(fm, 255, WIDTH * HEIGHT);

		for (int i = 0; i < 3; i++) {
			DrawPoint(m_PointArray[i].x, m_PointArray[i].y);
		}
		DrawCircle();
	}


}

void CPaintDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnLButtonUp(nFlags, point);
	if (isDragging == true) {
		isDragging = false;
		DrawCircle();
	}
}

LRESULT CPaintDlg::OnRandomUpdate(WPARAM wParam, LPARAM lParam)
{
	unsigned char* fm = (unsigned char*)m_image.GetBits();
	memset(fm, 255, WIDTH * HEIGHT);
	CGlimProjectDlg* pDlg = (CGlimProjectDlg*)m_pParent;

	for (int i = 0; i < 3; i++)
	{
		m_pt.Format(L"(%d, %d)", m_PointArray[i].x, m_PointArray[i].y);
		pDlg->UpdatePoint(m_nStaticID[i], m_pt);
		DrawPoint(m_PointArray[i].x, m_PointArray[i].y);
	}
	DrawCircle();

	return 0;
}
