#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    asignAim();
    L = 100;
    M = 400;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *evt){
    canvas = new QPainter(this);
    drawAim();
    canvas->end();
}

void Widget::asignAim(){
    starAim[0][0] = 125; starAim[0][1] = 125; starAim[0][2] = 1;
    starAim[1][0] = 200; starAim[1][1] = 112.5; starAim[1][2] = 1;
    starAim[2][0] = 275; starAim[2][1] = 125; starAim[2][2] = 1;
    starAim[3][0] = 245; starAim[3][1] = 112.5; starAim[3][2] = 1;
    starAim[4][0] = 275; starAim[4][1] = 100; starAim[4][2] = 1;
    starAim[5][0] = 200; starAim[5][1] = 112.5; starAim[5][2] = 1;
    starAim[6][0] = 125; starAim[6][1] = 100; starAim[6][2] = 1;
    starAim[7][0] = 155; starAim[7][1] = 112.5; starAim[7][2] = 1;
    starAim[8][0] = 125; starAim[8][1] = 125; starAim[8][2] = 1;
}

void Widget::drawAim()
{
    canvas->setPen(QColor(255,0,0));

    mapeo dibujo;
    dibujo.ventana(0,0,size().width(),size().height());
    dibujo.puerto(0,0, size().width(), size().height());

    int x1, y1, x2, y2;

    // Demostrar cómo funciona este ciclo
    for(int i = 0; i < 8; i++){
        dibujo.mapear( &starAim[i][0], &starAim[i][1],&x1, y1, L, M );
        qDebug()<<"x1: "<<x1<<"     y1"<<y1<<'\n';
        dibujo.mapear(&starAim[i+1][0], &starAim[i+1][1],&x2, y2, L, M);
        qDebug()<<"x2: "<<x2<<"     y2"<<y2<<'\n';
        canvas->drawLine(x1, y1, x2, y2);
    }
}
