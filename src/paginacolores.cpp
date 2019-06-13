/***************************************************************************
                          paginacolores.cpp  -  description
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

#include "paginacolores.h"

BEGIN_EVENT_TABLE(PaginaColores, wxPanel)
    EVT_PAINT(PaginaColores::OnPaint)
    EVT_BUTTON(DLG_PAGCOL_BTN_EDITAR, PaginaColores::editarCol)
    EVT_BUTTON(DLG_PAGCOL_BTN_APLICAR, PaginaColores::aplicar)
    EVT_LISTBOX(DLG_PAGCOL_LISTBOX, PaginaColores::seleccionarCol)
END_EVENT_TABLE()


PaginaColores::PaginaColores(MiCanvas *canvas,
          wxWindow *parent,const wxString& title)
          :wxPanel(parent,-1)
{
  Canvas=canvas;
  recargar();
//  SetTitle(wxT("Configuración de la Interfaz"));

  crearPagColores();
}

PaginaColores::~PaginaColores()
{
}

void PaginaColores::crearPagColores()
{
  wxPanel *PagColores = this;
  ButtonEditarCol  =new wxButton (PagColores,DLG_PAGCOL_BTN_EDITAR, wxT("Editar"));
  ButtonAplicarCol =new wxButton (PagColores,DLG_PAGCOL_BTN_APLICAR, wxT("Aplicar"));
  ListBoxItemsCol  =new wxListBox (PagColores,DLG_PAGCOL_LISTBOX);
  ListBoxItemsCol->SetSize(200,200);

  ListBoxItemsCol->Clear();
  int i,tam=0;
  tam=ListaCol.Nombres.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxItemsCol->Append(ListaCol.Nombres.Item(i));
  }
  if(tam>0)
  {
    ListBoxItemsCol->SetSelection(0);
  }


    sizerDibujoCol = new wxBoxSizer(wxVERTICAL);
    sizerDibujoCol->Add(40,20, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButSup = new wxBoxSizer(wxVERTICAL);
    sizerButSup->Add(sizerDibujoCol, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButSup->Add(ButtonEditarCol, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButSup->Add(ButtonAplicarCol, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxHORIZONTAL);
    sizerTotal->Add(ListBoxItemsCol, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButSup, 0, wxALIGN_CENTER | wxALL, 5);

  PagColores->SetAutoLayout(TRUE);
  PagColores->SetSizer(sizerTotal);

  sizerTotal->SetSizeHints(PagColores);
  sizerTotal->Fit(PagColores);

  Refresh();
}

void PaginaColores::recargar()
{
  ListaTempCol=&Canvas->Colores;
  ListaCol=*ListaTempCol;
}

void PaginaColores::editarCol(wxCommandEvent&)
{
  int item;
  item=ListBoxItemsCol->GetSelection();
  if(item<0){return;}
  wxColour col;
  wxColourDialog *dialog1;

  col = ListaCol.Colores.Item(item);
  Canvas->data.SetColour(col);
  dialog1=new wxColourDialog(this, &Canvas->data);
  dialog1->SetTitle(ListaCol.Nombres.Item(item));
  if (dialog1->ShowModal() == wxID_OK)
  {
      Canvas->data = dialog1->GetColourData();
      col=Canvas->data.GetColour();
      ListaCol.Colores.Item(item)=col;
  }
  delete dialog1;
  Refresh();
}


void PaginaColores::OnPaint(wxPaintEvent&)
{
  pintarCol();
}

void PaginaColores::aplicar(wxCommandEvent&)
{
  *ListaTempCol=ListaCol;
  Canvas->Refresh();
}

void PaginaColores::pintarCol()
{
  wxPaintDC dc(this);
  wxPoint origen=sizerDibujoCol->GetPosition();
  wxSize tamano=sizerDibujoCol->GetSize();

  wxBrush Brush;
  wxPen Pen;
  int item;
  item=ListBoxItemsCol->GetSelection();
  if(item<0){return;}
  Brush.SetColour(ListaCol.Colores.Item(item));
  dc.SetBrush (Brush);
  dc.DrawRectangle(origen,tamano);
  Pen.SetWidth(2);
  Pen.SetColour(*wxBLACK);
  dc.SetPen (Pen);
  dc.DrawRectangle(origen,tamano);
}

void PaginaColores::seleccionarCol(wxCommandEvent&)
{
  Refresh();
}
