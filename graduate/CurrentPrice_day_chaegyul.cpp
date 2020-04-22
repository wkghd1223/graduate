// CurrentPrice_day_chaegyul.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CurrentPrice_day_chaegyul.h"
#include "afxdialogex.h"


// CurrentPrice_day_chaegyul 대화 상자

IMPLEMENT_DYNAMIC(CurrentPrice_day_chaegyul, CDialogEx)

CurrentPrice_day_chaegyul::CurrentPrice_day_chaegyul(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRICE_D_CHAEGYUL, pParent)
{

}

CurrentPrice_day_chaegyul::~CurrentPrice_day_chaegyul()
{
}

void CurrentPrice_day_chaegyul::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CurrentPrice_day_chaegyul, CDialogEx)
END_MESSAGE_MAP()


// CurrentPrice_day_chaegyul 메시지 처리기
