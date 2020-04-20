﻿// CMainDlg.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#include "graduateDlg.h"

#include "CDayChartDlg.h"
#include "CWeekChartDlg.h"
#include "CMonthChartDlg.h"
// CMainDlg 대화 상자

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMainDlg, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "7777";
	m_strJongCode = "";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//pwndShow = NULL;
}

CMainDlg::~CMainDlg()
{
}
BOOL CMainDlg::OnInitDialog() {
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

	CString tabName[3] = { _T("일"), _T("주"),_T("월") };
	for (int i = 0; i < (sizeof(tabName) / sizeof(*tabName));i++) {
		candleChart.InsertItem(i , tabName[i]);
	}
	candleChart.SetCurSel(0);
	CRect Rect;
	candleChart.GetWindowRect(&Rect);
	//candleChart.GetClientRect(&Rect);
	
	cDayChart = new CDayChartDlg;
	cWeekChart = new CWeekChartDlg;
	cMonthChart = new CMonthChartDlg;


	cDayChart->Create(IDD_DIALOG_DAY_CHART, &candleChart);
	cDayChart->MoveWindow(0, 25, Rect.Width(), Rect.Height());
	//pwndShow = cDayChart;
	cDayChart->ShowWindow(SW_SHOW);

	cWeekChart->Create(IDD_DIALOG_WEEK_CHART, &candleChart);
	cWeekChart->MoveWindow(0, 25, Rect.Width(), Rect.Height());
	cWeekChart->ShowWindow(SW_HIDE);

	cMonthChart->Create(IDD_DIALOG_MONTH_CHART, &candleChart);
	cMonthChart->MoveWindow(0, 25, Rect.Width(), Rect.Height());
	cMonthChart->ShowWindow(SW_HIDE);

	
	return TRUE;
}

//*******************************************************************/
//! Function Name : OnClose
//! Function      : 파괴자
//! Param         : void
//! Return        : void
//! Create        : , 2014/06/02
//! Comment       : 
//******************************************************************/
void CMainDlg::OnClose()
{
	// 화면 닫을 때 부모윈도우에게 통보(화면 관리 위해)
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
void CMainDlg::OnPaint()
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
void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_USER, userInfo);
	DDX_Control(pDX, IDC_TEXT_STATIC, userInfoFormat);
	DDX_Control(pDX, IDC_EDIT_SEARCH, editSearch);
	DDX_Control(pDX, IDC_TEXT_STOCK_INFO, stockInfo);
	DDX_Control(pDX, IDC_TAB_CANDLE_CHART, candleChart);
}
//BEGIN_EVENTSINK_MAP(CMainDlg, CDialogEx)
//ON_EVENT(CMainDlg, IDC_KHOPENAPICTRL1, 1, CMainDlg::OnReceiveTrDataKhopenapictrl1, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
//END_EVENTSINK_MAP()
void CMainDlg::OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	//userInfo.SetWindowTextW(_T("asdf"));
	CString out = sRQName;
	CString str = _T("");
	if (out == _T("주식기본정보")) {
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("종목명"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("시가총액"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("현재가"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("거래량"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("PER"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("PBR"));
		out.Trim();
		str += out;
		str += _T("\n");
		out = theApp.kStock.GetCommData(sTrCode, sRQName, 0, _T("ROE"));
		out.Trim();
		stockInfo.SetWindowTextW(str);
	}
}
BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_SEARCH, &CMainDlg::OnEnChangeEditSearch)
	ON_BN_CLICKED(IDOK, &CMainDlg::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CANDLE_CHART, &CMainDlg::OnTcnSelchangeTabCandleChart)
	ON_BN_CLICKED(IDCANCEL, &CMainDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


void CMainDlg::OnEnChangeEditSearch()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMainDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString code = _T("");

	editSearch.GetWindowText(code);

	theApp.kStock.SetInputValue(_T("종목코드"), code);
	theApp.kStock.CommRqData(_T("주식기본정보"), _T("OPT10001"), 0, m_strScrNo);
	int pos = candleChart.GetCurSel();
	switch (pos)
	{
	case 0:
		cDayChart->ShowGraph(code);
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
	//CDialogEx::OnOK();
}


void CMainDlg::OnTcnSelchangeTabCandleChart(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//if (pwndShow != NULL) {
	//	pwndShow->ShowWindow(SW_HIDE);
	//	pwndShow = NULL;
	//}
	int pos = candleChart.GetCurSel();
	switch (pos)
	{
	case 0:
		cDayChart->ShowWindow(SW_SHOW);
		cWeekChart->ShowWindow(SW_HIDE);
		cMonthChart->ShowWindow(SW_HIDE);

		//pwndShow = cDayChart;
		break;
	case 1:
		cWeekChart->ShowWindow(SW_SHOW);
		cDayChart->ShowWindow(SW_HIDE);
		cMonthChart->ShowWindow(SW_HIDE);

		//pwndShow = cWeekChart;
		break;
	case 2:
		cMonthChart->ShowWindow(SW_SHOW);
		cWeekChart->ShowWindow(SW_HIDE);
		cDayChart->ShowWindow(SW_HIDE);
		//pwndShow = cMonthChart;
		break;
	default:
		break;
	}
	*pResult = 0;
}


void CMainDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}
