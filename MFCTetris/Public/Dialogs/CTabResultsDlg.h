#pragma once

#include <afxdialogex.h>

class CTabResultsDlg : public CDialogEx
{
public:
    CTabResultsDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TAB_RESULTS};  // ID ресурса диалога
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    // Созданные функции схемы сообщений
    virtual BOOL OnInitDialog();

    DECLARE_DYNAMIC(CTabResultsDlg)
    DECLARE_MESSAGE_MAP()

public:
    void AddScore(const CString& score);

private:
    CListCtrl m_ListCtrl;
};
