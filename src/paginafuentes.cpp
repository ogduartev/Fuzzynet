/***************************************************************************
                          paginafuentes.cpp  -  description
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

#include "paginafuentes.h"

BEGIN_EVENT_TABLE(PaginaFuentes, wxPanel)
    EVT_PAINT(PaginaFuentes::OnPaint)
    EVT_BUTTON(DLG_PAGFTE_BTN_EDITAR, PaginaFuentes::editarFte)
    EVT_BUTTON(DLG_PAGFTE_BTN_APLICAR, PaginaFuentes::aplicar)
    EVT_LISTBOX(DLG_PAGFTE_LISTBOX, PaginaFuentes::seleccionarFte)
END_EVENT_TABLE()


PaginaFuentes::PaginaFuentes(MiCanvas *canvas,
          wxWindow *parent,const wxString& title)
          :wxPanel(parent,-1)
{
  Canvas=canvas;
  recargar();
//  SetTitle(wxT("Configuración de la Interfaz"));

  crearPagFuentes();
}

PaginaFuentes::~PaginaFuentes()
{
}

void PaginaFuentes::crearPagFuentes()
{
  wxPanel *PagFuentes = this;
  ButtonEditarFte  =new wxButton (PagFuentes,DLG_PAGFTE_BTN_EDITAR, wxT("Editar"));
  ButtonAplicarFte =new wxButton (PagFuentes,DLG_PAGFTE_BTN_APLICAR, wxT("Aplicar"));
  ListBoxItemsFte  =new wxListBox (PagFuentes,DLG_PAGFTE_LISTBOX);
  ListBoxItemsFte->SetMinSize(wxSize(200,200));

  ListBoxItemsFte->Clear();
  int i,tam=0;
  tam=ListaFte.Nombres.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxItemsFte->Append(ListaFte.Nombres.Item(i));
  }
  if(tam>0)
  {
    ListBoxItemsFte->SetSelection(0);
  }


   sizerDibujoFte = new wxBoxSizer(wxVERTICAL);
   sizerDibujoFte->Add(40,20, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButSup = new wxBoxSizer(wxVERTICAL);
    sizerButSup->Add(sizerDibujoFte, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButSup->Add(ButtonEditarFte, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButSup->Add(ButtonAplicarFte, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxHORIZONTAL);
    sizerTotal->Add(ListBoxItemsFte, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButSup, 0, wxALIGN_CENTER | wxALL, 5);

  PagFuentes->SetAutoLayout(TRUE);
  PagFuentes->SetSizer(sizerTotal);

  sizerTotal->SetSizeHints(PagFuentes);
  sizerTotal->Fit(PagFuentes);

  Refresh();
}

void PaginaFuentes::recargar()
{
  ListaTempFte=&Canvas->Fuentes;
  ListaFte=*ListaTempFte;
}

void PaginaFuentes::editarFte(wxCommandEvent&)
{
  int item;
  item=ListBoxItemsFte->GetSelection();
  if(item<0){return;}
  wxFont fnt;
  wxFont fntRet;
  wxFontData data;
  wxFontDialog *dialog2;

  fnt = ListaFte.Fuentes.Item(item);
  data.SetInitialFont(fnt);
  dialog2 = new wxFontDialog(this,data);
  dialog2->SetTitle(ListaFte.Nombres.Item(item));
  if (dialog2->ShowModal() == wxID_OK)
  {
    wxFontData retData = dialog2->GetFontData();
    fntRet = retData.GetChosenFont();
    if(fntRet.Ok())
    {
      ListaFte.Fuentes.Item(item)=fntRet;
    }
  }
  delete dialog2;
  Refresh();
}


void PaginaFuentes::OnPaint(wxPaintEvent&)
{
  pintarFte();
}

void PaginaFuentes::aplicar(wxCommandEvent&)
{
  *ListaTempFte=ListaFte;
  Canvas->Refresh();
}

void PaginaFuentes::pintarFte()
{
  wxPaintDC dc(this);
  wxPoint origen=sizerDibujoFte->GetPosition();
  wxSize tamano=sizerDibujoFte->GetSize();

  wxBrush Brush;
  wxPen Pen;
  int item;
  item=ListBoxItemsFte->GetSelection();
  Brush.SetColour(*wxWHITE);
  dc.SetBrush (Brush);
  dc.DrawRectangle(origen,tamano);
  Pen.SetWidth(2);
  Pen.SetColour(*wxBLACK);
  dc.SetPen (Pen);
  dc.DrawRectangle(origen,tamano);
  dc.SetFont(ListaFte.Fuentes.Item(item));
  wxString cad=wxT("Abc");
  dc.DrawText(cad,origen);
}

void PaginaFuentes::seleccionarFte(wxCommandEvent&)
{
  Refresh();
}

