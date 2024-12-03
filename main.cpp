#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

#define UP 65
#define DOWN 66

#define EMP_SIZE 100

// ANSI color codes
#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"

typedef struct BD
{

    int day;
    int month;
    int year;

} BD;

typedef struct Employee
{
    /* data */
    char name[10];
    int emp_id;
    int age;
    int salary;
    BD bd;
} Employee;

// Function to move the cursor to a specific position
void gotoxy(int x, int y)
{
#ifdef _WIN32
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
    printf("\033[%d;%dH", y, x);
#endif
}

// Function to get a single character without echoing it to the console
int getch(void)
{
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

// Function to display the menu
void DisplayMenu(int currentPostion, int row, int col)
{
    printf("\033[H\033[J"); // Clear screen

    // "New" option
    gotoxy(col / 2 - 4, 1);
    if (currentPostion == 0)
    {
        printf("%sNew%s", GREEN_COLOR, RESET_COLOR);
    }
    else
    {
        printf("%sNew%s", BLUE_COLOR, RESET_COLOR);
    }

    // "Display" option 1
    gotoxy(col / 2 - 4, 3);
    if (currentPostion == 1)
    {
        printf("%sDisplay Employees%s", GREEN_COLOR, RESET_COLOR);
    }
    else
    {
        printf("%sDisplay Employees%s", BLUE_COLOR, RESET_COLOR);
    }

    // "Modify" option
    gotoxy(col / 2 - 4, 5);
    if (currentPostion == 2)
    {
        printf("%sModify Employee%s", GREEN_COLOR, RESET_COLOR);
    }
    else
    {
        printf("%sModify Employee%s", BLUE_COLOR, RESET_COLOR);
    }

    // "Exit" option
    gotoxy(col / 2 - 4, 7);
    if (currentPostion == 3)
    {
        printf("%sExit%s", GREEN_COLOR, RESET_COLOR);
    }
    else
    {
        printf("%sExit%s", BLUE_COLOR, RESET_COLOR);
    }
}

int main(void)
{
    int row = 20, col = 20, currentPostion = 0, ch, flagExitScreen = 1;
    int flagExitCurrentScreen = 1;
    Employee empArray[EMP_SIZE];

    DisplayMenu(currentPostion, row, col);

    while (flagExitScreen)
    {
        ch = getch();
        if (ch == 27)
        {
            ch = getch();
            if (ch == 91)
            {
                ch = getch();
                if (ch == UP)
                {
                    currentPostion = (currentPostion - 1 + 4) % 4; // Cycle 4 options
                }
                else if (ch == DOWN)
                {
                    currentPostion = (currentPostion + 1) % 4;
                }
            }
        }

        if (ch == 10)
        { // Check if Enter key is pressed
            if (currentPostion == 0)
            {

                printf("\033[H\033[J"); // Clear screen
                gotoxy(col / 2 - 4, 3);

                printf(" %sAdd New Employee%s \n", BLUE_COLOR, RESET_COLOR);
                int i = 0;
                while (flagExitCurrentScreen == 1 && i < EMP_SIZE)
                {

                    printf("Enter Employee Name:");
                    scanf("%s", &empArray[i].name);
                    while (getchar() != '\n')
                        ; // Clear input buffer

                    printf("Enter Employee ID:");
                    scanf("%d", &empArray[i].emp_id);
                    while (getchar() != '\n')
                        ; // Clear input buffer

                    printf("Enter Employee Age:");
                    scanf("%d", &empArray[i].age);
                    while (getchar() != '\n')
                        ; // Clear input buffer

                    printf("Enter Employee Salary:");
                    scanf("%d", &empArray[i].salary);
                    while (getchar() != '\n')
                        ; // Clear input buffer

                    printf("Enter Employee day Birth Date:");
                    scanf("%d", &empArray[i].bd.day);
                    while (getchar() != '\n')
                        ; // Clear input buffer

                    printf("Enter Employee month Birth Date:");
                    scanf("%d", &empArray[i].bd.month);
                    while (getchar() != '\n')
                        ; // Clear input buffer

                    printf("Enter Employee year Birth Date:");
                    scanf("%d", &empArray[i].bd.year);
                    while (getchar() != '\n')
                        ; // Clear input buffer

                    printf("Do You Want to Add New Employee? \n");
                    printf("Press (y) to add new employee, (n) to exit to main menu! \n");
                    ch = getch();
                    if (ch == 110 || i == EMP_SIZE)
                    {
                        flagExitCurrentScreen = 0;
                    }
                    i++;
                }

                // printf("\033[H\033[J"); // Clear screen
                // gotoxy(col / 2 - 4, 3);
            }
            else if (currentPostion == 1)
            {

                printf("\033[H\033[J"); // Clear screen
                gotoxy(col / 2 - 4, 3);
                printf(" %sEmployees Database%s \n", RED_COLOR, RESET_COLOR);
                for (int i = 0; i < EMP_SIZE; i++)
                {
                    printf("------------------------------\n");
                    printf("New Employee Name %d:  %s \n", i, empArray[i].name);
                    printf("New Employee ID %d:  %d \n", i, empArray[i].emp_id);
                    printf("Enter Employee Age %d:  %d \n", i, empArray[i].age);
                    printf("Enter Employee Salary %d: %d \n", i, empArray[i].salary);
                    printf("Enter Employee day Birth Date %d: %d \n", i, empArray[i].bd.day);
                    printf("Enter Employee month Birth Date %d: %d \n", i, empArray[i].bd.month);
                    printf("Enter Employee year Birth Date %d: %d \n", i, empArray[i].bd.year);
                    printf("------------------------------\n");
                }
                gotoxy(col / 2 - 4, 4);
                printf("----------------------");
                getch();
                flagExitScreen = 1;
            }
            else if (currentPostion == 2)
            {
                printf("\033[H\033[J"); // Clear screen
                gotoxy(col / 2 - 4, 3);
                int i = 0;
                printf(" %sModify Employee Functionality Coming Soon!%s \n", YELLOW_COLOR, RESET_COLOR);
                getch();
                while (i++)
                {
                    printf("------------------------------\n");
                    printf("New Employee ID %d:  %d \n", i, empArray[i].emp_id);
                    printf("New Employee Name %d:  %s \n", i, empArray[i].name);
                    printf("------------------------------\n");
                    i++;
                }
                // print choose id
                // switch with numbers represent employee attributes
                // validations on the id
                // valid input
            }

            else if (currentPostion == 3)
            {

                printf("\033[H\033[J"); // Clear screen
                gotoxy(col / 2 - 10, 3);
                printf(" %sPress Enter to Exit!%s \n", RED_COLOR, RESET_COLOR);

                gotoxy(col / 2 - 15, 4);

                flagExitScreen = 0;
            }
        }

        if (flagExitScreen)
        {

            DisplayMenu(currentPostion, row, col);
        }
    }

    return 0;
}
