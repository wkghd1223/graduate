#pragma once


// CurrentPrice_chaegyul 대화 상자

class CurrentPrice_chaegyul : public CDialogEx
{
	DECLARE_DYNAMIC(CurrentPrice_chaegyul)

public:
	CurrentPrice_chaegyul(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CurrentPrice_chaegyul();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRICE_CHAEGYUL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
