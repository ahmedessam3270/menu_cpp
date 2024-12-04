#include <iostream>
#include <cstring>
#include "./library/menu.cpp"
#include "./library/inputter.h"
using namespace std;

class Employee
{
    char name[100];
    int salary;
    int id;

public:
    Employee() {}
    Employee(const char *name, int salary, int id)
    {
        strcpy(this->name, name);
        this->salary = salary;
        this->id = id;
    }
    

    char *getName()
    {
        return this->name;
    }

    int getSalary()
    {
        return this->salary;
    }
    int getId()
    {
        return this->id;
    }
};

enum StackStatus
{
    StackIsFull = -1,
    StackIsEmpty = 1,
};

class Stack
{
private:
    int size;
    int top;
    Employee *items;

public:
    static int all;

    Stack(int size)
    {
        all++;
        this->size = size;
        this->items = new Employee[size];
        this->top = 0;
    }

    ~Stack()
    {
        all--;
        delete[] items;
    }

    static int getCount()
    {
        return all;
    }

    int getTop()
    {
        return top;
    }

    Employee *getAll()
    {
        return this->items;
    }

    bool isFull()
    {
        return top == size;
    }

    bool isEmpty()
    {
        return top == 0;
    }

    void push(Employee value)
    {
        if (top == size)
        {
            throw StackStatus::StackIsFull;
        }
        this->items[top++] = value;
    }

    Employee pop()
    {
        if (top == 0)
        {
            throw StackStatus::StackIsEmpty;
        }

        return this->items[--top];
    }

    void display()
    {
        if (top == 0)
        {
            cout << "[ <empty> ]";
            return;
        }
        cout << "[ \n";
        for (int i = 0; i < top; i++)
        {
            // this->items[i].print();
        }
        cout << endl;
        cout << "\n]";
    }
};
int Stack::all = 0;

class Master
{
public:
    Menu<Master> *menu;
    Stack *stack;
    int lol = 5;
    Master(Stack *stack, Menu<Master> *menu)
    {
        this->menu = menu;
        this->stack = stack;
        return;
    }
};


void main_push_click(Master *state)
{
    if (state->stack->isFull())
    {
        system("clear");
        cout << "Stack is full, press any key" << endl;
        getch();
        state->menu->render();
        return;
    }
    system("clear");
    char *name = new char[32];
    cout << "Enter name: ";
    cin >> name;
    cout << endl;
    int salary = 0;
    int id = 0;
    bool done_before = false;
    do
    {
        if (done_before)
        {
            cout << "Salary cannot be 0" << endl;
        }
        salary = prompt_int("Enter salary: ");
        done_before = false;
    } while (salary == 0);
    cout << endl;
    id = prompt_int("Enter id: ");
    cout << endl;
    Employee employee = Employee(name, salary, id);
    delete name; //TODO check this
    try
    {
        state->stack->push(employee);
        cout << "Pushed, press any key" << endl;
        getch();
    }
    catch (StackStatus err)
    {
        cout << "Stack is full, press any key" << endl;
        getch();
    }
    state->menu->render();
}

void main_display_click(Master *state)
{
    if (state->stack->isEmpty())
    {
        system("clear");
        cout << "Stack is empty, press any key" << endl;
        getch();
        state->menu->render();
        return;
    }
    system("clear");
    for (int i = 0; i < state->stack->getTop(); i++)
    {
        Employee current = state->stack->getAll()[i];
        cout << "Name \t:\t" << current.getName() << endl;
        cout << "Salary \t:\t" << current.getSalary() << endl;
        cout << "Id \t:\t" << current.getId() << endl;
        cout << "=========================================" << endl;
    }
    cout << "Press any key" << endl;
    getch();
    state->menu->render();
}

void main_pop_click(Master *state)
{
    system("clear");
    try
    {
        Employee employee = state->stack->pop();
        cout << "Name \t:\t" << employee.getName() << endl;
        cout << "Salary \t:\t" << employee.getSalary() << endl;
        cout << "Id \t:\t" << employee.getId() << endl;
        cout << "=========================================" << endl;
        cout << "Popped,please press any key" << endl;
        getch();
    }
    catch (StackStatus err)
    {
        cout << "Stack is Now empty,please press any key" << endl;
        getch();
    }
    state->menu->render();
}

void main_exit_click(Master *state)
{
    exit(0);
}

void noop(Master *state) {}

int main()
{
    int size = 0;
    bool done_before = false;

    do
    {
        if (done_before)
            cout << "\nSize cannot be 0" << endl;
        size = prompt_int("Enter your stack size: ");
        done_before = true;

    } while (size == 0);

    Stack *stack = new Stack(size);
    Master state(stack, NULL);

  

    MenuItem<Master> main_items[] = {
        MenuItem<Master>("Push", &main_push_click, &noop),
        MenuItem("Pop", &main_pop_click, &noop),
        MenuItem("Display", &main_display_click, &noop),
        MenuItem("Exit", &main_exit_click, &noop),
    };

    Menu<Master> main_menu = Menu<Master>(4, &state);
    main_menu.addItems(main_items);
    state.menu = &main_menu;
    main_menu.render();

    delete stack; //TODO check this
}