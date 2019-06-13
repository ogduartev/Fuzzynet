/***************************************************************************
                          paginadimensiones.h  -  description
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

#ifndef PAGINADIMENSIONES_H
#define PAGINADIMENSIONES_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include "micanvas.h"

/**Panel para Edición de dimensiones en el Diálogo de Configuración
  *@author Oscar G. Duarte
  */

class PaginaDimensiones : public wxPanel{
public:
	PaginaDimensiones(MiCanvas *canvas,
                 wxWindow* parent,const wxString& title);
	~PaginaDimensiones();
  void crearPagDimensiones();
  void recargar();
  void OnPaint(/*wxPaintEvent& event*/);
  void pintarDim();
  void aplicar(wxCommandEvent&);
  void seleccionarDim(wxCommandEvent&);

protected:
  MiCanvas *Canvas;

  ListaDimensiones *ListaTempDim;
  ListaDimensiones ListaDim;

  wxSpinCtrl *SpinDim;

  //Dimensiones
  wxButton *ButtonAplicarDim;
  wxListBox *ListBoxItemsDim;

   DECLARE_EVENT_TABLE()
};

enum
{
  DLG_PAGDIM_BTN_APLICAR=1,
  DLG_PAGDIM_LISTBOX,
  DLG_PAGDIM_SPIN
};

#endif
