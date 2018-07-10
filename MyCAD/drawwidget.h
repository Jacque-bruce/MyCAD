#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QtGui>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QColor>
#include <QPixmap>
#include <QPoint>
#include <QPainter>
#include <QPalette>
#include <QRubberBand>


class drawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit drawWidget(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    void paintEvent(QPaintEvent *);

    void resizeEvent(QResizeEvent *);

    void BresenhamLine(QPainter *painter,  QPoint sp,QPoint ep);

    void BresenhamCircle(QPainter *painter,QPoint o,int r);

    void DrawRectangle(QPainter *painter,QPoint sp,QPoint ep);

    void DrawPolygon(QPainter *painter,QPoint sp,QPoint ep,int n);

    void ClearRect(QPainter *painter,QPoint sp,QPoint ep);

    bool isLine=false;
    bool isCircle=false;
    bool isRect=false;
    bool isPolygon=false;
    bool isClearRect=false;

    int  polygonEdge;



signals:

public slots:
    void setStyle(int);//线型风格
    void setWidth(int);//线宽
    void setColor(QColor);//画笔颜色
    void clear();

private:
    QPixmap *pix;
    QPixmap *tempPix;
    QPoint  startPos;
    QPoint  endPos;
    int style;
    int  weight;
    QColor color;
    QRubberBand *rubberBand;




};

#endif // DRAWWIDGET_H
