#pragma once
#include "afxwin.h"


// CNewFolderDlg �Ի���

class CNewFolderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNewFolderDlg)

public:
	CNewFolderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewFolderDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWFOLDER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ·���༭��Ŀ��Ʊ���
	CEdit m_editFolderPath;
	// ·���༭��·������
	CString m_editStrFolderPath;
	// �ļ������༭����Ʊ���
	CEdit m_editFolderName;
	// �ļ�������������
	CString m_editStrFolderName;

public:
	void Initial(CString strDirPath);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
