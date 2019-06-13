/***************************************************************************
                          dialogointervalo.cpp  -  description
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

#include "dialogointervalo.h"

BEGIN_EVENT_TABLE(DialogoIntervalo, wxDialog)
    EVT_BUTTON(DLG_INTERVALO_BTN_OK, DialogoIntervalo::cerrarOk)
    EVT_BUTTON(DLG_INTERVALO_BTN_CANCEL, DialogoIntervalo::cancelar)
    EVT_BUTTON(DLG_INTERVALO_BTN_AYUDA, DialogoIntervalo::ayuda)
END_EVENT_TABLE()

DialogoIntervalo::DialogoIntervalo(float *va, float *vb, Proyecto *proy,
                   wxWindow *parent, wxHtmlHelpController *ayuda)
                   :wxDialog(parent,wxID_ANY,wxString(wxT(" ")))
{
  Proy=proy;
  Ayuda=ayuda;

    VATemp=va;
    VBTemp=vb;
    VA=*va;
    VB=*vb;

    SetTitle(wxT("Intervalo"));

     ButtonOK                         =new wxButton(this,DLG_INTERVALO_BTN_OK, wxT("OK"));
     ButtonCancelar                 =new wxButton(this,DLG_INTERVALO_BTN_CANCEL, wxT("Cancelar"));
     ButtonAyuda                    =new wxButton (this,DLG_INTERVALO_BTN_AYUDA, wxT("Ayuda"));
     StaticMinimo                     =new wxStaticText(this,DLG_INTERVALO_STATIC_MINIMO, wxT("Mínimo"));
     StaticMaximo                    =new wxStaticText(this,DLG_INTERVALO_STATIC_MAXIMO, wxT("Máximo"));
    TextMinimo                        =new wxTextCtrl(this,DLG_INTERVALO_TEXT_MINIMO);
    TextMaximo                       =new wxTextCtrl(this,DLG_INTERVALO_TEXT_MAXIMO);
/*    ButtonOK                          ->SetSize(80,20);
    ButtonCancelar                  ->SetSize(80,20);
    TextMinimo                        ->SetSize(80,20);
    TextMaximo                       ->SetSize(80,20);
*/
    wxFlexGridSizer *sizerMinMax = new wxFlexGridSizer(2,2,5,5);
    sizerMinMax->Add(StaticMinimo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerMinMax->Add(TextMinimo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerMinMax->Add(StaticMaximo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerMinMax->Add(TextMaximo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerMinMax, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoIntervalo::~DialogoIntervalo()
{
}

void DialogoIntervalo::llenarCuadro()
{
  wxString cad;
  cad=wxT(""); cad << VA;TextMinimo->SetValue(cad);
  cad=wxT(""); cad << VB;TextMaximo->SetValue(cad);
}


void DialogoIntervalo::leerTextos()
{
  wxString cad;
  double tmp;
  cad=TextMinimo->GetValue();
  if(cad.ToDouble(&tmp))
  {
    VA=(float)tmp;
  }
  cad=TextMaximo->GetValue();
  if(cad.ToDouble(&tmp))
  {
    VB=(float)tmp;
  }
}

void DialogoIntervalo::cerrarOk(wxCommandEvent&)
{
  leerTextos();
  if(VA > VB)
  {
    wxMessageBox(wxT("El Mínimo no puede ser mayor que el Máximo"),wxT("Atención"),wxOK);
  }else
  {
    *VATemp=VA;
    *VBTemp=VB;
    Close();
  }
}

void DialogoIntervalo::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoIntervalo::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición de Intervalos"));
}

