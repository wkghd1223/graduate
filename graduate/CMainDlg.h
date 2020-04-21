#pragma once
#include "CUser.h"
#include "graduate.h"
#include "ChartCtrl_source/ChartCtrl.h"
#include "ChartCtrl_source/ChartLineSerie.h"
#include "CDayChartDlg.h"
#include "CWeekChartDlg.h"
#include "CMonthChartDlg.h"

// CMainDlg 대화 상자
//class CDayChartDlg;
//class CWeekChartDlg;
//class CMonthChartDlg;

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
	CDayChartDlg cDayChart;
	CWeekChartDlg cWeekChart;
	CMonthChartDlg cMonthChart;
	CWnd* pwndShow;

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
	afx_msg void OnTcnSelchangeTabCandleChart(NMHDR* pNMHDR, LRESULT* pResult);
	void OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	CUser* user = new CUser();
	CStatic userInfo;
	CStatic userInfoFormat;
	CEdit editSearch;
	CStatic stockInfo;
	
	CTabCtrl candleChart;
	afx_msg void OnBnClickedCancel();

	virtual void PostNcDestroy();
};
