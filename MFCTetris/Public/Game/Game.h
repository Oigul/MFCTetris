#pragma once

#include <memory>
#include <vector>

#include "Form.h"

class Game
{
public:
	Game();

	bool IsCellFilled(int x, int y) const;

	int GetRowCount() const { return iRows; }
	int GetColCount() const { return iCols; }
	int GetCurrentScore() const { return m_score; }
	bool GetGameOver() const { return gameOver; }

	void Tick();
	bool OnKeyDown(WPARAM key);

protected:
	const int iRows = 20;
	const int iCols = 10;

	std::unique_ptr<Form> m_CurentForm;
	int m_iPosX = 0;
	int m_iPosY = 0;

	int m_score = 0;
	bool gameOver = false;

	std::vector<std::vector<int>> m_field;     //игровое поле
	std::vector<std::vector<int>> m_saveField;

	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Rotate();

	bool IntersectionCheck(int iNewX, int iNewY);
	bool IntersectionCheck(int iNewX, int iNewY, std::vector<std::vector<int>>& newField);

	void ClearLines();


};

