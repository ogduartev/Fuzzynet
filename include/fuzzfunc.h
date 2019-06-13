/***************************************************************************
                          fuzzfunc.h  -  description
                             -------------------
    begin                : dom abr 13 2003
    copyright            : (C) 2003 by Oscar Germán Duarte Velasco
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   Este programa ha sido diseñado por Oscar G. Duarte V. por encargo del *
 *   Departamento de Ciencias de la Computación e Inteligencia             *
 *   Artificial de la Universidad de Granada.                              *
 *                                                                         *
 ***************************************************************************/

#ifndef _FUZZFUNC_H
#define _FUZZFUNC_H


#include "fuzznum.h"

#include <wx/wx.h>
#include <math.h>
#include <algorithm>

#define ID_COMBINA_LINEAL 1
#define ID_SUPREMO 2
#define ID_INFIMO 3
#define ID_POLINOMIO 4
#define ID_COMBINA_LINEAL_ACOTADA 5
#define ID_PROD_SUMA  6
#define ID_SUMA_PROD 7
#define ID_RANKING 8
#define ID_PRODUCTO 9
#define ID_RANKING_OWA 10
#define ID_OWA_FAULHABER 11

using namespace std;
/**
 * La Clase Función es una clase abstracta que implementa las funciones crisp
 * monótonas extendidas a Números Difusos.
 *
 * La extensión se realiza con los algoritmos de Extensión Directa, Inversa
 * Necesaria, Inversa Posible, e Inversa Intermedia. Se implementa también el cálculo
 * de la medida de existencia de la Extensión INversa.
 *
 * ATENCION: Falta definir funciones para adicionar y eliminar variables... deben ser virtual=0
 */
class Funcion
{
public:
	Funcion()
  {
    ParametrosVariables=NULL;
    ParametrosFijos=NULL;
    FlagUmbral=0;
   }
	virtual ~Funcion()
  {
    if(ParametrosFijos != NULL)
    {
      delete[] ParametrosFijos;
    }
    if(ParametrosVariables != NULL)
    {
      delete[] ParametrosVariables;
    }
  }
/**
 * Función virtual para implmentar la función directa a extender
 * \param x es el vector de argumentos
 * \return La función calculada en x
 */
	virtual float directa(float *x)=0;
 /**
  * Funciones para presenetar la descripción de la función
  */
  virtual wxString descripcion()=0;
  virtual wxString descripcionHTML(){return descripcion();}
  virtual wxString descripcionLatex(){return descripcion();}
/**
 * Función virtual para implmentar la función inversa a extender
 * \param y es la salida de la función
 * \param x es el vector de entradas
 * \param k es el índice de la entrada que se desea calcular:
 * \return  x[k] calculada a partir de las demás entradas x y de y
 */
	virtual float inversa(float y, float *x, int k)=0;

	void directaDifusa(NumeroDifuso *Y, NumeroDifuso **X);
/**
 * Función para implementar la extensión inversa Intermedia
 * \param Y es un apuntador a la salida de la función
 * \param X es el vector de apuntadores de las entradas
 * \param k es el índice de la entrada que se desea calcular:
 * \param r es el parámetro que determina qué función intermedia debe
 * calcularse. r está entre 0 y 1. si es 0 calcula la extensión Posible;
 * si es 1 calcula la Extensión Necesaria.
 * \return  YR calculada con las entradas X conocidas y X[k] calculado
 * el número de alfa-cortes de YR es igual al de Y
 */
	NumeroDifuso* inversaIntermediaDifusa(NumeroDifuso *Y, NumeroDifuso **X, int k, float r)
	{
		NumeroDifuso *YP;
		YP=new NumeroDifuso();
		YP->copiar(Y);
		inversaDifusa(YP,X,k,r);
		return YP;
	}
/**
 * Función para implementar la extensión inversa Posible
 * \param Y es un apuntador a la salida de la función
 * \param X es el vector de apuntadores de las entradas
 * \param k es el índice de la entrada que se desea calcular:


 */
	void inversaPosibleDifusa(NumeroDifuso *Y, NumeroDifuso **X, int k)
	{
		NumeroDifuso *YP;
		YP=new NumeroDifuso();
		YP->copiar(Y);
		inversaDifusa(YP,X,k,0);
		delete YP;
	}
/**
 * Función para implementar la extensión inversa Necesaria
 * \param Y es un apuntador a la salida de la función
 * \param X es el vector de apuntadores de las entradas
 * \param k es el índice de la entrada que se desea calcular:
 * \return  YR calculada con las entradas X conocidas y X[k] calculado
 * el número de alfa-cortes de YR es igual al de Y
 */
	NumeroDifuso* inversaNecesariaDifusa(NumeroDifuso *Y, NumeroDifuso **X, int k)
	{
		NumeroDifuso *YP;
		YP=new NumeroDifuso();
		YP->copiar(Y);
		inversaDifusa(YP,X,k,1);
		return YP;
	}
	float umbral(NumeroDifuso *Y, NumeroDifuso **X, int k);
  virtual void cambiarParametroFijo(int j, float p);
  virtual void cambiarParametroVariables(int i,int j, float p);

  void crearMatrices();
/**
 * Número de variables de entrada de la función
 */
	int Orden;
/**
 *  Vector que determina si la relación entrada-salidaes creciente o decreciente

 * si Crecer[i]=1 la relación entre la entrada i y la salida es creciente;
 * si Crecer[i]=-1 la relación entre la entrada i y la salida es decreciente;
 */
	int *Crecer;
/**
 * Variable interna para el cálculo de la medida de la existencia de la extensión inversa
 */
	int FlagUmbral;
/**
 * Nombre de la función
 */
	wxString Tipo;
/** Identificador del tipo de Función:
 * 1=Combinación Lineal  2=Supremo 3;Infimo 4=Polinomio
 * 5=CombinacionLinealAcotada 6=Logaritmica 7=Valor
 * 10=Cash 15=Valor2

 */
	int Identificador;
  wxArrayString NombreParametrosFijos;
  wxArrayString NombreParametrosVariables;
  float *ParametrosFijos;
  float **ParametrosVariables;

	BOOL operator==(Funcion& other);
	void operator=(Funcion& other);

  virtual void adicionarOrden(int loc=-1);
  virtual void eliminarOrden(int loc);

	virtual void write(Mi_ofpstream &str);
	Funcion* read(Mi_ifpstream &str);
//	virtual void readLocal(Mi_ifpstream &str){}

protected:
	void inversaDifusa(NumeroDifuso *Y, NumeroDifuso **X, int k, float r);

};


/**
 * Implementa la función a0*x[0]+a1*x[1]+...an*x[n]+Offset
 * \see CombinacionLinealAcotada
 */
class CombinacionLineal:public Funcion
{
public:
/**
 * crea la función x[0]+x[1]
 */
	CombinacionLineal()
	{
		Identificador=ID_COMBINA_LINEAL;
		Tipo=wxT("Combinación Lineal");
		Orden=2;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("a[0]"));
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=0.0;
        float x[2];
        x[0]=1.0;x[1]=1.0;
        llenarVectores(x,2);
	}
/**
 * Combinacion Lineal genérica a0*x[0]+a1*x[1]+...an*x[n]+Offset
 * \param x vector con los coeficientes a0, a1, ...an
 * \param ord número de variables x[0], x[1], ...x[n]  (n=ord-1)
 * \param off Offset de la combinación Lineal
 */
	CombinacionLineal(float *x,int ord,float off=0.0)
	{
		Identificador=ID_COMBINA_LINEAL;
		Tipo=wxT("Combinación Lineal");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("a[0]"));
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
        Crecer=new int[Orden];
	llenarVectores(x,ord);
        ParametrosFijos[0]=off;
	}
	~CombinacionLineal()
	{
		delete[] Crecer;
	}
  void cambiarParametroVariables(int i,int, float p)
  {
    coeficiente(p,i);
  }
	void llenarVectores(float *x, int ord);
	float coeficiente(int i){return ParametrosVariables[i][0];}
	void coeficiente(float x, int i)
	{
		if(i<0){i=0;}
		if(i>=Orden){i=Orden-1;}
		ParametrosVariables[i][0]=x;


		if(ParametrosVariables[i][0]==0)
		{
			ParametrosVariables[i][0]=0.0001;
		}
		if(ParametrosVariables[i][0]>0)
		{
			Crecer[i]=1;
		}else
		{
			Crecer[i]=-1;
		}

	}
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
  float inversa(float y, float *x, int k);

};

/**
 * Implementa la función supremo: calcula el máximo de n datos
 */
class Supremo:public Funcion
{
public:
/**
 * \param ord número de datos entre los que hay que buscar el máximo
 */
	Supremo(int ord)
	{
		Identificador=ID_SUPREMO;

		Tipo=wxT("Supremo");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosVariables.Clear();
        crearMatrices();
		Crecer=new int[Orden];
		llenarVectores(ord);
	}
	~Supremo()
	{
		delete[] Crecer;
	}
	void llenarVectores( int ord);
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);

protected:

};

/**
 * Implementa la función infimo: calcula el máínmo de n datos
 */
class Infimo:public Funcion

{
public:
/**
 * \param ord número de datos entre los que hay que buscar el mínimo
 */
	Infimo(int ord)
	{
		Identificador=ID_INFIMO;
		Tipo=wxT("Infimo");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosVariables.Clear();
        crearMatrices();
		Crecer=new int[Orden];
		llenarVectores(ord);
	}
	~Infimo()
	{
		delete[] Crecer;
	}
	void llenarVectores( int ord);
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);

protected:

};
/**
 * Implementa la función a0*x[0]^b0+a1*x[1]^b1+...+an*x[n]^bn
 * ATENCION: sólo es válida para valores positivos de x .
 */
class Polinomio:public Funcion
{
public:
/**
 * Implementa el polinomio x[0]+x[1]
 */
	Polinomio()
	{
		Identificador=ID_POLINOMIO;
		Tipo=wxT("Polinomio");
		Orden=2;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        NombreParametrosVariables.Add(wxT("b"));
        crearMatrices();
		Crecer=new int[Orden];
        ParametrosVariables[0][0]=1.0;
        ParametrosVariables[0][1]=1.0;
        ParametrosVariables[1][0]=1.0;
        ParametrosVariables[1][1]=1.0;
		Crecer[0]=1;Crecer[1]=1;
	}
/**
 * el polinomio genérico a0*x[0]^b0+a1*x[1]^b1+...+an*x[n]^bn
 * \param x vector con los coeficientes a0, a1, ...an
 * \param e vector con los coeficientes b0, b1, ...bn
 * \param ord número de variables x[0], x[1], ...x[n]  (n=ord-1)
 */
	Polinomio(float *x,float *e,int ord)
	{
		Identificador=ID_POLINOMIO;
		Tipo=wxT("Polinomio");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        NombreParametrosVariables.Add(wxT("b"));
        crearMatrices();
		Crecer=new int[Orden];
		llenarVectores(x,e,ord);
	}
	~Polinomio()
	{
		delete[] Crecer;
	}
  void cambiarParametroVariables(int i,int, float p)
  {
    coeficiente(p,i);
  }
	void llenarVectores(float *x,float *e, int ord);

	float coeficiente(int i){return ParametrosVariables[i][0];}
	void coeficiente(float x, int i)
	{
		if(i<0){i=0;}
		if(i>=Orden){i=Orden-1;}
		ParametrosVariables[i][0]=x;
		if(ParametrosVariables[i][0]==0)
		{
			ParametrosVariables[i][0]=0.0001;
		}

		if((ParametrosVariables[i][0]*ParametrosVariables[i][1])>0.0)
		{
			Crecer[i]=1;
		}else
		{
			Crecer[i]=-1;
		}
	}
	float exponente(int i){return ParametrosVariables[i][1];}
	void exponente(float x, int i)
	{
		if(i<0){i=0;}
		if(i>=Orden){i=Orden-1;}
		ParametrosVariables[i][1]=x;
		if(ParametrosVariables[i][1]==0)
		{
			ParametrosVariables[i][1]=0.0001;
		}
		if((ParametrosVariables[i][0]*ParametrosVariables[i][1])>0)
		{
			Crecer[i]=1;
		}else
		{
			Crecer[i]=-1;
		}
	}
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);
};

/**
 * Implementa una Combinación Lineal acotada entre -Cota y +Cota
 * \see CombinacionLineal
 */
class CombinacionLinealAcotada:public Funcion
{
public:
/**
 * Implementa x[0]+x[1] acotado entre -1.0 y 1.0
 */

	CombinacionLinealAcotada()
	{
		Identificador=ID_COMBINA_LINEAL_ACOTADA;
		Tipo=wxT("Combinación Lineal Acotada");
		Orden=2;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosVariables.Clear();
        NombreParametrosFijos.Add(wxT("Offset"));
        NombreParametrosFijos.Add(wxT("Cota Inferior"));
        NombreParametrosFijos.Add(wxT("Cota Superior"));
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
		Crecer=new int[Orden];
      ParametrosVariables[0][0]=1.0;
      ParametrosVariables[1][0]=1.0;
		Crecer[0]=1;Crecer[1]=1;
    ParametrosFijos[0]=0.0;
    ParametrosFijos[1]=-1.0;
    ParametrosFijos[2]=1.0;
	}
/**
 * Combinacion Lineal genérica a0*x[0]+a1*x[1]+...an*x[n]+Offset
 * acotada entre -Cota y +Cota
 * \param x vector con los coeficientes a0, a1, ...an
 * \param ord número de variables x[0], x[1], ...x[n]  (n=ord-1)
 * \param off Offset de la combinación Lineal
 * \param cot Cota de la combinación Lineal. Si la combinación lineal se sale del
 * intervalo [cotinf,cotsup] el valor se ajusta al extremo más cercano de ese intervalo
 */
CombinacionLinealAcotada(float *x,int ord,float off=0.0,float cotinf=-1.0,float cotsup=1.0)
	{
		Identificador=ID_COMBINA_LINEAL_ACOTADA;
		Tipo=wxT("Combinación Lineal Acotada");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosVariables.Clear();
        NombreParametrosFijos.Add(wxT("Offset"));
        NombreParametrosFijos.Add(wxT("Cota Inferior"));
        NombreParametrosFijos.Add(wxT("Cota Superior"));
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
		Crecer=new int[Orden];
		llenarVectores(x,ord);
    ParametrosFijos[0]=off;
    ParametrosFijos[1]=cotinf;
    ParametrosFijos[2]=cotsup;
	}
	~CombinacionLinealAcotada()
	{
		delete[] Crecer;
	}
  void cambiarParametroVariables(int i,int, float p)
  {
    coeficiente(p,i);
  }
	void llenarVectores(float *x, int ord);
	float coeficiente(int i){return ParametrosVariables[i][0];}
	void coeficiente(float x, int i)
	{
		if(i<0){i=0;}
		if(i>=Orden){i=Orden-1;}
		ParametrosVariables[i][0]=x;
		if(ParametrosVariables[i][0]==0)
		{
			ParametrosVariables[i][0]=0.0001;
		}
		if(ParametrosVariables[i][0]>0)

		{
			Crecer[i]=1;
		}else
		{
			Crecer[i]=-1;
		}

	}
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);

};
/**
 * Producto-Suma. función genérica a0*x[0]*(a1*x[1]+...an*x[n])+Offset
 * Atención: es válida para x[i]>0, a[i]>=0 i=0,1,2...n
 * \see CombinacionLinealAcotada
 */
class ProdSuma:public Funcion
{
public:
/**
 * crea la función x[0]+x[1]
 */
	ProdSuma()
	{
		Identificador=ID_PROD_SUMA;

		Tipo=wxT("Producto-Suma");



		Orden=2;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("a[0]"));
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=0.0;
        float x[2];
        x[0]=1.0;x[1]=1.0;
        llenarVectores(x,2);
	}
/**
 * Producto-Suma. funcón genérica a0*x[0]*(a1*x[1]+...an*x[n])+Offset
 * Atención: es válida para x[i]>0, a[i]>=0 i=0,1,2...n
 * \param x vector con los coeficientes a0, a1, ...an
 * \param ord número de variables x[0], x[1], ...x[n]  (n=ord-1)
 * \param off Offset de la combinación Lineal
 */
	ProdSuma(float *x,int ord,float off=0.0)
	{
		Identificador=ID_PROD_SUMA;
		Tipo=wxT("Producto-Suma");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("a[0]"));
        NombreParametrosVariables.Clear();

        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
        Crecer=new int[Orden];
		llenarVectores(x,ord);
        ParametrosFijos[0]=off;
	}
	~ProdSuma()
	{
		delete[] Crecer;
	}
  void cambiarParametroVariables(int i,int, float p)
  {
    coeficiente(p,i);
  }
	void llenarVectores(float *x, int ord);
	float coeficiente(int i){return ParametrosVariables[i][0];}
	void coeficiente(float x, int i)
	{
		if(i<0){i=0;}
		if(i>=Orden){i=Orden-1;}
		ParametrosVariables[i][0]=x;
		if(ParametrosVariables[i][0]==0)
		{
			ParametrosVariables[i][0]=0.0001;
		}

		if(ParametrosVariables[i][0]*ParametrosVariables[0][0]>0.0)
		{
      Crecer[i]=1;
		}else
		{
      Crecer[i]=-1;
		}

	}
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);

};

/**
 * Suma-Producto. funcón genérica  a0*x[0]*a1*x[1] + a2*x[2]*a3*x[3] +... an-1+x[n-1]*an*x[n] +Offset
 * Atención: es válida para x[i]>0, a[i]>=0 i=0,1,2...n
 * \see CombinacionLinealAcotada

 */
class SumaProd:public Funcion
{
public:
/**

 * crea la función x[0]+x[1]
 */
	SumaProd()
	{
		Identificador=ID_SUMA_PROD;
		Tipo=wxT("Suma-Producto");
		Orden=2;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("a[0]"));
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=0.0;
        float x[2];
        x[0]=1.0;x[1]=1.0;
        llenarVectores(x,2);
	}
/**
 * Suma-Producto. funcón genérica a0*x[0]*a1*x[1] + a2*x[2]*a3*x[3] +... an-1+x[n-1]*an*x[n]  +Offset
 * Atención: es válida para x[i]>0, a[i]>=0 i=0,1,2...n ,
 * Debe haber un número par de variables
 * \param x vector con los coeficientes a0, a1, ...an, todos positivos
 * \param ord número de variables x[0], x[1], ...x[n]  (n=ord-1), ord es nu número par
 * \param off Offset de la combinación Lineal
 */


	SumaProd(float *x,int ord,float off=0.0)
	{
		Identificador=ID_SUMA_PROD;
		Tipo=wxT("Suma-Producto");
    if(ord%2!=0){Orden=ord-1;}else{Orden=ord;}
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("a[0]"));
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=off;
		llenarVectores(x,ord);
	}
	~SumaProd()
	{

		delete[] Crecer;
	}
  void cambiarParametroVariables(int i,int, float p)
  {
    coeficiente(p,i);
  }
	void llenarVectores(float *x, int ord);
	float coeficiente(int i){return ParametrosVariables[i][0];}
	void coeficiente(float x, int i)
	{
		if(i<0){i=0;}
		if(i>=Orden){i=Orden-1;}
		ParametrosVariables[i][0]=x;
		if(ParametrosVariables[i][0]==0.0)
		{
			ParametrosVariables[i][0]=0.0001;
		}
		if(ParametrosVariables[i][0]>0)
		{
			Crecer[i]=1;
		}else
		{
			ParametrosVariables[i][0]=-ParametrosVariables[i][0];
      Crecer[i]=1;
		}

	}
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);
};

/**
 * Implementa la función
 */
class Ranking:public Funcion
{
public:
/**
 * crea la función que compara x[0] con los demás valores x[i].
 * el parámetro "orden" determina si la comparación es ascendente o descendente
 * si "orden">=0 y=(x[0])/sum(x))
 *
 * si "orden"<0 y=1-(x[0])/sum(x))
 *
 */
	Ranking()
	{
		Identificador=ID_RANKING;
		Tipo=wxT("Ranking");
		Orden=2;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("orden"));
        NombreParametrosVariables.Clear();
//        NombreParametrosVariables.Add(_T("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=-1.0;
//        float x[2];
//        x[0]=1.0;x[1]=1.0;
        llenarVectores();
  }
/**
 * crea la función que compara x[0] con los demás valores x[i].
 *
 * \param o determina el sentido del ranking
 * ,es decir, si la comparación es ascendente o descendente
 *
 * si "orden">=0 y=(x[0])/sum(x))
 *
 * si "orden"<0 y=1-(x[0])/sum(x))
 */
	Ranking(int ord,float o)
	{
		Identificador=ID_RANKING;
		Tipo=wxT("Ranking");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("orden"));
        NombreParametrosVariables.Clear();
//        NombreParametrosVariables.Add(_T("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=o;
		llenarVectores();
	}
	~Ranking()
	{
		delete[] Crecer;
	}
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);
  void cambiarParametroFijo(int j, float p);
  void llenarVectores();
};

/**
 * Implementa la función
 */
class RankingOWA:public Funcion
{
public:
/**
 * crea la función que compara x[0] con los demás valores x[i].
 * el parámetro "orden" determina si la comparación es ascendente o descendente
 * si "orden">=0 y=(x[0])/sum(x))
 *
 * si "orden"<0 y=1-(x[0])/sum(x))
 *
 */
	RankingOWA()
	{
		Identificador=ID_RANKING_OWA;
		Tipo=wxT("Ranking OWA");
		Orden=2;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("orden"));
        NombreParametrosFijos.Add(wxT("alfa"));
        NombreParametrosFijos.Add(wxT("beta"));
        NombreParametrosVariables.Clear();
//        NombreParametrosVariables.Add(_T("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=-1.0;
        ParametrosFijos[1]=0.25;
        ParametrosFijos[2]=1.25;
//        float x[2];
//        x[0]=1.0;x[1]=1.0;
        llenarVectores();
  }
/**
 * crea la función que compara x[0] con los demás valores x[i].
 *
 * \param o determina el sentido del ranking
 * ,es decir, si la comparación es ascendente o descendente
 *
 * si "orden">=0 y=(x[0])/sum(x))
 *
 * si "orden"<0 y=1-(x[0])/sum(x))
 */
	RankingOWA(int ord,float o)
	{
		Identificador=ID_RANKING_OWA;
		Tipo=wxT("Ranking OWA");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("orden"));
        NombreParametrosFijos.Add(wxT("alfa"));
        NombreParametrosFijos.Add(wxT("beta"));
        NombreParametrosVariables.Clear();
//        NombreParametrosVariables.Add(_T("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=-1.0;
        ParametrosFijos[1]=0.25;
        ParametrosFijos[2]=1.25;
		llenarVectores();
	}
	~RankingOWA()
	{
		delete[] Crecer;
	}
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);
  void cambiarParametroFijo(int j, float p);
  void llenarVectores();
};

/**
 * Implementa la función
 */
class OWAfaulhaber:public Funcion
{
public:
/**
 * crea la función de agregación OWA basada en la fórmula de Faulhaber
 *
 */
	OWAfaulhaber()
	{
		Identificador=ID_OWA_FAULHABER;
		Tipo=wxT("OWA Faulhaber");
		Orden=2;
    ParametrosVariables= new float*[Orden];
    NombreParametrosFijos.Clear();
    NombreParametrosFijos.Add(wxT("orness"));
    NombreParametrosFijos.Add(wxT("beta"));
    NombreParametrosVariables.Clear();
    crearMatrices();
    Crecer=new int[Orden];
    ParametrosFijos[0]=0.5;
    ParametrosFijos[2]=1.5;
    llenarVectores();
  }
/**
 * crea la función de agregación OWA basada en la fórmula de Faulhaber
 */
	OWAfaulhaber(int ord,float o)
	{
		Identificador=ID_OWA_FAULHABER;
		Tipo=wxT("OWA Faulhaber");
		Orden=ord;
    ParametrosVariables= new float*[Orden];
    NombreParametrosFijos.Clear();
    NombreParametrosFijos.Add(wxT("orness"));
    NombreParametrosFijos.Add(wxT("beta"));
    NombreParametrosVariables.Clear();
    crearMatrices();
    Crecer=new int[Orden];
    ParametrosFijos[0]=0.5;
    ParametrosFijos[2]=1.5;
		llenarVectores();
	}
	~OWAfaulhaber()
	{
		delete[] Crecer;
	}
	float directa(float *x);
	float *pesos(float *x);
	float faux(float x, float beta);
	wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);
  void cambiarParametroFijo(int j, float p);
  void llenarVectores();
};

/**
 * Implementa la función a0*x[0]*a1*x[1]*...an*x[n]+Offset
 * x[i] debe ser mayor o igual que cero
 */
class Producto:public Funcion
{
public:
/**
 * crea la función x[0]*x[1]
 */
	Producto()
	{
		Identificador=ID_PRODUCTO;
		Tipo=wxT("Producto");
		Orden=2;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("a[0]"));
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=0.0;
        float x[2];
        x[0]=1.0;x[1]=1.0;
        llenarVectores(x,2);
	}
/**
 * Combinacion Lineal genérica a0*x[0]+a1*x[1]+...an*x[n]+Offset
 * \param x vector con los coeficientes a0, a1, ...an
 * \param ord número de variables x[0], x[1], ...x[n]  (n=ord-1)
 * \param off Offset de la combinación Lineal
 */
	Producto(float *x,int ord,float off=0.0)
	{
		Identificador=ID_PRODUCTO;
		Tipo=wxT("Producto");
		Orden=ord;
        ParametrosVariables= new float*[Orden];
        NombreParametrosFijos.Clear();
        NombreParametrosFijos.Add(wxT("a[0]"));
        NombreParametrosVariables.Clear();
        NombreParametrosVariables.Add(wxT("a"));
        crearMatrices();
        Crecer=new int[Orden];
        ParametrosFijos[0]=off;
		llenarVectores(x,ord);
	}
	~Producto()
	{
		delete[] Crecer;
	}
  void cambiarParametroVariables(int i,int, float p)
  {
    coeficiente(p,i);
  }
	void llenarVectores(float *x, int ord);
	float coeficiente(int i){return ParametrosVariables[i][0];}
	void coeficiente(float x, int i)
	{
		if(i<0){i=0;}
		if(i>=Orden){i=Orden-1;}
		ParametrosVariables[i][0]=x;
		if(ParametrosVariables[i][0]==0)
		{
			ParametrosVariables[i][0]=0.0001;
		}
		if(ParametrosVariables[i][0]>0)
		{
			Crecer[i]=1;
		}else
		{
			Crecer[i]=-1;
		}

	}
	float directa(float *x);
   wxString descripcion();
  wxString descripcionLatex();
	float inversa(float y, float *x, int k);

};


//
///*
//class Valor:public Funcion
//{
//public:
//	Valor()
//	{
//		Identificador=7;
//		Tipo="Valor";
//		Orden=1;
//		Parametro=1.0;
//		Exponente1=1.0/3.0;
//      Exponente2=2.0/3.0;
//		Crecer=new int[Orden];
//		llenarVectores(Orden);
//	}
//	~Valor()
//
//	{
//		delete[] Crecer;

//	}
//	void llenarVectores( int ord);
//	float directa(float *x);
//	float inversa(float y, float *x, int k);
//
//	float Parametro;
//	float Exponente1,Exponente2;
//protected:
//
//};
//*/
///*
//class Valor2:public Funcion
//{
//public:
//	Valor2()
//	{
//		Identificador=15;
//		Tipo="Valor2";
//		Orden=2;
//		Parametro=0.5;
//		Exponente1=1.0/3.0;
//		Exponente2=2.0/3.0;
//		Crecer=new int[Orden];
//
//		llenarVectores(Orden);
//	}
//	~Valor2()
//	{
//		delete[] Crecer;
//	}
//	void llenarVectores( int ord);
//
//	float directa(float *x);
//	float inversa(float y, float *x, int k);
//
//	float Parametro;
//	float Exponente1,Exponente2;
//protected:
//
//};
//*/
///*
//class Cash:public Funcion
//{
//public:
//	Cash(int ord)
//	{
//		Identificador=10;
//		Tipo="Cash";
//		Orden=ord;
//		Crecer=new int[Orden];
//		llenarVectores(ord);
//	}
//	~Cash()
//	{
//		delete[] Crecer;
//	}
//
//	void llenarVectores( int ord);
//	float directa(float *x);
//	float inversa(float y, float *x, int k);
//
//protected:
//
//};
//*/
//
////////////////
///*
//
//class Logaritmica:public Funcion
//
//{
//public:
//	Logaritmica(int ord=2)
//	{
//		Identificador=6;

//		Tipo="Logarítmica";
//
//		Orden=ord;
//		Crecer=new int[Orden];
//		llenarVectores(ord);
//	}
//	~Logaritmica()
//	{
//		delete[] Crecer;
//
//	}
//
//	void llenarVectores( int ord);
//	float directa(float *x);
//	float inversa(float y, float *x, int k);
//protected:

//};
//*/
//////////////////////////////////////////////////////////////////////////
//////////////////////////////       curvas         //////////////////////
//////////////////////////////////////////////////////////////////////////
///*
//class Curva
//{
//public:
//	Curva()
//	{
//		MinX=-100000.0;
//		MaxX=100000.0;
//	}
//	~Curva()
//	{
//		delete [] PuntosCriticos;
//	}
//	wxString tipo(){return Tipo;}
//	float minX(){return MinX;}
//	void minX(float m){MinX=m;}
//	float maxX(){return MaxX;}
//	void maxX(float m){MaxX=m;}
//	float minY();
//	float maxY();
//	int numeroPuntosCriticos(){return NumeroPuntosCriticos;}
//	float puntoCritico(int i)
//	{
//		if(i<0){i=0;}
//		if(i>=NumeroPuntosCriticos){i=NumeroPuntosCriticos-1;}
//		return PuntosCriticos[i];
//	}
//	virtual float directa(float x)=0;
//	void directaDifusa(NumeroDifuso *Y, NumeroDifuso *X);
//
//	BOOL operator==(Curva& other);
//	void operator=(Curva& other);
//
////	virtual void write(ofpstream &str);
////	virtual void read(ifpstream &str);
//
//protected:
//	wxString Tipo;
//	float *PuntosCriticos;
//	int NumeroPuntosCriticos;
//	float MinX,MaxX;
//};

//*/
///*
//class TrazosRectosContinuos:public Curva
//{
//public:
//	TrazosRectosContinuos(float *pc,float *pend, float b0, int npc);
//	TrazosRectosContinuos();
//	~TrazosRectosContinuos()
//	{
//		delete[] m;
//		delete[] b;
//		delete[] PuntosDeCorte;
//	}
//	void llenarPuntosCriticos();
//	void llenarTerminosIndependientes();
//	float directa(float x);
//
//	BOOL operator==(TrazosRectosContinuos& other);
//	void operator=(TrazosRectosContinuos& other);
//
////	void write(ofpstream &str);
////	void read(ifpstream &str);
//
//	float *m;
//	float *b;  // y=mx+b
//	float *PuntosDeCorte;
//	int NumeroPuntosDeCorte;
//};
//*/
//
//

#endif
