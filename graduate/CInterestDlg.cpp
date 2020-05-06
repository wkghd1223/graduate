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
	DDX_Control(pDX, IDC_CUSTOM_GRID_INTEREST, interestGrid);
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

	// GridControl
	int m_nRows = 9;
	int m_nCols = 4;
	int m_nFixRows = 1;
	int m_nFixCols = 1;

	interestGrid.SetRowCount(m_nRows);
	interestGrid.SetColumnCount(m_nCols);
	interestGrid.SetFixedRowCount(m_nFixRows);
	interestGrid.SetFixedColumnCount(m_nFixCols);

	DWORD dwTextStyle = DT_RIGHT | DT_VCENTER | DT_SINGLELINE;

	for (int row = 0; row < interestGrid.GetRowCount(); row++) {
		for (int col = 0; col < interestGrid.GetColumnCount(); col++) {
			GV_ITEM Item;
			Item.mask = GVIF_TEXT | GVIF_FORMAT;
			Item.row = row;
			Item.col = col;

			if (row < m_nFixRows) {
				Item.nFormat = DT_LEFT | DT_WORDBREAK;
				Item.strText.Format(_T("Column %d"), col);

			}
			else if (col < m_nFixCols) {
				Item.nFormat = dwTextStyle;
				Item.strText.Format(_T("Row %d"), row);

			}
			else {
				Item.nFormat = dwTextStyle;
				Item.strText.Format(_T("%d"), row * col);
			}
			interestGrid.SetItem(&Item);

			if (rand() % 10 == 1) {
				COLORREF clr = RGB(rand() % 128 + 128,
					rand() % 128 + 128,
					rand() % 128 + 128);
				interestGrid.SetItemBkColour(row, col, clr);
				interestGrid.SetItemFgColour(row, col, RGB(255, 0, 0));
			}
		}
	}


	// autoComplete
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

	//CDialogEx::OnOK();
}
