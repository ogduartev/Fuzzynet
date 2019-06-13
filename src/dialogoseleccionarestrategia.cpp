/***************************************************************************
                          dialogoseleccionarestrategia.cpp  -  description
                             -------------------
    begin                : sep 13 2003
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

#include "dialogoseleccionarestrategia.h"

BEGIN_EVENT_TABLE(DialogoSeleccionarEstrategia, wxDialog)
    EVT_BUTTON(DLG_ESTRATEGIAS_BTN_OK, DialogoSeleccionarEstrategia::cerrarOk)
    EVT_BUTTON(DLG_ESTRATEGIAS_BTN_CANCEL, DialogoSeleccionarEstrategia::cancelar)
    EVT_BUTTON(DLG_ESTRATEGIAS_BTN_AYUDA, DialogoSeleccionarEstrategia::ayuda)
    EVT_CHECKBOX(DLG_ESTRATEGIAS_CHECK_BORRAR,DialogoSeleccionarEstrategia::clickBorrar)
    EVT_CHECKBOX(DLG_ESTRATEGIAS_CHECK_ADICIONAR,DialogoSeleccionarEstrategia::clickAdicionar)
END_EVENT_TABLE()                                      


DialogoSeleccionarEstrategia::DialogoSeleccionarEstrategia(int *e,
    int *f, int *f2,Proyecto *proy, wxWindow *parent, wxHtmlHelpController *ayuda)
    :wxDialog(parent,wxID_ANY,wxString(wxT("Prueba")))
{
  Est=e;
  Proy=proy;
  Flag=f;
  Flag2=f2;
  Ayuda=ayuda;

  ButtonOK                =new wxButton (this,DLG_ESTRATEGIAS_BTN_OK, wxT("OK"));
  ButtonCancelar          =new wxButton (this,DLG_ESTRATEGIAS_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda             =new wxButton (this,DLG_ESTRATEGIAS_BTN_AYUDA, wxT("Ayuda"));
  StaticEstrategias       =new wxStaticText (this,DLG_ESTRATEGIAS_STATIC_ESTRATEGIAS, wxT("Metodologóias"));
  ListBoxEstrategias      =new wxListBox (this,DLG_ESTRATEGIAS_LISTBOX_ESTRATEGIAS,wxPoint(20,20),wxSize(200,100), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
  CheckBorrar             =new wxCheckBox(this,DLG_ESTRATEGIAS_CHECK_BORRAR,wxT("Borrar"));
  CheckAdicionar          =new wxCheckBox(this,DLG_ESTRATEGIAS_CHECK_ADICIONAR,wxT("Adicionar"));
  CheckGeneralidades      =new wxCheckBox(this,DLG_ESTRATEGIAS_CHECK_GENERALIDADES,wxT("Generalidades"));

  wxBoxSizer *sizerEstrategias = new wxBoxSizer(wxVERTICAL);
  sizerEstrategias->Add(StaticEstrategias, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
  sizerEstrategias->Add(ListBoxEstrategias, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerCheck = new wxBoxSizer(wxHORIZONTAL);
    sizerCheck->Add(CheckBorrar, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerCheck->Add(CheckAdicionar, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerEstrategias, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(CheckGeneralidades, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerCheck, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoSeleccionarEstrategia::~DialogoSeleccionarEstrategia()
{
}

void DialogoSeleccionarEstrategia::llenarCuadro()
{
  ListBoxEstrategias->Clear();
  int i,tam;
  tam=Proy->Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxEstrategias->Append(Proy->Estrategias.Item(i).Nombre);
  }
  ListBoxEstrategias->SetSelection(0);

  CheckBorrar->SetValue(1);
  CheckAdicionar->SetValue(0);
  CheckGeneralidades->SetValue(1);
}

void DialogoSeleccionarEstrategia::clickBorrar(wxCommandEvent&)
{
  if(CheckBorrar->GetValue())
  {
    CheckAdicionar->SetValue(0);
  }else
  {
    CheckAdicionar->SetValue(1);
  }
}

void DialogoSeleccionarEstrategia::clickAdicionar(wxCommandEvent&)
{
  if(CheckAdicionar->GetValue())
  {
    CheckBorrar->SetValue(0);
  }else
  {
    CheckBorrar->SetValue(1);
  }
}

void DialogoSeleccionarEstrategia::cerrarOk(wxCommandEvent&)
{
  int n;
  n=ListBoxEstrategias->GetSelection();
  *Est=n;
  if(CheckBorrar->GetValue())
  {
    *Flag=1;
  }else
  {
    *Flag=0;
  }
  if(CheckGeneralidades->GetValue())
  {
    *Flag2=1;
  }else
  {
    *Flag2=0;
  }
  Close();
}

void DialogoSeleccionarEstrategia::cancelar(wxCommandEvent&)
{
  *Est=-1;
  *Flag=-1;
  Close();
}

void DialogoSeleccionarEstrategia::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Copiar Variables de una Metodología"));
}


