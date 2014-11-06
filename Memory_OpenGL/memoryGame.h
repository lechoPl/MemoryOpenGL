#ifndef MEMORY_GAME
#define MEMORY_GAME

#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "field.h"

enum KEY {
	KEY_UP = GLFW_KEY_UP,
	KEY_DOWN = GLFW_KEY_DOWN,
	KEY_RIGHT = GLFW_KEY_RIGHT,
	KEY_LEFT = GLFW_KEY_LEFT,
};

struct Point
{
	unsigned x;
	unsigned y;

	Point() : x(0), y(0) { }
	Point(unsigned x, unsigned y) : x(x), y(y) { }

	inline bool operator == (const Point& p) { return x == p.x && y == p.y; }
};

class CMemoryGame
{
protected:
	static const unsigned m_uSize = 4;

	unsigned m_round;
	Point* m_firstSelectedField;
	Point* m_secendSelectedFiled;
	Point m_pos;
	CField m_board[m_uSize][m_uSize]; // 0 - empty; x - shape number; [x][y]
	
	virtual void printRounds();

public:
	CMemoryGame();
	virtual ~CMemoryGame();

	virtual void movePos(KEY k);
	virtual bool isWin();
	
	virtual bool selectField(); //true if select; false if unselect or empty
	
	virtual Point getCurrentPos() const { return m_pos; }
	virtual unsigned getRound() const { return m_round; }
	virtual unsigned getSize() const { return m_uSize; }
	virtual CField* getField(unsigned x, unsigned y) { return &m_board[x][y]; }
};

#endif