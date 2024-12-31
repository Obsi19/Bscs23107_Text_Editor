#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <Windows.h> // For console input handling on Windows
#include <conio.h> // For console input handling on Windows
using namespace std;

void gotoRowCol(int rpos, int cpos)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int xpos = cpos, ypos = rpos;
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}

struct letter {
    char ch;
    letter* next;

    letter(char c) : ch(c), next(nullptr) {}
};



class Line
{
    int Size;
    list<letter> Cs; // List of letters in this line

	friend class Doc;
	friend class Para;
	friend class TextEditor;

public:

	Line() : Size(0) {}
	Line(string s) : Size(0)
	{
		for (int i = 0; i < s.size(); i++)
		{
			Cs.push_back(letter(s[i]));
			Size++;
		}
	}
	Line(const Line& l) : Size(l.Size)
	{
		for (auto i = l.Cs.begin(); i != l.Cs.end(); i++)
		{
			Cs.push_back(letter(i->ch));
		}
	}
	~Line()
	{
		Cs.clear();
	}


	void PrintLine() const
	{
		for (const letter& ltr : Cs)
		{
			cout << ltr.ch;
		}
		cout << endl;
	}
	void DelCharAt(int ci)
	{
		if (ci >= 0 && ci <= Size) {
			auto it = Cs.begin();
			for (int i = 1; i < ci+1; ++i) { // Advance the iterator to (ci - 1)
				++it;
			}
			Cs.erase(it); // Remove the character at the cursor
			--Size;       // Update the size
		}
	}
	void BackSpaceChar(int ci)
	{
		if (ci >= 0 && ci <= Size) { // Ensure there's a character before the cursor
			auto it = Cs.begin();
			for (int i = 1; i < ci+1; ++i) { // Advance the iterator to (ci - 2)
				++it;
			}
			Cs.erase(it); // Remove the character before the cursor
			--Size;       // Update the size
		}
	}
	void InsertChar(int ci, char c)
	{
		auto it = Cs.begin();
		if (ci > Size) {

			while (Size < ci) {
				Cs.push_back(letter(' '));
				Size++;
			}
			it = Cs.end();
		}
		else {
			for (int i = 1; i < ci+1; ++i) {
				++it;
			}
		}

		Cs.insert(it, letter(c));
		Size++;
	}   //works 
	void SaveLine(ofstream& file) const
	{
		for (const letter& ltr : Cs) 
		{
			file << ltr.ch; 
		}
		file << endl;
	}
	void SetTextColor(int color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
	}

};



