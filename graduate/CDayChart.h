#pragma once


// CDayChart 대화 상자

class CDayChart : public CDialogEx
{
	DECLARE_DYNAMIC(CDayChart)

public:
	CDayChart(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDayChart();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DAY_CHART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
