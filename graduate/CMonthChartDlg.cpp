// CMonthChartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CMonthChartDlg.h"
#include "afxdialogex.h"


// CMonthChartDlg 대화 상자

IMPLEMENT_DYNAMIC(CMonthChartDlg, CDialogEx)

CMonthChartDlg::CMonthChartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MONTH_CHART, pParent)
{

}

CMonthChartDlg::~CMonthChartDlg()
{
}

void CMonthChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonthChartDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMonthChartDlg 메시지 처리기


void CMonthChartDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	//parent->cMonthChart = NULL;
	//delete this;
	CDialogEx::PostNcDestroy();
}


BOOL CMonthChartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//parent = (CMainDlg*)AfxGetMainWnd();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CMonthChartDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnClose();
}


void CMonthChartDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}


void CMonthChartDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}
