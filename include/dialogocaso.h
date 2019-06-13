/***************************************************************************
                          dialogocaso.h  -  description
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

#ifndef DIALOGOCASO_H
#define DIALOGOCASO_H


/**
  *@author Oscar G. Duarte
  */

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "micanvas.h"
#include "dialogovariable.h"
#include "dialogoseleccionarestrategia.h"
#include "dialogopropiedades.h"
#include "dialogolibreria.h"
  
class DialogoCaso : public wxDialog  {
public: 
	DialogoCaso(MiCanvas *canvas,Caso *cas,Proyecto *proy, wxWindow *parent, wxHtmlHelpController *ayuda);
	~DialogoCaso();

  void llenarCuadro();
  void editarVariable(wxCommandEvent&);
  void nuevaVariable(wxCommandEvent&);
  void borrarVariable(wxCommandEvent&);
  void copiarVariable(wxCommandEvent&);
  void propiedades(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void librerias(wxCommandEvent&);
  void ayuda(wxCommandEvent&);

private:
  MiCanvas *Canvas;
  Caso *Cas;
  Proyecto *Proy;
  wxHtmlHelpController *Ayuda;

    wxButton *ButtonEditarVariable;
    wxButton *ButtonNuevaVariable;
    wxButton *ButtonBorrarVariable;
    wxButton *ButtonCopiarVariables;
    wxButton *ButtonPropiedades;
    wxButton *ButtonOK;
//  wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxButton *ButtonLibrerias;
    wxListBox *ListBoxVariables;
    wxTextCtrl *TextNombre;
    wxStaticText *StaticNombre;
    wxStaticText *StaticVariables;
    wxStaticText *StaticDescripcion;
    wxTextCtrl *TextDescripcion;

    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_CASO_BTN_EDITAR_VARIABLE = 1,
  DLG_CASO_BTN_NUEVA_VARIABLE,
  DLG_CASO_BTN_BORRAR_VARIABLE,
  DLG_CASO_BTN_COPIAR_VARIABLE,
  DLG_CASO_BTN_PROPIEDADES,
  DLG_CASO_BTN_OK,
//DLG_CASO_BTN_CANCELAR,
  DLG_CASO_BTN_AYUDA,
  DLG_CASO_BTN_LIBRERIAS,
  DLG_CASO_LISTBOX_VARIABLES,
  DLG_CASO_TEXT_NOMBRE,
  DLG_CASO_STATIC_DESCRIPCION,
  DLG_CASO_TEXT_DESCRIPCION,
  DLG_CASO_STATIC_NOMBRE,
  DLG_CASO_STATIC_VARIABLES
};    

#endif
