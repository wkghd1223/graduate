#pragma once
#include "ChartCtrl_source/ChartCtrl.h"
#include "ChartCtrl_source/ChartLineSerie.h"
#include "ChartCtrl_source/ChartCandlestickSerie.h"

class CMainDlg;
// CDayChartDlg 대화 상자

class CDayChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDayChartDlg)

public:
	CDayChartDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDayChartDlg();

	//CMainDlg* parent;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DAY_CHART };
#endif

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void PostNcDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnClose();

	DECLARE_MESSAGE_MAP()
public:
	CChartCtrl dayChart;

	CChartLineSerie* pSeries;
	CChartCandlestickSerie* pCandle;
	void ShowGraph(CString code);
	void ReadData(SChartCandlestickPoint (&pCandlePoint)[600]);
	afx_msg void OnIdok();
	afx_msg void OnIdcancel();
	//afx_msg void OnPaint();
	afx_msg void OnDestroy();
};
