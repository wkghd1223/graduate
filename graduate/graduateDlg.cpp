﻿// graduateDlg.cpp: 구현 파일
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
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CgraduateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_KHOPENAPICTRL1, theApp.kStock);
	DDX_Control(pDX, IDC_STOCK_LIST, stockList);
}

BEGIN_MESSAGE_MAP(CgraduateDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CgraduateDlg::OnBnClickedButtonRun)
	ON_BN_CLICKED(IDC_BUTTON1, &CgraduateDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SEND, &CgraduateDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CgraduateDlg 메시지 처리기

BOOL CgraduateDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgraduateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgraduateDlg::OnBnClickedButtonRun()
{
	ShowWindow(FALSE);
	CMainDlg dlg;
	//dlg.user = new User(theApp.kStock.GetLoginInfo(_T("USER_NAME"))
	//	, theApp.kStock.GetLoginInfo(_T("ACCNO")) 
	//	, theApp.kStock.GetLoginInfo(_T("USER_ID"))
	//	, theApp.kStock.GetLoginInfo(_T("GetServerGubun")));
	
	dlg.user = new CUser(_T("USER_NAME")
		, _T("ACCNO") 
		, _T("USER_ID")
		, _T("GetServerGubun"));

	dlg.DoModal();
	EndDialog(0);
}

void CgraduateDlg::OnBnClickedButton1()
{
	//int loginFlag;
	//loginFlag = theApp.kStock.CommConnect();
	//if (loginFlag == 0)
	//	::AfxMessageBox(_T("log in"));
	//else
	//	::AfxMessageBox(_T("log in fail"));
	GetDlgItem(IDC_BUTTON_RUN)->EnableWindow(TRUE);
}
BEGIN_EVENTSINK_MAP(CgraduateDlg, CDialogEx)
ON_EVENT(CgraduateDlg, IDC_KHOPENAPICTRL1, 1, CgraduateDlg::OnReceiveTrDataKhopenapictrl1, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
END_EVENTSINK_MAP()


void CgraduateDlg::OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CString out = sRQName;

	if (out == _T("주식기본정보")) {
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("종목명"));
		out.Trim();
		stockList.AddString(_T("종목명") + out);
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("시가총액"));
		out.Trim();
		stockList.AddString(_T("시가총액\t") + out);
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("현재가"));
		out.Trim();
		stockList.AddString(_T("현재가\t") + out);
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("거래량"));
		out.Trim();
		stockList.AddString(_T("거래량\t") + out);
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("PER"));
		out.Trim();
		stockList.AddString(_T("PER\t") + out);
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("PBR"));
		out.Trim();
		stockList.AddString(_T("PBR\t") + out);
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("ROE"));
		out.Trim();
		stockList.AddString(_T("ROE\t") + out);
	}
}


void CgraduateDlg::OnBnClickedSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	theApp.kStock.SetInputValue(_T("종목코드"), _T("005930"));
	theApp.kStock.CommRqData(_T("주식기본정보"), _T("OPT10001"), 0, _T("0101"));
}