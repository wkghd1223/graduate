#pragma once


// CurrentPrice_day_chaegyul 대화 상자

class CurrentPrice_day_chaegyul : public CDialogEx
{
	DECLARE_DYNAMIC(CurrentPrice_day_chaegyul)

public:
	CurrentPrice_day_chaegyul(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CurrentPrice_day_chaegyul();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRICE_D_CHAEGYUL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
