#pragma once
#include "pch.h"
#include "afxdialogex.h"
#include <vector>
#include <string>
#include "ChartCtrl_source/ChartCandlestickSerie.h"

class CStock
{
public:
	CStock() {}
	CStock(CString name, CString code, CString sectors, CString listingDate, CString settlementMonth);
	~CStock() {}
private:
	// 주식 이름
	CString name;	
	// 종목코드
	CString code;	
	// 업종
	CString sectors; 
	// 상장일
	double listingDate; 
	// 결산일
	int settlementMonth;	
	// 날짜별 가격
	//CChartCandlestickSerie* price;	
public: 
	CString GetStockName() { return name; }
	CString GetStockCode() { return code; }
	CString GetSectors() { return sectors; }
};
