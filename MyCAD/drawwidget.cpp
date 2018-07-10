#include "drawwidget.h"
#include <QtGui>
#include <QPen>
#include <QColor>
#include <QRubberBand>
#include<QGraphicsView>



drawWidget::drawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    //背景色设置为白色
    setPalette(QPalette(Qt::white));
    pix=new QPixmap(size());

    //填充背景色为白色
    pix->fill(Qt::white);
    //设置绘图区域的最小尺寸
    setMinimumSize(1280,720);

    rubberBand=NULL;
}
void drawWidget::setStyle (int s)
 {
     style = s;
 }

void drawWidget::setWidth(int w)
{
    weight=w;
}

void drawWidget::setColor(QColor c)
{
    color=c;
}

void drawWidget::mousePressEvent(QMouseEvent *e)
{
    QPainter *painter=new QPainter;
    QPen pen;


    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight);
    pen.setColor(color);

    painter->begin(pix);
    painter->setPen(pen);

    startPos=e->pos();

    if(!rubberBand)
            rubberBand = new QRubberBand(QRubberBand::Rectangle,this);
        rubberBand->setGeometry(QRect(startPos,QSize()));
        rubberBand->show();

    if(isLine||isCircle||isRect)
    {
       painter->drawPoint(startPos);
    }

    painter->end();
    update();
}

void drawWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(rubberBand)
            rubberBand->setGeometry(QRect(startPos,e->pos()).normalized());

    /*QPainter *painter=new QPainter;
    QPen pen;


    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight);
    pen.setColor(color);

    painter->begin(pix);
    painter->setPen(pen);
    endPos=e->pos();

    if(isLine)
    {
        BresenhamLine(painter,startPos,e->pos());
    }
    if(isCircle)
    {
        int r;
        int r1,r2;
        r1=endPos.rx()-startPos.rx();
        r2=endPos.ry()-startPos.ry();
        r=sqrt(r1*r1+r2*r2);
        BresenhamCircle(painter,startPos,r);
    }
    if(isRect)
    {
        DrawRectangle(painter,startPos,endPos);
    }

    painter->end();*/

    update();
}

void drawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(rubberBand)
           rubberBand->hide();

    QPainter *painter=new QPainter;
    QPen pen;


    pen.setStyle((Qt::PenStyle)style);
    pen.setWidth(weight);
    pen.setColor(color);

    painter->begin(pix);
    painter->setPen(pen);
    endPos=e->pos();

    if(isLine)
    {
        BresenhamLine(painter,startPos,e->pos());
    }
    if(isCircle)
    {
        int r;
        int r1,r2;
        r1=endPos.rx()-startPos.rx();
        r2=endPos.ry()-startPos.ry();
        r=sqrt(r1*r1+r2*r2);
        BresenhamCircle(painter,startPos,r);

    }

    if(isRect)
    {
        DrawRectangle(painter,startPos,endPos);
    }
    if(isPolygon)
    {

        DrawPolygon(painter,startPos,endPos,polygonEdge);
    }
    if(isClearRect)
    {
        ClearRect(painter,startPos,endPos);
    }
    painter->end();
    startPos=e->pos();
    update();
}

void drawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0),*pix);

}

//画板大小自适应
void drawWidget::resizeEvent(QResizeEvent *event)
{
    if(height()>pix->height()||width()>pix->width())
    {
        QPixmap *newPix=new QPixmap(size());
        newPix->fill(Qt::white);

        QPainter p(newPix);
        p.drawPixmap(QPoint(0,0),*pix);
        pix=newPix;
    }

    QWidget::resizeEvent(event);
}

//清除画板
void drawWidget::clear()
{
    QPixmap *clearPix=new QPixmap(size());
    clearPix->fill(Qt::white);
    pix=clearPix;
    update();
}

//Bresenham画线算法
void drawWidget::BresenhamLine(QPainter *painter,QPoint sp,QPoint ep)
{

    int x0=sp.rx();
    int y0=sp.ry();
    int x1=ep.rx();
    int y1=ep.ry();

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x = x0;
    int y = y0;
    int stepX = 1;
    int stepY = 1;
    if(x0 > x1)  //从右向左画
        stepX = -1;
    if(y0 > y1)
        stepY = -1;

    if(dx > dy)  //沿着最长的那个轴前进
    {
        int e = dy * 2 - dx;
        for(int i=0; i<=dx; i++)
        {
           painter->drawPoint(x,y);
           x += stepX;
           e += dy;
           if(e >= 0)
            {
                y += stepY;
                e -= dx;
            }
        }
    }
    else
    {
        int e = 2 * dx - dy;
        for(int i=0; i<=dy; i++)
        {
            painter->drawPoint(x,y);
            y += stepY;
            e += dx;
            if(e >= 0)
            {
                x += stepX;
                e -= dy;
            }
        }
    }

}

//Bresenham画圆算法
void drawWidget::BresenhamCircle(QPainter *painter, QPoint o, int r)
{
    int ox=o.rx();
    int oy=o.ry();
    float d=1.25-r;
    int x=0,y=r,fx=r/1.4;

    while (x!=fx)
    {
        if(d<0)
        {
            d+=2*x+3;
        }
        else
        {
            d+=2*(x-y)+5;
            --y;
        }
        painter->drawPoint(ox+x,oy+y);
        painter->drawPoint(ox+x,oy-y);
        painter->drawPoint(ox-x,oy+y);
        painter->drawPoint(ox-x,oy-y);
        painter->drawPoint(ox+y,oy-x);
        painter->drawPoint(ox+y,oy+x);
        painter->drawPoint(ox-y,oy+x);
        painter->drawPoint(ox-y,oy-x);
        ++x;
    }
}
//矩形函数
void drawWidget::DrawRectangle(QPainter *painter, QPoint sp, QPoint ep)
{
    int x0=sp.rx();
    int y0=sp.ry();
    int x1=ep.rx();
    int y1=ep.ry();

    QPoint *p1=new QPoint(x1,y0);
    QPoint *p2=new QPoint(x0,y1);


    BresenhamLine(painter,sp,*p1);
    BresenhamLine(painter,sp,*p2);
    BresenhamLine(painter,*p1,ep);
    BresenhamLine(painter,*p2,ep);

}
//多边形
void drawWidget::DrawPolygon(QPainter *painter, QPoint sp, QPoint ep, int n)
{
    int x0=sp.rx();
    int y0=sp.ry();
    int x1=ep.rx();
    int y1=ep.ry();

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int R = sqrt(dx * dx + dy * dy);
    int px[n+1]={};
    int py[n+1]={};
    int angle=360/n;
    for(int i=1;i<=n;i++)
    {
        px[i]=x0+R*sin(angle*i*3.14/180);
        py[i]=y0+R*cos(angle*i*3.14/180);
        painter->drawPoint(px[i], py[i]);
    }

    for(int i=1;i<n;i++)
    {
        painter->drawLine(px[i],py[i],px[i+1],py[i+1]);
    }

    painter->drawLine(px[n],py[n],px[1],py[1]);


}
//擦除可选区域函数
void drawWidget::ClearRect(QPainter *painter, QPoint sp, QPoint ep)
{
    int x0=sp.rx();
    int y0=sp.ry();
    int x1=ep.rx();
    int y1=ep.ry();

    int dx = x1 - x0;
    int dy = y1 - y0;
    painter->eraseRect(x0,y0,dx,dy);
}
