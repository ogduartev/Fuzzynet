/***************************************************************************
                          fuzzfunc.cpp  -  description
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

#include "fuzzfunc.h"

#include <stdio.h>

/**
 * Calcula la extensión directa de funcionDirecta
 * \param Y apuntador al número difuso en el que se almacena el resultado
 * \param X vector de apuntadores que contiene las entradas a la función
 * \see funcionDirecta
 */
void Funcion::directaDifusa(NumeroDifuso *Y, NumeroDifuso **X)
{
  float *argumentoL;
	float *argumentoR;
	argumentoL=new float[Orden];
	argumentoR=new float[Orden];
	float *L;
	float *R;
  int i,tam=2;
  for(i=0;i<Orden;i++)
  {
    if(X[i]->Tamano > tam){tam=X[i]->Tamano;}
  }
  Y->tamano(tam);
	L=new float[Y->Tamano];
	R=new float[Y->Tamano];
//	int i;
	for(i=0;i<Y->Tamano;i++)
	{
		float alfa;
		alfa=Y->intervalo()*i;
		int j;
		for(j=0;j<Orden;j++)
		{
			argumentoL[j]=X[j]->d(alfa,Crecer[j]);
			argumentoR[j]=X[j]->d(alfa,-Crecer[j]);
		}
		L[i]=directa(argumentoL);
		R[i]=directa(argumentoR);
	}
	int N;
	N=Y->Tamano;
	Y->nuevo(L,R,N);
	delete[] L;
	delete[] R;
	delete[] argumentoL;
	delete[] argumentoR;

}

void Funcion::inversaDifusa(NumeroDifuso *Y, NumeroDifuso **X, int k, float r)
{
	FlagUmbral=0;
	if(r<0){r=0;}
	if(r>1){r=1;}
	if(k<0){k=0;}
	if(k>Orden){k=Orden;}
	float *argumentoL;
	float *argumentoR;
	argumentoL=new float[Orden];
	argumentoR=new float[Orden];

	int N;
	N=Y->Tamano;

  int TamanoK=X[k]->Tamano;

	float *L;
	float *R;
	L=new float[N];
	R=new float[N];

	int i;

	NumeroDifuso *YP;
  YP=new NumeroDifuso();
  YP->copiar(Y);

	////////////// PASO 1

	i=N-1;
	float alfa;
	alfa=1.0;
	int j;
	for(j=0;j<Orden;j++)
	{
		float temp1,temp2;
		temp1=X[j]->d(alfa,Crecer[j]*Crecer[k]);
		temp2=X[j]->d(alfa,-Crecer[j]*Crecer[k]);

		argumentoL[j]=temp2+r*(temp1-temp2);
		argumentoR[j]=temp1+r*(temp2-temp1);
	}

	L[i]=inversa(YP->d(alfa,Crecer[k]),argumentoL,k);
	R[i]=inversa(YP->d(alfa,-Crecer[k]),argumentoR,k);


	while(L[i]>R[i])
	{
		FlagUmbral=1;
		float ZERO=0.001;
		float FACTOR=0.01;
		YP->L[i]=YP->L[i]-((YP->R[i]-YP->L[i])+ZERO)*FACTOR;
		YP->R[i]=YP->R[i]+((YP->R[i]-YP->L[i])+ZERO)*FACTOR;
		L[i]=inversa(YP->d(alfa,Crecer[k]),argumentoL,k);
		R[i]=inversa(YP->d(alfa,-Crecer[k]),argumentoR,k);
	};

	///////////// FIN PASO 1

	///////////// ITERACION PASOS 2,3,4

	for (i=N-2;i>=0;i--)
	{

		//////////// PASO 2

		alfa=Y->intervalo()*i;
		if(YP->L[i]>YP->L[i+1])
		{



			FlagUmbral=1;
			YP->L[i]=YP->L[i+1];
		}
		if(YP->R[i]<YP->R[i+1])
		{
			FlagUmbral=1;
			YP->R[i]=YP->R[i+1];
		}

		////////////////// PASO 3

		for(j=0;j<Orden;j++)
		{
			float temp1,temp2;

			temp1=X[j]->d(alfa,Crecer[j]*Crecer[k]);
			temp2=X[j]->d(alfa,-Crecer[j]*Crecer[k]);

			argumentoL[j]=temp2+r*(temp1-temp2);
			argumentoR[j]=temp1+r*(temp2-temp1);
		}
		L[i]=inversa(YP->d(alfa,Crecer[k]),argumentoL,k);
		if(L[i]>L[i+1])
		{
			L[i]=L[i+1];
			for(j=0;j<Orden;j++)
			{
				float temp1,temp2;

				if(j!=k)
				{
					temp1=X[j]->d(alfa,Crecer[j]*Crecer[k]);
					temp2=X[j]->d(alfa,-Crecer[j]*Crecer[k]);

					argumentoL[j]=temp2+r*(temp1-temp2);
				}else
				{
					temp1=L[i+1];
					argumentoL[j]=temp1;
				}
			}
			float yp=directa(argumentoL);
			if(Crecer[k]==1)
			{
				FlagUmbral=1;
				YP->L[i]=yp;
			}else
			{
				FlagUmbral=1;
				YP->R[i]=yp;
			}

		}

		//////////////////////// PASO 4

		for(j=0;j<Orden;j++)
		{
			float temp1,temp2;

			temp1=X[j]->d(alfa,Crecer[j]*Crecer[k]);
			temp2=X[j]->d(alfa,-Crecer[j]*Crecer[k]);

			argumentoL[j]=temp2+r*(temp1-temp2);
			argumentoR[j]=temp1+r*(temp2-temp1);
		}
		R[i]=inversa(YP->d(alfa,-Crecer[k]),argumentoR,k);
		if(R[i]<R[i+1])
		{

			R[i]=R[i+1];
			for(j=0;j<Orden;j++)
			{
				float temp1,temp2;

				if(j!=k)
				{
					temp1=X[j]->d(alfa,Crecer[j]*Crecer[k]);
					temp2=X[j]->d(alfa,-Crecer[j]*Crecer[k]);

					argumentoR[j]=temp1+r*(temp2-temp1);
				}else
				{
					temp2=R[i+1];
					argumentoR[j]=temp2;
				}
			}
			float yp=directa(argumentoR);
			if(Crecer[k]==1)
			{
				FlagUmbral=1;
				YP->R[i]=yp;
			}else
			{
				FlagUmbral=1;
				YP->L[i]=yp;
			}
		}
	}

	X[k]->nuevo(L,R,N);

  X[k]->tamano(TamanoK);

	for(i=0;i<N;i++)
	{
		L[i]=YP->L[i];
		R[i]=YP->R[i];
	}
	Y->nuevo(L,R,N);
	delete[] L;
	delete[] R;
	delete[] argumentoL;
	delete[] argumentoR;
}

/**
 * Calcula la medida de la existencia de la extensión inversa de la función
 * \param Y es un apuntador a la salida de la función
 * \param X es el vector de apuntadores de las entradas
 * \param k es el índice de la entrada que se desea calcula con la inversa:
 * \return El valor de la medida de la existencia de la extensión inversa

 * de la función, un valor entre 0 y 1.
 */
float Funcion::umbral(NumeroDifuso *Y, NumeroDifuso **X, int k)
{
	NumeroDifuso *YP;
	YP=new NumeroDifuso();
	YP->copiar(Y);
	FlagUmbral=0;
	float u;
	for(u=0.0;u<=1.0001;u=u+0.01)
	{
		YP->copiar(Y);
		inversaDifusa(YP,X,k,u);
		if(FlagUmbral!=0)
		{
			return u;
		}
	}
	delete YP;
	return 1.0;
}

/**
 * Esta funcion cambia el parámetro fijo j
 * al valor p. Verifica que  j esté dentro de los márgenes
 * adecuados. No se modifica el vector Crecer, por lo tanto, si esto es
 * necesario hay que redefinir la función en la clase heredera
 */
void Funcion::cambiarParametroFijo(int j, float p)
{
  if(j<0 || j>NombreParametrosFijos.GetCount()){return;}
  ParametrosFijos[j]=p;
}

/**
 * Esta funcion cambia el parámetro variable j de la variable i
 * al valor p. Verifica que i y j estén dentro de los márgenes
 * adecuados. No se modifica el vector Crecer, por lo tanto, si esto es
 * necesario hay que redefinir la función en la clase heredera
 */
void Funcion::cambiarParametroVariables(int i,int j, float p)
{
  if(i<0 || i>Orden-1){return;}
  if(j<0 || j>NombreParametrosVariables.GetCount()){return;}
  ParametrosVariables[i][j]=p;
}

void Funcion::crearMatrices()
{
  if (ParametrosVariables!=NULL)
  {
    delete[] ParametrosVariables;
  }
  if (ParametrosFijos!=NULL)
  {
    delete[] ParametrosFijos;
  }
  ParametrosFijos=new float[NombreParametrosFijos.GetCount()];
  ParametrosVariables=new float*[Orden];
  int i,tam;
  tam=Orden;
  for(i=0;i<tam;i++)
  {
    ParametrosVariables[i]=new float[NombreParametrosVariables.GetCount()];
  }
}

/**
 * Compara dos funciones. Compara Orden, FlagUmbral, Tipo y vector Crecer
 */
BOOL Funcion::operator==(Funcion& other)
{
	int i,tam,res;

	res=((Orden==other.Orden)&(FlagUmbral==other.FlagUmbral)&(Tipo==other.Tipo)
           &(NombreParametrosFijos==other.NombreParametrosFijos)
           &(NombreParametrosVariables==other.NombreParametrosVariables) );
	if(res==1)
	{
		for(i=0;i<Orden;i++)
		{
			res=res&(Crecer[i]==other.Crecer[i]);
		}
	}
  if(res==1)
  {
    tam=NombreParametrosFijos.GetCount();
	for(i=0;i<tam;i++)
	{
		 res=res&(ParametrosFijos[i]==other.ParametrosFijos[i]);
	}
  }
  if(res==1)
  {
    tam=Orden;
	for(i=0;i<tam;i++)
	{
       int j,tam2;
       tam2=NombreParametrosVariables.GetCount();
    	for(j=0;j<tam2;j++)
    	{
    		res=res&(ParametrosVariables[i][j]==other.ParametrosVariables[i][j]);
    	}
	}
  }

	return res;
}




/**
 * Copia una función. Copia Orden,FlagUmbral, Tipo y vector Crecer
 */

void Funcion::operator=(Funcion& other)
{
	int i,tam;

	Orden=other.Orden;
	FlagUmbral=other.FlagUmbral;
	Tipo=other.Tipo;
	delete [] Crecer;
	Crecer=new int[Orden];
	for(i=0;i<Orden;i++)
	{
		Crecer[i]=other.Crecer[i];
	}
  ParametrosFijos=other.ParametrosFijos;
  ParametrosVariables=other.ParametrosVariables;
  crearMatrices();
    tam=NombreParametrosFijos.GetCount();
	for(i=0;i<tam;i++)
	{
		 ParametrosFijos[i]=other.ParametrosFijos[i];
	}
    tam=Orden;
	for(i=0;i<tam;i++)
	{
       int j,tam2;
       tam2=NombreParametrosVariables.GetCount();
    	for(j=0;j<tam2;j++)
    	{
    		ParametrosVariables[i][j]=other.ParametrosVariables[i][j];
    	}
	}
}

void Funcion::adicionarOrden(int loc)
{
  if(loc>Orden || loc < 0)
 {
    loc=Orden;
 }
	int ord=Orden+1;
	float **Coef;Coef=new float*[ord];
	int i,flag=0;
	for(i=0;i<ord;i++)
	{
    if(i==loc)
    {
      flag=1;
      int j,tam2;
      tam2=NombreParametrosVariables.GetCount();
      Coef[i]=new float[tam2];
      for(j=0;j<tam2;j++)
      {
        Coef[i][j]=0.0;
      }
    }else if(flag==0)
    {
		  Coef[i]=ParametrosVariables[i];
    }else
    {
		  Coef[i]=ParametrosVariables[i-1];
    }
	}
  Orden++;
  delete ParametrosVariables;
  ParametrosVariables=Coef;
  Coef=NULL;
}

void Funcion::eliminarOrden(int loc)
{
  if(loc>(Orden-1) || loc < 0)
 {
    loc=Orden-1;
 }
	int ord=Orden-1;
	float **Coef;Coef=new float*[ord];
	int i,flag=0;
	for(i=0;i<ord;i++)
	{
    if(i==loc || flag==1)
    {
      flag=1;
		  Coef[i]=ParametrosVariables[i+1];
    }else
    {
		  Coef[i]=ParametrosVariables[i];
    }
	}
  Orden--;
  delete ParametrosVariables;
  ParametrosVariables=Coef;
  Coef=NULL;
}

void Funcion::write(Mi_ofpstream &str)
{
	int i,tam;


	str << Identificador;
	str << Orden;
	str << Tipo;
	str << FlagUmbral;
    tam=Orden;
	for(i=0;i<tam;i++)
	{
		str << Crecer[i];
	}
    tam=NombreParametrosFijos.GetCount();
    str << tam;
	for(i=0;i<tam;i++)
	{
		str << NombreParametrosFijos.Item(i);
	}
    tam=NombreParametrosVariables.GetCount();
    str << tam;
	for(i=0;i<tam;i++)
	{
		str << NombreParametrosVariables.Item(i);
	}
    tam=NombreParametrosFijos.GetCount();
	for(i=0;i<tam;i++)

	{

		str << ParametrosFijos[i];
	}

    tam=Orden;
	for(i=0;i<tam;i++)
	{
       int j,tam2;
       tam2=NombreParametrosVariables.GetCount();
    	for(j=0;j<tam2;j++)
    	{
    		str << ParametrosVariables[i][j];
    	}
	}
}

Funcion* Funcion::read(Mi_ifpstream &str)
{
	int i,tam,ord;

	str >> Identificador;
  str >> ord;
  Funcion *F;
  switch(Identificador)
  {
    case ID_COMBINA_LINEAL:
          F=new CombinacionLineal();
          break;
    case ID_SUPREMO:

          F=new Supremo(ord);
          break;
    case ID_INFIMO:
          F=new Infimo(ord);
          break;
    case ID_POLINOMIO:
          F=new Polinomio();
          break;
    case ID_COMBINA_LINEAL_ACOTADA:
          F=new CombinacionLinealAcotada();
          break;
    case ID_PROD_SUMA:
          F=new ProdSuma();
          break;
    case ID_SUMA_PROD:
          F=new SumaProd();
          break;
    case ID_RANKING:
          F=new Ranking();
          break;
    case ID_RANKING_OWA:
          F=new RankingOWA();
          break;
    case ID_OWA_FAULHABER:
          F=new OWAfaulhaber();
          break;
    case ID_PRODUCTO:
          F=new Producto();
          break;
    default:
          F=new CombinacionLineal();
          break;
  }
  F->Identificador=Identificador;
  F->Orden=ord;

  wxString cad;
  str >> cad;  // No es necesario ler el Tipo, se crea en el constructor. se mantiene en write para legibilidad
//  str >> F->Tipo;
  str >> F->FlagUmbral;
  delete [] F->Crecer;
  F->Crecer=new int[F->Orden];
  for(i=0;i<F->Orden;i++)
  {
    str >> F->Crecer[i];
  }

    F->NombreParametrosFijos.Empty();
    str >> tam;
	for(i=0;i<tam;i++)
	{
		str >> cad;
       F->NombreParametrosFijos.Add(cad);
	}
    F->NombreParametrosVariables.Empty();
    str >> tam;
	for(i=0;i<tam;i++)
	{
		str >> cad;
       F->NombreParametrosVariables.Add(cad);
	}
   F->crearMatrices();
    tam=F->NombreParametrosFijos.GetCount();
	for(i=0;i<tam;i++)
	{
		str >> F->ParametrosFijos[i];
	}
    tam=F->Orden;
	for(i=0;i<tam;i++)
	{
       int j,tam2;
       tam2=F->NombreParametrosVariables.GetCount();
    	for(j=0;j<tam2;j++)
    	{
    		str >> F->ParametrosVariables[i][j];
    	}
	}

  return F;
}

///////////////////////////////////////////////////////////////

void CombinacionLineal::llenarVectores(float *x, int ord)
{
	Orden=ord;

	crearMatrices();

	Crecer=new int[Orden];
	int i;
	for(i=0;i<Orden;i++)
	{
		ParametrosVariables[i][0]=x[i];
		if(ParametrosVariables[i][0]==0.0)
		{
			ParametrosVariables[i][0]=0.0001;
		}
		if(ParametrosVariables[i][0]>0.0)
		{
			Crecer[i]=1;
		}else
		{
			Crecer[i]=-1;
		}
	}
}

float CombinacionLineal::directa(float *x)
{
	int i;
	float y=ParametrosFijos[0];
	for(i=0;i<Orden;i++)
	{
		y=y+ParametrosVariables[i][0]*x[i];
	}
	return y;
}

wxString CombinacionLineal::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Combinación Lineal' ");
  Desc << wxT("efectúa la Combinación Lineal de los argumentos (un promedio ponderado); incluye un valor constante. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("f(x1,x2,...,xn)=a[0] + a[1]*x1 + a[2]*x2 + ... + a[n]*xn");
  return Desc;
}

wxString CombinacionLineal::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Combinación Lineal} ");
  Desc << wxT("efectúa la Combinación Lineal de los argumentos (un promedio ponderado); incluye un valor constante. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=a_0 + \\sum_{i=1}^n{a_1x_i}");
  Desc << wxT("\\]\n");
  return Desc;
}

float CombinacionLineal::inversa(float y, float *x, int k)
{
	if(ParametrosVariables[k][0]==0)
	{
		return 0.0;
	}
	int i;
	float xk=y-ParametrosFijos[0];
	for(i=0;i<Orden;i++)
	{
		if(i!=k)
		{
			xk=xk-ParametrosVariables[i][0]*x[i];
		}
	}
	xk=xk/ParametrosVariables[k][0];
	return xk;
}

/////////////////////////////////////////////////////////////////
void Supremo::llenarVectores( int ord)
{
	Orden=ord;
	delete[] Crecer;
	Crecer=new int[Orden];

	int i;
	for(i=0;i<Orden;i++)
	{
		Crecer[i]=1;
	}
}

float Supremo::directa(float *x)
{
	int i;
	float y=-1000000.0;
	for(i=0;i<Orden;i++)
	{
		if(x[i]>y)
		{
			y=x[i];
		}
	}
	return y;
}

wxString Supremo::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Supremo' ");
  Desc << wxT("calcula el máximo valor de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("f(x1,x2,...,xn)=max(x1,x2,...,xn)");
  return Desc;
}

wxString Supremo::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Supremo} ");
  Desc << wxT("calcula el máximo valor de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=\\max (x_1,x_2,...,x_n)");
  Desc << wxT("\\]\n");
  return Desc;
}

float Supremo::inversa(float y, float *x, int k)
{
	float xk;
	xk=x[k];
	if(xk){}  // para eliminar warning
	xk=y;
	return xk;
}


/////////////////////////////////////////////////////////////////

void Infimo::llenarVectores( int ord)
{
	Orden=ord;
	delete[] Crecer;
	Crecer=new int[Orden];
	int i;


	for(i=0;i<Orden;i++)
	{
		Crecer[i]=1;
	}
}

float Infimo::directa(float *x)
{
	int i;
	float y=1000000.0;
	for(i=0;i<Orden;i++)
	{
		if(x[i]<y)
		{
			y=x[i];
		}
	}
	return y;
}

wxString Infimo::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Ínfimo' ");
  Desc << wxT("calcula el mínimo valor de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("f(x1,x2,...,xn)=min(x1,x2,...,xn)");
  return Desc;
}

wxString Infimo::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Ínfimo} ");
  Desc << wxT("calcula el mínimo valor de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=\\min(x_1,x_2,...,x_n)");
  Desc << wxT("\\]\n");
  return Desc;
}

float Infimo::inversa(float y, float *x, int k)
{
	float xk;
	xk=x[k];
	if(xk){}  // para eliminar warning
	xk=y;
	return xk;
}

/////////////////////////////////////////////////////////////////

void Polinomio::llenarVectores(float *x, float *e, int ord)
{
	Orden=ord;
  crearMatrices();
	delete[] Crecer;
	Crecer=new int[Orden];
	int i;

	for(i=0;i<Orden;i++)
	{
		ParametrosVariables[i][0]=x[i];
		if(ParametrosVariables[i][0]==0.0)
		{
			ParametrosVariables[i][0]=0.0001;
		}
		ParametrosVariables[i][1]=e[i];
		if(ParametrosVariables[i][1]==0.0)
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

}

float Polinomio::directa(float *x)
{
	int i;
	float y=0;
	for(i=0;i<Orden;i++)
	{
		y=y+ParametrosVariables[i][0]*pow(x[i],ParametrosVariables[i][1]);
	}
	return y;
}

wxString Polinomio::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Polinomio' ");
  Desc << wxT("efectúa la Combinación Lineal de monomios de los argumentos. ");
  Desc << wxT("Sólo es válida para valores no negativos de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("f(x1,x2,...,xn)=a[1]*x1^b[1] + a[2]*x2^b[2] + ... + a[n]*xn^b[n]");
  return Desc;
}

wxString Polinomio::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Polinomio} ");
  Desc << wxT("efectúa la Combinación Lineal de monomios de los argumentos. ");
  Desc << wxT("Sólo es válida para valores no negativos de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=\\sum_{i=1}^n{a_ix_i^{b_i}}");
  Desc << wxT("\\]\n");
  return Desc;
}

float Polinomio::inversa(float y, float *x, int k)
{
	if(ParametrosVariables[k][0]==0.0)
	{
		return 0.0;
	}
	int i;
	float xk=y;
	for(i=0;i<Orden;i++)
	{
		if(i!=k)
		{
			xk=xk-ParametrosVariables[i][0]*pow(x[i],ParametrosVariables[i][1]);
		}
	}
	xk=xk/ParametrosVariables[k][0];
	xk=pow(xk,(1/ParametrosVariables[k][1]));
	return xk;
}



/////////////////////////////////////////////////////////////////

void CombinacionLinealAcotada::llenarVectores(float *x, int ord)
{
	Orden=ord;

  crearMatrices();

  delete[] Crecer;
	Crecer=new int[Orden];
	int i;
	for(i=0;i<Orden;i++)
	{
		ParametrosVariables[i][0]=x[i];
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
}

float CombinacionLinealAcotada::directa(float *x)
{
	int i;
	float y=ParametrosFijos[0];
	for(i=0;i<Orden;i++)
	{
		y=y+ParametrosVariables[i][0]*x[i];
	}
	if(y>ParametrosFijos[2])
	{
		y=ParametrosFijos[2];
	}
	if(y<ParametrosFijos[1])
	{
   	y=ParametrosFijos[1];
	}
	return y;
}

wxString CombinacionLinealAcotada::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Combinación Lineal Acotada' ");
  Desc << wxT("efectúa la Combinación Lineal de los argumentos (propedio ponderado); incluye un Valor constante. ");
  Desc << wxT("El resultado se acota entre CotaInferior y CotaSuperior. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("y(x1,x2,...,xn)=a[0] + a[1]*x1 + a[2]*x2 + ... + a[n]*xn\n");
  Desc << wxT("z(x1,x2,...,xn)=max(y(x1,x2,...,xn), CotaInferior)\n");
  Desc << wxT("f(x1,x2,...,xn)=min(z(x1,x2,...,xn), CotaSuperior)\n");
  return Desc;
}

wxString CombinacionLinealAcotada::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Combinación Lineal Acotada} ");
  Desc << wxT("efectúa la Combinación Lineal de los argumentos (propedio ponderado); incluye un Valor constante. ");
  Desc << wxT("El resultado se acota entre CotaInferior y CotaSuperior. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("\\[");
  Desc << wxT("y=a_0 + \\sum_{i=1}^n{a_ix_i}");
  Desc << wxT("\\]\n");
  Desc << wxT("\\[");
  Desc << wxT("z=\\max(y, CotaInferior)");
  Desc << wxT("\\]\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=\\min(z, CotaSuperior)");
  Desc << wxT("\\]\n");
  return Desc;
}


float CombinacionLinealAcotada::inversa(float y, float *x, int k)
{
	if(ParametrosVariables[k][0]==0)
	{
		return 0.0;
	}
	int i;
	float xk=y-ParametrosFijos[0];
	for(i=0;i<Orden;i++)
	{
		if(i!=k)
		{
			xk=xk-ParametrosVariables[i][0]*x[i];
		}
	}
	xk=xk/ParametrosVariables[k][0];
	return xk;
}



/////////////////////////////////////////////////////////////////

void ProdSuma::llenarVectores(float *x, int ord)
{
	Orden=ord;
  crearMatrices();
  delete[] Crecer;
	Crecer=new int[Orden];
	int i;
	for(i=0;i<Orden;i++)

	{
		ParametrosVariables[i][0]=x[i];
		if(ParametrosVariables[i][0]==0)
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
}

float ProdSuma::directa(float *x)
{

	int i;
	float y=0;
	for(i=1;i<Orden;i++)
	{
		y=y+ParametrosVariables[i][0]*x[i];
	}
  y=ParametrosVariables[0][0]*x[0]*y + ParametrosFijos[0];
	return y;
}

wxString ProdSuma::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Producto - Suma' ");
  Desc << wxT("multiplica el primer argumento por la Combinación Lineal de los restantes argumentos; incluye un Valor constante. ");
  Desc << wxT("Sólo es válida para valores no negativos de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("f(x1,x2,...,xn)=a[0] + a[1]*x1*(a[2]*x2 + a[3]*x3 +... + a[n]*xn)");
  return Desc;
}

wxString ProdSuma::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Producto - Suma} ");
  Desc << wxT("multiplica el primer argumento por la Combinación Lineal de los restantes argumentos; incluye un Valor constante. ");
  Desc << wxT("Sólo es válida para valores no negativos de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=a_0 + a_1x_1\\left(\\sum_{i=2}^n{a_ix_i}\\right)");
  Desc << wxT("\\]\n");
  return Desc;
}


float ProdSuma::inversa(float y, float *x, int k)
{
	if(ParametrosVariables[k][0]==0.0)
	{
		return 0.0;
	}
	int i;
	float xtemp=0;
  float xk;
	for(i=1;i<Orden;i++)
	{
		if(i!=k)

		{
			xtemp=xtemp+ParametrosVariables[i][0]*x[i];
		}
	}
  if (k==0)
  {
    xk=(y-ParametrosFijos[0])/(ParametrosVariables[0][0]*xtemp);
  }else
  {
    xk=((y-ParametrosFijos[0])/(ParametrosFijos[0]*x[0])-xtemp)/ParametrosVariables[k][0];
  }
	return xk;
}
//
/////////////////////////////////////////////////////////////////

void SumaProd::llenarVectores(float *x, int ord)
{
  if(ord%2!=0){Orden=ord-1;}else{Orden=ord;}
  crearMatrices();
	delete[] Crecer;
	Crecer=new int[Orden];
	int i;
	for(i=0;i<Orden;i++)
	{
		ParametrosVariables[i][0]=x[i];
		if(ParametrosVariables[i][0]==0)
		{
			ParametrosVariables[i][0]=0.0001;
		}
		if(ParametrosVariables[i][0]>0.0)
		{
			Crecer[i]=1;
		}else
    {
      ParametrosVariables[i][0]=-ParametrosVariables[i][0];
			Crecer[i]=1;
		}
	}
}

float SumaProd::directa(float *x)
{
	int i;
	float y=ParametrosFijos[0];
	for(i=0;i<Orden;i++)
	{
    if((i+1)<Orden)  // Son Parejas
    {
      y=y+ParametrosVariables[i][0]*x[i]*ParametrosVariables[i+1][0]*x[i+1];
      i++;
    }else
    {
      y=y+ParametrosVariables[i][0]*x[i];
      i++;
    }
	}
	return y;
}

wxString SumaProd::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Suma - Producto' ");
  Desc << wxT("efectua la Combinación Lineal del producto de parejas de argumentos; incluye un Valor constante. ");
  Desc << wxT("Sólo es válida para valores no negativos de los argumemntos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("f(x1,x2,...,xn)=a[0] + (a[1]*x1*a[2]*x2) + (a[3]*x3*a[4]*x4) + ... + (a[n-1]*xn-1*a[n]*xn)");
  return Desc;
}

wxString SumaProd::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Suma - Producto} ");
  Desc << wxT("efectua la Combinación Lineal del producto de parejas de argumentos; incluye un Valor constante. ");
  Desc << wxT("Sólo es válida para valores no negativos de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=a_0 + \\sum_{i=1}^{n/2}{a_ix_ia_{i+1}x_{i+1}}");
  Desc << wxT("\\]\n");
  return Desc;
}

float SumaProd::inversa(float y, float *x, int k)
{
	if(ParametrosVariables[k][0]==0)
	{
		return 0.0;
	}
	int i;
	float xtemp=0;
  float xk;
	for(i=0;i<Orden;i++)
	{
		if(i!=k && (i+1)!=k )
		{
      if((i+1)<Orden)  // Son Parejas
      {
		  	xtemp=xtemp+ParametrosVariables[i][0]*x[i]*ParametrosVariables[i+1][0]*x[i+1];
      }else
      {
		  	xtemp=xtemp+ParametrosVariables[i][0]*x[i];
      }
		}
    i++;
	}
  if (k%2==0)
  {
    if((i+1)<Orden)  // Son Parejas
    {
      xk=(y-xtemp-ParametrosFijos[0])/(ParametrosVariables[k][0]*ParametrosVariables[k+1][0]*x[k+1]);
    }else
    {
      xk=(y-xtemp-ParametrosFijos[0])/(ParametrosVariables[k][0]);
    }
  }else
  {
    xk=(y-xtemp-ParametrosFijos[0])/(ParametrosVariables[k][0]*ParametrosVariables[k-1][0]*x[k-1]);
  }
	return xk;

}

///////////////////////

float Ranking::directa(float *x)
{
  int i,tam;
  tam=Orden;
  int contador=0;
  for(i=1;i<tam;i++)
  {
    if(x[i]>x[0])
    {
      contador++;
    }
  }
  int posicion;
  posicion=Orden-contador;
  float rank;
  rank=((float)posicion-0.5)/(float)Orden;
  if(ParametrosFijos[0]<=0.0)
  {
    rank=1.0-rank;
  }
  rank=rank*2/Orden;
  return rank;
}

wxString Ranking::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Ranking' ");
  Desc << wxT("compara el valor del primer argumento respecto a los demás. ");
  Desc << wxT("La comparación puede ser ascendente o descendente. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("Si orden > 0 \n");
  Desc << wxT("    f(x1,x2,...,xn)=(Pos - 0.5)/n*2/n\n");
  Desc << wxT("    Pos = n - número de valores x2, x3, ... ,xn mayores que x1\n");
  Desc << wxT("Si orden < 0 \n");
  Desc << wxT("    f(x1,x2,...,xn)= (1 - (Pos - 0.5)/n)*2/n\n");
  Desc << wxT("    Pos = n - número de valores x2, x3, ... ,xn mayores que x1\n");
  Desc << wxT("El resultado está entre 1/(n*2) y (1 - 1/2n)*2/n \n");
  return Desc;
}

wxString Ranking::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Ranking} ");
  Desc << wxT("compara el valor del primer argumento respecto a los demás. ");
  Desc << wxT("La comparación puede ser ascendente o descendente. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("Si $orden > 0$ :\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=\\frac{Pos - 0.5}\\times\\frac{2}{n}{n}");
  Desc << wxT("\\]\n");
  Desc << wxT("\\[");
  Desc << wxT("Pos = n - \\text{n\\'umero de valores } x_2, x_3, \\cdots ,x_n \\text{ mayores que } x_1");
  Desc << wxT("\\]\n");
  Desc << wxT("Si $orden < 0$ :\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=(1 - \\frac{Pos - 0.5}{n}) \\times\\frac{2}{n}");
  Desc << wxT("\\]\n");
  Desc << wxT("\\[");
  Desc << wxT("Pos = n - \\text{n\\'umero de valores } x_2, x_3, \\cdots ,x_n \\text{ mayores que } x_1");
  Desc << wxT("\\]\n");
  Desc << wxT("El resultado está entre $\\frac{1}{n^2}$ y $(1 - \\frac{1}{n})2/n$ \n");
  return Desc;
}



/////
// OJO: no está definido!!!!
// con y se busca la posición en el vector, y se efectúa interpolación
// entre los datos que lo rodean...
/////

float Ranking::inversa(float y, float *x, int k)
{
  return -1;  // atención esta instrucción debe revisarse, sólo se ha incluido
               // para eliminar error en VisualC
}


//float Ranking::directa(float *x)
//{
//  float sum,y;
//  int i;
//  sum=0;
//  for(i=0;i<Orden;i++)
//  {
//    sum=sum+x[i];
//  }
//  if(sum==0.0)
//  {
//    y=1.0/(float)Orden;
//  }else
//  {
//    y=x[0]/sum;
//  }
//  if(ParametrosFijos[0]<=0.0)
//  {
//    y=1.0-y;
//  }
//  return y;
//}

//float Ranking::inversa(float y, float *x, int k)
//{
//  float res;
//  float yt;
//  if(ParametrosFijos[0]>0)
//  {
//    yt=y;
//  }else
//  {
//    yt=1.0-y;
//  }
//  ///////////////
//  if(k==0)
//  {
//    if(y==1.0)
//    {
//      res=1.0;
//    }else
//    {
//      int i;
//      float sum=0.0;
//      for(i=1;i<Orden;i++)
//      {
//        sum=sum+x[i];
//      }
//      res=yt*sum/(1.0-yt);
//    }
//  }
//  {
//    if(y==0.0)
//    {
//      res=0.5;
//    }else
//    {
//      int i;
//      float sum=0.0;
//      for(i=0;i<Orden;i++)
//      {
//        sum=sum+x[i];
//      }
//      sum=sum-x[k];
//      res=(x[0]+yt*sum)/yt;
//    }
//  }
//  return res;
//}

void Ranking::cambiarParametroFijo(int j, float p)
{
  if(j!=0){return;}
  ParametrosFijos[j]=p;
  llenarVectores();
}

void Ranking::llenarVectores()
{
  if (ParametrosFijos[0]>0.0)
  {
    Crecer[0]=1;
  }else
  {
    Crecer[0]=-1;
  }
  int i;
  for(i=1;i<Orden;i++)
  {
    if (ParametrosFijos[0]>0.0)
    {
      Crecer[i]=-1;
    }else
    {
      Crecer[i]=1;
    }
  }
}
///////////////////////////////////////////////////////////////
///////////////////////

float RankingOWA::directa(float *x)
{
  int i,tam;
  tam=Orden;
  int contador=0;
  for(i=1;i<tam;i++)
  {
    if(x[i]>x[0])
    {
      contador++;
    }
  }
  int posicion;
  posicion=contador;
  if(ParametrosFijos[0]<=0.0)
  {
    posicion = Orden-posicion-1;
  }

  float alfa,beta,fAlfa,gAlfa,M,DeltaTotal,Delta,n;
  bool flag=false;
  n=(float)Orden - 1;
  M=1.0/(n+1);
  DeltaTotal=1.0-M;

  alfa=ParametrosFijos[1];
  beta=ParametrosFijos[2];

  if(alfa > 0.5)
  {
  	flag=true;
    alfa=1.0-alfa;
  }
///// MAIN ////
  fAlfa=1.0 - pow((1.0 - 2*alfa),beta);

  gAlfa=2*alfa;

  Delta=fAlfa*DeltaTotal;
  float rank;

  if(posicion==0)
  {
    rank=1.0 - Delta;
  }else
  {
  	float K,b;
    K=-6 * (fAlfa-gAlfa)/(n*n - 1);
    b=fAlfa/(n+1) -K*(n+1)/2.0;
    rank = K*posicion + b;
  }

  return rank;
}

wxString RankingOWA::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'RankingOWA' ");
  Desc << wxT("compara el valor del primer argumento respecto a los demás. ");
  Desc << wxT("La comparación puede ser ascendente o descendente. ");
  Desc << wxT("El resultado es un peso calculado como el peso de un operador OWA");
  Desc << wxT("para un alfa y beta dados");
  return Desc;
}

wxString RankingOWA::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Ranking} ");
  Desc << wxT("compara el valor del primer argumento respecto a los demás. ");
  Desc << wxT("La comparación puede ser ascendente o descendente. ");
  Desc << wxT("El resultado es un peso calculado como el peso de un operador OWA");
  Desc << wxT("para un $\\alpha$ y $\\beta$ dados");
  return Desc;
}

/////
// OJO: no está definido!!!!
// con y se busca la posición en el vector, y se efectúa interpolación
// entre los datos que lo rodean...
/////

float RankingOWA::inversa(float y, float *x, int k)
{
  return -1;  // atención esta instrucción debe revisarse, sólo se ha incluido
               // para eliminar error en VisualC
}

void RankingOWA::cambiarParametroFijo(int j, float p)
{
  if(j >= NombreParametrosFijos.GetCount()){return;}
  ParametrosFijos[j]=p;
  llenarVectores();
}

void RankingOWA::llenarVectores()
{
  if (ParametrosFijos[0]>0.0)
  {
    Crecer[0]=1;
  }else
  {
    Crecer[0]=-1;
  }
  int i;
  for(i=1;i<Orden;i++)
  {
    if (ParametrosFijos[0]>0.0)
    {
      Crecer[i]=-1;
    }else
    {
      Crecer[i]=1;
    }
  }
}

///////////////////////////////////////////////////////////////
///////////////////////

float OWAfaulhaber::directa(float *x)
{
  float y=0;

  float *w = this->pesos(x);
  std::sort(x,x+Orden, std::greater<float>());

  for(int i=0;i<Orden;i++)
	{
	  y+=w[i]*x[i];
	}

	delete[] w;

  return y;
}

float *OWAfaulhaber::pesos(float *x)
{
  float *w;
  int n;
  float orness,alfa,beta,m,Delta,K,b,fa;

  n=Orden;
  orness = ParametrosFijos[0];
  beta   = ParametrosFijos[1];

  if(orness <= 0.5)
	{
		alfa = orness;
	}else
	{
		alfa = 1 - orness;
	}
	m=(float)(n-1);
	fa=this->faux(alfa,beta);
	Delta = fa*m/(float)n;
	K = 6.0*(fa - 2*alfa)/(m*m - 1.0);
	b = fa/(float)n - K*(float)n/2.0;

  w=new float[Orden];
  if(orness <=0.5)
	{
	  w[n-1]=1-Delta;
	  for(int i=1;i<n;i++)
		{
		  w[i-1]=K*i + b;
		}
	}else
	{
	  w[0]=1-Delta;
	  for(int i=1;i<n;i++)
		{
		  w[i]=K*(n-i) + b;
		}
	}
	return w;
}

float OWAfaulhaber::faux(float x, float beta)
{
  float f;
  if(beta<1.0){beta=1.0;}
  if(beta>1.5){beta=1.5;}
  f = 1.0 - pow(1 - 2*x, beta);
  return f;
}

wxString OWAfaulhaber::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'OWA Faulhaber' ");
  Desc << wxT("implementa el operador de agregación OWA basado en la fórmula de Faulhaber, para un beta dado. ");
  Desc << wxT("La agregación se controla con el parámetro orness que varía entre 0 y 1. ");
  Desc << wxT("Si orness es 0 el operador equivale al mínimo. ");
  Desc << wxT("Si orness es 0.5 el operador equivale al promedio simple. ");
  Desc << wxT("Si orness es 1 el operador equivale a máximo. ");
  Desc << wxT("Al incrementar el \\{orness} la agregación varía suavemente.");
  return Desc;
}

wxString OWAfaulhaber::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{OWA Faulhaber} ");
  Desc << wxT("implementa el operador de agregación OWA basado en la fórmula de Faulhaber, para un $\\beta$ dado. ");
  Desc << wxT("La agregación se controla con el parámetro \\emph{orness} que varía entre 0 y 1. ");
  Desc << wxT("Si \\emph{orness} es 0 el operador equivale a $\\min{}$. ");
  Desc << wxT("Si \\emph{orness} es 0.5 el operador equivale al promedio simple. ");
  Desc << wxT("Si \\emph{orness} es 1 el operador equivale a $\\max{}$. ");
  Desc << wxT("Al incrementar el \\{orness} la agregación varía suavemente.");
  return Desc;
}

/////
// OJO: no está definido!!!!
// con y se busca la posición en el vector, y se efectúa interpolación
// entre los datos que lo rodean...
/////

float OWAfaulhaber::inversa(float y, float *x, int k)
{
  return -1;  // atención esta instrucción debe revisarse, sólo se ha incluido
               // para eliminar error en VisualC
}

void OWAfaulhaber::cambiarParametroFijo(int j, float p)
{
  if(j >= NombreParametrosFijos.GetCount()){return;}
  if(j==0)
	{
	  if(p<0.0){p=0.0;}
	  if(p>1.0){p=1.0;}
	}
  if(j==1)
	{
	  if(p<1.0){p=1.0;}
	  if(p>1.5){p=1.5;}
	}
  ParametrosFijos[j]=p;
  llenarVectores();
}

void OWAfaulhaber::llenarVectores()
{
  int i;
  for(i=0;i<Orden;i++)
  {
    Crecer[i]=1;
  }
}


///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////

void Producto::llenarVectores(float *x, int ord)
{
	Orden=ord;

  crearMatrices();

	Crecer=new int[Orden];
	int i;
	for(i=0;i<Orden;i++)
	{

		ParametrosVariables[i][0]=x[i];
		if(ParametrosVariables[i][0]==0.0)
		{
			ParametrosVariables[i][0]=0.0001;
		}
		if(ParametrosVariables[i][0]>0.0)
		{
			Crecer[i]=1;
		}else
		{
			Crecer[i]=-1;
		}
	}
}

float Producto::directa(float *x)
{
	int i;
	float y=ParametrosFijos[0];
  float temp=1.0;
	for(i=0;i<Orden;i++)
	{
		temp=temp*ParametrosVariables[i][0]*x[i];
	}
	return y+temp;
}

wxString Producto::descripcion()
{
  wxString Desc=wxT("");
  Desc << wxT("La función 'Producto' ");
  Desc << wxT("efectúa el Producto de los argumentos; incluye un Valor constante. ");
  Desc << wxT("Sólo es válida para valores no negativos de los argumemntos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("f(x1,x2,...,xn)=a[0] + a[1]*x1*a[2]*x2* ... *a[n]*xn");
  return Desc;
}

wxString Producto::descripcionLatex()
{
  wxString Desc=wxT("");
  Desc << wxT("La función \\emph{Producto} ");
  Desc << wxT("efectúa el Producto de los argumentos; incluye un Valor constante. ");
  Desc << wxT("Sólo es válida para valores no negativos de los argumentos. ");
  Desc << wxT("La expresión general es la siguiente:\n");
  Desc << wxT("\\[");
  Desc << wxT("f(x_1,x_2,\\cdots,x_n)=a_0 + \\prod_{i=1}^n{a_ix_i}");
  Desc << wxT("\\]\n");
  return Desc;
}

float Producto::inversa(float y, float *x, int k)
{
	if(ParametrosVariables[k][0]==0)
	{
		return 0.0;
	}
	int i;
	float xk=y-ParametrosFijos[0];
	for(i=0;i<Orden;i++)
	{
		if(i!=k)
		{
			xk=xk/(ParametrosVariables[i][0]*x[i]);
		}
	}
	xk=xk/ParametrosVariables[k][0];
	return xk;
}


/////////////////////////////////////////////////////////////////
///*
//void Valor::llenarVectores( int ord)
//{
//	Orden=ord;
//	delete[] Crecer;
//	Crecer=new int[Orden];
//	int i;
//	for(i=0;i<Orden;i++)
//	{
//		Crecer[i]=1;
//	}
//}
//
//float Valor::directa(float *x)
//{
//	float y,y1,y2;
//	if(fabs(Exponente1)<0.0001)
//	{
//		y1=1;
//	}else
//	{
//
//		y1=pow(Parametro,Exponente1);
//	}
//	y=fabs(x[0]);
//	if(y<0.0001){y=0.0001;}
//	if(fabs(Exponente2)<0.0001)
//	{
//		y2=1;
//	}else
//	{
//		y2=pow(y,Exponente2);
//	}
//	y=y1*y2;
//	if(x[0]<0){y=-1*y;}

//	return y;
//}
//
//float Valor::inversa(float y, float *, int )
//{
//	float xk;
//	xk=fabs(y);
//	if(xk<0.0001){xk=0.0001;}
//	if(fabs(Exponente1)<0.001)
//	{
//		xk=xk/1.0;
//	}else
//	{

//		xk=xk/pow(Parametro,Exponente1);
//	}
//	if(fabs(Exponente2)<0.0001)

//	{
//		xk=1.0;	// No es correcto, pero evita el error matematico
//	}else
//	{
//		xk=pow(xk,(1/Exponente2));
//	}
//	if(y<0){xk=-1*xk;}
//	return xk;
//}
//*/
/////////////////////////////////////////////////////////////////
///*
//void Valor2::llenarVectores( int ord)
//{
//	Orden=ord;
//	delete[] Crecer;
//	Crecer=new int[Orden];
//	int i;
//	for(i=0;i<Orden;i++)
//	{
//		Crecer[i]=1;
//	}
//}
//
//float Valor2::directa(float *x)
//{

//	float y,y1,y2;
//	y=fabs(x[0]);
//	if(y<0.0001){y=0.0001;}
//	if(fabs(Exponente1)<0.0001)
//	{
//		y1=1;
//	}else
//	{
//		y1=fabs(pow(y,Exponente1));
//	}
//	if(x[0]<0){y1=-1.0*y1;}
//	y=fabs(x[1]);
//	if(y<0.0001){y=0.0001;}
//	if(fabs(Exponente2)<0.0001)
//	{
//		y2=1;
//	}else
//	{
//		y2=fabs(pow(y,Exponente2));
//	}
//	if(x[1]<0){y2=-1.0*y2;}
//	y=Parametro*y1+(1.0-Parametro)*y2;
//	return y;
//}
//
//float Valor2::inversa(float y, float *, int )
//{
//	float xk;
//	xk=fabs(y);
//	if(xk<0.0001){xk=0.0001;}
//	if(fabs(Exponente1)<0.001)
//	{
//		xk=xk/1.0;
//	}else
//	{
//		xk=xk/pow(Parametro,Exponente1);
//	}
//	if(fabs(Exponente2)<0.0001)
//	{
//		xk=1.0;	// No es correcto, pero evita el error matematico
//	}else
//	{
//		xk=pow(xk,(1/Exponente2));
//	}
//	if(y<0){xk=-1*xk;}
//	return xk;
//}
//*/
/////////////////////////////////////////////////////////////////
///*
//void Logaritmica::llenarVectores( int ord)

//{
//	Orden=ord;
//	delete[] Crecer;
//	Crecer=new int[Orden];
//	int i;
//	for(i=0;i<Orden;i++)
//	{
//		Crecer[i]=1;
//
//	}
//}
//

//float Logaritmica::directa(float *x)
//{
//	int i;
//	float y=0;
//	for(i=0;i<Orden;i++)
//	{
//		float temp;
//		temp=x[i]/10.0;
//		temp=pow(10.0,temp);
//		y=y+temp;
//	}
//	y=10.0*log10(y);
//	return y;
//}
//
//float Logaritmica::inversa(float y, float *x, int k)
//{
//	float xk;
//	xk=pow(10,(y/10.0));
//   int i;
//	for(i=0;i<Orden;i++)
//	{
//		if(i!=k)
//		{
//

//			float temp;
//			temp=x[i]/10.0;
//			temp=pow(10.0,temp);
//			xk=xk-temp;
//		}
//	}
//	xk=10.0*log10(xk);
//
//	return xk;
//}
//*/
/////////////////////////////////////////////////////////////////
///*
//void Cash::llenarVectores( int ord)

//{
//	Orden=ord;
//	delete[] Crecer;
//	Crecer=new int[Orden];
//	int i;
//	Crecer[0]=-1;
//	for(i=1;i<Orden-1;i++)
//	{
//		Crecer[i]=1;
//	}
//	Crecer[Orden-1]=-1;
//}
//
//
//float Cash::directa(float *x)
//{
//	int i;
//	float y;
//	float r;
//	r=x[Orden-1];
//	if(r<0){r=0;}
//	y=x[0];
//	if(y>=0){y=-0.00001;}
//	for(i=1;i<Orden-1;i++)
//	{
//		if(x[i]<0){x[i]=0;}
//		y=y+x[i]/pow((r+1),i);
//	}
//	return y;
//}
//
//float Cash::inversa(float y, float *x, int k)
//
//{
//	float xk,r;
//	r=x[Orden-1];
//	if(k<Orden-1)
//	{
//		xk=y;
//		int i;
//		for(i=0;i<Orden-1;i++)
//		{
//
//			if(i!=k)
//			{
//				xk=xk-x[i]/(r+1);
//			}
//		}

//		xk=xk*(i+x[k]);
//	}else
//	{
//		float r1,r2,r3,s1,s2,s3;
//		r1=0.0;
//		r2=1.0;
//		x[Orden-1]=r1;
//		s1=directa(x);
//		x[Orden-1]=r2;
//		s2=directa(x);
//		do
//		{
//			r3=r1-(s1-y)*(r2-r1)/(s2-s1);
//			x[Orden-1]=r3;
//			s3=directa(x);
//			if(fabs(s2-y)<fabs(s1-y))
//			{
//				r1=r3;
//				s1=s3;
//			}else
//			{
//				r2=r3;
//				s2=s3;
//			}
//
//		}while(fabs(s3-y)>0.001);
//		xk=r3;
//	}
//	return xk;
//}
//*/
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////       curvas         //////////////////////
//////////////////////////////////////////////////////////////////////////
//
///*
//BOOL Curva::operator==(Curva& other)
//{
//	int res;
//	res= ((Tipo==other.Tipo) &
//			(MinX==other.MinX) &
//			(MaxX==other.MaxX) &
//			(NumeroPuntosCriticos==other.NumeroPuntosCriticos));
//	if(res==1)
//	{
//		int i;
//		for(i=0;i<NumeroPuntosCriticos;i++)
//		{
//			res=res & (PuntosCriticos[i]==other.PuntosCriticos[i]);
//		}
//	}
//	return res;

//}
//
//
//void Curva::operator=(Curva& other)
//{
//	Tipo=other.Tipo;
//	MinX=other.MinX;
//	MaxX=other.MaxX;
//
//	NumeroPuntosCriticos=other.NumeroPuntosCriticos;
//	delete []PuntosCriticos;
//	PuntosCriticos=new float[NumeroPuntosCriticos+1];
//	int i;
//	for(i=0;i<NumeroPuntosCriticos;i++)
//	{
//		PuntosCriticos[i]=other.PuntosCriticos[i];
//	}
//}
//
//float Curva::minY()
//{
//	float min;
//	float temp;
//	min=directa(MinX);
//	int i;
//	for (i=0;i<NumeroPuntosCriticos;i++)
//	{
//		temp=directa(PuntosCriticos[i]);
//		if(temp<min)
//		{
//			min=temp;
//		}
//	}
//	temp=directa(MaxX);
//	if(temp<min)
//	{
//		min=temp;
//	}
//	return min;
//
//}
//
//float Curva::maxY()
//{
//
//	float max;
//	float temp;
//	max=directa(MinX);
//	int i;
//	for (i=0;i<NumeroPuntosCriticos;i++)
//	{
//		temp=directa(PuntosCriticos[i]);
//		if(temp>max)
//		{
//			max=temp;
//		}
//	}
//	temp=directa(MaxX);
//	if(temp>max)
//	{
//		max=temp;
//	}
//	return max;
//}
//
//void Curva::directaDifusa(NumeroDifuso *Y, NumeroDifuso *X)
//{
//	float *L;
//	float *R;
//	L=new float[Y->Tamano];
//	R=new float[Y->Tamano];
//	int i;
//	for(i=0;i<Y->Tamano;i++)
//	{
//		float alfa;
//		alfa=Y->intervalo()*i;
//
//		float a,b,c;
//		a=X->d(alfa,1);
//		b=X->d(alfa,-1);
//		float min,max;
//		max=min=directa(a);
//		if(directa(b)<min)
//		{
//			min=directa(b);
//		}
//		if(directa(b)>max)

//		{
//			max=directa(b);
//		}
//
//		int j;
//		for(j=0;j<NumeroPuntosCriticos;j++)
//		{
//			c=PuntosCriticos[j];
//			if((a<c)&&(c<b))
//
//			{
//
//				if(directa(c)<min)
//				{
//					min=directa(c);
//				}
//				if(directa(c)>max)
//				{
//					max=directa(c);
//				}
//			}
//		}
//		L[i]=min;
//		R[i]=max;
//	}
//
//	int N;
//	N=Y->Tamano;
//	Y->nuevo(L,R,N);
//	delete[] L;
//	delete[] R;
//}
//*/
//////////////////////////////////////////////
//
///*
//TrazosRectosContinuos::TrazosRectosContinuos(float *pc,float *pend, float b0, int npc)
//{
//	Tipo="Trazos Rectos Contínuos";
//	NumeroPuntosDeCorte=npc;
//	m=new float[NumeroPuntosDeCorte+1];
//	b=new float[NumeroPuntosDeCorte+1];
//	PuntosDeCorte=new float[NumeroPuntosDeCorte+1];
//	b[0]=b0;
//	int i;
//	for(i=0;i<=NumeroPuntosDeCorte;i++)
//	{
//		PuntosDeCorte[i]=pc[i];
//		m[i]=pend[i];
//	}
//	llenarPuntosCriticos();
//	llenarTerminosIndependientes();
//
//}
//
//TrazosRectosContinuos::TrazosRectosContinuos()
//{
//	Tipo="Trazos Rectos Contínuos";
//	NumeroPuntosDeCorte=0;
//	m=new float[NumeroPuntosDeCorte+1];
//	b=new float[NumeroPuntosDeCorte+1];
//	PuntosDeCorte=new float[NumeroPuntosDeCorte+1];
//	b[0]=0;
//	m[0]=1;
//	int i;
//	for(i=0;i<=NumeroPuntosDeCorte;i++)
//	{
//		PuntosDeCorte[i]=0;
//		m[i]=1;
//	}
//	llenarPuntosCriticos();
//	llenarTerminosIndependientes();
//}
//
//BOOL TrazosRectosContinuos::operator==(TrazosRectosContinuos& other)
//{
//	int res;
//	res= ((Tipo==other.Tipo) &
//			(MinX==other.MinX) &
//			(MaxX==other.MaxX) &
//			(NumeroPuntosCriticos==other.NumeroPuntosCriticos));
//	if(res==1)
//	{
//		int i;
//		for(i=0;i<NumeroPuntosCriticos;i++)
//		{
//			res=res & (PuntosCriticos[i]==other.PuntosCriticos[i]);
//		}
//	}
//	llenarPuntosCriticos();
//
//	llenarTerminosIndependientes();
//	return res;
//}
//
//void TrazosRectosContinuos::operator=(TrazosRectosContinuos& other)
//{
//	Tipo=other.Tipo;
//	MinX=other.MinX;
//	MaxX=other.MaxX;
//	NumeroPuntosCriticos=other.NumeroPuntosCriticos;
//	delete []PuntosCriticos;
//	PuntosCriticos=new float[NumeroPuntosCriticos+1];
//	int i;
//
//	for(i=0;i<NumeroPuntosCriticos;i++)
//	{
//		PuntosCriticos[i]=other.PuntosCriticos[i];
//	}
//	NumeroPuntosDeCorte=other.NumeroPuntosDeCorte;
//	delete []m;
//	delete []b;
//	delete []PuntosDeCorte;
//	m=new float[NumeroPuntosDeCorte+1];
//	b=new float[NumeroPuntosDeCorte+1];
//	PuntosDeCorte=new float[NumeroPuntosDeCorte+1];
//	for(i=0;i<NumeroPuntosDeCorte;i++)
//	{
//		m[i]=other.m[i];
//		b[i]=other.b[i];
//		PuntosDeCorte[i]=other.PuntosDeCorte[i];
//	}
//	llenarPuntosCriticos();
//	llenarTerminosIndependientes();
//}
//
//void TrazosRectosContinuos::llenarPuntosCriticos()
//{
//	NumeroPuntosCriticos=0;
//	int i;
//	for(i=0;i<NumeroPuntosDeCorte;i++)
//	{
//		if((m[i]*m[i+1])<0)
//		{
//			NumeroPuntosCriticos++;
//		}
//	}
//	PuntosCriticos=new float[NumeroPuntosCriticos+1];
//	int k=0;
//	for(i=0;i<NumeroPuntosDeCorte;i++)
//	{
//		if((m[i]*m[i+1])<0)
//
//		{
//			PuntosCriticos[k]=PuntosDeCorte[i];
//			k++;
//		}
//	}
//}
//
//
//void TrazosRectosContinuos::llenarTerminosIndependientes()
//{
//	int i;
//	for(i=0;i<NumeroPuntosDeCorte;i++)
//	{
//		b[i+1]=m[i]*PuntosDeCorte[i]+b[i]-m[i+1]*PuntosDeCorte[i];
//	}
//}
//
//float TrazosRectosContinuos::directa(float x)
//{
//	float y;
//	if (NumeroPuntosDeCorte==0)
//	{
//		y=m[0]*x+b[0];
//	}else
//	{
//
//		if(x<=PuntosDeCorte[0])
//		{
//			y=m[0]*x+b[0];
//		}else if(x>PuntosDeCorte[NumeroPuntosDeCorte-1])
//		{
//			y=m[NumeroPuntosDeCorte]*x+b[NumeroPuntosDeCorte];
//		}else
//		{
//			int i;
//			for(i=0;i<(NumeroPuntosDeCorte-1);i++)
//			{
//				if((PuntosDeCorte[i]<=x)&&(x<=PuntosDeCorte[i+1]))
//				{
//					y=m[i+1]*x+b[i+1];
//				}
//			}
//		}
//	}
//	return y;
//}
//*/
///*
//void TrazosRectosContinuos::escribir(ofpstream &str)
//{
//	str << MinX << MaxX << NumeroPuntosDeCorte;
//	int i;
//	for(i=0;i<NumeroPuntosDeCorte;i++)
//	{
//		str << PuntosDeCorte[i];
//	}
//	for(i=0;i<NumeroPuntosDeCorte+1;i++)
//	{
//		str << m[i];
//	}
//	str << b[0];
//}
//
//
//void TrazosRectosContinuos::escribir(string &str)
//{
//	char cad[800];
//	int i;
//	sprintf(cad,"MinX:%f MaxX:%f\n",MinX,MaxX);
//	str +=cad;
//	sprintf(cad,"Puntos De Corte:%d\n",NumeroPuntosDeCorte);
//	str +=cad;
//	for(i=0;i<NumeroPuntosDeCorte;i++)
//	{
//		sprintf(cad,"%f\n",PuntosDeCorte[i]);
//		str+=cad;
//	}
//	for(i=0;i<NumeroPuntosDeCorte+1;i++)
//	{
//		sprintf(cad,"%f\n",m[i]);
//		str+=cad;
//	}
//	sprintf(cad,"%f\n",b[0]);
//	str+=cad;
//}
//  */
