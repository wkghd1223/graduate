#pragma once
#include "CUser.h"
#include "AutoComplete/PGEnumString.h"
#include "GridCtrl/GridCtrl.h"
#include "CStock.h"
// CInterestDlg dialog
typedef struct SectorVector {
	CString sector;
	std::vector<CString> stockNames;
};
class CInterestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInterestDlg)

public:
	CInterestDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CInterestDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CInterestDlg };
#endif
private:
	CPGEnumString* m_pEum;
	CComPtr<IAutoComplete> m_pac;
protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString		m_strScrNo;
	CWnd*		m_pParent;
	CString		m_strJongCode;

	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

	// 유저정보를 가져온다.
	CStatic userInfo;
	CStatic userInfoFormat;
	void initUserInfo();
	
	// 검색 창
	CEdit editSearch;
	// 검색어의 내용을 저장함
	CString search;

	// 검색버튼
	afx_msg void OnBnClickedOk();

	// 관심종목을 나열하는 그리드
	CGridCtrl interestGrid;
	// 그리드 컨트롤을 초기화한다.
	void initGrid(int nRow, int nCol);
	std::vector<SectorVector> sv;

	// 검색종목을 나열하는 리스트
	CListCtrl interestList;
	// 리스트에서 선택된 아이템의 인덱스를 저장
	int selectedNum = -1;
	// 리스트 컨트롤를 초기화한다.
	void initList();
	// 리스트 컨트롤의 값을 부여한다.
	void setList(CStock st);

	// 검색된 내용과 일치하는 주식들을 저장하는 변수
	std::vector<CStock> searchedStock;
	HBITMAP m_hBitmap;
	BITMAP m_bitmap;
	void initimageButton();
	CBitmapButton btnPlus;
	afx_msg void OnNMClickListInterestSearch(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonPlus();
	
};
