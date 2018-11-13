/**
* Team: fitsmu
* Jason Fitch
* Sam Smucny
*
* board.h: Declaration of soduku board class
*/

#pragma once
#include <iostream>
#include "d_matrix.h"

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
						   //  (usually 3).  The board has
						   //  SquareSize^2 rows and SquareSize^2
						   //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

// Stores the entire Sudoku board
class board
{
public:
	board(int);
	void clear();
	void initialize(ifstream &);
	void print() const;
	bool isBlank(const int&, const int&) const;
	ValueType getCell(const int&, const int&) const;
	void setCell(const int&, const int&, const ValueType&);
	void clearCell(const int&, const int&);
	bool isSolved() const;
	void printConflicts() const;

private:

	// The following matrices go from 1 to BoardSize in each
	// dimension, i.e., they are each (BoardSize) * (BoardSize)

	// Sudoku board values
	matrix<ValueType> value;

	// Conflict Vectors
	matrix<bool> rows;
	matrix<bool> cols;
	matrix<bool> squares;

};