#pragma once
#include "afxwin.h"


// CMoveFileDlg �Ի���

class CMoveFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMoveFileDlg)

public:
	CMoveFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CMoveFileDlg::CMoveFileDlg(CString SourcePath, CString FileName, CWnd* pParent = NULL );
	BOOL CMoveFileDlg::Ininatial(CString SourcePath, CString FileName);
	virtual ~CMoveFileDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOVEFILE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �ļ��ƶ�Ŀ��·���ؼ�
	CEdit m_editMoveFileDesPath;
	// �ļ��ƶ�Ŀ��·���ַ���
	CString m_editStrMoveFileDesPath;
	// �ļ��ƶ����ļ���
	CString m_StrMoveFileName;
	// �ļ��ƶ�����Դ·��
	CString m_StrMoveFileSourcePath;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
