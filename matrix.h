#ifndef MATRIX_H
#define MATRIX_H


//ARCHIVO DE DEFINICION DE LA CLASE
class Matrix
{
//POR DEFAULT SON PRIVADOS
    int col, ren;
    float **Mat;//DOBLE INDIRECCION

    public:

       Matrix(int nr=4,int nc=4, float valor=0);//constructor con arg. por defecto

       Matrix(float nr,float nc, float **m);

       Matrix(Matrix &);//CONSTRUCTOR DE COPIA
       ~Matrix();//DESTRUCTOR
       inline void SET(int R, int C, float val)
           {
               Mat[R][C]=val;
           }
       float GET(int R, int C){ return Mat[R][C];}
       int numCol(){ return col; }
       int numRen(){ return ren; }
       void Inicializa(int , int );

       Matrix &operator *=(Matrix &mat2);
//EXISTE LA SOBRECARGA DE OPERADORES EN JAVA

       Matrix &operator*(const Matrix &m1);

       Matrix operator*(float);//Multiplicar por un escalar

       Matrix &operator=(Matrix &);

       Matrix & asignar(Matrix);

       Matrix & Identidad(); // PERMITE INICIALIZAR LA MATRIZ BASE

       //TRANSFORMACIONES

       Matrix &traslacion(Matrix, Matrix, int, int);

       Matrix &esclacion(Matrix, Matrix, float, float);

       Matrix &escalacionPuntoFijo(Matrix, Matrix, float Sx, float Sy, int pFx, int pFy);

       Matrix &rotacion(Matrix,Matrix,float);

       Matrix &rotacionPuntoPivote(Matrix,Matrix,float angulo,float,float);

};

#endif // MATRIX_H
