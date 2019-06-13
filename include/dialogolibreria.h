/***************************************************************************
                          dialogolibreria.h  -  description
                             -------------------
    begin                : abr 21 2004
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

#ifndef DIALOGOLIBRERIA_H
#define DIALOGOLIBRERIA_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "libreria.h"

/**
  *@author Oscar G. Duarte
  */

class DialogoLibreria : public wxDialog  {
public: 
	DialogoLibreria(Estrategia *est,Caso *cas, VariableLinguistica *var,
                  wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoLibreria();

  void cerrarOk(wxCommandEvent&);
//  void cancelar();
  void ayuda(wxCommandEvent&);
  void archivo(wxCommandEvent&);
  void llenarCuadro();
  void seleccionaItem(wxCommandEvent&);
  void adicionar(wxCommandEvent&);
  void leer(wxCommandEvent&);
  void borrar(wxCommandEvent&);
  void salvar(wxCommandEvent&);

protected:
  Estrategia *Est;
  Caso *Cas;
  VariableLinguistica *Var;
  wxArrayString Nom,Desc;
  wxHtmlHelpController *Ayuda;
  
  int Tipo;

  Libreria Lib;
  wxString DirectorioInicial;
  wxString DirectorioActual;
  wxString ArchivoActual;

  // Comn
  wxButton *ButtonOK;
  wxButton *ButtonAyuda;
  wxButton *ButtonArchivo;
  wxButton *ButtonSalvar;
  wxButton *ButtonAdicionar;
  wxButton *ButtonLeer;
  wxButton *ButtonBorrar;
  wxStaticText *StaticArchivo;
  wxTextCtrl *TextArchivo;
  wxListBox *ListBoxItems;
  wxStaticText *StaticItems;
  wxStaticText *StaticDesc;
  wxTextCtrl *TextDesc;
  wxStaticText *StaticActual;
  wxTextCtrl *TextActual;
  

   DECLARE_EVENT_TABLE()
};

enum
{
  DLG_LIBRERIA_BTN_OK = 1,
  DLG_LIBRERIA_BTN_AYUDA,
  DLG_LIBRERIA_BTN_ARCHIVO,
  DLG_LIBRERIA_BTN_SALVAR,
  DLG_LIBRERIA_BTN_ADICIONAR,
  DLG_LIBRERIA_BTN_LEER,
  DLG_LIBRERIA_BTN_BORRAR,
  DLG_LIBRERIA_STATIC_ARCHIVO,
  DLG_LIBRERIA_TEXT_ARCHIVO,
  DLG_LIBRERIA_LIST_ITEMS,
  DLG_LIBRERIA_STATIC_ITEMS,
  DLG_LIBRERIA_STATIC_DESC,
  DLG_LIBRERIA_TEXT_DESC,
  DLG_LIBRERIA_STATIC_ACTUAL,
  DLG_LIBRERIA_TEXT_ACTUAL
};



#endif
