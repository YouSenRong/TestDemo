// SearchFile.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDemo.h"
#include "SearchFile.h"


// CSearchFile

IMPLEMENT_DYNAMIC(CSearchFile, CWnd)

CSearchFile::CSearchFile()
{
}

CSearchFile::~CSearchFile()
{
}


BEGIN_MESSAGE_MAP(CSearchFile, CWnd)
END_MESSAGE_MAP()



// CSearchFile ��Ϣ�������

//����SearchFileThread��������һ���µ��߳̽����ļ�����
//·��Ϊ�շ���-1�������ļ���Ϊ�շ���-2���ɹ�����1
UINT CSearchFile::StartSearchFile(CString strDirPath, CString strSearchFileName)
{
	static ThreadParameter tp;
	if (strDirPath == _T("") || strDirPath == _T("�ҵĵ���"))//����·��Ϊ��
	{
		return -1;
	}
	if (strSearchFileName.IsEmpty())//�����ļ���Ϊ��
	{
		return -2;
	}
	SearchFileListCtrl->DeleteAllItems();
	tp.SetThreadParameter(strDirPath, strSearchFileName);
	HANDLE hSearchFileThread;
	//����һ�������߳�
	hSearchFileThread = AfxBeginThread(SearchFileThread, &tp, 0, 0, 0, 0);
	if (hSearchFileThread == INVALID_HANDLE_VALUE)
	{
		MessageBox(_T("Create Search Error!"),_T("CSearchFile Class"), MB_ICONERROR);
		return FALSE;
	}
	WaitForSingleObject(hSearchFileThread, INFINITE);
	return TRUE;
}

//���ù������б�ؼ�
void CSearchFile::SetReleatedListCtrl(CListCtrl* ListCtrl)
{
	SearchFileListCtrl = ListCtrl;
}

//���ļ�������������������ļ������̺߳���
UINT CSearchFile::SearchFileThread(LPVOID pParam)
{
	ThreadParameter *tp = (ThreadParameter *)pParam;
	CString strDirPath = tp->strDirPath;
	CString strSearchFileName = tp->strSearchFileName;
	CList<CString> m_SearchFilePathList;
	m_SearchFilePathList.AddTail(strDirPath);
	INT iNum = 0;
	CFileFind fileFind;
	while (m_SearchFilePathList.GetSize() > 0)
	{
		CString strTempDirPath = m_SearchFilePathList.GetHead();
		if (strTempDirPath.Right(1) != _T("\\"))
		{
			strTempDirPath += _T("\\");
		}
		strTempDirPath += "*.*";
		BOOL bContinue = fileFind.FindFile(strTempDirPath);
		while (bContinue)
		{
			bContinue = fileFind.FindNextFile();
			if (fileFind.GetFileName() == strSearchFileName)
			{
				SHFILEINFO fileInfo;
				CString tempPath = strTempDirPath;
				int index = tempPath.Find(_T("*.*"));
				tempPath.Delete(index, 3);
				SHGetFileInfo(tempPath + fileFind.GetFileName(), 0, &fileInfo, sizeof(&fileInfo), SHGFI_ICON | SHGFI_DISPLAYNAME | SHGFI_TYPENAME);
				int iIcon = SearchFileListCtrl->GetImageList(LVSIL_SMALL)->Add(fileInfo.hIcon);
				int ret = SearchFileListCtrl->InsertItem(iNum, fileInfo.szDisplayName, iIcon);

				SearchFileListCtrl->SetItemText(iNum, 2, fileInfo.szTypeName);

				//�����ļ����Ա���
				CFileStatus status;
				CFile::GetStatus(tempPath + fileFind.GetFileName(), status);
				CString strSize;
				strSize.Format(_T("%.3f KB"), status.m_size / 1024.0);
				SearchFileListCtrl->SetItemText(iNum, 1, strSize);

				CString strModifyTime = status.m_ctime.Format("%Y-%m-%d %H:%M:%S");
				SearchFileListCtrl->SetItemText(iNum, 3, strModifyTime);
				SearchFileListCtrl->SetItemText(iNum, 4, fileFind.GetFilePath());
				iNum++;
			}
			if (fileFind.IsDirectory() && !fileFind.IsDots())
			{
				m_SearchFilePathList.AddTail(fileFind.GetFilePath());
			}
		}
		m_SearchFilePathList.RemoveHead();
	}
	if (iNum == 0)
	{
		SearchFileListCtrl->InsertItem(iNum, _T("�����޽��"));
	}
	else
	{
		++iNum;
		SearchFileListCtrl->InsertItem(iNum, _T("��������"));
	}

	
	return 0;
}
//�ݹ������ļ�
/*
UINT CSearchFile::SearchFileThread(LPVOID pParam)
{
	//���ļ�����ȱ���������
	ThreadParameter *tp = (ThreadParameter *)pParam;
	CString strTempDirPath = tp->strDirPath;
	if (strTempDirPath.Right(1) != _T("\\"))
	{
		strTempDirPath += _T("\\");
	}
	strTempDirPath += "*.*";
	CFileFind fileFind;
	BOOL bContinue = fileFind.FindFile(strTempDirPath);
	INT iNum = 0;
	while (bContinue)
	{
		bContinue = fileFind.FindNextFile();

		if (fileFind.GetFileName() == tp->strSearchFileName)
		{
			//AfxMessageBox(fileFind.GetFilePath());
			SHFILEINFO fileInfo;
			CString tempPath = strTempDirPath;
			int index = tempPath.Find(_T("*.*"));
			tempPath.Delete(index, 3);
			SHGetFileInfo(tempPath + fileFind.GetFileName(), 0, &fileInfo, sizeof(&fileInfo), SHGFI_ICON | SHGFI_DISPLAYNAME | SHGFI_TYPENAME);
			int iIcon = SearchFileListCtrl->GetImageList(LVSIL_SMALL)->Add(fileInfo.hIcon);
			int ret = SearchFileListCtrl->InsertItem(iNum, fileInfo.szDisplayName, iIcon);

			SearchFileListCtrl->SetItemText(iNum, 2, fileInfo.szTypeName);

			//�����ļ����Ա���
			CFileStatus status;
			CFile::GetStatus(tempPath + fileFind.GetFileName(), status);
			CString strSize;
			strSize.Format(_T("%d B"), status.m_size);
			SearchFileListCtrl->SetItemText(iNum, 1, strSize);

			CString strModifyTime = status.m_ctime.Format("%Y-%m-%d %H:%M:%S");
			SearchFileListCtrl->SetItemText(iNum, 3, strModifyTime);

			iNum++;
			//m_SearchFilePathArray.Add(fileFind.GetFilePath());
			
			return 0;
		}
		if (fileFind.IsDirectory() && !fileFind.IsDots())
		{
			ThreadParameter tempThreadParameter(fileFind.GetFilePath(), tp->strSearchFileName);
			SearchFileThread(&tempThreadParameter);
		}
	}
	return 0;
}*/