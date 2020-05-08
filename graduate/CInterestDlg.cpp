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
	DDX_Control(pDX, IDC_LIST_INTEREST_SEARCH, interestList);
	DDX_Control(pDX, IDC_BUTTON_PLUS, btnPlus);
}


BEGIN_MESSAGE_MAP(CInterestDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CInterestDlg::OnBnClickedOk)
//	ON_WM_PAINT()
ON_NOTIFY(NM_CLICK, IDC_LIST_INTEREST_SEARCH, &CInterestDlg::OnNMClickListInterestSearch)
ON_BN_CLICKED(IDC_BUTTON_PLUS, &CInterestDlg::OnBnClickedButtonPlus)
END_MESSAGE_MAP()


// CInterestDlg message handlers

BOOL CInterestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// plus button
	initimageButton();
	btnPlus.LoadBitmaps(IDB_BITMAP_PLUS, IDB_BITMAP_PLUS_ON);
	btnPlus.SizeToContent();

	// userInfo
	initUserInfo();

	// GridControl
	initGrid(2, 0);

	// listControl
	initList();

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
	searchedStock.clear();
	interestList.DeleteAllItems();

	editSearch.GetWindowText(search);
	search = search.Trim();
	std::vector<CStock> v;
	CgraduateDlg* parent = (CgraduateDlg*)m_pParent;
	v = parent->GetStockList();
	for (auto i : v) {
		CString tempName = i.GetStockName();
		CString tempCode = i.GetStockCode();
		CString tempSector = i.GetSectors();
		if (tempName.Find(search) >= 0 || tempCode.Find(search) >= 0 || tempSector.Find(search) >= 0) {
			searchedStock.push_back(i);
		}
	}


	for (auto i : searchedStock) {
		setList(i);
	}
	//CDialogEx::OnOK();
}

void CInterestDlg::initUserInfo()
{
	userInfoFormat.SetWindowTextW(_T("사용자\n 사용자 계정\n 사용자 ID"));
	CgraduateDlg* parent = (CgraduateDlg*)m_pParent;
	CUser user = parent->GetUser();
	CString str = _T("");
	str += user.getName();
	str += _T("\n");
	str += user.getAccount();
	str += _T("\n");
	str += user.getUserId();
	str += _T("\n");
	userInfo.SetWindowTextW(str);
}

void CInterestDlg::initList()
{
	CRect rect;
	interestList.GetWindowRect(&rect);
	interestList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	interestList.InsertColumn(0, L"종목코드", LVCFMT_CENTER, rect.Width() * 0.25);
	interestList.InsertColumn(1, L"종목명", LVCFMT_CENTER, rect.Width() * 0.35);
	interestList.InsertColumn(2, L"업종", LVCFMT_CENTER, rect.Width() * 0.4);
}

void CInterestDlg::setList(CStock st)
{
	int n = interestList.GetItemCount();
	interestList.InsertItem(n, st.GetStockCode());
	interestList.SetItem(n, 1, LVIF_TEXT, st.GetStockName(), NULL, NULL, NULL, NULL);
	interestList.SetItem(n, 2, LVIF_TEXT, st.GetSectors(), NULL, NULL, NULL, NULL);

}

void CInterestDlg::initimageButton()
{
	m_hBitmap = LoadBitmap(::AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_BITMAP_PLUS));
	GetObject(m_hBitmap, sizeof(BITMAP), &m_bitmap);
}

void CInterestDlg::initGrid(int nRow, int nCol)
{
	int m_nRows = nRow;
	int m_nCols = nCol;
	// 고정 행
	int m_nFixRows = 1;
	int m_nFixCols = 0;
	
	interestGrid.AutoSize();

	interestGrid.SetEditable(FALSE);
	interestGrid.SetListMode(TRUE);
	interestGrid.EnableDragAndDrop(TRUE);

	interestGrid.SetRowCount(m_nRows);
	interestGrid.SetColumnCount(m_nCols);
	interestGrid.SetFixedRowCount(m_nFixRows);
	interestGrid.SetFixedColumnCount(m_nFixCols);
	
	DWORD dwTextStyle = DT_RIGHT | DT_VCENTER | DT_SINGLELINE;

}

void CInterestDlg::OnNMClickListInterestSearch(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	selectedNum = pNMListView->iItem;//

	//int idx = pNMListView -> iItem;// 선택된 아이템값의 아이템을 (0,1 ... n 번째 인덱스) 한개 가져온다.
	//CString sIndexValue;sIndexValue = m_listDataTable.GetItemText(idx, 1);

	*pResult = 0;
}


void CInterestDlg::OnBnClickedButtonPlus()
{
	if (selectedNum < 0) {
		return;
	}
	CString TempCode = interestList.GetItemText(selectedNum, 0);
	CString TempName = interestList.GetItemText(selectedNum, 1);
	CString TempSector = interestList.GetItemText(selectedNum, 2);
	TempCode.Append(L" | ");
	TempCode.Append(TempName);

	int col = -1;
	int row = -1;
	int j=0;
	for (auto i : sv) {
		if (!i.sector.Compare(TempSector)) {
			col = j;
		}
		if (i.stockNames.size() < row) {
			row = i.stockNames.size();
		}
		j++;
	}

	if (col < 0) {
		SectorVector item;
		item.sector = TempSector;
		item.stockNames.push_back(TempCode);
		sv.push_back(item);

		interestGrid.SetColumnCount(sv.size());
		interestGrid.SetItemText(0, sv.size()-1, TempSector);
		interestGrid.SetItemBkColour(0, sv.size() - 1, RGB(255,255,153, 0.7));
		interestGrid.SetItemText(1, sv.size()-1, TempCode);
	}
	else {
		sv[col].stockNames;
		std::vector<CString>::iterator nit = std::find(sv[col].stockNames.begin(), sv[col].stockNames.end(), TempCode);
		if (nit == sv[col].stockNames.end()) {
			sv[col].stockNames.push_back(TempCode);
			if(sv[col].stockNames.size() > row)
				interestGrid.SetRowCount(sv[col].stockNames.size() + 1);
			interestGrid.SetItemText(sv[col].stockNames.size(), col, TempCode);
		}
	}
	
	interestGrid.AutoSize();
}
