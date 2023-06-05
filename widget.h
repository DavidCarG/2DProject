#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QtGui>
#include <QKeyEvent>
#include <QMouseEvent>
#include <set>
#include <QTimer>
#include <QPolygon>

#include "mapeo.h"
#include "matrix.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *evt) override;
    void asignAim();
    void drawAim();

    void translate(int Tx, int Ty);
    void keyPressEvent(QKeyEvent * evt) override;
    void keyReleaseEvent(QKeyEvent *evt) override;

    void mousePressEvent(QMouseEvent *evt) override;
    void mouseReleaseEvent(QMouseEvent *evt) override;

private slots:

    void rotate();

private:
    Ui::Widget *ui;

    QPainter *canvas;
    float starAim[9][3];
    float starAimBU[9][3];

    int L,M;

    set<int>pressedKeys;
    int Tx,Ty,speed;

    int centralX,centralY;
    QTimer *rotateTimer;
    int direction;

    QPolygon polyAim;
    QPainter *polygonCanvas;
    bool fillPolyAim;
};
#endif // WIDGET_H
