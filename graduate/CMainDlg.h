#pragma once
#include "CUser.h"
#include "graduate.h"
<<<<<<< HEAD
#include "CDayChart.h"
#include "CWeekChart.h"
#include "CMonthChart.h"
#include "CurrentPrice_chaegyul.h"
#include "CurrentPrice_day_chaegyul.h"
#include "CurrentPrice_hoga.h"
=======
#include "ChartCtrl_source/ChartCtrl.h"
#include "ChartCtrl_source/ChartLineSerie.h"
#include "ChartCtrl_source/ChartCandlestickSerie.h"
>>>>>>> a2be0a5b03e5a23ce56ab39ac2edde5ffa5011a9

// CMainDlg 대화 상자


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

	enum {DAY = 0, WEEK = 1, MONTH = 2};
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

	afx_msg void OnEnChangeEditSearch();
	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboChartPeriod();
	afx_msg void OnBnClickedCancel();
	void OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	CUser* user = new CUser();
	CStatic userInfo;
	CStatic userInfoFormat;
	CEdit editSearch;
	CStatic stockInfo;
	afx_msg void OnBnClickedCancel();
	CTabCtrl currentPrice;
	afx_msg void OnTcnSelchangeCurrentprice(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnBnClickedCancel();
	void ShowGraph(CString code);
	void ReadData(SChartCandlestickPoint(&pCandlePoint)[600]);
	int period = DAY;


	// this is chart
	CChartCtrl chart;
	// day | week | month
	CComboBox chartPeriod;
};
