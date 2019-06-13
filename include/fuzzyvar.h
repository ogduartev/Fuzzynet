/***************************************************************************
                          fuzzyvar.h  -  description
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

#ifndef __FUZZYVAR_H
#define __FUZZYVAR_H

#include<wx/wx.h>

#include "listaselecciones.h"
#include "fuzzfunc.h"

/**
 * Implementa las etiquetas de una Variable Lingüística.
 * Consiste de un NumeroDiduso ND y una cadena Label
 * Label es el nombre de la etiqueta y ND su semántica.
 * \see VariableLinguistica
 * \see NumeroDifuso
 */
class Etiqueta
{
public:
	Etiqueta(wxString str=wxT("Etiqueta Sin Nombre"));
	~Etiqueta()
	{
		delete ND;
	}

	void numero(NumeroDifuso *n){ND->copiar(n);}
	BOOL operator ==(Etiqueta& other)
	{
		return((Label==other.Label) &
			(*ND==*other.ND));
	}
	void operator =(Etiqueta& other)
	{
		Label=other.Label;
		ND->copiar(other.ND);
	}

	void write(Mi_ofpstream &str);
	void read(Mi_ifpstream &str);

	wxString Label;
	NumeroDifuso *ND;
};

WX_DECLARE_OBJARRAY(Etiqueta, ListaEtiquetas);

/**
 * Implementa una Variable Lingüística como un conjunto de Etiquetas
 * Esta clase tiene una alta funcionalidad. El valor de la Variable Linguistica
 * puede definirse por medio de un número crisp, un intervalo, un nmero difuso
 * o una etiqueta con modificadores lingüísticos.
 * see Etiqueta
 */
class VariableLinguistica
{
public:
	VariableLinguistica(wxString str=wxT("Variable Sin Nombre"),float min=0,float max=1.0,int num=5);
/**
 * Elimina las etiquetas
 */
	~VariableLinguistica()
	{
		limpiarListaEtiquetas();
	}
	void redefinirRecto();
	void autodefinirRecto(int num);
	void autodefinirCurvo(int num);
	void nuevoRango(float nuevoMin, float nuevoMax);
	void limpiarListaEtiquetas();

   void interpretacion(wxArrayString *ListaStr,NumeroDifuso *num);
   void interpretacionMaxima(wxString *Texto,NumeroDifuso *num);

   void importarCadena(wxString Dato,ListaSelecciones Opciones);

	NumeroDifuso *etiqueta();
	void strEtiqueta(wxString *et);
	wxString strEntrada();
  NumeroDifuso *valor();

	BOOL operator==(VariableLinguistica& other);
	void operator=(VariableLinguistica& other);
/**
 * Almacena el listado de etiquetas
 * \see Arreglo
 * \see Etiqueta
 */
  ListaEtiquetas Etiquetas;
//	Arreglo<Etiqueta> *Etiquetas;
/**
 * Nombre de la Variable Lingüística
 */
	wxString Nombre;
/**
 * Descripción de la Variable Linguistica
 */
  wxString Descripcion;
/**
 * Unidades en que se mide la Variable 
 */
  wxString Unidades;
/**
 * Rango sobre el que está definida la Variable 
 */
	float Minimo,Maximo;
/**
 * número de Etiqueta que define el valor de la Variable 
 * si Modificador=3;
 */
	int EtiquetaSeleccionada;
/**
 * Modificadores válidos: 0:Sin MOdificador;  1:A lo Sumo;
 * 2:Por lo Menos;   3=Nada;    4:Cualquier Cosa
 */
	int Modificador;
/**
 * Forma de calcular el valor de la variable 
 * 0=Indefinido; 1=crisp; 2=intervalo; 3=numeroDifuso; 4=etiqueta
 */
	int TipoDeValor;
/**
 * Valor de la Variable si Modificador=1;
 */
	float Crisp;
/**
 * Límites del Intervalo que define el Valor de la Variable si Modificador=2;
 */
  float IntA,IntB;
/**
 * Valor de la Variable si Modificador=3;
 */
  NumeroDifuso NumDif;


	void write(Mi_ofpstream &str);
	void read(Mi_ifpstream &str);

};


#endif
