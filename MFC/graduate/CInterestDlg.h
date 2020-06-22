#pragma once
#include "CUser.h"
#include "AutoComplete/PGEnumString.h"
#include "GridCtrl/GridCtrl.h"
#include "CStock.h"
// CInterestDlg dialog
typedef struct SectorVector {
	CString sector;
	std::vector<CString> stockNames;
};
class CInterestDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInterestDlg)

public:
	CInterestDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CInterestDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CInterestDlg };
#endif
private:
	CPGEnumString* m_pEum;
	CComPtr<IAutoComplete> m_pac;
protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString		m_strScrNo;
	CWnd*		m_pParent;
	CString		m_strJongCode;

	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

	// ���������� �����´�.
	CStatic userInfo;
	CStatic userInfoFormat;
	void initUserInfo();
	
	// �˻� â
	CEdit editSearch;
	// �˻����� ������ ������
	CString search;

	// �˻���ư
	afx_msg void OnBnClickedOk();

	// ���������� �����ϴ� �׸���
	CGridCtrl interestGrid;
	// �׸��� ��Ʈ���� �ʱ�ȭ�Ѵ�.
	void initGrid(int nRow, int nCol);
	std::vector<SectorVector> sv;

	// �˻������� �����ϴ� ����Ʈ
	CListCtrl interestList;
	// ����Ʈ���� ���õ� �������� �ε����� ����
	int selectedNum = -1;
	// ����Ʈ ��Ʈ�Ѹ� �ʱ�ȭ�Ѵ�.
	void initList();
	// ����Ʈ ��Ʈ���� ���� �ο��Ѵ�.
	void setList(CStock st);

	// �˻��� ����� ��ġ�ϴ� �ֽĵ��� �����ϴ� ����
	std::vector<CStock> searchedStock;
	HBITMAP m_hBitmap;
	BITMAP m_bitmap;
	void initimageButton();
	CBitmapButton btnPlus;
	afx_msg void OnNMClickListInterestSearch(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonPlus();
	
};
