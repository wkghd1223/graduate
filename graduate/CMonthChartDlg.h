#pragma once

//class CMainDlg;
// CMonthChartDlg 대화 상자

class CMonthChartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMonthChartDlg)

public:
	CMonthChartDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMonthChartDlg();
	//CMainDlg* parent;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MONTH_CHART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnClose();
	virtual void OnCancel();
	afx_msg void OnDestroy();
};
