/***************************************************************************
                          paginaselecciones.cpp  -  description
                             -------------------
    begin                : jue mar 25 2004
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

#include "paginaselecciones.h"

BEGIN_EVENT_TABLE(PaginaSelecciones, wxPanel)
    EVT_BUTTON(DLG_PAGSEL_BTN_APLICAR, PaginaSelecciones::aplicar)
    EVT_LISTBOX(DLG_PAGSEL_LISTBOX, PaginaSelecciones::seleccionarSel)
END_EVENT_TABLE()


PaginaSelecciones::PaginaSelecciones(MiCanvas *canvas,
          wxWindow *parent,const wxString& title)
          :wxPanel(parent,-1)
{
  Canvas=canvas;
  recargar();
//  SetTitle(wxT("Configuración de la Interfaz"));

  crearPagSelecciones();
}

PaginaSelecciones::~PaginaSelecciones()
{
}

void PaginaSelecciones::crearPagSelecciones()
{
  wxPanel *PagSelecciones = this;
  ButtonAplicarSel =new wxButton (PagSelecciones,DLG_PAGSEL_BTN_APLICAR, wxT("Aplicar"));
  ListBoxItemsSel  =new wxListBox (PagSelecciones,DLG_PAGSEL_LISTBOX);
  ListBoxItemsSel->SetMinSize(wxSize(200,200));
  ComboSel         =new wxComboBox (PagSelecciones,DLG_PAGSEL_COMBOBOX);
  ComboSel->SetMinSize(wxSize(120,60));

  ListBoxItemsSel->Clear();
  int i,tam=0;
  tam=ListaSel.Nombres.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxItemsSel->Append(ListaSel.Nombres.Item(i));
  }
  if(tam>0)
  {
    ListBoxItemsSel->SetSelection(0);
  }


    wxBoxSizer *sizerButSup = new wxBoxSizer(wxVERTICAL);
    sizerButSup->Add(ComboSel, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButSup->Add(ButtonAplicarSel, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxHORIZONTAL);
    sizerTotal->Add(ListBoxItemsSel, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButSup, 0, wxALIGN_CENTER | wxALL, 5);

  PagSelecciones->SetAutoLayout(TRUE);
  PagSelecciones->SetSizer(sizerTotal);

  sizerTotal->SetSizeHints(PagSelecciones);
  sizerTotal->Fit(PagSelecciones);

  pintarSel();
}

void PaginaSelecciones::recargar()
{
  ListaTempSel=&Canvas->Selecciones;
  ListaSel=*ListaTempSel;
//  pintarSel();
}


void PaginaSelecciones::aplicar(wxCommandEvent&)
{
  int item;
  item=ListBoxItemsSel->GetSelection();
  if(item<0){return;}
  int d;
  d=ComboSel->GetSelection();
  ListaSel.Selecciones.Item(item)=d;
  *ListaTempSel=ListaSel;
  pintarSel();
  Canvas->llenarRegiones();
  Canvas->Refresh();
}

void PaginaSelecciones::pintarSel()
{
  int item=0;
  item=ListBoxItemsSel->GetSelection();
  if(item<0){return;}
  ComboSel->Clear();
  int i,tam;
  tam=ListaSel.Opciones.Item(item).GetCount();
  for(i=0;i<tam;i++)
  {
    ComboSel->Append(ListaSel.Opciones.Item(item).Item(i));
  }
  if(tam>0 && tam > ListaSel.Selecciones.Item(item))
  {
    ComboSel->SetSelection(ListaSel.Selecciones.Item(item));
  }
}

void PaginaSelecciones::seleccionarSel(wxCommandEvent&)
{
  pintarSel();
}

