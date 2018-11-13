#pragma once
#include <iostream>
#include "d_matrix.h"

//using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
						   //  (usually 3).  The board has
						   //  SquareSize^2 rows and SquareSize^2
						   //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

class board
	// Stores the entire Sudoku board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &fin);
	void print();
	bool isBlank(int, int);
	ValueType getCell(int, int);
	void setCell(int i, int j, int val);
	void clearCell(int i, int j);
	bool isSolved();
	void printConflicts();

private:

	// The following matrices go from 1 to BoardSize in each
	// dimension, i.e., they are each (BoardSize+1) * (BoardSize+1)

	matrix<ValueType> value;

	// Conflict Vectors
	matrix<bool> rows;
	matrix<bool> cols;
	matrix<bool> squares;

};