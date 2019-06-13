/***************************************************************************
                          dialogopropiedades.h  -  description
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

#ifndef DIALOGOPROPIEDADES_H
#define DIALOGOPROPIEDADES_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "propiedades.h"

/**Edición de propiedades
  *@author Oscar G. Duarte
  */

class DialogoPropiedades : public wxDialog  {
public: 
	DialogoPropiedades(Propiedades *pr, wxWindow *parent, wxHtmlHelpController *ayuda);
	~DialogoPropiedades();

  void llenarCuadro();
  void adicionar(wxCommandEvent&);
  void editar(wxCommandEvent&);
  void borrar(wxCommandEvent&);
  void actualizar(wxCommandEvent&);
  void cambiaPropiedad(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
private:
  Propiedades Prop;
  Propiedades *PropTmp;
  wxHtmlHelpController *Ayuda;

  int sel;

  wxButton *ButtonAdicionar;
  wxButton *ButtonEditar;
  wxButton *ButtonBorrar;
  wxButton *ButtonActualizar;
  wxButton *ButtonOK;
  wxButton *ButtonCancelar;
  wxButton *ButtonAyuda;
  wxStaticText *StaticPropiedades;
  wxListBox *ListBoxPropiedades;
  wxTextCtrl *TextCtrlPropiedad;

  DECLARE_EVENT_TABLE()
};

enum
{
  DLG_PROPIEDADES_BTN_ACTUALIZAR = 1,
  DLG_PROPIEDADES_BTN_ADICIONAR,
  DLG_PROPIEDADES_BTN_EDITAR,
  DLG_PROPIEDADES_BTN_BORRAR,
  DLG_PROPIEDADES_BTN_OK,
  DLG_PROPIEDADES_BTN_CANCEL,
  DLG_PROPIEDADES_BTN_AYUDA,
  DLG_PROPIEDADES_STATIC_PROPIEDADES,
  DLG_PROPIEDADES_LISTBOX_PROPIEDADES,
  DLG_PROPIEDADES_TEXTCTRL_PROPIEDAD
};

#endif
