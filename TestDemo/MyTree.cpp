// MyTree.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "TestDemo.h"
#include "MyTree.h"


// MyTree

IMPLEMENT_DYNAMIC(MyTree, CTreeCtrl)

MyTree::MyTree()
{

}

MyTree::~MyTree()
{
}


BEGIN_MESSAGE_MAP(MyTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelChanged)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpandedTreedir)
END_MESSAGE_MAP()



// MyTree ��Ϣ�������


void MyTree::Initial(CListCtrl* listctrl,CEdit* address)
{
	this->SetRelatedList(listctrl);
	this->SetRelatedEdit(address);
	//����ImageList
	m_LeftImageList.Create(16,16,ILC_COLOR32,16,16);
	this->SetImageList(&m_LeftImageList,TVSIL_NORMAL);               //����TreeCtrl��ImageList����

	m_hRoot = this->InsertItem(_T("�ҵĵ���"),0,0,TVI_ROOT);
	GetLogicalDrives(m_hRoot);						//��ȡ�������������ص�Ŀ¼��
	GetDriveDir(m_hRoot);							//��ȡ��������һ���ļ��е�Ŀ¼��
	//InsertItemToTree(m_hRoot, _T("C:\\"), _T("����"));
	/*m_hDeskTop = this->InsertItem(_T("����"), 0, 0, TVI_ROOT);
	GetLogicalDrives(m_hDeskTop);
	GetDriveDir(m_hDeskTop);*/
}

//��ȱ��������ң����ָ�����ݵ����ڵ�
/*HTREEITEM MyTree::FindItemText(CTreeCtrl* tree, HTREEITEM item, CString strtext) 
{   
	HTREEITEM hfind;    

	//������ֱ�ӷ���NULL
	if(item == NULL)   
		return NULL;  

	//��������
	while(item!=NULL) 
	{   
		//��ǰ�ڵ㼴������ҽڵ�
		if(tree->GetItemText(item) == strtext)   
			return item;   	    

		//���ҵ�ǰ�ڵ���ӽڵ�
		if(tree->ItemHasChildren(item))  
		{
			item = tree->GetChildItem(item); 
			//�ݹ���ò����ӽڵ��½ڵ�
			hfind = FindItemText(tree,item,strtext);
			if(hfind)   
			{   
				return hfind;  
			}   
			else //�ӽڵ���δ��������ڵ㣬���������ֵܽڵ�
			{
				item = tree->GetNextSiblingItem(tree->GetParentItem(item)); 
			}
			
		} 
		else
		{ //�����ӽڵ㣬���������ֵܽڵ�
			 item = tree->GetNextSiblingItem(item);   
		}   

	}
    return item;   
}*/

//��ȱ��������ң�����ָ��·���µĽڵ�
HTREEITEM MyTree::FindItem(HTREEITEM item,CString strPath)
{
	HTREEITEM hfind;
	if(strPath.Right(1) == "\\")  //ȥ���Ҳ�'\'
	{
		strPath.Delete(strPath.GetLength()-1);
	}
	CString DirName;
	int pos = strPath.Find('\\');
	if(pos>0)
	    DirName = strPath.Left(pos);
	else
		DirName = strPath;

	//��������
   while(item!=NULL) 
   {   
	   CString curDir = this->GetItemText(item);
	   //ȥ�����ұߵ�"\"
		if(curDir.Right(1) == "\\")
		{
			curDir.Delete(curDir.GetLength()-1);
		}
	  //��ǰ�ڵ㼴������ҽڵ�
		if(curDir.CompareNoCase(DirName) == 0)
	  {
		  if(curDir.CompareNoCase(strPath) == 0)
			  return item; 
		  //����ҵ��ڵ㣬�����������ӽڵ�
		  else if(this->ItemHasChildren(item))
		  {
			  item = this->GetChildItem(item); 
			  //�ݹ���ò����ӽڵ��½ڵ�
			  hfind = FindItem(item,strPath.Mid(pos+1));
			  if(hfind)   
			  {   
				return hfind;  
			  }
		  }
		  return NULL;  //δ���ҵ� 
	  }
	  else
	  {
		  //�����ֵܽڵ�
		  if(this->GetNextSiblingItem(item) != NULL)
		  {
			  item = this->GetNextSiblingItem(item);
		  }
          //�����ֵܽڵ㣬���������ӽڵ�
		  else if(this->ItemHasChildren(item))
		  {
			  item = this->GetChildItem(item); 
		  }
		  else
			  return NULL;     //δ���ҵ� 

		  hfind = FindItem(item,strPath);
		  if(hfind)   
		  {   
			return hfind;  
		  }
	  }
   }
	return item;
}

// ��ȡ�̷���Ŀ¼������Ϊ��Ŀ¼��һ���ڵ�
void MyTree::GetLogicalDrives(HTREEITEM hRoot)
{
	size_t szAllDrivesStrings = GetLogicalDriveStrings(0,NULL);							//��ȡ�������ַ�����
	TCHAR* pDriveStrings = new TCHAR[szAllDrivesStrings + sizeof(_T(""))];				//�����ַ����洢�������ַ�pDriveStrings,����ָ��
	GetLogicalDriveStrings((DWORD)szAllDrivesStrings,pDriveStrings);					//��ȡ�������ַ���pDriveStrings
	//��ȡ�����������ַ�������ӵ�Ŀ¼����
	//������ʱ�ַ�ָ��ָ���������ַ���Ϣ
	//(Ϊ���������ͷ��������ַ�������,���ֱ���ƶ��ַ���ָ��,�������delete�ͷ��ַ�����Դ��ʱ��ᱨ��)
	TCHAR* pTempDrive = pDriveStrings;
	size_t szDriveString = wcslen(pTempDrive);

	//CString strDrivepame;			//������������
	//UINT uDriveType;				//������������
	while(szDriveString>0)
	{
		//strDrivepame = pTempDrive;								//����������������
		//uDriveType = GetDriveType(strDrivepame);				//��ȡ������������
		//this->InsertItem(pTempDrive,hRoot);					//���ؽ������һ����������Ϣ��Ŀ¼��
		InsertItemToTree(hRoot, pTempDrive, pTempDrive);
		pTempDrive += szDriveString + 1;
		szDriveString = wcslen(pTempDrive);
	}
	delete pDriveStrings;
}

// ��ȡ��������һ��Ŀ¼��Ŀ¼������ʾ
void MyTree::GetDriveDir(HTREEITEM hRoot)
{
	HTREEITEM hChild = this->GetChildItem(hRoot);				//��ȡ���ڵ��µĵ�һ���̷��ڵ�
	while(hChild)
	{
		//��ȡ����·��
		CString strText = this->GetItemText(hChild);
		if(strText.Right(1) != _T("\\"))
		{
			strText += _T("\\");
		}
		strText += "*.*";
		CFileFind fileFind;
		BOOL bContinue = fileFind.FindFile(strText);
		while(bContinue)
		{
			bContinue = fileFind.FindNextFile();
			//�����µ��ļ���Ŀ¼���Ҳ���[.]��[..]��ʱ�򣬼��ص�Ŀ¼��
			if(fileFind.IsDirectory() && !fileFind.IsDots())
			{
				//this->InsertItem(fileFind.GetFileName(),hChild);
				CString tempPath = strText;
				int index = tempPath.Find(_T("*.*"));
				tempPath.Delete(index,3);
				InsertItemToTree(hChild,tempPath+fileFind.GetFileName(),fileFind.GetFileName());
			}
		}
		//����һ��������
		hChild = this->GetNextItem(hChild,TVGN_NEXT);
	}
}

// ����Ŀ¼������һ�ڵ��ȡ��������Ŀ¼
void MyTree::AddSubDir(HTREEITEM hParent)
{
	CString strPath = GetFullPath(hParent);
	if(strPath.Right(1) != "\\")
	{
		strPath += "\\";
	}
	strPath += "*.*";
	CFileFind fileFind;
	BOOL bContinue = fileFind.FindFile(strPath);
	while(bContinue)
	{
		bContinue = fileFind.FindNextFile();
		if(fileFind.IsDirectory() && !fileFind.IsDots()&&!fileFind.IsHidden())
		{
			//this->InsertItem(fileFind.GetFileName(),hParent);
			CString tempPath = strPath;
			int index = tempPath.Find(_T("*.*"));
			strPath.Delete(index,3);
			InsertItemToTree(hParent,tempPath+fileFind.GetFileName(),fileFind.GetFileName());
		}
	}
}

// ��ȡĳ�ڵ���ļ�·��
CString MyTree::GetFullPath(HTREEITEM hCurrent)
{
	CString strTemp = _T("");
	CString strFullPath = _T("");
	while(hCurrent != m_hRoot)
	{
		//�ӵ�ǰ�ڵ����������ҳ��丸�ڵ㣬�����ڵ����
		strTemp = this->GetItemText(hCurrent);
		if(strTemp.Right(1) != _T("\\"))
			strTemp += _T("\\");
		strFullPath = strTemp + strFullPath;
		hCurrent = this->GetParentItem(hCurrent);
	}
	return strFullPath;
}

// չ��ĳ�ڵ㴥���¼�
void MyTree::OnItemexpandedTreedir(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TVITEM item = pNMTreeView->itemNew;				//��ȡ��ǰչ���ڵ�
	//�����ǰչ���ڵ�Ϊ���ڵ�,�򷵻�
	if(item.hItem == m_hRoot)
		return;
	HTREEITEM hChild = this->GetChildItem(item.hItem);
	if(pNMTreeView->action == 1)  //����
	{	
		while(hChild!=NULL)
		{
			while(this->ItemHasChildren(hChild))
			{
				HTREEITEM item = this->GetChildItem(hChild);
				this->DeleteItem(item);
			}
		    hChild = this->GetNextItem(hChild,TVGN_NEXT);
		}
	}
	else if(pNMTreeView->action == 2) //չ��
	{
		//��ѵչ���ڵ��ÿ���ӽڵ㣬�����ļ�Ŀ¼��Ϣ���ӽڵ���
		while(hChild!=NULL)
		{
			AddSubDir(hChild);
			hChild = this->GetNextItem(hChild,TVGN_NEXT);
		}
	}

	*pResult = 0;
}


void MyTree::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	this->Expand(this->GetSelectedItem(), TVE_EXPAND);

	m_lstRight->DeleteAllItems();					//ɾ��ListView������Ԫ��
	//��ȡ��ǰĿ¼·��
	TVITEM item = pNMTreeView->itemNew;
	if(item.hItem == m_hRoot)
	{
		m_edtAddress->SetWindowText(_T("�ҵĵ���"));
		return;
	}
	CString strDirPath = GetFullPath(item.hItem);
	m_edtAddress->SetWindowText(strDirPath); //���µ�ַ����ַ
	if(strDirPath.Right(1)=="\\")
	{
		strDirPath += "*.*";
	}
	//���ҵ�ǰĿ¼�µ������ļ���ӵ�ListView��
	CFileFind fileFind;
	BOOL bContinue = fileFind.FindFile(strDirPath);
	int iNum = 0;
	while(bContinue)
	{
		bContinue = fileFind.FindNextFile();
		if(/*!fileFind.IsDirectory() && */!fileFind.IsDots() && !fileFind.IsHidden())
		{
			SHFILEINFO fileInfo;
			CString tempPath = strDirPath;
			int index = tempPath.Find(_T("*.*"));
			tempPath.Delete(index,3);
			SHGetFileInfo(tempPath + fileFind.GetFileName(),0,&fileInfo,sizeof(&fileInfo),SHGFI_ICON | SHGFI_DISPLAYNAME | SHGFI_TYPENAME );
			int iIcon = m_lstRight->GetImageList(LVSIL_SMALL)->Add(fileInfo.hIcon);
			int ret = m_lstRight->InsertItem(iNum,fileInfo.szDisplayName,iIcon);
			
			m_lstRight->SetItemText(iNum,2,fileInfo.szTypeName);

			//�����ļ����Ա���
			CFileStatus status;
			CFile::GetStatus(tempPath + fileFind.GetFileName(), status);
			CString strSize;
			strSize.Format(_T("%.3f KB"),status.m_size / 1024.0);
            m_lstRight->SetItemText(iNum,1,strSize);

			CString strModifyTime = status.m_ctime.Format("%Y-%m-%d %H:%M:%S");
			m_lstRight->SetItemText(iNum,3,strModifyTime);
			m_lstRight->SetItemText(iNum, 4, fileFind.GetFilePath());

			iNum++;
		}
	}
	 *pResult = 0;
}

HTREEITEM MyTree::InsertItemToTree(HTREEITEM hParent, CString strPath, CString DisplayName)
{
	SHFILEINFO fileInfo;
	SHGetFileInfo(strPath,0,&fileInfo,sizeof(&fileInfo),SHGFI_ICON|SHGFI_DISPLAYNAME|SHGFI_TYPENAME);
	int iIcon = m_LeftImageList.Add(fileInfo.hIcon);
	return this->InsertItem(/*fileInfo.szDisplayName*/DisplayName,iIcon,iIcon,hParent);
}
