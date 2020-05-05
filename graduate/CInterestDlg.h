#pragma once
#include "CUser.h"
#include "AutoComplete/PGEnumString.h"
// CInterestDlg dialog

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
	CUser* user = new CUser();
	std::vector<std::wstring>  ReadStocks();

	CStatic userInfo;
	virtual BOOL OnInitDialog();
	CStatic userInfoFormat;
	afx_msg void OnClose();
	CEdit editSearch;
	afx_msg void OnBnClickedOk();
};
