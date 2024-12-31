#pragma once
#include <iostream>
#include "Line.h"
#include <vector>
using namespace std;


class Doc
{
    vector<Line*> lines;
    int cursorRow, cursorCol;
    int NoOfLines;

private:
    vector<Line*> lines;    // Vector of Line pointers to represent each line in the document
    int cursorRow, cursorCol; // Cursor position
    int NoOfLines;          // Number of lines in the document

public:
    Doc() : cursorRow(0), cursorCol(0), NoOfLines(0) {}

    void addLine() {
        lines.push_back(new Line());
        NoOfLines++;
    }

    void insertCharAtCursor(char ch) {
        // Ensure there is a line to insert characters into
        if (lines.empty()) {
            addLine();
        }
        if (cursorRow < NoOfLines) {
            lines[cursorRow]->insertChar(cursorCol, ch);
            cursorCol++;
        }
    }

    void deleteCharAtCursor() {
        if (cursorRow < NoOfLines && cursorCol < lines[cursorRow]->Cs.size()) {
            lines[cursorRow]->removeChar(cursorCol);
            if (cursorCol > 0) {
                cursorCol--;
            }
        }
    }

    void printDocument() const {
        for (int i = 0; i < NoOfLines; i++) {
            lines[i]->printLine();
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < NoOfLines; i++) {
                for (char ch : lines[i]->Cs) {
                    file << ch;
                }
                file << endl;
            }
            file.close();
        }
    }

    ~Doc() {
        for (auto line : lines) {
            delete line;
        }
    }
};

