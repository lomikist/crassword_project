#pragma once
#include <iostream>
#include <vector>
#include "string.h"
using namespace std;
class Menu
{
private:
    string name;
public:
    vector<string> items;
    string* active_item;
    void change_item(int);
    Menu(string);
    ~Menu();
};
