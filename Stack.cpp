#include "Stack.h"
#include "Employee.h" // Include the Employee header file

#include <iostream>

Stack::Stack(int capacity)
    : capacity(capacity), top(-1) {
    elements = new Employee[capacity];
}

Stack::~Stack() {
    delete[] elements;
}

void Stack::push(const Employee& emp) {
    if (top >= capacity - 1) {
        throw std::out_of_range("Stack overflow");
    }
    elements[++top] = emp;
}

void Stack::pop() {
    if (top < 0) {
        throw std::out_of_range("Stack underflow");
    }
    --top;
}

void Stack::display() const {
    for (int i = top; i >= 0; --i) {
        std::cout << "Name: " << elements[i].getName() << "\n"
                  << "ID: " << elements[i].getId() << "\n"
                  << "Age: " << elements[i].getAge() << "\n"
                  << "Salary: " << elements[i].getSalary() << "\n"
                  << "Birth Date: " << elements[i].getBirthDate().day << "-"
                  << elements[i].getBirthDate().month << "-"
                  << elements[i].getBirthDate().year << "\n"
                  << "------------------------------\n";
    }
}

bool Stack::empty() const {
    return top == -1;
}