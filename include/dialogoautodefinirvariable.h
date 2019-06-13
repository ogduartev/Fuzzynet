/***************************************************************************
                          dialogoautodefinirvariable.h  -  description
                             -------------------
    begin                : vie ago 1 2003
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

#ifndef DIALOGOAUTODEFINIRVARIABLE_H
#define DIALOGOAUTODEFINIRVARIABLE_H

#include <wx/wx.h>
#include <wx/html/helpctrl.h>
#include "cadenas.h"
#include "proyecto.h"
#include "dialogointervalo.h"
#include "dialogonumeroeditar.h"

/**
  *@author Oscar G. Duarte
  */

class DialogoAutodefinirVariable : public wxDialog  {
public:
	DialogoAutodefinirVariable(VariableLinguistica *var, Proyecto *proy,
                 wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda);
	~DialogoAutodefinirVariable();
  void clickRectos(wxCommandEvent&);
  void clickCurvos(wxCommandEvent&);
  void cerrarOk(wxCommandEvent&);
  void cancelar(wxCommandEvent&);
  void ayuda(wxCommandEvent&);

private:
    Proyecto *Proy;

    VariableLinguistica *VarTemp;
    VariableLinguistica Var;
    wxHtmlHelpController *Ayuda;
    
    wxButton *ButtonOK;
    wxButton *ButtonCancelar;
    wxButton *ButtonAyuda;
    wxStaticText *StaticConjuntos;
    wxSpinCtrl *SpinConjuntos;
    wxCheckBox *CheckRectos;
    wxCheckBox *CheckCurvos;

    DECLARE_EVENT_TABLE()
};

enum
{
  DLG_AUTOVARIABLE_BTN_OK = 1,
  DLG_AUTOVARIABLE_BTN_CANCEL,
  DLG_AUTOVARIABLE_BTN_AYUDA,
  DLG_AUTOVARIABLE_STATIC_CONJUNTOS,
  DLG_AUTOVARIABLE_SPIN_CONJUNTOS,
  DLG_AUTOVARIABLE_CHECKBOX_RECTOS,
  DLG_AUTOVARIABLE_CHECKBOX_CURVOS
};


#endif
