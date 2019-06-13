/***************************************************************************
                          dialogoordenarcasos.h  -  description
                             -------------------
    begin                : mar sep 16 2003
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

#ifndef DIALOGOORDENARCASOS_H
#define DIALOGOORDENARCASOS_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "proyecto.h"

/**
  *@author Oscar G. Duarte
  */

class DialogoOrdenarCasos : public wxDialog
{
public: 
	DialogoOrdenarCasos(Proyecto *proy, wxWindow *parent, wxHtmlHelpController *ayuda);
	~DialogoOrdenarCasos();

  void cerrarOk(wxCommandEvent&);
//  void cancelar();
  void llenarCuadro();
  void llenarNodos(wxCommandEvent&);
  void clickAscendente(wxCommandEvent&);
  void clickDescendente(wxCommandEvent&);
  void ordenar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);

private:
    Proyecto *Proy;
    wxHtmlHelpController *Ayuda;

    wxButton *ButtonOrdenar;
    wxButton *ButtonOK;
    wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxListBox *ListBoxEstrategias;
    wxListBox *ListBoxNodos;
    wxStaticText *StaticEstrategias;
    wxStaticText *StaticNodos;
    wxCheckBox *CheckAlfabetico;
    wxCheckBox *CheckAscendente;
    wxCheckBox *CheckDescendente;
    
    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_ORDENCASO_BTN_ORDENAR = 1,
  DLG_ORDENCASO_BTN_OK,
  DLG_ORDENCASO_BTN_CANCEL,
  DLG_ORDENCASO_BTN_AYUDA,
  DLG_ORDENCASO_STATIC_ESTRATEGIAS,
  DLG_ORDENCASO_STATIC_NODOS,
  DLG_ORDENCASO_CHECKBOX_ALFABETICO,
  DLG_ORDENCASO_CHECKBOX_ASCENDENTE,
  DLG_ORDENCASO_CHECKBOX_DESCENDENTE,
  DLG_ORDENCASO_LISTBOX_ESTRATEGIAS,
  DLG_ORDENCASO_LISTBOX_NODOS
};    

#endif
