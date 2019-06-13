/***************************************************************************
                          paginalistados.cpp  -  description
                             -------------------
    begin                : abr 5 2004
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

#include "paginalistados.h"

BEGIN_EVENT_TABLE(PaginaListados, wxPanel)
    EVT_BUTTON(DLG_PAGLIS_BTN_AGREGAR, PaginaListados::agregar)
    EVT_BUTTON(DLG_PAGLIS_BTN_ELIMINAR, PaginaListados::eliminar)
    EVT_BUTTON(DLG_PAGLIS_BTN_AGREGARTODO, PaginaListados::agregarTodo)
    EVT_BUTTON(DLG_PAGLIS_BTN_ELIMINARTODO, PaginaListados::eliminarTodo)
    EVT_BUTTON(DLG_PAGLIS_BTN_SUBIR, PaginaListados::subir)
    EVT_BUTTON(DLG_PAGLIS_BTN_BAJAR, PaginaListados::bajar)
END_EVENT_TABLE()

PaginaListados::PaginaListados(wxArrayString origen,
                wxWindow* parent)
                :wxPanel(parent,-1)
{
  Origen=origen;

  ButtonAgregar           =new wxButton(this,DLG_PAGLIS_BTN_AGREGAR,wxT(">>"));
  ButtonEliminar           =new wxButton(this,DLG_PAGLIS_BTN_ELIMINAR,wxT("<<"));
  ButtonAgregarTodo    =new wxButton(this,DLG_PAGLIS_BTN_AGREGARTODO,wxT(">>>>"));
  ButtonEliminarTodo    =new wxButton(this,DLG_PAGLIS_BTN_ELIMINARTODO,wxT("<<<<"));
  ButtonSubir               =new wxButton(this,DLG_PAGLIS_BTN_SUBIR,wxT("Subir"));
  ButtonBajar               =new wxButton(this,DLG_PAGLIS_BTN_BAJAR,wxT("Bajar"));
  StaticOrigen              =new wxStaticText(this,DLG_PAGLIS_STATIC_ORIGEN,wxT("Disponibles"));
  StaticDestino             =new wxStaticText(this,DLG_PAGLIS_STATIC_DESTINO,wxT("Seleccionados"));
  ListaOrigen               =new wxListBox (this,DLG_PAGLIS_LISTBOX_ORIGEN,wxDefaultPosition,wxDefaultSize, 0,0,wxLB_EXTENDED | wxLB_ALWAYS_SB);
  ListaDestino              =new wxListBox (this,DLG_PAGLIS_LISTBOX_DESTINO,wxDefaultPosition,wxDefaultSize,0,0,wxLB_EXTENDED | wxLB_ALWAYS_SB);
  ListaOrigen->SetMinSize(wxSize(150,200));
  ListaDestino->SetMinSize(wxSize(150,200));

  wxBoxSizer *sizerOrigen = new wxBoxSizer(wxVERTICAL);
  sizerOrigen->Add(StaticOrigen, 0, wxALIGN_CENTER | wxALL, 5);
  sizerOrigen->Add(ListaOrigen, 0, wxALIGN_CENTER | wxALL, 5);

  wxBoxSizer *sizerButOri = new wxBoxSizer(wxVERTICAL);
  sizerButOri->Add(ButtonAgregar, 0, wxALIGN_CENTER | wxALL, 5);
  sizerButOri->Add(ButtonEliminar, 0, wxALIGN_CENTER | wxALL, 5);
  sizerButOri->Add(ButtonAgregarTodo, 0, wxALIGN_CENTER | wxALL, 5);
  sizerButOri->Add(ButtonEliminarTodo, 0, wxALIGN_CENTER | wxALL, 5);

  wxBoxSizer *sizerDestino = new wxBoxSizer(wxVERTICAL);
  sizerDestino->Add(StaticDestino, 0, wxALIGN_CENTER | wxALL, 5);
  sizerDestino->Add(ListaDestino, 0, wxALIGN_CENTER | wxALL, 5);

  wxBoxSizer *sizerButDes = new wxBoxSizer(wxVERTICAL);
  sizerButDes->Add(ButtonSubir, 0, wxALIGN_CENTER | wxALL, 5);
  sizerButDes->Add(ButtonBajar, 0, wxALIGN_CENTER | wxALL, 5);

  wxBoxSizer *sizerTotal = new wxBoxSizer(wxHORIZONTAL);
  sizerTotal->Add(sizerOrigen, 0, wxALIGN_CENTER | wxALL, 5);
  sizerTotal->Add(sizerButOri, 0, wxALIGN_CENTER | wxALL, 5);
  sizerTotal->Add(sizerDestino, 0, wxALIGN_CENTER | wxALL, 5);
  sizerTotal->Add(sizerButDes, 0, wxALIGN_CENTER | wxALL, 5);

  SetAutoLayout(TRUE);
  SetSizer(sizerTotal);

  sizerTotal->SetSizeHints(this);
  sizerTotal->Fit(this);

  llenarCuadro();
}

PaginaListados::~PaginaListados()
{
}

void PaginaListados::llenarCuadro()
{
  ListaOrigen->Clear();
  int i,tam;
  tam=Origen.GetCount();
  for(i=0;i<tam;i++)
  {
    ListaOrigen->Append(Origen.Item(i));
  }
}

void PaginaListados::agregar(wxCommandEvent&)
{
  wxArrayInt Sel;
  ListaOrigen->GetSelections(Sel);
  int i,tam;
  tam=Sel.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=Origen.Item(Sel.Item(i));
    if(ListaDestino->FindString(cad)<0)
    {
      Destino.Add(cad);
      ListaDestino->Append(cad);
    }
  }
}

void PaginaListados::eliminar(wxCommandEvent&)
{
  wxArrayInt Sel;
  ListaDestino->GetSelections(Sel);
  int i,tam;
  tam=Sel.GetCount();
  for(i=0;i<tam;i++)
  {
    Destino.RemoveAt(Sel.Item(i));
    ListaDestino->Delete(Sel.Item(i));
  }
}

void PaginaListados::agregarTodo(wxCommandEvent&)
{
  int i,tam;
  tam=Origen.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=Origen.Item(i);
    if(ListaDestino->FindString(cad)<0)
    {
      Destino.Add(cad);
      ListaDestino->Append(cad);
    }
  }
}

void PaginaListados::eliminarTodo(wxCommandEvent&)
{
  int i,tam;
  tam=Destino.GetCount();
  for(i=0;i<tam;i++)
  {
    Destino.RemoveAt(0);
    ListaDestino->Delete(0);
  }
}

// Solo se sube el primer item seleccionado
// si se tomaran más items, se desordena la lista
void PaginaListados::subir(wxCommandEvent&)
{
  wxArrayInt Sel;
  ListaDestino->GetSelections(Sel);
  int i,tam;
  tam=Sel.GetCount();
  if(tam<1){return;}

    int posIni,posFin;
    wxString cad;
    posIni=Sel.Item(0);
    cad=Destino.Item(posIni);
    if(posIni>0)
    {
      posFin=posIni-1;
      Destino.RemoveAt(posIni);
      ListaDestino->Delete(posIni);
      Destino.Insert(cad,posFin);
      ListaDestino->InsertItems(1,&cad,posFin);
      for(i=0;i<tam;i++)
      {
        ListaDestino->Deselect(Sel.Item(i));
      }
      ListaDestino->SetSelection(posFin);
    }
}

// Solo se baja el primer item seleccionado
// si se tomaran más items, se desordena la lista
void PaginaListados::bajar(wxCommandEvent&)
{
  wxArrayInt Sel;
  ListaDestino->GetSelections(Sel);
  int i,tam;
  tam=Sel.GetCount();
  if(tam<1){return;}

    int posIni,posFin;
    wxString cad;
    posIni=Sel.Item(0);
    cad=Destino.Item(posIni);
    if(posIni<Destino.GetCount()-1)
    {
      posFin=posIni+1;
      Destino.RemoveAt(posIni);
      ListaDestino->Delete(posIni);
      Destino.Insert(cad,posFin);
      ListaDestino->InsertItems(1,&cad,posFin);
      for(i=0;i<tam;i++)
      {
        ListaDestino->Deselect(Sel.Item(i));
      }
      ListaDestino->SetSelection(posFin);
    }
}

