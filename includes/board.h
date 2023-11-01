#pragma once
#include <iostream>
#include <vector>
#include "string.h"
using namespace std;
class Board
{
public:
    // (x1,y1,x2,y2)
    Board(int,int,int,int);
    ~Board();
    // board drawing lefte upper corner
    pair<int, int> startPoint;
    // board drawing right bottom corner
    pair<int, int> endPoint;
    // coutn first horizontal count of lines, soconde vertical cout of lines.
    pair<int, int> lineCount;
};
