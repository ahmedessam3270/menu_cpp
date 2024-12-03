#include <iostream>
#include <string>
#include "Stack.h"
#include "Employee.h"

#define UP 65
#define DOWN 66

#define RESET_COLOR "\033[0m"
#define GREEN_COLOR "\033[32m"
#define BLUE_COLOR "\033[34m"

void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void displayMenu(int currentPosition, int row, int col) {
    std::cout << "\033[H\033[J"; // Clear screen

    gotoxy(col / 2 - 4, 1);
    std::cout << (currentPosition == 0 ? GREEN_COLOR : BLUE_COLOR) << "New" << RESET_COLOR;

    gotoxy(col / 2 - 4, 3);
    std::cout << (currentPosition == 1 ? GREEN_COLOR : BLUE_COLOR) << "Display Employees" << RESET_COLOR;

    gotoxy(col / 2 - 4, 5);
    std::cout << (currentPosition == 2 ? GREEN_COLOR : BLUE_COLOR) << "Modify Employee" << RESET_COLOR;

    gotoxy(col / 2 - 4, 7);
    std::cout << (currentPosition == 3 ? GREEN_COLOR : BLUE_COLOR) << "Exit" << RESET_COLOR;
}

int main() {
    int row = 20, col = 20, currentPosition = 0, ch;
    bool flagExitScreen = true, flagExitCurrentScreen = true;
    Stack empStack;

    displayMenu(currentPosition, row, col);

    while (flagExitScreen) {
        ch = getchar();
        if (ch == 27) {
            ch = getchar();
            if (ch == 91) {
                ch = getchar();
                if (ch == UP) {
                    currentPosition = (currentPosition - 1 + 4) % 4; // Cycle 4 options
                } else if (ch == DOWN) {
                    currentPosition = (currentPosition + 1) % 4;
                }
            }
        }

        if (ch == 10) { // Enter key
            if (currentPosition == 0) {
                std::cout << "\033[H\033[J"; // Clear screen
                gotoxy(col / 2 - 4, 3);
                std::cout << BLUE_COLOR << "Add New Employee" << RESET_COLOR << "\n";

                while (flagExitCurrentScreen) {
                    std::string name;
                    int emp_id, age, salary, day, month, year;
                    std::cout << "Enter Employee Name: ";
                    std::cin >> name;
                    std::cout << "Enter Employee ID: ";
                    std::cin >> emp_id;
                    std::cout << "Enter Employee Age: ";
                    std::cin >> age;
                    std::cout << "Enter Employee Salary: ";
                    std::cin >> salary;
                    std::cout << "Enter Employee Birth Date (day month year): ";
                    std::cin >> day >> month >> year;
                    BD bd = {day, month, year};
                    Employee emp(name, emp_id, age, salary, bd);

                    empStack.push(emp);

                    char choice;
                    std::cout << "Do You Want to Add New Employee? (y/n): ";
                    std::cin >> choice;
                    if (choice == 'n') {
                        flagExitCurrentScreen = false;
                    }
                }
            } else if (currentPosition == 1) {
                std::cout << "\033[H\033[J"; // Clear screen
                gotoxy(col / 2 - 4, 3);
                std::cout << "Employees Database\n";
                empStack.display();
                getchar(); // Wait for key press
            } else if (currentPosition == 2) {
                std::cout << "\033[H\033[J"; // Clear screen
                gotoxy(col / 2 - 4, 3);
                std::cout << "Modify Employee Functionality Coming Soon!\n";
                getchar(); // Wait for key press
            } else if (currentPosition == 3) {
                flagExitScreen = false;
            }
        }

        if (flagExitScreen) {
            displayMenu(currentPosition, row, col);
        }
    }

    return 0;
}