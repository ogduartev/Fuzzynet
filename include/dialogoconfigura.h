/***************************************************************************
                          dialogoconfigura.h  -  description
                             -------------------
    begin                : mar 17 2004
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

#ifndef DIALOGOCONFIGURA_H
#define DIALOGOCONFIGURA_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/html/helpctrl.h>
#include "micanvas.h"
#include "paginacolores.h"
#include "paginafuentes.h"
#include "paginadimensiones.h"
#include "paginaselecciones.h"


/**Cuadro de Diálogo para la configuración de la Interfaz gráfica
  *@author Oscar G. Duarte
  */

class DialogoConfigura : public wxDialog{
public: 
	DialogoConfigura(MiCanvas *canvas,
                 wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoConfigura();
  void llenarNotebook();
  void leerConfigura(wxCommandEvent&);
  void escribirConfigura(wxCommandEvent&);
  void defecto(wxCommandEvent&);
  void OnPaint(wxPaintEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
  
protected:
  MiCanvas *Canvas;

  wxNotebook *Notebook;
  PaginaColores *PagColores;
  PaginaFuentes *PagFuentes;
  PaginaDimensiones *PagDimensiones;
  PaginaSelecciones *PagSelecciones;
  wxHtmlHelpController *Ayuda;

  // Comn
  wxButton *ButtonOK;
  wxButton *ButtonCancelar;
  wxButton *ButtonAyuda;
  wxButton *ButtonLeerConfigura;
  wxButton *ButtonEscribirConfigura;
  wxButton *ButtonDefecto;

   DECLARE_EVENT_TABLE()
};

enum
{
  DLG_CONFIGURA_BTN_OK = 1,
  DLG_CONFIGURA_BTN_CANCEL,
  DLG_CONFIGURA_BTN_AYUDA,
  DLG_CONFIGURA_BTN_LEERCONFIGURA,
  DLG_CONFIGURA_BTN_ESCRIBIRCONFIGURA,
  DLG_CONFIGURA_BTN_DEFECTO,
  DLG_CONFIGURA_NOTEBOOK
};


#endif
