#pragma once
#include "Document.h"
#include "Line.h"
#include <iostream>
#include <vector>
using namespace std;





class TextEditor
{
private:

    vector<Doc*> AllDocs;
    int cc=0 , cr=0;
    int Cdri = 0, Cdci = 0;
    int Cdoci=0, NofDocs=0;

public:

	TextEditor();
	void ControlEditor();
	~TextEditor();

};


TextEditor::TextEditor()
{
	int choice;

	cout << " I WELCOME YOU TO MY TEXT EDITOR" << endl;
	restart:
	cout << endl;
	cout << "Press 1 to create a new document" << endl;
	cout << "Press 2 to open an existing document" << endl;
	cout << "Press 3 ghar jao wapis" << endl;

	cin >> choice;


	switch (choice)
	{
	case 1:  //new document
	{
		system("cls");
		cout << "Enter the name of the document" << endl;
		string name;
		cin >> name;
		string ename = name + ".txt";
		AllDocs.push_back(new Doc(ename, true));
		NofDocs++;
		system("cls");
		AllDocs[NofDocs - 1]->printdoc();
		Cdoci = NofDocs - 1;

		break;
	}
	case 2: // new document 
	{
		system("cls");
		cout << "Enter the name of the document" << endl;
		string name;
		cin >> name;
		string ename = name + ".txt";
		AllDocs.push_back(new Doc(ename, false));
		NofDocs++;
		Cdoci = NofDocs - 1;
		system("cls");
		AllDocs[Cdoci]->printdoc();

		break;
	}
	case 3:   //salamolaikum
	{
		cout << "Ghar ke daastaan ke liye app ko salam" << endl;
		break;
	}
	default:
		cout << "Invalid choice" << endl;
		goto restart;
		break;
	}

}




void TextEditor::ControlEditor()
{
    int keyCode;         // Stores the pressed key's code
    char character;      // Stores the character input
    cr = 0;              // Initialize cursor row
    cc = 0;              // Initialize cursor column
    gotoRowCol(cr, cc);  // Position the console cursor

    while (true)
    {
        if (_kbhit()) // Check if a key is pressed
        {
            keyCode = _getch();

            // Handle special keys (arrow keys, delete, etc.)
            if (keyCode == 224)
            {
                keyCode = _getch();
                switch (keyCode)
                {
                case 72: // Up Arrow
                    if (cr > 0)
                    {
                        cr--;
                        cc = min(cc, AllDocs[Cdoci]->lines[cr].Size);
                    }
                    break;

                case 80: // Down Arrow
                    if (cr < AllDocs[Cdoci]->NoOfLines - 1)
                    {
                        cr++;
                        cc = min(cc, AllDocs[Cdoci]->lines[cr].Size);
                    }
                    break;

                case 77: // Right Arrow
                    cc++;
                    if (cc > AllDocs[Cdoci]->lines[cr].Size && cr < AllDocs[Cdoci]->NoOfLines - 1)
                    {
                        cr++;
                        cc = 0;
                    }
                    break;

                case 75: // Left Arrow
                    if (cc > 0)
                    {
                        cc--;
                    }
                    else if (cr > 0)
                    {
                        cr--;
                        cc = AllDocs[Cdoci]->lines[cr].Size;
                    }
                    break;

                case 83: // Delete
                    AllDocs[Cdoci]->delChar(cr, cc);
                    AllDocs[Cdoci]->printdoc();
                    break;
                }
            }
            else
            {
                // Handle regular keys and actions
                switch (keyCode)
                {
                case 13: // Enter
                    AllDocs[Cdoci]->InsertNewLineAt(cr, cc);
                    cr++;
                    cc = 0;
                    AllDocs[Cdoci]->printdoc();
                    break;

                case 8: // Backspace
                    if (cc > 0)
                    {
                        cc--;
                        AllDocs[Cdoci]->backspaceChar(cr, cc);
                    }
                    else if (cr > 0)
                    {
                        cr--;
                        cc = AllDocs[Cdoci]->lines[cr].Size;
                    }
                    AllDocs[Cdoci]->printdoc();
                    break;

                
                    

                case 15: // CTRL + O (Custom Functionality)
                    AllDocs[Cdoci]->saveFile(AllDocs[Cdoci]->Dname);
                    cout << "Document saved." << endl;

                    break;

                case 21: // CTRL + U for ToLowerLine
                    AllDocs[Cdoci]->ToUpperLine(cr, cc);
                    AllDocs[Cdoci]->printdoc();
                    break;
                case 12: // CTRL + L for ToLowerLine
                    AllDocs[Cdoci]->ToLowerLine(cr, cc);
                    AllDocs[Cdoci]->printdoc();
                    break;

                case 6: // CTRL + F for Case-Sensitive Search
                { 

					system("cls");
                    string word;
                    cout << "Enter the word to search (case-sensitive): ";
                    cin >> word;

					system("cls");
                    AllDocs[Cdoci]->FindWordCaseSensitive(word);
                    break;
                }
                case 23: // CTRL + W for Case-Insensitive Search
                {
					system("cls");
                    string word;
                    cout << "Enter the word to search (case-insensitive): ";
                    cin >> word;

					system("cls");
                    AllDocs[Cdoci]->FindWordCaseInsensitive(word);
                    break;
                }
                case 14: // CTRL + N for Finding a Sentence
                {
                    system("cls");
                    string sentence;
                    cout << "Enter the sentence to search: ";
                    cin.ignore(); 
                    getline(cin, sentence); 
                    system("cls");
                    AllDocs[Cdoci]->FindSentence(sentence);
                    break;
                }

                case 2: // CTRL + B for Finding a Substring
                {
                    system("cls");
                    string substring;
                    cout << "Enter the substring to search: ";
                    cin >> substring;
                    system("cls");
                    AllDocs[Cdoci]->FindSubstring(substring);
                    break;
                }

                case 18: // CTRL + R for Replace First Occurrence
                {
                    system("cls");
                    string oldWord, newWord;
                    cout << "Enter the word to replace: ";
                    cin >> oldWord;
                    cout << "Enter the new word: ";
                    cin >> newWord;

                    AllDocs[Cdoci]->ReplaceFirstOccurrence(oldWord, newWord);
                    break;
                }

                case 5: // CTRL + E for Replace All Occurrences
                {
                    system("cls");
                    string oldWord, newWord;
                    cout << "Enter the word to replace: ";
                    cin >> oldWord;
                    cout << "Enter the new word: ";
                    cin >> newWord;

                    AllDocs[Cdoci]->ReplaceAllOccurrences(oldWord, newWord);
                    break;
                }
                case 1: // CTRL + A for Average Word Length
                {
                    system("cls");
                    AllDocs[Cdoci]->AvgWordLength();
                    break;
                }
                case 7: // CTRL + G for Add Prefix to Word
                {
                    system("cls");
                    string word, prefix;
                    cout << "Enter the word to add prefix to: ";
                    cin >> word;
                    cout << "Enter the prefix: ";
                    cin >> prefix;

                    AllDocs[Cdoci]->AddPrefixToWord(word, prefix);
                    AllDocs[Cdoci]->printdoc();
                    break;
                }
                case 9: // CTRL + I for Add Postfix to Word
                {
                    system("cls");
                    string word, postfix;
                    cout << "Enter the word to add postfix to: ";
                    cin >> word;
                    cout << "Enter the postfix: ";
                    cin >> postfix;

                    AllDocs[Cdoci]->AddPostfixToWord(word, postfix);
                    AllDocs[Cdoci]->printdoc();
                    break;
                }

                case 4: // CTRL + D for Substring Count
                {
                    system("cls");
                    string substring;
                    cout << "Enter the substring to count: ";
                    cin >> substring;

                    AllDocs[Cdoci]->SubstringCount(substring);
                    break;
                }

                case 11: // CTRL + K for Special Characters Count
                {
                    system("cls");
                    AllDocs[Cdoci]->FindSpecialCharactersCount();
                    break;
                }

                case 25: // CTRL + Y for Largest Word Length
                {
                    system("cls");
                    AllDocs[Cdoci]->FindLargestWord();
                    break;
                }

                case 26: // CTRL + Z for Smallest Word Length
                {
                    system("cls");
                    AllDocs[Cdoci]->FindSmallestWord();
                    break;
                }
                case 24: // CTRL + X for Word-Game
                {
                    system("cls");
                    cout << "Welcome to the Word-Game!" << endl;

                    AllDocs[Cdoci]->WordGame();
                    break;
                }

                case 16: // CTRL + P for Merge Files
                {
                    system("cls");
                    cout << "Merge Files Functionality" << endl;

                    string fname1, fname2;
                    cout << "Enter the name of the first file to merge: ";
                    cin >> fname1;
                    fname1 += ".txt";

                    cout << "Enter the name of the second file to merge: ";
                    cin >> fname2;
                    fname2 += ".txt";

                    AllDocs[Cdoci]->mergeFiles(fname1, fname2);
                    cout << "Files merged successfully!" << endl;

                    system("cls");
                    AllDocs[Cdoci]->printdoc();
                }
                default: // Regular Character Input( works perfectly)
                    character = char(keyCode);
                    AllDocs[Cdoci]->InsertAChar(cr, cc, character);
                    cc++;
                    AllDocs[Cdoci]->printdoc();
                    break;
                }
            }

            // Update cursor position in the console
            gotoRowCol(cr, cc);
        }
    }
}




TextEditor::~TextEditor()
{
	for (int i = 0; i < NofDocs; i++)
	{
		delete AllDocs[i];
	}
}













//void TextEditor::ControlEditor()
//{
//	int d;
//	char ch;
//	bool IsFirst = true;
//	bool IsFirst2 = true;
//	cr = 0; cc = 0;
//	gotoRowCol(cr, cc);
//	//Line ALine;
//	while (true)
//	{
//		if (_kbhit())
//		{
//			d = _getch();
//
//			//
//			if (d == 224)
//			{
//				d = _getch();
//				if (d == 72)
//				{
//					if (cr > 0) {
//						cr--;
//					}
//					if (AllDocs[Cdoci]->Ls[cr].Size < cc)
//					{
//						cc = AllDocs[0]->Ls[cr].Size;
//					}
//				}
//				else if (d == 80)
//				{
//					if (AllDocs[Cdoci]->NofLines - 1 != cr) {
//						cr++;
//					}
//					if (AllDocs[Cdoci]->Ls[cr].Size < cc)
//					{
//						cc = AllDocs[Cdoci]->Ls[cr].Size;
//					}
//				}
//				else if (d == 77)
//				{
//					cc++;
//					if (cc == AllDocs[Cdoci]->Ls[cr].Size)
//					{
//						cc = 0;
//						cr++;
//					}
//				}
//				else if (d == 75)
//				{
//					cc--;
//					if (cc == -1 && cr != 0)
//					{
//						cr--;
//						cc = AllDocs[Cdoci]->Ls[cr].Size;
//					}
//				}
//				else if (d == 83) {
//					//AllDocs[Cdoci]->DeleteCharAt(cr, cc + 1);
//					AllDocs[Cdoci]->DeleteCharAt2(cr, cc);
//					AllDocs[Cdoci]->PrintDocument();
//				}
//			}
//			else if (d == 13)
//			{
//				//InsertNewLineAt
//				AllDocs[Cdoci]->InsertNewLineAt(cr, cc);
//				cr++;
//				cc = 0;
//				AllDocs[Cdoci]->PrintDocument();
//			}
//			else if (d == 8)
//			{
//				//AllDocs[Cdoci]->DeleteCharAt(cr, cc);
//				//AllDocs[Cdoci]->PrintDocument();
//				if (cc == 0 && cr != 0)
//				{
//					cr--;
//					cc = AllDocs[Cdoci]->Ls[cr].Size;
//				}
//				else if (cc == 0 && cr == 0)
//				{
//					cr = 0;
//					cc = 0;
//				}
//				else
//				{
//					cc--;
//				}
//			}
//			else if (IsFirst && d == 15)
//			{
//				//if (d == 15)
//				{
//					IsFirst = false;
//				}
//			}
//			else if (!IsFirst)
//			{
//				if (d == 15)
//				{
//					//string word;
//					//gotoRowCol(28, 0);
//					//cin >> word;
//					//gotoRowCol(0, 0);
//					//cout << "Ctrl + O" << endl;
//					//To Upper
//					//AllDocs[Cdoci]->ToLowerLine(cr,cc);
//					//AllDocs[Cdoci]->ToUpperWord(cr, cc);
//					//AllDocs[Cdoci]->findingWordCaseSensitive(word);
//					//AllDocs[Cdoci]->findingWordCaseInSensitive(word);
//					//AllDocs[Cdoci]->findingSpecialCharCount();
//					//AllDocs[Cdoci]->avgWordLength();
//					//AllDocs[Cdoci]->wordGame();
//					//AllDocs[Cdoci]->saveFile();
//					//AllDocs[Cdoci]->findingSubString(word);
//					//AllDocs[Cdoci]->replaceAll(word, "alif");
//					//AllDocs[Cdoci]->AddPrefixToWords("lm", word);
//					//AllDocs[Cdoci]->AddSuffixToWords("lm", word);
//					//AllDocs[Cdoci]->subStringCount(word);
//					//AllDocs[Cdoci]->LargestWordLength();
//					//AllDocs[Cdoci]->SmallestWordLength();
//					//AllDocs[Cdoci]->countParas();
//					//string file1, file2;
//					//cout << "Enter File 1: ";
//					//cin >> file1;
//					//file1 = file1 + ".txt";
//					//cout << "Enter File 2: ";
//					//cin >> file2;
//					//file2 = file2 + ".txt";
//					//AllDocs[Cdoci]->mergeFiles(file1, file2);
//					//AllDocs[Cdoci]->PrintDocument();
//				}
//				else if (d == 5)
//				{
//					cout << "Ctrl + D" << endl;
//				}
//				else if (d == 4) {
//					//InsertNewLineAt
//					AllDocs[Cdoci]->InsertNewLineAt(cr, cc);
//					cr++;
//					cc = 0;
//					AllDocs[Cdoci]->Ls[cr].isParaStarter = true;
//					cout << AllDocs[Cdoci]->Ls[cr].isParaStarter;
//					cout << AllDocs[Cdoci]->DName;
//					AllDocs[Cdoci]->PrintDocument();
//				}
//				IsFirst = true;
//			}
//			else
//			{
//				ch = char(d);
//				//cout << char(d);
//				//cout<<ch;
//				//ALine.InserCharAt(cc, ch);
//
//				AllDocs[Cdoci]->InsertAChar(cr, cc, ch);
//				//AllDocs[Cdoci]->Ls[cr].InsertCharAt(cc, ch);
//				AllDocs[Cdoci]->PrintDocument();
//				cc++;
//
//			}
//
//			gotoRowCol(cr, cc);
//
//		}
//	}
//}