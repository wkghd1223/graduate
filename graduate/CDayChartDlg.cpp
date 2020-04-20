// CDayChartDlg.cpp: 구현 파일
//
#include "pch.h"
#include "graduate.h"
#include "CDayChartDlg.h"
#include "afxdialogex.h"
//#include "jsoncpp/include/json/json.h"
//#pragma commet(lib, "jsoncpp\\lib\\lib_json.lib")

// CDayChartDlg 대화 상자

IMPLEMENT_DYNAMIC(CDayChartDlg, CDialogEx)

CDayChartDlg::CDayChartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DAY_CHART, pParent)
{

}
CDayChartDlg::~CDayChartDlg()
{
}
BOOL CDayChartDlg::OnInitDialog()
{
	parent = (CMainDlg*)AfxGetMainWnd();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	return TRUE;
}
void CDayChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CUSTOM_CHART_DAY, dayChart);
}

void CDayChartDlg::ShowGraph(CString code)
{
	
	((CStatic*)GetDlgItem(IDC_STATIC_TEST))->SetWindowTextW(code);
	
	CChartDateTimeAxis* pBottomAxis = dayChart.CreateDateTimeAxis(CChartCtrl::BottomAxis);
	CChartStandardAxis* pLeftAxis = dayChart.CreateStandardAxis(CChartCtrl::LeftAxis);

	// 축 자동설정
	pBottomAxis->SetAutomaticMode(CChartAxis::FullAutomatic);
	pLeftAxis->SetAutomaticMode(CChartAxis::FullAutomatic);
	// 축 수동설정
	//COleDateTime minValue(2019, 1, 1, 0, 0, 0);
	//COleDateTime maxValue(2019, 9, 30, 0, 0, 0);
	//pBottomAxis->SetMinMax(CChartCtrl::DateToValue(minValue), CChartCtrl::DateToValue(maxValue));
	//pBottomAxis->SetTickIncrement(false, CChartDateTimeAxis::tiMonth, 1);
	//pBottomAxis->SetTickLabelFormat(false, _T("%b %Y"));

	
	pBottomAxis->SetDiscrete(false);
	dayChart.ShowMouseCursor(false);
	CChartCrossHairCursor* pCrossHair = dayChart.CreateCrossHairCursor();

	CChartXYSerie* pSeries = nullptr;
	pSeries = dayChart.CreateLineSerie();

	double XVal[50];
	double YVal[50];
	for (int i = 0; i < 50; i++) {
		COleDateTime date(2017, 6, 1, 0, 0, 0);
		XVal[i] = CChartCtrl::DateToValue(date) + (double)i * 16;
		YVal[i] = sin(i) * 5000 + 47000;
	}
	pSeries->SetPoints(XVal, YVal, 50);
	pSeries->SetColor(RGB(255, 0, 0));
	pSeries->CreateBalloonLabel(5, _T("this is sin curve"));

	CChartCandlestickSerie* pCandle = nullptr;
	pCandle = dayChart.CreateCandlestickSerie();
	SChartCandlestickPoint pCandlePoint[600];

	ReadData(pCandlePoint);
	pCandle->SetPoints(pCandlePoint, 600);
	pCandle->SetColor(RGB(0, 255, 255));
	pCandle->CreateBalloonLabel(5, _T("this is a candle"));
	//pCandle->SetVisible(true);
}

void CDayChartDlg::ReadData(SChartCandlestickPoint(&pCandlePoint)[600])
{
	//UpdateData(TRUE);

	int year = 2017 , month = 4, day = 6 ;
	for (int i = 0; i < 600; i++) {
		pCandlePoint[i].Open = 46000.0;
		pCandlePoint[i].Close = 53234.0;
		pCandlePoint[i].High = 54300.0;
		pCandlePoint[i].Low = 43542.0;
		
		COleDateTime date(year, month, day, 0, 0, 0);
		pCandlePoint[i].XVal = CChartCtrl::DateToValue(date);
		day++;
		if (day > 28) {
			day = 1;
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}
	}
}


BEGIN_MESSAGE_MAP(CDayChartDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_COMMAND(IDOK, &CDayChartDlg::OnIdok)
	ON_COMMAND(IDCANCEL, &CDayChartDlg::OnIdcancel)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDayChartDlg 메시지 처리기


void CDayChartDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	parent->cDayChart = NULL;
	delete this;
	CDialogEx::PostNcDestroy();
}


void CDayChartDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	this->DestroyWindow();
	//CDialogEx::OnCancel();
}


void CDayChartDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	this->DestroyWindow();
	//CDialogEx::OnOK();
}

void CDayChartDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	this->DestroyWindow();
	//CDialogEx::OnClose();
}

void CDayChartDlg::OnIdok()
{
	// TODO: Add your command handler code here
}


void CDayChartDlg::OnIdcancel()
{
	// TODO: Add your command handler code here
}


void CDayChartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


void CDayChartDlg::OnDestroy()
{
	
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}
