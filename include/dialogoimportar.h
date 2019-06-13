/***************************************************************************
                          dialogoimportar.h  -  description
                             -------------------
    begin                : mar abr 6 2004
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

#ifndef DIALOGOIMPORTAR_H
#define DIALOGOIMPORTAR_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "proyecto.h"

/**Importación de archivos de texto
  *@author Oscar G. Duarte
  */

class DialogoImportar : public wxDialog  {
public: 
	DialogoImportar(Proyecto *proy,wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoImportar();

  void llenarCuadro();
  void cambiaSel(wxCommandEvent&);
  void aplicar(wxCommandEvent&);
  void seleccionarArchivo(wxCommandEvent&);
  void importar(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);

private:
  Proyecto *Proy;
  wxHtmlHelpController *Ayuda;

  wxString DirectorioActual;
  wxString ArchivoActual;

  ListaSelecciones ListaSel;

  wxButton *ButtonOK;
  wxButton *ButtonCancelar;
  wxButton *ButtonAyuda;
  wxButton *ButtonArchivo;
  wxButton *ButtonImportar;
  wxStaticText *StaticArchivo;
  wxStaticText *StaticOpciones;
  wxTextCtrl *TextArchivo;
  wxListBox *ListBoxItems;
  wxComboBox *ComboSel;
  wxButton *ButtonAplicar;

  DECLARE_EVENT_TABLE()
};

enum
{
  DLG_IMPORTAR_BTN_OK = 1,
  DLG_IMPORTAR_BTN_CANCEL,
  DLG_IMPORTAR_BTN_AYUDA,
  DLG_IMPORTAR_BTN_ARCHIVO,
  DLG_IMPORTAR_BTN_IMPORTAR,
  DLG_IMPORTAR_STATIC_ARCHIVO,
  DLG_IMPORTAR_STATIC_OPCIONES,
  DLG_IMPORTAR_TEXT_ARCHIVO,
  DLG_IMPORTAR_LISTBOX_ITEMS,
  DLG_IMPORTAR_COMBOBOX_SEL,
  DLG_IMPORTAR_BTN_APLICAR
};


#endif
