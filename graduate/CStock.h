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
	CString name;	// �ֽ� �̸�
	CString code;	// �����ڵ�
	std::vector<CString> sectors; // ����
	double listingDate; // ������
	int settlementMonth;	// �����
	//CChartCandlestickSerie* price;	// ��¥�� ����
public: 
	CString GetStockName() { return name; }
	CString GetStockCode() { return code; }
	std::vector<CString> GetSectors() { return sectors; }
};
