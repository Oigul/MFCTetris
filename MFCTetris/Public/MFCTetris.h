
// MFCTetris.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include <vector>

#include "..\External\SQLLite\sqlite3.h"
#include "..\resource.h"		// основные символы

class CMFCTetrisApp : public CWinApp
{
public:
	CMFCTetrisApp();

protected:
	sqlite3* db;
	//int m_score = 0;
	std::vector<int> m_scores;
// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMFCTetrisApp theApp;
