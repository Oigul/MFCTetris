//#include "pch.h"
#include "../../Public/Dialogs/CTabResultsDlg.h"
#include "../../resource.h"

IMPLEMENT_DYNAMIC(CTabResultsDlg, CDialogEx)

CTabResultsDlg::CTabResultsDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TAB_RESULTS, pParent)
{
}

void CTabResultsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RESULTS_LIST, m_ListCtrl);
}

void CTabResultsDlg::AddScore(const CString& score)
{
    int index = m_ListCtrl.GetItemCount();
    m_ListCtrl.InsertItem(index, score);
}

BOOL CTabResultsDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    m_ListCtrl.InsertColumn(0, _T("Очки"), LVCFMT_LEFT, 100);

    return TRUE;
}

BEGIN_MESSAGE_MAP(CTabResultsDlg, CDialogEx)
END_MESSAGE_MAP()
