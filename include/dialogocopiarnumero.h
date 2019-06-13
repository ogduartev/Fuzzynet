/***************************************************************************
                          dialogocopiarnumero.h  -  description
                             -------------------
    begin                :  sep 13 2003
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

#ifndef DIALOGOCOPIARNUMERO_H
#define DIALOGOCOPIARNUMERO_H


/**
  *@author Oscar G. Duarte
  */

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "proyecto.h"

class DialogoCopiarNumero : public wxDialog  {
public: 
	DialogoCopiarNumero(NumeroDifuso *num,
                      Proyecto *proy, wxWindow* parent, wxHtmlHelpController *ayuda);
	~DialogoCopiarNumero();

  void llenarCuadro();
  void llenarNodos(wxCommandEvent&);
  void copiar(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
  
private:
  Proyecto *Proy;
  NumeroDifuso Num;
  NumeroDifuso *NumTemp;
  wxHtmlHelpController *Ayuda;
  
  wxButton *ButtonCopiar;
  wxButton *ButtonOK;
  wxButton *ButtonCancelar;
  wxButton *ButtonAyuda;
  wxListBox *ListBoxEstrategias;
  wxListBox *ListBoxNodos;
  wxListBox *ListBoxCasos;
  wxStaticText *StaticEstrategias;
  wxStaticText *StaticNodos;
  wxStaticText *StaticCasos;
  wxStaticText *StaticSeleccion;

  DECLARE_EVENT_TABLE()
};

enum
{
  DLG_NUMEROCOPIAR_BTN_COPIAR = 1,
  DLG_NUMEROCOPIAR_BTN_OK,
  DLG_NUMEROCOPIAR_BTN_CANCEL,
  DLG_NUMEROCOPIAR_BTN_AYUDA,
  DLG_NUMEROCOPIAR_LISTBOX_ESTRATEGIAS,
  DLG_NUMEROCOPIAR_LISTBOX_NODOS,
  DLG_NUMEROCOPIAR_LISTBOX_CASOS,
  DLG_NUMEROCOPIAR_STATIC_ESTRATEGIAS,
  DLG_NUMEROCOPIAR_STATIC_NODOS,
  DLG_NUMEROCOPIAR_STATIC_CASOS,
  DLG_NUMEROCOPIAR_STATIC_SELECCION
};          

#endif
