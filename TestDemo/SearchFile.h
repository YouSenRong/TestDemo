#pragma once


//�Զ���ṹ�壬���ڶ��̵߳Ĳ�������
struct ThreadParameter
{
	CString strDirPath;
	CString strSearchFileName;
	ThreadParameter() {}	//Ĭ�Ϲ��캯��
	ThreadParameter(CString strDirPath, CString strSearchFileName)//���캯��
	{
		this->strDirPath = strDirPath;
		this->strSearchFileName = strSearchFileName;
	}
	BOOL SetThreadParameter(CString strDirPath, CString strSearchFileName)
	{
		this->strDirPath = strDirPath;
		this->strSearchFileName = strSearchFileName;
		return TRUE;
	}
};

//����ؼ�����ʾ�������
static CListCtrl *SearchFileListCtrl;

// CSearchFile
//�����ļ�����
class CSearchFile : public CWnd
{
	DECLARE_DYNAMIC(CSearchFile)

public:
	CSearchFile();
	virtual ~CSearchFile();

protected:
	DECLARE_MESSAGE_MAP()
protected:
public:
	//����SearchFileThread��������һ���µ��߳̽����ļ�����
	//·��Ϊ�շ���-1�������ļ���Ϊ�շ���-2���ɹ�����1
	UINT StartSearchFile(CString strDirPath, CString strSearchFileName);
	//���ù������б�ؼ�
	void SetReleatedListCtrl(CListCtrl* ListCtrl);
private:
	//���ļ�������������������ļ������̺߳���
	static UINT SearchFileThread(LPVOID pParam);

};


