#include "../../pch.h"
#include "../../Public/Game/Game.h"

#include <ctime>

Game::Game() : m_field(iRows, std::vector<int>(iCols, 0)), m_saveField(iRows, std::vector<int>(iCols, 0))
{
	std::srand(std::time(nullptr));
	int randomNumber = std::rand() % 7;    // от 0 до 6
	m_CurentForm = std::make_unique<Form>(randomNumber);

	for (int y = 0; y < m_CurentForm->GetRowCount(); ++y)
	{
		for (int x = 0; x < m_CurentForm->GetColCount(); ++x)
		{
			if (m_CurentForm->GetCell(y, x) != 0)
				m_field[y][x] = m_CurentForm->GetCell(y, x);
		}
	}
}

bool Game::IsCellFilled(int x, int y) const
{
	if (y < 0 || y >= iRows)
		return false;
	if (x < 0 || x >= iCols)
		return false;

	return (m_field[y][x] == 1 || m_saveField[y][x] == 1);
}

void Game::Tick()
{
	MoveDown();
}

bool Game::OnKeyDown(WPARAM key)
{
	switch (key)
	{
	case VK_LEFT:  MoveLeft();  return true;
	case VK_RIGHT: MoveRight(); return true;
	case VK_DOWN:  MoveDown();  return true;
	case VK_UP:    Rotate();    return true;
	}
	return false;
}

void Game::MoveDown()
{
	//определение длины фигуры
	int rowsInform = 0;//длина фигуры
	for (int y = 0; y < 4; ++y)
	{
		if (m_CurentForm->GetCell(y, 0) != 0)
		{
			++rowsInform;
		}
	}

	//выход, если нельзя сместить ниже | IntersectionCheck false - есть пересечение ture - нет
	if (m_iPosY + rowsInform == iRows || !IntersectionCheck(m_iPosX, m_iPosY + 1))
	{
		for (int y = 0; y < iRows; ++y)
		{
			for (int x = 0; x < iCols; ++x)
			{
				if (m_field[y][x] == 1 && m_saveField[y][x] != 1)
					m_saveField[y][x] = 1;
			}
		}

		ClearLines();

		m_field = m_saveField;

		std::srand(std::time(nullptr));
		int randomNumber = std::rand() % 7;    // от 0 до 6
		m_CurentForm->MakeNewGrid(randomNumber);
		m_iPosY = 0;
		m_iPosX = 0;

		if (!IntersectionCheck(m_iPosX, m_iPosY))
		{
			gameOver = true;
			return;
		}

		return;
	}

	//смещение фигуры
	for (int y = 0; y < rowsInform; ++y)
	{
		for (int x = 0; x < m_CurentForm->GetColCount(); ++x)
		{
			if (y == 0)
			{
				if (m_iPosX + x < iCols)
					m_field[m_iPosY][m_iPosX+x] = 0;
			}

			if (m_iPosY + 1 + y < iRows && m_iPosX + x < iCols)
			{
				if (m_saveField[m_iPosY + 1 + y][m_iPosX + x] != 1)
					m_field[m_iPosY + 1 + y][m_iPosX + x] = m_CurentForm->GetCell(y,x);
			}
		}
	}

	++m_iPosY;
}

void Game::MoveLeft()
{
	//определение ширины и длины фигуры
	int colsInform = 0;
	for (int x = 0; x < 4; ++x)
	{
		if (m_CurentForm->GetCell(0, x) != 0)
		{
			++colsInform;
		}
	}

	int rowsInform = 0;
	for (int y = 0; y < 4; ++y)
	{
		if (m_CurentForm->GetCell(y, 0) != 0)
		{
			++rowsInform;
		}
	}

	//выход, если нельзя сместить левее
	if (m_iPosX == 0 || m_iPosY + rowsInform == iRows)
		return;

	if (!IntersectionCheck(m_iPosX - 1, m_iPosY))
		return;

	int m_iPosXNew = m_iPosX - 1;

	//смещение фигуры
	for (int y = 0; y < rowsInform; ++y)
	{
		for (int x = 0; x < colsInform; ++x)
		{
			if (x == colsInform - 1)
			{
				if (m_iPosY + y < iRows)
					m_field[m_iPosY + y][m_iPosX + x] = 0;
			}

			if (m_iPosY + y < iRows && m_iPosXNew + x < iCols)
			{
				m_field[m_iPosY + y][m_iPosXNew + x] = m_CurentForm->GetCell(y, x);
			}
			else
				return;//OIGUL!!! break????
		}
	}

	m_iPosX = m_iPosXNew;
}

void Game::MoveRight()
{
	//IntersectionCheck(m_iPosX + 1, m_iPosY);
	
	//определение ширины и длины фигуры
	int colsInform = 0;
	for (int x = 0; x < 4; ++x)
	{
		if (m_CurentForm->GetCell(0, x) != 0)
		{
			++colsInform;
		}
	}

	int rowsInform = 0;
	for (int y = 0; y < 4; ++y)
	{
		if (m_CurentForm->GetCell(y, 0) != 0)
		{
			++rowsInform;
		}
	}

	//выход, если нельзя сместить левее
	if (m_iPosX >= 9)
	{
		int a = 0;
	}

	if (m_iPosX + colsInform == iCols || m_iPosY + rowsInform == iRows || m_iPosX == iCols)
	{
		//m_iPosX = m_iPosX + colsInform;
		return;
	}

	if (m_iPosX + colsInform < iCols && m_iPosY + rowsInform != iRows)
		if (!IntersectionCheck(m_iPosX + 1, m_iPosY))
			return;

	//смещение фигуры
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			if (x == 0)
			{
				if (m_iPosY + y < iRows)
					m_field[m_iPosY + y][m_iPosX] = 0;
			}

			if (m_iPosY + y < iRows && m_iPosX + 1 + x < iCols)
			{
				m_field[m_iPosY + y][m_iPosX + 1 + x] = m_CurentForm->GetCell(y, x);
				//bWasMove = true
			}
			else
				break;
		}
	}

	++m_iPosX;
}

void Game::Rotate()
{
	std::vector<std::vector<int>> NewGrid1(m_CurentForm->GetRowCount(), std::vector<int>(m_CurentForm->GetColCount(), 0));
	NewGrid1 = m_CurentForm->GetGrid();

	//поворот матрицы
	for (int y = 0; y < m_CurentForm->GetRowCount() / 2; ++y)
	{
		for (int x = y; x < m_CurentForm->GetColCount() - y - 1; ++x)
		{
			int N = m_CurentForm->GetRowCount();

			int temp = NewGrid1[y][x];
			NewGrid1[y][x] = NewGrid1[N - 1 - x][y];
			NewGrid1[N - 1 - x][y] = NewGrid1[N - 1 - y][N - 1 - x];
			NewGrid1[N - 1 - y][N - 1 - x] = NewGrid1[x][N - 1 - y];
			NewGrid1[x][N - 1 - y] = temp;
		}

	}

	//поиск положения фигуры в матрице
	int PosX = 0;
	bool find = false;
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			if (NewGrid1[y][x] != 0)
			{
				find = true;
				PosX = x;
				break;
			}
			else
				if (find)
					break;
		}
		if (find)
			break;
	}

	int PosY = 0;
	find = false;
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			if (NewGrid1[y][x] != 0)
			{
				find = true;
				PosY = y;
				break;
			}
		}
		if (find)
			break;
	}

	//смещение в начало сетки
	std::vector<std::vector<int>> NewGrid(m_CurentForm->GetRowCount(), std::vector<int>(m_CurentForm->GetColCount(), 0));
	for (int y = 0; y < m_CurentForm->GetRowCount(); ++y)
	{
		for (int x = 0; x < m_CurentForm->GetColCount(); ++x)
		{
			if (y + PosY < m_CurentForm->GetRowCount() && x + PosX < m_CurentForm->GetColCount())
				NewGrid[y][x] = NewGrid1[y + PosY][PosX + x];
		}
	}

	//определение ширины и длины новой фигуры
	int colsInform = 0;
	for (int x = 0; x < 4; ++x)
	{
		if (NewGrid[0][x] != 0)
		{
			++colsInform;
		}
	}

	int rowsInform = 0;
	for (int y = 0; y < 4; ++y)
	{
		if (NewGrid[y][0] != 0)
		{
			++rowsInform;
		}
	}

	//если новая фигура не влезает или есть пересечение с другими фигурами - выход
	if (m_iPosY + rowsInform - 1 >= iRows)
		return;

	if (!IntersectionCheck(m_iPosX, m_iPosY, NewGrid))
		return;

	//смещение фигуры влево пока она не влезает (если не будет наезжать на другие фигуры)
	int iNewPosX = m_iPosX;
	while (iNewPosX  + colsInform - 1 >= iCols)
	{
		--iNewPosX;
		if (iNewPosX >= 0 && !IntersectionCheck(iNewPosX, m_iPosY, NewGrid))
		{
			return;
		}
	}
	m_iPosX = iNewPosX;

	m_CurentForm->SetGrid(NewGrid);

	for (int y = 0; y < m_CurentForm->GetRowCount(); ++y)
	{
		for (int x = 0; x < m_CurentForm->GetColCount(); ++x)
		{
			if (m_iPosY + y < iRows && m_iPosX + x < iCols)
				m_field[m_iPosY + y][m_iPosX + x] = m_CurentForm->GetCell(y, x);
		}
	}
}

//false есть пересечение true нет его
bool Game::IntersectionCheck(int iNewX, int iNewY)
{
	if (iNewX > iCols && iNewY > iRows)
		return false;

	int rowsInform = 0;
	for (int y = 0; y < m_CurentForm->GetRowCount(); ++y)
	{
		if (m_CurentForm->GetCell(y, 0) != 0)
		{
			++rowsInform;
		}
		else
			break;
	}

	for (int y = 0; y < rowsInform; ++y)
	{
		for (int x = 0; x < m_CurentForm->GetColCount(); ++x)
		{
			if (iNewY + y < iRows && iNewX + x < iCols)
				if (m_saveField[iNewY + y][iNewX + x] == 1 && m_CurentForm->GetCell(y, x) == 1)
					return false;
		}
	}

	return true;
}

//false есть пересечение true нет его
bool Game::IntersectionCheck(int iNewX, int iNewY, std::vector<std::vector<int>>& newField)
{
	if (iNewX > iCols && iNewY > iRows)
		return false;

	int rowsInform = 0;
	for (int y = 0; y < m_CurentForm->GetRowCount(); ++y)
	{
		if (m_CurentForm->GetCell(y, 0) != 0)
		{
			++rowsInform;
		}
		else
			break;
	}

	for (int y = 0; y < rowsInform; ++y)
	{
		for (int x = 0; x < m_CurentForm->GetColCount(); ++x)
		{
			if (iNewY + y < iRows && iNewX + x < iCols)
				if (m_saveField[iNewY + y][iNewX + x] == 1 && newField[y][x] == 1)
					return false;
		}
	}

	return true;
}

void Game::ClearLines()
{
	for (int y = iRows - 1; y >= 0; --y)
	{
		bool bThereIsAnEmptyCell = false;
		int iPaintedOver = 0;
		
		for (int x = 0; x < iCols; ++x)
		{
			if (m_saveField[y][x] != 0)
			{
				++iPaintedOver;
			}
			else
			{
				bThereIsAnEmptyCell = true;
				break;
			}
		}

		if (!bThereIsAnEmptyCell)
		{
			++m_score;

			//bool last = false;
			for (int y2 = y; y2 > 0; --y2)
			{
				int rowAboveIsEmpty = 0;
				for (int x = 0; x < iCols; ++x)
				{
					if (m_saveField[y2 - 1][x] == 1)
					{
						m_saveField[y2][x] = m_saveField[y2 - 1][x];
					}
					else
					{
						++rowAboveIsEmpty;
						m_saveField[y2][x] = 0;
					}
				}

				//if (last == true)
					//break;
				if (rowAboveIsEmpty == iCols /* && last == false*/)
				{
					break;
				}
			}
			++y;
		}

	}
}
