/***************************************************************************
                          fuzznum.cpp  -  description
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


#include "fuzznum.h"

#include <math.h>



/**
 * Se construye un numero difuso a partir de otro nmero difuso
 * El constructor verifica que los valores sean coherentes, es decir, que
 * formen 2 o más intervalos anidados. Si no son coherentes crea dos alfa-
 * cortes de extremos iguales a cero
 * \param l vector con extremos inferiores de los alfa-cortes del nmero difuso modelo
 * \param r vector con extremos superiores de los alfa-cortes del número difuso modelo
 * \param T tamaño de los vectores del número difuso modelo
 * \see verificaNumero
*/
NumeroDifuso::NumeroDifuso(float* l, float *r,int T)
{
	if (!verificaNumero(l,r,T))
	{
		Tamano=2;
		L=new float[Tamano];
		R=new float[Tamano];
		int i;
		for(i=0;i<Tamano;i++)
		{
			L[i]=0;
			R[i]=0;
		}
	}else
	{
		Tamano=T;
		L=new float[Tamano];
		R=new float[Tamano];
		int i;
		for(i=0;i<Tamano;i++)
		{
			L[i]=l[i];
			R[i]=r[i];
		}
	}
}
/**
 * Compara dos números difusos. Compara el tamaño y los extremos de
 * los alfa-cortes
 */
BOOL NumeroDifuso::operator==(NumeroDifuso& other)
{
	if(Tamano!=other.Tamano)
	{
		return 0;
	}
	int i;
	for(i=0;i<Tamano;i++)
	{
		if(L[i]!=other.L[i]||R[i]!=other.R[i])
		{
			return 0;
		}
	}
	return 1;
}

/**
 * Copia el número difuso y, su tamaño y los extremos de los alfa-cortes
 */
void NumeroDifuso::copiar(NumeroDifuso* y)
{
	int i;

	delete[] L;
	delete[] R;
	L=new float[y->Tamano];
	R=new float[y->Tamano];
  Tamano=y->Tamano;
	for(i=0;i<y->Tamano;i++)
	{
		L[i]=y->L[i];
		R[i]=y->R[i];

	}
}

/**
 * Remplaza los alfa-cortes por otros contenidos en los vectores l y r.
 * La función verifica que los valores sean coherentes, es decir, que
 * formen 2 o más intervalos anidados. Si no son coherentes crea dos alfa-
 * cortes de extremos iguales a cero
 * \param l vector con extremos inferiores de los alfa-cortes del nmero difuso modelo
 * \param r vector con extremos superiores de los alfa-cortes del nmero difuso modelo
 * \param T tamaño de los vectores del número difuso modelo
 * \see verificaNumero

*/
void NumeroDifuso::nuevo(float* l, float *r,int T)
{
	if (!verificaNumero(l,r,T))
	{
		delete[] L;
		delete[] R;
		Tamano=T;
		L=new float[Tamano];
		R=new float[Tamano];
		int i;
		for(i=0;i<Tamano;i++)
		{
			L[i]=0;
			R[i]=0;
		}
	}else
	{
		Tamano=T;
		delete[] L;
		delete[] R;
		L=new float[Tamano];
		R=new float[Tamano];
		int i;
		for(i=0;i<Tamano;i++)
		{
			L[i]=l[i];
			R[i]=r[i];
		}
	}
}

/**
 * Verifica si los vectores l y r, que deben ser de tamaño T, almacenan valores válidos como
 * extremos inferiores y superiores de alfa-cortes de un núero difuso, respectivamente.
 * Las condiciones que verifica son las siguientes:
 *
 * a) T debe ser mayor o igual que 2.
 *
 * b) l[i] debe ser menor o igual que r[i] para i=0,1,2,... T-1
 *
 * c) l[i] debe ser menor o igual que l[i+1] para i=0,1,2,... T-2
 *
 * d) r[i] debe ser mayor o igual que r[i+1] para i=0,1,2,... T-2
 */
int NumeroDifuso::verificaNumero(float* l, float *r,int T)

{
	int i;
	if (T<2)

	{
		return 0;
	}
	for(i=0;i<T;i++)
	{
		if(l[i]>r[i])
		{
			return 0;
		}
	}
	for(i=0;i<T-1;i++)
	{
		if(l[i]>l[i+1])
		{
			return 0;
		}
		if(r[i]<r[i+1])
		{
			return 0;
		}
	}

	return 1;
}

/**
 * Calcula los extremos de los alfa-cortes efectuando interpolación lineal entre
 * los valores almacenados en L y R.
 * \param a Un valor entre 0 y 1, correspondiente al alfa-corte que se desea. Si a
 * no está en ese intervalo, se ajusta a 0 o a 1.
 * \param D determina qué extremo se calcula. Si D>0 se calcula el extremo inferior.
 * En caso contrario se calcula el extremo superior
 */

float NumeroDifuso::d(float a, int D)
{
	float alfa;
	alfa=a;
	if(alfa<0)
	{
		alfa=0;
	}
	if(alfa>=1)
	{
//		alfa=1;
		if(D>0)
		{
			return L[Tamano-1];
		}else
		{
			return R[Tamano-1];
		}
	}

	int indice;
	indice=(int)(alfa/intervalo());
	float valor;
	if(D>0)
	{
		valor=L[indice]+(L[indice+1]-L[indice])*(alfa-intervalo()*indice)/intervalo();
	}else
	{
		valor=R[indice]+(R[indice+1]-R[indice])*(alfa-intervalo()*indice)/intervalo();
	}

	return valor;
}

/**
 * Calcula el grado de pertenencia  de x al número difuso efectuando interpolación 
 * lineal entre los valores almacendos en L y R.
 */

float NumeroDifuso::pertenece(float x)
{
	if(x<L[0]||x>R[0])
	{
		return 0.0;
	}
	if(x>=L[Tamano-1]&&x<=R[Tamano-1])
	{
		return 1.0;
	}
	int i;
	for(i=0;i<=Tamano-2;i++)
	{
		if(x==L[i]&&x==L[i+1])
		{
			return intervalo()*(i+1);
		}
		if(x==R[i]&&x==R[i+1])
		{
			return intervalo()*(i+1);
		}
		if(x>=L[i]&&x<L[i+1])
		{
			float u;
		  u=intervalo()*i+(x-L[i])*intervalo()/(L[i+1]-L[i]);
			return u;
		}
		if(x<=R[i]&&x>R[i+1])
		{
			float u;
		  u=intervalo()*i+(x-R[i])*intervalo()/(R[i+1]-R[i]);
			return u;
		}
	}
	return 0;
}

/**
 * Modifica los alfa-cortes para construir un número difuso trapezoidal
 * de vértices (a,b,c,d). No cambia el número de Alfa-Cortes.
 * \param a menor valor del soporte
 * \param b menor valor del ncleo
 * \param c mayor valor del ncleo
 * \param d mayor valor del soporte
 */
void NumeroDifuso::trapecio(float a, float b, float c, float d)
{
	if(a<=b && b<=c && c<=d)
	{
		int i;
		for(i=0;i<Tamano;i++)
		{
			L[i]=a+(b-a)*intervalo()*i;
			R[i]=d-(d-c)*intervalo()*i;
		}
	}
}

/**
 * Modifica los alfa-cortes para construir un número difuso curvo
 * de vértices (a,b,c,d). Las curvas son cuadráticas. No cambia el número de Alfa-Cortes.
 * \param a menor valor del soporte
 * \param b menor valor del ncleo
 * \param c mayor valor del ncleo
 * \param d mayor valor del soporte
 */
void NumeroDifuso::campana(float a, float b, float c, float d)
{
	if(a<=b && b<=c && c<=d)
	{
		int i;
		for(i=0;i<Tamano;i++)
		{
      float alfa;
      alfa=intervalo()*i;
			if(alfa<0.5)
			{
				L[i]=a+(b-a)*sqrt(alfa/2.0);
				R[i]=d-(d-c)*sqrt(alfa/2.0);
			}else
			{
				L[i]=b-(b-a)*sqrt((1.0-alfa)/2.0);
				R[i]=c+(d-c)*sqrt((1.0-alfa)/2.0);

			}
		}
	}
}

/**
 * Cambia el nmero de alfa-cortes del nmero difuso. Los nuevos extremos los
 * calcula a partir de los anteriores.
 * \param T Nuevo nmero de alfa-cortes. debe ser mayor o igual a 2
*/
void NumeroDifuso::tamano(int T)
{
	if(T>=2)
	{
		float *NL;
		float *NR;
		NL=new float[T];
		NR=new float[T];
		float Nintervalo;
		Nintervalo=1.0/(T-1.0);
		int i;
		for(i=0;i<T;i++)
		{
			NL[i]=d(i*Nintervalo,1);
			NR[i]=d(i*Nintervalo,-1);
		}
		delete[] L;
		delete[] R;

		Tamano=T;
		L=new float[Tamano];
		R=new float[Tamano];
		for(i=0;i<Tamano;i++)
		{
			L[i]=NL[i];
			R[i]=NR[i];
		}
		delete[] NL;
		delete[] NR;
	}
}

/**
 * Calcula el valor representativo del Nmero Difuso tomando 100 alfa-cortes
 */
float NumeroDifuso::valorRepresentativo()
{
	float v;
	v=0.005*(d(0,1)+d(0,-1))*0.005;
	float alfa;
	for(alfa=0;alfa<1.001;alfa+=0.01)
	{
		v=v+alfa*(d(alfa,1)+d(alfa,-1))*0.01;
	}
	v=v-1*(d(0,1)+d(0,-1))*0.005;
	return v;
}

/**
* Calcula el valor representativo en función del "optimismo" opt. si opt=0 toma
* los extremos izquierdos de los alfa-cortes. si opt=1 toma los extreos derechos
* de los alfa-cortes. para 0 < opt < 1 toma valores intermedios con interpolación lineal
* Efecta un promedio ponderado de los valores representativos de cada alfa-corte
* El promedio se hace con la funcion alfa^r
*/
float NumeroDifuso::valorRepresentativo(float opt,float r)
{
 if(r<0.0){r=0.0;}
 if(opt<0.0){opt=0.0;}
 if(opt>1.0){opt=1.0;}
float v=0.0;
 int i;
float ai,aj,Vi,Vj;

for(i=0;i<Tamano-1;i++)
{
   ai=i*intervalo();
   aj=(i+1)*intervalo();
   Vi=(1-opt)*d(ai,1)+opt*d(ai,-1);
   Vj=(1-opt)*d(aj,1)+opt*d(aj,-1);
   v=v+(pow(aj,r+1)-pow(ai,r+1))*Vi/(r+1);
   v=v+(pow(aj,r+2)-pow(ai,r+2))*(Vj-Vi)/((r+2)*(aj-ai));
   v=v-(pow(aj,r+1)-pow(ai,r+1))*ai*(Vj-Vi)/((r+1)*(aj-ai));
}
 v=(r+1)*v;
return v;
}

/**
 * Calcula la ambigüedad del Número Difuso tomando 100 alfa-cortes
 */
float NumeroDifuso::ambiguedad()
{
	float v;
	v=0.005*(d(0,-1)-d(0,1))*0.005;
	float alfa;
	for(alfa=0;alfa<1.001;alfa+=0.01)
	{
		v=v+alfa*(d(alfa,-1)-d(alfa,1))*0.01;
	}
	v=v-1*(d(0,-1)-d(0,1))*0.005;
	return v;
}
/**
 * Calcula la consistencia entre el Número Difuso y num tomando 100 alfa-cortes
 */
float NumeroDifuso::consistencia(NumeroDifuso *num)
{
	float cons;
	float a,b,c,d;
	int i;
	for(i=0;i<=100;i++)
	{
		cons=i*0.01;
		a=this->d(cons,1);b=this->d(cons,-1);
		c=num->d(cons,1);d=num->d(cons,-1);
		if((a>d)||(c>b))

		{
			i=101;
		}
	}
   return cons;
}


void NumeroDifuso::write(Mi_ofpstream &str)
{
	int i;
	str << Tamano;
	for(i=0;i<Tamano;i++)
	{
		str << L[i];
		str << R[i];
	}
}

void NumeroDifuso::read(Mi_ifpstream &str)
{
	int i;
	str >> Tamano;
	delete [] L;
	delete [] R;
	L=new float[Tamano];
	R=new float[Tamano];

	for(i=0;i<Tamano;i++)
	{
      str >> L[i];
      str >> R[i];
	}

}
