/***************************************************************************
                          fuzznum.h  -  description
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

#ifndef _FUZZNUM_H
#define _FUZZNUM_H

#include "mi_fstream.h"

typedef int BOOL;

/**
 * La Clase NumeroDifuso implementa los Nmeros Difusos en función de sus alfa-cortes.
 * Cada Alfa Corte es un intervalo cerrado.
*/
class NumeroDifuso
{
public:
/**
 * Se crean los vectores. Por defecto se trabajan trapecios (2 alfa-cortes)
*/
	NumeroDifuso(int T=2)
	{
		Tamano=T;
		L=new float[Tamano];
		R=new float[Tamano];
		int i;
		for(i=0;i<Tamano;i++)
		{
			L[i]=0;
			R[i]=0;
		}
	}
	NumeroDifuso(float* l, float *r,int T);



/**
 * Se destruyen los vectores
*/
	~NumeroDifuso()
	{
		delete[] L;
		delete[] R;
	}
	void nuevo(float* l, float *r,int T);
	void tamano(int T);
/**
 * Calcula el intervalo de separación entre Alfa-Cortes
 */
	float intervalo(void){return 1.0/(Tamano-1.0);}
	float d(float a, int D);
	float pertenece(float x);
	int verificaNumero(float* l, float *r,int T);
	void trapecio(float a, float b, float c, float d);
	void campana(float a, float b, float c, float d);
	float valorRepresentativo();
  float valorRepresentativo(float opt=0.5,float r=0);

	float ambiguedad();
	float consistencia(NumeroDifuso *num);
	BOOL operator==(NumeroDifuso& other);
/**
 * Copia el número difuso y
 */
	void operator=(NumeroDifuso& other){copiar(&other);}
	void copiar(NumeroDifuso* y);

	void write(Mi_ofpstream &str);
	void read(Mi_ifpstream &str);

/**
 * Número de alfa cortes utilizados, igualmente espaciados en el intervalo [0,1]
 */
	int Tamano;
/**
 * Vector de tamaño Tamano en los que se almacenan los extremos inferiores de los alfa-corte.
*/
	float *L;
/**
 * Vector de tamaño Tamano en los que se almacenan los extremos superiores de los alfa-corte.
 */
	float *R;

};


#endif
