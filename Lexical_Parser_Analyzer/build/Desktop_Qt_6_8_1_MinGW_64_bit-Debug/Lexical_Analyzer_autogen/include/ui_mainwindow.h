/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *themeChange;
    QTabWidget *tabWidget;
    QWidget *Code;
    QHBoxLayout *horizontalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QTableWidget *errorTable;
    QPlainTextEdit *LineNumberArea;
    QPlainTextEdit *textarea;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *cleartext;
    QPushButton *loadfile;
    QPushButton *Compile;
    QWidget *Output;
    QHBoxLayout *horizontalLayout_5;
    QTableWidget *TokenTable;
    QTableWidget *SymbolTable;
    QWidget *tab;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(806, 617);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:  rgb(6, 4, 54);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        themeChange = new QPushButton(centralwidget);
        themeChange->setObjectName("themeChange");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(themeChange->sizePolicy().hasHeightForWidth());
        themeChange->setSizePolicy(sizePolicy);
        themeChange->setMaximumSize(QSize(100, 16777215));
        QFont font;
        font.setFamilies({QString::fromUtf8("Century Gothic")});
        font.setPointSize(11);
        font.setBold(true);
        themeChange->setFont(font);
        themeChange->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(themeChange, 0, 1, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setEnabled(true);
        tabWidget->setStyleSheet(QString::fromUtf8("background-color:rgb(6, 4, 54);"));
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        Code = new QWidget();
        Code->setObjectName("Code");
        horizontalLayout_4 = new QHBoxLayout(Code);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        scrollArea = new QScrollArea(Code);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 776, 503));
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
        scrollAreaWidgetContents->setSizeIncrement(QSize(50, 50));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName("gridLayout_2");
        errorTable = new QTableWidget(scrollAreaWidgetContents);
        if (errorTable->columnCount() < 2)
            errorTable->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        errorTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        errorTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        errorTable->setObjectName("errorTable");
        errorTable->setMaximumSize(QSize(16777215, 150));
        errorTable->setAutoFillBackground(false);
        errorTable->setStyleSheet(QString::fromUtf8("background-color: rgb(19, 19, 19);"));
        errorTable->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        errorTable->setDragEnabled(false);
        errorTable->setAlternatingRowColors(true);
        errorTable->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerItem);
        errorTable->setRowCount(0);
        errorTable->setColumnCount(2);
        errorTable->horizontalHeader()->setVisible(true);
        errorTable->horizontalHeader()->setCascadingSectionResizes(false);
        errorTable->horizontalHeader()->setMinimumSectionSize(20);
        errorTable->horizontalHeader()->setStretchLastSection(false);
        errorTable->verticalHeader()->setVisible(true);
        errorTable->verticalHeader()->setStretchLastSection(false);

        gridLayout_2->addWidget(errorTable, 2, 1, 1, 1);

        LineNumberArea = new QPlainTextEdit(scrollAreaWidgetContents);
        LineNumberArea->setObjectName("LineNumberArea");
        LineNumberArea->setMaximumSize(QSize(50, 16777215));
        LineNumberArea->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        LineNumberArea->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(0, 85, 127);"));
        LineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        LineNumberArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        LineNumberArea->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);

        gridLayout_2->addWidget(LineNumberArea, 1, 0, 1, 1);

        textarea = new QPlainTextEdit(scrollAreaWidgetContents);
        textarea->setObjectName("textarea");
        textarea->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(0, 85, 127);"));
        textarea->setSizeAdjustPolicy(QAbstractScrollArea::SizeAdjustPolicy::AdjustToContents);
        textarea->setTabStopDistance(80.000000000000000);
        textarea->setBackgroundVisible(false);

        gridLayout_2->addWidget(textarea, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        cleartext = new QPushButton(scrollAreaWidgetContents);
        cleartext->setObjectName("cleartext");
        sizePolicy.setHeightForWidth(cleartext->sizePolicy().hasHeightForWidth());
        cleartext->setSizePolicy(sizePolicy);
        cleartext->setMinimumSize(QSize(150, 25));
        cleartext->setMaximumSize(QSize(50, 16777215));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Century Gothic")});
        font1.setPointSize(12);
        font1.setBold(true);
        cleartext->setFont(font1);
        cleartext->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        cleartext->setStyleSheet(QString::fromUtf8("background-color:#003f87;"));

        horizontalLayout_3->addWidget(cleartext);

        loadfile = new QPushButton(scrollAreaWidgetContents);
        loadfile->setObjectName("loadfile");
        sizePolicy.setHeightForWidth(loadfile->sizePolicy().hasHeightForWidth());
        loadfile->setSizePolicy(sizePolicy);
        loadfile->setMinimumSize(QSize(150, 25));
        loadfile->setMaximumSize(QSize(50, 16777215));
        loadfile->setFont(font1);
        loadfile->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        loadfile->setStyleSheet(QString::fromUtf8("background-color:#003f87;"));

        horizontalLayout_3->addWidget(loadfile);

        Compile = new QPushButton(scrollAreaWidgetContents);
        Compile->setObjectName("Compile");
        sizePolicy.setHeightForWidth(Compile->sizePolicy().hasHeightForWidth());
        Compile->setSizePolicy(sizePolicy);
        Compile->setMinimumSize(QSize(150, 25));
        Compile->setMaximumSize(QSize(50, 16777215));
        Compile->setFont(font1);
        Compile->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        Compile->setStyleSheet(QString::fromUtf8("background-color: #003f87;"));

        horizontalLayout_3->addWidget(Compile);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 1, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_4->addWidget(scrollArea);

        tabWidget->addTab(Code, QString());
        Output = new QWidget();
        Output->setObjectName("Output");
        Output->setEnabled(true);
        horizontalLayout_5 = new QHBoxLayout(Output);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        TokenTable = new QTableWidget(Output);
        if (TokenTable->columnCount() < 3)
            TokenTable->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        TokenTable->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        TokenTable->setHorizontalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        TokenTable->setHorizontalHeaderItem(2, __qtablewidgetitem4);
        TokenTable->setObjectName("TokenTable");
        TokenTable->setEnabled(true);
        TokenTable->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        TokenTable->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        TokenTable->setColumnCount(3);

        horizontalLayout_5->addWidget(TokenTable);

        SymbolTable = new QTableWidget(Output);
        if (SymbolTable->columnCount() < 4)
            SymbolTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        SymbolTable->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        SymbolTable->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        SymbolTable->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        SymbolTable->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        SymbolTable->setObjectName("SymbolTable");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(SymbolTable->sizePolicy().hasHeightForWidth());
        SymbolTable->setSizePolicy(sizePolicy2);
        SymbolTable->setMaximumSize(QSize(16777215, 10000000));
        SymbolTable->setFrameShadow(QFrame::Shadow::Sunken);
        SymbolTable->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        SymbolTable->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        SymbolTable->setGridStyle(Qt::PenStyle::SolidLine);
        SymbolTable->setColumnCount(4);

        horizontalLayout_5->addWidget(SymbolTable);

        tabWidget->addTab(Output, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        sizePolicy2.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy2);
        tab->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        graphicsView = new QGraphicsView(tab);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(0, 0, 781, 511));
        sizePolicy2.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy2);
        tabWidget->addTab(tab, QString());

        gridLayout->addWidget(tabWidget, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 806, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        themeChange->setText(QCoreApplication::translate("MainWindow", "\342\230\200\357\270\217Light", nullptr));
        QTableWidgetItem *___qtablewidgetitem = errorTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Error_Line", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = errorTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Error_Descrption", nullptr));
        textarea->setPlaceholderText(QCoreApplication::translate("MainWindow", "What's on your mind dude??", nullptr));
        cleartext->setText(QCoreApplication::translate("MainWindow", "\360\237\247\275Clear Textarea", nullptr));
        loadfile->setText(QCoreApplication::translate("MainWindow", "\342\254\206\357\270\217Load File", nullptr));
        Compile->setText(QCoreApplication::translate("MainWindow", "\360\237\217\203\342\200\215\342\231\202\357\270\217\342\200\215\342\236\241\357\270\217Compile", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Code), QCoreApplication::translate("MainWindow", "\360\237\247\221\342\200\215\360\237\222\273Code", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = TokenTable->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "LINE", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = TokenTable->horizontalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "TOKEN", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = TokenTable->horizontalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "NAME", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = SymbolTable->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "LINE", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = SymbolTable->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "NAME", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = SymbolTable->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "VALUE", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = SymbolTable->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "TYPE", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Output), QCoreApplication::translate("MainWindow", "\360\237\223\244Output", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
