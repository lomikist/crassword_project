#include "../includes/board.h"

Board::Board(int x1, int y1, int x2, int y2 ) {
    this->startPoint.first = x1;
    this->startPoint.second = y1;
    
    this->endPoint.first = x2;
    this->endPoint.second = y2;

    // horizontal line count is 2 times less than board width.
    // and vertical line count also 2 times less.
    // ------
    // |*|
    // ------
    // |*|
    // horizontal
    this->lineCount.first = (int) ( this->endPoint.second - this->startPoint.second ) / 2;
    // vertical 
    this->lineCount.second = (int) ( this->endPoint.first - this->startPoint.first ) / 2;
}