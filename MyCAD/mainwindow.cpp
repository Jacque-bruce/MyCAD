#include "mainwindow.h"
#include"vector2d.h"

#include<QPushButton>
#include<QString>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QToolBar>
#include<QStatusBar>
#include<QDebug>
#include<QPoint>
#include<QWidget>
#include<QScrollArea>
#include<QComboBox>
#include<QDialog>
#include<QColorDialog>
#include<QColor>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dw=new drawWidget;

    setCentralWidget(dw);
    createToolBar();
    setMinimumSize(600,400);
    ShowStyle();
    dw->setWidth(widthSpinBox->value());
    dw->setColor(Qt::black);
    edgeLabel=new QLabel(tr("0"));

}

void MainWindow::createToolBar()
{
    QToolBar *toolBar=addToolBar("Tool");
    styleLable=new QLabel(tr("  线型： "));
    styleComboBox=new QComboBox;
    styleComboBox->addItem(tr("solidLine"),
                           static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem (tr("DotLine"),
                           static_cast<int>(Qt::DotLine));

    connect (styleComboBox, SIGNAL(activated(int)), this, SLOT(ShowStyle()));

        //创建线宽选择控件
        widthLable = new QLabel(tr("  线宽:  "));
        widthSpinBox = new QSpinBox;
        connect (widthSpinBox, SIGNAL(valueChanged(int)), dw, SLOT(setWidth(int)));
        //创建颜色选择控件
        colorBtn = new QToolButton;
        //颜色选择按钮控件上的图像
        QPixmap pixmap(20, 20);
        pixmap.fill (Qt::black);
        //设置按钮图像
        colorBtn->setIcon (QIcon(pixmap));
        connect (colorBtn, SIGNAL(clicked(bool)), this, SLOT(ShowColor()));

        clearBtn = new QToolButton();                    //创建清除按钮
        clearBtn->setText (tr("  清除  "));
        connect (clearBtn, SIGNAL(clicked(bool)), dw, SLOT(clear()));

        lineBtn=new QToolButton();
        lineBtn->setText(" 直线 ");
        connect (lineBtn, &QToolButton::clicked,
                 [=]()
                {
                    dw->isLine=true;
                    dw->isCircle=false;
                    dw->isRect=false;
                    dw->isPolygon=false;
                    dw->isClearRect=false;
                }
                 );

        rectBtn=new QToolButton();
        rectBtn->setText(" 矩形 ");
        connect (rectBtn, &QToolButton::clicked,
                 [=]()
                {
                    dw->isLine=false;
                    dw->isCircle=false;
                    dw->isRect=true;
                    dw->isPolygon=false;
                    dw->isClearRect=false;
                }
                 );


        circleBtn=new QToolButton();
        circleBtn->setText(" 圆 ");
        connect (circleBtn, &QToolButton::clicked,
                 [=]()
                {
                    dw->isLine=false;
                    dw->isCircle=true;
                    dw->isRect=false;
                    dw->isPolygon=false;
                    dw->isClearRect=false;
                }
                 );

        polygonBtn=new QToolButton();
        polygonBtn->setText(" 多边形 ");
        connect (polygonBtn, &QToolButton::clicked,
                 [=]()
                {
                    dw->isLine=false;
                    dw->isCircle=false;
                    dw->isRect=false;
                    dw->isPolygon=true;
                    dw->isClearRect=false;
                    dw->polygonEdge= EdgeNumber();

                }
                 );

        clearRectBtn=new QToolButton();
        clearRectBtn->setText(" 擦除 ");
        connect (clearRectBtn, &QToolButton::clicked,
                 [=]()
                {
                    dw->isLine=false;
                    dw->isCircle=false;
                    dw->isRect=false;
                    dw->isPolygon=false;
                    dw->isClearRect=true;

                }
                 );

        toolBar->addWidget(lineBtn);
        toolBar->addWidget(rectBtn);
        toolBar->addWidget(circleBtn);
        toolBar->addWidget(polygonBtn);
        toolBar->addWidget(clearRectBtn);
        toolBar->addWidget (styleLable);
        toolBar->addWidget (styleComboBox);
        toolBar->addWidget (widthLable);
        toolBar->addWidget (widthSpinBox);
        toolBar->addWidget (colorBtn);
        toolBar->addWidget (clearBtn);
}

void MainWindow::ShowStyle ()
{
    dw->setStyle (styleComboBox->itemData (styleComboBox->currentIndex (),
                                                   Qt::UserRole).toInt ());
}

void MainWindow::ShowColor ()
{
    QColor color = QColorDialog::getColor (static_cast<int>(Qt::black));

    if (color.isValid ())
    {
        //先将新选择的颜色传给绘制区,用于改变画笔的颜色值
        dw->setColor (color);
        //改变按钮图案
        QPixmap p(20, 20);
        p.fill (color);
        colorBtn->setIcon (QIcon(p));
        dw->setColor(color);
    }

}

int MainWindow::EdgeNumber()
{
    bool ok;
    int edgeNumber=QInputDialog::getInt(this,tr("多边形"),tr("输入多边形的边数"),edgeLabel->text().toInt(),0,100,1,&ok);
    if(ok)
    {
        edgeLabel->setText(QString(tr("%1")).arg(edgeNumber));
    }
    return edgeNumber;
}

MainWindow::~MainWindow()
{

}
