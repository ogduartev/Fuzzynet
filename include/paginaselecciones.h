/***************************************************************************
                          paginaselecciones.h  -  description
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

#ifndef PAGINASELECCIONES_H
#define PAGINASELECCIONES_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/combobox.h>
#include "micanvas.h"

/**Panel para edición de selecciones en Diálogo de Configuración
  *@author Oscar G. Duarte
  */

class PaginaSelecciones : public wxPanel{
public:
	PaginaSelecciones(MiCanvas *canvas,
                 wxWindow* parent,const wxString& title);
	~PaginaSelecciones();
  void crearPagSelecciones();
  void recargar();
  void pintarSel();
  void aplicar(wxCommandEvent&);
  void seleccionarSel(wxCommandEvent&);

protected:
  MiCanvas *Canvas;

  ListaSelecciones *ListaTempSel;
  ListaSelecciones ListaSel;

  wxComboBox *ComboSel;

  //Selecciones
  wxButton *ButtonAplicarSel;
  wxListBox *ListBoxItemsSel;

   DECLARE_EVENT_TABLE()
};

enum
{
  DLG_PAGSEL_BTN_APLICAR=1,
  DLG_PAGSEL_LISTBOX,
  DLG_PAGSEL_COMBOBOX
};

#endif
