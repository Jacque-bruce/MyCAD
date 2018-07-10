#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QLabel>
#include <QComboBox>   //下拉框
#include <QSpinBox>    //自选盒
#include<QToolButton>
#include<QInputDialog>

#include "drawwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createToolBar();


public slots:
    void ShowStyle();
    void ShowColor();
    int  EdgeNumber();


private:
    drawWidget *dw;
    QLabel *styleLable;
    QComboBox *styleComboBox;
    QLabel *widthLable;
    QSpinBox *widthSpinBox;
    QToolButton *colorBtn;
    QToolButton *clearBtn;
    QToolButton *lineBtn;
    QToolButton *rectBtn;
    QToolButton *circleBtn;
    QToolButton *polygonBtn;
    QToolButton *clearRectBtn;
    QInputDialog *inputDialog;
    QLabel *edgeLabel;
};

#endif // MAINWINDOW_H
