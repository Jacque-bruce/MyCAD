#include "paintwidget.h"

#include<QPainter>
#include<QImage>

#include<QtPrintSupport/QPrintDialog>
#include<QtPrintSupport/QPrinter>

paintWidget::paintWidget(QWidget *parent) : QWidget(parent)
{
    image=QImage(400,300,QImage::Format_RGB32);  //画布的初始化大小设为400*300，使用32位颜色
       backColor=qRgb(255,255,255);  //画布初始化背景色使用白色
       image.fill(backColor);

       modified=false;
       //modified=true;

       scale=1;
       angle=0;
       shear=0;

       penColor=Qt::black;
       brushColor=Qt::black;
       penWidth=1;
       penStyle=Qt::SolidLine;
       curShape=None;

       isDrawing=false;
}
