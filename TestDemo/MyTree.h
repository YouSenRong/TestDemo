#pragma once


// MyTree

class MyTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(MyTree)

public:
	MyTree();
	virtual ~MyTree();
	void Initial(CListCtrl* listctrl,CEdit* address);

	//��ȱ��������ң����ָ�����ݵ����ڵ�
    HTREEITEM FindItemText(CTreeCtrl* tree,HTREEITEM item, CString strtext);  
	//��ȱ��������ң�
	HTREEITEM FindItem(HTREEITEM item,CString strPath);   

protected:
	 //������ص��б���ͼ
	void SetRelatedList(CListCtrl* listctrl){m_lstRight = listctrl;}
	//������صĵ�ַ��
	void SetRelatedEdit(CEdit* address){m_edtAddress = address;}
	HTREEITEM InsertItemToTree(HTREEITEM hParent, CString strPath,CString DisplayName);
	// ��ȡ�̷���Ŀ¼������Ϊ��Ŀ¼��һ���ڵ�
	void GetLogicalDrives(HTREEITEM hRoot);
	// ��ȡ��������һ��Ŀ¼��Ŀ¼������ʾ
	void GetDriveDir(HTREEITEM hRoot);
	// ����Ŀ¼������һ�ڵ��ȡ��������Ŀ¼
	void AddSubDir(HTREEITEM hParent);
	// ��ȡĳ�ڵ���ļ�·��
	CString GetFullPath(HTREEITEM hCurrent);
protected:
	afx_msg void OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnItemexpandedTreedir(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()


private:
	//���ڵ�
	HTREEITEM m_hRoot;
	/*//����ڵ�
	HTREEITEM m_hDeskTop;
	CString m_strDeskTopPath;*/
	//Image List
	CImageList m_LeftImageList;
	CListCtrl* m_lstRight;
	CEdit* m_edtAddress;
	//CString m_DriveType[7] = { _T("��δ֪��"), _T("����Ч·����"), _T("���ƶ����̣�"), _T("�����̣�"), _T("��������������"), _T("��CD/DVD��"), _T("������洢���̣�") };
};


