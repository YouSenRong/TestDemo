#pragma once
#include "afxwin.h"


// CRenameFileDLg �Ի���

class CRenameFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRenameFileDlg)

public:
	CRenameFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRenameFileDlg();
	void Initital(CString strFilename, CString strAddress);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RENAMEFILE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// ԭ�ļ����༭��ؼ�
	CEdit m_editPreFileName;
	// ���ļ����༭��ؼ�
	CEdit m_editNewFileName;
	// ���ļ���
	CString m_editStrNewFileName;
	// ԭ�ļ���
	CString m_editStrPreFileName;
	// �ļ�·��
	CString m_strAddress;
	virtual void OnOK();
};
