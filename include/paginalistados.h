/***************************************************************************
                          paginalistados.h  -  description
                             -------------------
    begin                : lun abr 5 2004
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

#ifndef PAGINALISTADOS_H
#define PAGINALISTADOS_H

#include <wx/wx.h>
#include <wx/notebook.h>

/**
  *@author Oscar G. Duarte
  */

class PaginaListados : public wxPanel  {
public: 
	PaginaListados(wxArrayString origen,
                wxWindow* parent);
	~PaginaListados();
  void llenarCuadro();
  void agregar(wxCommandEvent&);
  void eliminar(wxCommandEvent&);
  void agregarTodo(wxCommandEvent&);
  void eliminarTodo(wxCommandEvent&);
  void subir(wxCommandEvent&);
  void bajar(wxCommandEvent&);

  wxArrayString Destino;

private:
  wxArrayString Origen;
  wxListBox *ListaOrigen;
  wxListBox *ListaDestino;
  wxButton *ButtonAgregar;
  wxButton *ButtonEliminar;
  wxButton *ButtonAgregarTodo;
  wxButton *ButtonEliminarTodo;
  wxButton *ButtonSubir;
  wxButton *ButtonBajar;
  wxStaticText *StaticOrigen;
  wxStaticText *StaticDestino;

   DECLARE_EVENT_TABLE()
  
};

enum
{
  DLG_PAGLIS_LISTBOX_ORIGEN=1,
  DLG_PAGLIS_LISTBOX_DESTINO,
  DLG_PAGLIS_BTN_AGREGAR,
  DLG_PAGLIS_BTN_ELIMINAR,
  DLG_PAGLIS_BTN_AGREGARTODO,
  DLG_PAGLIS_BTN_ELIMINARTODO,
  DLG_PAGLIS_BTN_SUBIR,
  DLG_PAGLIS_BTN_BAJAR,
  DLG_PAGLIS_STATIC_ORIGEN,
  DLG_PAGLIS_STATIC_DESTINO
};

#endif
