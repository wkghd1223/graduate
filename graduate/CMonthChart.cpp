// CMonthChart.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CMonthChart.h"
#include "afxdialogex.h"


// CMonthChart 대화 상자

IMPLEMENT_DYNAMIC(CMonthChart, CDialogEx)

CMonthChart::CMonthChart(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MONTH_CHART, pParent)
{

}

CMonthChart::~CMonthChart()
{
}

void CMonthChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMonthChart, CDialogEx)
END_MESSAGE_MAP()


// CMonthChart 메시지 처리기
