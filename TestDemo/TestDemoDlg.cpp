// TestDemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestDemo.h"
#include "TestDemoDlg.h"
#include "SearchFile.h"
#include "DeleteFile.h"
#include "CopyFile.h"
#include <Windows.h>
#include <iostream>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString strCopySource = _T("");
CString strCopyFileName = _T("");

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CTestDemoDlg �Ի���


CTestDemoDlg::CTestDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	dlgInitital = new CDialog();
	dlgInitital = this;
	m_dlgNewFile = NULL;
	m_dlgNewFolder = NULL;
	m_dlgMoveFile = NULL;
	m_dlgRenameFile = NULL;
	m_dlgProcessManager = NULL;
}
CTestDemoDlg::~CTestDemoDlg()
{
	delete m_dlgNewFile;
	delete m_dlgNewFolder;
	delete m_dlgMoveFile;
	delete m_dlgRenameFile;
	delete m_dlgProcessManager;
}
void CTestDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDemoDlg, CDialog)    //�ֶ����ӳ��
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_GOTO, OnbtnGoto)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnbtnSearch)//IDֵ�ǰ����õ���AddControl()��˳�����
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MSG, &CTestDemoDlg::OnMsg)
	ON_COMMAND(IDM_EDIT_COPY, &CTestDemoDlg::OnEditCopy)
	//ON_COMMAND(IDM_EDIT_CUT, &CTestDemoDlg::OnEditCut)
	ON_COMMAND(IDM_EDIT_PATSE, &CTestDemoDlg::OnEditPatse)
	ON_COMMAND(IDM_EDIT_DELETE, &CTestDemoDlg::OnEditDelete)
	ON_COMMAND(IDM_HELP_ABOUT, &CTestDemoDlg::OnHelpAbout)
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(IDM_EDIT_RENAME, &CTestDemoDlg::OnEditRename)
	
	ON_COMMAND(IDM_EDIT_MOVE, &CTestDemoDlg::OnEditMove)
	ON_COMMAND(IDM_EDIE_NEW_FILE, &CTestDemoDlg::OnEditNew)
	ON_COMMAND(IDM_EDIT_NEW_FOLDER, &CTestDemoDlg::OnEditNewFolder)
	ON_COMMAND(IDM_PROCESS_MANAGER, &CTestDemoDlg::OnProcessManager)
//	ON_COMMAND(IDM_EDIT_CUT, &CTestDemoDlg::OnEditCut)
ON_COMMAND(IDM_HELP_NOTE, &CTestDemoDlg::OnHelpNote)
END_MESSAGE_MAP()


// CTestDemoDlg ��Ϣ�������

BOOL CTestDemoDlg::OnInitDialog()            //��ʼ������
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//����Ĭ�ϴ�С
	this->ShowWindow(SW_SHOWNORMAL);
	this->SetWindowTextW(_T("Windows ��Դ������"));
	


	//�������ڼ��ز˵�
	m_rscMainMenu.LoadMenu(IDR_MENU_MAINFRAME);
	SetMenu(&m_rscMainMenu);

	//get the screen's pixel ����豸��Ļ��С
    int screenX = GetSystemMetrics(SM_CXSCREEN);   
    int screenY = GetSystemMetrics(SM_CYSCREEN);
	//��öԻ����С
	this->GetWindowRect(&m_rectClient);
	
	ScreenToClient(&m_rectClient);
	m_iClientWidth = m_rectClient.Width();
    m_iClientHeight = m_rectClient.Height();
	//���ô���λ���Լ���С
	this->SetWindowPos(&wndNoTopMost, (screenX- m_iClientWidth)/2, (screenY- m_iClientHeight)/2, 1300, 800, SWP_SHOWWINDOW);
	
	//�����ǽ��ؼ���ӵ�TESTDEMO�Ի����ϵĴ��룬������CList������
    //CRect()��ǰ���������ǿؼ����Ͻǵ����꣬�����ʾ���½�����
	
	//��ť�ؼ�
	stAddress = new CStatic();
	AddControl(stAddress, _T("STATIC"), _T("��ַ"), WS_VISIBLE | WS_CHILD, CRect(10, 10, 10 + 40, 10 + 30));
	m_edtAddress = new CEdit();
	AddControl(m_edtAddress, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER, CRect(60, 10, 60 + 640, 10 + 30));
	m_edtAddress->SetFocus();
	m_btnGoto = new CButton();
	AddControl(m_btnGoto, _T("BUTTON"), _T("ת��"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_ICON, CRect(710, 10, 710 + 40, 10 + 30));
	m_stSearch = new CStatic();
	AddControl(m_stSearch, _T("STATIC"), _T("����"), WS_VISIBLE | WS_CHILD, CRect(750 + 10, 10, 750 + 10 + 40, 10 + 30));
	m_edtSearch = new CEdit();
	AddControl(m_edtSearch, _T("EDIT"), _T(""), WS_VISIBLE | WS_CHILD | WS_BORDER, CRect(810, 10, 810 + 410, 10 + 30));
	m_btnSearch = new CButton();
	AddControl(m_btnSearch, _T("BUTTON"), _T("����"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_ICON, CRect(1230, 10, 1230 + 40, 10 + 30));
	//Ŀ¼���ؼ�
	//m_treLeft = new CTreeCtrl();
	//m_treLeft = new CMFCShellTreeCtrl;
	m_treLeft = new MyTree();
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | WS_BORDER | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS|TVS_SHOWSELALWAYS;
	AddControl(m_treLeft,WC_TREEVIEW,_T(""),dwViewStyle,CRect(10,50,10+330,50+660));

	//��ͼ�б�ؼ�
	//m_lstRight = new CListCtrl();
	//m_lstRight = new CMFCShellListCtrl();
	m_lstRight = new MyList();
	AddControl(m_lstRight, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL | ILC_MASK, CRect(350, 50, 350 + 920, 50 + 660));
	m_lstRight->SetExtendedStyle(m_lstRight->GetExtendedStyle()|LVS_EX_FULLROWSELECT );

	/*CStatusBarCtrl * barStatus = new CStatusBarCtrl();;
	AddControl(barStatus,STATUSCLASSNAME,_T(""),WS_CHILD | WS_VISIBLE | WS_BORDER|SBARS_SIZEGRIP| SBT_TOOLTIPS, CRect(0,rectClient.bottom-20,rectClient.Width(),rectClient.Height())) ;	
	CRect rect;
	barStatus->GetClientRect(&rect);
    int a[4]= {rect.right-600, rect.right-500, rect.right-300, -1 };
	barStatus->SetParts(4,a);*/

	/*barStatus->SetText(L"Arrcen",1,SBT_NOBORDERS );
    barStatus->SetText(L"MFC",2,SBT_POPOUT);
    barStatus->SetText(L"Show",3,SBT_NOBORDERS);*/

	stAddress->SetFont(GetFont());
	m_edtAddress->SetFont(GetFont());
	m_btnGoto->SetFont(GetFont());
	m_stSearch->SetFont(GetFont());
	m_edtSearch->SetFont(GetFont());
	m_btnSearch->SetFont(GetFont());

	//Ŀ¼���ؼ���ʼ��
	m_treLeft->Initial(m_lstRight,m_edtAddress);
	m_treLeft->Expand(m_treLeft->GetRootItem(), TVE_EXPAND);
	//��ͼ�б�ؼ���ʼ��
	m_lstRight->Initial(m_edtAddress);

	//�����ļ�·���༭������뽹��
	m_edtAddress->SetFocus();
	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDemoDlg::OnSize( UINT nType, int cx, int cy )
{
	CDialog::OnSize(nType,cx,cy);
	POSITION   pos = m_ControlList.GetHeadPosition();
	this->GetWindowRect(&m_rectClient);
	ScreenToClient(&m_rectClient);
	CRect tempRect;
	if (nType == SIZE_MAXIMIZED)
	{
		//���õ�ַ���༭���λ��
		m_edtAddress->MoveWindow(60, 10, (int)(m_rectClient.Width()*0.50), 30);

		//��õ�ַ���༭���λ�ò����á�ת������ť��λ��
		m_edtAddress->GetWindowRect(&tempRect);
		ScreenToClient(tempRect);
		m_btnGoto->MoveWindow(tempRect.right + 10, tempRect.top, 40, tempRect.Height());

		//��á�ת������ť��λ�ò����á���������̬�ı����λ��
		m_btnGoto->GetWindowRect(&tempRect);
		ScreenToClient(tempRect);
		m_stSearch->MoveWindow(tempRect.right +10, tempRect.top, 40, tempRect.Height());

		//��á���������̬�ı����λ�ò����á��������༭���λ��
		m_stSearch->GetWindowRect(&tempRect);
		ScreenToClient(tempRect);
		m_edtSearch->MoveWindow(tempRect.right + 10, tempRect.top, (int)(m_rectClient.Width()*0.36), tempRect.Height());

		//��á��������༭���λ�ò����á���������ť��λ��
		m_edtSearch->GetWindowRect(&tempRect);
		ScreenToClient(tempRect);
		m_btnSearch->MoveWindow(tempRect.right + 10, tempRect.top, 40, tempRect.Height());

		//��������Ŀ¼�ؼ���λ��
		m_treLeft->MoveWindow(10, 50, (int)(m_rectClient.Width()*0.20), (int)(m_rectClient.Height()*0.85));
		
		//�������Ŀ¼�ؼ���λ�ò�������ͼ�б�ؼ���λ��
		m_treLeft->GetWindowRect(&tempRect);
		ScreenToClient(tempRect);
		CRect tempRect1;
		m_btnSearch->GetWindowRect(&tempRect1);
		ScreenToClient(tempRect1);
		//m_lstRight->MoveWindow(tempRect.right + 10, tempRect.top, (int)(m_rectClient.Width()*0.76), tempRect.Height());
		m_lstRight->MoveWindow(tempRect.right + 10, tempRect.top, tempRect1.right - (tempRect.right + 10), tempRect.Height());
		return;
	
	}
	//��󻯻�ԭ��ؼ���λ��
	if(pos != NULL)
	{
		m_edtAddress->MoveWindow(60, 10, 640, 30);
		m_btnGoto->MoveWindow(710, 10, 40, 30);
		m_stSearch->MoveWindow(760, 10, 40, 30);
		m_edtSearch->MoveWindow(810, 10, 410, 30);
		m_btnSearch->MoveWindow(1230, 10, 40, 30);
		m_treLeft->MoveWindow(10, 50, 330, 660);
		m_lstRight->MoveWindow(350, 50, 920, 660);
	}	
}


//���ٴ��ڣ��ͷ���Դ
BOOL CTestDemoDlg::DestroyWindow()
{
	//�ͷſؼ��������Դ
	while(!m_ControlList.IsEmpty())
	{
		CWnd* pWndCtrl = m_ControlList.RemoveTail();
		pWndCtrl->DestroyWindow();
		delete pWndCtrl;
		pWndCtrl = NULL;
	}
	return CDialog::DestroyWindow();
}

//��ӿؼ����Ի���ĺ���
void CTestDemoDlg::AddControl(CWnd* control,LPCTSTR lpszClassName,LPCTSTR lpszText, DWORD dwStyle, const RECT& rect)
{
	m_ControlList.AddTail(control);
	BOOL ret = control->Create(lpszClassName,lpszText,dwStyle,rect, dlgInitital,1001+m_ControlList.GetCount());//dlgInitital��Ϊ��ǰ�Ի���
}

afx_msg LRESULT CTestDemoDlg::OnMsg(WPARAM wParam, LPARAM lParam)    //NewFile��ر�ʱ��������Ϣ�Ĵ�����
{
	OnbtnGoto();
	return 0;
}

void CTestDemoDlg::OnbtnGoto()   //�൱�ڸ����ı����е�·����ˢ���Ҳ��б�
{
	CString strAddress;
	m_edtAddress->GetWindowText(strAddress);  //��ȡ�ı��������
	
	CString strInstead;
	strInstead = "D:\\";     // ת��"D:\"��ת�������൱��ʵ��ˢ�¹���
	if (strAddress == strInstead)
	{
		strInstead = "C:\\";
	}
	//��·����ȱ���������
	HTREEITEM item1 = m_treLeft->FindItem(m_treLeft->GetRootItem(),strInstead);
	HTREEITEM item2 = m_treLeft->FindItem(m_treLeft->GetRootItem(), strAddress);
	if (item2 != NULL)
	{
		m_treLeft->SelectItem(item1);
		m_treLeft->SetFocus();
		m_treLeft->SelectItem(item2);
		m_treLeft->SetFocus();
	}
	else
		return;
	
}
	
void CTestDemoDlg::OnbtnSearch()
{
	CString strDirPath;			//�������ļ�·��
	CString strSearchFileName; //�������ļ���
	CSearchFile SF;
	m_edtAddress->GetWindowText(strDirPath);		//�ӱ༭�����ļ�·��
	m_edtSearch->GetWindowText(strSearchFileName); //�ӱ༭�����ļ���
	SF.SetReleatedListCtrl(m_lstRight);
	switch (SF.StartSearchFile(strDirPath, strSearchFileName))
	{
	case 1:
		break;
	case -1:
		MessageBox(_T("����·��Ϊ��"), NULL, MB_ICONWARNING);
		break;
	case -2:
		MessageBox(_T("�����ļ���Ϊ��"), NULL, MB_ICONWARNING);
		break;
	}

}

//�½��ļ�
void CTestDemoDlg::OnEditNew()
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
void CTestDemoDlg::OnEditNewFolder()
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

void CTestDemoDlg::OnEditCopy()			//�˵����ġ����ơ�
{
	CString strAddress;
	switch (m_lstRight->GetSelectedItemPath(strAddress))
	{
	case 1:
		strCopySource = strAddress;
		m_lstRight->GetSelectedItemFileName(strCopyFileName);
		MessageBox(_T("�ļ����Ƴɹ�"));
		break;
	case 2:
		strCopySource = strAddress;
		m_lstRight->GetSelectedItemFileName(strCopyFileName);
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

void CTestDemoDlg::OnEditPatse()		//�˵����ġ�ճ����
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
		OnbtnGoto();
		MessageBox(_T("�ļ���ճ���ɹ�!"));
		break;
	case 2:
		OnbtnGoto();
		MessageBox(_T("�ļ�ճ���ɹ�!"));
		break;
	case 0:
		MessageBox(_T("�ļ�ճ��ʧ��!"), NULL, MB_ICONERROR);
		break;
	}
}


void CTestDemoDlg::OnEditDelete()		//�˵����ġ�ɾ����
{
	// TODO: �ڴ���������������
	CString strAddress;
	CDeleteFile DF;
	switch (m_lstRight->GetSelectedItemPath(strAddress))
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
		OnbtnGoto();
		MessageBox(_T("�ļ���ɾ���ɹ�"));
		break;
	case 2:
		OnbtnGoto();
		MessageBox(_T("�ļ�ɾ���ɹ�"));
		break;
	case 0:
		MessageBox(_T("ɾ��ʧ��"));
		break;
	}
}

void CTestDemoDlg::OnEditMove()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	CString strAddress;
	CString strFileName;
	if (m_dlgMoveFile == NULL)
	{
		m_dlgMoveFile = new CMoveFileDlg();
		m_dlgMoveFile->Create(IDD_MOVEFILE_DIALOG, this);
	}
	
	switch (m_lstRight->GetSelectedItemPath(strAddress))
	{
	case 1:
		m_lstRight->GetSelectedItemFileName(strFileName);
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

void CTestDemoDlg::OnEditRename()		//�˵����ġ���������
{
	// TODO: �ڴ���������������
	CString strAddress;
	CString strFileName;
	if (m_dlgRenameFile == NULL)
	{
		m_dlgRenameFile = new CRenameFileDlg();
		m_dlgRenameFile->Create(IDD_RENAMEFILE_DIALOG, this);
	}

	switch (m_lstRight->GetSelectedItemPath(strAddress))
	{
	case 1:
		m_edtAddress->GetWindowText(strAddress);
		m_lstRight->GetSelectedItemFileName(strFileName);
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

void CTestDemoDlg::OnHelpAbout()		//�˵����ġ�������->�����ڡ�
{
	// TODO: �ڴ���������������
	CAboutDlg MenuAboutDlg;
	MenuAboutDlg.DoModal();
}



BOOL CTestDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		{
			m_edtAddress->SetFocus();
			m_edtAddress->SetSel(0, -1);
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CTestDemoDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (lpMMI->ptMinTrackSize.x <= 800)
		lpMMI->ptMinTrackSize.x = 800;
	if (lpMMI->ptMinTrackSize.y <= 500)
		lpMMI->ptMinTrackSize.y = 500;
	CDialog::OnGetMinMaxInfo(lpMMI);
}


void CTestDemoDlg::OnProcessManager()
{
	// TODO: �ڴ���������������
	if (m_dlgProcessManager == NULL)
	{
		m_dlgProcessManager = new CProcessManager();
		m_dlgProcessManager->Create(IDD_PROCESSMANAGER_DIALOG, this);
	}
	m_dlgProcessManager->GetProcessList();
	m_dlgProcessManager->ShowWindow(SW_SHOW);

}


void CTestDemoDlg::OnHelpNote()
{
	// TODO: �ڴ���������������
	ShellExecute(NULL, _T("open"), _T("C:\\����ϵͳ��Ŀʵ�鱨��.docx"), 0, 0, SW_SHOWNORMAL);
}
