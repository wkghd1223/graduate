
// graduateDlg.h: 헤더 파일
//

#pragma once
#define UM_SCRENN_CLOSE		1000


// CgraduateDlg 대화 상자
class CgraduateDlg : public CDialogEx
{
// 생성입니다.

public:
	CgraduateDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GRADUATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnScreenClose(WPARAM wParam, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
	DECLARE_EVENTSINK_MAP();
public:

	CMapStringToPtr m_mapScreen;
	CMapStringToString m_mapScreenNum;
	int m_nScrN0;
	BOOL GetNextScreenNum(int nScreenType);
	void OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg);
	
	afx_msg void OnBnClickedOk();
};
