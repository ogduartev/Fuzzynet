/***************************************************************************
                          listadimensiones.h  -  description
                             -------------------
    begin                : mar 24 2004
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

#ifndef LISTADIMENSIONES_H
#define LISTADIMENSIONES_H

#include <wx/wx.h>
#include <wx/dynarray.h>

WX_DECLARE_OBJARRAY(int, ListaDeDimensiones);

/**Lista de dimensiones de configuración para la interfaz gráfica
  *@author Oscar G. Duarte
  */

class ListaDimensiones {
public:
	ListaDimensiones();
	~ListaDimensiones();

  void adicionarDimension(wxString N, int d);
  int Dimension(wxString N);
  void limpiar();

  wxArrayString Nombres;
  ListaDeDimensiones Dimensiones;
};

#endif
