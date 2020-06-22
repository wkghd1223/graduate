
// graduate.h: PROJECT_NAME 애플리케이션에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "khopenapictrl1.h"
#include "GridCtrl\GridCtrl.h"


// CgraduateApp:
// 이 클래스의 구현에 대해서는 graduate.cpp을(를) 참조하세요.
//
#define NUM_DOUBLE 18
#define DT_NONE			0		// 기본문자 형식
#define DT_DATE			1		// 일자 형식
#define DT_TIME			2		// 시간 형식
#define DT_NUMBER		3		// 콤파 숫자 형식
#define DT_ZERO_NUMBER	4		// 콤파 숫자(0표시) 형식
#define DT_SIGN			5		// 대비기호 형식
typedef struct
{
	CString	strKey;				// 조회 키
	CString	strRealKey;			// 리얼 키
	int		nRow;				// 그리드 행
	int		nCol;				// 그리드 열
	int		nDataType;			// 데이타 타입(0:기본문자, 1:일자, 2:시간, 3:콤파 숫자, 4:콤파 숫자(0표시), 5:대비기호)
	BOOL		bTextColor;			// 문자열 색 변경(상승, 하락색)
	UINT		nAlign;				// 문자열 정렬(DT_LEFT, DT_CENTER, DT_RIGHT)
	CString	strBeforeData;		// 문자열 앞 문자 넣기
	CString	strAfterData;		// 문자열 뒤 문자 넣기
} stGRID;

class CgraduateApp : public CWinApp
{
public:
	CgraduateApp();
	CKhopenapictrl1 kStock;	// 키움증권 클래스 객체선언

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	void SetSignData(CGridCtrl* pGrid, int nRow, int nCol, LPCTSTR szData);
	void SetDataFgColour(CGridCtrl* pGrid, int nRow, int nCol, LPCTSTR szData);
	CString ConvDataFormat(int nType, LPCTSTR szData, LPCTSTR szBeforeData/* = ""*/, LPCTSTR szAfterData/* = ""*/);

// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CgraduateApp theApp;
