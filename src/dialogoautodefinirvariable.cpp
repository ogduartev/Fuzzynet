/***************************************************************************
                          dialogoautodefinirvariable.cpp  -  description
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

#include "dialogoautodefinirvariable.h"

BEGIN_EVENT_TABLE(DialogoAutodefinirVariable, wxDialog)
    EVT_BUTTON(DLG_AUTOVARIABLE_BTN_OK, DialogoAutodefinirVariable::cerrarOk)
    EVT_BUTTON(DLG_AUTOVARIABLE_BTN_CANCEL, DialogoAutodefinirVariable::cancelar)
    EVT_BUTTON(DLG_AUTOVARIABLE_BTN_AYUDA, DialogoAutodefinirVariable::ayuda)
    EVT_CHECKBOX(DLG_AUTOVARIABLE_CHECKBOX_RECTOS, DialogoAutodefinirVariable::clickRectos)
    EVT_CHECKBOX(DLG_AUTOVARIABLE_CHECKBOX_CURVOS, DialogoAutodefinirVariable::clickCurvos)
END_EVENT_TABLE()

DialogoAutodefinirVariable::DialogoAutodefinirVariable(VariableLinguistica *var,
          Proyecto *proy, wxWindow *parent,const wxString& title, wxHtmlHelpController *ayuda)
          :wxDialog(parent,-1,title)
{
  Proy=proy;

  VarTemp=var;
  Var=*VarTemp;

  Ayuda=ayuda;

  SetTitle(wxT("Autodefinir Variable Lingüística"));

  ButtonOK                         =new wxButton(this,DLG_AUTOVARIABLE_BTN_OK, wxT("OK"));
  ButtonCancelar                 =new wxButton(this,DLG_AUTOVARIABLE_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda                    =new wxButton (this,DLG_AUTOVARIABLE_BTN_AYUDA, wxT("Ayuda"));
  StaticConjuntos                =new wxStaticText(this,DLG_AUTOVARIABLE_STATIC_CONJUNTOS, wxT("Número de Conjuntos"));
  SpinConjuntos                 =new wxSpinCtrl (this,DLG_AUTOVARIABLE_SPIN_CONJUNTOS);
  CheckRectos                   =new wxCheckBox (this,DLG_AUTOVARIABLE_CHECKBOX_RECTOS,wxT("Rectos"));
  CheckCurvos                  =new wxCheckBox (this,DLG_AUTOVARIABLE_CHECKBOX_CURVOS,wxT("Curvos"));

  CheckRectos->SetValue(TRUE);
  CheckCurvos->SetValue(FALSE);
  SpinConjuntos->SetMinSize(wxSize(40,20));
  SpinConjuntos->SetRange(2,100);
  SpinConjuntos->SetValue(Var.Etiquetas.GetCount());

    wxBoxSizer *sizerCheck = new wxBoxSizer(wxHORIZONTAL);
    sizerCheck->Add(StaticConjuntos, 0, wxALIGN_CENTER | wxALL, 5);
    sizerCheck->Add(SpinConjuntos, 0, wxALIGN_CENTER | wxALL, 5);
    sizerCheck->Add(CheckRectos, 0, wxALIGN_CENTER | wxALL, 5);
    sizerCheck->Add(CheckCurvos, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerCheck, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

//    llenarCuadro();
}

DialogoAutodefinirVariable::~DialogoAutodefinirVariable()
{
}

void DialogoAutodefinirVariable::clickRectos(wxCommandEvent&)
{
  if(CheckRectos->GetValue())
  {
    CheckCurvos->SetValue(FALSE);
  }else
  {
    CheckCurvos->SetValue(TRUE);
  }
}

void DialogoAutodefinirVariable::clickCurvos(wxCommandEvent&)
{
  if(CheckCurvos->GetValue())
  {
    CheckRectos->SetValue(FALSE);
  }else
  {
    CheckRectos->SetValue(TRUE);
  }
}

void DialogoAutodefinirVariable::cerrarOk(wxCommandEvent&)
{
  int n;
  n=SpinConjuntos->GetValue();
  if(CheckRectos->GetValue())
  {
    Var.autodefinirRecto(n);
  }else
  {
    Var.autodefinirCurvo(n);
  }
  *VarTemp=Var;
  Close();
}

void DialogoAutodefinirVariable::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoAutodefinirVariable::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Definición Automática de Variables"));
}


