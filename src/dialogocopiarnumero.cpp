/***************************************************************************
                          dialogocopiarnumero.cpp  -  description
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

#include "dialogocopiarnumero.h"

BEGIN_EVENT_TABLE(DialogoCopiarNumero, wxDialog)
    EVT_BUTTON(DLG_NUMEROCOPIAR_BTN_COPIAR, DialogoCopiarNumero::copiar)
    EVT_BUTTON(DLG_NUMEROCOPIAR_BTN_OK, DialogoCopiarNumero::cerrarOk)
    EVT_BUTTON(DLG_NUMEROCOPIAR_BTN_CANCEL, DialogoCopiarNumero::cancelar)
    EVT_BUTTON(DLG_NUMEROCOPIAR_BTN_AYUDA, DialogoCopiarNumero::ayuda)
    EVT_LISTBOX(DLG_NUMEROCOPIAR_LISTBOX_ESTRATEGIAS,DialogoCopiarNumero::llenarNodos)
END_EVENT_TABLE()

DialogoCopiarNumero::DialogoCopiarNumero(NumeroDifuso *num,
                      Proyecto *proy, wxWindow* parent,wxHtmlHelpController *ayuda)
                     :wxDialog(parent,wxID_ANY,wxString(wxT("Prueba")))
{
  Proy=proy;
  Num.copiar(num);
  NumTemp=num;
  Ayuda=ayuda;

  SetTitle(wxT("Copiar Número Difuso"));

  ButtonCopiar         =new wxButton (this,DLG_NUMEROCOPIAR_BTN_COPIAR, wxT("Copiar"));
  ButtonOK             =new wxButton (this,DLG_NUMEROCOPIAR_BTN_OK, wxT("OK"));
  ButtonCancelar       =new wxButton (this,DLG_NUMEROCOPIAR_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda          =new wxButton (this,DLG_NUMEROCOPIAR_BTN_AYUDA, wxT("Ayuda"));
  ListBoxEstrategias   =new wxListBox (this,DLG_NUMEROCOPIAR_LISTBOX_ESTRATEGIAS,wxPoint(20,20),wxSize(200,100), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
  ListBoxNodos         =new wxListBox (this,DLG_NUMEROCOPIAR_LISTBOX_NODOS,wxPoint(20,20),wxSize(200,100), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
  ListBoxCasos         =new wxListBox (this,DLG_NUMEROCOPIAR_LISTBOX_CASOS,wxPoint(20,20),wxSize(200,100), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
  StaticEstrategias    =new wxStaticText (this,DLG_NUMEROCOPIAR_STATIC_ESTRATEGIAS, wxT("Metodologías"));
  StaticNodos          =new wxStaticText (this,DLG_NUMEROCOPIAR_STATIC_NODOS, wxT("Nodos"));
  StaticCasos          =new wxStaticText (this,DLG_NUMEROCOPIAR_STATIC_CASOS, wxT("Casos"));
  StaticSeleccion      =new wxStaticText (this,DLG_NUMEROCOPIAR_STATIC_SELECCION, wxT("Selección:"));

  wxBoxSizer *sizerEstrategias = new wxBoxSizer(wxVERTICAL);
  sizerEstrategias->Add(StaticEstrategias, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 5);
  sizerEstrategias->Add(ListBoxEstrategias, 0, wxALIGN_CENTER |  wxTOP | wxBOTTOM, 5);

  wxBoxSizer *sizerNodos = new wxBoxSizer(wxVERTICAL);
  sizerNodos->Add(StaticNodos, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 5);
  sizerNodos->Add(ListBoxNodos, 0, wxALIGN_CENTER |  wxTOP | wxBOTTOM, 5);

  wxBoxSizer *sizerCasos = new wxBoxSizer(wxVERTICAL);
  sizerCasos->Add(StaticCasos, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 5);
  sizerCasos->Add(ListBoxCasos, 0, wxALIGN_CENTER |  wxTOP | wxBOTTOM, 5);

  wxBoxSizer *sizerListas = new wxBoxSizer(wxHORIZONTAL);
  sizerListas->Add(sizerEstrategias, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
  sizerListas->Add(sizerNodos, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
  sizerListas->Add(sizerCasos, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

  wxBoxSizer *sizerSeleccion = new wxBoxSizer(wxVERTICAL);
  sizerSeleccion->Add(StaticSeleccion, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 5);
  sizerSeleccion->Add(ButtonCopiar, 0, wxALIGN_CENTER |  wxTOP | wxBOTTOM, 5);

  wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
  sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
  sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
  sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

  wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
  sizerTotal->Add(sizerListas, 0, wxALIGN_CENTER | wxALL, 5);
  sizerTotal->Add(sizerSeleccion, 0, wxALIGN_CENTER | wxALL, 5);
  sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

  SetAutoLayout(TRUE);
  SetSizer(sizerTotal);

  sizerTotal->SetSizeHints(this);
  sizerTotal->Fit(this);

  llenarCuadro();
  wxCommandEvent ev;
  llenarNodos(ev);
                          
}

void DialogoCopiarNumero::llenarCuadro()
{
  ListBoxEstrategias->Clear();
  int i,tam;
  tam=Proy->Estrategias.GetCount();
//  ListBoxEstrategias->Append(wxT("Sin Selección"));
  for(i=0;i<tam;i++)
  {
    ListBoxEstrategias->Append(Proy->Estrategias.Item(i).Nombre);
  }
  ListBoxEstrategias->SetSelection(0);

  ListBoxCasos->Clear();
  tam=Proy->Casos.GetCount();
//  ListBoxCasos->Append(wxT("Sin Selección"));
  for(i=0;i<tam;i++)
  {
    ListBoxCasos->Append(Proy->Casos.Item(i).Nombre);
  }
  ListBoxCasos->SetSelection(0);

}

void DialogoCopiarNumero::llenarNodos(wxCommandEvent&)
{
  ListBoxNodos->Clear();
  Estrategia *Est;
  Est=&Proy->Estrategias.Item(ListBoxEstrategias->GetSelection());

  ListaNodos Lista;
  Est->Grafo.llenarArreglo(&Lista);
  int i,tam;
  tam=Lista.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxNodos->Append(Lista.Item(0).VarCalculada.Nombre);
    Lista.Detach(0);
  }
  ListBoxNodos->SetSelection(0);
}

DialogoCopiarNumero::~DialogoCopiarNumero()
{
}

void DialogoCopiarNumero::copiar(wxCommandEvent&)
{
  int NumEst,NumCas;
  wxString NomNodo;
  NumEst=ListBoxEstrategias->GetSelection();
  NomNodo=ListBoxNodos->GetStringSelection();
  NumCas=ListBoxCasos->GetSelection();

  NumeroDifuso *Resultado;
  ///////
  Caso *cas;
  cas=&Proy->Casos.Item(NumCas);
  Resultado=Proy->Estrategias.Item(NumEst).Grafo.buscarNodo(NomNodo)->calcularCaso(cas);
  ///////
  Num.copiar(Resultado);
  delete Resultado;

  wxString cad;
  cad << wxT("Selección: ") << ListBoxEstrategias->GetStringSelection();
  cad << wxT(" - ") << NomNodo << wxT(" - ");
  cad <<  ListBoxCasos->GetStringSelection();

  StaticSeleccion->SetLabel(cad);
}

void DialogoCopiarNumero::cerrarOk(wxCommandEvent&)
{
  NumTemp->copiar(&Num);
  Close();
}

void DialogoCopiarNumero::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoCopiarNumero::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Copiar Números Difusos"));
}


