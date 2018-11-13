// Declarations and functions for project #4
#include <iostream>
#include <fstream>
#include "board.h"

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
				std::cout << "The board has been solved!" << endl;
			}
			else
			{
				std::cout << "The board has NOT been solved." << endl;
			}
		}
	}
	catch (indexRangeError &ex)
	{
		std::cout << ex.what() << endl;
		exit(1);
	}
}