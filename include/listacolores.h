/***************************************************************************
                          listacolores.h  -  description
                             -------------------
    begin                : vie mar 5 2004
    copyright            : (C) 2004 by 
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef LISTACOLORES_H
#define LISTACOLORES_H

#include <wx/wx.h>
#include <wx/dynarray.h>

WX_DECLARE_OBJARRAY(wxColour, ListaDeColores);

/**
  *@author 
  */

class ListaColores {
public: 
	ListaColores();
	~ListaColores();

  void adicionarColor(wxString N, wxColour C);
  wxColour* Color(wxString N);
  void limpiar();

  wxArrayString Nombres;
  ListaDeColores Colores;
};

#endif
