// MyList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyList.h"
#include "TestDemo.h"
#include <iostream>
#include <string>
#include "resource.h"
#include "TestDemoDlg.h"
#include "DeleteFile.h"
#include "CopyFile.h"
using namespace std;


// MyList

IMPLEMENT_DYNAMIC(MyList, CListCtrl)

MyList::MyList()
{
	m_dlgNewFile = NULL;
	m_dlgNewFolder = NULL;
	m_dlgMoveFile = NULL;
	m_dlgRenameFile = NULL;
}

MyList::~MyList()
{
	delete m_dlgNewFile;
	delete m_dlgNewFolder;
	delete m_dlgMoveFile;
	delete m_dlgRenameFile;
}


BEGIN_MESSAGE_MAP(MyList, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK,OnColumnClick)
//	ON_NOTIFY_REFLECT(NM_RCLICK, &MyList::OnNMRClick)
ON_WM_RBUTTONDOWN()
ON_COMMAND(IDM_EDIT_COPY, &MyList::OnEditCopy)
ON_NOTIFY_REFLECT(NM_DBLCLK, &MyList::OnNMDblclk)
//ON_WM_RBUTTONUP()
ON_COMMAND(IDM_EDIT_DELETE, &MyList::OnEditDelete)
ON_COMMAND(IDM_EDIT_PATSE, &MyList::OnEditPatse)
ON_COMMAND(IDM_EDIT_MOVE, &MyList::OnEditMove)
ON_COMMAND(IDM_EDIT_RENAME, &MyList::OnEditRename)
ON_COMMAND(IDM_EDIE_NEW_FILE, &MyList::OnEditNew)
ON_COMMAND(IDM_EDIT_NEW_FOLDER, &MyList::OnEditNewFolder)
END_MESSAGE_MAP()



// MyList ��Ϣ�������

void MyList::Initial(CEdit* address)
{
	m_RightImageList.Create(16,16,ILC_COLOR32,16,16);
	this->SetImageList(&m_RightImageList,LVSIL_SMALL);			//����ListCtrl��ImageList����

	this->InsertColumn(0,	_T("����"),		LVCFMT_LEFT,	200);
	this->InsertColumn(1,	_T("��С"),		LVCFMT_LEFT,	160);
	this->InsertColumn(2,	_T("����"),		LVCFMT_LEFT,	180);
	this->InsertColumn(3,	_T("�޸�����"),	LVCFMT_LEFT,	180);
	this->InsertColumn(4,	_T("·��"),		LVCFMT_LEFT,	300);

	m_edtAddress = address;
}

void MyList::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	//MessageBox(_T("OnColumnClick"));
    int nCouter,i;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	 
	MyList *m_FileList=this;
	if(pNMListView->iSubItem == m_nSortedCol)
	{
		m_bAsc=!m_bAsc;
	}
	else
	{
		m_bAsc=this->GetStyle() & LVS_SORTASCENDING;;
		m_nSortedCol = pNMListView->iSubItem;
	}
	nCouter=m_FileList->GetItemCount();
	for (i=0;i<nCouter;i++)
	{
		CString strText = m_FileList->GetItemText(i,m_nSortedCol);
		m_FileList->SetItemData(i,i);
	}
	m_FileList->SortItems(ListCompare,(DWORD)m_FileList);
	*pResult = 0;
}

int CALLBACK MyList::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	MyList *sort=(MyList *)lParamSort;
	CString string1 = sort->GetItemText(lParam1,sort->GetSortedCol());
	CString string2= sort->GetItemText(lParam2,sort->GetSortedCol());

	//if(sort->GetAsc()==TRUE)
	//	return string1>string2;
	//else 
	//	return string1<string2;

	if(sort->GetAsc()==TRUE)
		return string1.CompareNoCase(string2);
	else 
		return string1.CompareNoCase(string2)*(-1);
	
}

void MyList::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	GetWindowRect(&rect); //�õ��ؼ���������

	int x = point.x + rect.left; //����˵���ʾλ�õ�X����
	int y = point.y + rect.top; //����˵���ʾλ�õ�y����

	/*if (!GetSelectedCount()) //���û���б��ѡ��
	{
		return;
	}*/

	CMenu* m_PopMenu = new CMenu;
	m_PopMenu->LoadMenu(IDR_MENU_MAINFRAME); //���ز˵�

	//������ݲ˵�
	TrackPopupMenu(m_PopMenu->GetSubMenu(1)->m_hMenu, 0, x, y, 0, this->GetSafeHwnd(), &rect);

	CListCtrl::OnRButtonDown(nFlags, point);
}

// ˫���б�����Ӧ�¼�������Ӧ�б�����ļ��������ļ���
void MyList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strFilePath, strFileName;
	INT iNum = 0;
	CFileFind fileFind;
	int nSelectNumber;
	nSelectNumber = GetSelectionMark();
	strFileName = GetItemText(nSelectNumber, 0);
	m_edtAddress->GetWindowText(strFilePath);
	if (GetItemText(nSelectNumber, 2) == _T("�ļ���"))//������ļ�������
	{
		DeleteAllItems();
		strFilePath = strFilePath + strFileName + _T("\\");
		m_edtAddress->SetWindowText(strFilePath);
		strFilePath += "*.*";
		//MessageBox(_T("�ļ���"));
		BOOL bContinue = fileFind.FindFile(strFilePath);
		while (bContinue)
		{
			bContinue = fileFind.FindNextFile();
			if (/*!fileFind.IsDirectory() && */!fileFind.IsDots() && !fileFind.IsHidden())
			{
				SHFILEINFO fileInfo;
				CString tempPath = strFilePath;
				int index = tempPath.Find(_T("*.*"));
				tempPath.Delete(index, 3);
				SHGetFileInfo(tempPath + fileFind.GetFileName(), 0, &fileInfo, sizeof(&fileInfo), SHGFI_ICON | SHGFI_DISPLAYNAME | SHGFI_TYPENAME);
				int iIcon = GetImageList(LVSIL_SMALL)->Add(fileInfo.hIcon);
				int ret = InsertItem(iNum, fileInfo.szDisplayName, iIcon);

				SetItemText(iNum, 2, fileInfo.szTypeName);

				//�����ļ����Ա���
				CFileStatus status;
				CFile::GetStatus(tempPath + fileFind.GetFileName(), status);
				CString strSize;
				strSize.Format(_T("%.3f KB"), status.m_size / 1024.0);
				SetItemText(iNum, 1, strSize);

				CString strModifyTime = status.m_ctime.Format("%Y-%m-%d %H:%M:%S");
				SetItemText(iNum, 3, strModifyTime);
				SetItemText(iNum, 4, fileFind.GetFilePath());

				iNum++;
			}
		}
	}
	//������ļ������ShellExecute����Ĭ�Ϸ�ʽ���ļ�
	else
	{
		strFileName = strFilePath + strFileName;
		ShellExecute(NULL, _T("open"), strFileName, 0, 0, SW_SHOWNORMAL);
	}
	*pResult = 0;
}

//���ѡ�������ļ���,�ɹ�Ϊ�ļ�����1���ɹ�Ϊ�ļ��з���2��û��ѡ������-1;
INT MyList::GetSelectedItemFileName(CString &strFileName)
{
	int nSelectNumber;                   //�����ѡ�ļ����к�
	nSelectNumber = this->GetSelectionMark(); //���ѡ�е��е��к�
	if (nSelectNumber == -1)                           //δѡ���ļ�������ʾɾ��ʧ��
	{
		return -1;
	}
	strFileName = GetItemText(nSelectNumber, 0);
	if (GetItemText(nSelectNumber, 2) == _T("�ļ���") )//���ļ������Ҳ���".",�ʷ���-1
	{
		return 2;
	}
	else
		return 1;
	
}

//���ѡ������·��,�ɹ�����1��û��ѡ������-1��û��ѡ��·������-2
INT MyList::GetSelectedItemPath(CString &strAddress)
{
	CString strFileName;
	m_edtAddress->GetWindowText(strAddress);
	INT FileType;
	if (strAddress.IsEmpty())
	{
			return -2;
	}
	FileType = GetSelectedItemFileName(strFileName);
	if(FileType == 1)
	{
		strAddress = strAddress + strFileName;
		return 1;
	}
	else if (FileType == 2)
	{
		strAddress = strAddress + strFileName;
		return 2;
	}
	else
	{
		return -1;
	}
	return 1;
}
//�Ҽ������˵���Ӧ�¼�
//�½�
void MyList::OnEditNew()
{
	// TODO: �ڴ���������������
	CString strAddress;
	m_edtAddress->GetWindowText(strAddress);  //��ȡ��ǰ·��
	if (strAddress.IsEmpty())                   //·������Ϊ��
	{
		MessageBox(_T("�½�ʧ�ܣ�·��Ϊ��"), NULL, MB_ICONERROR);
		return;
	}
	if (m_dlgNewFile == NULL)
	{
		m_dlgNewFile = new NewFileDlg();
		m_dlgNewFile->Create(IDD_NEWFILE_DIALOG, this);
	}
	//���½��ļ��ĶԻ���
	m_dlgNewFile->Initital(strAddress);
	m_dlgNewFile->ShowWindow(SW_SHOW);	                     //��ʾ�˶Ի���,��ģ̬
}

//�½��ļ���
void MyList::OnEditNewFolder()
{
	// TODO: �ڴ���������������
	CString strAddress;
	m_edtAddress->GetWindowText(strAddress);	//��ȡ��ǰ·��
	if (strAddress.IsEmpty())					 //·������Ϊ��
	{
		MessageBox(_T("�½�ʧ�ܣ�·��Ϊ��"), NULL, MB_ICONERROR);
		return;
	}
	if (m_dlgNewFolder == NULL)
	{
		m_dlgNewFolder = new CNewFolderDlg();
		m_dlgNewFolder->Create(IDD_NEWFOLDER_DIALOG, this);		//���½��ļ��ĶԻ���
	}
	m_dlgNewFolder->Initial(strAddress);
	m_dlgNewFolder->ShowWindow(SW_SHOW);						//��ʾ�˶Ի���
}


//����
void MyList::OnEditCopy()
{
	// TODO: �ڴ���������������
	CString strAddress;
	switch (GetSelectedItemPath(strAddress))
	{
	case 1:
		strCopySource = strAddress;
		GetSelectedItemFileName(strCopyFileName);
		MessageBox(_T("�ļ����Ƴɹ�"));
		break;
	case 2:
		strCopySource = strAddress;
		GetSelectedItemFileName(strCopyFileName);
		MessageBox(_T("�ļ��и��Ƴɹ�"));
		break;
	//û��ѡ����
	case -1:
		MessageBox(_T("��ǰû��ѡ����"), NULL, MB_ICONWARNING);
		break;
	//û��ѡ��·��
	case -2:
		MessageBox(_T("��ǰ·��Ϊ��"), NULL, MB_ICONWARNING);
		break;
	}
}
//ճ��
void MyList::OnEditPatse()
{
	// TODO: �ڴ���������������
	CString strAddress;
	m_edtAddress->GetWindowText(strAddress);
	if (strAddress.IsEmpty())
	{
		MessageBox(_T("��ǰ·��Ϊ��"), NULL, MB_ICONWARNING);
		return;
	}
	CCopyFile CF;
	CString strPasteDesti = strAddress + "\\" + strCopyFileName;   //Ҫճ������Ŀ�ĵ�ַ
	if (strCopySource.IsEmpty()) return;
	switch (CF.Copy(strCopySource, strPasteDesti))
	{
	case 1:
		GetParent()->SendMessage(WM_MSG, 0, 0);     //����½�������Ϣ��TESTDEMO�Ի���
		MessageBox(_T("�ļ���ճ���ɹ�!"));
		break;
	case 2:
		GetParent()->SendMessage(WM_MSG, 0, 0);     //����½�������Ϣ��TESTDEMO�Ի���
		MessageBox(_T("�ļ�ճ���ɹ�!"));
		break;
	case 0:
		MessageBox(_T("�ļ�ճ��ʧ��!"), NULL, MB_ICONERROR);
		break;
	}
}
//ɾ��
void MyList::OnEditDelete()
{
	// TODO: �ڴ���������������
	CString strAddress;
	CDeleteFile DF;
	switch (GetSelectedItemPath(strAddress))
	{
	case -1:
		MessageBox(_T("��ǰû��ѡ����"), NULL, MB_ICONWARNING);
		return;
		//û��ѡ��·��
	case -2:
		MessageBox(_T("��ǰ·��Ϊ��"), NULL, MB_ICONWARNING);
		return;
	}
	switch (DF.Delete(strAddress))
	{
	case 1:
		MessageBox(_T("�ļ���ɾ���ɹ�"));
		break;
	case 2:
		MessageBox(_T("�ļ�ɾ���ɹ�"));
		break;
	case 0:
		MessageBox(_T("ɾ��ʧ��"));
		break;
	}
	GetParent()->SendMessage(WM_MSG, 0, 0);     //����½�������Ϣ��TESTDEMO�Ի���
}
//�ƶ�
void MyList::OnEditMove()
{
	// TODO: �ڴ���������������
	CString strAddress;
	CString strFileName;
	if (m_dlgMoveFile == NULL)
	{
		m_dlgMoveFile = new CMoveFileDlg();
		m_dlgMoveFile->Create(IDD_MOVEFILE_DIALOG, this);
	}
	switch (GetSelectedItemPath(strAddress))
	{
	case 1:
		GetSelectedItemFileName(strFileName);
		m_dlgMoveFile->Ininatial(strAddress, strFileName);
		m_dlgMoveFile->ShowWindow(SW_SHOW);
		break;
	//û��ѡ����
	case -1:
		MessageBox(_T("��ǰû��ѡ����"), NULL, MB_ICONWARNING);
		break;
	//û��ѡ��·��
	case -2:
		MessageBox(_T("��ǰ·��Ϊ��"), NULL, MB_ICONWARNING);
		break;
	}
}
//������
void MyList::OnEditRename()
{
	// TODO: �ڴ���������������
	CString strAddress;
	CString strFileName;
	if (m_dlgRenameFile == NULL)
	{
		m_dlgRenameFile = new CRenameFileDlg();
		m_dlgRenameFile->Create(IDD_RENAMEFILE_DIALOG, this);
	}
	switch (GetSelectedItemPath(strAddress))
	{
	case 1:
		m_edtAddress->GetWindowText(strAddress);
		GetSelectedItemFileName(strFileName);
		m_dlgRenameFile->Initital(strFileName, strAddress);
		m_dlgRenameFile->ShowWindow(SW_SHOW);
		break;
	//û��ѡ����
	case -1:
		MessageBox(_T("��ǰû��ѡ����"), NULL, MB_ICONWARNING);
		break;
	//û��ѡ��·��
	case -2:
		MessageBox(_T("��ǰ·��Ϊ��"), NULL, MB_ICONWARNING);
		break;
	}
}
