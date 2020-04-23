#pragma once
#include "pch.h"
//#include "afxdialogex.h"

class CStock
{
	CStock() {}
	~CStock() {}
private:
	long code;				// �����ڵ�

	double open;			// �ð�
	double close;			// ����
	double high;			// ��
	double low;				// ����
	double base;			// ���ذ�
	double current;			// ���簡
	double volume;			// �ŷ���
	double marketCap;		// �ð��Ѿ�
	double marketCapRatio;	// �ð��Ѿ׺���
	double foreignMaxRatio;	// ���μ�����

	CString stockName;		// �����
	CString creditRatio;	// �ſ����
	int numOfStock;			// �����ֽ�
	double capital;			// �ں���
	double faceValue;		// �׸鰡
	double sales;			// �����
	double operatingIncome;	// ��������
	double netIncome;		// ��������
	double outstandingShare;// �����ֽ�
	double osShareRatio;	// �������

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