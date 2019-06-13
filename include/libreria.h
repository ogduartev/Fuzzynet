/***************************************************************************
                          libreria.h  -  description
                             -------------------
    begin                : abr 21 2004
    copyright            : (C) 2004 by Oscar G. Duarte
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef LIBRERIA_H
#define LIBRERIA_H

#include "proyecto.h"

/**
  *@author Oscar G. Duarte
  */

class Libreria {
public: 
	Libreria();
	~Libreria();

	void write(Mi_ofpstream &str);
	void read(Mi_ifpstream &str);
  void datos(wxArrayString *Nom, wxArrayString *Des,int caso);

  ListaEstrategias Estrategias;
  ListaCasos Casos;
  ListaVariables Variables;
};

#endif
