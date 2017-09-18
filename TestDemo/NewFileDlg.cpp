// NewFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDemo.h"
#include "NewFileDlg.h"
#include "TestDemoDlg.h"
#include "afxdialogex.h"


// NewFileDlg �Ի���

IMPLEMENT_DYNAMIC(NewFileDlg, CDialogEx)

NewFileDlg::NewFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NEWFILE_DIALOG, pParent)
{
	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	
}

NewFileDlg::NewFileDlg(CString strAddress, CWnd* pParent /*= NULL*/)
	: CDialogEx(IDD_NEWFILE_DIALOG, pParent)
{
	this->m_strAddressPath = strAddress;
	::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

NewFileDlg::~NewFileDlg()
{
}

void NewFileDlg::Initital()                    //��ʼ������
{
	m_Edit_NewFile_Path.SetWindowTextW(m_strAddressPath);
	m_Edit_NewFile_FileName.SetFocus();
}

void NewFileDlg::Initital(CString strAddress)                    //��ʼ������
{
	this->m_strAddressPath = strAddress;
	m_Edit_NewFile_Path.SetWindowTextW(m_strAddressPath);
	m_Edit_NewFile_FileName.SetFocus();
}

void NewFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_NEWFILE_PATH, m_Edit_NewFile_Path);
	DDX_Control(pDX, IDC_EDIT_NEWFILE_FILENAME, m_Edit_NewFile_FileName);
}


BEGIN_MESSAGE_MAP(NewFileDlg, CDialogEx)                      //���ӳ��
	ON_BN_CLICKED(IDC_BTN_NEWFILE_NEW, &NewFileDlg::OnBnClickedNewFileNew)
	ON_BN_CLICKED(IDC_BTN_NEWFILE_CANCLE, &NewFileDlg::OnBnClickedNewFileCancle)
	ON_EN_CHANGE(IDC_EDIT_NEWFILE_PATH, &NewFileDlg::OnEnChangeEditNewfilePath)
END_MESSAGE_MAP()


// NewFileDlg ��Ϣ�������


void NewFileDlg::OnBnClickedNewFileNew()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_Edit_NewFile_Path.GetWindowTextW(m_strAddressPath);  //��ȡ�ı��������
	m_Edit_NewFile_FileName.GetWindowTextW(m_strFileName);
	if (m_strFileName.IsEmpty())
	{
		MessageBox(_T("�½�ʧ�ܣ��������ļ�����"), NULL, MB_ICONERROR);
		return;
	}
	m_strAddressPath = m_strAddressPath + "\\" + m_strFileName;  //�����ĵ�ַ������·�����ļ�����
	CreateFile(m_strAddressPath,             //��CreatFile()�½��ļ�
		GENERIC_ALL,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	GetParent()->SendMessage(WM_MSG, 0, 0);     //����½�������Ϣ��TESTDEMO�Ի���
	SendMessage(WM_CLOSE);
			      	        
}

//����enter
void NewFileDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	OnBnClickedNewFileNew();
	CDialogEx::OnOK();
}

//"ȡ��"��ť����Ӧ
void NewFileDlg::OnBnClickedNewFileCancle()
{
	SendMessage(WM_CLOSE);                
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void NewFileDlg::OnEnChangeEditNewfilePath()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}