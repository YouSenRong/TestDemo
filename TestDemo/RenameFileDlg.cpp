// RenameFileDLg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDemo.h"
#include "RenameFileDlg.h"
#include "afxdialogex.h"

#define WM_MSG WM_USER+0x01


// CRenameFileDLg �Ի���

IMPLEMENT_DYNAMIC(CRenameFileDlg, CDialogEx)

CRenameFileDlg::CRenameFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_RENAMEFILE_DIALOG, pParent)
	, m_editStrNewFileName(_T(""))
	, m_editStrPreFileName(_T(""))
{
	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

CRenameFileDlg::~CRenameFileDlg()
{
}

void CRenameFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PREFILENAME, m_editPreFileName);
	DDX_Control(pDX, IDC_EDIT_NEWFILENAME, m_editNewFileName);
	DDX_Text(pDX, IDC_EDIT_NEWFILENAME, m_editStrNewFileName);
	DDX_Text(pDX, IDC_EDIT_PREFILENAME, m_editStrPreFileName);
}


void CRenameFileDlg::Initital(CString strFileName, CString strAddress)
{
	m_editStrPreFileName = strFileName;
	m_editStrNewFileName = strFileName;
	m_strAddress = strAddress;
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CRenameFileDlg, CDialogEx)
END_MESSAGE_MAP()


// CRenameFileDLg ��Ϣ�������


void CRenameFileDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CString strJudge = (CString)"�������ɹ�";
	CString strNewAddress;
	CString strSourceAddress;
	UpdateData(TRUE);
	strSourceAddress = m_strAddress + m_editStrPreFileName; //�ļ�Դ��ַ
	strNewAddress = m_strAddress + m_editStrNewFileName;	//�ļ�Ŀ�ĵ�ַ
	if (MoveFile(strSourceAddress, strNewAddress))
	{
		MessageBox(strJudge);
		GetParent()->SendMessage(WM_MSG, 0, 0);     //����½�������Ϣ��TESTDEMO�Ի���
		//SendMessage(WM_CLOSE);
	}
	else
	{
		strJudge.Format(_T("%d"), GetLastError());
		MessageBox((CString)"������ʧ�ܣ������Ϊ:" + strJudge);
	}
	CDialogEx::OnOK();
}
