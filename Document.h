#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
#include "Line.h"
#include <unordered_map>

using namespace std;

class Doc
{
	friend class TextEditor;
    Line* lines;                
    int cursorRow, cursorCol;   
    int NoOfLines;              
	string Dname;               
	bool Locked = true;		 
	string Password = "hello";			 


public:
	
	// Function to load the document from the file (change it)
    void load()
    {
        ifstream file(Dname);
        if (!file.is_open())
        {
            cout << "Error: Could not open file " << Dname << endl;
            return;
        }

        string lineContent;
        NoOfLines = 0;

        while (getline(file, lineContent))
        {
            NoOfLines++;
        }

        file.close();
        file.open(Dname);

        if (NoOfLines > 0)
        {
            lines = new Line[NoOfLines]; // Allocate memory for lines
        }

        int row = 0, col = 0;
        char character;

        while (file.get(character)) // Read character by character
        {
            if (character == '\n') // Newline encountered
            {
                row++;
                col = 0;
            }
            else
            {
                lines[row].InsertChar(col, character); // Insert character at the current position
                col++;
            }
        }

        file.close(); // Close the file after reading
    }

    Doc(string name) : Dname(name), cursorRow(0), cursorCol(0), NoOfLines(0), lines(nullptr) {}
	Doc(string name, bool first);
	~Doc()
	{
		delete[] lines;
	}
    void printdoc();
	void saveFile(string name);
	void InsertAChar(int row, int col, char c);
	void delChar(int row, int col);
	void backspaceChar(int row, int col);
    void InsertNewLineAt(int row, int col);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ToUpperLine(int ri, int ci);
	void ToLowerLine(int ri, int ci);
    void FindWordCaseSensitive(const string& word);
	void FindWordCaseInsensitive(const string& word);
    void FindSentence(const string& sentence);
    void FindSubstring(const string& substring);
    void ReplaceFirstOccurrence(const string& oldWord, const string& newWord);
    void ReplaceAllOccurrences(const string& oldWord, const string& newWord);
	void AvgWordLength();
	void AddPrefixToWord(const string& word, const string& prefix);
	void AddPostfixToWord(const string& word, const string& postfix);
	void SubstringCount(const string& substring);
	void FindSpecialCharactersCount();
	void FindLargestWord();
	void FindSmallestWord();
    void WordGame();
   // void FindReplaceFromCursor(int startRow, int startCol, const string& target, const string& replacement, bool forward = true, bool replaceAll = false);
    void mergeFiles(const string& file1, const string& file2);








};


void SetTextColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

Doc::Doc(string name, bool first)
{
    Dname = name;
    if (first)
    {
		cout << " if you want protection for the file (Yes:Y or y)||(No:any) ";
		char ch;
		cin >> ch;
        if (ch == 'y' || ch == 'Y') { Locked = true; cout << "enter password" << endl; cin >> Password;}
        
       
        NoOfLines = 0;
        cursorCol = 0;
        cursorRow = 0;
        lines = new Line; 

        ofstream file(Dname, ios::out);
        if (file.is_open())
        {
            file << "Created New File";
            file.close();
        }
        else
        {
            cerr << "Error: Unable to create file " << Dname << endl;
        }
    }
    else {
        if (Locked)
        {
            string pass;
            cout << "Enter Password: ";
            do
            {
                cin >> pass;


                if (pass != Password) {
                    cout << "Incorrect Password. Enter Again" << endl;
                }

            } while (pass != Password);


        }
         
    }
    load();
}
void Doc::printdoc()
{
	system("cls");
	gotoRowCol(0, 0);

	for (int i = 0; i < NoOfLines; i++)
	{
		lines[i].PrintLine();
	}
}
void Doc::saveFile(string Dname)
{
    ofstream file(Dname); // Open the file for writing
    if (!file.is_open())
    {
        cout << "Error: Could not open file " << Dname << " for saving." << endl;
        return;
    }

    for (int i = 0; i < NoOfLines; i++)
    {
        lines[i].SaveLine(file); // Use the SaveLine function from the Line class
    }

    file.close();
    cout << "Document saved successfully to " << Dname << endl;
}
void Doc::InsertAChar(int row, int col, char c)
{
    lines[row].InsertChar(col, c);
}
void Doc::delChar(int row, int col)
{
	lines[row].DelCharAt(col);
}
void Doc::backspaceChar(int row, int col)
{
	lines[row].BackSpaceChar(col);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Doc::InsertNewLineAt(int row, int col)
{
    if (row < 0 || row >= NoOfLines) {
        cout << "Invalid row" << endl;
        return;
    }

    Line* newLines = new Line[NoOfLines + 1]; 
    int newRowIndex = 0;

    for (int i = 0; i < NoOfLines; ++i) {
        if (i == row) {
            Line newLineBefore;
            auto it = lines[row].Cs.begin();
            for (int c = 0; c < col && it != lines[row].Cs.end(); ++c, ++it) {
                newLineBefore.InsertChar(newLineBefore.Size, it->ch);
            }
            newLines[newRowIndex++] = newLineBefore;

            Line newLineAfter;
            while (it != lines[row].Cs.end()) {
                newLineAfter.InsertChar(newLineAfter.Size, it->ch);
                ++it;
            }
            newLines[newRowIndex++] = newLineAfter;
        }
        else {
            newLines[newRowIndex++] = lines[i]; 
        }
    }

    delete[] lines;        
    lines = newLines;      
    NoOfLines++;           
}
void Doc::ToUpperLine(int ri, int ci)
{
    if (ri < 0 || ri >= NoOfLines) {
        cout << "Invalid row index" << endl;
        return;
    }

    Line& currentLine = lines[ri]; 
    auto it = currentLine.Cs.begin();
    int colIndex = 0;

    bool insideWord = false;
    auto wordStart = it;
    auto wordEnd = it;

    for (; it != currentLine.Cs.end(); ++it, ++colIndex) {
        if (colIndex == ci && isalpha(it->ch)) {
            insideWord = true;
        }

        if (insideWord) {
            if (isalpha(it->ch)) {
                wordEnd = it;
            }
            else {
                break;
            }
        }
        else {
            if (isalpha(it->ch)) {
                wordStart = it;
            }
        }
    }

    if (insideWord) {
        for (auto iter = wordStart; iter != next(wordEnd); ++iter) {
            iter->ch = toupper(iter->ch);
        }
    }
    else {
        for (auto& letter : currentLine.Cs) {
            letter.ch = toupper(letter.ch);
        }
    }
}
void Doc::ToLowerLine(int ri, int ci)
{
    if (ri < 0 || ri >= NoOfLines) {
        cout << "Invalid row index" << endl;
        return;
    }

    Line& currentLine = lines[ri]; 
    auto it = currentLine.Cs.begin();
    int colIndex = 0;

    bool insideWord = false;
    auto wordStart = it;
    auto wordEnd = it;

    for (; it != currentLine.Cs.end(); ++it, ++colIndex) {
        if (colIndex == ci && isalpha(it->ch)) {
            insideWord = true;
        }

        if (insideWord) {
            if (isalpha(it->ch)) {
                wordEnd = it; 
            }
            else {
                break; 
            }
        }
        else {
            if (isalpha(it->ch)) {
                wordStart = it;
            }
        }
    }

    if (insideWord) {
        for (auto iter = wordStart; iter != next(wordEnd); ++iter) {
            iter->ch = tolower(iter->ch);
        }
    }
    else {
        for (auto& letter : currentLine.Cs) {
            letter.ch = tolower(letter.ch);
        }
    }
}
void Doc::FindWordCaseSensitive(const string& word)
{
    bool found = false;

    for (int i = 0; i < NoOfLines; ++i) {
        string lineContent;
        for (const letter& ltr : lines[i].Cs) {
            lineContent += ltr.ch;
        }

        size_t pos = lineContent.find(word); 
        if (pos != string::npos) {
            found = true;
        }

        if (found)
        {
            for (size_t j = 0; j < lineContent.size(); ++j) {
                if (pos != string::npos && j >= pos && j < pos + word.length())
                {
                    SetTextColor(10); // Green color 
                    cout << lineContent[j];
                    SetTextColor(7);
                }
                else 
                {
                    cout << lineContent[j];
                }
            }
            cout << endl;
        }
    }

    gotoRowCol(0, 28);
    if (!found) {
        cout << "Word '" << word << "' not found in the document." << endl;
    }
}
void Doc::FindWordCaseInsensitive(const string& word)
{
    auto toLower = [](char c) { return tolower(static_cast<unsigned char>(c)); };
    bool found = false;

    for (int i = 0; i < NoOfLines; ++i) {
        string lineContent;
        for (const letter& ltr : lines[i].Cs) {
            lineContent += ltr.ch;
        }

        string lowerLine, lowerWord;
        for (char c : lineContent) lowerLine += toLower(c);
        for (char c : word) lowerWord += toLower(c);

        size_t pos = lowerLine.find(lowerWord); 
        if (pos != string::npos) {
            found = true;
        }
        if (found) {

            for (size_t j = 0; j < lineContent.size(); ++j) {
                if (pos != string::npos && j >= pos && j < pos + word.length()) {
                    SetTextColor(10); // Green color
                    cout << lineContent[j];
                    SetTextColor(7);  // Reset 
                }
                else {
                    cout << lineContent[j];
                }
            }
            cout << endl;
        }
    }

    gotoRowCol(0, 28); 
    if (!found) {
        cout << "Word '" << word << "' not found in the document." << endl;
    }
}
void Doc::FindSentence(const string& sentence)
{
    bool found = false;

    for (int i = 0; i < NoOfLines; ++i) {
        string lineContent;
        for (const letter& ltr : lines[i].Cs) {
            lineContent += ltr.ch;
        }

        size_t pos = lineContent.find(sentence); 
        if (pos != string::npos) {
            found = true;
        }

        if (found) {
            for (size_t j = 0; j < lineContent.size(); ++j) {
                if (pos != string::npos && j >= pos && j < pos + sentence.length()) {
                    SetTextColor(11); // Cyan color
                    cout << lineContent[j];
                    SetTextColor(7);  // Reset
                }
                else {
                    cout << lineContent[j];
                }
            }
            cout << endl;
        }
    }

    gotoRowCol(0, 28); 
    if (!found){
        cout << "Sentence '" << sentence << "' not found in the document." << endl;
    }
}
void Doc::FindSubstring(const string& substring)
{
    bool found = false;

    for (int i = 0; i < NoOfLines; ++i) {
        string lineContent;
        for (const letter& ltr : lines[i].Cs) {
            lineContent += ltr.ch;
        }

        size_t pos = lineContent.find(substring); 
        if (pos != string::npos) {
            found = true;
        }

        if (found) {
            for (size_t j = 0; j < lineContent.size(); ++j) {
                if (pos != string::npos && j >= pos && j < pos + substring.length()) {
                    SetTextColor(14); // Yellow color
                    cout << lineContent[j];
                    SetTextColor(7);  // Reset
                }
                else {
                    cout << lineContent[j];
                }
            }
            cout << endl;
        }
    }

    gotoRowCol(0, 28); 
    if (!found) {
        cout << "Substring '" << substring << "' not found in the document." << endl;
    }
}
void Doc::ReplaceFirstOccurrence(const string& oldWord, const string& newWord)
{
    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        size_t pos = lineContent.find(oldWord);
        if (pos != string::npos)
        {
            lineContent.replace(pos, oldWord.length(), newWord);

            // Update the line
            lines[i] = Line(lineContent);
            cout << "Replaced the first occurrence of '" << oldWord << "' with '" << newWord << "'." << endl;
            return; 
        }
    }
    cout << "Word '" << oldWord << "' not found in the document." << endl;
}
void Doc::ReplaceAllOccurrences(const string& oldWord, const string& newWord)
{
    bool replaced = false;

    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        size_t pos = 0;
        while ((pos = lineContent.find(oldWord, pos)) != string::npos) 
        {
            lineContent.replace(pos, oldWord.length(), newWord);
            pos += newWord.length(); 
            replaced = true;
        }

        lines[i] = Line(lineContent);
    }

    if (replaced)
    {
        cout << "Replaced all occurrences of '" << oldWord << "' with '" << newWord << "'." << endl;
    }
    else
    {
        cout << "Word '" << oldWord << "' not found in the document." << endl;
    }
}
void Doc::AvgWordLength()
{
    int totalWords = 0;
    int totalLength = 0;

    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        stringstream rdr(lineContent);
        string word;
        while (rdr >> word)
        {
            totalWords++;
            totalLength += word.length();
        }
    }

    if (totalWords > 0)
    {
        double avgLength = static_cast<double>(totalLength) / totalWords;
        cout << "The average word length in the file is: " << avgLength << " words." << endl;
    }
    else
    {
        cout << "No words found in the file." << endl;
    }
}
void Doc::AddPrefixToWord(const string& word, const string& prefix)
{
    bool replaced = false;

    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        size_t pos = 0;
        while ((pos = lineContent.find(word, pos)) != string::npos)
        {
            lineContent.replace(pos, word.length(), prefix + word); 
            pos += (prefix + word).length(); 
            replaced = true;
        }
        lines[i] = Line(lineContent);
    }

    if (replaced)
    {
        cout << "Added prefix '" << prefix << "' to all occurrences of '" << word << "'." << endl;
    }
    else
    {
        cout << "Word '" << word << "' not found in the document." << endl;
    }
}
void Doc::AddPostfixToWord(const string& word, const string& postfix)
{
    bool replaced = false;

    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        size_t pos = 0;
        while ((pos = lineContent.find(word, pos)) != string::npos) 
        {
            lineContent.replace(pos, word.length(), word + postfix); 
            pos += (word + postfix).length(); 
            replaced = true;
        }
        lines[i] = Line(lineContent);
    }

    if (replaced)
    {
        cout << "Added postfix '" << postfix << "' to all occurrences of '" << word << "'." << endl;
    }
    else
    {
        cout << "Word '" << word << "' not found in the document." << endl;
    }
}
void Doc::SubstringCount(const string& substring)
{
    int count = 0;

    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        size_t pos = 0;
        while ((pos = lineContent.find(substring, pos)) != string::npos)
        {
            count++;
            pos += substring.length(); // Move past the current match
        }
    }

    cout << "The substring '" << substring << "' appears " << count << " times in the document." << endl;
}
void Doc::FindSpecialCharactersCount()
{
    int count = 0;

    for (int i = 0; i < NoOfLines; ++i)
    {
        for (const letter& ltr : lines[i].Cs)
        {
            if (!isalnum(ltr.ch) && !isspace(ltr.ch)) // Exclude alphanumeric and whitespace
            {
                count++;
            }
        }
    }

    cout << "The document contains " << count << " special characters." << endl;
}
void Doc::FindLargestWord()
{
    int maxLength = 0;
    string largestWord;

    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        stringstream ss(lineContent);
        string word;
        while (ss >> word)
        {
            if (word.length() > maxLength)
            {
                maxLength = word.length();
                largestWord = word;
            }
        }
    }

    if (!largestWord.empty())
    {
        cout << "The largest word in the document is: '" << largestWord << "' with length " << maxLength << endl;
    }
    else
    {
        cout << "No words found in the document." << endl;
    }
}
void Doc::FindSmallestWord()
{
    int minLength = 100000000;
    string smallestWord;

    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        stringstream ss(lineContent);
        string word;
        while (ss >> word)
        {
            if (word.length() < minLength)
            {
                minLength = word.length();
                smallestWord = word;
            }
        }
    }

    if (minLength == 100000000)
    {
        cout << "No words found in the document." << endl;
    }
    else
    {
        cout << "The smallest word in the document is: '" << smallestWord << "' with length " << minLength << endl;
    }
}
void Doc::WordGame()
{
    vector<string> words;
    vector<unordered_map<char, int>> frequencyMaps;

    // Extract all words and create frequency maps
    for (int i = 0; i < NoOfLines; ++i)
    {
        string lineContent;
        for (const letter& ltr : lines[i].Cs)
        {
            lineContent += ltr.ch;
        }

        string currentWord;
        for (char c : lineContent)
        {
            if (isalnum(c))
                currentWord += tolower(c);
            else if (!currentWord.empty())
            {
                words.push_back(currentWord);

                unordered_map<char, int> freqMap;
                for (char ch : currentWord)
                    freqMap[ch]++;
                frequencyMaps.push_back(freqMap);

                currentWord.clear();
            }
        }

        if (!currentWord.empty())
        {
            words.push_back(currentWord);
            unordered_map<char, int> freqMap;
            for (char ch : currentWord)
                freqMap[ch]++;
            frequencyMaps.push_back(freqMap);
        }
    }

    // Compare frequency maps to determine the best word
    int maxScore = 0;
    string bestWord;
    vector<string> formableWords;

    for (size_t i = 0; i < words.size(); ++i)
    {
        int score = 0;
        vector<string> currentFormableWords;

        for (size_t j = 0; j < words.size(); ++j)
        {
            if (i == j) continue;

            bool canForm = true;
            for (const auto& pair : frequencyMaps[j])
            {
                if (frequencyMaps[i][pair.first] < pair.second)
                {
                    canForm = false;
                    break;
                }
            }

            if (canForm)
            {
                score++;
                currentFormableWords.push_back(words[j]);
            }
        }

        if (score > maxScore)
        {
            maxScore = score;
            bestWord = words[i];
            formableWords = currentFormableWords;
        }
    }

    // Output the result
    if (!bestWord.empty())
    {
        cout << "The best word is: '" << bestWord << "' with a score of " << maxScore << "." << endl;
        cout << "Words that can be formed:" << endl;
        for (const string& word : formableWords)
        {
            cout << " - " << word << endl;
        }
    }
    else
    {
        cout << "No valid word found for the Word-Game." << endl;
    }
}
/*void Doc::FindReplaceFromCursor(int startRow, int startCol, const string& target, const string& replacement, bool forward = true, bool replaceAll = false)
{
    bool replaced = false;

    if (forward)
    {
        for (int i = startRow; i < NoOfLines; ++i)
        {
            string lineContent;
            for (const letter& ltr : lines[i].Cs)
            {
                lineContent += ltr.ch;
            }

            size_t pos = (i == startRow) ? lineContent.find(target, startCol) : lineContent.find(target);
            while (pos != string::npos)
            {
                lineContent.replace(pos, target.length(), replacement);
                lines[i] = Line(lineContent);
                replaced = true;

                if (!replaceAll) return; // Replace only the first occurrence
                pos = lineContent.find(target, pos + replacement.length());
            }
        }
    }
    else
    {
        for (int i = startRow; i >= 0; --i)
        {
            string lineContent;
            for (const letter& ltr : lines[i].Cs)
            {
                lineContent += ltr.ch;
            }

            size_t pos = (i == startRow) ? lineContent.rfind(target, startCol) : lineContent.rfind(target);
            while (pos != string::npos)
            {
                lineContent.replace(pos, target.length(), replacement);
                lines[i] = Line(lineContent);
                replaced = true;

                if (!replaceAll) return; // Replace only the first occurrence
                pos = (pos == 0) ? string::npos : lineContent.rfind(target, pos - 1);
            }
        }
    }

    if (replaced)
    {
        cout << "Replacement complete." << endl;
    }
    else
    {
        cout << "Target word not found from current cursor position." << endl;
    }
}
*/
void Doc::mergeFiles(const string& fname1, const string& fname2) {
    ifstream file1(fname1), file2(fname2);
    if (!file1.is_open() || !file2.is_open()) {
        cout << "Error: Unable to open one or both input files." << endl;
        return;
    }

    cout << "Enter the name of the output file: ";
    string newFileName;
    cin >> newFileName;
    newFileName += ".txt";

    ofstream outFile(newFileName);
    if (!outFile.is_open()) {
        cout << "Error: Unable to create the output file." << endl;
        return;
    }

    cout << "Choose merging mode:\n1. Interleave lines from both files\n2. Append file1 then file2\n3. Append file2 then file1\nEnter your choice: ";
    int choice;
    cin >> choice;

    string line1, line2;
    bool dataExists = true;

    if (choice == 1) {
        while (dataExists) {
            dataExists = false; 
            if (getline(file1, line1)) {
                outFile << line1 << endl;
                dataExists = true;
            }
            if (getline(file2, line2)) {
                outFile << line2 << endl;
                dataExists = true;
            }
        }
    }
    else if (choice == 2) {
        while (getline(file1, line1)) {
            outFile << line1 << endl;
        }
        while (getline(file2, line2)) {
            outFile << line2 << endl;
        }
    }
    else if (choice == 3) {
        while (getline(file2, line2)) {
            outFile << line2 << endl;
        }
        while (getline(file1, line1)) {
            outFile << line1 << endl;
        }
    }
    else {
        cout << "Invalid choice. No files were merged." << endl;
    }

    file1.close();
    file2.close();
    outFile.close();

    cout << "Files have been successfully merged into: " << newFileName << endl;
}

