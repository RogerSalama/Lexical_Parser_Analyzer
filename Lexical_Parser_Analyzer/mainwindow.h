#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <vector>
#include <string>
#include <utility>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include "ParseTree.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onClearButtonClicked();
    void onAnalyzeButtonClicked();
    void updateLineNumbers();
    void loadFile();

private:
    // Lexer functions
    void setupGraphicsView();
    void resizeSceneToFitContent();
    pair<vector<pair<int,pair<string, string>>>,vector<pair<int,vector<string>>>> lexical_analyzer(vector<char>& text);
    int findSymbolTableIndex(vector<pair<int,vector<string>>>& symbolTable,int lineCount, string tempString);
    void setValue(vector<char>& text, int i, vector<pair<int,vector<string>>>& symbolTable, string tempString);
    void checkErrors(vector<pair<int, string>>& errors, int lineCount, string error);
    vector<pair<int,vector<string>>> parser(vector<pair<int,pair<string, string>>> Tokens, map<string, map<string, string>> parsingTable, vector<pair<int,vector<string>>> symbolTable);
    void changeTheme();
    void validateCompileButton();
    void populateParseTree(std::vector<ParseTreeNode*>& nodes);
    void renderParseTree();
    void drawNode(ParseTreeNode* node, QGraphicsScene* scene, int x, int y, int xOffset);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void arrangeTree(ParseTreeNode* node, QPointF position, double verticalSpacing, QGraphicsScene* scene);
    double calculateSubtreeWidth(ParseTreeNode* node);
    Ui::MainWindow *ui;
    QPlainTextEdit *lineNumberArea;
    ParseTree parseTree;
};

#endif // MAINWINDOW_H
