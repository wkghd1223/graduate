// CInterestDlg.cpp : implementation file
//

#include "pch.h"
#include "graduate.h"
#include "CInterestDlg.h"
#include "afxdialogex.h"
#include "graduateDlg.h"
#include "CStock.h"

// CInterestDlg dialog

IMPLEMENT_DYNAMIC(CInterestDlg, CDialogEx)

CInterestDlg::CInterestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CInterestDlg, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "8888";
	m_strJongCode = "";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CInterestDlg::~CInterestDlg()
{
}

void CInterestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_USER, userInfo);
	DDX_Control(pDX, IDC_TEXT_STATIC, userInfoFormat);
	DDX_Control(pDX, IDC_EDIT_SEARCH, editSearch);
}


BEGIN_MESSAGE_MAP(CInterestDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CInterestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInterestDlg message handlers

BOOL CInterestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	userInfoFormat.SetWindowTextW(_T("사용자\n 사용자 계정\n 사용자 ID"));

	CString str = _T("");
	str += user->getName();
	str += _T("\n");
	str += user->getAccount();
	str += _T("\n");
	str += user->getUserId();
	str += _T("\n");
	userInfo.SetWindowTextW(str);

	// TODO:  Add extra initialization here



	HRESULT hr = m_pac.CoCreateInstance(CLSID_AutoComplete);
	if (SUCCEEDED(hr)) {
		CComQIPtr<IAutoComplete2> pAC2(m_pac);
		hr = pAC2->SetOptions(ACO_UPDOWNKEYDROPSLIST | ACO_AUTOSUGGEST | ACO_AUTOAPPEND);
		pAC2.Release();

		std::vector<std::wstring> temp;
		CgraduateDlg* parent = (CgraduateDlg*)m_pParent;
		temp = parent->GetStockData();

		m_pEum = new CPGEnumString(temp);
		hr = m_pac->Init(editSearch.GetSafeHwnd(), m_pEum, NULL, NULL);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CInterestDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	if (m_pParent)
	{
		int nLen = m_strScrNo.GetLength();
		char* cScrNo = new char[nLen + 1];
		memset(cScrNo, 0x00, nLen + 1);
		memcpy(cScrNo, m_strScrNo, nLen);
		m_pParent->PostMessage(UM_SCRENN_CLOSE, 0U, (LPARAM)cScrNo);
	}
	CDialogEx::OnClose();
}


void CInterestDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
