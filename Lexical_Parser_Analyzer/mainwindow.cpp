#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ParseTree.h"
#include "ParseTreeNode.h"
#include "CustomGraphicsView.h"
#include <iostream>
#include <stack>
#include <unordered_set>
#include <string>
#include <QPainter>
#include <QTextBlock>
#include <QScrollBar>
#include <vector>
#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGraphicsView>
#include <QPointF>
using namespace std;
#define START 0
#define NUMBER 1
#define INTEGER 2
#define FLOAT_STATE 3
#define IDENTIFIER 4
#define STRINGS 5
#define OPERATORS 6
#define COMMENT 7
#define BRACKET 8
#define ERROR 9
#define InvalidChar 10
#define InvalidIdent 11
#define InvalidFloat 12
#define UnterminatedString 13
static int currentTokenIndex = 0;
map<string, map<string, string>> createParsingTable() {
    // Initialize the parsing table with all non-terminals and terminals
    map<string, map<string, string>> parsingTable;

    // List of all non-terminals
    vector<string> nonTerminals = {
        "program", "statement_list", "new_statement_list", "statement",
        "simple_statement", "simple_identifier_statement", "compound_statement",
        "print_statement", "is_print_comma", "return_statement",
        "return_bracket_statement", "bracket_return_bracket_statement", "return_if",
        "if_statement", "elif_statement", "else_statement", "while_statement",
        "for_statement", "is_newline_for", "in_range", "in_range_2",
        "function_definition", "is_parameter_list", "parameter_list",
        "more_parameter_list", "assignment_statement", "expression",
        "boolean_OR_operation", "boolean_AND_expression", "boolean_AND_operation",
        "boolean_NOT_expression", "boolean_NOT_operation", "comparison_expression",
        "comparison_operation", "bitwise_OR_expression", "bitwise_OR_operation",
        "bitwise_XOR_expression", "bitwise_XOR_operation", "bitwise_AND_expression",
        "bitwise_AND_operation", "bitwise_shift_expression", "bitwise_shift_operation",
        "arith_expr", "arith_operation", "term", "term_operation",
        "factor", "factor_operation", "primary", "is_function_call", "literal","string","statement_after_newline", "statement_list_after_newline_2"
    };
    vector<string> terminals = {
        "identifier", "numeric_literal", "'", "True", "False", "None",
        "(", ")", "return", "break", "continue", "print", "if", "while", "for", "def",
        "NEWLINE", "INDENT", "DEDENT", "elif", "else", ",", "or", "and", "not",
        "==", "!=", "<", ">", "<=", ">=", "&", "^", "<<", ">>", "+", "-", "*", "**",
        "/", "%", "=", ":", "$", "\""
    };
    // Initialize all entries to "null"
    for (const string& nt : nonTerminals) {
        for (const string& t : terminals) {
            parsingTable[nt][t] = ""; // Default value
        }
    }



    // Program
    parsingTable["program"]["identifier"] = "statement_list";
    parsingTable["program"]["return"] = "statement_list";
    parsingTable["program"]["break"] = "statement_list";
    parsingTable["program"]["continue"] = "statement_list";
    parsingTable["program"]["print"] = "statement_list";
    parsingTable["program"]["numeric_literal"] = "statement_list";
    parsingTable["program"]["'"] = "statement_list";
    parsingTable["program"]["\""] = "statement_list";
    parsingTable["program"]["True"] = "statement_list";
    parsingTable["program"]["False"] = "statement_list";
    parsingTable["program"]["None"] = "statement_list";
    parsingTable["program"]["("] = "statement_list";
    parsingTable["program"]["if"] = "statement_list";
    parsingTable["program"]["while"] = "statement_list";
    parsingTable["program"]["for"] = "statement_list";
    parsingTable["program"]["def"] = "statement_list";

    // Statement list
    parsingTable["statement_list"]["identifier"] = "statement new_statement_list";
    parsingTable["statement_list"]["return"] = "statement new_statement_list";
    parsingTable["statement_list"]["break"] = "statement new_statement_list";
    parsingTable["statement_list"]["continue"] = "statement new_statement_list";
    parsingTable["statement_list"]["print"] = "statement new_statement_list";
    parsingTable["statement_list"]["numeric_literal"] = "statement new_statement_list";
    parsingTable["statement_list"]["'"] = "statement new_statement_list";
    parsingTable["statement_list"]["\""] = "statement new_statement_list";
    parsingTable["statement_list"]["True"] = "statement new_statement_list";
    parsingTable["statement_list"]["False"] = "statement new_statement_list";
    parsingTable["statement_list"]["None"] = "statement new_statement_list";
    parsingTable["statement_list"]["("] = "statement new_statement_list";
    parsingTable["statement_list"]["if"] = "statement new_statement_list";
    parsingTable["statement_list"]["while"] = "statement new_statement_list";
    parsingTable["statement_list"]["for"] = "statement new_statement_list";
    parsingTable["statement_list"]["def"] = "statement new_statement_list";

    // New statement list
    parsingTable["new_statement_list"]["NEWLINE"] = "NEWLINE statement_list_after_newline";
    parsingTable["new_statement_list"]["$"] = "epsilon";
    parsingTable["new_statement_list"]["DEDENT"] = "epsilon";

    //statment after newline ginger shot
    parsingTable["statement_list_after_newline"]["identifier"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["return"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["break"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["continue"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["print"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["numeric_literal"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["'"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["\""] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["True"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["False"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["None"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["("] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["if"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["while"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["for"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["def"] = "statement statement_list_after_newline_2";
    parsingTable["statement_list_after_newline"]["DEDENT"] = "epsilon";
    parsingTable["statement_list_after_newline"]["$"] = "epsilon";


    //statment after newline 2
    parsingTable["statement_list_after_newline_2"]["NEWLINE"] = "NEWLINE statement_list_after_newline";
    parsingTable["statement_list_after_newline_2"]["DEDENT"] = "epsilon";
    parsingTable["statement_list_after_newline_2"]["$"] = "epsilon";



    // Statement
    parsingTable["statement"]["identifier"] = "simple_statement";
    parsingTable["statement"]["return"] = "simple_statement";
    parsingTable["statement"]["break"] = "simple_statement";
    parsingTable["statement"]["continue"] = "simple_statement";
    parsingTable["statement"]["print"] = "simple_statement";
    parsingTable["statement"]["numeric_literal"] = "simple_statement";
    parsingTable["statement"]["'"] = "simple_statement";
    parsingTable["statement"]["\""] = "simple_statement";
    parsingTable["statement"]["True"] = "simple_statement";
    parsingTable["statement"]["False"] = "simple_statement";
    parsingTable["statement"]["None"] = "simple_statement";
    parsingTable["statement"]["("] = "simple_statement";
    parsingTable["statement"]["if"] = "compound_statement";
    parsingTable["statement"]["while"] = "compound_statement";
    parsingTable["statement"]["for"] = "compound_statement";
    parsingTable["statement"]["def"] = "compound_statement";

    // Simple statement
    parsingTable["simple_statement"]["identifier"] = "identifier simple_identifier_statement";
    parsingTable["simple_statement"]["return"] = "return return_statement";
    parsingTable["simple_statement"]["break"] = "break";
    parsingTable["simple_statement"]["continue"] = "continue";
    parsingTable["simple_statement"]["print"] = "print_statement";
    parsingTable["simple_statement"]["numeric_literal"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_statement"]["'"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_statement"]["\""] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_statement"]["True"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_statement"]["False"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_statement"]["None"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_statement"]["("] = "( expression ) factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";

    // Simple identifier statement
    parsingTable["simple_identifier_statement"]["("] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["**"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["*"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["/"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["%"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["+"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["-"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["<<"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"][">>"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["&"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["^"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["|"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["<"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"][">"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["=="] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["!="] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["<="] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"][">="] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["not"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["and"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["or"] = "is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["simple_identifier_statement"]["="] = "assignment_statement";
    parsingTable["simple_identifier_statement"]["NEWLINE"] = "epsilon";
    parsingTable["simple_identifier_statement"]["$"] = "epsilon";
    parsingTable["simple_identifier_statement"]["DEDENT"] = "epsilon";

    // Compound statement
    parsingTable["compound_statement"]["if"] = "if_statement";
    parsingTable["compound_statement"]["while"] = "while_statement";
    parsingTable["compound_statement"]["for"] = "for_statement";
    parsingTable["compound_statement"]["def"] = "function_definition";


    // Print statement
    parsingTable["print_statement"]["print"] = "print ( expression return_if is_print_comma )";

    // Is print comma
    parsingTable["is_print_comma"][","] = ", expression return_if is_print_comma";
    parsingTable["is_print_comma"][")"] = "epsilon";

    // Return statement
    parsingTable["return_statement"]["identifier"] = "identifier is_function_call factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["return_statement"]["("] = "( expression return_bracket_statement";
    parsingTable["return_statement"]["numeric_literal"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["return_statement"]["'"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["return_statement"]["\""] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["return_statement"]["True"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["return_statement"]["False"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["return_statement"]["None"] = "literal factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation";
    parsingTable["return_statement"]["NEWLINE"] = "epsilon";
    parsingTable["return_statement"]["$"] = "epsilon";
    parsingTable["return_statement"]["DEDENT"] = "epsilon";

    // Return bracket statement
    parsingTable["return_bracket_statement"][")"] = ") bracket_return_bracket_statement";
    parsingTable["return_bracket_statement"]["if"] = "if expression else expression )";

    // Bracket return bracket statement
    parsingTable["bracket_return_bracket_statement"]["**"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["*"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["/"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["%"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["+"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["-"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["<<"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"][">>"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["&"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["^"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["|"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["<"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"][">"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["=="] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["!="] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["<="] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"][">="] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["not"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["and"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["or"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["if"] = "factor_operation term_operation arith_operation bitwise_shift_operation bitwise_AND_operation bitwise_XOR_operation bitwise_OR_operation comparison_operation boolean_NOT_operation boolean_AND_operation boolean_OR_operation return_if";
    parsingTable["bracket_return_bracket_statement"]["NEWLINE"] = "epsilon";
    parsingTable["bracket_return_bracket_statement"]["$"] = "epsilon";
    parsingTable["bracket_return_bracket_statement"]["DEDENT"] = "epsilon";

    // Return if
    parsingTable["return_if"]["if"] = "if expression else expression return_if";
    parsingTable["return_if"]["NEWLINE"] = "epsilon";
    parsingTable["return_if"]["$"] = "epsilon";
    parsingTable["return_if"]["DEDENT"] = "epsilon";
    parsingTable["return_if"][","] = "epsilon";
    parsingTable["return_if"][")"] = "epsilon";

    // If statement
    parsingTable["if_statement"]["if"] = "if expression : NEWLINE INDENT statement_list DEDENT elif_statement else_statement";

    // Elif statement
    parsingTable["elif_statement"]["elif"] = "elif expression : NEWLINE INDENT statement_list DEDENT elif_statement";
    parsingTable["elif_statement"]["else"] = "epsilon";
    parsingTable["elif_statement"]["NEWLINE"] = "epsilon";
    parsingTable["elif_statement"]["$"] = "epsilon";
    parsingTable["elif_statement"]["DEDENT"] = "epsilon";

    // Else statement
    parsingTable["else_statement"]["else"] = "else : NEWLINE INDENT statement_list DEDENT";
    parsingTable["else_statement"]["NEWLINE"] = "epsilon";
    parsingTable["else_statement"]["$"] = "epsilon";
    parsingTable["else_statement"]["DEDENT"] = "epsilon";

    // While statement
    parsingTable["while_statement"]["while"] = "while expression : NEWLINE INDENT statement_list DEDENT";

    // For statement
    parsingTable["for_statement"]["for"] = "for identifier in range ( expression in_range ) : is_newline_for";

    // Is newline for
    parsingTable["is_newline_for"]["NEWLINE"] = "NEWLINE INDENT statement_list DEDENT";
    parsingTable["is_newline_for"]["identifier"] = "statement_list";
    parsingTable["is_newline_for"]["return"] = "statement_list";
    parsingTable["is_newline_for"]["break"] = "statement_list";
    parsingTable["is_newline_for"]["continue"] = "statement_list";
    parsingTable["is_newline_for"]["print"] = "statement_list";
    parsingTable["is_newline_for"]["numeric_literal"] = "statement_list";
    parsingTable["is_newline_for"]["'"] = "statement_list";
    parsingTable["is_newline_for"]["\""] = "statement_list";
    parsingTable["is_newline_for"]["True"] = "statement_list";
    parsingTable["is_newline_for"]["False"] = "statement_list";
    parsingTable["is_newline_for"]["None"] = "statement_list";
    parsingTable["is_newline_for"]["("] = "statement_list";
    parsingTable["is_newline_for"]["if"] = "statement_list";
    parsingTable["is_newline_for"]["while"] = "statement_list";
    parsingTable["is_newline_for"]["for"] = "statement_list";
    parsingTable["is_newline_for"]["def"] = "statement_list";

    // In range
    parsingTable["in_range"][","] = ", expression in_range_2";
    parsingTable["in_range"][")"] = "epsilon";

    // In range 2
    parsingTable["in_range_2"][","] = ", expression";
    parsingTable["in_range_2"][")"] = "epsilon";

    // Function definition
    parsingTable["function_definition"]["def"] = "def identifier ( is_parameter_list ) : NEWLINE INDENT statement_list DEDENT";

    // Is parameter list
    parsingTable["is_parameter_list"]["identifier"] = "parameter_list";
    parsingTable["is_parameter_list"][")"] = "epsilon";

    // Parameter list
    parsingTable["parameter_list"]["identifier"] = "identifier more_parameter_list";

    // More parameter list
    parsingTable["more_parameter_list"][","] = ", identifier more_parameter_list";
    parsingTable["more_parameter_list"][")"] = "epsilon";

    // Assignment statement
    parsingTable["assignment_statement"]["="] = "= expression";

    // Expression
    parsingTable["expression"]["identifier"] = "boolean_AND_expression boolean_OR_operation";
    parsingTable["expression"]["numeric_literal"] = "boolean_AND_expression boolean_OR_operation";
    parsingTable["expression"]["'"] = "boolean_AND_expression boolean_OR_operation";
    parsingTable["expression"]["\""] = "boolean_AND_expression boolean_OR_operation";
    parsingTable["expression"]["True"] = "boolean_AND_expression boolean_OR_operation";
    parsingTable["expression"]["False"] = "boolean_AND_expression boolean_OR_operation";
    parsingTable["expression"]["None"] = "boolean_AND_expression boolean_OR_operation";
    parsingTable["expression"]["("] = "boolean_AND_expression boolean_OR_operation";

    // Boolean OR operation
    parsingTable["boolean_OR_operation"]["or"] = "or boolean_AND_expression boolean_OR_operation";
    parsingTable["boolean_OR_operation"]["NEWLINE"] = "epsilon";
    parsingTable["boolean_OR_operation"]["$"] = "epsilon";
    parsingTable["boolean_OR_operation"]["DEDENT"] = "epsilon";
    parsingTable["boolean_OR_operation"][")"] = "epsilon";
    parsingTable["boolean_OR_operation"]["if"] = "epsilon";
    parsingTable["boolean_OR_operation"][","] = "epsilon";
    parsingTable["boolean_OR_operation"]["else"] = "epsilon";
    parsingTable["boolean_OR_operation"][":"] = "epsilon";

    // Boolean AND expression
    parsingTable["boolean_AND_expression"]["identifier"] = "boolean_NOT_expression boolean_AND_operation";
    parsingTable["boolean_AND_expression"]["numeric_literal"] = "boolean_NOT_expression boolean_AND_operation";
    parsingTable["boolean_AND_expression"]["'"] = "boolean_NOT_expression boolean_AND_operation";
    parsingTable["boolean_AND_expression"]["\""] = "boolean_NOT_expression boolean_AND_operation";
    parsingTable["boolean_AND_expression"]["True"] = "boolean_NOT_expression boolean_AND_operation";
    parsingTable["boolean_AND_expression"]["False"] = "boolean_NOT_expression boolean_AND_operation";
    parsingTable["boolean_AND_expression"]["None"] = "boolean_NOT_expression boolean_AND_operation";
    parsingTable["boolean_AND_expression"]["("] = "boolean_NOT_expression boolean_AND_operation";


    // Boolean AND operation
    parsingTable["boolean_AND_operation"]["and"] = "and boolean_NOT_expression boolean_AND_operation";
    parsingTable["boolean_AND_operation"]["NEWLINE"] = "epsilon";
    parsingTable["boolean_AND_operation"]["$"] = "epsilon";
    parsingTable["boolean_AND_operation"]["DEDENT"] = "epsilon";
    parsingTable["boolean_AND_operation"][")"] = "epsilon";
    parsingTable["boolean_AND_operation"]["if"] = "epsilon";
    parsingTable["boolean_AND_operation"][","] = "epsilon";
    parsingTable["boolean_AND_operation"]["else"] = "epsilon";
    parsingTable["boolean_AND_operation"][":"] = "epsilon";
    parsingTable["boolean_AND_operation"]["or"] = "epsilon";

    // Boolean NOT expression
    parsingTable["boolean_NOT_expression"]["identifier"] = "comparison_expression boolean_NOT_operation";
    parsingTable["boolean_NOT_expression"]["numeric_literal"] = "comparison_expression boolean_NOT_operation";
    parsingTable["boolean_NOT_expression"]["'"] = "comparison_expression boolean_NOT_operation";
    parsingTable["boolean_NOT_expression"]["\""] = "comparison_expression boolean_NOT_operation";
    parsingTable["boolean_NOT_expression"]["True"] = "comparison_expression boolean_NOT_operation";
    parsingTable["boolean_NOT_expression"]["False"] = "comparison_expression boolean_NOT_operation";
    parsingTable["boolean_NOT_expression"]["None"] = "comparison_expression boolean_NOT_operation";
    parsingTable["boolean_NOT_expression"]["("] = "comparison_expression boolean_NOT_operation";



    // Boolean NOT operation
    parsingTable["boolean_NOT_operation"]["not"] = "not comparison_expression boolean_NOT_operation";
    parsingTable["boolean_NOT_operation"]["NEWLINE"] = "epsilon";
    parsingTable["boolean_NOT_operation"]["$"] = "epsilon";
    parsingTable["boolean_NOT_operation"]["DEDENT"] = "epsilon";
    parsingTable["boolean_NOT_operation"][")"] = "epsilon";
    parsingTable["boolean_NOT_operation"]["if"] = "epsilon";
    parsingTable["boolean_NOT_operation"][","] = "epsilon";
    parsingTable["boolean_NOT_operation"]["else"] = "epsilon";
    parsingTable["boolean_NOT_operation"][":"] = "epsilon";
    parsingTable["boolean_NOT_operation"]["or"] = "epsilon";
    parsingTable["boolean_NOT_operation"]["and"] = "epsilon";

    // Comparison expression
    parsingTable["comparison_expression"]["identifier"] = "bitwise_OR_expression comparison_operation";
    parsingTable["comparison_expression"]["numeric_literal"] = "bitwise_OR_expression comparison_operation";
    parsingTable["comparison_expression"]["'"] = "bitwise_OR_expression comparison_operation";
    parsingTable["comparison_expression"]["\""] = "bitwise_OR_expression comparison_operation";
    parsingTable["comparison_expression"]["True"] = "bitwise_OR_expression comparison_operation";
    parsingTable["comparison_expression"]["False"] = "bitwise_OR_expression comparison_operation";
    parsingTable["comparison_expression"]["None"] = "bitwise_OR_expression comparison_operation";
    parsingTable["comparison_expression"]["("] = "bitwise_OR_expression comparison_operation";


    // Comparison operation
    parsingTable["comparison_operation"]["=="] = "== bitwise_OR_expression comparison_operation";
    parsingTable["comparison_operation"]["!="] = "!= bitwise_OR_expression comparison_operation";
    parsingTable["comparison_operation"]["<"] = "< bitwise_OR_expression comparison_operation";
    parsingTable["comparison_operation"][">"] = "> bitwise_OR_expression comparison_operation";
    parsingTable["comparison_operation"]["<="] = "<= bitwise_OR_expression comparison_operation";
    parsingTable["comparison_operation"][">="] = ">= bitwise_OR_expression comparison_operation";
    parsingTable["comparison_operation"]["NEWLINE"] = "epsilon";
    parsingTable["comparison_operation"]["$"] = "epsilon";
    parsingTable["comparison_operation"]["DEDENT"] = "epsilon";
    parsingTable["comparison_operation"][")"] = "epsilon";
    parsingTable["comparison_operation"]["if"] = "epsilon";
    parsingTable["comparison_operation"][","] = "epsilon";
    parsingTable["comparison_operation"]["else"] = "epsilon";
    parsingTable["comparison_operation"][":"] = "epsilon";
    parsingTable["comparison_operation"]["or"] = "epsilon";
    parsingTable["comparison_operation"]["and"] = "epsilon";
    parsingTable["comparison_operation"]["not"] = "epsilon";

    // Bitwise OR expression
    parsingTable["bitwise_OR_expression"]["identifier"] = "bitwise_XOR_expression bitwise_OR_operation";
    parsingTable["bitwise_OR_expression"]["numeric_literal"] = "bitwise_XOR_expression bitwise_OR_operation";
    parsingTable["bitwise_OR_expression"]["'"] = "bitwise_XOR_expression bitwise_OR_operation";
    parsingTable["bitwise_OR_expression"]["\""] = "bitwise_XOR_expression bitwise_OR_operation";
    parsingTable["bitwise_OR_expression"]["True"] = "bitwise_XOR_expression bitwise_OR_operation";
    parsingTable["bitwise_OR_expression"]["False"] = "bitwise_XOR_expression bitwise_OR_operation";
    parsingTable["bitwise_OR_expression"]["None"] = "bitwise_XOR_expression bitwise_OR_operation";
    parsingTable["bitwise_OR_expression"]["("] = "bitwise_XOR_expression bitwise_OR_operation";

    // Bitwise OR operation
    parsingTable["bitwise_OR_operation"]["|"] = "| bitwise_XOR_expression bitwise_OR_operation";
    parsingTable["bitwise_OR_operation"]["NEWLINE"] = "epsilon";
    parsingTable["bitwise_OR_operation"]["$"] = "epsilon";
    parsingTable["bitwise_OR_operation"]["DEDENT"] = "epsilon";
    parsingTable["bitwise_OR_operation"][")"] = "epsilon";
    parsingTable["bitwise_OR_operation"]["if"] = "epsilon";
    parsingTable["bitwise_OR_operation"][","] = "epsilon";
    parsingTable["bitwise_OR_operation"]["else"] = "epsilon";
    parsingTable["bitwise_OR_operation"][":"] = "epsilon";
    parsingTable["bitwise_OR_operation"]["or"] = "epsilon";
    parsingTable["bitwise_OR_operation"]["and"] = "epsilon";
    parsingTable["bitwise_OR_operation"]["not"] = "epsilon";
    parsingTable["bitwise_OR_operation"]["<"] = "epsilon";
    parsingTable["bitwise_OR_operation"][">"] = "epsilon";
    parsingTable["bitwise_OR_operation"]["=="] = "epsilon";
    parsingTable["bitwise_OR_operation"]["!="] = "epsilon";
    parsingTable["bitwise_OR_operation"]["<="] = "epsilon";
    parsingTable["bitwise_OR_operation"][">="] = "epsilon";

    // Bitwise XOR expression
    parsingTable["bitwise_XOR_expression"]["identifier"] = "bitwise_AND_expression bitwise_XOR_operation";
    parsingTable["bitwise_XOR_expression"]["numeric_literal"] = "bitwise_AND_expression bitwise_XOR_operation";
    parsingTable["bitwise_XOR_expression"]["'"] = "bitwise_AND_expression bitwise_XOR_operation";

    parsingTable["bitwise_XOR_expression"]["\""] = "bitwise_AND_expression bitwise_XOR_operation";
    parsingTable["bitwise_XOR_expression"]["True"] = "bitwise_AND_expression bitwise_XOR_operation";
    parsingTable["bitwise_XOR_expression"]["False"] = "bitwise_AND_expression bitwise_XOR_operation";
    parsingTable["bitwise_XOR_expression"]["None"] = "bitwise_AND_expression bitwise_XOR_operation";
    parsingTable["bitwise_XOR_expression"]["("] = "bitwise_AND_expression bitwise_XOR_operation";


    // Bitwise XOR operation
    parsingTable["bitwise_XOR_operation"]["^"] = "^ bitwise_AND_expression bitwise_XOR_operation";
    parsingTable["bitwise_XOR_operation"]["NEWLINE"] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["$"] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["DEDENT"] = "epsilon";
    parsingTable["bitwise_XOR_operation"][")"] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["if"] = "epsilon";
    parsingTable["bitwise_XOR_operation"][","] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["else"] = "epsilon";
    parsingTable["bitwise_XOR_operation"][":"] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["or"] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["and"] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["not"] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["<"] = "epsilon";
    parsingTable["bitwise_XOR_operation"][">"] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["=="] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["!="] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["<="] = "epsilon";
    parsingTable["bitwise_XOR_operation"][">="] = "epsilon";
    parsingTable["bitwise_XOR_operation"]["|"] = "epsilon";

    // Bitwise AND expression
    parsingTable["bitwise_AND_expression"]["identifier"] = "bitwise_shift_expression bitwise_AND_operation";
    parsingTable["bitwise_AND_expression"]["numeric_literal"] = "bitwise_shift_expression bitwise_AND_operation";
    parsingTable["bitwise_AND_expression"]["'"] = "bitwise_shift_expression bitwise_AND_operation";
    parsingTable["bitwise_AND_expression"]["\""] = "bitwise_shift_expression bitwise_AND_operation";
    parsingTable["bitwise_AND_expression"]["True"] = "bitwise_shift_expression bitwise_AND_operation";
    parsingTable["bitwise_AND_expression"]["False"] = "bitwise_shift_expression bitwise_AND_operation";
    parsingTable["bitwise_AND_expression"]["None"] = "bitwise_shift_expression bitwise_AND_operation";
    parsingTable["bitwise_AND_expression"]["("] = "bitwise_shift_expression bitwise_AND_operation";


    // Bitwise AND operation
    parsingTable["bitwise_AND_operation"]["&"] = "& bitwise_shift_expression bitwise_AND_operation";
    parsingTable["bitwise_AND_operation"]["NEWLINE"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["$"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["DEDENT"] = "epsilon";
    parsingTable["bitwise_AND_operation"][")"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["if"] = "epsilon";
    parsingTable["bitwise_AND_operation"][","] = "epsilon";
    parsingTable["bitwise_AND_operation"]["else"] = "epsilon";
    parsingTable["bitwise_AND_operation"][":"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["or"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["and"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["not"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["<"] = "epsilon";
    parsingTable["bitwise_AND_operation"][">"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["=="] = "epsilon";
    parsingTable["bitwise_AND_operation"]["!="] = "epsilon";
    parsingTable["bitwise_AND_operation"]["<="] = "epsilon";
    parsingTable["bitwise_AND_operation"][">="] = "epsilon";
    parsingTable["bitwise_AND_operation"]["|"] = "epsilon";
    parsingTable["bitwise_AND_operation"]["^"] = "epsilon";

    // Bitwise shift expression
    parsingTable["bitwise_shift_expression"]["identifier"] = "arith_expr bitwise_shift_operation";
    parsingTable["bitwise_shift_expression"]["numeric_literal"] = "arith_expr bitwise_shift_operation";
    parsingTable["bitwise_shift_expression"]["'"] = "arith_expr bitwise_shift_operation";
    parsingTable["bitwise_shift_expression"]["\""] = "arith_expr bitwise_shift_operation";

    parsingTable["bitwise_shift_expression"]["True"] = "arith_expr bitwise_shift_operation";
    parsingTable["bitwise_shift_expression"]["False"] = "arith_expr bitwise_shift_operation";
    parsingTable["bitwise_shift_expression"]["None"] = "arith_expr bitwise_shift_operation";
    parsingTable["bitwise_shift_expression"]["("] = "arith_expr bitwise_shift_operation";


    // Bitwise shift operation
    parsingTable["bitwise_shift_operation"]["<<"] = "<< arith_expr bitwise_shift_operation";
    parsingTable["bitwise_shift_operation"][">>"] = ">> arith_expr bitwise_shift_operation";
    parsingTable["bitwise_shift_operation"]["NEWLINE"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["$"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["DEDENT"] = "epsilon";
    parsingTable["bitwise_shift_operation"][")"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["if"] = "epsilon";
    parsingTable["bitwise_shift_operation"][","] = "epsilon";
    parsingTable["bitwise_shift_operation"]["else"] = "epsilon";
    parsingTable["bitwise_shift_operation"][":"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["or"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["and"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["not"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["<"] = "epsilon";
    parsingTable["bitwise_shift_operation"][">"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["=="] = "epsilon";
    parsingTable["bitwise_shift_operation"]["!="] = "epsilon";
    parsingTable["bitwise_shift_operation"]["<="] = "epsilon";
    parsingTable["bitwise_shift_operation"][">="] = "epsilon";
    parsingTable["bitwise_shift_operation"]["|"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["^"] = "epsilon";
    parsingTable["bitwise_shift_operation"]["&"] = "epsilon";

    // Arithmetic expression
    parsingTable["arith_expr"]["identifier"] = "term arith_operation";
    parsingTable["arith_expr"]["numeric_literal"] = "term arith_operation";
    parsingTable["arith_expr"]["'"] = "term arith_operation";
    parsingTable["arith_expr"]["\""] = "term arith_operation";
    parsingTable["arith_expr"]["True"] = "term arith_operation";
    parsingTable["arith_expr"]["False"] = "term arith_operation";
    parsingTable["arith_expr"]["None"] = "term arith_operation";
    parsingTable["arith_expr"]["("] = "term arith_operation";



    // Arithmetic operation
    parsingTable["arith_operation"]["+"] = "+ term arith_operation";
    parsingTable["arith_operation"]["-"] = "- term arith_operation";
    parsingTable["arith_operation"]["NEWLINE"] = "epsilon";
    parsingTable["arith_operation"]["$"] = "epsilon";
    parsingTable["arith_operation"]["DEDENT"] = "epsilon";
    parsingTable["arith_operation"][")"] = "epsilon";
    parsingTable["arith_operation"]["if"] = "epsilon";
    parsingTable["arith_operation"][","] = "epsilon";
    parsingTable["arith_operation"]["else"] = "epsilon";
    parsingTable["arith_operation"][":"] = "epsilon";
    parsingTable["arith_operation"]["or"] = "epsilon";
    parsingTable["arith_operation"]["and"] = "epsilon";
    parsingTable["arith_operation"]["not"] = "epsilon";
    parsingTable["arith_operation"]["<"] = "epsilon";
    parsingTable["arith_operation"][">"] = "epsilon";
    parsingTable["arith_operation"]["=="] = "epsilon";
    parsingTable["arith_operation"]["!="] = "epsilon";
    parsingTable["arith_operation"]["<="] = "epsilon";
    parsingTable["arith_operation"][">="] = "epsilon";
    parsingTable["arith_operation"]["|"] = "epsilon";
    parsingTable["arith_operation"]["^"] = "epsilon";
    parsingTable["arith_operation"]["&"] = "epsilon";
    parsingTable["arith_operation"]["<<"] = "epsilon";
    parsingTable["arith_operation"][">>"] = "epsilon";

    // Term
    parsingTable["term"]["identifier"] = "factor term_operation";
    parsingTable["term"]["numeric_literal"] = "factor term_operation";
    parsingTable["term"]["'"] = "factor term_operation";
    parsingTable["term"]["\""] = "factor term_operation";
    parsingTable["term"]["True"] = "factor term_operation";
    parsingTable["term"]["False"] = "factor term_operation";
    parsingTable["term"]["None"] = "factor term_operation";
    parsingTable["term"]["("] = "factor term_operation";


    // Term operation
    parsingTable["term_operation"]["*"] = "* factor term_operation";
    parsingTable["term_operation"]["/"] = "/ factor term_operation";
    parsingTable["term_operation"]["%"] = "% factor term_operation";
    parsingTable["term_operation"]["NEWLINE"] = "epsilon";
    parsingTable["term_operation"]["$"] = "epsilon";
    parsingTable["term_operation"]["DEDENT"] = "epsilon";
    parsingTable["term_operation"][")"] = "epsilon";
    parsingTable["term_operation"]["if"] = "epsilon";
    parsingTable["term_operation"][","] = "epsilon";
    parsingTable["term_operation"]["else"] = "epsilon";
    parsingTable["term_operation"][":"] = "epsilon";
    parsingTable["term_operation"]["or"] = "epsilon";
    parsingTable["term_operation"]["and"] = "epsilon";
    parsingTable["term_operation"]["not"] = "epsilon";
    parsingTable["term_operation"]["<"] = "epsilon";
    parsingTable["term_operation"][">"] = "epsilon";
    parsingTable["term_operation"]["=="] = "epsilon";
    parsingTable["term_operation"]["!="] = "epsilon";
    parsingTable["term_operation"]["<="] = "epsilon";
    parsingTable["term_operation"][">="] = "epsilon";
    parsingTable["term_operation"]["|"] = "epsilon";
    parsingTable["term_operation"]["^"] = "epsilon";
    parsingTable["term_operation"]["&"] = "epsilon";
    parsingTable["term_operation"]["<<"] = "epsilon";
    parsingTable["term_operation"][">>"] = "epsilon";
    parsingTable["term_operation"]["+"] = "epsilon";
    parsingTable["term_operation"]["-"] = "epsilon";

    // Factor
    parsingTable["factor"]["identifier"] = "primary factor_operation";
    parsingTable["factor"]["numeric_literal"] = "primary factor_operation";
    parsingTable["factor"]["'"] = "primary factor_operation";
    parsingTable["factor"]["\""] = "primary factor_operation";
    parsingTable["factor"]["True"] = "primary factor_operation";
    parsingTable["factor"]["False"] = "primary factor_operation";
    parsingTable["factor"]["None"] = "primary factor_operation";
    parsingTable["factor"]["("] = "primary factor_operation";


    // Factor operation
    parsingTable["factor_operation"]["**"] = "** primary factor_operation";
    parsingTable["factor_operation"]["NEWLINE"] = "epsilon";
    parsingTable["factor_operation"]["$"] = "epsilon";
    parsingTable["factor_operation"]["DEDENT"] = "epsilon";
    parsingTable["factor_operation"][")"] = "epsilon";
    parsingTable["factor_operation"]["if"] = "epsilon";
    parsingTable["factor_operation"][","] = "epsilon";
    parsingTable["factor_operation"]["else"] = "epsilon";
    parsingTable["factor_operation"][":"] = "epsilon";
    parsingTable["factor_operation"]["or"] = "epsilon";
    parsingTable["factor_operation"]["and"] = "epsilon";
    parsingTable["factor_operation"]["not"] = "epsilon";
    parsingTable["factor_operation"]["<"] = "epsilon";
    parsingTable["factor_operation"][">"] = "epsilon";
    parsingTable["factor_operation"]["=="] = "epsilon";
    parsingTable["factor_operation"]["!="] = "epsilon";
    parsingTable["factor_operation"]["<="] = "epsilon";
    parsingTable["factor_operation"][">="] = "epsilon";
    parsingTable["factor_operation"]["|"] = "epsilon";
    parsingTable["factor_operation"]["^"] = "epsilon";
    parsingTable["factor_operation"]["&"] = "epsilon";
    parsingTable["factor_operation"]["<<"] = "epsilon";
    parsingTable["factor_operation"][">>"] = "epsilon";
    parsingTable["factor_operation"]["+"] = "epsilon";
    parsingTable["factor_operation"]["-"] = "epsilon";
    parsingTable["factor_operation"]["*"] = "epsilon";
    parsingTable["factor_operation"]["/"] = "epsilon";
    parsingTable["factor_operation"]["%"] = "epsilon";


    // Primary
    parsingTable["primary"]["identifier"] = "identifier is_function_call";
    parsingTable["primary"]["numeric_literal"] = "literal";
    parsingTable["primary"]["'"] = "literal";
    parsingTable["primary"]["\""] = "literal";
    parsingTable["primary"]["True"] = "literal";
    parsingTable["primary"]["False"] = "literal";
    parsingTable["primary"]["None"] = "literal";
    parsingTable["primary"]["("] = "( expression )";


    // Is function call
    parsingTable["is_function_call"]["("] = "( is_parameter_list )";
    parsingTable["is_function_call"]["NEWLINE"] = "epsilon";
    parsingTable["is_function_call"]["$"] = "epsilon";
    parsingTable["is_function_call"]["DEDENT"] = "epsilon";
    parsingTable["is_function_call"][")"] = "epsilon";
    parsingTable["is_function_call"]["if"] = "epsilon";
    parsingTable["is_function_call"][","] = "epsilon";
    parsingTable["is_function_call"]["else"] = "epsilon";
    parsingTable["is_function_call"][":"] = "epsilon";
    parsingTable["is_function_call"]["or"] = "epsilon";
    parsingTable["is_function_call"]["and"] = "epsilon";
    parsingTable["is_function_call"]["not"] = "epsilon";
    parsingTable["is_function_call"]["<"] = "epsilon";
    parsingTable["is_function_call"][">"] = "epsilon";
    parsingTable["is_function_call"]["=="] = "epsilon";
    parsingTable["is_function_call"]["!="] = "epsilon";
    parsingTable["is_function_call"]["<="] = "epsilon";
    parsingTable["is_function_call"][">="] = "epsilon";
    parsingTable["is_function_call"]["|"] = "epsilon";
    parsingTable["is_function_call"]["^"] = "epsilon";
    parsingTable["is_function_call"]["&"] = "epsilon";
    parsingTable["is_function_call"]["<<"] = "epsilon";
    parsingTable["is_function_call"][">>"] = "epsilon";
    parsingTable["is_function_call"]["+"] = "epsilon";
    parsingTable["is_function_call"]["-"] = "epsilon";
    parsingTable["is_function_call"]["*"] = "epsilon";
    parsingTable["is_function_call"]["/"] = "epsilon";
    parsingTable["is_function_call"]["%"] = "epsilon";
    parsingTable["is_function_call"]["**"] = "epsilon";

    // Literal
    parsingTable["literal"]["numeric_literal"] = "numeric_literal";
    parsingTable["literal"]["'"] = "string";
    parsingTable["literal"]["\""] = "string";

    parsingTable["literal"]["True"] = "True";
    parsingTable["literal"]["False"] = "False";
    parsingTable["literal"]["None"] = "None";


    //STRING
    parsingTable["string"]["\""] = " \" string_literal \" ";
    parsingTable["string"]["'"] = " ' string_literal ' ";


    return parsingTable;
}


// In mainwindow.cpp constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  // Initialize our custom editor
{
    // // Create the nodes first (without children)
    // ParseTreeNode* program = new ParseTreeNode("program", nullptr);
    // ParseTreeNode* statement_list = new ParseTreeNode("statement_list", program);
    // ParseTreeNode* statement = new ParseTreeNode("statement", statement_list);
    // ParseTreeNode* new_statement_list = new ParseTreeNode("new_statement_list", statement_list);
    // ParseTreeNode* compound_statement = new ParseTreeNode("compound_statement", statement);
    // ParseTreeNode* if_stmt = new ParseTreeNode("if_stmt", compound_statement);

    // // Now assign children vectors
    // program->children = { statement_list };
    // statement_list->children = { statement, new_statement_list };
    // statement->children = { compound_statement };
    // new_statement_list->children = { };   // empty
    // compound_statement->children = { if_stmt };
    // if_stmt->children = { };  // empty

    // // Finally, put the root node in a vector (or use a pointer to root)
    // vector<ParseTreeNode*> tree = { program };


    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setupGraphicsView();
    // populateParseTree(tree);
    renderParseTree();
    resizeSceneToFitContent();
    ui->tabWidget->setCurrentIndex(0);

    // Create the line number area
    lineNumberArea = ui->LineNumberArea;
    lineNumberArea->setReadOnly(true);
    ui->LineNumberArea->setStyleSheet(
        "QPlainTextEdit {"
        "    background-color: rgb(0, 85, 127);"
        "    color: white;"            // Text color
        "    font: 10pt 'Century Gothic';" // Font style, weight, size
        "}"
        );
    ui->textarea->setStyleSheet(
        "QPlainTextEdit {"
        "    background-color: rgb(0, 85, 127);"
        "    color: white;"            // Text color
        "    font: 10pt 'Century Gothic';" // Font style, weight, size
        "}"
        );


    ui->errorTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: rgb(0, 85, 127);"
        "    color: red;"            // Text color
        "    font: bold 12pt 'Century Gothic';" // Font style, weight, size
        "}"
        );
    ui->SymbolTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: rgb(0, 85, 127);"
        "    color: white;"            // Text color
        "    font: bold 12pt 'Century Gothic';" // Font style, weight, size
        "}"
        "QTableWidget::item {"
        "   text-align: center;" // Center-align the text
        "}"
        );

    ui->TokenTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: rgb(0, 85, 127);"
        "    color: white;"            // Text color
        "    font: bold 12pt 'Century Gothic';"
        "    text-align: center"        // Font style, weight, size
        "}"

        );
    ui->errorTable->setColumnWidth(0, 65);
    ui->errorTable->horizontalHeader()->setStretchLastSection(true);

    ui->TokenTable->setColumnWidth(0, 65);
    ui->SymbolTable->setColumnWidth(0, 65);

    ui->errorTable->horizontalHeader()->setStretchLastSection(true);
    ui->TokenTable->horizontalHeader()->setStretchLastSection(true);
    ui->SymbolTable->horizontalHeader()->setStretchLastSection(true);

    // Enable resizing behavior for the table
    ui->errorTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);    // Fixed size for first column
    ui->errorTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Stretch remaining column

    ui->TokenTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);    // Fixed size for first column
    ui->TokenTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Stretch remaining column
    ui->TokenTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Stretch remaining column
    ui->TokenTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch); // Stretch remaining column

    ui->SymbolTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);    // Fixed size for first column
    ui->SymbolTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch); // Stretch remaining column
    ui->SymbolTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch); // Stretch remaining column

    connect(ui->textarea->verticalScrollBar(), &QScrollBar::valueChanged,
            ui->LineNumberArea->verticalScrollBar(), &QScrollBar::setValue);
    connect(ui->LineNumberArea->verticalScrollBar(), &QScrollBar::valueChanged,
            ui->textarea->verticalScrollBar(), &QScrollBar::setValue);

    // Connect text changes to line number updates
    connect(ui->textarea, &QPlainTextEdit::textChanged, this, &MainWindow::updateLineNumbers);

    // Initial line number update
    updateLineNumbers();

    connect(ui->cleartext, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);
    connect(ui->Compile, &QPushButton::clicked, this, &MainWindow::onAnalyzeButtonClicked);
    connect(ui->textarea, &QPlainTextEdit::textChanged, this, &MainWindow::validateCompileButton);

    validateCompileButton(); // Check the initial state
    connect(ui->loadfile, &QPushButton::clicked, this, &MainWindow::loadFile);
    connect(ui->themeChange, &QPushButton::clicked,this, &MainWindow::changeTheme);
}
void MainWindow::validateCompileButton() {
    QString text = ui->textarea->toPlainText();

    // Check if the text is empty or only whitespace
    bool isEmpty = text.trimmed().isEmpty();

    // Enable the compile button only if the text is not empty
    ui->Compile->setEnabled(!isEmpty);
    if(isEmpty){
        ui->Compile->setStyleSheet(
            "QPushButton {"
            "     background-color:grey;"
            "}"
            );
    }
    else{
        ui->Compile->setStyleSheet(
            "QPushButton {"
            "     background-color:#003f87;"
            "}"
            );
    }
}

void MainWindow::changeTheme() {


    if (ui->themeChange->text() == "🌑Dark") {
        ui->tabWidget->setStyleSheet(R"(QWidget {background-color: rgb(6, 4, 54);color: white;})");
        ui->centralwidget->setStyleSheet(R"(QWidget {background-color: rgb(6, 4, 54);})");
        //QPlainTextEdit
        ui->textarea->setStyleSheet(R"(QPlainTextEdit {background-color: rgb(0, 85, 127);color: white;})");
        ui->LineNumberArea->setStyleSheet(R"(QPlainTextEdit {background-color: rgb(0, 85, 127);color: white;})");

        //Button
        ui->Compile->setStyleSheet(R"(QPushButton {background-color: #003f87;color: white;border-radius: 5px;padding: 5px;})");
        ui->themeChange->setStyleSheet(R"(QPushButton {background-color: #003f87;color: white;border-radius: 5px;padding: 5px;})");
        ui->cleartext->setStyleSheet(R"(QPushButton {background-color: #003f87;color: white;border-radius: 5px;padding: 5px;})");
        ui->loadfile->setStyleSheet(R"(QPushButton {background-color: #003f87;color: white;border-radius: 5px;padding: 5px;})");

        //Tables
        ui->TokenTable->setStyleSheet(R"(QTableWidget {background-color: rgb(0, 85, 127);color: white;font: bold 12pt 'Century Gothic';})");
        ui->SymbolTable->setStyleSheet(R"(QTableWidget {background-color: rgb(0, 85, 127);color: white;font: bold 12pt 'Century Gothic';})");
        ui->errorTable->setStyleSheet(R"(QTableWidget {background-color: rgb(0, 85, 127); color: red; font: bold 12pt 'Century Gothic';})");

        ui->themeChange->setText("☀️Light");
    }

    else {
        ui->tabWidget->setStyleSheet(R"(QWidget {background-color: #90D5FF;color:rgb(0, 85, 127) ;})");
        ui->centralwidget->setStyleSheet(R"(QWidget {background-color: #90D5FF;})");
        //QPlainTextEdit
        ui->textarea->setStyleSheet(R"(QPlainTextEdit {background-color: rgb(255, 255, 255);color: rgb(0, 85, 127);})");
        ui->LineNumberArea->setStyleSheet(R"(QPlainTextEdit {background-color: rgb(255, 255, 255);color: rgb(0, 85, 127);})");

        //Button
        ui->Compile->setStyleSheet(R"(QPushButton {background-color: #4194cb;color: rgb(0, 85, 127);border-radius: 5px;padding: 5px;})");
        ui->themeChange->setStyleSheet(R"(QPushButton {background-color: #4194cb;color: rgb(0, 85, 127);border-radius: 5px;padding: 5px;})");
        ui->cleartext->setStyleSheet(R"(QPushButton {background-color: #4194cb;color: rgb(0, 85, 127);border-radius: 5px;padding: 5px;})");
        ui->loadfile->setStyleSheet(R"(QPushButton {background-color: #4194cb;color: rgb(0, 85, 127);border-radius: 5px;padding: 5px;})");

        //Tables
        ui->TokenTable->setStyleSheet(R"(QTableWidget {background-color: white; color: rgb(0, 85, 127);font: bold 12pt 'Century Gothic';})");
        ui->SymbolTable->setStyleSheet(R"(QTableWidget {background-color: white; color: rgb(0, 85, 127);font: bold 12pt 'Century Gothic';})");
        ui->errorTable->setStyleSheet(R"(QTableWidget {background-color: white; color:green; font: bold 12pt 'Century Gothic';})");

        ui->themeChange->setText("🌑Dark");
    }

}

void MainWindow::loadFile()
{
    // Get file path from dialog
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Open Python File"),
        QDir::homePath(),
        tr("Python Files (*.py);;All Files (*)")
        );

    // If user canceled
    if (filePath.isEmpty()) {
        return;
    }

    // Check if it's a Python file
    if (!filePath.endsWith(".py", Qt::CaseInsensitive)) {
        QMessageBox::warning(this, tr("Invalid File"),
                             tr("Please select a Python (.py) file."));
        return;
    }

    QFile file(filePath);

    // Check if file can be opened
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"),
                              tr("Could not open file for reading."));
        return;
    }

    // Read file content
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    // Check if file is empty
    if (content.isEmpty()) {
        QMessageBox::information(this, tr("Empty File"),
                                 tr("The selected file is empty."));
        return;
    }

    // Set text in the editor
    ui->textarea->setPlainText(content);
}

void MainWindow::updateLineNumbers() {
    // Get the text from the main text area
    QString text = ui->textarea->toPlainText();

    // Split the text by '\n' to count lines
    QStringList lines = text.split('\n');
    int lineCount = lines.size();

    // Generate line numbers
    QString lineNumbers;
    for (int i = 1; i <= lineCount; ++i) {
        lineNumbers += QString::number(i) + "\n";
    }

    // Update the line number area
    lineNumberArea->setPlainText(lineNumbers);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//
void MainWindow::onClearButtonClicked()
{
    ui->textarea->clear();
}

void MainWindow::onAnalyzeButtonClicked()
{
    QString inputText = ui->textarea->toPlainText();
    vector<char> vec;
    for (QChar ch : inputText) {
        vec.push_back(ch.toLatin1());
    }
    ui->TokenTable->setRowCount(0);
    ui->SymbolTable->setRowCount(0);
    ui->errorTable->setRowCount(0);
    auto s = lexical_analyzer(vec);
    map<string, map<string, string>> parsingTable = createParsingTable();
    parser(s.first, parsingTable, s.second);

}


void MainWindow::checkErrors(vector<pair<int, string>>& errors, int lineCount, string error) {
    for (auto i:errors) {
        if (i.first==lineCount) {
            if (i.second==error) {
                return;
            }
        }
    }
    errors.push_back({ lineCount,error});
}

int MainWindow::findSymbolTableIndex(vector<pair<int,vector<string>>>& symbolTable, int lineCount, string tempString)
{
    for (int i = 0; i < symbolTable.size(); i++) {
        // Check if the symbol matches (stored in the first element of the vector<string>)
        if (symbolTable[i].second[0] == tempString) {
            return i; // Return the index if the symbol already exists
        }
    }

    // Add a new entry to the symbolTable with the line count and symbol details
    symbolTable.push_back({lineCount, {tempString, "", ""}});
    return symbolTable.size() - 1; // Return the index of the newly added symbol
}

pair<vector<pair<int,pair<string, string>>>,vector<pair<int,vector<string>>>>MainWindow::lexical_analyzer(vector<char>& text)
{
    text.push_back('\n'); // Ensure final line is processed

    int state = START;
    int startPtr = 0;
    vector<pair<int,pair<string, string>>> Tokens;
    vector<pair<int,vector<string>>> symbolTable;
    vector<int> indentStack = { 0 }; // Track indentation levels (spaces)
    bool newLine = true;
    int spaceCount = 0;
    int lineCount = 1;
    bool errorFound = false;
    int errorLine=0;
    int error=0;
    vector<pair<int,string>>errors;


    for (int i = 0; i < text.size(); i++)
    {
        char ch = text[i];

        if (newLine)
        {
            spaceCount = 0;
            while (ch == ' ' || ch == '\t')
            {
                spaceCount += (ch == '\t') ? 4 : 1;
                i++;
                ch = text[i];
            }

            if (ch == '\n' || ch == '#')
            {
                if (ch == '#') {
                    newLine = false;
                    state = COMMENT;
                }
                else {
                    newLine = true;
                    lineCount++;
                }
                continue;
            }

            if (spaceCount > indentStack.back())
            {
                indentStack.push_back(spaceCount);
                Tokens.push_back({lineCount,{ "INDENT", to_string(spaceCount) }});
            }
            else if (spaceCount < indentStack.back())
            {
                while (spaceCount < indentStack.back())
                {
                    indentStack.pop_back();
                    Tokens.push_back({lineCount,{ "DEDENT", to_string(spaceCount) }});
                    Tokens.push_back({lineCount,{"NEWLINE","\\n"}});
                }
            }

            newLine = false;
        }

        switch (state) {
        case START:
        {
            startPtr = i;
            if (isdigit(ch))
                state = INTEGER;
            else if (isalpha(ch) || ch == '_')
                state = IDENTIFIER;
            else if (ch == '\'' || ch == '\"')
                state = STRINGS;
            else if (ch == '=' || ch == '!' || ch == '+' || ch == '-' ||
                     ch == '*' || ch == '/' || ch == '%' || ch == '<' || ch == '>' ||
                     ch == '&' || ch == '|' || ch == '^' )
                state = OPERATORS;
            else if (ch == '#')
                state = COMMENT;
            else if (ch == '(' || ch == ')' || ch == '[' || ch == ']' ||
                     ch == '{' || ch == '}')
                Tokens.push_back({lineCount,{ "BRACKET", string(1, ch) }});
            else if (ch == ':' || ch == ';' || ch == ',')
                Tokens.push_back({lineCount,{ "punctuation",string(1, ch) }}); // or "delimiter" if you prefer
            else if (ch == '.') {
                if (isdigit(text[i + 1]))
                    state = FLOAT_STATE;
                else Tokens.push_back({lineCount,{ "punctuation",string(1, ch) }}); // or "delimiter" if you prefer
            }
            else if (ch == '\n') {
                lineCount++;
                Tokens.push_back({lineCount,{"NEWLINE","\\n"}});
                newLine = true;
            }
            else if (ch == ' ' || ch == '\t') continue;
            else{
                state = ERROR;
                error = InvalidChar;
            }
            break;
        }
        case INTEGER:
        {
            if (isdigit(ch)) {///so that when a digit is present it stays in integer state and doesnt go to other states
            }
            else if (ch == '.') {
                if (!isdigit(text[i+1])) {
                    string tempString(text.begin() + startPtr, text.begin() + i+1);
                    tempString += "0";
                    Tokens.push_back({lineCount,{ "FLOAT", tempString }});
                    state = START;
                }
                else state = FLOAT_STATE;
            }
            else if (isalpha(ch) || ch == '_')
            {
                error = InvalidIdent;
                state = ERROR;  //Invalid Identifier ex: 123abc
            }
            else
            {
                string tempString(text.begin() + startPtr, text.begin() + i);
                Tokens.push_back({lineCount,{ "INTEGER", tempString }});
                state = START;
                i--;
            }
            break;
        }
        case FLOAT_STATE:
        {
            if (isdigit(ch)) {}
            else if (ch == '.')
            {
                error = InvalidFloat;
                state = ERROR;  //Invalid float ex: 5.4.2
            }
            else if (isalpha(ch) || ch == '_')
            {
                error = InvalidIdent;
                state = ERROR;  //Invalid Identifier ex: 123abc
            }
            else
            {
                string tempString(text.begin() + startPtr, text.begin() + i);
                Tokens.push_back({lineCount,{ "FLOAT", tempString }});
                state = START;
                i--;
            }
            break;
        }
        case IDENTIFIER:
        {
            if (isalnum(ch) || ch == '_') {}
            else
            {
                string tempString(text.begin() + startPtr, text.begin() + i);
                vector<string> keywords = {
                    "if", "else", "elif", "def", "return", "for", "while",
                    "continue", "break", "and", "or", "not", "print", "in",
                    "__init__","__main__","None","range","pass","class","__name__","self","True","False"
                };

                bool isKeyword = false;
                for (const string& k : keywords)
                {
                    if (tempString == k)
                    {
                        if ((tempString == "else" || tempString == "elif") && Tokens[Tokens.size() - 1].second.first == "NEWLINE")
                        {
                            Tokens.pop_back();
                        }
                        Tokens.push_back({lineCount,{ tempString, tempString }});
                        isKeyword = true;
                        break;
                    }
                }

                if (!isKeyword)
                {
                    int index = findSymbolTableIndex(symbolTable,lineCount, tempString);
                    Tokens.push_back({lineCount,{ "ID", to_string(index) }});
                }

                state = START;
                i--;
            }
            break;
        }
        case STRINGS:
        {
            char quoteType = text[startPtr];
            int iPtr = startPtr + 1;
            string content;
            bool terminated = false;
            while (iPtr < text.size()) {
                if (text[iPtr] == '\\' && iPtr + 1 < text.size()) {
                    // include escape sequence
                    if (isalpha(text[iPtr+1]))
                        content += text[iPtr];
                    content += text[iPtr + 1];
                    iPtr += 2;
                }
                else if (text[iPtr] == quoteType) {
                    terminated = true;
                    break;
                }
                else if (text[iPtr] == '\n') {
                    // unterminated string
                    break;
                }
                else {
                    content += text[iPtr];
                    iPtr++;
                }
            }

            if (terminated)
            {
                string quote(1, quoteType);
                Tokens.push_back({lineCount,{ "Quotation", quote }});
                Tokens.push_back({lineCount,{ "string_literal", content }});
                Tokens.push_back({lineCount,{ "Quotation", quote }});
                i = iPtr;          // advance main index to closing quote
                state = START;
            }
            else
            {
                error = UnterminatedString;
                state = ERROR;
                i--;
            }
            break;
        }
        case COMMENT:
        {
            while (i < text.size() && text[i] != '\n') {
                i++;
            }
            state = START;
            newLine = true;
            lineCount++;
            break;
        }
        case OPERATORS:
        {
            string op(1, text[startPtr]); // Use the original character that caused transition to OPERATORS
            if (i < text.size())
            {
                string twoChar = op + text[i];
                if (twoChar == "==" || twoChar == "!=" || twoChar == "<=" ||
                    twoChar == ">=" || twoChar == "<<" || twoChar == ">>" ||
                    twoChar == "**" )
                {
                    Tokens.push_back({lineCount,{ "OPERATOR", twoChar }});
                    state = START;
                    break;
                }
            }

            Tokens.push_back({lineCount,{ "OPERATOR", op }});
            state = START;
            i--; // since ch wasn't part of this operator, reprocess it
            break;
        }
        case ERROR:
        {
            switch (error) {
            case InvalidChar:
                checkErrors(errors, lineCount, string("invalid char: ") + text[i - 1]);
                i--;
                error = 0;
                state = START;
                errorFound = true;
                break;

            case InvalidIdent:
                if (!(isalnum(ch) || ch == '_')) {
                    string errorString(text.begin() + startPtr, text.begin() + i);
                    checkErrors(errors, lineCount, string("invalid identifier: ") + errorString);
                    i--;
                    state = START;
                    error = 0;
                }
                errorFound = true;
                break;

            case InvalidFloat:
                if (!(isdigit(ch) || ch == '.'))
                {
                    string errorString(text.begin() + startPtr, text.begin() + i);
                    checkErrors(errors, lineCount, string("invalid Float: ") + errorString);
                    state = START;
                    error = 0;
                    i--;
                }
                errorFound = true;
                break;

            case UnterminatedString:
                checkErrors(errors, lineCount, "Unterminated String");
                error = 0;
                i--;
                state = START;
                errorFound = true;
                break;
            }
        }

        }
    }

    // Emit final DEDENTs at EOF
    while (indentStack.size() > 1)
    {
        indentStack.pop_back();
        Tokens.push_back({lineCount,{ "DEDENT", "0" }});
    }

    if (Tokens[Tokens.size() - 1].second.first == "NEWLINE")
    {
        Tokens.pop_back();
    }

    if (errorFound==false) {
        ui->tabWidget->setCurrentIndex(1);

        for (const auto &token : Tokens) {
            int row = ui->TokenTable->rowCount();
            ui->TokenTable->insertRow(row); // Add a new row

            // Create items
            QTableWidgetItem *lineItem = new QTableWidgetItem(QString::number(token.first)); // Line number
            QTableWidgetItem *nameItem = new QTableWidgetItem(QString::fromStdString(token.second.first)); // Token name
            QTableWidgetItem *typeItem = new QTableWidgetItem(QString::fromStdString(token.second.second)); // Token type

            // Center-align text
            lineItem->setTextAlignment(Qt::AlignCenter);
            nameItem->setTextAlignment(Qt::AlignCenter);
            typeItem->setTextAlignment(Qt::AlignCenter);

            // Set items in the table
            ui->TokenTable->setItem(row, 0, lineItem);
            ui->TokenTable->setItem(row, 1, nameItem);
            ui->TokenTable->setItem(row, 2, typeItem);
        }

        // for (int i = 0; i < symbolTable.size(); i++) {
        //     const auto& entry = symbolTable[i];

        //     // Add a new row
        //     ui->SymbolTable->insertRow(i);

        //     // Create items
        //     QTableWidgetItem *lineItem = new QTableWidgetItem(QString::number(entry.first)); // Line number
        //     QTableWidgetItem *symbolItem = new QTableWidgetItem(QString::fromStdString(entry.second[0])); // Symbol name
        //     QTableWidgetItem *valueItem = new QTableWidgetItem(QString::fromStdString(entry.second[1])); // Value
        //     QTableWidgetItem *typeItem = new QTableWidgetItem(QString::fromStdString(entry.second[2])); // Type

        //     // Center-align text
        //     lineItem->setTextAlignment(Qt::AlignCenter);
        //     symbolItem->setTextAlignment(Qt::AlignCenter);
        //     valueItem->setTextAlignment(Qt::AlignCenter);
        //     typeItem->setTextAlignment(Qt::AlignCenter);

        //     // Set items in the table
        //     ui->SymbolTable->setItem(i, 0, lineItem);
        //     ui->SymbolTable->setItem(i, 1, symbolItem);
        //     ui->SymbolTable->setItem(i, 2, valueItem);
        //     ui->SymbolTable->setItem(i, 3, typeItem);
        // }

    }

    else {
        for (auto i:errors) {
            int row = ui->errorTable->rowCount();  // Get the current row count
            ui->errorTable->insertRow(row);       // Insert a new row

            // Populate the row with error data
            ui->errorTable->setItem(row, 0, new QTableWidgetItem(QString::number(i.first))); // Line number
            ui->errorTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(i.second))); // Error message
        }
    }
    return {Tokens,symbolTable};
}


int precedence(const string& op) {
    if (op == "or") return 1;
    if (op == "and") return 2;
    if (op == "not") return 3;
    if (op == "<" || op == ">" || op == "==" || op == "!=" || op == "<=" || op == ">=") return 4;
    if (op == "|") return 5;
    if (op == "^") return 6;
    if (op == "&") return 7;
    if (op == "<<" || op == ">>") return 8;
    if (op == "+" || op == "-") return 9;
    if (op == "*" || op == "/" || op == "%") return 10;
    if (op == "**") return 11;
    return -1;
}

bool isRightAssociative(const string& op) {
    return op == "**" || op == "not";
}

// Check if token is number (integer/float or boolean-like)
bool isNumber(const string& token) {
    if (token == "true" || token == "false") return true;
    char* end = nullptr;
    strtod(token.c_str(), &end);
    return *end == '\0';
}


// Apply binary or unary operator
double applyOp(double a, double b, const string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    if (op == "%") return fmod(a, b);
    if (op == "**") return pow(a, b);

    if (op == "==") return a == b;
    if (op == "!=") return a != b;
    if (op == "<") return a < b;
    if (op == "<=") return a <= b;
    if (op == ">") return a > b;
    if (op == ">=") return a >= b;

    if (op == "&") return (int)a & (int)b;
    if (op == "|") return (int)a | (int)b;
    if (op == "^") return (int)a ^ (int)b;
    if (op == "<<") return (int)a << (int)b;
    if (op == ">>") return (int)a >> (int)b;

    if (op == "and") return a && b;
    if (op == "or") return a || b;

    throw runtime_error("Unknown binary operator: " + op);
}

double applyUnary(double a, const string& op) {
    if (op == "not") return !a;
    throw runtime_error("Unknown unary operator: " + op);
}

bool isOperator(const string& token) {
    return precedence(token) != -1 || token == "(" || token == ")";
}

// Evaluate expression using Shunting Yard + RPN
double evaluateExpression(const vector<string>& tokens) {
    vector<string> output;
    stack<string> ops;

    unordered_set<string> unaryOps = { "not", "-" };

    for (size_t i = 0; i < tokens.size(); ++i) {
        const string& token = tokens[i];

        if (isNumber(token)) {
            output.push_back(token);
        }
        else if (token == "(") {
            ops.push(token);
        }
        else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop(); // remove "("
        }
        else {
            // Check for unary operators
            bool isUnary = false;
            if (token == "not") {
                isUnary = true;
            }
            else if (token == "-") {
                if (i == 0 || tokens[i - 1] == "(" || isOperator(tokens[i - 1])) {
                    isUnary = true;
                }
            }

            if (isUnary) {
                ops.push("u" + token); // Mark as unary
            }
            else {
                // Binary operator logic
                while (!ops.empty() && ops.top() != "(" &&
                       (precedence(ops.top()) > precedence(token) ||
                        (precedence(ops.top()) == precedence(token) && !isRightAssociative(token)))) {
                    output.push_back(ops.top());
                    ops.pop();
                }
                ops.push(token);
            }
        }
    }

    while (!ops.empty()) {
        output.push_back(ops.top());
        ops.pop();
    }

    // Evaluate RPN
    stack<double> values;
    for (const string& token : output) {
        if (isNumber(token)) {
            if (token == "true") values.push(1.0);
            else if (token == "false") values.push(0.0);
            else values.push(stod(token));
        }
        else if (token.substr(0, 1) == "u") { // Unary operator
            string op = token.substr(1);
            double a = values.top(); values.pop();
            values.push(applyUnary(a, op));
        }
        else {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(applyOp(a, b, token));
        }
    }

    return values.top();
}

void updateSymbolTable(string ID, vector<string> assignment_expr, vector<pair<int,vector<string>>>& symbolTable) {
    for (const string& token : assignment_expr) {
        cout << "current token" << token << endl;
        if (token.empty()) {
        }
    }
    double value = evaluateExpression(assignment_expr);
    symbolTable[stoi(ID)].second[1] = to_string(value);
    cout << "updated value" << symbolTable[stoi(ID)].second[1] << endl;

}

pair<string, string> getNextToken(vector<pair<int,pair<string, string>>> tokenStream) {

    if (currentTokenIndex >= tokenStream.size()) {
        return { "$", "$" };
    }
    return tokenStream[currentTokenIndex++].second;
}

bool findInParsingTable(stack<string>& parseStack,
                        const string& token,
                        map<string, map<string, string>>& parsingTable,
                        ParseTree& parsetree) {
    string top = parseStack.top();
    string production = parsingTable[top][token];

    if (production == "") {
        return false;  // No production found
    }
    else if (production == "epsilon") {
        parseStack.pop();
        return true;
    }
    else {
        // Split production into symbols
        vector<string> symbols;
        istringstream iss(production);
        string sym;
        while (iss >> sym) {
            symbols.push_back(sym);
        }

        // Generate unique ID for the new node
        string newNodeId = parsetree.generateNodeId(top, parseStack.size());
        ParseTreeNode* newNode = new ParseTreeNode(newNodeId, top);

        // Handle root node case
        if (parseStack.top() == parsetree.root->symbol) {
            parseStack.pop();
            vector<ParseTreeNode*> children;

            // Process symbols in reverse order
            for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
                parseStack.push(*it);
                string childId = parsetree.generateNodeId(*it, parseStack.size());
                ParseTreeNode* child = new ParseTreeNode(childId, *it, newNode);
                children.push_back(child);
            }

            // Add children in correct order and update root
            parsetree.root->children.assign(children.rbegin(), children.rend());
            return true;
        }

        // Normal case - non-root node
        parseStack.pop();
        vector<ParseTreeNode*> children;

        // Process symbols in reverse order
        for (auto it = symbols.rbegin(); it != symbols.rend(); ++it) {
            parseStack.push(*it);
            string childId = parsetree.generateNodeId(*it, parseStack.size());
            ParseTreeNode* child = new ParseTreeNode(childId, *it, newNode);
            children.push_back(child);
        }

        // Add children in correct order
        newNode->children.assign(children.rbegin(), children.rend());

        // Find and link to parent node
        if (!parseStack.empty()) {
            // Search through the tree to find the parent node
            // This assumes you have a way to track the current parent position
            // Alternatively, you could maintain a separate stack of node pointers
            ParseTreeNode* parent = parsetree.findParentById(parsetree.root, newNodeId);
            if (parent) {
                parent->children.push_back(newNode);
                newNode->parent = parent;
            }
        }

        return true;
    }
}
vector<pair<int,vector<string>>> MainWindow::parser(vector<pair<int,pair<string, string>>> tokens, map<string, map<string, string>> parsingTable, vector<pair<int,vector<string>>> symbolTable)
{
    pair<string, string> token = getNextToken(tokens);
    stack<string> Seifos;
    Seifos.push("$");
    Seifos.push("program");
    string rootid = parseTree.generateNodeId(Seifos.top(),1);
    ParseTreeNode* root = new ParseTreeNode(rootid,Seifos.top());
    parseTree.root=root;
    stack<string>INDENT;
    INDENT.push("0");
    int lineCount = 1;
    string ID;
    bool assignment = false;
    vector<string> assignment_expr;
    bool skipAssignment = false;

    while (Seifos.top() != "$")
    {
        if (token.first == "ID")
        {
            token.first = "identifier";
            if (assignment == false)
                ID = token.second; //index in symbol table
        }
        else if (token.first == "INTEGER" || token.first == "FLOAT")
        {
            token.first = "numeric_literal";
        }

        if (token.first == "identifier" || token.first == "numeric_literal" || token.first == "NEWLINE" || token.first == "INDENT" || token.first == "DEDENT" || token.first == "string_literal")
        {

            if (Seifos.top() == token.first) //MATCH
            {

                if (assignment == true) {
                    if (token.first == "numeric_literal") {
                        assignment_expr.push_back(token.second);
                    }
                    else if (token.first == "identifier") {
                        assignment_expr.push_back(symbolTable[stoi(token.second)].second[1]);
                    }
                }

                if (token.first == "NEWLINE") {
                    if (assignment == true) {
                        //updateSymbolTable(ID, assignment_expr, symbolTable);
                        assignment = false;
                    }
                    lineCount++;
                }

                if (token.first == "INDENT") {
                    INDENT.push(token.second);
                }
                else if (token.first == "DEDENT") {
                    while (stoi(token.second) < stoi(INDENT.top())) {
                        INDENT.pop();
                    }
                    if (INDENT.top() != token.second) {
                        cout << "Unindent amount does not match previous indent" << endl;
                        cout << "top of indent stack: " << INDENT.top() << endl;
                        break;
                    }
                }



                Seifos.pop();
                token = getNextToken(tokens);
                continue;

            }

            if (!findInParsingTable(Seifos, token.first, parsingTable,parseTree))
            {
                break;
            }
        }
        else
        {
            if (Seifos.top() == token.second) //MATCH
            {

                if (assignment == true) {
                    assignment_expr.push_back(token.second);
                }

                if (token.second == "=") {
                    assignment = true;

                }

                Seifos.pop();
                token = getNextToken(tokens);
                continue;
            }

            if (!findInParsingTable(Seifos, token.second, parsingTable,parseTree))
            {
                break;
            }
        }

    }



    // Print final symbol table
    cout << "\nSymbol Table:\n";
    cout << "ID\tName\tValue\n";
    cout << "-----------------\n";
    for (size_t i = 0; i < symbolTable.size(); i++) {
        cout << i << "\t" << symbolTable[i].second[0] << "\t" << symbolTable[i].second[1] << "\n";
    }
    if (token.first == "$" && Seifos.top() == "$")
    {
        currentTokenIndex=0;
        ui->errorTable->setRowCount(0);
        int row = ui->errorTable->rowCount();  // Get the current row count
        ui->errorTable->insertRow(row);       // Insert a new row

        // Populate the row with error data
        ui->errorTable->setItem(row, 1, new QTableWidgetItem("Accepted")); // Line number
        qDebug() << "Row inserted. Current row count:" << ui->errorTable->rowCount();
        vector<ParseTreeNode*> tree = {parseTree.root};
        populateParseTree(tree);
        renderParseTree();
    }
    else
    {
        currentTokenIndex=0;
        ui->errorTable->setRowCount(0);
        int row = ui->errorTable->rowCount();  // Get the current row count
        ui->errorTable->insertRow(row);       // Insert a new row
        string errormsg = "Error in line: " + to_string(lineCount) + ", unexpected token \"" + token.second + "\"";
        // Populate the row with error data
        ui->errorTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(errormsg))); // Line number
        qDebug() << "awl el token "<< token.first << "awl el stack" << Seifos.top();
        qDebug() << "Error in line: " << lineCount << ", unexpected token \"" << token.second << "\"";
    }

    for (int i = 0; i < symbolTable.size(); i++) {
        const auto& entry = symbolTable[i];

        // Add a new row
        ui->SymbolTable->insertRow(i);

        // Create items
        QTableWidgetItem *lineItem = new QTableWidgetItem(QString::number(entry.first)); // Line number
        QTableWidgetItem *symbolItem = new QTableWidgetItem(QString::fromStdString(entry.second[0])); // Symbol name
        QTableWidgetItem *valueItem = new QTableWidgetItem(QString::fromStdString(entry.second[1])); // Value
        QTableWidgetItem *typeItem = new QTableWidgetItem(QString::fromStdString(entry.second[2])); // Type

        // Center-align text
        lineItem->setTextAlignment(Qt::AlignCenter);
        symbolItem->setTextAlignment(Qt::AlignCenter);
        valueItem->setTextAlignment(Qt::AlignCenter);
        typeItem->setTextAlignment(Qt::AlignCenter);

        // Set items in the table
        ui->SymbolTable->setItem(i, 0, lineItem);
        ui->SymbolTable->setItem(i, 1, symbolItem);
        ui->SymbolTable->setItem(i, 2, valueItem);
        ui->SymbolTable->setItem(i, 3, typeItem);
    }

    return symbolTable;
}

bool panning = false;
QPoint lastMousePos;

void MainWindow::populateParseTree(std::vector<ParseTreeNode*>& nodes) {
    if (nodes.empty()) return;  // Ensure there are nodes to process.

    // Assume the first node in the vector is the root.
    parseTree.root = nodes[0];

    // Establish child-parent relationships (assuming they are pre-linked in the vector).
    for (ParseTreeNode* node : nodes) {
        if (!node->children.empty()) {
            for (ParseTreeNode* child : node->children) {
                // Optional: Ensure the child nodes are part of the vector.
                if (std::find(nodes.begin(), nodes.end(), child) == nodes.end()) {
                    qWarning() << "Child node not found in the vector!";
                }
            }
        }
    }

    qDebug() << "Parse tree populated with" << nodes.size() << "nodes.";
}
void MainWindow::renderParseTree() {
    QGraphicsScene* scene = new QGraphicsScene(this);  // Create a scene
   // drawNode(parseTree.root, scene, 0, 0, 100);  // Start drawing from root

    ui->graphicsView->setScene(scene);  // Attach the scene to the graphics view
    // Configure spacing (adjust if needed)
    double horizontalSpacing = 200.0;
    double verticalSpacing = 100.0;

    // Start arranging tree from root at position (0, 0)
    arrangeTree(parseTree.root, QPointF(0, 0), verticalSpacing, scene);

    // Fit scene rect to all items to avoid clipping
    scene->setSceneRect(scene->itemsBoundingRect());
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::wheelEvent(QWheelEvent *event) {
    QGraphicsView *view = ui->graphicsView;
    static const double zoomFactor = 1.02;
    static const double minScale = 0.1;
    static const double maxScale = 5.0;

    // Get the current transformation
    QTransform currentTransform = view->transform();

    // Zoom in or out while respecting the limits
    if (event->angleDelta().y() > 0) {
        // Zoom in
        if (currentTransform.m11() < maxScale) {
            view->scale(zoomFactor, zoomFactor);
        }
    } else {
        // Zoom out
        if (currentTransform.m11() > minScale) {
            view->scale(1.0 / zoomFactor, 1.0 / zoomFactor);
        }
    }

    // Prevent the event from propagating further
    event->accept();

}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        panning = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

// Pan Move
void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (panning) {
        QGraphicsView *view = ui->graphicsView;
        QPoint delta = event->pos() - lastMousePos;

        // Translate the view instead of relying on scrollbars
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        view->translate(delta.x(), delta.y());
        lastMousePos = event->pos();
    }
}

// Pan End
void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        panning = false;
        setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::arrangeTree(ParseTreeNode* node, QPointF position, double verticalSpacing, QGraphicsScene* scene) {
    if (!node) return;

    // Determine the color of the node (green for leaf, yellow for non-leaf)
    QColor nodeColor = node->children.empty() ? Qt::green : Qt::yellow;

    // Draw ellipse for the node with the determined color
    QGraphicsEllipseItem* ellipse = scene->addEllipse(position.x() - 30, position.y() - 15, 60, 30, QPen(Qt::black), QBrush(nodeColor));

    // Draw centered text inside ellipse
    QGraphicsTextItem* text = scene->addText(QString::fromStdString(node->symbol));
    text->setDefaultTextColor(Qt::black);
    text->setPos(position.x() - text->boundingRect().width() / 2, position.y() - text->boundingRect().height() / 2);

    // If the node has no children, return early
    if (node->children.empty()) {
        return;
    }

    // Calculate the total width needed for children
    double totalWidth = 0;
    std::vector<double> childWidths;

    for (auto& child : node->children) {
        double childWidth = calculateSubtreeWidth(child);
        childWidths.push_back(childWidth);
        totalWidth += childWidth;
    }

    // Adjust the starting x-coordinate for the first child
    double currentX = position.x() - totalWidth / 2;

    for (size_t i = 0; i < node->children.size(); ++i) {
        ParseTreeNode* child = node->children[i];
        double childWidth = childWidths[i];

        // Center the child within its calculated space
        QPointF childPosition(currentX + childWidth / 2, position.y() + verticalSpacing);

        // Draw line between parent and child
        scene->addLine(position.x(), position.y() + 15, childPosition.x(), childPosition.y() - 15, QPen(Qt::black));

        // Recursive call to draw the child's subtree
        arrangeTree(child, childPosition, verticalSpacing, scene);

        // Update the x-coordinate for the next child
        currentX += childWidth;
    }
}

double MainWindow::calculateSubtreeWidth(ParseTreeNode* node) {
    if (!node || node->children.empty()) {
        return 100; // Minimum width for a single node
    }

    double totalWidth = 0;
    for (auto& child : node->children) {
        totalWidth += calculateSubtreeWidth(child);
    }

    return totalWidth;
}

void MainWindow::setupGraphicsView() {
    // Assuming 'view' is your QGraphicsView and 'this' is your MainWindow
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Set QGraphicsView to expand with the parent widget
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Use a layout to manage resizing
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(ui->graphicsView);

    // Set the layout on the central widget
    QWidget* thirdPage = ui->tabWidget->widget(2);

    // Create a layout for the third page if it doesn’t have one already
    QLayout* existingLayout = thirdPage->layout();
    if (!existingLayout) {
        QVBoxLayout* layout = new QVBoxLayout(thirdPage);
        thirdPage->setLayout(layout);
        existingLayout = layout;
    }

    // Add the graphicsView to the third page’s layout
    existingLayout->addWidget(ui->graphicsView);

}

void MainWindow::resizeSceneToFitContent() {
    QGraphicsScene *scene = ui->graphicsView->scene();
    if (scene) {
        QRectF contentBounds = scene->itemsBoundingRect();
        scene->setSceneRect(contentBounds);
    }
}
