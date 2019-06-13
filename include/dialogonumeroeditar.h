/***************************************************************************
                          dialogonumeroeditar.h  -  description
                             -------------------
    begin                : lun jul 28 2003
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

#ifndef DIALOGONUMEROEDITAR_H
#define DIALOGONUMEROEDITAR_H

/**
  *@author 
  */

#include <wx/wx.h>
#include <wx/generic/grid.h>
#include <wx/html/helpctrl.h>
#include <wx/spinctrl.h>
#include "cadenas.h"
#include "dialogocopiarnumero.h"
  
class DialogoNumeroEditar : public wxDialog  {
public: 
	DialogoNumeroEditar(int etiflag, Etiqueta *e,float min,float max,
                      Proyecto *proy, wxWindow* parent, wxHtmlHelpController *ayuda);
	~DialogoNumeroEditar();
  
  void OnPaint(wxPaintEvent&);
  void pintar(wxPaintDC &dc);
  void llenarCuadro();

  void spinAlfa(wxSpinEvent&);
  void clickListaAlfa(wxCommandEvent&);
  void definir(wxCommandEvent&);
  void clickTrapecio(wxCommandEvent&);
  void clickCampana(wxCommandEvent&);
  void leerCuadro();
  void copiarResultado(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);
  
private:
  Proyecto *Proy;
  Etiqueta *EtiTemp;
  NumeroDifuso Num;
  wxHtmlHelpController *Ayuda;
  wxString Label;
  float Min,Max,Opt,Rep;
  int EtiFlag;
  
  wxButton *ButtonCopiarResultado;
  wxButton *ButtonDefinicionRapida;
  wxButton *ButtonOK;
  wxButton *ButtonCancelar;
  wxButton *ButtonAyuda;
  wxListBox *ListBoxAlfa;
//  wxGrid *GrillaAlfa;
  wxStaticText *StaticLabel;
  wxStaticText *StaticValor;
  wxStaticText *StaticAmbiguedad;
  wxStaticText *StaticA;
  wxStaticText *StaticB;
  wxStaticText *StaticC;
  wxStaticText *StaticD;
  wxStaticText *StaticSpinAlfa;
  wxSpinCtrl *SpinAlfa;
  wxTextCtrl *TextLabel;
  wxTextCtrl *TextA;
  wxTextCtrl *TextB;
  wxTextCtrl *TextC;
  wxTextCtrl *TextD;
  wxCheckBox *CheckTrapecio;
  wxCheckBox *CheckCampana;
  
  wxSizer* SizerDibujo;
  

  DECLARE_EVENT_TABLE()
};

enum
{
  DLG_NUMEROEDITAR_BTN_COPIARRESULTADO = 1,
  DLG_NUMEROEDITAR_BTN_DEFINICIONRAPIDA,
  DLG_NUMEROEDITAR_BTN_OK,
  DLG_NUMEROEDITAR_BTN_CANCEL,
  DLG_NUMEROEDITAR_BTN_AYUDA,
  DLG_NUMEROEDITAR_LISTBOX_GRILLA_ALFA,
//  DLG_NUMEROEDITAR_GRID_GRILLA_ALFA,
  DLG_NUMEROEDITAR_STATIC_LABEL,
  DLG_NUMEROEDITAR_STATIC_VALOR,
  DLG_NUMEROEDITAR_STATIC_AMBIGUEDAD,
  DLG_NUMEROEDITAR_STATIC_A,
  DLG_NUMEROEDITAR_STATIC_B,
  DLG_NUMEROEDITAR_STATIC_C,
  DLG_NUMEROEDITAR_STATIC_D,
  DLG_NUMEROEDITAR_STATIC_SPIN_ALFA,
  DLG_NUMEROEDITAR_SPIN_ALFA,
  DLG_NUMEROEDITAR_TEXT_LABEL,
  DLG_NUMEROEDITAR_TEXT_A,
  DLG_NUMEROEDITAR_TEXT_B,
  DLG_NUMEROEDITAR_TEXT_C,
  DLG_NUMEROEDITAR_TEXT_D,
  DLG_NUMEROEDITAR_CHECK_TRAPECIO,
  DLG_NUMEROEDITAR_CHECK_CAMPANA
};

#endif
