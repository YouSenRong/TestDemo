#pragma once
#include "afxcmn.h"
#include <tlhelp32.h>


// CProcessManager �Ի���

class CProcessManager : public CDialogEx
{
	DECLARE_DYNAMIC(CProcessManager)

public:
	CProcessManager(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProcessManager();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROCESSMANAGER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL GetProcessList();

protected:
	
	BOOL ListProcessModules(DWORD dwPID);
	BOOL ListProcessThreads(DWORD dwOwnerPID);
	void printError(TCHAR* msg);
public:
	virtual BOOL OnInitDialog();
	void Initial();

	// �����б�ؼ����Ʊ���
	CListCtrl m_listctrlProcess;
	afx_msg void OnBnClickedProcessmanagerRefreshBtn();
	afx_msg void OnBnClickedProcessmanagerTerminateBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
