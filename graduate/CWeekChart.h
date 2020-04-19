#pragma once


// CWeekChart 대화 상자

class CWeekChart : public CDialogEx
{
	DECLARE_DYNAMIC(CWeekChart)

public:
	CWeekChart(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CWeekChart();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WEEK_CHART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
