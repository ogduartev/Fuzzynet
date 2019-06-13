/***************************************************************************
                          dialogoreporte.h  -  description
                             -------------------
    begin                : lun abr 19 2004
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

#ifndef DIALOGOREPORTE_H
#define DIALOGOREPORTE_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>
#include <wx/html/helpctrl.h>
#include "reporte.h"
#include "reportetexto.h"
#include "reportelatex.h"
#include "reportehtml.h"
#include "paginaseleccionesgrilla.h"


/**Cuadro de Diálogo para la generación de reportes
  *@author Oscar G. Duarte
  */

class DialogoReporte : public wxDialog{
public:
	DialogoReporte(Proyecto *proy,int con,int tipo,
                 wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoReporte();
  void llenarNotebook();
  void leerConfigura(wxCommandEvent&);
  void escribirConfigura(wxCommandEvent&);
  void defecto(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
  void generar(wxCommandEvent&);
  void archivo(wxCommandEvent&);

protected:
  Proyecto *Proy;
  wxHtmlHelpController *Ayuda;
  int Contenido,Tipo;

  ReporteTexto Rep;
  wxString DirectorioInicial;
  wxString DirectorioActual;
  wxString ArchivoActual;

  wxNotebook *Notebook;
  PaginaSeleccionesGrilla **PagSelecciones;
  int NumPag;

  // Comn
  wxButton *ButtonOK;
  wxButton *ButtonCancelar;
  wxButton *ButtonAyuda;
  wxButton *ButtonLeerConfigura;
  wxButton *ButtonEscribirConfigura;
  wxButton *ButtonDefecto;
  wxButton *ButtonGenerar;
  wxGauge *GaugeAvance;
  wxButton *ButtonArchivo;
  wxStaticText *StaticArchivo;
  wxTextCtrl *TextArchivo;

   DECLARE_EVENT_TABLE()
};

enum
{
  DLG_REPORTE_BTN_OK = 1,
  DLG_REPORTE_BTN_CANCEL,
  DLG_REPORTE_BTN_AYUDA,
  DLG_REPORTE_BTN_LEERCONFIGURA,
  DLG_REPORTE_BTN_ESCRIBIRCONFIGURA,
  DLG_REPORTE_BTN_DEFECTO,
  DLG_REPORTE_BTN_GENERAR,
  DLG_REPORTE_GAUGE_AVANCE,
  DLG_REPORTE_BTN_ARCHIVO,
  DLG_REPORTE_STATIC_ARCHIVO,
  DLG_REPORTE_TEXT_ARCHIVO,
  DLG_REPORTE_NOTEBOOK
};    


#endif
