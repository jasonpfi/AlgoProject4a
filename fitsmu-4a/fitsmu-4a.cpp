// Declarations and functions for project #4
#include <iostream>
#include <limits.h>
#include "d_matrix.h"
#include "d_except.h"
#include <list>
#include <fstream>

using namespace std;

typedef int ValueType; // The type of the value in a cell
const int Blank = -1;  // Indicates that a cell is blank

const int SquareSize = 3;  //  The number of cells in a small square
						   //  (usually 3).  The board has
						   //  SquareSize^2 rows and SquareSize^2
						   //  columns.

const int BoardSize = SquareSize * SquareSize;

const int MinValue = 1;
const int MaxValue = 9;

int numSolutions = 0;

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

template<typename T>
ostream &operator<<(ostream &ostr, vector<T> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	cout << endl;
	return ostr;
}

board::board(int sqSize)
	: value(BoardSize, BoardSize),
	rows(BoardSize), cols(BoardSize), squares(BoardSize)
	// Board constructor
{
	clear();
}

bool board::isSolved()
{
	bool boardFull = true, noColConflict = true, noRowConflict = true,
		noSqConflict = true;

	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			boardFull = boardFull && value[i][j] != Blank;
			noRowConflict = noRowConflict && rows[i - 1].at(j - 1);
			noColConflict = noColConflict && cols[i - 1].at(j - 1);
			noSqConflict = noSqConflict && squares[i - 1].at(j - 1);
		}
	}

	return boardFull && noColConflict && noRowConflict && noSqConflict;
}

void board::printConflicts()
{
	cout << "\nConflicts:\n";
	cout << "Digit: 1 2 3 4 5 6 7 8 9" << endl << endl;
	for (int i = 0; i < rows.rows(); i++)
	{
		cout << "Row " << i + 1 << ": " << rows[i];
	}
	cout << endl;
	for (int i = 0; i < cols.rows(); i++)
	{
		cout << "Col " << i + 1 << ": " << cols[i];
	}
	cout << endl;
	for (int i = 0; i < squares.rows(); i++)
	{
		cout << "Sqr " << i + 1 << ": " << squares[i];
	}
	cout << endl;
}

void board::clear()
// Mark all possible values as legal for each board entry
{
	for (int i = 1; i <= BoardSize; i++)
		for (int j = 1; j <= BoardSize; j++)
		{
			value[i - 1][j - 1] = Blank;
		}
}

int squareNumber(int i, int j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom.  Note that i and j each go from 1 to BoardSize
{
	// Note that (int) i/SquareSize and (int) j/SquareSize are the x-y
	// coordinates of the square that i,j is in.

	return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file.
{
	char ch;

	cols.resize(BoardSize, MaxValue);
	squares.resize(BoardSize, MaxValue);
	rows.resize(BoardSize, MaxValue);
	clear();

	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			fin >> ch;

			// If the read char is not Blank
			if (ch != '.')
				setCell(i, j, ch - '0');   // Convert char to int
		}
	}
}

void board::clearCell(int i, int j)
// Sets the value in the cell to blank, updates the conflict list to remove
// conflicts with this number in the column, row, and square
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
	{
		ValueType tmp = value[i - 1][j - 1] - 1;
		value[i - 1][j - 1] = Blank;
		cols[i - 1].at(tmp) = false;
		rows[j - 1].at(tmp) = false;
		squares[squareNumber(i, j) - 1].at(tmp) = false;
	}
	else
		throw rangeError("bad value in clearCell");
}

void board::setCell(int i, int j, int val)
// Sets the value in a cell. Throws exception if bad values
// are passed.
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize && val >= MinValue
		&& val <= MaxValue)
	{
		value[i - 1][j - 1] = val;
		cols[j - 1].at(val - 1) = true;
		rows[i - 1].at(val - 1) = true;
		int sqNum(squareNumber(i, j) - 1);
		squares[sqNum].at(val - 1) = true;

	}
	else
		throw rangeError("bad value in setCell");
}

ValueType board::getCell(int i, int j)
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
		return value[i - 1][j - 1];
	else
		throw rangeError("bad value in getCell");
}

bool board::isBlank(int i, int j)
// Returns true if cell i,j is blank, and false otherwise.
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
		throw rangeError("bad value in setCell");

	return (getCell(i, j) == Blank);
}

void board::print()
// Prints the current board.
{
	for (int i = 1; i <= BoardSize; i++)
	{
		if ((i - 1) % SquareSize == 0)
		{
			cout << " -";
			for (int j = 1; j <= BoardSize; j++)
				cout << "---";
			cout << "-";
			cout << endl;
		}
		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j - 1) % SquareSize == 0)
				cout << "|";
			if (!isBlank(i, j))
				cout << " " << getCell(i, j) << " ";
			else
				cout << "   ";
		}
		cout << "|";
		cout << endl;
	}

	cout << " -";
	for (int j = 1; j <= BoardSize; j++)
		cout << "---";
	cout << "-";
	cout << endl;
}

int main()
{

	ifstream fin;

	// Read the sample grid from the file.
	string fileName = "data/sudoku1.txt";

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	try
	{
		board b1(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			b1.initialize(fin);
			b1.print();
			b1.printConflicts();

			if (b1.isSolved())
			{
				cout << "The board has been solved!" << endl;
			}
			else
			{
				cout << "The board has NOT been solved." << endl;
			}
		}
	}
	catch (indexRangeError &ex)
	{
		cout << ex.what() << endl;
		exit(1);
	}
}