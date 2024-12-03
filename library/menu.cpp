#include <iostream>
#include <cstring>
#include "./conio.h"
#include "./keyboard.cpp"
class AppState
{
};


template <typename T>
using Callback = void (*)(T *);



template <typename T>
class MenuItem
{

public:
    char *title;
    Callback<T> clickCallback;
    Callback<T> renderCallback;
    MenuItem(const char *title, Callback<T> callback, Callback<T> renderCallback)
    {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
        this->clickCallback = callback;
        this->renderCallback = renderCallback;
    }
    MenuItem() {}
    ~MenuItem() {
        delete[] this->title; // TODO check this
    }
};

template <typename T>
class Menu
{
private:
    int at = 0;
    int size;
    T *context;
    Callback<T> onRender;

public:
    int current = 0;
    MenuItem<T> *items;
    Menu(int size, T *context)
    {
        this->size = size;
        this->items = new MenuItem<T>[size];
        this->context = context;
    }
    ~Menu()
    {   
        delete[] this->items;
    }
    void addItems(MenuItem<T> item[])
    {
        for (int i = 0; i < this->size; i++)
        {
            this->items[i] = item[i];
            this->at++;
        }
    }
    void render()
    {
        while (1)
        {
            clrscr();
            for (int i = 0; i < this->at; i++)
            {
                if (i == this->current)
                {
                    textbackground(BLUE);
                    textcolor(WHITE);
                }
                this->items[i].renderCallback(this->context);
                std::cout << this->items[i].title << std::endl;
                resetTextColor();
                resetBackgroundColor();
            }
            KeyboardButton button = captureKeyboardInput();
            switch (button)
            {
            case KeyboardButton::ArrowDown:
            {
                this->current = this->current >= this->at - 1 ? 0 : this->current + 1;
                break;
            case KeyboardButton::ArrowUp:
            {
                this->current = this->current == 0 ? at - 1 : this->current - 1;
                break;
            case KeyboardButton::Enter:
            {
                this->items[this->current].clickCallback(this->context);
                this->render();
                break;
            }
            }
            }
            default:
                break;
            }
        }
    }
};