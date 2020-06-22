#pragma once
#include "CUser.h"
#include "graduate.h"
#include "CStock.h"
#include "ChartCtrl_source/ChartCtrl.h"
#include "ChartCtrl_source/ChartLineSerie.h"
#include "ChartCtrl_source/ChartCandlestickSerie.h"
#include "AutoComplete/PGEnumString.h"
#include "GridCtrl/GridCtrl.h"

// CMainDlg 대화 상자



const CString listOPT10001[] = {
	 L"시가", L"종가", L"고가", L"저가", L"기준가", 
	 L"현재가", L"거래량", L"시가총액",L"자본금",L"액면가",
	L"매출액", L"영업이익", L"당기순이익", L"유통주식", L"ROE",
	L"PER", L"PBR", L"EV", L"상장주식", L"종목코드", 
	L"종목명", L"신용비율"
};
const stGRID lstOPT10003[] =
{
	{L"시간",			L"20",	-1,	0,	DT_TIME,		FALSE,	DT_CENTER,	L"",	L""},
	{L"현재가",			L"10",	-1,	1,	DT_ZERO_NUMBER,	TRUE,	DT_RIGHT,	L"",	L""},
	{L"sign",			L"25",	-1,	2,	DT_SIGN,		TRUE,	DT_CENTER,	L"",	L""},
	{L"전일대비",		L"11",	-1,	3,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",	L""},
	{L"누적거래량",		L"13",	-1,	4,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""},
	{L"누적거래대금",	L"14",	-1,	5,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",	L""},
};

const stGRID lstOPT10004[] =
{
	/////////////////////////////////////
	// 총매도/매수 잔량
	{L"총매도잔량",		L"61",	0,	0,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",L""},
	{L"총매수잔량",		L"63",	0,	1,	DT_ZERO_NUMBER,	FALSE,	DT_RIGHT,	L"",L""},
	/////////////////////////////////////
	// 매도호가
	{L"매도10차선잔량",	L"70",	1,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도10차선호가",	L"50",	1,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도9차선잔량",	L"69",	2,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도9차선호가",	L"49",	2,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도8차선잔량",	L"68",	3,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도8차선호가",	L"48",	3,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도7차선잔량",	L"67",	4,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도7차선호가",	L"47",	4,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도6차선잔량",	L"66",	5,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도6차선호가",	L"46",	5,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도5차선잔량",	L"65",	6,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도5차선호가",	L"45",	6,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도4차선잔량",	L"64",	7,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도4차선호가",	L"44",	7,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도3차선잔량",	L"63",	8,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도3차선호가",	L"43",	8,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도2차선잔량",	L"62",	9,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도2차선호가",	L"42",	9,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도최우선잔량",	L"61",	10,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매도최우선호가",	L"41",	10,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	/////////////////////////////////////
	// 매수호가
	{L"매수최우선호가",	L"51",	11,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매도최우선잔량",	L"71",	11,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수2차선호가",	L"52",	12,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수2차선잔량",	L"72",	12,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수3차선호가",	L"53",	13,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수3차선잔량",	L"73",	13,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수4차선호가",	L"54",	14,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수4차선잔량",	L"74",	14,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수5차선호가",	L"55",	15,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수5차선잔량",	L"75",	15,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수6차선호가",	L"56",	16,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수6차선잔량",	L"76",	16,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수7차선호가",	L"57",	17,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수7차선잔량",	L"77",	17,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수8차선호가",	L"58",	18,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수8차선잔량",	L"78",	18,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수9차선호가",	L"59",	19,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수9차선잔량",	L"79",	19,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"매수10차선호가",	L"60",	20,	1,	DT_NUMBER,		TRUE,	DT_RIGHT,	L"",L""},
	{L"매수10차선잔량",	L"80",	20,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	/////////////////////////////////////
	// 총잔량
	{L"총매도잔량",		L"121",	21,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"총매수잔량",		L"125",	21,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	/////////////////////////////////////
	// 호가잔량기준시간
	{L"호가잔량기준시간",L"21",	21,	1,	DT_TIME,		FALSE,	DT_CENTER,	L"",L""},
	/////////////////////////////////////
	// 시간외 매도/매수 잔량
	{L"시간외매도잔량",	L"131",	22,	0,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
	{L"시간외매수잔량",	L"132",	22,	2,	DT_NUMBER,		FALSE,	DT_RIGHT,	L"",L""},
};
const CString listOPT10081[] = {
	L"종목코드", L"현재가", L"거래량", L"거래대금", L"일자", L"시가", L"고가", L"저가", L"수정주가구분", L"수정비율", L"대업종구분", L"소업종구분", L"종목정보", L"수정주가이벤트", L"전일종가"
};
class CMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMainDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMainDlg };
#endif
	CWnd* pwndShow;


	// 차트 일/주/월
	enum {DAY = 0, WEEK = 1, MONTH = 2};

	// 자동완성기능
private:
	CPGEnumString* m_pEum;
	CComPtr<IAutoComplete> m_pac;
protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
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
};
