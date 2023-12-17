#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#define x 30 // will decide height of gameboard
#define y 30 // will decide width of gameboard
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

char board[x][y];
char input;
int generaterandomx = 0, generaterandomy = 0, generaterandomxf = 0, generaterandomyf = 0, hasgamejustbegun = 0, score = 0; // hasgamejustbegun used for checking if snake should still be randomly placed or is it already placed

void randomlyplacesnake()
{
    generaterandomx = 1 + rand() % (x - 2);        // x within boundary
    generaterandomy = 1 + rand() % (y - 2);        // y within boundary
    board[generaterandomx][generaterandomy] = 'U'; // snake head and in this case tail, placed
}

void randomlyplacefood()
{
    generaterandomxf = 1 + rand() % (x - 2);
    generaterandomyf = 1 + rand() % (y - 2);
    board[generaterandomxf][generaterandomyf] = 'O';
}

void initplayarea()
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            board[i][j] = '~';
        }
    }
    for (int i = 1; i < x - 1; i++)
    {
        for (int j = 1; j < y - 1; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void draw()
{
    system("cls");
    printf(ANSI_COLOR_MAGENTA "\tWelcome!" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_YELLOW "\tGerm game" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_GREEN "->Press w for moving forward\n->Press s for moving backward\n->Press a for moving left\n->Press d for moving right\n-->To exit program press m" ANSI_COLOR_RESET "\n");
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            if (board[i][j] == 'U')
                printf(ANSI_COLOR_RED "%c " ANSI_COLOR_RESET, board[i][j]);
            else if (board[i][j] == 'O')
                printf(ANSI_COLOR_YELLOW "%c " ANSI_COLOR_RESET, board[i][j]);
            else
                printf(ANSI_COLOR_CYAN "%c " ANSI_COLOR_RESET, board[i][j]);
        }
        printf("\n");
    }
    printf(ANSI_COLOR_YELLOW "\n\tScore : %d" ANSI_COLOR_RESET, score);
    takeinput();
}

void takeinput()
{
    input = ' ';
    int true = 1;
    while (true)
    {
        input = getch();
        if (input == 'm' || input == 'M')
        {
            system("cls");
            printf(ANSI_COLOR_MAGENTA "Bye, I hope you had a fun time playing.\n" ANSI_COLOR_RESET);
            Sleep(2000);
            exit(0);
        }
        if (input >= 65 && input <= 90)
            input += 32;
        if (input != 'w' && input != 's' && input != 'a' && input != 'd')
        {
            printf("Invalid input. Please read key mappings.\nInput again.");
            input = ' ';
        }
        else
        {
            true = 0;
        }
    }
    switch (input)
    {
    case 'a':
        if (generaterandomy == 1)
        {
            printf("Game over!");
        }
        else
        {
            board[generaterandomx][generaterandomy] = ' ';
            generaterandomy--;
            board[generaterandomx][generaterandomy] = 'U';
        }
        break;
    case 'w':
        if (generaterandomx == 1)
        {
            printf("Game over!");
        }
        else
        {
            board[generaterandomx][generaterandomy] = ' ';
            generaterandomx--;
            board[generaterandomx][generaterandomy] = 'U';
        }
        break;
    case 's':
        if (generaterandomx == x - 2)
        {
            printf("Game over!");
        }
        else
        {
            board[generaterandomx][generaterandomy] = ' ';
            generaterandomx++;
            board[generaterandomx][generaterandomy] = 'U';
        }
        break;
    case 'd':
        if (generaterandomy == y - 2)
        {
            printf("Game over!");
        }
        else
        {
            board[generaterandomx][generaterandomy] = ' ';
            generaterandomy++;
            board[generaterandomx][generaterandomy] = 'U';
        }
        break;
    }
    if (generaterandomx == generaterandomxf && generaterandomy == generaterandomyf) // if snake is at food
    {
        score++;
        printf("\a");
        randomlyplacefood();
    }
    draw();
}

int main()
{
    srand(time(0));
    // FILE *ptr;
    // char name[100]=" ", infilename[100]=" ";
    // int i=0;
    // printf("Enter your name (one word only): ");
    // gets(name);
    // ptr = fopen("score.txt", "r");
    // while(1)
    // {
    //     infilename[i] = fgetc(ptr);
    //     if(infilename[i]==EOF) break;
    //     i++;
    // }
    // fclose(ptr);
    // for(int k=0;k<100;k++){
    //     if(name[i]!=infilename[i]){
    //         ptr = fopen("score.txt", "a");
    //         fprintf(ptr, "\n%s", name);
    //     }
    // }

    initplayarea();
    if (!hasgamejustbegun)
    {
        randomlyplacesnake();
        hasgamejustbegun = 1;
    }
    randomlyplacefood();
    draw();
    return 0;
}
