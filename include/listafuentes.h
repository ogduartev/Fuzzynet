/***************************************************************************
                          listafuentes.h  -  description
                             -------------------
    begin                : mar 10 2004
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

#ifndef LISTAFUENTES_H
#define LISTAFUENTES_H

#include <wx/wx.h>
#include <wx/dynarray.h>

WX_DECLARE_OBJARRAY(wxFont, ListaDeFuentes);


/**
  *@author Oscar G. Duarte
  */

class ListaFuentes {
public: 
	ListaFuentes();
	~ListaFuentes();

  void adicionarFuente(wxString N, wxFont F);
  wxFont* Fuente(wxString N);
  void limpiar();
  
  wxArrayString Nombres;
  ListaDeFuentes Fuentes;
};

#endif
