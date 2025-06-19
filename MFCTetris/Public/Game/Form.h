#pragma once

#include <vector> 

enum FigureType
{
    I, // Палка
    O, // Квадрат
    T, // Т-образная
    S, // Змейка влево
    Z, // Змейка вправо
    J, // Обратная L
    L  // L-образная
};

class Form
{
public:

    Form(int iType);

    int GetRowCount() const { return iRows; }
    int GetColCount() const { return iCols; }
    int GetCell(int y, int x) const { return m_grid[y][x]; }
    const std::vector<std::vector<int>>& GetGrid() const { return m_grid; }
    void SetGrid(const std::vector<std::vector<int>>& newGrid) { m_grid = newGrid; }


    void MakeNewGrid(int i);

protected:
    int iRows = 4;
    int iCols = 4;
    int m_Type;
    std::vector<std::vector<int>> m_grid;

    inline static const std::vector<std::vector<std::vector<int>>> TetrisFigures = {
        // I
        {
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // O
        {
            {1,1,0,0},
            {1,1,0,0},
            {0,0,0,0},
            {0,0,0,0}
        },

        // Т
        {
            {1,1,1,0},
            {2,1,2,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        //  S
        {
            {2,1,1,0},
            {1,1,2,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // Z
        {
            {1,1,2,0},
            {2,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        // J
        {
            {2,1,0,0},
            {2,1,0,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        // L
        {
            {1,2,0,0},
            {1,2,0,0},
            {1,1,0,0},
            {0,0,0,0}
        },

    };
};
