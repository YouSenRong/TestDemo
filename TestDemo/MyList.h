#pragma once

// MyList

#include "NewFileDlg.h"
#include "NewFolderDlg.h"
#include "MoveFileDlg.h"
#include "RenameFileDlg.h"

class MyList : public CListCtrl
{
	DECLARE_DYNAMIC(MyList)

public:
	MyList();
	virtual ~MyList();

	void Initial(CEdit* address);
	int GetSortedCol(){return m_nSortedCol;}
	BOOL GetAsc(){return m_bAsc;}

	//���ѡ������·��,�ɹ�Ϊ�ļ�����1���ɹ�Ϊ�ļ��з���2��
	//û��ѡ������-1��û��ѡ��·������-2
	INT GetSelectedItemPath(CString &strAddress);
	//���ѡ�������ļ���,�ɹ�Ϊ�ļ�����1���ɹ�Ϊ�ļ��з���2��
	//û��ѡ������-1;
	INT GetSelectedItemFileName(CString &strFileName);
	

protected:
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()


private:
	//�б�����
	static int CALLBACK ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

	//���б�͵�ַ����ϵ����
	void SetRelatedEdit(CEdit* address) { m_edtAddress = address; }

	CImageList m_RightImageList;
	int m_nSortedCol;//��ǰ�������
	BOOL m_bAsc;//�Ƿ�˳������
	CEdit* m_edtAddress;

	//�����ļ���Դ��ַ
	//CString strCopySource;
	//���Ƶ��ļ����ļ���
	//CString strCopyFileName;

	//����ָ��
	NewFileDlg*			m_dlgNewFile;
	CNewFolderDlg*		m_dlgNewFolder;
	CMoveFileDlg*		m_dlgMoveFile;
	CRenameFileDlg*		m_dlgRenameFile;

public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	// ˫���б�����Ӧ�¼�������Ӧ�б�����ļ��������ļ���
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditDelete();
	afx_msg void OnEditPatse();
	afx_msg void OnEditMove();
	afx_msg void OnEditRename();
	afx_msg void OnEditNew();
	afx_msg void OnEditNewFolder();
};


