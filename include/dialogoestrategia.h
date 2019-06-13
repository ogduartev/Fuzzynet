/***************************************************************************
                          dialogoestrategia.h  -  description
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

#ifndef DIALOGOESTRATEGIA_H
#define DIALOGOESTRATEGIA_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "proyecto.h"
#include "micanvas.h"
#include "dialogopropiedades.h"
#include "dialogolibreria.h"

/**Edición de la Estrategia
  *@author Oscar G. Duarte
  */

class DialogoEstrategia : public wxDialog  {
public: 
	DialogoEstrategia(Estrategia *est,Proyecto *proy, MiCanvas *canvas, wxWindow *parent, wxHtmlHelpController *ayuda);
	~DialogoEstrategia();

  void llenarCuadro();
  void grafo(wxCommandEvent&);
  void propiedades(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void librerias(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
  
private:
  Estrategia *Est;
  Proyecto *Proy;
  MiCanvas *Canvas;
  wxHtmlHelpController *Ayuda;

    wxButton *ButtonGrafo;
    wxButton *ButtonPropiedades;
    wxButton *ButtonOK;
//  wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxButton *ButtonLibrerias;
    wxTextCtrl *TextNombre;
    wxStaticText *StaticNombre;
    wxStaticText *StaticDescripcion;
    wxTextCtrl *TextDescripcion;

    DECLARE_EVENT_TABLE()
    
};

enum
{
  DLG_EST_BTN_GRAFO,
  DLG_EST_BTN_PROPIEDADES,
  DLG_EST_BTN_OK,
//DLG_EST_BTN_CANCELAR,
  DLG_EST_BTN_AYUDA,
  DLG_EST_BTN_LIBRERIAS,
  DLG_EST_TEXT_NOMBRE,
  DLG_EST_STATIC_DESCRIPCION,
  DLG_EST_TEXT_DESCRIPCION,
  DLG_EST_STATIC_NOMBRE,
};

#endif
