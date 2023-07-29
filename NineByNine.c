#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

void GetNumber();
void SudokuSolver();
void AvailableNums(int box, int *pRow, int *pColumn);
void PrintSudoku();

int previousBox = 0;
int sudokuElements[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int sudoku[][9] = {0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0,
                   0, 0, 0, 0, 0, 0, 0, 0, 0};

int main()
{
    int t = 10;
    int confirm;

    while (t--){
        PrintSudoku();
        GetNumber();
        system("cls");
    }

    printf("\tBEFORE\n");
    PrintSudoku();

    do{
        printf("\n\nPress [Y] to Launch: ");
        scanf(" %c", &confirm);

        confirm = toupper(confirm);
    } while (confirm != 'Y');
    
    printf("\n\tAFTER\n");
    SudokuSolver();
}

void GetNumber()
{
    int box, row, column, tempValue, none, none1;

    do{
            printf("\nEnter the number of box[1 - 9]: ");
            scanf("%d", &box);

            if (box < 1 || box > 9)
                printf("Invalid Input of Box.\n");

        } while (box < 1 || box > 9);

    do{
        do{
            printf("\nEnter the number of row[1 - 3]: ");
            scanf("%d", &row);

            if (row < 1 || row > 3)
                printf("Invalid Input of Row.\n");

        } while (row < 1 || row > 3);

        do{
            printf("Enter the number of column[1 - 3]: ");
            scanf("%d", &column);

            if (column < 1 || column > 3)
                printf("Invalid Input of Column.\n\n");

        } while (column < 1 || column > 3);

        row--; column--;
        
        switch(box){
            case 9:
            case 8:
                column += (box == 9 ? 6 : 3);
            case 7:
                row += 6;
                break;
            case 6:
            case 5:
                column += (box == 6 ? 6 : 3);
            case 4:
                row += 3;
                break;
            case 3:
            case 2:
                column += (box == 3 ? 6 : 3);
                break;
        }

        if (sudoku[row][column] != 0)
            printf("The position is already occupied. Input another row and column\n");

    } while(sudoku[row][column] != 0);

    if (box != previousBox || previousBox == 0)
        AvailableNums(box, &none, &none1);

    do {
        printf("\nEnter the number[1 - 9] you want to insert: ");
        scanf("%d", &tempValue);

        if (sudokuElements[tempValue - 1] == 0)
            printf("Number %d has already been used in the sudoku.\n", tempValue);
    } while (sudokuElements[tempValue - 1] == 0);

    sudokuElements[tempValue - 1] = 0;
    sudoku[row][column] = tempValue;

    previousBox = box;
}

void SudokuSolver()
{
    int row, column, count = 0;

    for (int box = 0; box < 9; box++){
        AvailableNums(box + 1, &row, &column);

        for (int i = row; i < row + 3; i++){
            for (int j = column; j < column + 3; j++){
                if (sudoku[i][j] == 0){
                    while (sudokuElements[count] == 0 && count < 9)
                        count++;
                
                    sudoku[i][j] = sudokuElements[count];
                    count++;
                }
            }
        }

        count = 0;
    }

    PrintSudoku();
}

void AvailableNums(int box, int *pRow, int *pColumn)
{
    for (int i = 0; i < 9; i++)
        sudokuElements[i] = i + 1;

    if (box == 1 || box == 4 || box == 7)
        *pColumn = 0;
    else if (box == 2 || box == 5 || box == 8)
        *pColumn = 3;
    else if (box == 3 || box == 6 || box == 9)
        *pColumn = 6;
    
    if (box <= 3)
        *pRow = 0;
    else if (box <= 6)
        *pRow = 3;
    else if (box <= 9)
        *pRow = 6;
    
    for (int i = *pRow; i < *pRow + 3; i++)
        for (int j = *pColumn; j < *pColumn + 3; j++)
            if (sudoku[i][j] != 0)
                sudokuElements[(sudoku[i][j]) - 1] = 0;
}


void PrintSudoku()
{ 
    //PrintBorder(); //Call PrintBorder() to print a horizontal border.

    for (int i = 0; i < 9; i++){
        if (i % 3 == 0 && i != 0)
            printf("\t-------------   -------------   -------------\n");
        printf("\t-------------   -------------   -------------\n\t");
        for (int j = 0; j < 9; j++){
            if (j % 3 == 0 && j != 0)
                printf("   ");

            (sudoku[i][j] != 0) ? printf("| %d ", sudoku[i][j]) : printf("|   ");

            if ((j + 1) % 3 == 0)
                printf("|");
        }
        printf("\n");
    }
    printf("\t-------------   -------------   -------------\n");
}
