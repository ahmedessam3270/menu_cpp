#ifndef STACK_H
#define STACK_H

#include "Employee.h"
#include <stdexcept>

class Stack {
public:
    Stack(int capacity = 100);
    ~Stack();

    void push(const Employee& emp);
    void pop();
    void display() const;
    bool empty() const;

private:
    Employee* elements;
    int capacity;
    int top;
};

#endif // STACK_H