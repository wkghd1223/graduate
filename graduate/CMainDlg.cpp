// CMainDlg.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CMainDlg.h"
#include "afxdialogex.h"


// CMainDlg 대화 상자

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMainDlg, pParent)
{
}

CMainDlg::~CMainDlg()
{
}
BOOL CMainDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();
	userInfoFormat.SetWindowTextW(_T("사용자\n 사용자 계정\n 사용자 ID"));

	CString str = _T("");
	str += user->getName();
	str += _T("\n");
	str += user->getAccount();
	str += _T("\n");
	str += user->getUserId();
	str += _T("\n");
	userInfo.SetWindowTextW(str);

	
	return TRUE;
}
void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_USER, userInfo);
	DDX_Control(pDX, IDC_TEXT_STATIC, userInfoFormat);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)

END_MESSAGE_MAP()
