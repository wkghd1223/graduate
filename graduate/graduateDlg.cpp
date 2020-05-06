// graduateDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "graduate.h"
#include "graduateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CMainDlg.h"
#include "CInterestDlg.h"
#include <locale.h>


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgraduateDlg 대화 상자



CgraduateDlg::CgraduateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRADUATE_DIALOG, pParent)
{
	m_nScrN0 = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgraduateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL1, theApp.kStock);
	DDX_Control(pDX, IDOK, btnRun);
	DDX_Control(pDX, IDC_INTEREST, btnInterest);
}

BEGIN_MESSAGE_MAP(CgraduateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_MESSAGE(UM_SCRENN_CLOSE, OnScreenClose)
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CgraduateDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_INTEREST, &CgraduateDlg::OnBnClickedInterest)
END_MESSAGE_MAP()


// CgraduateDlg 메시지 처리기

BOOL CgraduateDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	theApp.kStock.CommConnect();
	ReadStocks();

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgraduateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgraduateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CgraduateDlg::OnDestroy()
{
	CString strKey;
	CWnd* pWnd = NULL;
	POSITION pos = m_mapScreen.GetStartPosition();
	while (pos != NULL)
	{
		pWnd = NULL;
		m_mapScreen.GetNextAssoc(pos, strKey, (void*&)pWnd);
		if (pWnd)
		{
			delete pWnd;
			pWnd = NULL;
		}
	}
	m_mapScreen.RemoveAll();
	m_mapScreenNum.RemoveAll();

	// 통신 종료 처리
	theApp.kStock.CommTerminate();
}

LRESULT CgraduateDlg::OnScreenClose(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case 0:
	{
		char* cScrNo = (char*)lParam;
		CString strKey, strScrType;
		strKey.Format(_T("%s"), cScrNo);
		delete cScrNo;

		if (m_mapScreenNum.Lookup(strKey, strScrType))
		{
			m_mapScreenNum.RemoveKey(strKey);
		}

		CWnd* pWnd = NULL;
		if (m_mapScreen.Lookup(strKey, (void*&)pWnd) && pWnd)
		{
			delete pWnd;
			pWnd = NULL;
		}
		m_mapScreen.RemoveKey(strKey);

		if (theApp.kStock.GetSafeHwnd())
		{
			theApp.kStock.DisconnectRealData(strKey);
		}
	}
	break;
	}

	return 0L;
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgraduateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CgraduateDlg::OnBnClickedOk()
{
	if (!GetNextScreenNum(0))
	{
		return;
	}
	//ShowWindow(FALSE);
	CMainDlg* mainDlg = new CMainDlg(this);
	mainDlg->m_strScrNo.Format(_T("%04d"), m_nScrN0);
	m_mapScreen.SetAt(mainDlg->m_strScrNo, mainDlg);

	mainDlg->user = new CUser(theApp.kStock.GetLoginInfo(_T("USER_NAME"))
		, theApp.kStock.GetLoginInfo(_T("ACCNO"))
		, theApp.kStock.GetLoginInfo(_T("USER_ID"))
		, theApp.kStock.GetLoginInfo(_T("GetServerGubun")));

	//dlg.user = new CUser(_T("USER_NAME")
	//	, _T("ACCNO") 
	//	, _T("USER_ID")
	//	, _T("GetServerGubun"));
	mainDlg->Create(IDD_CMainDlg);
	mainDlg->ShowWindow(SW_SHOW);


	//ShowWindow(FALSE);
	//EndDialog(0);
	//CDialogEx::OnOK();
}

BEGIN_EVENTSINK_MAP(CgraduateDlg, CDialogEx)
ON_EVENT(CgraduateDlg, IDC_KHOPENAPICTRL1, 1, CgraduateDlg::OnReceiveTrDataKhopenapictrl1, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
ON_EVENT(CgraduateDlg, IDC_KHOPENAPICTRL1, 5, CgraduateDlg::OnEventConnectKhopenapictrl1, VTS_I4)
END_EVENTSINK_MAP()


void CgraduateDlg::OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (!theApp.kStock.GetSafeHwnd())
	{
		return;
	}
	CString strScrType, strKey = sScrNo;
	if (!m_mapScreenNum.Lookup(strKey, strScrType))
	{
		return;
	}

	CWnd* pWnd = NULL;
	if(m_mapScreen.Lookup(strKey, (void*&)pWnd) && pWnd)
		((CMainDlg*)pWnd)->OnReceiveTrDataKhopenapictrl1(sScrNo, sRQName, sTrCode, sRecordName, sPrevNext, nDataLength, sErrorCode, sMessage, sSplmMsg);

}

//*******************************************************************/
//! Function Name : GetNextScreenNum
//! Function      : 다음 화면 번호 취득
//! Param         : int nScreenType
//! Return        : BOOL
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
BOOL CgraduateDlg::GetNextScreenNum(int nScreenType)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int nRepeat = 0;
	m_nScrN0++;
	if (m_nScrN0 > 9999)
	{
		nRepeat++;
		m_nScrN0 = 1;
	}

	if (nRepeat > 1)
	{
		nRepeat = 0;
		::AfxMessageBox(_T("더 이상 화면을 열수 없습니다.다른 화면을 닫고 실행 해 주세요~!"));
		return FALSE;
	}

	CString strKey, strTemp;
	strKey.Format(_T("%04d"), m_nScrN0);
	if (m_mapScreenNum.Lookup(strKey, strTemp))
	{
		return GetNextScreenNum(nScreenType);
	}

	nRepeat = 0;
	strTemp.Format(_T("%d"), nScreenType);
	m_mapScreenNum.SetAt(strKey, strTemp);
	return TRUE;
}



void CgraduateDlg::OnEventConnectKhopenapictrl1(long nErrCode)
{
	btnRun.EnableWindow(TRUE);
	// TODO: Add your message handler code here
}


void CgraduateDlg::OnBnClickedInterest()
{
	if (!GetNextScreenNum(1))
	{
		return;
	}
	//ShowWindow(FALSE);
	CInterestDlg* interestDlg = new CInterestDlg(this);
	interestDlg->m_strScrNo.Format(_T("%04d"), m_nScrN0);
	m_mapScreen.SetAt(interestDlg->m_strScrNo, interestDlg);

	interestDlg->user = new CUser(theApp.kStock.GetLoginInfo(_T("USER_NAME"))
		, theApp.kStock.GetLoginInfo(_T("ACCNO"))
		, theApp.kStock.GetLoginInfo(_T("USER_ID"))
		, theApp.kStock.GetLoginInfo(_T("GetServerGubun")));

	//dlg.user = new CUser(_T("USER_NAME")
	//	, _T("ACCNO") 
	//	, _T("USER_ID")
	//	, _T("GetServerGubun"));
	interestDlg->Create(IDD_CInterestDlg);
	interestDlg->ShowWindow(SW_SHOW);


	//ShowWindow(FALSE);
	//EndDialog(0);
	//CDialogEx::OnOK();
	// TODO: Add your control notification handler code here
}
void CgraduateDlg::ReadStocks()
{
	CString str;
	CString filepath = _T("");
	filepath.Format(L"C:\\Users\\pumkinjeon\\Desktop\\Pumpkin\\workspace\\graduate\\stock_list.csv");
	setlocale(LC_ALL, "korean");
	CStdioFile file(filepath, CFile::modeRead | CFile::typeText);

	while (1) {
		if (!file.ReadString(str))
			break;
		CString temp;
		CString tok[2];
		int n = 0;
		while (::AfxExtractSubString(temp, str, n, ',')) {
			stockData.push_back(std::wstring(temp));
			tok[n % 2] = temp;
			n++;
		}
		hashStock.insert({ tok[1], tok[0] });
		//hashStock[tok[1]] = tok[0];
		//hashStock.insert(std::pair<CString,CString>((LPCTSTR)tok[1], tok[0]));
	}
	 CString aa = hashStock[L"삼성전자"];
}
