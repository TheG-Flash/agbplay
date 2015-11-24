#include <ncurses.h>
#include <cstdint>
#include "ColorDef.h"
#include "CursesWin.h"
#include "MyException.h"

using namespace agbplay;

CursesWin::CursesWin(uint32_t height, uint32_t width, uint32_t yPos, uint32_t xPos) {
    if ((winPtr = newwin((int)height, (int)width, (int)yPos, (int)xPos)) == nullptr) {
        throw MyException("Error while creating curses window [newwin]");
    }
    this->height = height;
    this->width = width;
}

CursesWin::~CursesWin() {
    if (delwin(winPtr) == ERR) {
        throw MyException("Error while deleteing curses window [delwin]");
    }
}

void CursesWin::Resize(uint32_t height, uint32_t width,
        uint32_t yPos, uint32_t xPos) {
    if (delwin(winPtr) == ERR) {
        throw MyException("Error while resizing curses window [delwin]");
    }
    this->height = height;
    this->width = width;
    if ((winPtr = newwin((int)height, (int)width, (int)yPos, (int)xPos)) == nullptr) {
        throw MyException("Error while resizing curses window [newwin]");
    }
}

void CursesWin::update() {
    wattrset(winPtr, COLOR_PAIR(DEFAULT_ON_DEFAULT));
    wclear(winPtr);
}