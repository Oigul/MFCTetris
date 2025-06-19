#pragma once

#include <afxdialogex.h>
#include "../../resource.h"

#include "../Game/Game.h"
//s:\c++ projects\mfctetris\MFCTetris\Game.h

class CTabGameDlg : public CDialogEx
{
public:
    CTabGameDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TAB_GAME };  // ID ресурса диалога
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    // Реализация
protected:
    // Созданные функции схемы сообщений
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();

    DECLARE_DYNAMIC(CTabGameDlg)
    DECLARE_MESSAGE_MAP()

public:
    int GetCurrentScore();
    BOOL PreTranslateMessage(MSG* pMsg);

private:
    std::unique_ptr<Game> m_Game;
    void DrawField(CDC& dc);
    void OnTimer(UINT_PTR nIDEvent);
};

