// CMainDlg.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#include "graduateDlg.h"


// CMainDlg 대화 상자

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CMainDlg, pParent)
{
	m_pParent = pParent;
	m_strScrNo = "7777";
	m_strJongCode = "";
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXT_USER, userInfo);
	DDX_Control(pDX, IDC_TEXT_STATIC, userInfoFormat);
	DDX_Control(pDX, IDC_EDIT_SEARCH, editSearch);
	DDX_Control(pDX, IDC_TEXT_STOCK_INFO, stockInfo);
}
//BEGIN_EVENTSINK_MAP(CMainDlg, CDialogEx)
//ON_EVENT(CMainDlg, IDC_KHOPENAPICTRL1, 1, CMainDlg::OnReceiveTrDataKhopenapictrl1, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR)
//END_EVENTSINK_MAP()
void CMainDlg::OnReceiveTrDataKhopenapictrl1(LPCTSTR sScrNo, LPCTSTR sRQName, LPCTSTR sTrCode, LPCTSTR sRecordName, LPCTSTR sPrevNext, long nDataLength, LPCTSTR sErrorCode, LPCTSTR sMessage, LPCTSTR sSplmMsg)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	userInfo.SetWindowTextW(_T("asdf"));
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
	//CDialogEx::OnOK();
}
