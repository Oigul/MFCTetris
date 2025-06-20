
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
	std::vector<int> m_scores;

	sqlite3* db;

	void SavingScores(int playerScore);
	void ConnectingBD();
	void RequestBD();
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CMFCTetrisApp theApp;
