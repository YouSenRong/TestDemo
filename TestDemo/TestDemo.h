// TestDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
//#include <afxwinappex.h>

// CTestDemoApp:
// �йش����ʵ�֣������ TestDemo.cpp
//

class CTestDemoApp : public CWinApp //public CWinAppEx
{
public:
	CTestDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestDemoApp theApp;