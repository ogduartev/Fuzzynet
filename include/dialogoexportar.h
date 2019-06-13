/***************************************************************************
                          dialogoexportar.h  -  description
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

#ifndef DIALOGOEXPORTAR_H
#define DIALOGOEXPORTAR_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "proyecto.h"
#include "paginalistados.h"

/**
  *@author Oscar G. Duarte
  */

class DialogoExportar : public wxDialog  {
public: 
	DialogoExportar(Proyecto *proy,wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoExportar();

  void llenarNoteBook();
  void llenarCuadro();
  void seleccionarArchivo(wxCommandEvent&);
  void exportar(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);

private:
  Proyecto *Proy;
  PaginaListados **Paginas;
  wxArrayString *Origen;
  int NumPaginas;
  wxHtmlHelpController *Ayuda;
  
  wxString DirectorioActual;
  wxString ArchivoActual;


  wxNotebook *Notebook;
  wxButton *ButtonOK;
  wxButton *ButtonCancelar;
  wxButton *ButtonAyuda;
  wxButton *ButtonArchivo;
  wxButton *ButtonExportar;
  wxStaticText *StaticArchivo;
  wxStaticText *StaticOpciones;
  wxStaticText *StaticSeparador;
  wxTextCtrl *TextArchivo;
  wxComboBox *ComboOpciones;
  wxComboBox *ComboSeparador;
  wxCheckBox *CheckTodo;
  wxCheckBox *CheckPropiedades;

  DECLARE_EVENT_TABLE()
};

enum
{
  DLG_EXPORTAR_BTN_OK = 1,
  DLG_EXPORTAR_BTN_CANCEL,
  DLG_EXPORTAR_BTN_AYUDA,
  DLG_EXPORTAR_BTN_ARCHIVO,
  DLG_EXPORTAR_BTN_EXPORTAR,
  DLG_EXPORTAR_STATIC_ARCHIVO,
  DLG_EXPORTAR_STATIC_OPCIONES,
  DLG_EXPORTAR_STATIC_SEPARADOR,
  DLG_EXPORTAR_TEXT_ARCHIVO,
  DLG_EXPORTAR_COMBOBOX_OPCIONES,
  DLG_EXPORTAR_COMBOBOX_SEPARADOR,
  DLG_EXPORTAR_CHECKBOX_TODO,
  DLG_EXPORTAR_CHECKBOX_PROPIEDADES,
  DLG_EXPORTAR_NOTEBOOK
};

#endif
