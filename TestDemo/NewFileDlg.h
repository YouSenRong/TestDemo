#pragma once
#include "afxwin.h"


// NewFileDlg �Ի���

class NewFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NewFileDlg)

public:
	NewFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	NewFileDlg(CString strAddress, CWnd* pParent = NULL);
	//�Զ��庯������ʼ������
	void Initital();
	//�Զ��庯������ʼ������
	void Initital(CString strAddress);
	virtual ~NewFileDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWFILE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CEdit m_Edit_NewFile_Path;                      //��һ���ı��򣬼�Ϊ�½��ļ��ĵ�ַ
	CEdit m_Edit_NewFile_FileName;                  //�ڶ����ı��򣬼�Ϊ�½��ļ������֣�Ҫ�����׺
	CString m_strAddressPath;							//�ļ�·��
	CString m_strFileName;							//�ļ���
	afx_msg void OnBnClickedNewFileNew();			//"�½�"��ť
	afx_msg void OnBnClickedNewFileCancle();		//"ȡ��"��ť
	afx_msg void OnEnChangeEditNewfilePath();
	virtual void OnOK();
};
