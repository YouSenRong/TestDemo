// NewFolderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDemo.h"
#include "NewFolderDlg.h"
#include "afxdialogex.h"

#define WM_MSG WM_USER+0x01

// CNewFolderDlg �Ի���

IMPLEMENT_DYNAMIC(CNewFolderDlg, CDialogEx)

CNewFolderDlg::CNewFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEWFOLDER_DIALOG, pParent)
	, m_editStrFolderPath(_T(""))
	, m_editStrFolderName(_T(""))
{

}

CNewFolderDlg::~CNewFolderDlg()
{
}

void CNewFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NEWFOLDER_PATH, m_editFolderPath);
	DDX_Text(pDX, IDC_EDIT_NEWFOLDER_PATH, m_editStrFolderPath);
	DDV_MaxChars(pDX, m_editStrFolderPath, 100);
	DDX_Control(pDX, IDC_EDIT_NEWFOLDER_FOLDERNAME, m_editFolderName);
	DDX_Text(pDX, IDC_EDIT_NEWFOLDER_FOLDERNAME, m_editStrFolderName);
	DDV_MaxChars(pDX, m_editStrFolderName, 100);
}


void CNewFolderDlg::Initial(CString strDirPath)
{
	m_editStrFolderPath = strDirPath;
	UpdateData(FALSE);
}

BEGIN_MESSAGE_MAP(CNewFolderDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewFolderDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewFolderDlg ��Ϣ�������


BOOL CNewFolderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_editFolderName.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CNewFolderDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_editFolderPath.GetWindowText(m_editStrFolderPath);
	m_editFolderName.GetWindowText(m_editStrFolderName);
	if (m_editStrFolderName.IsEmpty())
	{
		MessageBox(_T("�½�ʧ�ܣ��������ļ�������"), NULL, MB_ICONERROR);
		return;
	}
	m_editStrFolderPath = m_editStrFolderPath + "\\" + m_editStrFolderName;	//�����ĵ�ַ������·�����ļ�����
	if (CreateDirectory(m_editStrFolderPath, NULL))
	{
		MessageBox(_T("�½��ɹ�"));
	}
	GetParent()->SendMessage(WM_MSG, 0, 0);		//����½�������Ϣ��TESTDEMO�Ի���
	CDialogEx::OnOK();
}
