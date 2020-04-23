#pragma once
#include "pch.h"
//#include "afxdialogex.h"

class CStock
{
	CStock() {}
	~CStock() {}
private:
	long code;				// 종목코드

	double open;			// 시가
	double close;			// 종가
	double high;			// 고가
	double low;				// 저가
	double base;			// 기준가
	double current;			// 현재가
	double volume;			// 거래량
	double marketCap;		// 시가총액
	double marketCapRatio;	// 시가총액비중
	double foreignMaxRatio;	// 외인소진률

	CString stockName;		// 종목명
	CString creditRatio;	// 신용비율
	int numOfStock;			// 상장주식
	double capital;			// 자본금
	double faceValue;		// 액면가
	double sales;			// 매출액
	double operatingIncome;	// 영업이익
	double netIncome;		// 당기순이익
	double outstandingShare;// 유통주식
	double osShareRatio;	// 유통비율

	double eps;				// EPS
	double roe;				// ROE
	double per;				// PER
	double pbr;				// PBR
	double ev;				// EV
	double bps;				// BPS
};

class CCompany {
	CCompany() {}
	~CCompany(){}
private:
	CStock* stock;

};