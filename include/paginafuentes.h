/***************************************************************************
                          paginafuentes.h  -  description
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

#ifndef PAGINAFUENTES_H
#define PAGINAFUENTES_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include "micanvas.h"

/**
  * Panel para edición de colores en el Diálogo de Configuración
  *@author Oscar G. Duarte
  */

class PaginaFuentes : public wxPanel{
public:
	PaginaFuentes(MiCanvas *canvas,
                 wxWindow* parent,const wxString& title);
	~PaginaFuentes();
  void crearPagFuentes();
  void recargar();
  void editarFte(wxCommandEvent&);
  void OnPaint(wxPaintEvent&);
  void pintarFte();
  void aplicar(wxCommandEvent&);
  void seleccionarFte(wxCommandEvent&);

protected:
  MiCanvas *Canvas;

  ListaFuentes *ListaTempFte;
  ListaFuentes ListaFte;

  wxBoxSizer *sizerDibujoFte;


  //Fuentes
  wxButton *ButtonEditarFte;
  wxButton *ButtonAplicarFte;
  wxListBox *ListBoxItemsFte;

   DECLARE_EVENT_TABLE()
};

enum
{
  DLG_PAGFTE_BTN_EDITAR=1,
  DLG_PAGFTE_BTN_APLICAR,
  DLG_PAGFTE_LISTBOX
};

#endif
