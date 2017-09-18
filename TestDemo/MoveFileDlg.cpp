// MoveFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDemo.h"
#include "MoveFileDlg.h"
#include "afxdialogex.h"
#define WM_MSG WM_USER+1

// CMoveFileDlg �Ի���

IMPLEMENT_DYNAMIC(CMoveFileDlg, CDialogEx)

CMoveFileDlg::CMoveFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MOVEFILE_DIALOG, pParent)
	, m_editStrMoveFileDesPath(_T(""))
{

}

CMoveFileDlg::CMoveFileDlg( CString SourcePath, CString FileName, CWnd* pParent /*=NULL*/ )
	: CDialogEx(IDD_MOVEFILE_DIALOG, pParent)
	, m_editStrMoveFileDesPath(_T(""))
{
	m_StrMoveFileSourcePath = SourcePath;
	m_StrMoveFileName = FileName;
}

BOOL CMoveFileDlg::Ininatial(CString strSourcePath, CString strFileName)
{
	m_StrMoveFileSourcePath = strSourcePath;
	m_editStrMoveFileDesPath = strSourcePath;
	m_StrMoveFileName = strFileName;
	UpdateData(FALSE);
	return TRUE;
}

BOOL CMoveFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_editMoveFileDesPath.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

CMoveFileDlg::~CMoveFileDlg()
{
}

void CMoveFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MOVEFILEPATH, m_editMoveFileDesPath);
	DDX_Text(pDX, IDC_EDIT_MOVEFILEPATH, m_editStrMoveFileDesPath);
}


BEGIN_MESSAGE_MAP(CMoveFileDlg, CDialogEx)
END_MESSAGE_MAP()


// CMoveFileDlg ��Ϣ�������


void CMoveFileDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	CString strJudge;
	m_editMoveFileDesPath.GetWindowText(m_editStrMoveFileDesPath);
	if (m_editStrMoveFileDesPath.Right(1) != _T("\\"))
	{
		m_editStrMoveFileDesPath += _T("\\");
	}
	m_editStrMoveFileDesPath = m_editStrMoveFileDesPath + m_StrMoveFileName;   //Ҫ�ƶ�����Ŀ�ĵ�ַ
	if (MoveFile(m_StrMoveFileSourcePath, m_editStrMoveFileDesPath/*, MOVEFILE_COPY_ALLOWED*/))             //�����������滻
	{
		strJudge = (CString)"�ļ��ƶ��ɹ�!";
		MessageBox(strJudge);
		GetParent()->SendMessage(WM_MSG, 0, 0);     //����½�������Ϣ��TESTDEMO�Ի���
	}
	else
	{
		strJudge.Format(_T("%d"), GetLastError());
		MessageBox((CString)"�ƶ�ʧ�ܣ������Ϊ:" + strJudge, NULL, MB_ICONERROR);
	}
	CDialogEx::OnOK();
}
