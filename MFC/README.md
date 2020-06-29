# MFC 프로그램
목차
[구성](#구성)
[사용 라이브러리](#사용-라이브러리)

## 구성
#### CgraduateDlg
##### 설명
다른 3개의 다이얼로그를 호출하는 다이얼로그이다.
##### 함수
```c++
void CgraduateDlg::OnEventConnectKhopenapictrl1(long nErrCode)
{
	btnRun.EnableWindow(TRUE);

	user =  CUser(
		theApp.kStock.GetLoginInfo(_T("USER_NAME"))
		, theApp.kStock.GetLoginInfo(_T("ACCNO"))
		, theApp.kStock.GetLoginInfo(_T("USER_ID"))
		, theApp.kStock.GetLoginInfo(_T("GetServerGubun"))
	);
}
```
키움증권에서 제공하는 OnEventConnectKhopenapictrl1 함수를 이용하여 로그인 시 CMainDlg를 호출할 수 있게한다.
```c++
void CgraduateDlg::ReadStocks()
{
	CString str;
	CString filepath = _T("");
	filepath.Format(L".\\res\\stock_list.csv");
	setlocale(LC_ALL, "korean");
	CStdioFile file(filepath, CFile::modeRead | CFile::typeText);

	while (1) {
		if (!file.ReadString(str))
			break;
		CString temp;
		CString tok[5];
		int n = 0;
		while (::AfxExtractSubString(temp, str, n++, ',')) {
			if(n-1 < 2)
				stockData.push_back(std::wstring(temp));
			tok[n-1] = temp;
		}
		// 종목 명으로 code 검색을 하기 위함
		hashStock.insert({ tok[0], tok[1] });
		
		// 각 종목의 상장일, 업종, 등을 저장
		CStock tempStock(tok[0], tok[1], tok[2], tok[3], tok[4]);
		stockList.push_back(tempStock);
	}
}
```
상장 주식 목록 csv파일을 파싱하여 상장 주식 목록을 배열에 담는다.
```c++
BOOL CgraduateDlg::GetNextScreenNum(int nScreenType)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int nRepeat = 0;
	m_nScrN0++;
	if (m_nScrN0 > 9999)
	{
		nRepeat++;
		m_nScrN0 = 1;
	}

	if (nRepeat > 1)
	{
		nRepeat = 0;
		::AfxMessageBox(_T("더 이상 화면을 열수 없습니다.다른 화면을 닫고 실행 해 주세요~!"));
		return FALSE;
	}

	CString strKey, strTemp;
	strKey.Format(_T("%04d"), m_nScrN0);
	if (m_mapScreenNum.Lookup(strKey, strTemp))
	{
		return GetNextScreenNum(nScreenType);
	}

	nRepeat = 0;
	strTemp.Format(_T("%d"), nScreenType);
	m_mapScreenNum.SetAt(strKey, strTemp);
	return TRUE;
}

```
화면번호를 등록하고 다음화면번호를 취득하는 함수이다.
#### CMainDlg
##### 설명
주식 차트 및 호가창, 주식차트 딥러닝 결과물을 확인할 수 있는 화면이다.
CMainDlg.h
```c++
...
public:
	CString		m_strScrNo;
	CWnd*		m_pParent;
	CString		m_strJongCode;

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboChartPeriod();
	afx_msg void OnBnClickedCancel();
	void OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	
	CStatic userInfo;
	CStatic userInfoFormat;
	void initUserInfo();
	
	CEdit editSearch;
	CString search = L"";
	CStatic stockInfo;
	SChartCandlestickPoint pCandlePoint[1000];
	CChartCandlestickSerie* pCandle;
	int pointNum;
	int showNum = 60;
	void InitGraph();
	void ShowGraph();
	int period = DAY;

	CGridCtrl m_grdHoga;
	void InitHogaGrid();
	void SetDataHogaGrid(CStringArray& arrData /*CString strRealType = ""*/);

	// this is chart
	CChartCtrl chart;
	// day | week | month
	CComboBox chartPeriod;
	CStock *stock;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	CListCtrl chartList;
	void initList();
	void setList(CStock st);
	int listNum = -1;

	std::vector<CStock> searchedStock;
	afx_msg void OnNMClickListInterestSearch(NMHDR* pNMHDR, LRESULT* pResult);
...
```
##### 함수
```c++
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
```
주식차트 초기화 함수
#### CInterestDlg
#### CNewsDlg

### 사용 라이브러리
#### 키움증권 API
#### AutoComplete
#### ChartCtrl
```c++
void CChartCandlestickSerie::DrawAll(CDC *pDC)
{
	if (!m_bIsVisible)
		return;

	unsigned uFirst=0, uLast=0;
	if (!GetVisiblePoints(uFirst,uLast))
		return;

	if (pDC->GetSafeHdc())
	{
		ShadowBrush.CreateSolidBrush(m_ShadowColor);
		NewPen.CreatePen(PS_SOLID,1,m_SerieColor);
		ShadowPen.CreatePen(PS_SOLID,1,m_ShadowColor);
		// 변경
		BrushFill.CreateSolidBrush(RGB(0, 0, 255));
		// 변경
		BrushEmpty.CreateSolidBrush(RGB(255,0,0));

		pDC->SetBkMode(TRANSPARENT);
		//To have lines limited in the drawing rectangle :
		pDC->IntersectClipRect(m_PlottingRect);

		for (m_uLastDrawnPoint=uFirst;m_uLastDrawnPoint<=uLast;m_uLastDrawnPoint++)
		{
			SChartCandlestickPoint Point = GetPoint(m_uLastDrawnPoint);
			DrawCandleStick(pDC, Point);
		}

		pDC->SelectClipRgn(NULL);
		BrushFill.DeleteObject();
		BrushEmpty.DeleteObject();
		NewPen.DeleteObject();
		ShadowBrush.DeleteObject();
		ShadowPen.DeleteObject();
	}
}
```
차트 색 변경
```c++
CChartCandlestickSerie::CChartCandlestickSerie(CChartCtrl* pParent) 
  : CChartSerieBase<SChartCandlestickPoint>(pParent), m_iCandlestickWidth(800) // 
{
	m_bShadow = true;
}
```
초기 너비 변경
#### GridCtrl