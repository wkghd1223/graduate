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

	pwndShow = NULL;
}

CMainDlg::~CMainDlg()
{
}
BOOL CMainDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 사용자 정보
	initUserInfo();

	// 차트 combobox 일/주/월
	chartPeriod.AddString(_T("일"));
	chartPeriod.AddString(_T("주"));
	chartPeriod.AddString(_T("월"));
	chartPeriod.SetCurSel(DAY);

	InitGraph();

	// 자동완성
	HRESULT hr = m_pac.CoCreateInstance(CLSID_AutoComplete);
	if (SUCCEEDED(hr)) {
		CComQIPtr<IAutoComplete2> pAC2(m_pac);
		hr = pAC2->SetOptions(ACO_UPDOWNKEYDROPSLIST | ACO_AUTOSUGGEST | ACO_AUTOAPPEND);
		pAC2.Release();

		std::vector<std::wstring> temp;
		CgraduateDlg* parent = (CgraduateDlg*)m_pParent;
		temp = parent->GetStockData();


		m_pEum = new CPGEnumString(temp);
		hr = m_pac->Init(editSearch.GetSafeHwnd(), m_pEum, NULL, NULL);
	}

	//현재가격(호가,체결,일별 체결)
	CString currentPrice_tabName[3] = { _T("호가"), _T("체결"),_T("일별") };
	for (int i = 0; i < (sizeof(currentPrice_tabName) / sizeof(*currentPrice_tabName)); i++) {
		currentPrice.InsertItem(i + 1, currentPrice_tabName[i]);
	}
	CRect rect;
	currentPrice.GetClientRect(&rect);

	cPrice_Hoga.Create(IDD_PRICE_HOGA, &currentPrice);
	cPrice_Hoga.SetWindowPos(NULL, 5, 25, rect.Width()+10, rect.Height() - 33, SWP_SHOWWINDOW | SWP_NOZORDER);

	cPrice_Chaegyul.Create(IDD_PRICE_CHAEGYUL, &currentPrice);
	cPrice_Chaegyul.SetWindowPos(NULL, 5, 25, rect.Width()+10, rect.Height() - 33, SWP_SHOWWINDOW | SWP_NOZORDER);

	cPrice_dChaegyul.Create(IDD_PRICE_D_CHAEGYUL, &currentPrice);
	cPrice_dChaegyul.SetWindowPos(NULL, 5, 25, rect.Width()+10, rect.Height() - 33, SWP_SHOWWINDOW | SWP_NOZORDER);

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
	DDX_Control(pDX, IDC_CURRENTPRICE, currentPrice);
}
void CMainDlg::OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//userInfo.SetWindowTextW(_T("asdf"));
	CString out = sRQName;
	if (!out.Compare(L"주식기본정보")) {
		int i;
		double doubleTemp[NUM_DOUBLE] = {};
		int intTemp[2] = {};
		CString CStringTemp[2] = {};

		for (i = 0; i < NUM_DOUBLE; i++) {
			doubleTemp[i] = _tstof(theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10001[i]));
		}
		for (i = 0; i < 2; i++) {
			intTemp[i] = _ttoi(theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10001[i+NUM_DOUBLE]));
		}
		for (i = 0; i < 2 ; i++) {
			CStringTemp[i] = theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10001[i+NUM_DOUBLE+2]);
			CStringTemp[i].Trim();
		}

		stockInfo.SetWindowTextW(/*stock->GetStockName()*/CStringTemp[0]);
	}
	else if (!(out.Compare( L"주식일봉차트조회") && out.Compare(L"주식주봉차트조회" )&&out.Compare( L"주식월봉차트조회"))) {
		pointNum = theApp.kStock.GetRepeatCnt(sTrCode, sRQName);
		for (int i = 0; i < pointNum; i++) {
			CString date;
			int year, month, day;
			date = theApp.kStock.GetCommData(sTrCode, sRQName, i, listOPT10081[4]); date.Trim();
			year = _ttoi(date.Left(4));
			month = _ttoi(date.Mid(4, 2));
			day = _ttoi(date.Right(2));

			COleDateTime oDate(year, month, day, 0, 0, 0);
			pCandlePoint[i].XVal = CChartCtrl::DateToValue(oDate);

			pCandlePoint[i].Open = _tstof(theApp.kStock.GetCommData(sTrCode, sRQName, i, listOPT10081[5])); 
			pCandlePoint[i].Close = _tstof(theApp.kStock.GetCommData(sTrCode, sRQName, i, listOPT10081[1]));
			pCandlePoint[i].High = _tstof(theApp.kStock.GetCommData(sTrCode, sRQName, i, listOPT10081[6]));
			pCandlePoint[i].Low = _tstof(theApp.kStock.GetCommData(sTrCode, sRQName, i, listOPT10081[7]));

			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[0]); // 종목코드
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[2]); // 거래량
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[3]); // 거래대금
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[8]); // 수정주가구분
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[9]); // 수정비율
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[10]); // 대업종구분
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[11]); // 소업종구분
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[12]); // 종목정보
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[13]); // 수정주가이벤트
			//theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[14]); // 전일종가
		}
		ShowGraph();
	}
	else {
	}
}
void CMainDlg::initUserInfo()
{
	userInfoFormat.SetWindowTextW(_T("사용자\n 사용자 계정\n 사용자 ID"));
	CgraduateDlg* parent = (CgraduateDlg*)m_pParent;
	CUser user = parent->GetUser();
	CString str = _T("");
	str += user.getName();
	str += _T("\n");
	str += user.getAccount();
	str += _T("\n");
	str += user.getUserId();
	str += _T("\n");
	userInfo.SetWindowTextW(str);
}
BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)

	ON_NOTIFY(TCN_SELCHANGE, IDC_CURRENTPRICE, &CMainDlg::OnTcnSelchangeCurrentprice)

	ON_BN_CLICKED(IDCANCEL, &CMainDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_CHART_PERIOD, &CMainDlg::OnCbnSelchangeComboChartPeriod)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


void CMainDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	showNum = 60;

	editSearch.GetWindowText(search);
	search.Trim();
	CgraduateDlg* parent = (CgraduateDlg*)m_pParent;
	std::map<CString, CString> temp = parent->GetHashStock();
	if (temp.count(search) != 0) {
		search = temp.find(search)->second;
	}

	//날짜 선정 해줘야 함
	
	// combobox 값 별 분기
	int pos = chartPeriod.GetCurSel();
	switch (pos)
	{

	case DAY:
		theApp.kStock.SetInputValue(L"종목코드", search);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식일봉차트조회"), _T("opt10081"), 0, m_strScrNo);
		break;

	case WEEK:
		theApp.kStock.SetInputValue(L"종목코드", search);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식주봉차트조회"), _T("opt10082"), 0, m_strScrNo);
		break;

	case MONTH:
		theApp.kStock.SetInputValue(L"종목코드", search);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식월봉차트조회"), _T("opt10083"), 0, m_strScrNo);
		break;
	default:
		break;
	}

	theApp.kStock.SetInputValue(L"종목코드", search);
	theApp.kStock.CommRqData(_T("주식기본정보"), _T("OPT10001"), 0, m_strScrNo);

	//주식일봉차트에 관한 정보 받아오기
	//code : 종목입력 변수

	//CDialogEx::OnOK();
}



void CMainDlg::OnBnClickedCancel()
{

	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}



void CMainDlg::OnCbnSelchangeComboChartPeriod()
{
	showNum = 60;

	if (search.GetLength() != 6 ) {

		return;
	}
	// 종목을 선택하지 않고 눌렀을 경우 예외 처리
	// TODO: Add your control notification handler code here
	int pos = chartPeriod.GetCurSel();
	switch (pos)
	{
	case DAY:
		theApp.kStock.SetInputValue(L"종목코드", search);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식일봉차트조회"), _T("opt10081"), 0, m_strScrNo);
		break;

	case WEEK:
		theApp.kStock.SetInputValue(L"종목코드", search);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식주봉차트조회"), _T("opt10082"), 0, m_strScrNo);
		break;

	case MONTH:
		theApp.kStock.SetInputValue(L"종목코드", search);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식월봉차트조회"), _T("opt10083"), 0, m_strScrNo);
		break;
	default:
		break;
	}

}
void CMainDlg::InitGraph() {
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
	pCandle = nullptr;
}
void CMainDlg::ShowGraph() {

	if (pCandle == nullptr) {
		pCandle = chart.CreateCandlestickSerie();	
	}
	pCandle->SetPoints(pCandlePoint, showNum);
	//pCandle->SetShadowColor(RGB(255, 0, 0));
	pCandle->SetColor(RGB(0, 0, 0));
	//chart.SetBackGradient(RGB(255, 0, 0), RGB(0, 0, 255), gtHorizontal);
	RECT rect;
	chart.GetClientRect(&rect);
	pCandle->SetWidth(rect.bottom / (showNum+1));
}

void CMainDlg::OnTcnSelchangeCurrentprice(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pwndShow != NULL) {
		pwndShow->ShowWindow(SW_HIDE);
		pwndShow = NULL;
	}
	int pos = currentPrice.GetCurSel();
	switch (pos) {
	case 0:
		cPrice_Hoga.ShowWindow(SW_SHOW);
		pwndShow = &cPrice_Hoga;
		break;
	case 1:
		cPrice_Chaegyul.ShowWindow(SW_SHOW);
		pwndShow = &cPrice_Chaegyul;
		break;
	case 2:
		cPrice_dChaegyul.ShowWindow(SW_SHOW);
		pwndShow = &cPrice_dChaegyul;
		break;
	}
	*pResult = 0;
}


BOOL CMainDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	ScreenToClient(&pt);

	if (zDelta > 1 && showNum < pointNum-1) {
		showNum += 1;
	}
	else if (showNum > 0 && zDelta <= 0) {
		showNum += -1;
	}
	double max, min;
	RECT rect;
	chart.GetClientRect(&rect);
	pCandle->SetWidth(rect.bottom / (showNum+1));
	pCandle->SetPoints(pCandlePoint, showNum);



	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
