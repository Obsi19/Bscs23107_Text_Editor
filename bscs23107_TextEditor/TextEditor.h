#pragma once
#include "Document.h"
#include <iostream>
#include <vector>
using namespace std;





class TextEditor
{
private:

    vector<Doc*> AllDocs;
    int Cdri = 0, Cdci = 0;
    int Cdoci, NofDocs;


public:

    TextEditor() : NoOfDocs(0), Cdoci(0) {};


    void createNewDocument(int numLines = 10) {
        Doc* newDoc = new Doc(numLines);
        AllDocs.push_back(newDoc);
        Cdoci = AllDocs.size() - 1;
        NofDocs++;
    }

    void switchDocument(int docIndex) {
        if (docIndex >= 0 && docIndex < AllDocs.size()) {
            Cdoci = docIndex;
            Cdri = Cdci = 0;
        }
    }

    void insertChar(char ch) {
        if (Cdoci < AllDocs.size()) {
            AllDocs[Cdoci]->insertCharAtCursor(ch);
            Cdci++;
        }
    }

    void deleteChar() {
        if (Cdoci < AllDocs.size()) {
            AllDocs[Cdoci]->deleteCharAtCursor();
        }
    }

    void saveCurrentDocument(const string& filename) const {
        if (Cdoci < AllDocs.size()) {
            AllDocs[Cdoci]->saveToFile(filename);
        }
    }

    void printCurrentDocument() const {
        if (Cdoci < AllDocs.size()) {
            AllDocs[Cdoci]->printDocument();
        }
    }

    ~TextEditor() {
        for (auto doc : AllDocs) {
            delete doc;
        }
    }


};

