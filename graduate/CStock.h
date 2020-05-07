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
	CString name;	// 주식 이름
	CString code;	// 종목코드
	std::vector<CString> sectors; // 업종
	double listingDate; // 상장일
	int settlementMonth;	// 결산일
	//CChartCandlestickSerie* price;	// 날짜별 가격
public: 
	CString GetStockName() { return name; }
	CString GetStockCode() { return code; }
	std::vector<CString> GetSectors() { return sectors; }
};
