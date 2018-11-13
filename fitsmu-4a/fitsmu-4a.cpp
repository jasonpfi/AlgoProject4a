/**
* Team: fitsmu
* Jason Fitch
* Sam Smucny
*
* fitsmu-4a.cpp: Main program file
*/

#include <iostream>
#include <fstream>
#include "board.h"

int main()
// main method of program
{
	// declare input files to read
	ifstream fin;
	string files[] = { "data/sudoku1.txt", "data/sudoku2.txt", "data/sudoku3.txt" };

	// cycle through each of the files
	for (int i = 0; i < 3; i++)
	{
		// Read the grid from the file.
		string fileName = files[i];
		std::cout << "Reading " << fileName << std::endl;

		fin.open(fileName.c_str());
		if (!fin)
		{
			cerr << "Cannot open " << fileName << std::endl;
			exit(1);
		}

		try
		{
			board b1(SquareSize);

			while (fin && fin.peek() != 'Z')
			{
				// initialize board and print information to console
				b1.initialize(fin);
				b1.print();
				b1.printConflicts();

				// check if the board is solved
				if (b1.isSolved())
				{
					std::cout << "The board has been solved!" << std::endl;
				}
				else
				{
					std::cout << "The board has NOT been solved." << std::endl;
				}
			}
		}
		catch (indexRangeError &ex)
		{
			std::cout << ex.what() << std::endl;
			fin.close();
			exit(1);
		}

		std::cout << std::endl << std::endl;
		fin.close();
	}
}