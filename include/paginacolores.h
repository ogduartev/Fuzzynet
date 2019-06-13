/***************************************************************************
                          paginacolores.h  -  description
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

#ifndef PAGINACOLORES_H
#define PAGINACOLORES_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include "micanvas.h"

/**
  * Panel para edición de colores en el Diálogo de Configuración
  *@author Oscar G. Duarte
  */

class PaginaColores : public wxPanel{
public:
	PaginaColores(MiCanvas *canvas,
                 wxWindow* parent,const wxString& title);
	~PaginaColores();
  void crearPagColores();
  void recargar();
  void editarCol(wxCommandEvent&);
  void OnPaint(wxPaintEvent&);
  void pintarCol();
  void aplicar(wxCommandEvent&);
  void seleccionarCol(wxCommandEvent&);

protected:
  MiCanvas *Canvas;

  ListaColores *ListaTempCol;
  ListaColores ListaCol;

  wxBoxSizer *sizerDibujoCol;


  //Colores
  wxButton *ButtonEditarCol;
  wxButton *ButtonAplicarCol;
  wxListBox *ListBoxItemsCol;

   DECLARE_EVENT_TABLE()
};

enum
{
  DLG_PAGCOL_BTN_EDITAR=1,
  DLG_PAGCOL_BTN_APLICAR,
  DLG_PAGCOL_LISTBOX
};

#endif
