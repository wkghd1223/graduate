// CMainDlg.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#include "graduateDlg.h"
#include "GridCtrl\GridCtrl.h"

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

	initList();
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

	InitHogaGrid();
	
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
	DDX_Control(pDX, IDC_LIST_INTEREST_SEARCH, chartList);
	DDX_Control(pDX, IDC_GRD_HOGA, m_grdHoga);
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
		CString tempDate = theApp.kStock.GetCommData(sTrCode, sRQName, 0, listOPT10081[4]); tempDate.Trim();
		CTime nDate(_ttoi(tempDate.Left(4)), _ttoi(tempDate.Mid(4,2)), _ttoi(tempDate.Right(2)), 0, 0, 0);
		
		double xval = CChartCtrl::DateToValue(COleDateTime(nDate.GetTime()));
		pointNum = theApp.kStock.GetRepeatCnt(sTrCode, sRQName);
		for (int i = 0; i < pointNum; i++) {
			//CString date;
			//int year, month, day;
			//date = theApp.kStock.GetCommData(sTrCode, sRQName, i, listOPT10081[4]); date.Trim();
			//year = _ttoi(date.Left(4));
			//month = _ttoi(date.Mid(4, 2));
			//day = _ttoi(date.Right(2));
			//COleDateTime oDate(year, month, day, 0, 0, 0);
			//pCandlePoint[i].XVal = CChartCtrl::DateToValue(oDate);
			pCandlePoint[i].XVal = xval--;
			nDate = nDate - CTimeSpan(1, 0, 0, 0);
			xval = CChartCtrl::DateToValue(COleDateTime(nDate.GetTime()));

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
	else if(!out.Compare(L"주식호가요청")){
		CString strData;
		CStringArray arrData;
		int nFieldCnt = sizeof(lstOPT10004) / sizeof(*lstOPT10004);		// 전체크기 / 원소크기 = 원소개수

		//sRQName = _T("주식호가");
		int i, j, nCnt = theApp.kStock.GetRepeatCnt(sTrCode, sRQName);
		for (i = 0; i < nCnt; i++)
		{
			arrData.RemoveAll();
			for (j = 0; j < nFieldCnt; j++)
			{
				strData = theApp.kStock.GetCommData(sTrCode, sRQName, i, lstOPT10004[j].strKey);	strData.Trim();
				//				strData = theApp.m_khOpenApi.CommGetData(sTrcode, _T(""), strRQName, i, lstOPT10004[j].strKey);	strData.Trim();
				arrData.Add(strData);
			}
			SetDataHogaGrid(arrData);
		}
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


	ON_BN_CLICKED(IDCANCEL, &CMainDlg::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO_CHART_PERIOD, &CMainDlg::OnCbnSelchangeComboChartPeriod)
	ON_WM_MOUSEWHEEL()
	ON_NOTIFY(NM_CLICK, IDC_LIST_INTEREST_SEARCH, &CMainDlg::OnNMClickListInterestSearch)
END_MESSAGE_MAP()


void CMainDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	searchedStock.clear();
	chartList.DeleteAllItems();

	editSearch.GetWindowText(search);
	search = search.Trim();
	std::vector<CStock> v;
	CgraduateDlg* parent = (CgraduateDlg*)m_pParent;
	v = parent->GetStockList();
	for (auto i : v) {
		CString tempName = i.GetStockName();
		CString tempCode = i.GetStockCode();
		CString tempSector = i.GetSectors();
		if (tempName.Find(search) >= 0 || tempCode.Find(search) >= 0 || tempSector.Find(search) >= 0) {
			searchedStock.push_back(i);
		}
	}


	for (auto i : searchedStock) {
		setList(i);
	}

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

	if (listNum == -1 ) {
		return;
	}
	CString TempCode = chartList.GetItemText(listNum, 0);

	// 종목을 선택하지 않고 눌렀을 경우 예외 처리
	// TODO: Add your control notification handler code here
	int pos = chartPeriod.GetCurSel();
	switch (pos)
	{
	case DAY:
		theApp.kStock.SetInputValue(L"종목코드", TempCode);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식일봉차트조회"), _T("opt10081"), 0, m_strScrNo);
		break;

	case WEEK:
		theApp.kStock.SetInputValue(L"종목코드", TempCode);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식주봉차트조회"), _T("opt10082"), 0, m_strScrNo);
		break;

	case MONTH:
		theApp.kStock.SetInputValue(L"종목코드", TempCode);
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
	//pBottomAxis->SetTickIncrement(FALSE, CChartDateTimeAxis::tiDay, 1);
	// 축 수동설정
	
	//pBottomAxis->SetTickIncrement(false, CChartDateTimeAxis::tiMonth, 1);
	

	pBottomAxis->SetDiscrete(false);
	chart.ShowMouseCursor(false);
	CChartCrossHairCursor* pCrossHair = chart.CreateCrossHairCursor();
	pCandle = nullptr;

	
}
void CMainDlg::ShowGraph() {

	if (pCandle == nullptr) {
		pCandle = chart.CreateCandlestickSerie();	
	}
	pCandle->SetPoints(pCandlePoint, pointNum);
	//pCandle->SetShadowColor(RGB(255, 0, 0));
	pCandle->SetColor(RGB(0, 0, 0));
	//chart.SetBackGradient(RGB(255, 0, 0), RGB(0, 0, 255), gtHorizontal);

	// 현재 날짜부터 60일을 차트에 보여줌
	COleDateTime maxValue = COleDateTime::GetCurrentTime();
	CTime tempMin = CTime::GetCurrentTime() - CTimeSpan(60, 0, 0, 0);
	COleDateTime minValue(tempMin.GetTime());
	double min = CChartCtrl::DateToValue(minValue);
	double max = CChartCtrl::DateToValue(maxValue);

	// 차트에 보여지는 크기 조정
	chart.GetBottomAxis()->SetMinMax(min, max);
	pCandle->GetSerieYScreenMinMax(min, max);
	chart.GetLeftAxis()->SetMinMax(min, max);
	pCandle->SetWidth(8);

}



BOOL CMainDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	ScreenToClient(&pt);
	RECT rect;
	chart.GetClientRect(&rect);

	//if (zDelta > 1 && showNum < pointNum-1) {
	//	showNum += 1;
	//}
	//else if (showNum > 0 && zDelta <= 0) {
	//	showNum += -1;
	//}
	//double max, min;
	//
	//pCandle->SetWidth(rect.bottom / (showNum+1));
	//pCandle->SetPoints(pCandlePoint, showNum);

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void CMainDlg::initList()
{
	CRect rect;
	chartList.GetWindowRect(&rect);
	chartList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	chartList.InsertColumn(0, L"종목코드", LVCFMT_CENTER, rect.Width() * 0.25);
	chartList.InsertColumn(1, L"종목명", LVCFMT_CENTER, rect.Width() * 0.35);
	chartList.InsertColumn(2, L"업종", LVCFMT_CENTER, rect.Width() * 0.4);
}

void CMainDlg::setList(CStock st)
{
	int n = chartList.GetItemCount();
	chartList.InsertItem(n, st.GetStockCode());
	chartList.SetItem(n, 1, LVIF_TEXT, st.GetStockName(), NULL, NULL, NULL, NULL);
	chartList.SetItem(n, 2, LVIF_TEXT, st.GetSectors(), NULL, NULL, NULL, NULL);
}


void CMainDlg::OnNMClickListInterestSearch(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	listNum = pNMListView->iItem;
	CString TempCode = chartList.GetItemText(listNum, 0);
	
	//날짜 선정 해줘야 함

	// combobox 값 별 분기
	int pos = chartPeriod.GetCurSel();
	switch (pos)
	{

	case DAY:
		theApp.kStock.SetInputValue(L"종목코드", TempCode);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식일봉차트조회"), _T("opt10081"), 0, m_strScrNo);
		break;

	case WEEK:
		theApp.kStock.SetInputValue(L"종목코드", TempCode);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식주봉차트조회"), _T("opt10082"), 0, m_strScrNo);
		break;

	case MONTH:
		theApp.kStock.SetInputValue(L"종목코드", TempCode);
		theApp.kStock.SetInputValue(L"기준일자", L"20200423");
		theApp.kStock.SetInputValue(L"수정주가구분", L"0");
		theApp.kStock.CommRqData(_T("주식월봉차트조회"), _T("opt10083"), 0, m_strScrNo);
		break;
	default:
		break;
	}

	theApp.kStock.SetInputValue(L"종목코드", TempCode);
	theApp.kStock.CommRqData(_T("주식기본정보"), _T("OPT10001"), 0, m_strScrNo);

	theApp.kStock.SetInputValue(L"종목코드", TempCode);
	theApp.kStock.CommRqData(L"주식호가요청", _T("opt10004"), 0, m_strScrNo);

	//주식일봉차트에 관한 정보 받아오기
	//code : 종목입력 변수
	*pResult = 0;
}
//*******************************************************************/
//! Function Name : InitHogaGrid
//! Function      : 호가 그리드 초기 처리
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CMainDlg::InitHogaGrid()
{
	
	m_grdHoga.SetEditable(false);				//cell을 에디트 못하게 함.
	m_grdHoga.EnableScrollBar(SB_BOTH, FALSE);

	// 행/열 갯수 설정
	m_grdHoga.SetRowCount(23);
	m_grdHoga.SetColumnCount(3);

	// 열의 넓이 설정
	int i;
	for (i = 0; i < 3; i++)
	{
		m_grdHoga.SetColumnWidth(i, 80);
	}

	// 행의 높이 설정
	for (i = 0; i < 21; i++)
	{
		m_grdHoga.SetRowHeight(i, 20);
		m_grdHoga.SetItemFormat(i, 0, DT_RIGHT);
		m_grdHoga.SetItemFormat(i, 1, DT_RIGHT);
		m_grdHoga.SetItemFormat(i, 2, DT_RIGHT);
	}

	m_grdHoga.SetRowHeight(21, 22);
	m_grdHoga.SetItemFormat(21, 0, DT_RIGHT);
	m_grdHoga.SetItemFormat(21, 1, DT_CENTER);
	m_grdHoga.SetItemFormat(21, 2, DT_RIGHT);
	m_grdHoga.SetRowHeight(22, 22);
	m_grdHoga.SetItemFormat(22, 0, DT_RIGHT);
	m_grdHoga.SetItemFormat(22, 1, DT_CENTER);
	m_grdHoga.SetItemFormat(22, 2, DT_RIGHT);
	m_grdHoga.SetItemText(22, 1, L"시간외");

	// 호가 그리드 배경색 설정
	m_grdHoga.SetItemBkColour(0, 0, RGB(233, 243, 253));		// 지정된 셀의 배경색 설정
	COLORREF clrHoga[] =
	{
		RGB(253,232,227),
		RGB(205,230,235), RGB(209,234,238), RGB(216,235,241), RGB(222,237,242), RGB(226,241,244),
		RGB(233,244,246), RGB(238,246,249), RGB(243,248,251), RGB(248,252,251), RGB(249,255,253),
		RGB(251,255,250), RGB(255,250,247), RGB(255,241,241), RGB(252,239,231), RGB(252,233,226),
		RGB(253,226,219), RGB(251,221,211), RGB(250,216,204), RGB(250,210,198), RGB(252,204,192),
	};
	for (i = 0; i < 21; i++)
	{
		m_grdHoga.SetItemBkColour(i, 1, clrHoga[i]);			// 지정된 셀의 배경색 설정
	}

	COLORREF clr = RGB(238, 238, 238);
	for (i = 21; i < 23; i++)
	{
		m_grdHoga.SetItemBkColour(i, 0, clr);			// 지정된 셀의 배경색 설정
		m_grdHoga.SetItemBkColour(i, 1, clr);			// 지정된 셀의 배경색 설정
		m_grdHoga.SetItemBkColour(i, 2, clr);			// 지정된 셀의 배경색 설정
	}
	CRect rect;
	m_grdHoga.GetClientRect(&rect);

	m_grdHoga.Invalidate();
}


void CMainDlg::SetDataHogaGrid(CStringArray& arrData /*= ""*/)
{
	CString strData, strTemp;
	CString strRealType;
	int i, nCnt = arrData.GetSize();

	int nStart = 0, nEnd = nCnt;
	if (strRealType == "D")			// 주식호가잔량
	{
		nEnd = nCnt - 2;
	}
	else if (strRealType == "E")	// 주식시간외호가
	{
		nStart = nCnt - 3;
	}

	for (i = nStart; i < nEnd; i++)
	{
		strData = arrData.GetAt(i);
		if (lstOPT10004[i].bTextColor)
		{
			theApp.SetDataFgColour(&m_grdHoga, lstOPT10004[i].nRow, lstOPT10004[i].nCol, strData);
		}
		if (lstOPT10004[i].nDataType == DT_SIGN)
		{
			theApp.SetSignData(&m_grdHoga, lstOPT10004[i].nRow, lstOPT10004[i].nCol, strData);
		}
		else
		{
			m_grdHoga.SetItemText(lstOPT10004[i].nRow, lstOPT10004[i].nCol, theApp.ConvDataFormat(lstOPT10004[i].nDataType, strData, lstOPT10004[i].strBeforeData, lstOPT10003[i].strAfterData));
		}
	}
	m_grdHoga.Invalidate();
}