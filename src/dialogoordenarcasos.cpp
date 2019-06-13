/***************************************************************************
                          dialogoordenarcasos.cpp  -  description
                             -------------------
    begin                : mar sep 16 2003
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

#include "dialogoordenarcasos.h"

BEGIN_EVENT_TABLE(DialogoOrdenarCasos, wxDialog)
    EVT_BUTTON(DLG_ORDENCASO_BTN_ORDENAR, DialogoOrdenarCasos::ordenar)
    EVT_BUTTON(DLG_ORDENCASO_BTN_OK, DialogoOrdenarCasos::cerrarOk)
//    EVT_BUTTON(DLG_ORDENCASO_BTN_CANCELAR, DialogoOrdenarCasos::cancelar)
    EVT_BUTTON(DLG_ORDENCASO_BTN_AYUDA, DialogoOrdenarCasos::ayuda)
    EVT_LISTBOX(DLG_ORDENCASO_LISTBOX_ESTRATEGIAS,DialogoOrdenarCasos::llenarNodos)
    EVT_CHECKBOX(DLG_ORDENCASO_CHECKBOX_ASCENDENTE, DialogoOrdenarCasos::clickAscendente)
    EVT_CHECKBOX(DLG_ORDENCASO_CHECKBOX_DESCENDENTE, DialogoOrdenarCasos::clickDescendente)
END_EVENT_TABLE()                              


DialogoOrdenarCasos::DialogoOrdenarCasos(Proyecto *proy, wxWindow *parent, wxHtmlHelpController *ayuda):
    wxDialog(parent,wxID_ANY,wxString(wxT("Prueba")))
{
  Proy=proy;
  Ayuda=ayuda;

    ButtonOrdenar          =new wxButton(this,DLG_ORDENCASO_BTN_ORDENAR, wxT("Ordenar"));
    ButtonOK               =new wxButton(this,DLG_ORDENCASO_BTN_OK, wxT("OK"));
//    ButtonCancelar         =new wxButton(this,DLG_ORDENCASO_BTN_CANCEL, wxT("Cancelar"));
    ButtonAyuda            =new wxButton(this,DLG_ORDENCASO_BTN_AYUDA, wxT("Ayuda"));
    ListBoxEstrategias     =new wxListBox(this,DLG_ORDENCASO_LISTBOX_ESTRATEGIAS,wxPoint(0,0),wxSize(150, 80), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
    ListBoxNodos           =new wxListBox(this,DLG_ORDENCASO_LISTBOX_NODOS,wxPoint(0,0),wxSize(150, 80), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
    StaticEstrategias      =new wxStaticText(this,DLG_ORDENCASO_STATIC_ESTRATEGIAS, wxT("Metodologías"));
    StaticNodos            =new wxStaticText(this,DLG_ORDENCASO_STATIC_NODOS, wxT("Nodos"));
    CheckAlfabetico        =new wxCheckBox(this,DLG_ORDENCASO_CHECKBOX_ALFABETICO, wxT("Orden Alfabético"));
    CheckAscendente        =new wxCheckBox(this,DLG_ORDENCASO_CHECKBOX_ASCENDENTE, wxT("Ascendente"));
    CheckDescendente       =new wxCheckBox(this,DLG_ORDENCASO_CHECKBOX_DESCENDENTE, wxT("Descendente"));

  CheckAlfabetico->SetValue(1);
  CheckAscendente->SetValue(1);
  CheckDescendente->SetValue(0);

    wxBoxSizer *sizerEst = new wxBoxSizer(wxVERTICAL);
    sizerEst->Add(StaticEstrategias, 0, wxALIGN_CENTER | wxALL, 5);
    sizerEst->Add(ListBoxEstrategias, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerNod = new wxBoxSizer(wxVERTICAL);
    sizerNod->Add(StaticNodos, 0, wxALIGN_CENTER | wxALL, 5);
    sizerNod->Add(ListBoxNodos, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerListas = new wxBoxSizer(wxHORIZONTAL);
    sizerListas->Add(sizerEst, 0, wxALIGN_CENTER | wxALL, 5);
    sizerListas->Add(sizerNod, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerAlf = new wxBoxSizer(wxVERTICAL);
    sizerAlf->Add(CheckAlfabetico, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerOrden = new wxBoxSizer(wxVERTICAL);
    sizerOrden->Add(CheckAscendente, 0, wxALIGN_LEFT | wxALL, 0);
    sizerOrden->Add(CheckDescendente, 0, wxALIGN_LEFT | wxALL, 0);

    wxBoxSizer *sizerCheck = new wxBoxSizer(wxHORIZONTAL);
    sizerCheck->Add(sizerAlf, 0, wxALIGN_TOP | wxALL, 5);
    sizerCheck->Add(sizerOrden, 0, wxALIGN_TOP | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
//    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerListas, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerCheck, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(ButtonOrdenar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
    
}                                                             

DialogoOrdenarCasos::~DialogoOrdenarCasos()
{
}

void DialogoOrdenarCasos::llenarCuadro()
{
  ListBoxEstrategias->Clear();
  int i,tam;
  tam=Proy->Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=Proy->Estrategias.Item(i).Nombre;
    ListBoxEstrategias->Append(cad);
  }
  if(tam>0)
  {
    ListBoxEstrategias->SetSelection(0);
  }
  wxCommandEvent ev;
  llenarNodos(ev);
}

void DialogoOrdenarCasos::llenarNodos(wxCommandEvent&)
{
  ListBoxNodos->Clear();
  int i,tam;
  Estrategia *Est;
  int numEst;
  numEst=ListBoxEstrategias->GetSelection();
  if(numEst<0){return;}
  Est=&Proy->Estrategias.Item(numEst);
  ListaNodos Lista;
  Est->Grafo.llenarArreglo(&Lista);
  tam=Lista.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=Lista.Item(0).VarCalculada.Nombre;
    ListBoxNodos->Append(cad);
    Lista.Detach(0);
  }
  if(tam>0)
  {
    ListBoxNodos->SetSelection(0);
  }
}

void DialogoOrdenarCasos::clickAscendente(wxCommandEvent&)
{
  if(CheckAscendente->GetValue())
  {
    CheckDescendente->SetValue(FALSE);
  }else
  {
    CheckDescendente->SetValue(TRUE);
  }
}

void DialogoOrdenarCasos::clickDescendente(wxCommandEvent&)
{
  if(CheckDescendente->GetValue())
  {
    CheckAscendente->SetValue(FALSE);
  }else
  {
    CheckAscendente->SetValue(TRUE);
  }
}


void DialogoOrdenarCasos::ordenar(wxCommandEvent&)
{
  if(CheckAlfabetico->GetValue())
  {
    Proy->ordenNombre(CheckDescendente->GetValue());
    wxString cad=wxT("Se han ordenado los casos alfabéticamente");
    wxMessageBox(cad, GENERAL_ADVERTENCIA, wxOK | wxICON_INFORMATION, this);
  }else
  {
    Estrategia *Est;
    NodoCalculo *Nodo;
    int numEst,numNodo;
    numEst=ListBoxEstrategias->GetSelection();
    numNodo=ListBoxNodos->GetSelection();
    if(numEst*numNodo < 0){return;}
    Est=&Proy->Estrategias.Item(numEst);
    Nodo=Est->Grafo.buscarNodo(ListBoxNodos->GetStringSelection());
    if(Nodo==NULL){return;}
    float opt,r;
    opt=Proy->Optimismo;
    r=Proy->Representatividad;
    Proy->ordenValor(Nodo,opt,r,CheckDescendente->GetValue());
    wxString cad=wxT("Se han ordenado los casos");
    wxMessageBox(cad, GENERAL_ADVERTENCIA, wxOK | wxICON_INFORMATION, this);
  }
}

void DialogoOrdenarCasos::cerrarOk(wxCommandEvent&)
{
  Close();
}

void DialogoOrdenarCasos::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Ordenar los Casos"));
}
