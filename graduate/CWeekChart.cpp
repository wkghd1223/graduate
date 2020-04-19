// CWeekChart.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CWeekChart.h"
#include "afxdialogex.h"


// CWeekChart 대화 상자

IMPLEMENT_DYNAMIC(CWeekChart, CDialogEx)

CWeekChart::CWeekChart(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_WEEK_CHART, pParent)
{

}

CWeekChart::~CWeekChart()
{
}

void CWeekChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWeekChart, CDialogEx)
END_MESSAGE_MAP()


// CWeekChart 메시지 처리기
