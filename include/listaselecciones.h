/***************************************************************************
                          listaselecciones.h  -  description
                             -------------------
    begin                : jue mar 25 2004
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

#ifndef LISTASELECCIONES_H
#define LISTASELECCIONES_H

#include <wx/wx.h>
#include <wx/dynarray.h>

WX_DECLARE_OBJARRAY(wxArrayString, ListaDeOpciones);

WX_DECLARE_OBJARRAY(int, ListaDeSelecciones);

/**Lista de selecciones de configuración para la interfaz gráfica
  *@author Oscar G. Duarte
  */

class ListaSelecciones {
public: 
	ListaSelecciones();
	~ListaSelecciones();
  void adicionarSeleccion(wxString N, wxArrayString C,int S);
  wxArrayString* Opcion(wxString N);
  int Seleccion(wxString N);
  void seleccion(wxString N,int S);
  void limpiar();

  wxArrayString Nombres;
  ListaDeOpciones Opciones;
  ListaDeSelecciones Selecciones;
};

#endif
