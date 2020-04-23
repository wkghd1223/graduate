// CurrentPrice_chaegyul.cpp: 구현 파일
//

#include "pch.h"
#include "graduate.h"
#include "CurrentPrice_chaegyul.h"
#include "afxdialogex.h"


// CurrentPrice_chaegyul 대화 상자

IMPLEMENT_DYNAMIC(CurrentPrice_chaegyul, CDialogEx)

CurrentPrice_chaegyul::CurrentPrice_chaegyul(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRICE_CHAEGYUL, pParent)
{

}

CurrentPrice_chaegyul::~CurrentPrice_chaegyul()
{
}

void CurrentPrice_chaegyul::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CurrentPrice_chaegyul, CDialogEx)
END_MESSAGE_MAP()


// CurrentPrice_chaegyul 메시지 처리기
