#include "memoryGame.h"

#include <ctime>
#include <cstdio>

CMemoryGame::CMemoryGame() : m_round(0), m_pos(0u, 0u), m_firstSelectedField(NULL), m_secendSelectedFiled(NULL)
{
	srand(static_cast<unsigned>(time(NULL)));

	if (m_uSize % 2 != 0)
	{
		fputs("Board size must be divisible by two.", stderr);
		exit(-1);
	}

	const unsigned numberOfFieldTypes = m_uSize * m_uSize / 2;

	short randedFields[numberOfFieldTypes];
	for (int i = 0; i < numberOfFieldTypes; ++i)
		randedFields[i] = 0;

	for (int i = 0; i < m_uSize; ++i)
	{
		for (int j = 0; j < m_uSize; ++j)
		{
			int randed;
			do
			{
				randed = rand() % numberOfFieldTypes;
			} while (randedFields[randed] >= 2);

			randedFields[randed] += 1;

			m_board[i][j].setTypeId(randed);
			m_board[i][j].setX(i);
			m_board[i][j].setY(j);
		}
	}
}
CMemoryGame::~CMemoryGame()
{
	if (m_firstSelectedField != NULL)
	{
		delete m_firstSelectedField;
		m_firstSelectedField = NULL;
	}

	if (m_secendSelectedFiled != NULL)
	{
		delete m_secendSelectedFiled;
		m_secendSelectedFiled = NULL;
	}
}
void CMemoryGame::printRounds()
{
	printf("Current round: %d\n", m_round);
}
void CMemoryGame::movePos(KEY k)
{
	switch (k)
	{
	case KEY_UP:
		m_pos.y = (m_pos.y < 1 ? m_uSize : m_pos.y) - 1;
		break;
	case KEY_DOWN:
		m_pos.y = m_pos.y >= m_uSize - 1 ? 0 : m_pos.y + 1;
		break;
	case KEY_LEFT:
		m_pos.x = (m_pos.x < 1 ? m_uSize : m_pos.x) - 1;
		break;
	case KEY_RIGHT:
		m_pos.x = m_pos.x >= m_uSize - 1 ? 0 : m_pos.x + 1;
		break;
	default:
		return;
	}
}
bool CMemoryGame::isWin()
{
	unsigned count = 0;
	for (int i = 0; i < m_uSize; ++i)
	{
		for (int j = 0; j < m_uSize; ++j)
		{
			if (m_board[i][j].getTypeId() < 0) ++count;
		}
	}

	return count == m_uSize * m_uSize;
}
bool CMemoryGame::selectField()
{	
	if (m_firstSelectedField != NULL && m_secendSelectedFiled != NULL)
	{
		if (m_board[m_firstSelectedField->x][m_firstSelectedField->y].getTypeId() == m_board[m_secendSelectedFiled->x][m_secendSelectedFiled->y].getTypeId())
		{
			m_board[m_firstSelectedField->x][m_firstSelectedField->y].setTypeId(-1);
			m_board[m_secendSelectedFiled->x][m_secendSelectedFiled->y].setTypeId(-1);
		}

		m_board[m_firstSelectedField->x][m_firstSelectedField->y].hideSign();
		m_board[m_secendSelectedFiled->x][m_secendSelectedFiled->y].hideSign();

		delete m_firstSelectedField;
		m_firstSelectedField = NULL;

		delete m_secendSelectedFiled;
		m_secendSelectedFiled = NULL;

		if (this->isWin())
		{
			printf("Game Over\n");
		}
	}

	if (m_board[m_pos.x][m_pos.y].getTypeId() < 0)
		return false;

	if (m_firstSelectedField == NULL)
	{
		m_firstSelectedField = new Point(m_pos);
		m_board[m_firstSelectedField->x][m_firstSelectedField->y].showSign();
		return true;
	}
	else
	{
		if (m_secendSelectedFiled == NULL)
		{
			if (*m_firstSelectedField == m_pos)
				return false;

			m_secendSelectedFiled = new Point(m_pos);
			m_board[m_secendSelectedFiled->x][m_secendSelectedFiled->y].showSign();

			++m_round;
			printRounds();

			return true;
		}
	}
	
	return true;
}


