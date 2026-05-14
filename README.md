# Bscs23107 Text Editor

A feature-rich, keyboard-driven console text editor written in modern C++ for Windows. Built from scratch as a Data Structures project, it uses custom linked-list and dynamic-array implementations under the hood — no `std::string`-based shortcuts for the document body — and ships with everything you'd expect from a real editor plus a few delightful extras (password-protected files, a built-in word game, document statistics, file merging, and more).

![Platform](https://img.shields.io/badge/platform-Windows-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B17-00599C)
![Build](https://img.shields.io/badge/build-Visual%20Studio%20%7C%20MinGW-success)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

---

## Table of Contents

- [Preview](#preview)
- [Features](#features)
- [Keyboard Shortcuts](#keyboard-shortcuts)
- [Getting Started](#getting-started)
- [Project Structure](#project-structure)
- [Architecture](#architecture)
- [Roadmap](#roadmap)
- [Acknowledgements](#acknowledgements)

---

## Preview

**Welcome screen — create or open a document, with optional password protection**

![Welcome screen](screenshots/01_welcome.png)

**The editor itself — full cursor navigation, real-time rendering**

![Editor in use](screenshots/02_editor.png)

**Search & statistics — find words, count occurrences, analyze the document**

![Search and statistics](screenshots/03_search.png)

**Word Game — guess a hidden word picked from your own document**

![Word Game](screenshots/04_wordgame.png)

---

## Features

### Editing essentials
- Create a brand new document or open an existing one
- Optional **password protection** when creating a file
- Insert any printable character at the cursor
- **Arrow-key** navigation (Up / Down / Left / Right)
- **Backspace** and **Delete** with intelligent line-wrap handling
- **Enter** splits the current line at the cursor and creates a new one
- Save to disk with a single shortcut

### Case operations
- Convert the current line to **UPPERCASE**
- Convert the current line to **lowercase**

### Search
- **Case-sensitive** word search
- **Case-insensitive** word search
- Whole-**sentence** search (multi-word lookup)
- **Substring** search (matches inside words)

### Replace
- Replace the **first** occurrence of a word
- Replace **all** occurrences of a word

### Text transformation
- Add a **prefix** to every occurrence of a chosen word
- Add a **postfix** to every occurrence of a chosen word

### Document analytics
- Average word length across the whole document
- Largest word and smallest word
- Substring frequency counter
- Special character count

### Extras
- **Word Game** — the editor picks a word from your document and you guess it letter by letter
- **Merge files** — combine two `.txt` files into the open document

---

## Keyboard Shortcuts

| Shortcut | Action |
|----------|--------|
| `Arrow keys` | Move cursor |
| `Enter` | Insert new line at cursor |
| `Backspace` | Delete character before cursor |
| `Delete` | Delete character at cursor |
| `Ctrl + O` | Save the current document |
| `Ctrl + U` | Convert current line to UPPERCASE |
| `Ctrl + L` | Convert current line to lowercase |
| `Ctrl + F` | Find a word (case-sensitive) |
| `Ctrl + W` | Find a word (case-insensitive) |
| `Ctrl + N` | Find a full sentence |
| `Ctrl + B` | Find a substring |
| `Ctrl + R` | Replace first occurrence of a word |
| `Ctrl + E` | Replace all occurrences of a word |
| `Ctrl + G` | Add a prefix to a chosen word |
| `Ctrl + I` | Add a postfix to a chosen word |
| `Ctrl + A` | Show average word length |
| `Ctrl + D` | Count a substring's occurrences |
| `Ctrl + K` | Count special characters |
| `Ctrl + Y` | Find the largest word |
| `Ctrl + Z` | Find the smallest word |
| `Ctrl + X` | Launch the Word Game |
| `Ctrl + P` | Merge two `.txt` files into the document |

> Tip: every action that takes input (search term, replacement word, filename, etc.) prompts you for it at the bottom of the screen and then re-renders the document.

---

## Getting Started

### Requirements

- **Windows** (the editor uses `<conio.h>` and `<Windows.h>` for raw keyboard input and console cursor control)
- A C++17-capable compiler — any of:
  - **Visual Studio 2019 / 2022** with the *Desktop development with C++* workload (recommended; the repo ships with a ready-made solution)
  - **MinGW-w64** (`g++`) for the command line
  - **Clang** for Windows

### Option 1 — Visual Studio (recommended)

1. Clone the repository:
   ```bash
   git clone https://github.com/Obsi19/Bscs23107_Text_Editor.git
   cd Bscs23107_Text_Editor
   ```
2. Open `Bscs23107_Text_Editor.sln` in Visual Studio.
3. Select the **Release** configuration and an **x64** target.
4. Press `Ctrl + F5` to build and run.

### Option 2 — Command line (MinGW-w64)

From the project root, run:

```bash
g++ -std=c++17 Bscs23107_Text_Editor.cpp -o TextEditor.exe
./TextEditor.exe
```

That's it — there's nothing else to link and no external dependencies.

### Cross-compiling from Linux

If you're on Linux and just want to verify a build, MinGW will happily produce a valid `.exe`:

```bash
sudo apt install mingw-w64
x86_64-w64-mingw32-g++ -std=c++17 Bscs23107_Text_Editor.cpp -o TextEditor.exe
```

(You'll need Wine or an actual Windows machine to run the resulting binary — the runtime uses the Win32 console API.)

### First run

On startup you'll be greeted with three choices:

```
 I WELCOME YOU TO MY TEXT EDITOR

Press 1 to create a new document
Press 2 to open an existing document
Press 3 to exit
```

- Choose **1** and enter a filename (without `.txt`). You'll be asked whether you'd like a password on the file.
- Choose **2** and enter the name of an existing `.txt` file in the working directory to open it.

Once a document is open, you're in editing mode — just type, navigate, and use the shortcuts above.

---

## Project Structure

```
Bscs23107_Text_Editor/
├── Bscs23107_Text_Editor.cpp        # Program entry point
├── TextEditor.h                     # Main controller: input loop & menu
├── Document.h                       # Doc class: file I/O, all text operations
├── Line.h                           # Line class: a linked list of characters
├── Paragraph.h                      # Para class (reserved for future use)
├── Bscs23107_Text_Editor.sln        # Visual Studio solution
├── Bscs23107_Text_Editor.vcxproj    # Visual Studio project file
├── test1.txt, text2.txt, ...        # Sample documents
└── screenshots/                     # Project screenshots
```

---

## Architecture

The editor is built around three nested classes, each owning the layer below it:

```
TextEditor
   │
   ├── std::vector<Doc*>              ← all open documents
   │
   Doc
   │
   ├── Line[] lines                   ← dynamic array of lines
   │
   Line
   │
   └── std::list<letter>              ← linked list of characters
```

- **`Line`** stores its characters as a `std::list<letter>` of singly-linked character nodes. This makes single-character insertion and deletion at any position cheap — the operations the editor calls most often.
- **`Doc`** owns a heap-allocated array of `Line` objects, plus the filename, password and lock state. It handles loading from disk, saving to disk, and every text-manipulation feature (search, replace, statistics, the word game, prefix/postfix, etc.).
- **`TextEditor`** is the controller. It runs the main loop, reads keyboard input with `_kbhit()` / `_getch()`, decodes special keys (arrow keys, Ctrl combinations), routes them to the right `Doc` method, and repaints by calling `printdoc()`.

Cursor positioning is handled by a small helper, `gotoRowCol(row, col)` in `Line.h`, which wraps `SetConsoleCursorPosition` from the Win32 console API.

---

## Roadmap

A few things that would round the editor out nicely:

- Undo / redo stack
- Word-wrap for lines longer than the console width
- Syntax highlighting for `.cpp` / `.py` / `.md`
- Mouse-based cursor positioning
- Status bar with line/column indicator and document name
- A cross-platform port using `ncurses` instead of `conio.h` + `Windows.h`

---

## Acknowledgements

Built as part of the **BSCS Data Structures** coursework. Thanks to anyone who tries it, files an issue, or sends a PR.

If you find a bug or have a suggestion, please open an issue on the [GitHub repository](https://github.com/Obsi19/Bscs23107_Text_Editor).
