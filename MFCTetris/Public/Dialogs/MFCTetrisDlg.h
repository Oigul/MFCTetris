
// MFCTetrisDlg.h: файл заголовка
//

#pragma once

#include "..\..\Public\Dialogs\CTabGameDlg.h"
#include "..\..\Public\Dialogs\CTabResultsDlg.h"
#include "..\..\Public\Game\Game.h"

//S:\C++ projects\MFCTetris\MFCTetris\CTabResultsDlg.h
// Диалоговое окно CMFCTetrisDlg
class CMFCTetrisDlg : public CDialogEx
{
// Создание
public:
	CMFCTetrisDlg(std::vector<int> &scores, CWnd* pParent = nullptr);

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTETRIS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV

// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTcnSelchangeTabControl(NMHDR* pNMHDR, LRESULT* pResult);

public:
	int GetCurrentScore();

private:
	CTabCtrl m_TabCtrl;
	CTabGameDlg m_GameDlg;
	CTabResultsDlg m_ResultsDlg;
	
	int m_CurrentTab;

	std::vector<int> m_scores;

	void OnTabSelChange(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL PreTranslateMessage(MSG* pMsg);

	void OnTimer(UINT_PTR nIDEvent);
	
	void WriteScoreTable();
};
