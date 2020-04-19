#pragma once


// CMonthChart 대화 상자

class CMonthChart : public CDialogEx
{
	DECLARE_DYNAMIC(CMonthChart)

public:
	CMonthChart(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMonthChart();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MONTH_CHART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
