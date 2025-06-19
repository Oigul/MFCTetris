//#include "pch.h"
#include "../../Public/Dialogs/CTabGameDlg.h"
#include "../../resource.h"

#include <ctime>

IMPLEMENT_DYNAMIC(CTabGameDlg, CDialogEx)

CTabGameDlg::CTabGameDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TAB_GAME, pParent)
{
}

BOOL CTabGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	int randomNumber = std::rand() % 7;    // Число от 0 до 6
	m_Game = std::make_unique<Game>(randomNumber);

	SetTimer(1, 500, NULL);
	std::srand(std::time(nullptr));

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CTabGameDlg::OnPaint()
{
	CPaintDC dc(this); // контекст устройства для рисования
	DrawField(dc);
}

void CTabGameDlg::DrawField(CDC& dc)
{
	const int cellSize = 20;
	for (int y = 0; y < m_Game->GetRowCount(); ++y)
	{
		for (int x = 0; x < m_Game->GetColCount(); ++x)
		{
			CBrush brush(m_Game->IsCellFilled(x,y) ? RGB(0, 120, 255) : RGB(240, 240, 240));
			CRect rect(x * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize);
			dc.FillRect(rect, &brush);
		}
	}
}

void CTabGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		m_Game->Tick();
		Invalidate();
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CTabGameDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (m_Game->OnKeyDown(pMsg->wParam))
		{
			Invalidate();
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTabGameDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

int CTabGameDlg::GetCurrentScore()
{
	return m_Game->GetCurrentScore();
}

BEGIN_MESSAGE_MAP(CTabGameDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()
