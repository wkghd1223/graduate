#pragma once


// CurrentPrice_hoga 대화 상자

class CurrentPrice_hoga : public CDialogEx
{
	DECLARE_DYNAMIC(CurrentPrice_hoga)

public:
	CurrentPrice_hoga(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CurrentPrice_hoga();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRICE_HOGA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
