 /*
 Version: V 3.0 MINESWEEPER [REMASTERED] 
 Description: This program implements the classic Minesweeper game. 
 In Minesweeper, players are presented with a grid of covered squares. 
 Some squares contain hidden mines, and the player's goal is to uncover all squares without detonating any mines. 
 Players can uncover squares one at a time, and each uncovered square reveals a number indicating how many adjacent squares contain mines. 
 The game ends when all safe squares are uncovered, or when a mine is detonated. This program allows players to navigate the game board and perform actions using the keyboard.
 Author: Julian Jedidiah Kyle Martin
 Section: S18A
 Last Modified: MARCH 31 2024 - 1:28 PM
 Acknowledgments: https://www.tutorialspoint.com/index.htm
                  "interface.c" library provided by Sir Thomas Tiam-Lee
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <unistd.h>
#include <time.h>
#include "interface.c"

#define MAX 100
#define MAX1 100
#define RecentGames 3

typedef char String[50];
typedef char name[21];
typedef char LevelNames[70];

struct Game
{
    String GameType;
    String Outcome;
    int row;
    int columns;
    int AdjacentBombs[MAX][MAX];
    char cBoardFlag[MAX][MAX];
};

struct Profile
{   
    name PlayerName;
    int numberOfGamesPlayed;
    int numberOfGamesLostClassic;
    int numberOfGamesLostCustom;
    int numberOfGamesWonClassic;
    int numberOfGamesWonCustom;
};

/* <This function displays the opening header at the start of the game>
 @return: void
 Pre-condition: None */

void DisplayOpeningHeader() 
{   
    printf("\n\n\n");
    printf("     |  \\/  |_   _| \\ | |  ____|/ ____\\ \\        / /  ____|  ____|  __ \\|  ____|  __ \\  \n");
    printf("     | \\  / | | | |  \\| | |__  | (___  \\ \\  /\\  / /| |__  | |__  | |__) | |__  | |__) | \n");
    printf("     | |\\/| | | | | . ` |  __|  \\___ \\  \\ \\/  \\/ / |  __| |  __| |  ___/|  __| |  _  /  \n");
    printf("     | |  | |_| |_| |\\  | |____ ____) |  \\  /\\  /  | |____| |____| |    | |____| | \\ \\  \n");
    printf("     |_|  |_|_____|_| \\_|______|_____/    \\/  \\/   |______|______|_|    |______|_|  \\_\\ \n");
    printf("\n");
    iSetColor(3);
    printf("                                        Remastered");
    iSetColor(0);
    printf("\n\n");
}

/* <This function display the Opening Screen Menu>
 @return: Void
 Pre-condition: None */

void DisplayOpenScreen()
{
    printf("\n");
    printf("                                        Welcome to: ");
    DisplayOpeningHeader(); 

    printf("\n\n");

    printf("                                      [1] Start game\n");
    printf("                                      [2] Create Level\n");
    printf("                                      [3] View Statistics\n");
    printf("                                      [4] Profile Menu\n");
    printf("                                      [5] Game Mechanics\n");
    printf("                                      [6] Quit\n");
    printf("\n\n");
    printf("                                      Enter: ");
}

/* <This function is a display what type of game the user wishes to play>
 @return: Void
 Pre-condition: None */

void DisplayChooseTypeOfGame() 
{  
    DisplayOpeningHeader();
    printf("\n\n");
    printf("                                      [1] Classic Game\n");
    printf("                                      [2] Custom Game\n");
    printf("                                      [3] Back");
    printf("\n\n");
    printf("                                      Enter: ");  
}

/* <This function displays a brief background and game mechanics of Minesweeper>
 @return: Void
 Pre-condition: None */

void GameMechanics() 
{
    DisplayOpeningHeader(); 
    printf("\n\n");
    printf("                                    Origins of Minesweeper:\n\n");
    printf("                 Programmed and designed by Robert Donner and Curt Johnson in 1989\n");
    printf("            Minesweeper is a classic computer game that was released as a part of Windows 3.1.\n");
    printf("        According to Cobbett (2009), Minesweeper is dubbed as the most successful game in history\n");
    printf("\n\n");
    printf("                                        Game Mechanics:\n\n");
    printf("            Clear a rectangular board containing hidden mines without revealing any of them.                \n");
    printf("    Minesweeper is played on a grid, and each square in the grid can either contain a mine or be empty.    \n");
    printf("                    The player can reveal squares by pressing [E] to inspect. \n");
    printf("    If a revealed square that contains a mine, the game ends, resulting in the player's loss.  \n");
    printf("If a revealed square does not contain a mine, it will display the number of adjacent squares containing mines. \n");
    printf(" Using this information, the player must deduce the locations of mines and mark them by pressing [F] to flag. \n");
    printf("        The amount of flags you only have is the amount mines there is in the grid, so flag wisely.\n");
    printf("                     The game is won when all non-mine squares are revealed. \n");
    printf("\n\n");
    printf("                                   ");
    system("pause");
    system("cls");
}

/* This function randomly plant bombs for classic game in easy mode
 @param Arr -  An array that is initialized as -2 for the cells that doesn't contain bombs and -1 for the cells that does contain a bomb
 @param row -  The number of rows in the array
 @param column - The number of columns of the array

 @return Void
 Pre-condition: Array must be initialized to -2 before storing the random generated bombs */

void PlantBombsEasy (int Arr[][MAX], int row, int column)
{
    int i, j; 
    int random; 
    int random1;
    int count = 1;

    srand(time(0)); // INITIALIZE THE SEED FOR RANDOM NUMBER GENERATOR
   
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            Arr[i][j] = -2; // INITIALIZES THE ARRAY TO -2
        }
    }


    while (count <= 10) // ITERATES UNTIL COUNT IS 10
    {
        random = rand() % row; // GENERATES RANDOM ROW 
        random1 = rand() % column; // GENERATES RANDOM COLUMN

        if (Arr[random][random1] != -1) 
        {
            Arr[random][random1] = -1;
            count++;
        }
    }
           
}

/* This function randomly plant bombs for classic game in easy mode
 @param Arr -  An array that is initialized as -2 for the cells that doesn't contain bombs and -1 for the cells that does contain a bomb
 @param row -  The number of rows in the array
 @param column - The number of columns of the array

 @return Void
 Pre-condition: Array must be initialized to -2 before storing the random generated bombs */

void PlantBombsDifficult (int Arr[][MAX], int row, int column)
{
    int i, j; 
    int random; 
    int random1;
    int count = 1;

    srand(time(0)); // INITIALIZE THE SEED FOR RANDOM NUMBER GENERATOR
   
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            Arr[i][j] = -2; // INITIALIZES THE ARRAY TO -2
        }
    }


    while (count <= 35) // ITERATES UNTIL COUNT IS 35
    {
        random = rand() % row; // GENERATES RANDOM ROW 
        random1 = rand() % column; // GENERATES RANDOM COLUMN

        if (Arr[random][random1] != -1)
        {
            Arr[random][random1] = -1;
            count++;
        }
    }
}

 /* This function counts the number of mines adjacent to the cell
 @param Arr - The array that holds the mines -1
 @param row - The y value in the array. Used for locating the cell 
 @param col - The x value in the array. Used for locating the cell 
 @param OrigRow - The number of row in the array
 @param OrigCol - The number of columns in the array
 ...
 @return The number of mines adjacent to the cell
 Pre-condition: Mines should be assigned as -1 */

int countAdjacentBombs (int Arr[][MAX], int row, int col, int OrigRow, int OrigCol)
{
    int count = 0;

    if (row - 1 >= 0 && Arr[row - 1][col] == -1) // UP
    {
        count++; 
    }

    if (row + 1 < OrigRow && Arr[row + 1][col] == -1) // DOWN
    {
        count++;
    }

    if (col - 1 >= 0 && Arr[row][col - 1] == -1) // LEFT
    {
        count++;
    }

    if (col + 1 <= OrigCol && Arr[row][col + 1] == -1) // RIGHT
    {
        count++;
    }

    if (row + 1 < OrigRow && col - 1 >= 0 && Arr[row + 1][col - 1] == -1) // LOWER LEFT
    {   
        count++;
    }   

    if (row + 1 < OrigRow && col + 1 < OrigCol && Arr[row + 1][col + 1] == -1) // LOWER RIGHT
    {
        count++;
    }

    if (row - 1 >= 0 && col - 1 >= 0 && Arr[row - 1][col - 1] == -1) // UPPER LEFT
    {
        count++;
    }

    if (row - 1 >= 0 && col + 1 < OrigCol && Arr[row - 1][col + 1] == -1) // UPPER RIGHT
    {
        count++;
    }
    

    return count;
}

 /* This function executes a recursion that checks if the cells are safe (number of mines adjacent to the cell is 0) achieving a cascading effect
 @param Arr - The integer array that holds the mines (-1)
 @param Flag - The character array that holds the flags
 @param row - The y value in the array. Used for locating the cell 
 @param col - The x value in the array. Used for locating the cell 
 @param TileCounter - A pointer parameter that accepts an integer which counts the number of tiles revealed 
 @param OrigRow - The number of rows in the array
 @param OrigCol - The number of columns in the array 
 
 @return Void
 Pre-condition: Mines should be assigned as -1 */

void CascadeBombs(int Arr[][MAX], char Flag[][MAX], int row, int columns, int *TileCounter, int OrigRow, int OrigCol)
{
    if (row >= 0 && row < OrigRow && columns >= 0 && columns < OrigCol && Flag[row][columns] != 'F' && Arr[row][columns] == -2)
    {
    
        Arr[row][columns] = countAdjacentBombs(Arr, row, columns, OrigRow, OrigCol); // REVEALS TILE

        if (Arr[row][columns] == 0)
        {
            (*TileCounter)++;

            CascadeBombs(Arr, Flag, row - 1, columns, TileCounter, OrigRow, OrigCol);
            CascadeBombs(Arr, Flag, row + 1, columns, TileCounter, OrigRow, OrigCol);
            CascadeBombs(Arr, Flag, row, columns - 1, TileCounter, OrigRow, OrigCol);  // RECURSIVE CALLS FOR CASCADING BOMBS
            CascadeBombs(Arr, Flag, row, columns + 1, TileCounter, OrigRow, OrigCol);
            CascadeBombs(Arr, Flag, row - 1, columns - 1, TileCounter, OrigRow, OrigCol);
            CascadeBombs(Arr, Flag, row - 1, columns + 1, TileCounter, OrigRow, OrigCol);
            CascadeBombs(Arr, Flag, row + 1, columns - 1, TileCounter, OrigRow, OrigCol);
            CascadeBombs(Arr, Flag, row + 1, columns + 1, TileCounter, OrigRow, OrigCol);
        }
    }
}

 /* This function prints the board for the classic mode - easy
 @param Arr - The integer array that holds the mines (-1)
 @param Flag - The character array that holds the flags
 @param row - The number of rows in the array
 @param columns - The number of columns in the array
 @param cursorRow - The y value in the array. Used for locating the cell 
 @param cursorColumns - The x value in the array. Used for locating the cell

 @return Void
 Pre-condition: Mines should be assigned as -1 */

void PrintBoard(int Arr[][MAX], char Flag[][MAX], int row, int columns, int cursorRow, int cursorColumn)
{
    int space;
    int pad = 11;
    int i, j;

    system("CLS");
    printf("\t\t\t\t  ");
        for (i = 0; i < columns; i++)
            printf("  %d", i); // COLUMNS INDICES

        printf("\n");
        for (i = 0; i < row; i++)
        {
            for (space = 0; space < pad; space++) {
                printf("   "); // PADS THE BOARD FOR OUTPUT
            }

            printf("%d", i ); // ROW INDICES

            for (j = 0; j < columns; j++)
            {
                if (i == cursorRow && j == cursorColumn)
                {
                    iSetColor(1);
                    printf("  %c",  254);
                    iSetColor(0);
                }
                else if (Flag[i][j] == 'F') 
                {
                    iSetColor(4);
                    printf("  %c", Flag[i][j]);
                    iSetColor(0);
                }
                else if (Arr[i][j] == 0)
                {
                    printf("  %c", '_');
                }
                else if (Arr[i][j] >= 0 && Arr[i][j] <= 8)
                {
                    printf("  %d", Arr[i][j]);
                }
                else 
                {
                    printf("  %c", 254);
                }
            }
            printf("\n");
        }
}

 /* This function prints the board for the classic mode - difficult
 @param Arr - The integer array that holds the mines (-1)
 @param Flag - The character array that holds the flags
 @param row - The number of rows in the array
 @param columns - The number of columns in the array
 @param cursorRow - The y value in the array. Used for locating the cell 
 @param cursorColumns - The x value in the array. Used for locating the cell

 @return Void
 Pre-condition: Mines should be assigned as -1 */

void PrintBoardDifficult(int Arr[][MAX], char Flag[][MAX], int row, int columns, int cursorRow, int cursorColumn)
{
    int space;
    int pad = 9;
    int i, j;

    system("CLS");
    printf("\t\t\t    ");
        for (i = 0; i < columns; i++)
            printf(" %2d", i); // COLUMN INDICES

        printf("\n");
        for (i = 0; i < row; i++)
        {
            for (space = 0; space < pad; space++) {
                printf("   "); // PADS THE BOARD FOR OUTPUT
            }

            printf("%d", i ); // ROW INDICES

            for (j = 0; j < columns; j++)
            {
                if (i == cursorRow && j == cursorColumn)
                {
                    iSetColor(1);
                    printf("  %c",  254);
                    iSetColor(0);
                }
                else if (Flag[i][j] == 'F') 
                {
                    iSetColor(4);
                    printf("  %c", Flag[i][j]);
                    iSetColor(0);
                }
                else if (Arr[i][j] == 0)
                {
                    printf("  %c", '_');
                }
                else if (Arr[i][j] >= 0 && Arr[i][j] <= 8)
                {
                    printf("  %d", Arr[i][j]);
                }
                else 
                {
                    printf("  %c", 254);
                }
            }
            printf("\n");
        }
}

 /* This function prints the board for the custom mode 
 @param Arr - The integer array that holds the mines (-1)
 @param Flag - The character array that holds the flags
 @param row - The number of rows in the array
 @param columns - The number of columns in the array
 @param cursorRow - The y value in the array. Used for locating the cell 
 @param cursorColumns - The x value in the array. Used for locating the cell

 @return Void
 Pre-condition: Mines should be assigned as -1 */

void PrintBoardCustom(int Arr[][MAX], char Flag[][MAX], int row, int columns, int cursorRow, int cursorColumn)
{
    int space;
    int pad = 11;
    int i, j;

        system("CLS");
        if (columns >= 5 && columns <= 9)
        {
            printf("\t\t        ");
            for (i = 0; i < columns; i++)
                printf("  %d", i);

            printf("\n");
        }
        else{                                   // COLUMN INDICES
            printf("\t\t\t");
            for (i = 0; i < columns; i++)
            printf(" %2d", i);

            printf("\n");
        }

        for (i = 0; i < row; i++)
        {
            for (space = 0; space < pad; space++) {
                printf("  ");   // PADS THE BOARD FOR OUTPUT
            }  

            if (i <= 9)
            {
                printf(" ");
            }

            printf("%d", i); // ROW INDICES


            for (j = 0; j < columns; j++)
            {
                if (i == cursorRow && j == cursorColumn)
                {
                    iSetColor(1);
                    printf("  %c",  254);
                    iSetColor(0);
                }
                else if (Flag[i][j] == 'F')
                {
                    iSetColor(4);
                    printf("  %c", Flag[i][j]);
                    iSetColor(0);
                }
                else if (Arr[i][j] == 0)
                {
                    printf("  %c", '_');
                }
                else if (Arr[i][j] >= 0 && Arr[i][j] <= 8)
                {
                    printf("  %d", Arr[i][j]);
                }   
                else 
                {
                    printf("  %c", 254);
                }
            }
            printf("\n");
        }
}

 /* This functions updates and writes the contents of the player's data in a text file 
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structre Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots

 @return Void
 Pre-condition: User must be playing the game*/

void UpdateSavedProfile(struct Profile *IGN, struct Game Games[])
{
    FILE *fp;
    char Path[30] = "Profiles\\";
    char Temp[30];

    strcpy(Temp, Path);
    strcat(Temp, IGN->PlayerName);
    fp = fopen(Temp, "w"); // OPENS THE FILE FOR WRITING

    if (fp == NULL)
    {
        printf("Error in accessing file!\n");
    }

    fprintf(fp, "%d", IGN->numberOfGamesPlayed);
    fprintf(fp, "\n");
    fprintf(fp, "%d %d %d %d", IGN->numberOfGamesWonClassic, IGN->numberOfGamesLostClassic, IGN->numberOfGamesWonCustom, IGN->numberOfGamesLostCustom);
    fprintf(fp, "\n"); // WRITES CONTENTS ON THE FILE
    fprintf(fp,"%s %s %s %s %s %s", Games[0].GameType, Games[0].Outcome, Games[1].GameType, Games[1].Outcome, Games[2].GameType, Games[2].Outcome);
    fprintf(fp, "\n");

    fclose(fp); 
}

/* This function clears the index of an array of struct Game
 @param struct Game Games - An array of structre Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots
 @param Index - The index of that needs to be cleared

 @return Void
 Pre-condition: User must be playing the game*/

void ClearSnap(struct Game Games[], int Index)
{
    int i, j; 

    for (i = 0; i < Games[Index].row; i++)
    {
        for (j = 0; j < Games[Index].columns; j++)
        {
            Games[Index].AdjacentBombs[i][j] = 0; 
            Games[Index].cBoardFlag[i][j] = '\0';
        }
    }

    Games[Index].row = 0;
    Games[Index].columns = 0;
}

 /* This code saves a snapshot of the games played by the user to a file
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structre Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots

 @return Void
 Pre-condition: User must be playing the game*/

void GetSnapshots(struct Profile *IGN, struct Game Games[])
{
    int i, j;
    int count = 0;
    FILE *SnapshotFile;
    char Path[30] = "Snapshots\\";
    char Temp[30];

    strcpy(Temp, Path);
    strcat(Temp, IGN->PlayerName);

    SnapshotFile = fopen(Temp, "w");

    if (SnapshotFile == NULL)
    {
        printf("Error in accessing file!\n");
    }

    while (count < RecentGames)
    {
        fprintf(SnapshotFile, "%d %d\n", Games[count].row, Games[count].columns);

        for (i = 0; i < Games[count].row; i++)
        {
            for (j = 0; j < Games[count].columns; j++)
            {
                if (Games[count].AdjacentBombs[i][j] > 0)
                {
                    fprintf(SnapshotFile, "%d ", Games[count].AdjacentBombs[i][j]);
                }
                else if (Games[count].cBoardFlag[i][j] == 'F' || Games[count].cBoardFlag[i][j] == '*' || Games[count].cBoardFlag[i][j] == 'X')
                {
                    fprintf(SnapshotFile, "%c ", Games[count].cBoardFlag[i][j]);
                }
                else
                {
                    fprintf(SnapshotFile, "%c ", '.');
                }
            }
            fprintf(SnapshotFile, "\n");
        }
        fprintf(SnapshotFile, "\n");

        count++;
    }
    
    fclose(SnapshotFile);

}

 /* This function executes the classic mode - easy
 @param Arr - The 2D integer array that holds the mines (-1)
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of struct Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots

 @return Void
 Pre-condition: User must be playing */

void Easy(int Arr[][MAX], struct Profile *IGN, struct Game Games[])
{
    int i, j;
    int row = 0, column = 0;
    int TotalBombs = 10;
    int space;
    int pad = 11;
    int flag = 0; 
    int quit = 0;
    int count = 0;
    int countTiles = 0;
    int tiles;
    char Flag[MAX][MAX];
    int getIndex = IGN->numberOfGamesPlayed % RecentGames;

    if (IGN->numberOfGamesPlayed >= 3)
    {
        ClearSnap(Games, IGN->numberOfGamesPlayed % RecentGames);
    }

    Games[getIndex].row = 8;
    Games[getIndex].columns = 8;

    PlantBombsEasy(Arr, 8, 8);
    printf("\n");

    for (i = 0; i < 10; i++)
    { 
        for (j = 0; j < 15; j++) // INITIALIZE FLAG ARRAY
        {
            Flag[i][j] = '\0'; 
        }
    }

    do  
    {
        iHideCursor();
        PrintBoard(Arr, Flag, 8, 8, row, column);

        printf("\n");
        printf("Flags: %d\n", TotalBombs); 
        printf("_______________________________________________________________\n");
        printf("Controls: W [UP] A [LEFT] D [RIGHT] S [DOWN]\n");
        printf("[F] FLAG | [E] INSPECT | [Q] REMOVE FLAG | [ESC] QUIT\n");
        printf("_______________________________________________________________\n");
        printf("\n");
        tiles = (8 * 8) - 10; 

        if (count == 10 || countTiles == tiles)
        {
            flag = 1;
        }
        else 
        {    
            switch(getch())
            {
                case 'w':
                case 'W':
                    if (row > 0) 
                    row--;
                    break;
                case 's':
                case 'S':
                    if (row < 8 - 1) 
                    row++;
                    break;
                case 'a':
                case 'A':
                    if (column > 0) 
                    column--;
                    break;
                case 'd':
                case 'D':
                    if (column < 8 - 1) 
                    column++;
                    break;
                case 'f':
                case 'F': // CONDITIONS FOR FLAGGING
                    if (Arr[row][column] == -1 && !(Arr[row][column] >= 0) && Flag[row][column] != 'F' && TotalBombs != 0) 
                    {  
                        Flag[row][column] = 'F'; 
                        TotalBombs--;
                        count++;
                    }
                    else if (Arr[row][column] != -1 && !(Arr[row][column] >= 0) && Flag[row][column] != 'F' && TotalBombs != 0)
                    {
                        Flag[row][column] = 'F'; 
                        TotalBombs--;
                    }
                    else if (TotalBombs == 0)
                    {
                        printf("\nYou have no more flags\n\n");
                        getch();
                    }
                    else if (Arr[row][column] >= 0)
                    {
                        printf("\nYou inspected this already!\n\n");
                        getch();
                    }
                    else 
                    {
                        printf("\nYou flagged this already!\n\n");
                        getch();
                    }
                    break;
                case 'e':
                case 'E': // CONDITIONS FOR INSPECTION
                    if (Arr[row][column] == -1 && Flag[row][column] != 'F')
                    {  
                        flag = 1;
                    }
                    else if (Arr[row][column] != -1 && Flag[row][column] != 'F')
                    {
                        int AdjacentBombs = countAdjacentBombs(Arr, row, column, 8, 8);

                        if (AdjacentBombs == 0)
                        {
                            CascadeBombs(Arr, Flag, row, column, &countTiles, 8, 8);
                        }
                        else 
                        {
                            Arr[row][column] = countAdjacentBombs(Arr, row, column, 8, 8);
                            countTiles++;
                        }
                    }
                    else 
                    {
                        printf("\n");
                        printf("Action cannot be performed\n");    
                        getch();
                    }
                    break;
                case 'q':
                case 'Q': // CONDITIONS FOR REMOVING FLAG
                    if (Flag[row][column] != 'F')
                    {
                        printf("\nYou haven't flagged this yet!\n\n");
                        getch();
                    }
                    else
                    {   
                        Flag[row][column] = '\0';
                        TotalBombs++;
                    }
                    break;
                case 27: // ESC key
                    printf("Are you sure you want to forfeit the game? This will result in a loss!\n"); 
                    printf("Press [ESC] to continue or any key to cancel forgeit: \n");
                    switch(getch())
                    {
                        case 27:  
                            quit = 1;
                            break;
                    }
                    break;
                default:
                    printf("Invalid input!\n");    
                    getch();
            }
        }
    } while (flag != 1 && quit != 1);

    system("CLS");
    printf("\n");
    
    if (count == 10 || countTiles == tiles)
    {
        printf("Congratulations! You won!\n");

        for (i = 0; i < Games[getIndex].row; i++)
        {
            for (j = 0; j < Games[getIndex].columns; j++)
            {
                if (Arr[i][j] > 0)
                {
                    Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                }
                else if (Arr[i][j] == -1)
                {
                    Games[getIndex].cBoardFlag[i][j] = 'X';
                }
            }
        }

        IGN->numberOfGamesWonClassic++;
        strcpy(Games[getIndex].Outcome, "WON");
        strcpy(Games[getIndex].GameType, "Classic");
        IGN->numberOfGamesPlayed++;

        GetSnapshots(IGN, Games);
    }
    else if (quit == 1)
    {
        printf("You forfeited the game!\n");

        for (i = 0; i < Games[getIndex].row; i++)
        {
            for (j = 0; j < Games[getIndex].columns; j++)
            {
                if (Arr[i][j] > 0)
                {
                    Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                }
                else if (Flag[i][j] == 'F')
                {
                    Games[getIndex].cBoardFlag[i][j] = Flag[i][j];
                }
            }
        }

        IGN->numberOfGamesLostClassic++;
        strcpy(Games[getIndex].Outcome, "LOST");
        strcpy(Games[getIndex].GameType, "Classic");
        IGN->numberOfGamesPlayed++;

        GetSnapshots(IGN, Games);
    }
    else 
    {
        printf("A mine exploded! Better luck next time :>\n");

        for (i = 0; i < Games[getIndex].row; i++)
        {
            for (j = 0; j < Games[getIndex].columns; j++)
            {
                if (Arr[i][j] == -1)
                {
                    if (i == row && j == column)
                    {
                        Games[getIndex].cBoardFlag[i][j] = '*';
                    }
                    else 
                    {
                        Games[getIndex].cBoardFlag[i][j] = 'X';
                    }
                }
                else if (Flag[i][j] == 'F')
                {
                    Games[getIndex].cBoardFlag[i][j] = Flag[i][j];
                }
                else if (Arr[i][j] > 0)
                {
                    Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                }
            }
        }

        IGN->numberOfGamesLostClassic++;
        strcpy(Games[getIndex].Outcome, "LOST");
        strcpy(Games[getIndex].GameType, "Classic");
        IGN->numberOfGamesPlayed++;

        GetSnapshots(IGN, Games);
    }

    printf("\n");

    for (i = 0; i < 8; i++)
    {
        for (space = 0; space < pad; space++) {
            printf("   ");
        }

        for (j = 0; j < 8; j++)
        {
            if (Arr[i][j] == -1)
            {
                printf("  %c", 'X');
            }
            else
            {
                printf("  %c", 254);
            }
        }
        printf("\n");
    }

    for (i = 0; i < 8; i++)
    { 
        for (j = 0; j < 8; j++) // RESET BOARD
        {
            Flag[i][j] = '\0'; 
        }
    }

    UpdateSavedProfile(IGN, Games);

    printf("\n");
    printf("                             ");
    system("pause");
    system("CLS");
}   

 /* This function executes the classic mode - difficult
 @param Arr - The 2D integer array that holds the mines (-1)
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structure Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots

 @return Void
 Pre-condition: User must be playing */

void Difficult(int Arr[][MAX], struct Profile *IGN, struct Game Games[])
{
    int i, j;
    int row = 0, column = 0;
    int TotalBombs = 35;
    int space;
    int pad = 9;
    int flag = 0; 
    int count = 0;
    int quit = 0;
    int countTiles = 0;
    int tiles;
    char Flag[MAX][MAX];
    int getIndex = IGN->numberOfGamesPlayed % RecentGames;

    if (IGN->numberOfGamesPlayed >= 3)
    {
        ClearSnap(Games, IGN->numberOfGamesPlayed % RecentGames);
    }

    Games[getIndex].row = 10;
    Games[getIndex].columns = 15;

    PlantBombsDifficult(Arr, 10, 15);

    printf("\n");

    for (i = 0; i < 10; i++)
    { 
        for (j = 0; j < 15; j++) // INITIALIZE FLAG ARRAY
        {
            Flag[i][j] = '\0'; 
        }
    }

    do  
    {
        iHideCursor();
        PrintBoardDifficult(Arr, Flag, 10, 15, row, column);

        printf("\n");
        printf("Flags: %d\n", TotalBombs); 
        printf("____________________________________________________________________________________\n");
        printf("Controls: W [UP] A [LEFT] D [RIGHT] S [DOWN]\n");
        printf("[F] FLAG | [E] INSPECT | [Q] REMOVE FLAG | [ESC] QUIT\n");
        printf("____________________________________________________________________________________\n");
        printf("\n");
        printf("\n");
        tiles = (10 * 15) - 35; 

        if (count == 35 || countTiles == tiles)
        {
            flag = 1;
        }
        else 
        {    
            switch(getch())
            {
                case 'w':
                case 'W':
                    if (row > 0) 
                    row--;
                    break;
                case 's':
                case 'S':
                    if (row < 10 - 1) 
                    row++;
                    break;
                case 'a':
                case 'A':
                    if (column > 0) 
                    column--;
                    break;
                case 'd':
                case 'D':
                    if (column < 15 - 1) 
                    column++;
                    break;
                case 'f':
                case 'F': // CONDITIONS FOR FLAGGING
                    if (Arr[row][column] == -1 && !(Arr[row][column] >= 0) && Flag[row][column] != 'F' && TotalBombs != 0)
                    {  
                        Flag[row][column] = 'F'; 
                        TotalBombs--;
                        count++;
                    }
                    else if (Arr[row][column] != -1 && !(Arr[row][column] >= 0) && Flag[row][column] != 'F' && TotalBombs != 0)
                    {
                        Flag[row][column] = 'F'; 
                        TotalBombs--;
                    }
                    else if (TotalBombs == 0)
                    {
                        printf("\nYou have no more flags\n\n");
                        getch();
                    }
                    else if (Arr[row][column] >= 0)
                    {
                        printf("\nYou inspected this already!\n\n");
                        getch();
                    }
                    else 
                    {
                        printf("\nYou flagged this already!\n\n");
                        getch();
                    }
                    break;
                case 'e':
                case 'E': // CONDITIONS FOR INSPECTION
                    if (Arr[row][column] == -1 && Flag[row][column] != 'F')
                    {
                        flag = 1;  
                    }
                    else if (Arr[row][column] != -1 && Flag[row][column] != 'F')
                    {
                        int AdjacentBombs = countAdjacentBombs(Arr, row, column, 10, 15);
                        
                        if (AdjacentBombs == 0)
                        {
                            CascadeBombs(Arr, Flag, row, column, &countTiles, 10, 15);
                        }
                        else 
                        {
                            Arr[row][column] = countAdjacentBombs(Arr, row, column, 10, 15);
                            countTiles++;
                        }
                    }
                    else 
                    {
                        printf("\n");
                        printf("Action cannot be performed\n");    
                        getch();
                    }
                    break;
                case 'q':
                case 'Q': // CONDITIONS FOR REMOVING FLAG
                    if (Flag[row][column] != 'F')
                    {
                        printf("\nYou haven't flagged this yet!\n\n");
                        getch();
                    }
                    else
                    {   
                        Flag[row][column] = '\0';
                        TotalBombs++;
                    }
                    break;
                case 27: // ESC key
                    printf("Are you sure you want to forfeit the game? This will result in a loss!\n"); 
                    printf("Press [ESC] to continue or any key to cancel forgeit: \n");
                    switch(getch())
                    {
                        case 27:  
                            quit = 1;
                            break;
                    }
                    break;
                default:
                    printf("Invalid input!\n");    
                    getch();
            }
        }
    } while (flag != 1 && quit != 1);

    system("CLS");
    printf("\n");
    
    if (count == 35 || countTiles == tiles)
    {
        printf("Congratulations! You won!\n");

        for (i = 0; i < Games[getIndex].row; i++)
        {
            for (j = 0; j < Games[getIndex].columns; j++)
            {
                if (Arr[i][j] > 0)
                {
                    Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                }
                else if (Arr[i][j] == -1)
                {
                    Games[getIndex].cBoardFlag[i][j] = 'X';
                }
            }
        }

        IGN->numberOfGamesWonClassic++;
        strcpy(Games[getIndex].Outcome, "WON");
        strcpy(Games[getIndex].GameType, "Classic");
        IGN->numberOfGamesPlayed++;

        GetSnapshots(IGN, Games);
    }
    else if (quit == 1)
    {
        printf("You forfeited the game!\n");

        for (i = 0; i < Games[getIndex].row; i++)
        {
            for (j = 0; j < Games[getIndex].columns; j++)
            {
                if (Arr[i][j] > 0)
                {
                    Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                }
                else if (Flag[i][j] == 'F')
                {
                    Games[getIndex].cBoardFlag[i][j] = Flag[i][j];
                }
            }
        }

        IGN->numberOfGamesLostClassic++;
        strcpy(Games[getIndex].Outcome, "LOST");
        strcpy(Games[getIndex].GameType, "Classic");
        IGN->numberOfGamesPlayed++;

        GetSnapshots(IGN, Games);
    }
    else 
    {
        printf("A mine exploded! Better luck next time :>\n");

        for (i = 0; i < Games[getIndex].row; i++)
        {
            for (j = 0; j < Games[getIndex].columns; j++)
            {
                if (Arr[i][j] == -1)
                {
                    if (i == row && j == column)
                    {
                        Games[getIndex].cBoardFlag[i][j] = '*';
                    }
                    else 
                    {
                        Games[getIndex].cBoardFlag[i][j] = 'X';
                    }
                }
                else if (Flag[i][j] == 'F')
                {
                    Games[getIndex].cBoardFlag[i][j] = Flag[i][j];
                }
                else if (Arr[i][j] > 0)
                {
                    Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                }
            }
        }

        IGN->numberOfGamesLostClassic++;
        strcpy(Games[getIndex].Outcome, "LOST");
        strcpy(Games[getIndex].GameType, "Classic");
        IGN->numberOfGamesPlayed++;

        GetSnapshots(IGN, Games);
    }

    printf("\n");

    for (i = 0; i < 10; i++)
    {
        for (space = 0; space < pad; space++) {
            printf("   ");
        }

        for (j = 0; j < 15; j++)
        {
            if (Arr[i][j] == -1)
            {
                printf("  %c", 'X');
            }
            else
            {
                printf("  %c", 254);
            }
        }
        printf("\n");
    }

    for (i = 0; i < 10; i++)
    { 
        for (j = 0; j < 15; j++) // reset board
        {
            Flag[i][j] = '\0'; 
        }
    }

    UpdateSavedProfile(IGN, Games);

    printf("\n");
    printf("                             ");
    system("pause");
    system("CLS");
}   

 /* This function initializes an integer 2D array with the value of -1 based on the coordinates corresponding to the locations where the character 'X' 
 is found in a given 2D character array
 @param Arr - The integer 2D array that holds the mines (-1)
 @param cBoard - The character 2D array that holds the characters 'X' corresponding to a mine
 @param rws - The number of rows in the 2D array
 @param clmns - The number of columns in the 2D array
 
 @return number of mines 
 Pre-condition: cBoard must be able to read the custom level file */

int setUpCustomBoard(int Arr[][MAX], char cBoard[][MAX], int rws, int clmns)
{ 
    int i, j;
    int count = 0;

    for (i = 0; i < rws; i++)
    {
        for (j = 0; j < clmns; j++)
        {
            if (cBoard[i][j] == 'X')
            {
                Arr[i][j] = -1;
                count++;
            }
            else 
            {
                Arr[i][j] = -2;
            }
        }
    }

    return count;
}

 /* This function executes the custom mode 
 @param Arr - The integer array that holds the mines (-1)
 @param cBoard - The character 2D array that holds the characters 'X' corresponding to a mine
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structre Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots

 @return Void
 Pre-condition: User must be playing */

void CustomGame(int Arr[][MAX], char cBoard[][MAX], struct Profile *IGN, struct Game Games[])
{
    char Path[30] = "Levels\\";
    char Flag[MAX][MAX];
    int row, columns;
    int gameRow = 0, gameColumns = 0;
    int TotalBombs;
    int tiles = 0;
    int flag = 0;
    int count = 0;
    int quit = 0;
    int countTiles = 0;
    int pad = 11;
    int space;
    int i, j;
    int bombs;
    int getIndex = IGN->numberOfGamesPlayed % RecentGames;
    String Temp;
    String Filename;
    LevelNames Levels;
    FILE *LevelFiles;

    LevelFiles = fopen("Levels\\LevelLists", "r");

    printf("                                    [CUSTOM LEVEL FILES]: \n\n");

    while (fgets(Levels, sizeof(Levels), LevelFiles))
    {
        printf("                                    %s\n", Levels);
    }

    printf("\n");
    printf("                                    Enter file name: ");
    scanf("%s", Filename);
    system("cls");
    strcpy(Temp, Path);
    strcat(Temp, Filename);
    FILE *fp;
    if ((fp = fopen(Temp, "r")) == NULL)
    {
        printf("\n\n");
        printf("                                     Level file does not exist!\n");
        printf("\n");
        printf("                                    ");
        system("pause");
        system("cls");
    }
    else 
    {
        printf("\n");
        fopen(Temp, "r");

        fscanf(fp, "%d", &row);
        fscanf(fp, "%d", &columns);

        for (i = 0; i < row; i++)
        {
            for (j = 0; j < columns; j++)
            {
                fscanf(fp, " %c", &cBoard[i][j]);
            }
            printf("\n");
        }

        fclose(fp);
        system("CLS");

        if (IGN->numberOfGamesPlayed >= 3)
        {
            ClearSnap(Games, IGN->numberOfGamesPlayed % RecentGames);
        }

        Games[getIndex].row = row;
        Games[getIndex].columns = columns;


        bombs = setUpCustomBoard(Arr, cBoard, row, columns);
        TotalBombs = bombs;
        tiles = (row * columns) - bombs;

        for (i = 0; i < 10; i++)
        { 
            for (j = 0; j < 15; j++) // INITIALIZE FLAG ARRAY
            {
                Flag[i][j] = '\0'; 
            }
        }

        do 
        {
            iHideCursor();
            PrintBoardCustom(Arr, Flag, row, columns, gameRow, gameColumns);
            printf("\n\n");

            printf("Flags: %d\n", TotalBombs); 
            printf("______________________________________________________________________________\n");
            printf("Controls: W [UP] A [LEFT] D [RIGHT] S [DOWN]\n");
            printf("[F] FLAG | [E] INSPECT | [Q] REMOVE FLAG | [ESC] QUIT\n");
            printf("_______________________________________________________________________________\n");
            printf("\n");
            printf("\n");
            if (count == bombs || countTiles == tiles)
            {
                flag = 1;
            }
            else 
            {
                switch(getch())
                {
                    case 'w':
                    case 'W':
                        if (gameRow > 0) 
                        gameRow--;
                        break;
                    case 's':
                    case 'S':
                        if (gameRow < row - 1) 
                        gameRow++;
                        break;
                    case 'a':
                    case 'A':
                        if (gameColumns > 0) 
                        gameColumns--;
                        break;
                    case 'd':
                    case 'D':
                        if (gameColumns < columns - 1) 
                        gameColumns++;
                        break;
                    case 'f':
                    case 'F': // CONDITIONS FOR FLAGGING
                        if (Arr[gameRow][gameColumns] == -1 && !(Arr[gameRow][gameColumns] >= 0) && Flag[gameRow][gameColumns] != 'F' && TotalBombs != 0)
                        {  
                            Flag[gameRow][gameColumns] = 'F'; 
                            TotalBombs--;
                            count++;
                        }
                        else if (Arr[gameRow][gameColumns] != -1 && !(Arr[gameRow][gameColumns] >= 0) && Flag[gameRow][gameColumns] != 'F' && TotalBombs != 0)
                        {
                            Flag[gameRow][gameColumns] = 'F'; 
                            TotalBombs--;
                        }
                        else if (TotalBombs == 0)
                        {
                            printf("\nYou have no more flags\n\n");
                            getch();
                        }
                        else if (Arr[gameRow][gameColumns] >= 0)
                        {
                            printf("\nYou inspected this already!\n\n");
                            getch();
                        }
                        else 
                        {
                            printf("\nYou flagged this already!\n\n");
                            getch();
                        }
                        break;
                    case 'e':
                    case 'E': // CONDITIONS FOR INSPECTION
                        if (Arr[gameRow][gameColumns] == -1 && Flag[gameRow][gameColumns] != 'F')
                        {
                            flag = 1;    
                        }
                        else if (Arr[gameRow][gameColumns] != -1 && Flag[gameRow][gameColumns] != 'F')
                        {
                           int AdjacentBombs = countAdjacentBombs(Arr, gameRow, gameColumns, row, columns);
                        
                            if (AdjacentBombs == 0)
                            {
                                CascadeBombs(Arr, Flag, gameRow, gameColumns, &countTiles, row, columns);
                            }
                            else 
                            {
                                Arr[gameRow][gameColumns] = countAdjacentBombs(Arr, gameRow, gameColumns, row, columns);
                                countTiles++;
                            }
                        }
                        else 
                        {
                            printf("\n");
                            printf("Action cannot be performed\n");    
                            getch();
                        }
                        break;
                    case 'q':
                    case 'Q': // CONDITIONS FOR REMOVING FLAG
                        if (Flag[gameRow][gameColumns] != 'F')
                        {
                            printf("\nYou haven't flagged this yet!\n\n");
                            getch();
                        }
                        else
                        {   
                            Flag[gameRow][gameColumns] = '\0';
                            TotalBombs++;
                        }
                        break;
                    case 27: // ESC key
                        printf("Are you sure you want to forfeit the game? This will result in a loss!\n"); 
                        printf("Press [ESC] to continue or any key to cancel forgeit: \n");
                        switch(getch())
                        {
                            case 27:  
                                quit = 1;
                                break;
                        }
                        break;
                    default:
                        printf("Invalid input!\n");    
                        getch();
                }
        
            } 
        } while (flag != 1 && quit != 1);

        system("CLS");

        if (count == bombs || countTiles == tiles)
        {
            printf("Congratulations! You won!\n");

            for (i = 0; i < Games[getIndex].row; i++)
            {
                for (j = 0; j < Games[getIndex].columns; j++)
                {
                    if (Arr[i][j] > 0)
                    {
                        Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                    }
                    else if (Arr[i][j] == -1)
                    {
                        Games[getIndex].cBoardFlag[i][j] = 'X';
                    }
                }
            }

            IGN->numberOfGamesWonCustom++;
            strcpy(Games[getIndex].Outcome, "Won");
            strcpy(Games[getIndex].GameType, "Custom");
            IGN->numberOfGamesPlayed++;

            GetSnapshots(IGN, Games);
        }
        else if (quit == 1)
        {
            printf("You forfeited the game!\n");

            for (i = 0; i < Games[getIndex].row; i++)
            {
                for (j = 0; j < Games[getIndex].columns; j++)
                {
                    if (Arr[i][j] > 0)
                    {
                        Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                    }
                    else if (Flag[i][j] == 'F')
                    {
                        Games[getIndex].cBoardFlag[i][j] = Flag[i][j];
                    }
                }
            }

            IGN->numberOfGamesLostCustom++;
            strcpy(Games[getIndex].Outcome, "LOST");
            strcpy(Games[getIndex].GameType, "Custom");
            IGN->numberOfGamesPlayed++;

            GetSnapshots(IGN, Games);
        }
        else 
        {
            printf("A mine exploded! Better luck next time :>\n");

            for (i = 0; i < Games[getIndex].row; i++)
            {
                for (j = 0; j < Games[getIndex].columns; j++)
                {
                    if (Arr[i][j] == -1)
                    {
                        if (i == gameRow && j == gameColumns)
                        {
                            Games[getIndex].cBoardFlag[i][j] = '*';
                        }
                        else 
                        {
                            Games[getIndex].cBoardFlag[i][j] = 'X';
                        }
                    }
                    else if (Flag[i][j] == 'F')
                    {
                        Games[getIndex].cBoardFlag[i][j] = Flag[i][j];
                    }
                    else if (Arr[i][j] > 0)
                    {
                        Games[getIndex].AdjacentBombs[i][j] = Arr[i][j];
                    }
                }
            }

            IGN->numberOfGamesLostCustom++;
            strcpy(Games[getIndex].Outcome, "LOST");
            strcpy(Games[getIndex].GameType, "Custom");
            IGN->numberOfGamesPlayed++;

            GetSnapshots(IGN, Games);
        }

        printf("\n");
        

        for (i = 0; i < row; i++)
        {
            if (columns >= 5 && columns <= 10 && row >= 5 && row <= 10)
            {
                for (space = 0; space <= 3; space++)
                {
                    printf("       ");
                }
            }
            else 
            {
                for (space = 0; space < pad; space++) 
                {
                    printf("  ");
                }
            }

            for (j = 0; j < columns; j++)
            {
                if (Arr[i][j] == -1)
                {
                    printf("  %c", 'X');
                }
                else
                {
                    printf("  %c", 254);
                }
            }
            printf("\n");
        }

        for (i = 0; i < row; i++)
        { 
            for (j = 0; j < columns; j++) // reset board
            {
                Flag[i][j] = '\0'; 
            }
        }

        UpdateSavedProfile(IGN, Games);

        printf("\n");
        printf("                             ");
        system("pause");
        system("CLS");
    }

}

/* This function serves as a menu system to what game mode the user wants to play
 @param Arr - The integer array that holds the mines (-1)
 @param cBoard - The character 2D array that holds the characters 'X' corresponding to a mine
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structure Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots

 @return Void
 Pre-condition: User must be playing */

void GameMode(int Arr[][MAX], char cBoard[][MAX], struct Profile *IGN, struct Game Games[])
{
    int Option; 

    DisplayChooseTypeOfGame();
    scanf("%d", &Option); 
    system("CLS");
    
    if (Option == 1)
    {   
        DisplayOpeningHeader();
        printf("\n\n");
        printf("                                      [1] Easy\n");
        printf("                                      [2] Difficult\n");
        printf("                                      [3] Back");
        printf("\n\n");
        printf("                                      Enter: ");  
        scanf("%d", &Option);
        system("CLS");
        if (Option == 1)
        {
            DisplayOpeningHeader();
            printf("\n\n");
            Easy(Arr, IGN, Games);
        }
        else if (Option == 2)
        {
            DisplayOpeningHeader();
            printf("\n\n");
            Difficult(Arr, IGN, Games);
        }
        else if (Option == 3)
        {   
            GameMode(Arr, cBoard, IGN, Games);
        }
        else 
        {
            printf("Invalid Input\n");
        }
    }
    else if (Option == 2) 
    {
        DisplayOpeningHeader();
        printf("\n\n");
        CustomGame(Arr, cBoard, IGN, Games);
    }
    else if (Option == 3)
    {
        system("CLS");
    }
    else 
    {
        printf("Invalid Input\n");
    }
}

/* This function initializes the 2D character array 
 @param cBoard - The character 2D array that holds the characters 'X' corresponding to a mine
 @param rows - The number of rows in the 2D array
 @param columns - The number of columns in the 2D array
 
 @return Void
 Pre-condition: User must be playing */

void initializeCustomBoard(char cBoard[][MAX], int rows, int columns)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            cBoard[i][j] = '.';
        }
    }
}

/* This function counts the number of mines in the character array
 @param cBoard - The character 2D array that holds the characters 'X' corresponding to a mine
 @param row - The number of rows in the 2D array
 @param columns - The number of columns in the 2D array
 
 @return number of mines in the character array
 Pre-condition: User must be playing */

int CountBombs(char cBoard[][MAX], int row, int columns)
{
    int i, j;
    int count = 0;

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (cBoard[i][j] == 'X')
            {
                count++;
            }
        }
    }

    return count++;
}

/* This function allows the user to create a custom board
 @param cBoard - The character 2D array that holds the characters 'X' corresponding to a mine
 @param row - The number of rows in the 2D array
 @param columns - The number of columns in the 2D array
 
 @return Void
 Pre-condition: User must be playing */

void createCustomBoard(char cBoard[][MAX], int rows, int columns)
{
    int i, j;
    int exit = 0;
    int pad = 11;
    int space;
    int row = 0, column = 0;
    int boardElements = rows * columns;
    int MineCounter = 0;

    initializeCustomBoard(cBoard, rows, columns);

    do 
    {
        system("CLS");

        if (columns >= 5 && columns <= 9)
        {
            printf("\t\t        ");
            for (i = 0; i < columns; i++)
                printf("  %d", i);

            printf("\n");
        }
        else{
            printf("\t\t\t");
            for (i = 0; i < columns; i++)
            printf(" %2d", i);

            printf("\n");
        }

        
        for (i = 0; i < rows; i++)
        {
            for (space = 0; space < pad; space++) {
                printf("  ");
            }  

            if (i <= 9)
            {
                printf(" ");
            }

            printf("%d", i);
            
            for (j = 0; j < columns; j++)
            {
                if (i == row && j == column)
                {
                    iSetColor(1);
                    printf("  %c",  254);
                    iSetColor(0);
                }
                else if (cBoard[i][j] == 'X')
                {
                    printf("  %c", cBoard[i][j]);
                }
                else 
                {
                    printf("  %c", 254);
                }
            }
            printf("\n");
        }
        printf("\n");
        printf("Mines: %d\n", MineCounter);
        printf("_____________________________________________________________________________\n");
        printf("Controls: W [UP] | A [LEFT] | D [RIGHT] | S [DOWN]\n");
        printf("[ENTER] ADD OR REMOVE MINES | [ESC] QUIT\n");
        printf("______________________________________________________________________________\n");

        switch(getch())
        {
            case 'w':
            case 'W':
                if (row > 0) 
                    row--;
                break;
            case 's':
            case 'S':
                if (row < rows - 1) 
                    row++;
                break;
            case 'a':
            case 'A':
                if (column > 0) 
                    column--;
                break;
            case 'd':
            case 'D':
                if (column < columns - 1) 
                    column++;
                break;
            case 13:
                if (cBoard[row][column] != 'X')
                {
                    cBoard[row][column] = 'X';
                    MineCounter++;
                }
                else if (cBoard[row][column] == 'X')
                {
                    cBoard[row][column] = '.';
                    MineCounter--;
                }
                break;
            case 27: // ESC key
                if (MineCounter == 0)
                {
                    printf("You didnt plant any mines!\n");
                    getch();
                }
                else if (MineCounter == boardElements)
                {
                    printf("You placed mines on all cells!\n");
                    getch();
                }
                else 
                {
                    printf("\n");
                    printf("Are you sure you want to save changes?\n");
                    printf("Press [ESC] to continue or any key to cancel creation: \n");
                    if (getch() == 27)
                    {
                        exit = 1;
                    }
                }
                break;
            default:
                printf("\n");
                printf("Invalid input!\n");    
                getch();    
                break;
        }

    } while (exit == 0);
}

/* This function allows the user to create a custom level file
 @param cBoard - The character 2D array that holds the characters 'X' corresponding to a mine
 
 @return Void
 Pre-condition: User must be playing */

void CreateLevel(char cBoard[][MAX])
{
    int i, j;
    String Filename;
    FILE *Levels;
    FILE *fp;
    int Mines;
    int row, column;
    int exit = 0;
    char Path[30] = "Levels\\";
    char Temp[30];

    do 
    {
        DisplayOpeningHeader();
        printf("\n\n");
        printf("                              Enter Desired File Name: "); 
        scanf("%s", Filename);
        printf("\n");
        strcpy(Temp, Path);
        strcat(Temp, Filename);
        if ((fp = fopen(Temp, "r")) != NULL)
        {
            printf("                     File name already exists! Please choose a different name\n");
            strcpy(Temp, " ");
            printf("\n");
            printf("                                  ");
            system("pause");
            system("cls");
        }
        else 
        {
            system("CLS");
            printf("\t                          Let's create a level!\n");
            printf("\n");
            printf("Enter row [5 - 10]: ");
            scanf("%d", &row);
            if (row >= 5 && row <= 10)
            {
                printf("Enter column [5 - 15]: ");
                scanf("%d", &column);
                if (column >= 5 && column <= 15)
                {
                    system("cls");

                    createCustomBoard(cBoard, row, column);

                    Mines = CountBombs(cBoard, row, column);

                    FILE *fp = fopen(Temp, "w");

                    fprintf(fp, "%d %d\n", row, column);

                    printf("\n");

                    for(i = 0; i < row; i++)
                    {
                        for (j = 0; j < column; j++)
                        {
                            fprintf(fp, "%c", cBoard[i][j]);
                        }
                        fprintf(fp, "\n");
                    }

                    fclose(fp);
                    strcpy(Temp, " ");

                    Levels = fopen("Levels\\LevelLists", "a");
                    
                    if (Mines >= 1 && Mines <= 10)
                    {
                        strcat(Filename, " | Beginner");
                        fprintf(Levels, "%s", Filename);
                        fprintf(Levels, "\n");
                    }
                    else if (Mines > 10 && Mines <= 30)
                    {
                        strcat(Filename, " | Intermediate");
                        fprintf(Levels, "%s", Filename);
                        fprintf(Levels, "\n");
                    }
                    else 
                    {
                        strcat(Filename, " | Expert");
                        fprintf(Levels, "%s", Filename);
                        fprintf(Levels, "\n");
                    }

                    fclose(Levels);

                    exit = 1;
                    system("cls");
                }
                else 
                {
                    system("CLS");
                    printf("                                        Invalid input!\n");
                    printf("                                ");
                    printf("Press any key to restart again...\n");
                    getch();
                    system("CLS");
                }
            }
            else 
            {   
                system("CLS");
                printf("                                        Invalid input!\n");
                printf("                                ");
                printf("Press any key to restart again...\n");
                getch();
                system("CLS");
            }
        }
    } while (exit == 0);
  
}

/* This function checks if the user's preferred In Game Name is valid 
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 
 @return 1 if IGN is valid 
 @return 2 if IGN is invalid
 Pre-condition: User must create a profile first */

int checkIGN(struct Profile IGN)
{
    int i;
    int countLetters = 0;

    for (i = 0; IGN.PlayerName[i] != '\0'; i++)
    {
        if (IGN.PlayerName[i] >= 'a' && IGN.PlayerName[i] <= 'z')
        {
            return 0;
        }
        countLetters++;
    }

    if (countLetters < 3 || countLetters > 20)
    {
        return 0;
    }
    else 
    {
        return 1;
    }
   
}

/* This function sorts the profiles in alphabetical order  
 @param struct Profile Player - A array of struct Profile Players that holds the blueprints of the player
 @param size - The number of players
 
 @return Void
 Pre-condition: Multiple players are created */

void SortProfiles(struct Profile Players[], int size)
{
    int i, j;
    int min;
    struct Profile Switch;

    for (i = 0; i < size; i++)
    {
        min = i;
        for (j = i + 1; j < size; j++)
        {
            if (strcmp(Players[j].PlayerName, Players[min].PlayerName) < 0) // SELECTION SORT ALGORITHM
            {
                min = j;
            }
        }

        if (min != i)
        {
            Switch = Players[min];
            Players[min] = Players[i];
            Players[i] = Switch;
        }
    }
}

/* This function reads the profiles in a text file 
 @param struct Profile Player - A array of struct Profile that holds the blueprints of the player
 
 @return number of current profiles listed
 Pre-condition: A player is created */

int LoadProfiles(struct Profile Players[])
{
    int countPlayers = 0;

    FILE *ListPlayers = fopen("Profiles\\LISTOFPLAYERS", "r");

    while (fscanf(ListPlayers, "%s", Players[countPlayers].PlayerName) == 1)
    {
        countPlayers++;
    }
    
    fclose(ListPlayers); 

    return countPlayers; // RETURNS NUMBER OF CURRENT PROFILES LISTED
}

/* This function allows the user to delete a profile 
 @param struct Profile Player - A array of struct Profile that holds the blueprints of the player
 
 @return void
 Pre-condition: A player is created and a player should not be currently logged in to the profile wished to be deleted*/

void DelProfile(struct Profile Players[], int* selectedPlayer, name DelProfile)
{
    int i, j; 
    char Path[30] = "Profiles\\";
    char Temp[50];
    char Temp1[50];
    char PathToSnaps[30] = "Snapshots\\";
    name TempCheck; 
    FILE *CurrentSavedProfile;
    FILE *TotalListPlayers;
    int countPlayers = 0;
    int TotalPlayers = LoadProfiles(Players);

    CurrentSavedProfile = fopen("Profiles\\SAVEDPROFILE", "r");

    if (CurrentSavedProfile == NULL)
    {
        printf("Error in accessing file!\n");
    }

    fscanf(CurrentSavedProfile, "%s", TempCheck); 
    fclose(CurrentSavedProfile);

    if (strcmp(TempCheck, DelProfile) == 0) // CHECKS CURRENT SAVED PROFILE
    {
       system("CLS");
       printf("                       Trouble deleting file. You are currently in game!\n");
       printf("\n");
       system("pause");
       system("CLS");   
    }
    else 
    {
        for (i = 0; i < TotalPlayers; i++)
        {
            if (strcmp(Players[i].PlayerName, DelProfile) == 0)
            {
                strcpy(Temp, Path);
                strcat(Temp, Players[i].PlayerName); // CONCATENATES PATH TO CREATE PROFILE FILES 

                strcpy(Temp1, PathToSnaps);
                strcat(Temp1, Players[i].PlayerName); // CONCATENATES PATH TO CREATHE SNAPSHOTS FILES
                                                            
                for (j = i; j < TotalPlayers - 1; j++)
                {
                    Players[j] = Players[j + 1]; // REARRANGES PLAYERS
                }

                if (*selectedPlayer >= i)
                {
                    (*selectedPlayer)--; // UPDATES THE SELECTED PLAYER'S INDEX
                }
            }
            else 
            {  
                countPlayers++; // COUNTS NUMBER OF PLAYERS 
            }
        }
    
        TotalListPlayers = fopen("Profiles\\LISTOFPLAYERS", "w"); // OVERWRITES CURRENT PLAYERS
        
        for (i = 0; i < countPlayers; i++)
        {
            fprintf(TotalListPlayers, "%s\n", Players[i].PlayerName); // STORES NEW FILE CONTENTS
        } 

        fclose(TotalListPlayers);

        if (remove(Temp) == 0 && remove(Temp1) == 0) // DELETES INDIVIDUAL FILE IN PROFILES AND SNAPS
        {   
            system("cls");
            printf("\n");
            printf("                                    Success deleting profile\n");        
            printf("                                    ");
            system("pause");
            system("CLS");    
        }
        else 
        {
            printf("\n");
            printf("                                      Profile doesn't exist!\n");
            printf("                                    ");
            system("pause");
            system("CLS");
        }
    }
    
}

/* This function initializes the structures for new players 
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structure Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots
 
 @return void
 Pre-condition: A player is created */

void InitializeGameFile(struct Profile *IGN, struct Game Games[])
{
    IGN->numberOfGamesPlayed = 0; IGN->numberOfGamesWonClassic = 0;
    IGN->numberOfGamesLostClassic = 0; IGN->numberOfGamesWonCustom = 0;  
    IGN->numberOfGamesLostCustom = 0; // INITIALIZES VALUES FOR PLAYER

    strcpy(Games[0].Outcome, "NULL"); strcpy(Games[0].GameType, "NULL");
    strcpy(Games[1].Outcome, "NULL"); strcpy(Games[1].GameType, "NULL"); 
    strcpy(Games[2].Outcome, "NULL"); strcpy(Games[2].GameType, "NULL");
}

/* This function clears the blueprint needed to create a snapshot 
 @param struct Game Games - An array of structure Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots
 
 @return Void
 Pre-condition: A player is created */

void ResetSnapshot(struct Game Games[])
{
    int i, j, k;

    for (i = 0; i < RecentGames; i++)
    {
        for (j = 0; j < Games[i].row; j++)
        {
            for (k = 0; k < Games[i].columns; k++)
            {
                Games[i].AdjacentBombs[j][k] = 0;
                Games[i].cBoardFlag[j][k] = '\0';
            }
        }
        Games[i].row = 0;
        Games[i].columns = 0;
        strcpy(Games[i].Outcome, ""); 
        strcpy(Games[i].GameType, "");
    }
}

/* This function reads the snapshots of the player in their own files 
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structure Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots
 
 @return void
 Pre-condition: A player must have their snapshots */

void RetrieveSnapshots(struct Profile *IGN, struct Game Games[])
{
    int i, j;
    int count = 0;
    FILE *SnapshotFile;
    char Path[30] = "Snapshots\\";
    char Temp[30];

    strcpy(Temp, Path);
    strcat(Temp, IGN->PlayerName);

    SnapshotFile = fopen(Temp, "r");

    if (SnapshotFile == NULL)
    {
        printf("Error in accessing file!\n");
    }

    while (count < RecentGames && !feof(SnapshotFile))
    {
        int row, columns;
        if (fscanf(SnapshotFile, "%d %d", &row, &columns) == 2)
        {
            Games[count].row = row;
            Games[count].columns = columns;

            for (i = 0; i < Games[count].row; i++)
            {
                for (j = 0; j < Games[count].columns; j++)
                {
                    int adjacentBomb;
                    char cBoardFlag;
                    if (fscanf(SnapshotFile, "%d", &adjacentBomb) == 1)
                    {
                        Games[count].AdjacentBombs[i][j] = adjacentBomb;
                    }
                    else if (fscanf(SnapshotFile, " %c", &cBoardFlag) == 1)
                    {
                        Games[count].cBoardFlag[i][j] = cBoardFlag;
                    }
                }
            }
            count++;
        }
    }
  
    fclose(SnapshotFile);

}

/* This function allows the user to create or select their own profiles
 @param InitialRun - Accepts a pointer to an integer that checks if the program is at its initial run
 @param struct Profile Player - A array of struct Profile Players that holds the blueprints of the player
 @param selectedPlayer - Accepts a pointer to an integer that assigns an index for each player
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structre Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots
 
 @return void
 Pre-condition: A player is created */

void CreateProfile (int *InitialRun, struct Profile Players[], int* selectedPlayer, struct Profile *IGN, struct Game Games[])
{
    int option;
    int exit = 0;
    int i; 
    int select;
    int countPlayers = LoadProfiles(Players);
    char Path[30] = "Profiles\\";
    char PathToSnaps[30] = "Snapshots\\";
    char Temp1[30];
    char Temp[30];
    name DeleteProfile;
    FILE *fp;
    FILE *ListPlayers;
    FILE *CurrentSavedProfile;
    FILE *Snaps;

    DisplayOpeningHeader();
    printf("                                       Profile Menu: "); 
    printf("\n\n");
    printf("                                    [1] Create profile\n");
    printf("                                    [2] Select \\ Change profile\n");
    printf("                                    [3] Delete profile\n");

    if (*InitialRun == 1)
    {
        printf("                                    [4] Back\n");
    }

    printf("\n\n");
    printf("                                    Enter: ");  
    scanf("%d", &option);
    if (option == 1)
    {
        if (countPlayers != 10)
        {
            do 
            {
                system("cls");
                DisplayOpeningHeader();
                printf("\n\n");
                printf("                                  Create a player profile \n");
                printf("                                 - UPPERCASE LETTERS ONLY\n");
                printf("                                       - No spaces\n");
                printf("                        - Minimum 3 characters - Maximum 20 characters\n");
                printf("\n\n");
                printf("                                 Enter In Game Name (IGN): ");
                printf("\n");
                printf("                                        ");
                scanf("%s", IGN->PlayerName);
                strcpy(Temp, Path);
                strcat(Temp, IGN->PlayerName);
                if ((fp = fopen(Temp, "r")) != NULL)
                {
                    printf("\n");
                    printf("                Account name already exists! Please choose a different name\n");
                    Temp[0] = '\0';
                    printf("\n");
                    printf("                                  ");
                    system("pause");
                    system("cls");
                }   
                else 
                {
                    if (checkIGN(*IGN) == 1)
                    {
                        *selectedPlayer = countPlayers;
                        Players[*selectedPlayer] = *IGN;
                    
                        fp = fopen(Temp, "w");

                        ResetSnapshot(Games); // FUNCTION CALL TO RESET BOARD SNAPSHOTS 
                        InitializeGameFile(IGN, Games); // CALL TO INITIALIZE VALUES 
        
                        fprintf(fp, "%d", IGN->numberOfGamesPlayed);
                        fprintf(fp, "\n");
                        fprintf(fp, "%d %d %d %d", IGN->numberOfGamesWonClassic, IGN->numberOfGamesLostClassic, IGN->numberOfGamesWonCustom, IGN->numberOfGamesLostCustom); // Formats file
                        fprintf(fp, "\n");

                        for (i = 0; i < 3; i++) 
                        {
                            if (strlen(Games[i].GameType) > 0 && strlen(Games[i].Outcome) > 0) 
                            {
                                fprintf(fp, "%s %s\n", Games[i].GameType, Games[i].Outcome);
                            }
                        }

                        fclose(fp); // CREATES SEPERATE FILE FOR EACH PLAYER

                        strcpy(Temp1, PathToSnaps);
                        strcat(Temp1, IGN->PlayerName);

                        Snaps = fopen(Temp1, "w"); // CREATES SNAPSHOT FILE FOR EACH PLAYER
                        fclose(Snaps);
                        
                        ListPlayers = fopen("Profiles\\LISTOFPLAYERS", "a");
                        fprintf(ListPlayers, "%s\n", IGN->PlayerName);  // APPENDS PLAYER LIST 
                        fclose(ListPlayers);

                        CurrentSavedProfile = fopen("Profiles\\SAVEDPROFILE", "w");
                        fprintf(CurrentSavedProfile, "%s\n", IGN->PlayerName); // STORES AS CURRENT SAVED PROFILE 
                        fclose(CurrentSavedProfile);

                        system("CLS");
                        DisplayOpeningHeader();
                        printf("\n\n");
                        printf("                                You are now logged in as: %s", IGN->PlayerName);
                        printf("\n\n");   
                        printf("                                ");
                        system("pause");
                        system("CLS");  
                        *InitialRun = 1;
                        exit = 1;
                    }
                }

            } while (exit == 0);
        }
        else 
        {
            system("CLS");
            printf("                        Number of profiles has exceeded. Delete some profile\n");
            printf("                                  ");
            system("pause");
            system("CLS");
        }

    }
    else if (option == 2)
    {
        if (countPlayers == 0)
        {
            system("CLS");
            printf("                                     LIST OF PLAYER PROFILES: ");
            printf("\n\n");            
            printf("                            No listed profiles. Create a profile first\n" );
            printf("\n");
            printf("                                 ");
            system("pause");
            system("cls");
        } 
        else 
        {
            system("CLS");

            FILE *LaunchProfile;

            LaunchProfile = fopen("Profiles\\SAVEDPROFILE", "r");
            fscanf(LaunchProfile, "%s", IGN->PlayerName); // READS CURRENT SAVED PROFILE 
            fclose(LaunchProfile);

            DisplayOpeningHeader(); 
            printf("\n\n");
            printf("                                      [CHOOSE PROFILE]\n\n");
            printf("                                   LIST OF PLAYER PROFILES: ");
            printf("\n\n");
        
            SortProfiles(Players, countPlayers); // SORTS PROFILE DISPLAY

            for (i = 0; i < countPlayers; i++)
            {
                printf("                                      %d. [%s]\n", i + 1, Players[i].PlayerName);
            }

            printf("\n");
            printf("                                 Enter Index number of profile: ");
            scanf("%d", &select);
            if (select <= countPlayers && select != 0 && strcmp(Players[select - 1].PlayerName, "") != 0) 
            {
                if (strcmp(Players[select - 1].PlayerName, IGN->PlayerName) != 0)
                {
                    ResetSnapshot(Games); // FUNCTION CALL TO RESET BOARD SCREENSHOTS
                    InitializeGameFile(IGN, Games); // CALL TO INITIALIZE VALUES 
        
                    *selectedPlayer = select - 1; // GETS INDEX OF SELECTED PROFILE 
                    *IGN = Players[*selectedPlayer];

                    printf("\n\n");
                    printf("                                  You are now logged in as: %s\n", IGN->PlayerName);

                    strcpy(Temp, Path);
                    strcat(Temp, IGN->PlayerName);

                    fp = fopen(Temp, "r");

                    if (fp == NULL)
                    {
                        printf("Error in accessing file!\n");
                    }

                    RetrieveSnapshots(IGN, Games);
                    
                    fscanf(fp, "%s %s %s %s %s %s", Games[0].GameType, Games[0].Outcome, Games[1].GameType, Games[1].Outcome, Games[2].GameType, Games[2].Outcome);
                    fclose(fp);

                    CurrentSavedProfile = fopen("Profiles\\SAVEDPROFILE", "w");
                    fprintf(CurrentSavedProfile, "%s\n", IGN->PlayerName); // OVERWRITES CURRENT SAVED PROFILE 
                    fclose(CurrentSavedProfile);

                    *InitialRun = 1;
                }
                else 
                {
                    printf("\n");
                    printf("                               You are already logged in to this profile!\n");
                }
            }
            else 
            {
                printf("\n");
                printf("                                   Player profile doesnt exist!\n");
            }
            printf("\n");
            printf("                                   ");
            system("pause");
            system("CLS");
        }
    }
    else if (option == 3)
    {
        if (countPlayers == 0)
        {
            system("CLS");
            printf("                                     LIST OF PLAYER PROFILES: ");
            printf("\n\n");            
            printf("                            No listed profiles. Create a profile first\n" );
            printf("\n");
            printf("                              ");
            system("pause");
            system("cls");
        } 
        else 
        {
            system("CLS");
            SortProfiles(Players, countPlayers);

            DisplayOpeningHeader(); 

            printf("\n\n");
            printf("                                      [DELETE PROFILE]\n\n");
            printf("                                   LIST OF PLAYER PROFILES: ");
            printf("\n\n");
            for (i = 0; i < countPlayers; i++)
            {
                printf("                                       %d. [%s]\n", i + 1, Players[i].PlayerName);
            }
            printf("\n");
            printf("                                    Enter name of profile: ");
            scanf("%s", DeleteProfile);
            DelProfile(Players, selectedPlayer, DeleteProfile); // FUNCTION CALL FOR DELETE PROFILE *SEE LINE 1238
        }
    }
    else if (option == 4 && *InitialRun == 1)
    {
        system("CLS");
    }
    else 
    {
        printf("\n");
        printf("                                           Invalid Input\n");
        printf("\n");
        printf("                                    ");
        system("pause");
        system("CLS");
    }
}

/* This function allows the players to view their own statistics
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structure Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots
 
 @return void
 Pre-condition: A player is created */

void ViewStatistics(struct Profile *IGN, struct Game Games[])
{
    char Path[30] = "Profiles\\";
    char Temp[30];
    int i, j;
    int count;
    FILE *fp;

    if (strcmp(IGN->PlayerName, "") == 0)
    {
        DisplayOpeningHeader();
        printf("\n\n");
        printf("                     NO STATS TO BE SHOWN! PLEASE CREATE OR SELECT A PROFILE\n");
        printf("\n\n");
    }
    else 
    {
        strcpy(Temp, Path);
        strcat(Temp, IGN->PlayerName);

        fp = fopen(Temp, "r");

        if (Temp == NULL)
        {
            printf("Error in accessing file!\n");
        }

        fscanf(fp, "%d %d %d %d %d", &IGN->numberOfGamesPlayed, &IGN->numberOfGamesWonClassic, &IGN->numberOfGamesLostClassic, &IGN->numberOfGamesWonCustom, &IGN->numberOfGamesLostCustom);
        fscanf(fp,"%s %s %s %s %s %s", Games[0].GameType, Games[0].Outcome, Games[1].GameType, Games[1].Outcome, Games[2].GameType, Games[2].Outcome);

        fclose(fp); // CREATES SEPERATE FILE FOR EACH PLAYER
    
        DisplayOpeningHeader();
        printf("\n\n");

        printf("                                [PLAYER STATISTICS FOR %s]\n\n", IGN->PlayerName);
        printf("                                            %d - %d\n\n", IGN->numberOfGamesWonClassic + IGN->numberOfGamesWonCustom, IGN->numberOfGamesLostClassic + IGN->numberOfGamesLostCustom);
        printf("                   ______________________________________________________\n\n");
        printf("                                        Classic mode:\n\n");
        printf("                                            %d - %d\n\n", IGN->numberOfGamesWonClassic, IGN->numberOfGamesLostClassic);
        printf("                                        Games won: %d\n", IGN->numberOfGamesWonClassic);
        printf("                                        Games lost: %d\n", IGN->numberOfGamesLostClassic);
        printf("                   ______________________________________________________\n\n");
        printf("                                        Custom mode:\n\n");
        printf("                                            %d - %d\n\n", IGN->numberOfGamesWonCustom, IGN->numberOfGamesLostCustom);
        printf("                                        Games won: %d\n", IGN->numberOfGamesWonCustom);
        printf("                                        Games lost: %d\n", IGN->numberOfGamesLostCustom);
        printf("                   ______________________________________________________\n\n");
        printf("\n\n");
        printf("                                       [RECENT GAMES]\n\n");
        if (strcmp(Games[0].GameType, "NULL") == 0 && strcmp(Games[0].GameType, "NULL") == 0)
        {
            printf("                              %s HASN'T PLAYED A SINGLE GAME\n\n", IGN->PlayerName);
        }
        else 
        {
            if (strcmp(Games[0].GameType, "NULL") != 0 && strcmp(Games[0].Outcome, "NULL") != 0)
            {
                printf("                                     1. %s : %s\n\n", Games[0].GameType, Games[0].Outcome);
                for (i = 0; i < Games[0].row; i++)
                {
                    if (Games[0].row >= 5 && Games[0].row <= 10)
                    {
                        for (count = 0; count <= 3; count++)
                        {
                            printf("\t      ");
                        }
                    }
                    else 
                    {
                        for (count = 0; count <= 7; count++)
                        {
                            printf("    ");
                        }
                    }
                    
                    for (j = 0; j < Games[0].columns; j++)
                    {
                        if (Games[0].cBoardFlag[i][j] == 'F' || Games[0].cBoardFlag[i][j] == 'X' || Games[0].cBoardFlag[i][j] == '*')
                        {
                            if (Games[0].cBoardFlag[i][j] == '*')
                            {
                                iSetColor(1);
                                printf("%c ", Games[0].cBoardFlag[i][j]);
                                iSetColor(0);
                            }
                            else 
                            {
                                printf("%c ", Games[0].cBoardFlag[i][j]);
                            }
                        }
                        else if (Games[0].AdjacentBombs[i][j] > 0)
                        {
                            printf("%d ", Games[0].AdjacentBombs[i][j]);
                        }
                        else 
                        {
                            printf("%c ", 254);
                        }
                    }
                    printf("\n");
                }

                if (strcmp(Games[1].GameType, "NULL") != 0 && strcmp(Games[1].Outcome, "NULL") != 0)
                {
                    printf("\n");
                    printf("                                     2. %s : %s\n\n", Games[1].GameType, Games[1].Outcome);
                    for (i = 0; i < Games[1].row; i++)
                    {
                        if (Games[1].row >= 5 && Games[1].row <= 10)
                        {
                            for (count = 0; count <= 3; count++)
                            {
                                printf("\t      ");
                            }
                        }
                        else 
                        {
                            for (count = 0; count <= 7; count++)
                            {
                                printf("    ");
                            }
                        }

                        for (j = 0; j < Games[1].columns; j++)
                        {
                            if (Games[1].cBoardFlag[i][j] == 'F' || Games[1].cBoardFlag[i][j] == 'X' || Games[1].cBoardFlag[i][j] == '*')
                            {
                                if (Games[1].cBoardFlag[i][j] == '*')
                                {
                                    iSetColor(1);
                                    printf("%c ", Games[1].cBoardFlag[i][j]);
                                    iSetColor(0);
                                }
                                else 
                                {
                                    printf("%c ", Games[1].cBoardFlag[i][j]);
                                }
                            }
                            else if (Games[1].AdjacentBombs[i][j] > 0)
                            {
                                printf("%d ", Games[1].AdjacentBombs[i][j]);
                            }
                            else 
                            {
                                printf("%c ", 254);
                            }
                        }
                        printf("\n");
                    }
                    if (strcmp(Games[2].GameType, "NULL") != 0 && strcmp(Games[2].Outcome, "NULL") != 0)
                    {
                        printf("\n");
                        printf("                                     3. %s : %s\n\n", Games[2].GameType, Games[2].Outcome);
                        for (i = 0; i < Games[2].row; i++)
                        {
                            if (Games[2].row >= 5 && Games[2].row <= 10)
                            {
                                for (count = 0; count <= 3; count++)
                                {
                                    printf("\t      ");
                                }
                            }
                            else 
                            {
                                for (count = 0; count <= 7; count++)
                                {
                                    printf("    ");
                                }
                            }

                            for (j = 0; j < Games[2].columns; j++)
                            {
                                if (Games[2].cBoardFlag[i][j] == 'F' || Games[2].cBoardFlag[i][j] == 'X' || Games[2].cBoardFlag[i][j] == '*')
                                {
                                    if (Games[2].cBoardFlag[i][j] == '*')
                                    {
                                        iSetColor(1);
                                        printf("%c ", Games[2].cBoardFlag[i][j]);
                                        iSetColor(0);
                                    }
                                    else 
                                    {
                                        printf("%c ", Games[2].cBoardFlag[i][j]);
                                    }
                                }
                                else if (Games[2].AdjacentBombs[i][j] > 0)
                                {
                                    printf("%d ", Games[2].AdjacentBombs[i][j]);
                                }
                                else 
                                {
                                    printf("%c ", 254);
                                }
                            }
                            printf("\n");
                        }
                    }
                }
            }
        }
    }

    printf("\n\n");
    printf("                                  ");
    system("pause");
    system("cls");
}

/* This function executes the Main menu 

 @param InitialRun - Accepts a pointer to an integer that checks if the program is at its initial run
 @param choose - An integer that checks what the user wants to execute
 @param Arr - The integer array that holds the mines (-1)
 @param cBoard - The character 2D array that holds the characters 'X' corresponding to a mine
 @param struct Profile Player - A array of struct Profile Players that holds the blueprints of the player
 @param selectedPlayer - Accepts a pointer to an integer that assigns index of each player
 @param struct Profile IGN - Accepts a pointer to a structure Profile that holds the necessary data for the player 
 @param struct Game Games - An array of structure Game that holds the current games of the player - the outcome, type of game, and the necessary variables for printing the snapshots
 
 @returns various actions based on different cases, depending on the user's input.
 Pre-condition: A player is created */

int MainMenu(int *InitialRun, int choose, int Arr[][MAX], char cBoard[][MAX], struct Profile Players[], int *select, struct Profile *IGN, struct Game Games[])
{
    switch (choose) {
        case 1: 
            GameMode(Arr, cBoard, IGN, Games);
            return 1;
            break;
        case 2:
            CreateLevel(cBoard);
            return 2; 
            break;
        case 3: 
            ViewStatistics(IGN, Games);
            return 3;
            break;
        case 4: 
            CreateProfile(InitialRun, Players, select, IGN, Games);
            return 4;
            break;
        case 5:
            GameMechanics();
            return 5;
            break;
        case 6: 
            return 6;
            break; 
    }

    return 0;
    
}

int main()
{
    int Array[MAX][MAX];
    int ChooseOption;
    int firstRun = 0;
    int select; 
    char CustomBoard[MAX][MAX];
    FILE *CurrentSavedProfile;
    struct Profile PlayerProfiles[10];
    struct Profile SelectedProfile;
    struct Game GamesPlayed[3];

    printf("\n\n");
    iSetColor(3);
    printf("                            In partial fulfillment for CCPROG2\n");
    printf("                         This program was written and designed by\n");
    printf("                              Jedidiah Kyle Martin Julian\n");
    iSetColor(0);
    printf("\n\n\n");
    printf("                                ");
    system("pause");
    system("cls");
    DisplayOpeningHeader(); 
    printf("\n\n");
    iSetColor(3);
    printf("                                       Loading Mines...");
    iSetColor(0);
    sleep(2);
    printf("\n\n");
    system("cls");

    while (firstRun == 0)
    {
        CreateProfile(&firstRun, PlayerProfiles, &select, &SelectedProfile, GamesPlayed);
    }
        
    do
    {
        DisplayOpenScreen();

        scanf("%d", &ChooseOption);

        system("CLS");
    
    } while (MainMenu(&firstRun, ChooseOption, Array, CustomBoard, PlayerProfiles, &select, &SelectedProfile, GamesPlayed) != 6);

    CurrentSavedProfile = fopen("Profiles\\SAVEDPROFILE", "w");
    fprintf(CurrentSavedProfile, "%s\n", ""); // RESETS CURRENT SAVED PROFILE 
    fclose(CurrentSavedProfile);

    return 0;
}

/******************************************************************
This is to certify that this project is my own work, based on my
personal efforts in studying and applying the concepts learned. I
have constructed the functions and their respective algorithms
and corresponding code by myself. The program was run, tested, and
debugged by my own efforts. I further certify that I have not
copied in part or whole or otherwise plagiarized the work of other
students and/or persons.
<Julian, Jedidiah Kyle Martin>, DLSU ID# <12307211>
******************************************************************/