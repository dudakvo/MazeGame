#include <iostream>
#include <string>
#include <array>
#include <random>
#include "./def.h"
#include <time.h>
#include <stdlib.h>
#include <vector>

// const int cMazeColumns = 12;
// const int cMazeRows = 8;

// const char cEmptySymbol = ' ';
// const char cWallSymbol = 'X';
// const char cCharacterSymbol = '@';
// const char cExitSymbol = '#';

// Checks if user want so play
// Return true if user wants to play; false otherwise
bool doesUserWantsToPlay()
{
    bool rResult = false;

    std::cout << "Maze Game" << std::endl;

    while (true)
    {
        std::cout << "Do you want to play? (1 - yes, 0 - no):";

        std::string answer;
        std::cin >> answer;

        if ((answer == "1") || (answer == "0"))
        {
            rResult = (answer == "1");
            break;
        }

        std::cout << "Sorry, I did not understand." << std::endl;
    }

    return rResult;
}


void randomSymbolGeneration (Maze &prMaze, char cSymbol)
{
   int rowMaze, columnMaze;
  // srand(time(NULL));
   do
   {
     static std::random_device rd;
     static std::mt19937 mt{rd()};
     static std::uniform_int_distribution<int> rowGenerator = std::uniform_int_distribution<int>(2, cMazeRows - 2);
     static std::uniform_int_distribution<int> columnGenerator = std::uniform_int_distribution<int>(2, cMazeColumns - 2);
     rowMaze=rowGenerator(mt);
     columnMaze=columnGenerator(mt);
	
//	rowMaze = 2 + rand() % (cMazeRows - 2);
//	columnMaze = 2 + rand() % (cMazeColumns -2);

     if(scanForCharS(prMaze, cEmptySymbol, rowMaze, columnMaze))
     {
        prMaze[rowMaze][columnMaze] = cSymbol;
	return;
     }
    }
    while (true);
}

biasMaze (Maze &prMaze) // generation maze  by method of bias 
{
	int course;
	srand(time(NULL));
	for (int row = 1; row < cMazeRows; row +=2)
	
	{
//	int row{1};
	//row=1;
	   for (int column = 1; column < (cMazeColumns-2); column += 2)
	   {
 	     if ((row-2) < 0)
	    	prMaze[row][column+1] = cEmptySymbol;
	     else
	     {
		course = 1 + rand() % 2;
		if(course == 1)
			prMaze[row-1][column]=cEmptySymbol;
		if (course ==2)
			if ((column+2)>cMazeColumns)
			 	prMaze[row-1][column]=cEmptySymbol;
			else
				prMaze[row][column+1]=cEmptySymbol;
	     }	
	   }
	}    
}

void sidewinderMaze (Maze &prMaze)
{
  int course, cellsRoom;
  int randomCell;
  std::vector <int> room;
  srand(time(NULL));
  for ( int row=1; row<cMazeRows; row+=2)
  {
	for (int column=1; column>cMazeColumns; column+=2)
	{
		while (true)
		{
			cellsRoom=1 + rand() % 3;
			if (((cellsRoom*2)+column)<cMazeColumns)  //????
				break;
		} 

		for (int cell=column; cell<(column+(cellsRoom*2)-1); cell+=2)
		{
			room.push_back(cell);
			prMaze[row][cell+1]=cEmptySymbol;
		}
		randomCell = rand() % cellsRoom;
		course = 1 + rand () % 2; 
		if (((prMaze[row][room[randomCell]+1]==cEmptySymbol) || 
				(room[randomCell]+2)>cMazeColumns)&&(row-2)>0)
		{
			prMaze[row-1][room[randomCell]];
		}
		if (((room[randomCell]+2)>cMazeColumns) && (row-2)>0)
		{
			prMaze[row-1][room[randomCell]]=cEmptySymbol;
		}
		else
		{
			if(1==course)
				prMaze[row-1][room[randomCell]]==cEmptySymbol;
			if (2==course)
				prMaze[row][room[randomCell]+1];
		}
		column += (cellsRoom*2);
		room.clear();
	}
  }


}

// Generates maze
// Parameters:
//       maze - reference to maze field that will be modified
//              (walls added, added character and exit)
void generateMaze(Maze &prMaze)
{
//    int course;
    for (int row = 0; row < cMazeRows; row++)   // generation walls
    {
        for (int column = 0; column < cMazeColumns; column++)
        {
            if ((row == 0) || (row == cMazeRows - 1) || (column == 0) || (column == cMazeColumns - 1) || ((row % 2) ==0) 
			 									|| ((column % 2) == 0))
            {
                prMaze[row][column] = cWallSymbol;
            }
            else
            {
                prMaze[row][column] = cEmptySymbol;
            }
        }
    }
    //=================================================
    //======generator doors ===========================

    biasMaze(prMaze);
  //  sidewinderMaze(prMaze);
 
    // Place character - always at positon 1,1
	 randomSymbolGeneration (prMaze, cKeySymbol);

    prMaze[1][1] = cCharacterSymbol;

    // Place exit randomly

    randomSymbolGeneration (prMaze, cExitSymbol);
   
   
}

// Draws maze onto screen
// Parameters:
//      maze - maze field to draw
void drawMaze(const Maze &maze)
{
    for (int row = 0; row < cMazeRows; row++)
    {
        for (int column = 0; column < cMazeColumns; column++)
        {
            std::cout << maze[row][column];
        }

        std::cout << std::endl;
    }
}

// Searches given char on the given maze field,
// returns if found and filling row and column with coordinates
// Parameters:
//      maze - maze field where character will be serched
//      charToFind - char that should be found on maze field
//      prCharRow - reference to row variable for which will be assigned row position
//      prCharColumn - reference to column variable for which will be assigned column position
// Returns true if found; false otherwise.
bool scanForChar(const Maze &maze,
                 const char charToFind,
                 int &prCharRow,
                 int &prCharColumn)
{
    for (int row = 0; row < cMazeRows; row++)
    {
        for (int column = 0; column < cMazeColumns; column++)
        {
            if (maze[row][column] == charToFind)
            {
                prCharRow = row;
                prCharColumn = column;
                return true;
            }
        }
    }

    return false;
}

bool scanForCharS(const Maze &maze,
                 const char charToFind,
                 int prCharRow,
                 int prCharColumn)
{
    for (int row = 0; row < cMazeRows; row++)
    {
        for (int column = 0; column < cMazeColumns; column++)
        {
            if (maze[row][column] == charToFind)
            {
                prCharRow = row;
                prCharColumn = column;
                return true;
            }
        }
    }

    return false;
}

// Moves character according to given command and retuns eaten symbol (if any)
// Parameters:
//      row - character row position
//      column - character column position
//      command - test string with given command ("l" - left, "r" - right, "u" - up, "d" - down)
//      prMaze - reference to maze field; will be modified as a result of command execution
char moveAndGather(int row,
                   int column,
                   const std::string &command,
 		   const bool keyTicket,
                   Maze  &prMaze)
{
    char rCharMovedOnto = cEmptySymbol;

    // Take character out from map
    prMaze[row][column] = cEmptySymbol;

    if (command == "l")
    {
        rCharMovedOnto = prMaze[row][column - 1];

        if ((rCharMovedOnto != cWallSymbol)&&((rCharMovedOnto != cExitSymbol) || keyTicket))
        {
            column--;
        }
    }

    if (command == "r")
    {
        rCharMovedOnto = prMaze[row][column + 1];

        if ((rCharMovedOnto != cWallSymbol) && (rCharMovedOnto != cExitSymbol) || keyTicket)
        {
            column++;
        }
    }

    if (command == "u")
    {
        rCharMovedOnto = prMaze[row - 1][column];

        if ((rCharMovedOnto != cWallSymbol) && (rCharMovedOnto != cExitSymbol) || keyTicket)
        {
            row--;
        }
    }

    if (command == "d")
    {
        rCharMovedOnto = prMaze[row + 1][column];

        if ((rCharMovedOnto != cWallSymbol) && (rCharMovedOnto != cExitSymbol) || keyTicket)
        {
            row++;
        }
    }

    // Place character back with new position
    prMaze[row][column] = cCharacterSymbol;

    return rCharMovedOnto;
}

// Prints message to player.
// Parameters:
//      message - text message to player
void gameMessage(const std::string& message)
{
    std::cout << std::endl << message << std::endl << std::endl;
}

// Moves character and check if exit was found as a result of that move.
// Parameters:
//      prMaze - reference to maze field; will be modified while player moves.
bool moveCharacterAndCheckIfExitFound(Maze &prMaze, bool &keyTicket)
{
    bool rExitFound = false;
//    bool keyTicket == false;

    int charRow = 1;
    int charColumn = 1;
    if (scanForChar(prMaze, cCharacterSymbol, charRow, charColumn))
    {
        std::cout << "Command (l - left, r - right, u - up, d- down):";
        std::string command;
        std::cin >> command;

        const char charMovedOnto = moveAndGather(charRow, charColumn, command, keyTicket, prMaze);

        if (charMovedOnto == cWallSymbol)
        {
            gameMessage("Cannot move here!");
        }
        
        if (charMovedOnto == cKeySymbol)
        {
	   keyTicket = true;
	   gameMessage ("You have key!!!");
 	}

        if ((charMovedOnto == cExitSymbol)&&keyTicket)
        {
            gameMessage("Exit found!");
            rExitFound = true;
        }
    }
    else
    {
        gameMessage("Error: cannot find char!");
    }

    return rExitFound;
}

// Executes one round of the game
void playMazeGame()
{
    
    bool keyTicket = false;
    std::cout << "LETS START!" << std::endl;

    Maze maze;
    generateMaze(maze);

    do
    {
        drawMaze(maze);
    }
    while (!moveCharacterAndCheckIfExitFound(maze, keyTicket));
}

int main()
{
    while (doesUserWantsToPlay())
    {
        playMazeGame();
    }
}
