// CMainDlg.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#include "graduateDlg.h"

//#include "CchartDlg.h"
//#include "CWeekChartDlg.h"
//#include "CMonthChartDlg.h"
// CMainDlg 대화 상자

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMainDlg, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "7777";
	m_strJongCode = "";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

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

	chartPeriod.AddString(_T("일"));
	chartPeriod.AddString(_T("주"));
	chartPeriod.AddString(_T("월"));
	chartPeriod.SetCurSel(DAY);


	return TRUE;
}

//*******************************************************************/
//! Function Name : OnClose
//! Function      : 파괴자
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CMainDlg::OnClose()
{
	// 화면 닫을 때 부모윈도우에게 통보(화면 관리 위해)
	if (m_pParent)
	{
		int nLen = m_strScrNo.GetLength();
		char* cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);
	}

	CDialogEx::OnClose();
}
void CMainDlg::OnPaint()
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
void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_USER, userInfo);
	DDX_Control(pDX, IDC_TEXT_STATIC, userInfoFormat);
	DDX_Control(pDX, IDC_EDIT_SEARCH, editSearch);
	DDX_Control(pDX, IDC_TEXT_STOCK_INFO, stockInfo);
	DDX_Control(pDX, IDC_CUSTOM_CHART, chart);
	DDX_Control(pDX, IDC_COMBO_CHART_PERIOD, chartPeriod);
}
//BEGIN_EVENTSINK_MAP(CMainDlg, CDialogEx)
//ON_EVENT(CMainDlg, IDC_KHOPENAPICTRL1, 1, CMainDlg::OnReceiveTrDataKhopenapictrl1, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
//END_EVENTSINK_MAP()
void CMainDlg::OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//userInfo.SetWindowTextW(_T("asdf"));
	CString out = sRQName;
	CString str = _T("");
	if (out == _T("주식기본정보")) {
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("종목명"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("시가총액"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("현재가"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("거래량"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("PER"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("PBR"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("ROE"));
		out.Trim();
		stockInfo.SetWindowTextW(str);
	}
}
BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CMainDlg::OnEnChangeEditSearch)
	ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMainDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_CHART_PERIOD, &CMainDlg::OnCbnSelchangeComboChartPeriod)
END_MESSAGE_MAP()


void CMainDlg::OnEnChangeEditSearch()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMainDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString code = _T("");

	editSearch.GetWindowText(code);

	theApp.kStock.SetInputValue(_T("종목코드"), code);
	theApp.kStock.CommRqData(_T("주식기본정보"), _T("OPT10001"), 0, m_strScrNo);

	ShowGraph(code);
	//CDialogEx::OnOK();
}


void CMainDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}



void CMainDlg::OnCbnSelchangeComboChartPeriod()
{
	// TODO: Add your control notification handler code here
	int pos = chartPeriod.GetCurSel();
	switch (pos)
	{
	case DAY:

		break;
	case WEEK:
		break;
	case MONTH:
		break;
	default:
		break;
	}
}
void CMainDlg::ShowGraph(CString code) {
	CChartDateTimeAxis* pBottomAxis = chart.CreateDateTimeAxis(CChartCtrl::BottomAxis);
	CChartStandardAxis* pLeftAxis = chart.CreateStandardAxis(CChartCtrl::LeftAxis);

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
	chart.ShowMouseCursor(false);
	CChartCrossHairCursor* pCrossHair = chart.CreateCrossHairCursor();

	CChartXYSerie* pSeries = nullptr;
	pSeries = chart.CreateLineSerie();

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
	pCandle = chart.CreateCandlestickSerie();
	SChartCandlestickPoint pCandlePoint[600];

	ReadData(pCandlePoint);
	pCandle->SetPoints(pCandlePoint, 600);
	pCandle->SetColor(RGB(0, 0, 255));
	pCandle->CreateBalloonLabel(5, _T("this is a candle"));

	pCandle->SetVisible(true);

	// 이미지로 저장했을 때 이미지가 보여지는 것으로 보아 
	//RECT rect;
	//GetClientRect(&rect);
	//chart.SaveAsImage(_T("asf.png"), rect,32);
}

void CMainDlg::ReadData(SChartCandlestickPoint(&pCandlePoint)[600])
{
	//UpdateData(TRUE);

	int year = 2017, month = 4, day = 6;
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