#include "matrix.h"
#include <math.h>
#include <assert.h>


//ARCHIVO DE IMPLEMENTACION DE LA CLASE

/* SE LLAMA AL CONSTRUCTOR DE LA MATRIZ */

// CONSTRUCTOR POR DEFECTO
Matrix::Matrix(int nr,int nc, float valor)
{
  ren = nr;
  col = nc;
  Mat = new float*[ren];//DEFINIMOS EL NUMERO DE RENS DEL
                        //VECTOR DE PUNTEROS
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
      Mat[i] = new float[col];
      assert(Mat[i]);
  }

  for(int i = 0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = valor;
}

// CONSTRUCTOR PARAMETRIZADO
Matrix::Matrix(float nr,float nc, float **m)
{
  ren = nr;
  col = nc;
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
      Mat[i] = new float[col];
      assert(Mat[i]);
  }

  for(int i = 0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = m[i][j];
}


//CONSTRUCTOR DE COPIA
Matrix::Matrix(Matrix &m)
{
   this->ren=m.numRen();
   this->col=m.numCol();
   this->Mat =new float*[ren];
   for(int i = 0; i < ren; i++)
   {
     Mat[i] = new float[col];
     assert(Mat[i]);
   }
   for(int i=0; i<ren; i++)
      for( int j=0; j<col; j++)
         Mat[i][j]=m.GET(i,j);
}

void Matrix::Inicializa(int R, int C)
{
   col=C;
   ren=R;
   Mat=new float *[ren];
   for(int i=0; i<ren; i++)
      Mat[i]=new float[col];
   for(int i=0; i<ren; i++)
      for(int j=0; j<col; j++)
         Mat[i][j]=0;
}

Matrix &Matrix::operator*=(Matrix &mat2)
{
   Matrix aux;
   aux.Inicializa(ren, mat2.numCol());
   for(int i=0; i<ren; i++)
   {
      for(int j=0; j<mat2.numCol(); j++)
      {
         float suma=0;
        // Mat[i][j]=0;
         for(int k=0; k<col; k++)
         {      //round o redondea
           suma+=floor(Mat[i][k]*mat2.GET(k,j)+0.5);
           aux.SET(i,j,suma);
         }
         //aux.SET(i,j,suma);
      }
   }
   asignar(aux);
   return *this;
}

// multiplica por un escalar la matriz
Matrix Matrix::operator*(float val)
{
   Matrix temp;
   temp.Inicializa(ren,col);
   for(int i=0; i<ren;i++)
      for(int j=0; j<col; j++)
         temp.SET(i,j,Mat[i][j]* val);
   return temp;
}

// multiplicar una matriz por otra (n x m)
Matrix &Matrix::operator*(const Matrix &m1)
{
  //assert((this->ren == m1.ren) && (col == m1.col));
   Matrix * result = new Matrix(ren,col,0);//se incializa a 0's
   assert(result);
   for(int i=0; i < ren; i++)
     for(int j = 0;  j < col; j++)
                       //DEBE SER EL NUMERO DE COLUMNAS
                     //REN SOLO SI ES CUADRADA EJ: 3 x 3

         // nuestra matriz de transformación siempre va a ser de 3x3
       for(int k = 0; k < col; k++)
            //result->Mat[i][j]= result->Mat[i][j] +
           // Mat[i][k] * m1.Mat[k][j];
           result->Mat[i][j] += Mat[i][k] * m1.Mat[k][j];

   return *result;
}

Matrix &Matrix::operator=(Matrix &m)
{
//eliminar el tamaño de la matriz destino
  for(int i= 0; i<ren;i++ )
     //Se borran los renglones de la matriz
       delete [] Mat[i];
  //Se borra el arreglo de punteros
  delete []Mat;
//Asignar los nuevos datos de la matriz que llego
  ren=m.numRen();
  col = m.numCol();
  Mat = new float*[ren];
  assert(Mat);
  for(int i = 0; i < ren; i++)
  {
     Mat[i] = new float[col];
     assert(Mat[i]);
  }
  for( int i =0; i < ren; i++)
    for(int j = 0; j < col; j++)
        Mat[i][j] = m.Mat[i][j];

  return *this;
}


Matrix &Matrix::asignar(Matrix m)
{
   for(int i=0;i<m.numRen();i++)
       for(int j=0;j<m.numCol();j++)
                Mat[i][j]=m.GET(i,j);
   return *this;
}

Matrix::~Matrix()
{
  //Se libera la memoria
  for(int i= 0; i<ren;i++ )
     //Se borran los renglones de la matriz
       delete [] Mat[i];
  //Se borra el arreglo de punteros
  delete []Mat;

}

Matrix &Matrix::Identidad()
{
  for(int i=0; i < ren; i++)
    for( int j = 0; j < col; j++)
      if( i == j)
         Mat[i][i]= 1;
      else
         Mat[i][j]= 0;
  return *this;
}

Matrix &Matrix::traslacion(Matrix figura, Matrix id, int Tx, int Ty)
{
    id.Identidad();
    id.SET(2,0,Tx);
    id.SET(2,1,Ty);

    figura *= id;
    this->asignar(figura);
    return *this;

}

Matrix &Matrix::esclacion(Matrix fig, Matrix id, float Sx, float Sy)
{
    id.Identidad();
    id.SET(0,0, Sx);
    id.SET(1,1, Sy);

    fig *= id;

    asignar(fig);

    return *this;

}

Matrix &Matrix::escalacionPuntoFijo(Matrix fig, Matrix id, float Sx, float Sy, int pFx, int pFy)
{
    id.Identidad();
    float escPFx = pFx * (1 - Sx);
    float escPFy = pFy * (1- Sy);

    id.SET(0,0,Sx);
    id.SET(1,1,Sy);

    id.SET(2,0,escPFx);
    id.SET(2,1,escPFy);

    fig *= id;

    asignar(fig);

    return *this;
}

Matrix &Matrix::rotacion(Matrix fig, Matrix id, float grados)
{
    id.Identidad();
    float radianes = grados*M_PI/180.0;

    id.SET(0,0,cos(radianes));
    id.SET(0,1,sin(radianes));
    id.SET(1,0,-sin(radianes));
    id.SET(1,1,cos(radianes));

    fig*=id;
    asignar(fig);
    return *this;
}

Matrix &Matrix::rotacionPuntoPivote(Matrix id, Matrix fig, float angulo, float pPx, float pPy)
{
//    id.Identidad();
//    float radianes = angulo*M_PI/180.0;

//    float r20 = pPx + (x - pPx) * cos(angle) - (y - pPy) * sin(angle);
//    float r21 = pPy*(1-cos(radianes)-pPx*sin(radianes));

//    id.SET(2,0,r20);
//    id.SET(2,1,r21);

//    fig*=id;
//    asignar(fig);
    return *this;
}

