#pragma once
#include "CMainDlg.h"

class CMainDlg;
// CWeekChartDlg 대화 상자

class CWeekChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWeekChartDlg)

public:
	CWeekChartDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CWeekChartDlg();
	CMainDlg* parent;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WEEK_CHART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
public:
	virtual void OnCancel();
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
};
