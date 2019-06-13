/***************************************************************************
                          paginaseleccionesgrilla.h  -  description
                             -------------------
    begin                : dom abr 18 2004
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

#ifndef PAGINASELECCIONESGRILLA_H
#define PAGINASELECCIONESGRILLA_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/combobox.h>
#include <wx/image.h>
#include "micanvas.h"

/**Panel para edición de selecciones en Diálogo de Configuración
  *@author Oscar G. Duarte
  */

class PaginaSeleccionesGrilla : public wxPanel{
public:
	PaginaSeleccionesGrilla(ListaSelecciones *lista,
                 wxWindow* parent,const wxString& title);
	~PaginaSeleccionesGrilla();
  void crearPagSelecciones();
  void cambiaSeleccion(wxGridEvent &ev);
  void leeContenido();

protected:

  ListaSelecciones *ListaSel;

  wxComboBox *ComboSel;

  //Selecciones
  wxGrid *Grilla;

   DECLARE_EVENT_TABLE()
};

enum
{
  DLG_PAGSELGRILLA_GRILLA=1,
  DLG_PAGSELGRILLA_CHOICE
//  DLG_PAGSEL_COMBOBOX
};




#endif
