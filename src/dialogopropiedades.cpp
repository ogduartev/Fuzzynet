/***************************************************************************
                          dialogopropiedades.cpp  -  description
                             -------------------
    begin                : lun abr 5 2004
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

#include "dialogopropiedades.h"

BEGIN_EVENT_TABLE(DialogoPropiedades, wxDialog)
    EVT_BUTTON(DLG_PROPIEDADES_BTN_ADICIONAR, DialogoPropiedades::adicionar)
    EVT_BUTTON(DLG_PROPIEDADES_BTN_EDITAR, DialogoPropiedades::editar)
    EVT_BUTTON(DLG_PROPIEDADES_BTN_BORRAR, DialogoPropiedades::borrar)
    EVT_BUTTON(DLG_PROPIEDADES_BTN_ACTUALIZAR, DialogoPropiedades::actualizar)
    EVT_BUTTON(DLG_PROPIEDADES_BTN_OK, DialogoPropiedades::cerrarOk)
    EVT_BUTTON(DLG_PROPIEDADES_BTN_CANCEL, DialogoPropiedades::cancelar)
    EVT_BUTTON(DLG_PROPIEDADES_BTN_AYUDA, DialogoPropiedades::ayuda)
    EVT_LISTBOX(DLG_PROPIEDADES_LISTBOX_PROPIEDADES,DialogoPropiedades::cambiaPropiedad)
END_EVENT_TABLE()


DialogoPropiedades::DialogoPropiedades(Propiedades *pr,wxWindow *parent, wxHtmlHelpController *ayuda):wxDialog(parent,wxID_ANY,wxString(wxT("")))
{
  PropTmp=pr;
  Prop=*PropTmp;
  Ayuda=ayuda;

  SetTitle(wxT("Propiedades Genéricas"));

  ButtonAdicionar                =new wxButton(this,DLG_PROPIEDADES_BTN_ADICIONAR, wxT("Adicionar"));
  ButtonEditar                   =new wxButton(this,DLG_PROPIEDADES_BTN_EDITAR, wxT("Editar"));
  ButtonBorrar                   =new wxButton(this,DLG_PROPIEDADES_BTN_BORRAR, wxT("Borrar"));
  ButtonActualizar               =new wxButton(this,DLG_PROPIEDADES_BTN_ACTUALIZAR, wxT("Actualizar"));
  ButtonOK                       =new wxButton(this,DLG_PROPIEDADES_BTN_OK, wxT("OK"));
  ButtonCancelar                 =new wxButton(this,DLG_PROPIEDADES_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda                    =new wxButton(this,DLG_PROPIEDADES_BTN_AYUDA, wxT("Ayuda"));
  StaticPropiedades              =new wxStaticText(this,DLG_PROPIEDADES_STATIC_PROPIEDADES, wxT("Lista de Propiedades"));
  ListBoxPropiedades             =new wxListBox(this,DLG_PROPIEDADES_LISTBOX_PROPIEDADES,wxDefaultPosition,wxDefaultSize, 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
  TextCtrlPropiedad              =new wxTextCtrl(this,DLG_PROPIEDADES_TEXTCTRL_PROPIEDAD,wxT(""),wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE);

  ListBoxPropiedades->SetMinSize(wxSize(150,150));
  TextCtrlPropiedad->SetMinSize(wxSize(300,80));
  
    wxBoxSizer *sizerLista = new wxBoxSizer(wxVERTICAL);
    sizerLista->Add(StaticPropiedades, 0, wxALIGN_CENTER | wxALL, 5);
    sizerLista->Add(ListBoxPropiedades, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerBut = new wxBoxSizer(wxVERTICAL);
    sizerBut->Add(ButtonAdicionar, 0, wxALIGN_CENTER | wxALL, 0);
    sizerBut->Add(ButtonEditar, 0, wxALIGN_CENTER | wxALL, 0);
    sizerBut->Add(ButtonBorrar, 0, wxALIGN_CENTER | wxALL, 0);
    sizerBut->Add(30,10, 0, wxALIGN_CENTER | wxALL, 0);
    sizerBut->Add(ButtonActualizar, 0, wxALIGN_CENTER | wxALL, 0);

    wxBoxSizer *sizerProp = new wxBoxSizer(wxHORIZONTAL);
    sizerProp->Add(sizerLista, 0, wxALIGN_CENTER | wxALL, 5);
    sizerProp->Add(sizerBut, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerProp, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(TextCtrlPropiedad, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoPropiedades::~DialogoPropiedades()
{
}

void DialogoPropiedades::llenarCuadro()
{
  ListBoxPropiedades->Clear();
  int i,tam;
  tam=Prop.tamano();
  for(i=0;i<tam;i++)
  {
    ListBoxPropiedades->Append(Prop.nombre(i));
  }
  if(tam>0)
  {
    sel=0;
    ListBoxPropiedades->SetSelection(sel);
    TextCtrlPropiedad->SetValue(Prop.valor(sel));
  }
}

void DialogoPropiedades::adicionar(wxCommandEvent&)
{
  wxCommandEvent ev;
  actualizar(ev);
  wxTextEntryDialog dlg(this,wxT("Nombre de la Propiedad"),wxT("Entrada"));
  if(dlg.ShowModal()==wxID_OK)
  {
    wxString cad;
    cad=dlg.GetValue();

    if(ListBoxPropiedades->FindString(cad)!=-1)
    {
      wxMessageBox(wxT("Ya existe una Propiedad con ese nombre"),wxT("Alerta"),wxOK,this);
    }else
    {
      sel++;
      Prop.adicionarPropiedad(cad,sel);
      int selTmp=sel;
      llenarCuadro();
      sel=selTmp;
      ListBoxPropiedades->SetSelection(sel);
      wxCommandEvent ev;
      cambiaPropiedad(ev);
    }
  }
}

void DialogoPropiedades::editar(wxCommandEvent&)
{
  if(sel<0){return;}
  wxCommandEvent ev;
  actualizar(ev);
  wxTextEntryDialog dlg(this,wxT("Nombre de la Propiedad"),wxT("Entrada"));
  dlg.SetValue(ListBoxPropiedades->GetStringSelection());
  if(dlg.ShowModal()==wxID_OK)
  {
    wxString cad;
    cad=dlg.GetValue();

    if(ListBoxPropiedades->FindString(cad)!=-1)
    {
      wxMessageBox(wxT("Ya existe una Propiedad con ese nombre"),wxT("Alerta"),wxOK,this);
    }else
    {
      Prop.modificarNombre(cad,sel);
      int selTmp=sel;
      llenarCuadro();
      sel=selTmp;
      ListBoxPropiedades->SetSelection(sel);
      wxCommandEvent ev;
      cambiaPropiedad(ev);
    }
  }
}

void DialogoPropiedades::borrar(wxCommandEvent&)
{
  if(sel<0){return;}
  wxCommandEvent ev;
  actualizar(ev);
//  int tam;
//  tam=Prop.tamano();
//  if(tam<2)
//  {
//    wxMessageBox("Debe haber al menos una Propiedad","Alerta",wxOK,this);
//  }else
//  {
    wxString cad;
    cad << wxT("Desea borrar la Propiedad '") <<ListBoxPropiedades->GetStringSelection() << wxT("'?");
    if(wxMessageBox(cad,wxT("Alerta"),wxICON_QUESTION | wxYES_NO,this)==wxYES)
    {
      Prop.eliminarPropiedad(sel);
      if(Prop.tamano()-1 < sel)
      {
        sel=Prop.tamano()-1;
      }
      int selTmp=sel;
      llenarCuadro();
      sel=selTmp;
      ListBoxPropiedades->SetSelection(sel);
      wxCommandEvent ev;
      cambiaPropiedad(ev);
    }
//  }
}

void DialogoPropiedades::actualizar(wxCommandEvent&)
{
  if(sel>=0)
  {
    Prop.modificarValor(TextCtrlPropiedad->GetValue(),sel);
  }
}

void DialogoPropiedades::cambiaPropiedad(wxCommandEvent&)
{
  if(TextCtrlPropiedad->IsModified())
  {
    wxCommandEvent ev;
    actualizar(ev);
  }
  sel=ListBoxPropiedades->GetSelection();
  if(sel>=0)
  {
    TextCtrlPropiedad->SetValue(Prop.valor(sel));
  }else
  {
    TextCtrlPropiedad->SetValue(wxT(""));
  }
}

void DialogoPropiedades::cerrarOk(wxCommandEvent&)
{
  *PropTmp=Prop;
  Close();
}
void DialogoPropiedades::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoPropiedades::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición de Generalidades"));
}


