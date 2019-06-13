/***************************************************************************
                          dialogoseleccionarestrategia.h  -  description
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

#ifndef DIALOGOSELECCIONARESTRATEGIA_H
#define DIALOGOSELECCIONARESTRATEGIA_H

/**
  *@author Oscar G. Duarte
  */
#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "proyecto.h"

class DialogoSeleccionarEstrategia : public wxDialog  {
public: 
	DialogoSeleccionarEstrategia(int *e, int *f,  int *f2,Proyecto *proy, wxWindow *parent, wxHtmlHelpController *ayuda);
	~DialogoSeleccionarEstrategia();

  void llenarCuadro();
  void clickBorrar(wxCommandEvent&);
  void clickAdicionar(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
  
private:
  int *Est;
  Proyecto *Proy;
  int *Flag,*Flag2;
  wxHtmlHelpController *Ayuda;
    
  wxButton *ButtonOK;
  wxButton *ButtonCancelar;
  wxButton *ButtonAyuda;
  wxStaticText *StaticEstrategias;
  wxListBox *ListBoxEstrategias;
  wxCheckBox *CheckBorrar;
  wxCheckBox *CheckAdicionar;
  wxCheckBox *CheckGeneralidades;

  DECLARE_EVENT_TABLE()
};

enum
{
  DLG_ESTRATEGIAS_BTN_OK = 1,
  DLG_ESTRATEGIAS_BTN_CANCEL,
  DLG_ESTRATEGIAS_BTN_AYUDA,
  DLG_ESTRATEGIAS_STATIC_ESTRATEGIAS,
  DLG_ESTRATEGIAS_LISTBOX_ESTRATEGIAS,
  DLG_ESTRATEGIAS_CHECK_BORRAR,
  DLG_ESTRATEGIAS_CHECK_ADICIONAR,
  DLG_ESTRATEGIAS_CHECK_GENERALIDADES
};

#endif
