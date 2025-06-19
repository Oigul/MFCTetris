#include "../../pch.h"
#include "../../Public/Game/Form.h"

Form::Form(int iType) : m_grid(iRows, std::vector<int>(iCols, 0)), m_Type(iType)
{
    for (int y = 0; y < iRows; ++y)
    {
        for (int x = 0; x < iCols; ++x)
        {
            if (TetrisFigures[m_Type][y][x] != 0)
                m_grid[y][x] = TetrisFigures[m_Type][y][x];
        }
    }
}

void Form::MakeNewGrid(int i)
{
    for (int y = 0; y < iRows; ++y)
    {
        for (int x = 0; x < iCols; ++x)
        {
            m_grid[y][x] = 0;
        }
    }

    m_Type = i;
    for (int y = 0; y < iRows; ++y)
    {
        for (int x = 0; x < iCols; ++x)
        {
            if (TetrisFigures[m_Type][y][x] != 0)
                m_grid[y][x] = TetrisFigures[m_Type][y][x];
        }
    }
}
