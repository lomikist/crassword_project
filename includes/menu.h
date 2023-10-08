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
    Menu(string);
    ~Menu();
};
