#include "pch.h"
#include "CStock.h"

CStock::CStock(CString name, CString code, CString sectors, CString listingDate, CString settlementMonth)
{
	// �̸�
	this->name = name;

	// �ڵ�
	this->code = code;

	// ����
	sectors.Replace('|', ',');
	this->sectors = sectors;

	// ������
	int date[3];
	CString temp;
	int n = 0;
	while (::AfxExtractSubString(temp, listingDate, n++, '-')) {
		date[n-1] = _ttoi(temp.Trim());
	}
	COleDateTime oDate(date[0], date[1], date[2], 0, 0, 0);
	this->listingDate = CChartCtrl::DateToValue(oDate);
	// �����
	this->settlementMonth = _ttoi(settlementMonth);
}
