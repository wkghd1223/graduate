#pragma once
#include "CUser.h"
#include "graduate.h"
#include "CStock.h"
#include "CurrentPrice_chaegyul.h"
#include "CurrentPrice_day_chaegyul.h"
#include "CurrentPrice_hoga.h"
#include "ChartCtrl_source/ChartCtrl.h"
#include "ChartCtrl_source/ChartLineSerie.h"
#include "ChartCtrl_source/ChartCandlestickSerie.h"
#include "AutoComplete/PGEnumString.h"

// CMainDlg 대화 상자
#define NUM_DOUBLE 18

const CString listOPT10001[] = {
	 L"시가", L"종가", L"고가", L"저가", L"기준가", 
	 L"현재가", L"거래량", L"시가총액",L"자본금",L"액면가",
	L"매출액", L"영업이익", L"당기순이익", L"유통주식", L"ROE",
	L"PER", L"PBR", L"EV", L"상장주식", L"종목코드", 
	L"종목명", L"신용비율"
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

	CurrentPrice_hoga cPrice_Hoga;
	CurrentPrice_chaegyul cPrice_Chaegyul;
	CurrentPrice_day_chaegyul cPrice_dChaegyul;

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
	afx_msg void OnTcnSelchangeCurrentprice(NMHDR* pNMHDR, LRESULT* pResult);
	void OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	CUser* user = new CUser();
	CStatic userInfo;
	CStatic userInfoFormat;
	CEdit editSearch;
	CString search = L"";
	CStatic stockInfo;
	CTabCtrl currentPrice;
	SChartCandlestickPoint pCandlePoint[1000];
	CChartCandlestickSerie* pCandle;
	int pointNum;
	int showNum = 60;
	void InitGraph();
	void ShowGraph();
	int period = DAY;


	// this is chart
	CChartCtrl chart;
	// day | week | month
	CComboBox chartPeriod;
	CStock *stock;
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
