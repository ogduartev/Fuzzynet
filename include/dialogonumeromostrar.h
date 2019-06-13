/***************************************************************************
                          dialogonumeromostrar.h  -  description
                             -------------------
    begin                : jue abr 8 2004
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

#ifndef DIALOGONUMEROMOSTRAR_H
#define DIALOGONUMEROMOSTRAR_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "proyecto.h"

/**Muestra un nmero difuso y su variable de contexto, pero no permite editarlo.
  *@author Oscar G. Duarte
  */

class DialogoNumeroMostrar : public wxDialog  {
public:
	DialogoNumeroMostrar(VariableLinguistica *var, NumeroDifuso *num,
                 wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoNumeroMostrar();

  void OnPaint(wxPaintEvent&);
  void pintar(wxPaintDC &dc);
  void llenarCuadro();
  void seleccionarEtiqueta(wxCommandEvent&);

  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);

private:
    VariableLinguistica *Var;
    NumeroDifuso *Num;
    wxHtmlHelpController *Ayuda;
        
    wxButton *ButtonOK;
    wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxStaticText *StaticNombre;
    wxStaticText *StaticMinimo;
    wxStaticText *StaticMaximo;
    wxStaticText *StaticUnidades;
    wxStaticText *StaticEtiquetas;
    wxStaticText *StaticValorCalculado;
    wxTextCtrl *TextNombre;
    wxTextCtrl *TextMinimo;
    wxTextCtrl *TextMaximo;
    wxTextCtrl *TextUnidades;
    wxListBox *ListBoxEtiquetas;

    wxSizer* SizerDibujo;

    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_NUMERO_MOSTRAR_BTN_OK = 1,
  DLG_NUMERO_MOSTRAR_BTN_CANCEL,
  DLG_NUMERO_MOSTRAR_BTN_AYUDA,
  DLG_NUMERO_MOSTRAR_STATIC_NOMBRE,
  DLG_NUMERO_MOSTRAR_STATIC_MINIMO,
  DLG_NUMERO_MOSTRAR_STATIC_MAXIMO,
  DLG_NUMERO_MOSTRAR_STATIC_UNIDADES,
  DLG_NUMERO_MOSTRAR_STATIC_ETIQUETAS,
  DLG_NUMERO_MOSTRAR_STATIC_VALORCALCULADO,
  DLG_NUMERO_MOSTRAR_STATIC_INTERPRETACION,
  DLG_NUMERO_MOSTRAR_STATIC_INTERPRETACIONLARGA,
  DLG_NUMERO_MOSTRAR_TEXT_NOMBRE,
  DLG_NUMERO_MOSTRAR_TEXT_MINIMO,
  DLG_NUMERO_MOSTRAR_TEXT_MAXIMO,
  DLG_NUMERO_MOSTRAR_TEXT_UNIDADES,
  DLG_NUMERO_MOSTRAR_LISTBOX_ETIQUETAS
};


#endif
