
// MFCTetrisDlg.cpp: файл реализации
//

#include "../../pch.h"
#include "../../framework.h"
#include "../../Public/MFCTetris.h"
#include "../../Public/Dialogs/MFCTetrisDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CMFCTetrisDlg
CMFCTetrisDlg::CMFCTetrisDlg(std::vector<int> &scores, CWnd* pParent /*=nullptr*/)
	:m_scores(scores), CDialogEx(IDD_MFCTETRIS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTetrisDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		Invalidate();
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL CMFCTetrisDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
		case VK_RIGHT:
		case VK_DOWN:
		case VK_UP:
			m_GameDlg.PreTranslateMessage(pMsg);
			return true;
		}
		Invalidate();
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CMFCTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCTetrisDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, &CMFCTetrisDlg::OnTcnSelchangeTabControl)
END_MESSAGE_MAP()


// Обработчики сообщений CMFCTetrisDlg
BOOL CMFCTetrisDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок


	//TabControl
	m_TabCtrl.SubclassDlgItem(IDC_TAB_CONTROL, this);
	m_TabCtrl.InsertItem(0, _T("Игра"));
	m_TabCtrl.InsertItem(1, _T("Результаты"));

	m_GameDlg.Create(IDD_TAB_GAME, &m_TabCtrl);
	m_ResultsDlg.Create(IDD_TAB_RESULTS, &m_TabCtrl);

	CRect rc;
	m_TabCtrl.GetClientRect(&rc);     // Получение полного прямоугольника таба
	m_TabCtrl.AdjustRect(FALSE, &rc); // Сужение rc до области содержимого (без вкладок)
	m_GameDlg.MoveWindow(&rc);
	m_ResultsDlg.MoveWindow(&rc);

	m_GameDlg.ShowWindow(SW_SHOW);
	m_ResultsDlg.ShowWindow(SW_HIDE);

	m_CurrentTab = 0;

	//bd
	WriteScoreTable();
	
	//таймер для более плавного перемещения фигур
	SetTimer(1, 50, NULL);


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CMFCTetrisDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCTetrisDlg::OnTcnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult)
{
	m_CurrentTab = m_TabCtrl.GetCurSel();

	if (m_CurrentTab == 0)
	{
		m_GameDlg.ShowWindow(SW_SHOW);
		m_ResultsDlg.ShowWindow(SW_HIDE);
		m_GameDlg.SetFocus();
		//m_GameDlg.GetDlgItem(IDC_TAB_CONTROL)->SetFocus();
	}
	else
	{
		m_GameDlg.ShowWindow(SW_HIDE);
		m_ResultsDlg.ShowWindow(SW_SHOW);
		//m_ResultsDlg.SetFocus();
	}

	*pResult = 0; // сигнал системе: уведомление обработано успешно
}

void CMFCTetrisDlg::OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	int tabIndex = m_TabCtrl.GetCurSel();

	m_CurrentTab = tabIndex;
	
	Invalidate();

	*pResult = 0; // сигнал системе: уведомление обработано успешно
}

void CMFCTetrisDlg::WriteScoreTable()
{
	for (int i = 0; i < m_scores.size(); ++i)
	{
		CString scoreStr;
		scoreStr.Format(_T("%d очков"), m_scores[i]);
		m_ResultsDlg.AddScore(scoreStr);
	}
}

int CMFCTetrisDlg::GetCurrentScore()
{
	return m_GameDlg.GetCurrentScore();
}
