// CWeekChartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CWeekChartDlg.h"
#include "afxdialogex.h"


// CWeekChartDlg 대화 상자

IMPLEMENT_DYNAMIC(CWeekChartDlg, CDialogEx)

CWeekChartDlg::CWeekChartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WEEK_CHART, pParent)
{

}

CWeekChartDlg::~CWeekChartDlg()
{
}

void CWeekChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWeekChartDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CWeekChartDlg 메시지 처리기


void CWeekChartDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	//parent->cWeekChart = NULL;
	//delete this;
	CDialogEx::PostNcDestroy();
}


BOOL CWeekChartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//parent = (CMainDlg*)AfxGetMainWnd();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CWeekChartDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}


void CWeekChartDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CWeekChartDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
}
