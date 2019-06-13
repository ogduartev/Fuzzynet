/***************************************************************************
                          paginadimensiones.cpp  -  description
                             -------------------
    begin                : mar 24 2004
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

#include "paginadimensiones.h"

BEGIN_EVENT_TABLE(PaginaDimensiones, wxPanel)
//    EVT_PAINT(PaginaDimensiones::OnPaint)
    EVT_BUTTON(DLG_PAGDIM_BTN_APLICAR, PaginaDimensiones::aplicar)
    EVT_LISTBOX(DLG_PAGDIM_LISTBOX, PaginaDimensiones::seleccionarDim)
END_EVENT_TABLE()


PaginaDimensiones::PaginaDimensiones(MiCanvas *canvas,
          wxWindow *parent,const wxString& title)
          :wxPanel(parent,-1)
{
  Canvas=canvas;
  recargar();
//  SetTitle(wxT("Configuración de la Interfaz"));

  crearPagDimensiones();
}

PaginaDimensiones::~PaginaDimensiones()
{
}

void PaginaDimensiones::crearPagDimensiones()
{
  wxPanel *PagDimensiones = this;
  ButtonAplicarDim =new wxButton (PagDimensiones,DLG_PAGDIM_BTN_APLICAR, wxT("Aplicar"));
  ListBoxItemsDim  =new wxListBox (PagDimensiones,DLG_PAGDIM_LISTBOX);
  ListBoxItemsDim->SetSize(200,200);
  SpinDim          =new wxSpinCtrl (PagDimensiones,DLG_PAGDIM_SPIN);
  SpinDim->SetSize(100,20);
  SpinDim->SetRange(0,2000);

  ListBoxItemsDim->Clear();
  int i,tam=0;
  tam=ListaDim.Nombres.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxItemsDim->Append(ListaDim.Nombres.Item(i));
  }
  if(tam>0)
  {
    ListBoxItemsDim->SetSelection(0);
  }


    wxBoxSizer *sizerButSup = new wxBoxSizer(wxVERTICAL);
    sizerButSup->Add(SpinDim, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButSup->Add(ButtonAplicarDim, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxHORIZONTAL);
    sizerTotal->Add(ListBoxItemsDim, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButSup, 0, wxALIGN_CENTER | wxALL, 5);

  PagDimensiones->SetAutoLayout(TRUE);
  PagDimensiones->SetSizer(sizerTotal);

  sizerTotal->SetSizeHints(PagDimensiones);
  sizerTotal->Fit(PagDimensiones);

  Refresh();
}

void PaginaDimensiones::recargar()
{
  ListaTempDim=&Canvas->Dimensiones;
  ListaDim=*ListaTempDim;
}

void PaginaDimensiones::OnPaint(/*wxPaintEvent& event*/)
{
  pintarDim();
}

void PaginaDimensiones::aplicar(wxCommandEvent&)
{
  int item;
  item=ListBoxItemsDim->GetSelection();
  if(item<0){return;}
  int d;
  d=SpinDim->GetValue();
  ListaDim.Dimensiones.Item(item)=d;
  *ListaTempDim=ListaDim;
  Canvas->Refresh();
}

void PaginaDimensiones::pintarDim()
{
  int item;
  item=ListBoxItemsDim->GetSelection();
  if(item<0){return;}
  SpinDim->SetValue(Canvas->Dimensiones.Dimensiones.Item(item));
}

void PaginaDimensiones::seleccionarDim(wxCommandEvent&)
{
  pintarDim();
}

