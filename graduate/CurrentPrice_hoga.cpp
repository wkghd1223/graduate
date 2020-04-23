// CurrentPrice_hoga.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CurrentPrice_hoga.h"
#include "afxdialogex.h"


// CurrentPrice_hoga 대화 상자

IMPLEMENT_DYNAMIC(CurrentPrice_hoga, CDialogEx)

CurrentPrice_hoga::CurrentPrice_hoga(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRICE_HOGA, pParent)
{

}

CurrentPrice_hoga::~CurrentPrice_hoga()
{
}

void CurrentPrice_hoga::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CurrentPrice_hoga, CDialogEx)
END_MESSAGE_MAP()


// CurrentPrice_hoga 메시지 처리기
