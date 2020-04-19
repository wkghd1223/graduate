// CDayChart.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CDayChart.h"
#include "afxdialogex.h"


// CDayChart 대화 상자

IMPLEMENT_DYNAMIC(CDayChart, CDialogEx)

CDayChart::CDayChart(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DAY_CHART, pParent)
{

}

CDayChart::~CDayChart()
{
}

void CDayChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDayChart, CDialogEx)
END_MESSAGE_MAP()


// CDayChart 메시지 처리기
