/***************************************************************************
                          dialogomodificador.h  -  description
                             -------------------
    begin                : ago 2 2003
    copyright            : (C) 2003 by Oscar G. Duarte
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

#ifndef DIALOGOMODIFICADOR_H
#define DIALOGOMODIFICADOR_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "proyecto.h"

/**
  *@author Oscar G. Duarte
  */

class DialogoModificador : public wxDialog  {
public:
	DialogoModificador(VariableLinguistica *var, Proyecto *proy,
                 wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoModificador();
  void clickModificador(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);

private:
    Proyecto *Proy;

    VariableLinguistica *VarTemp;
    VariableLinguistica Var;
    wxHtmlHelpController *Ayuda;
    
    wxButton *ButtonOK;
    wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxStaticText *StaticCadena;
    wxListBox *ListBoxModificador;

    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_MODIFICADOR_BTN_OK = 1,
  DLG_MODIFICADOR_BTN_CANCEL,
  DLG_MODIFICADOR_BTN_AYUDA,
  DLG_MODIFICADOR_STATIC_CADENA,
  DLG_MODIFICADOR_LISTBOX_MODIFICADOR
};

#endif
