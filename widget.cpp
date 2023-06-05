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
    Tx = Ty = 0;
    speed = 40;
    direction =1 ;

    rotateTimer = new QTimer();
    connect(rotateTimer,SIGNAL(timeout()),this,SLOT(rotate()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *evt){
    Q_UNUSED(evt)
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

    for(int i = 0; i < 8; i++){
        dibujo.mapear( &starAim[i][0], &starAim[i][1],&x1, y1, L, M );
        //qDebug()<<"x1: "<<x1<<"     y1"<<y1<<'\n';
        dibujo.mapear(&starAim[i+1][0], &starAim[i+1][1],&x2, y2, L, M);
        //qDebug()<<"x2: "<<x2<<"     y2"<<y2<<'\n';
        canvas->drawLine(x1, y1, x2, y2);
    }

    //dibujo.mapear(&starAim[1][0], &starAim[1][1],&centralX,centralY,L, M);
}

void Widget::translate(int Tx, int Ty)
{
    Matrix fig, id, figtransf;

     fig.Inicializa(9,3);
     id.Inicializa(3,3);
     figtransf.Inicializa(9,3);

     for(int i = 0; i < fig.numRen(); i++){
         for(int j = 0; j < fig.numCol(); j++){
             fig.SET(i,j, starAim[i][j]);

         }

     }

     figtransf.traslacion(fig,id,Tx,Ty);

     for(int r = 0; r < figtransf.numRen(); r++){
         for(int c = 0; c < figtransf.numCol(); c++){
             starAim[r][c] = figtransf.GET(r,c);
         }
     }
     this->update();
}

void Widget::keyPressEvent(QKeyEvent *evt) {
    pressedKeys.insert(evt->key());

    if (pressedKeys.count(Qt::Key_D))
        translate(Tx + speed, 0);

    if (pressedKeys.count(Qt::Key_A))
        translate(Tx - speed, 0);

    if (pressedKeys.count(Qt::Key_W))
        translate(0, Ty + speed);

    if (pressedKeys.count(Qt::Key_S))
        translate(0, Ty - speed);
}

void Widget::keyReleaseEvent(QKeyEvent *evt)
{
    pressedKeys.erase(evt->key());
}

void Widget::rotate()
{
    static int cont = 1;
    if(cont>=5){
        cont=0;
        rotateTimer->stop();
    }
    cont++;
    int angle =18*direction;
    Matrix fig,id,fres;

    centralX = starAim[1][0];
    centralY = starAim[1][1];

    fig.Inicializa(9,3);
    id.Inicializa(3,3);
    fres.Inicializa(9,3);

    for(int i=0;i<fig.numRen();i++){
        for(int j=0;j<fig.numCol();j++){
            fig.SET(i,j,starAim[i][j]);
        }
    }

    fres.rotacion(fig,id,angle);

    for(int r=0;r<fres.numRen();r++){
        for(int c=0;c<fres.numCol();c++){
            starAim[r][c] = fres.GET(r,c);
        }
    }

    translate(centralX-starAim[1][0],centralY-starAim[1][1]);
}

void Widget::mousePressEvent(QMouseEvent *evt)
{
    if(evt->button()==Qt::RightButton){
        direction=1;
        rotateTimer->start(15);
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *evt)
{
    if(evt->button()==Qt::RightButton){
        direction =-1;
        rotateTimer->start(15);
    }
}
