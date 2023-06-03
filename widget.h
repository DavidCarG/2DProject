#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>

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

private:
    Ui::Widget *ui;

    QPainter *canvas;
    float starAim[9][3];
    float starAimBU[9][3];

    int L,M;
};
#endif // WIDGET_H
