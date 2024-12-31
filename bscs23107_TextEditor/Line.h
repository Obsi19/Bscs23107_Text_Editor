#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <conio.h> // For console input handling on Windows
using namespace std;

struct letter {
    char ch;
    letter* next;

    letter(char c) : ch(c), next(nullptr) {}
};

class Line
{
    int Size;
    list<letter> Cs; // List of letters in this line

    Line() : Size(0) {}

    void insertChar(int pos, char ch) {
        if (pos < 0 || pos > Size) {
            cout << "Invalid position\n";
            return;
        }

        auto it = Cs.begin();
        advance(it, pos);
        Cs.insert(it, letter(ch));
        Size++;
    }

    void removeChar(int pos) {
        if (pos < 0 || pos >= Size) {
            cout << "Invalid position\n";
            return;
        }

        auto it = Cs.begin();
        advance(it, pos);
        Cs.erase(it);
        Size--;
    }

    void toUpper() {
        for (auto& l : Cs) {
            l.ch = toupper(l.ch);
        }
    }

    void toLower() {
        for (auto& l : Cs) {
            l.ch = tolower(l.ch);
        }
    }

    void printLine() const {
        for (const auto& l : Cs) {
            cout << l.ch;
        }
        cout << endl;
    }

};



