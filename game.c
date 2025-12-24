#include <windows.h>
#include <stdio.h>
#include <time.h>

int testcolu(int t[6][6], int a);
#define SIZE 5

// Game Board
int board[SIZE + 1][SIZE + 1];

void calc()
{
    for (int i = 0; i < SIZE; i++)
    {
        board[i][SIZE] = 0;
        for (int j = 0; j < SIZE; j++)
        {

            board[i][SIZE] += board[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++)
    {
        board[SIZE][i] = 0;
        for (int j = 0; j < SIZE; j++)
        {
            board[SIZE][i] += board[j][i];
        }
    }
    board[SIZE][SIZE] = 0;
    for (int i = 0; i < SIZE; i++)
    {
        board[SIZE][SIZE] = board[SIZE][SIZE] + board[i][i];
    }
}

void primaryColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_BLUE |
                                                                 FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void secondaryColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void defaultColor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

int search(int n)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == n)
                return 1;
        }
    }
    return 0;
}

// Function to generate the initial board layout
void generateBoard()
{
    // Generate the board with random numbers from 1 to 25
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            int n = rand() % 25 + 1;
            while (search(n))
            {
                n = rand() % 25 + 1;
            }

            board[i][j] = n;
        }
    }
}

// Function to check if a player has won
int test(int t[6][6])
{
    int cnt = 0;
    int a;
    for (int i = 0; i < 5; i++)
    {
        for (int k = i + 1; k < 5; k++)
        {
            if (t[i][5] == t[k][5])
            {
                cnt++;
                a = t[k][5];
            }
        }
    }
    if (cnt == 0)
    {
        return 0;
    }
    else if (cnt > 1)
    {
        return 1;
    }
    if (cnt == 1)
    {
        if (testcolu(t, a) == 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}
int testcolu(int t[6][6], int a)
{
    for (int i = 0; i <= 5; i++)
    {
        if (t[5][i] == a)
        {
            return 1;
        }
    }
    return 0;
}

// Function to toggle two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void togglePoint(int x1, int y1, int x2, int y2)
{
    swap(&board[x1][y1], &board[x2][y2]);
}

void toggle(int a, int b)
{
    if (a == b)
        return;

    int x1, x2, y1, y2;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == a)
            {
                x1 = i;
                y1 = j;
            }
            if (board[i][j] == b)
            {
                x2 = i;
                y2 = j;
            }
        }
    }
    togglePoint(x1, y1, x2, y2);
}

void display()
{
    printf("\n\n");
    calc();
    for (int i = 0; i < SIZE + 1; i++)
    {
        for (int j = 0; j < SIZE + 1; j++)
        {
            if ((i == SIZE) || (j == SIZE))
            {
                primaryColor();
            }
            else
            {
                secondaryColor();
            }
            if (board[i][j] < 10)
            {
                printf(" %d  ", board[i][j]);
            }
            else
            {
                printf(" %d ", board[i][j]);
            }
            defaultColor();
        }
        printf("\n");
    }
}

// Main function
int main()
{
    int cnt = 0;
    printf("----------------------------- NEW GAME -----------------------------\n\n\n ");

    // Seed the random number generator
    srand(time(NULL));

    // Generate the board
    generateBoard();
    display();
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    // Game loop
    while (1)
    {

        // Prompt for input
        printf("\nPC: ");
        do
        {
            x1 = (rand() % 25) + 1;
            y1 = (rand() % 25) + 1;

        } while ((x1 > 25) || (x1 < 1) || (y1 > 25) || (y1 < 0) || (y1 == y2) || (y1 == x2) || (x1 == y2) || (x1 == x2) || (x1 == y1));
        toggle(x1, y1);
        printf("(x,y)=(%d,%d)\n", x1, y1);
        display();
        // Check if a player has won
        if (test(board) == 1)
        {
            printf("You are a loser !\n");
            break;
        }
        // Prompt for input
        do
        {
            printf("Choose two elements to swap (x, y): ");
            scanf("%d %d", &x2, &y2);
        } while ((x2 > 25) || (x2 < 1) || (y2 > 25) || (y2 < 1) || (y2 == y1) || (y2 == x1) || (x2 == y1) || (x2 == x1) || (x2 == y2));

        // Toggle the elements
        toggle(x2, y2);
        display();
        // Check if a player has won
        if (test(board) == 1)
        {
            printf("you are the winner !\n");
            break;
        }
    }

    return 0;
}
