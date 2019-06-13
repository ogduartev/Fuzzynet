/***************************************************************************
                          dialogomodificador.cpp  -  description
                             -------------------
    begin                : ago 2 2003
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

#include "dialogomodificador.h"

BEGIN_EVENT_TABLE(DialogoModificador, wxDialog)
    EVT_BUTTON(DLG_MODIFICADOR_BTN_OK, DialogoModificador::cerrarOk)
    EVT_BUTTON(DLG_MODIFICADOR_BTN_CANCEL, DialogoModificador::cancelar)
    EVT_BUTTON(DLG_MODIFICADOR_BTN_AYUDA, DialogoModificador::ayuda)
    EVT_LISTBOX(DLG_MODIFICADOR_LISTBOX_MODIFICADOR, DialogoModificador::clickModificador)
END_EVENT_TABLE()

DialogoModificador::DialogoModificador(VariableLinguistica *var,
          Proyecto *proy, wxWindow *parent,const wxString& title, wxHtmlHelpController *ayuda)
          :wxDialog(parent,-1,title)
{
  Proy=proy;
  Ayuda=ayuda;

  VarTemp=var;
  Var=*VarTemp;

  SetTitle(wxT("Autodefinir Variable Lingüística"));

  ButtonOK                         =new wxButton(this,DLG_MODIFICADOR_BTN_OK, wxT("OK"));
  ButtonCancelar                 =new wxButton(this,DLG_MODIFICADOR_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda                    =new wxButton (this,DLG_MODIFICADOR_BTN_AYUDA, wxT("Ayuda"));
  StaticCadena                =new wxStaticText(this,DLG_MODIFICADOR_STATIC_CADENA, wxT("Etiqueta"));
  ListBoxModificador                  =new wxListBox (this,DLG_MODIFICADOR_LISTBOX_MODIFICADOR);

  wxString cad;
  Var.strEtiqueta(&cad);
  StaticCadena->SetLabel(cad);

  ListBoxModificador->Append(wxT("Sin Modificador"));
  ListBoxModificador->Append(wxT("A lo sumo"));
  ListBoxModificador->Append(wxT("Por lo menos"));
  ListBoxModificador->Append(wxT("Nada"));
  ListBoxModificador->Append(wxT("Cualquier cosa"));
  ListBoxModificador->SetSelection(Var.Modificador);
  
    wxBoxSizer *sizerEtiqueta = new wxBoxSizer(wxVERTICAL);
    sizerEtiqueta->Add(StaticCadena, 0, wxALIGN_LEFT | wxALL, 5);
    sizerEtiqueta->Add(ListBoxModificador, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerEtiqueta, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

//    llenarCuadro();
}

DialogoModificador::~DialogoModificador()
{
}

void DialogoModificador::clickModificador(wxCommandEvent&)
{
  Var.Modificador=ListBoxModificador->GetSelection();
  wxString cad;
  Var.strEtiqueta(&cad);
  StaticCadena->SetLabel(cad);
}

void DialogoModificador::cerrarOk(wxCommandEvent&)
{
  *VarTemp=Var;
  Close();
}

void DialogoModificador::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoModificador::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición de Modificadores Lingüísticos"));
}


