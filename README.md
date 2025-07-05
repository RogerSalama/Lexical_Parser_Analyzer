# Python Compiler Lexical Analyzer 🐍
## Aim of the Project 🎯
The goal is to build a lexical analyzer and parser for Python, forming the initial stages of a compiler. The lexical analyzer converts Python source code into a stream of tokens, while the parser processes these tokens to validate syntax and construct a parsing tree, handling indentation, maintaining a symbol table, and detecting lexical and syntactic errors to prepare for semantic analysis.
## Algorithm Used 🛠️
 - Finite State Machine (FSM) 🔄: Processes input character by character, transitioning between states (e.g., START, INTEGER, FLOAT, IDENTIFIER, STRINGS, OPERATORS, COMMENT, ERROR) to identify tokens like keywords, identifiers, literals, operators, and delimiters.
 - LL(1) Parsing 🌳: The parser uses an LL(1) (Left-to-right, Leftmost derivation, 1-token lookahead) algorithm, a top-down predictive parsing method. It constructs a parse tree by matching tokens against a context-free grammar for Python, ensuring deterministic parsing with a single-token lookahead.
---
## Features ✨

#### Tokenization 🔍: Categorizes Python tokens (keywords, identifiers, integers, floats, strings, operators, delimiters).
#### Syntax Parsing 🌲: Validates Python syntax using LL(1) parsing, constructing a parse tree to represent the program’s structure.
#### Indentation Tracking 🧩: Manages Python’s indentation rules, producing INDENT/DEDENT tokens for block structures.
#### Symbol Table 📊: Maintains a table for identifier details (name, value, type) for later compilation stages.
#### Error Detection 🕵️: Identifies lexical errors with detailed messages (e.g., "Invalid char: @ 😕", "Unterminated String 😣").
#### Parse Tree Visualization 📈: Generates a hierarchical parse tree, displayed in the GUI or as output, showing the syntactic structure of the code.
#### Qt-based GUI 🖥️:
  - Numbered Lines 🔢: Shows line numbers for easy code navigation and error tracking.
  - Theme Switching 🌙☀️: Supports light and dark themes for better readability.
  - File Loading 📂: Loads Python (.py) files into the code textarea with file type validation.

## Prerequisites 🛠️:

  - Install Qt framework (compatible version, e.g., Qt 4 or later).
  - Ensure a C++ compiler (e.g., g++) is installed.

## Build the Project 🔨:
  - Open in Qt Creator or a compatible IDE.
  - Configure to include Qt libraries.

## Demo of the App 🖱️:
See the lexical analyzer/Parser in action with this demo video! It shows how to load a Python file, run the analysis, switch themes, and view tokens/errors in the GUI. 🎬
Go to file named "DemoVideo.mp4"


