/***************************************************************************
                          caso.h  -  description
                             -------------------
    begin                : mar abr 15 2003
    copyright            : (C) 2003 by Oscar G. Duarte V.
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   Este programa ha sido diseñado por Oscar G. Duarte V. por encargo del *
 *   Departamento de Ciencias de la Computación e Inteligencia             *
 *   Artificial de la Universidad de Granada.                              *      
 *                                                                         *
 ***************************************************************************/

#ifndef CASO_H
#define CASO_H

#include "fuzzyvar.h"
#include "propiedades.h"

WX_DECLARE_OBJARRAY(VariableLinguistica, ListaVariables);

/**
 * Tiene La información de cada uno de los casos que se calcularán con la Estrategia
 */
class Caso
{
public: 
	Caso();
	~Caso();

	void write(Mi_ofpstream &str);
	void read(Mi_ifpstream &str);

  ListaVariables Variables;
  Propiedades Generalidades;
  wxString Nombre;
  wxString Descripcion;
};

#endif
