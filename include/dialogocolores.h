/***************************************************************************
                          dialogocolores.h  -  description
                             -------------------
    begin                : jue abr 1 2004
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

#ifndef DIALOGOCOLORES_H
#define DIALOGOCOLORES_H

#include <wx/wx.h>
#include "listacolores.h"

/**Dialogo para mostrar los Colores de la Pantalla
  *@author Oscar G. Duarte
  */

class DialogoColores : public wxDialog  {
public: 
	DialogoColores(ListaColores col,
                 wxWindow* parent,const wxString& title);
	~DialogoColores();
  void OnPaint(wxPaintEvent&);

  ListaColores Colores;

DECLARE_EVENT_TABLE()

};

#endif
