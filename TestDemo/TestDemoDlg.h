// TestDemoDlg.h : ͷ�ļ�
//

#pragma once

#include "MyTree.h"
#include "MyList.h"
#include "NewFileDlg.h"
#include "NewFolderDlg.h"
#include "MoveFileDlg.h"
#include "RenameFileDlg.h"
#include "ProcessManager.h"
#define WM_MSG WM_USER+0x01

extern CString strCopySource;		//�����ļ���Դ��ַ
extern CString strCopyFileName;	//���Ƶ��ļ����ļ���

// CTestDemoDlg �Ի���
class CTestDemoDlg : public CDialog
{
// ����
public:
	CTestDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CTestDemoDlg();
	
// �Ի�������
	enum { IDD = IDD_TESTDEMO_DIALOG };

//���ݲ���
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
    virtual BOOL DestroyWindow();

// ʵ��
protected:
	HICON m_hIcon;
public:
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	//��ת������ť�ĵ�����Ӧ
	afx_msg void OnbtnGoto();        //��ת������ť�ĵ�����Ӧ
	afx_msg void OnbtnSearch();		//����������ť�ĵ�����Ӧ
	DECLARE_MESSAGE_MAP()

protected:
	//���ؼ�������Ի����еĺ���
	virtual void AddControl(CWnd* control,LPCTSTR lpszClassName,LPCTSTR lpszText, DWORD dwStyle, const RECT& rect);

	
private:
	CDialog* dlgInitital;			//���Ի���
	CList<CWnd*> m_ControlList;		//����ؼ�������
	CStatic* stAddress;				//��̬�ı���
	CEdit* m_edtAddress;			//��ַ��ʾ���ı���
	CButton* m_btnGoto;				//��ת������ť��������ˢ��
	CStatic* m_stSearch;			//����������̬�ı���
	CEdit* m_edtSearch;				//�����ɱ༭�ı���
	CButton* m_btnSearch;			//�����ҡ���ť
	//CTreeCtrl* m_treLeft;
	//CListCtrl* m_lstRight;

	//CMFCShellTreeCtrl* m_treLeft;
	//CMFCShellListCtrl* m_lstRight;

	MyTree* m_treLeft;			//������������Ŀ¼���ؼ�
	MyList* m_lstRight;			//���������Ҳ���б�ؼ�

	CRect m_rectClient;
	int m_iClientWidth;			//�ͻ����Ŀ��
	int m_iClientHeight;		//�ͻ����ĸ߶�

	
	//INT PatseOrCut;					//�жϵ�ǰ�����Ǹ��ƻ��Ǽ��У�1��ʾ���ƣ�2��ʾ���У������޲���

	CMenu m_rscMainMenu;

	//����ָ��
	NewFileDlg*			m_dlgNewFile;			//�½��ļ�����
	CNewFolderDlg*		m_dlgNewFolder;			//�½��ļ��д���
	CMoveFileDlg*		m_dlgMoveFile;			//�ƶ��ļ�����
	CRenameFileDlg*		m_dlgRenameFile;		//����������
	CProcessManager*	m_dlgProcessManager;	//���̹���������

protected:
	afx_msg LRESULT OnMsg(WPARAM wParam, LPARAM lParam);

public:
	//�˵�����ť����Ϣ��Ӧ����
	afx_msg void OnEditCopy();
	afx_msg void OnEditPatse();
	afx_msg void OnEditDelete();
	afx_msg void OnHelpAbout();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnEditRename();
	afx_msg void OnEditMove();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnEditNew();
	afx_msg void OnEditNewFolder();
	afx_msg void OnProcessManager();
//	afx_msg void OnEditCut();
	afx_msg void OnHelpNote();
};
