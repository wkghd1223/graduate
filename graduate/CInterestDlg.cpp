// CInterestDlg.cpp : implementation file
//

#include "pch.h"
#include "graduate.h"
#include "CInterestDlg.h"
#include "afxdialogex.h"
#include "graduateDlg.h"


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

		std::vector<std::wstring> temp = ReadStocks();
		//temp.push_back(std::wstring(L"000020"));
		//temp.push_back(std::wstring(L"005930"));
		//temp.push_back(std::wstring(L"삼성전자"));
		//temp.push_back(std::wstring(L"000040"));

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
std::vector<std::wstring>  CInterestDlg::ReadStocks() {
	std::vector<std::wstring> temp;

	FILE* fp = NULL;
	CString filepath = _T("");
	filepath.Format(L"C:\\Users\\pumkinjeon\\Desktop\\Pumpkin\\workspace\\graduate\\stock_list.csv");
	fopen_s(&fp, (CStringA)filepath, "r");
	if (fp) {
		char buf[2048] = { 0, };
		memset(buf, NULL, 2048);
		while (fgets(buf, 2048, fp)) {
			CString strContent;
			strContent.Format(L"%s", buf);
			memset(buf, NULL, 2048);
			if (strContent.Find(L"#") >= 0) {
				continue;
			}
			strContent.Remove('\r');
			strContent.Remove('\n');


			CString rString;
			int nSubString = 0;
			while (::AfxExtractSubString(rString, strContent, nSubString++, ',')) {
				switch (nSubString) {
				case 1: // 종목 명
					temp.push_back(std::wstring(rString));
				case 2: // 종목 코드
					temp.push_back(std::wstring(rString));
				default:
					break;
				}
			}
		}
	}
	

	return temp;
}