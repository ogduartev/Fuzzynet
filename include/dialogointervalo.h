/***************************************************************************
                          dialogointervalo.h  -  description
                             -------------------
    begin                : jul 26 2003
    copyright            : (C) 2003 by 
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DIALOGOINTERVALO_H
#define DIALOGOINTERVALO_H

/**
  *@author 
  */

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "proyecto.h"

class DialogoIntervalo : public wxDialog  {
public: 
	DialogoIntervalo(float *va, float *vb, Proyecto *proy, wxWindow* parent, wxHtmlHelpController *ayuda);
	~DialogoIntervalo();

  void llenarCuadro();
  void leerTextos();

  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
    
private:
    Proyecto *Proy;
    wxHtmlHelpController *Ayuda;
    
    float *VATemp,*VBTemp;
    float VA,VB;

    wxButton *ButtonOK;
    wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxStaticText *StaticMinimo;
    wxStaticText *StaticMaximo;
    wxTextCtrl *TextMinimo;
    wxTextCtrl *TextMaximo;

    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_INTERVALO_BTN_OK = 1,
  DLG_INTERVALO_BTN_CANCEL,
  DLG_INTERVALO_BTN_AYUDA,
  DLG_INTERVALO_STATIC_MINIMO,
  DLG_INTERVALO_STATIC_MAXIMO,
  DLG_INTERVALO_TEXT_MINIMO,
  DLG_INTERVALO_TEXT_MAXIMO
};

#endif
