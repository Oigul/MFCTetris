
// MFCTetris.cpp: определяет поведение классов для приложения.
//

#include "../pch.h"
#include "../framework.h"
#include "../Public/MFCTetris.h"
#include "../Public/Dialogs/MFCTetrisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCTetrisApp

BEGIN_MESSAGE_MAP(CMFCTetrisApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Создание CMFCTetrisApp

CMFCTetrisApp::CMFCTetrisApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance

	//OIGUL SQLLITE
	const char* createTableSQL = "CREATE TABLE IF NOT EXISTS game_state (id INTEGER PRIMARY KEY, score INTEGER);";

	sqlite3_open("game2.db", &db);

	sqlite3_exec(db, createTableSQL, nullptr, nullptr, nullptr);

	const char* selectSQL = "CREATE TABLE IF NOT EXISTS game_state ("
							"id INTEGER PRIMARY KEY AUTOINCREMENT, "
							"score INTEGER);";





	//// Очищаем предыдущие данные
	//m_ListCtrl.DeleteAllItems();

	selectSQL = "SELECT score FROM game_state ORDER BY id DESC;";
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(db, selectSQL, -1, &stmt, nullptr) == SQLITE_OK)
	{
		int row = 0;
		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			int score = sqlite3_column_int(stmt, 0);

			//CString str;
			//str.Format(_T("%d очков"), score);

			// Вставляем строку в ListCtrl в первую колонку
			m_scores.push_back(score);
		}
		sqlite3_finalize(stmt);
	}
	else
	{
		//MessageBox(_T("Ошибка при загрузке результатов"), _T("Ошибка"), MB_ICONERROR);
	}

}


// Единственный объект CMFCTetrisApp

CMFCTetrisApp theApp;


// Инициализация CMFCTetrisApp

BOOL CMFCTetrisApp::InitInstance()
{
	// InitCommonControlsEx() требуется для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("Локальные приложения, созданные с помощью мастера приложений"));

	CMFCTetrisDlg mainDlg(m_scores);
	m_pMainWnd = &mainDlg;
	INT_PTR nResponse = mainDlg.DoModal();
	if (nResponse == IDOK)
	{
		//OIGUL SQLLITE
		int playerScore = mainDlg.GetCurrentScore();
		
		// 1. SQL-команда вставки
		const char* insertSQL = "INSERT INTO game_state (score) VALUES (?);";

		// 2. Подготавливаем SQL-выражение
		sqlite3_stmt* stmt;
		if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK)
		{
			// 3. Подставляем значение игрока в SQL-запрос
			sqlite3_bind_int(stmt, 1, playerScore);

			// 4. Выполняем запрос
			if (sqlite3_step(stmt) != SQLITE_DONE) {
				//MessageBox(_T("Ошибка при сохранении результата"), _T("Ошибка"), MB_ICONERROR);
			}
		}

		// 5. Освобождаем ресурсы
		sqlite3_finalize(stmt);
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Введите код для обработки закрытия диалогового окна
		//  с помощью кнопки "Отмена"
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Предупреждение. Не удалось создать диалоговое окно, поэтому работа приложения неожиданно завершена.\n");
		TRACE(traceAppMsg, 0, "Предупреждение. При использовании элементов управления MFC для диалогового окна невозможно #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

