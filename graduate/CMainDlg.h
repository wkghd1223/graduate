﻿#pragma once
#include "CUser.h"
#include "graduate.h"
#include "CDayChart.h"
#include "CWeekChart.h"
#include "CMonthChart.h"
#include "CurrentPrice_chaegyul.h"
#include "CurrentPrice_day_chaegyul.h"
#include "CurrentPrice_hoga.h"

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
	CDayChart cDayChart;
	CWeekChart cWeekChart;
	CMonthChart cMonthChart;
	CWnd* pwndShow;

	CurrentPrice_hoga cPrice_Hoga;
	CurrentPrice_chaegyul cPrice_Chaegyul;
	CurrentPrice_day_chaegyul cPrice_dChaegyul;

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	CString		m_strScrNo;
	CWnd*		m_pParent;
	CString		m_strJongCode;

	void OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	CUser* user = new CUser();
	CStatic userInfo;
	CStatic userInfoFormat;
	afx_msg void OnEnChangeEditSearch();
	CEdit editSearch;
	CStatic stockInfo;
	afx_msg void OnBnClickedOk();
	
	CTabCtrl candleChart;
	afx_msg void OnTcnSelchangeTabCandleChart(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl currentPrice;
	afx_msg void OnTcnSelchangeCurrentprice(NMHDR* pNMHDR, LRESULT* pResult);
	
};
