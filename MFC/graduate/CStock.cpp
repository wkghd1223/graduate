#include "pch.h"
#include "CStock.h"

CStock::CStock(CString name, CString code, CString sectors, CString listingDate, CString settlementMonth)
{
	// 이름
	this->name = name;

	// 코드
	this->code = code;

	// 업종
	sectors.Replace('|', ',');
	this->sectors = sectors;

	// 상장일
	int date[3];
	CString temp;
	int n = 0;
	while (::AfxExtractSubString(temp, listingDate, n++, '-')) {
		date[n-1] = _ttoi(temp.Trim());
	}
	COleDateTime oDate(date[0], date[1], date[2], 0, 0, 0);
	this->listingDate = CChartCtrl::DateToValue(oDate);
	// 결산일
	this->settlementMonth = _ttoi(settlementMonth);
}
