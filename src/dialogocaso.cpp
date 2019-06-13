/***************************************************************************
                          dialogocaso.cpp  -  description
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

#include "dialogocaso.h"

BEGIN_EVENT_TABLE(DialogoCaso, wxDialog)
    EVT_BUTTON(DLG_CASO_BTN_EDITAR_VARIABLE, DialogoCaso::editarVariable)
    EVT_BUTTON(DLG_CASO_BTN_NUEVA_VARIABLE, DialogoCaso::nuevaVariable)
    EVT_BUTTON(DLG_CASO_BTN_BORRAR_VARIABLE, DialogoCaso::borrarVariable)
    EVT_BUTTON(DLG_CASO_BTN_COPIAR_VARIABLE, DialogoCaso::copiarVariable)
    EVT_BUTTON(DLG_CASO_BTN_PROPIEDADES, DialogoCaso::propiedades)
    EVT_BUTTON(DLG_CASO_BTN_OK, DialogoCaso::cerrarOk)
//    EVT_BUTTON(DLG_CASO_BTN_CANCELAR, DialogoCaso::noImplementada)
    EVT_BUTTON(DLG_CASO_BTN_AYUDA, DialogoCaso::ayuda)
    EVT_BUTTON(DLG_CASO_BTN_LIBRERIAS, DialogoCaso::librerias)
END_EVENT_TABLE()


DialogoCaso::DialogoCaso(MiCanvas *canvas,Caso *cas,
          Proyecto *proy, wxWindow *parent, wxHtmlHelpController *ayuda)
          :wxDialog(parent,wxID_ANY,wxString(wxT("Prueba")))
{
  Canvas=canvas;
  Cas=cas;
  Proy=proy;
  Ayuda=ayuda;

    ButtonEditarVariable    =new wxButton (this,DLG_CASO_BTN_EDITAR_VARIABLE, wxT("Editar"));
    ButtonNuevaVariable     =new wxButton (this,DLG_CASO_BTN_NUEVA_VARIABLE, wxT("Nueva"));
    ButtonBorrarVariable    =new wxButton (this,DLG_CASO_BTN_BORRAR_VARIABLE, wxT("Borrar"));
    ButtonCopiarVariables   =new wxButton (this,DLG_CASO_BTN_COPIAR_VARIABLE, wxT("Copiar"));
    ButtonPropiedades       =new wxButton (this,DLG_CASO_BTN_PROPIEDADES, wxT("Propiedades"));
    ButtonOK                =new wxButton (this,DLG_CASO_BTN_OK, wxT("OK"));
//    ButtonCancelar          =new wxButton (this,DLG_CASO_BTN_CANCEL, wxT("Cancelar"));
    ButtonAyuda             =new wxButton (this,DLG_CASO_BTN_AYUDA, wxT("Ayuda"));
    ButtonLibrerias         =new wxButton (this,DLG_CASO_BTN_LIBRERIAS, wxT("Librerías"));
    ListBoxVariables        =new wxListBox (this,DLG_CASO_LISTBOX_VARIABLES,wxPoint(20,20),wxSize(200,100), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
    TextNombre              =new wxTextCtrl(this,DLG_CASO_TEXT_NOMBRE);
    StaticNombre            =new wxStaticText (this,DLG_CASO_STATIC_NOMBRE, wxT("Nombre"));
    StaticVariables         =new wxStaticText (this,DLG_CASO_STATIC_VARIABLES, wxT("Variables"));
    StaticDescripcion     = new wxStaticText(this,DLG_CASO_STATIC_DESCRIPCION,wxT("Descripción"));
    TextDescripcion       = new wxTextCtrl(this,DLG_CASO_TEXT_DESCRIPCION,wxT(""),wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE);

    TextDescripcion->SetMinSize(wxSize(300,80));
    TextNombre->SetMinSize(wxSize(200,20));
    ButtonPropiedades->SetMinSize(wxSize(120,30));

    wxBoxSizer *sizerNombre = new wxBoxSizer(wxHORIZONTAL);
    sizerNombre->Add(StaticNombre, 0, wxALIGN_RIGHT | wxLEFT |wxRIGHT, 5);
    sizerNombre->Add(TextNombre, 0, wxALIGN_LEFT | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerVariables = new wxBoxSizer(wxVERTICAL);
    sizerVariables->Add(StaticVariables, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerVariables->Add(ListBoxVariables, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerBut = new wxBoxSizer(wxVERTICAL);
    sizerBut->Add(ButtonEditarVariable, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerBut->Add(ButtonNuevaVariable, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerBut->Add(ButtonBorrarVariable, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerBut->Add(20,30, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerBut->Add(ButtonCopiarVariables, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerEditVariables = new wxBoxSizer(wxHORIZONTAL);
    sizerEditVariables->Add(sizerVariables, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerEditVariables->Add(sizerBut, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
//    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonLibrerias, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerDescr = new wxBoxSizer(wxVERTICAL);
    sizerDescr->Add(StaticDescripcion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerDescr->Add(TextDescripcion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerNombre, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerEditVariables, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(ButtonPropiedades, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerDescr, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoCaso::~DialogoCaso()
{
}

void DialogoCaso::llenarCuadro()
{
  TextNombre->SetValue(Cas->Nombre);
  TextDescripcion->SetValue(Cas->Descripcion);

  ListBoxVariables->Clear();
  int i,tam;
  tam=Cas->Variables.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=Cas->Variables.Item(i).Nombre;
    ListBoxVariables->Append(cad);
  }
  if(tam>0)
  {
    ListBoxVariables->SetSelection(0);
  }
}

void DialogoCaso::editarVariable(wxCommandEvent&)
{
  int n;
  n=ListBoxVariables->GetSelection();
  if(n<0){return;}
  VariableLinguistica *Var;
  Var=&Cas->Variables.Item(n);
  DialogoVariable dlg(Var,Proy,this,wxT("Prueba"), Ayuda);
  dlg.ShowModal();
  llenarCuadro();
  ListBoxVariables->SetSelection(n);
}

void DialogoCaso::nuevaVariable(wxCommandEvent&)
{
  wxTextEntryDialog dlg(this,wxT("Nombre de la Variable"));
  if(dlg.ShowModal()==wxID_OK)
  {
    wxString cad;
    cad=dlg.GetValue();
    if(ListBoxVariables->FindString(cad)!=-1)
    {
      wxMessageBox(wxT("Ya existe una Variable con ese nombre"),wxT("Alerta"),wxOK,this);
    }else
    {
      VariableLinguistica *Var;
      Var=new VariableLinguistica();
      Var->Nombre=cad;
      int n=ListBoxVariables->GetSelection();
      Cas->Variables.Insert(Var,n+1);
    }
    Cas->Descripcion=TextDescripcion->GetValue();
    wxString cad2;
    cad2=TextNombre->GetValue();
    Cas->Nombre=cad2;
    llenarCuadro();
  }
}

void DialogoCaso::borrarVariable(wxCommandEvent&)
{
  int n;
  n=ListBoxVariables->GetSelection();
  if(n<0){return;}
  wxString cad;
  cad << wxT("Desea borrar La Variable '") <<ListBoxVariables->GetStringSelection() << wxT("'?");
  if(wxMessageBox(cad,wxT("Alerta"),wxICON_QUESTION | wxYES_NO,this)==wxYES)
  {
    Cas->Variables.RemoveAt(n);
    llenarCuadro();
    if(Cas->Variables.GetCount()>n)
    {
      ListBoxVariables->SetSelection(n);
    }else
    {
      ListBoxVariables->SetSelection(n-1);
    }
  }
}

void DialogoCaso::copiarVariable(wxCommandEvent&)
{
  int Est=-1;
  int Flag=0;
  int Flag2=1;
  DialogoSeleccionarEstrategia dlg(&Est,&Flag,&Flag2,Proy,this, Ayuda);
  dlg.ShowModal();
  switch(Flag)
  {
    case -1 : return;
    case 0 : // adicionar
            break;
    case 1 : // borrar
            Cas->Variables.Empty();
            break;
    default : return;
  }
  if(Est>-1)
  {
    Estrategia *est=&Proy->Estrategias.Item(Est);
    est->llenarCasoIndefinido(Cas,Flag2);
  }
  Cas->Descripcion=TextDescripcion->GetValue();
  wxString cad2;
  cad2=TextNombre->GetValue();
  Cas->Nombre=cad2;
  llenarCuadro();
}

void DialogoCaso::propiedades(wxCommandEvent&)
{
  Cas->Descripcion=TextDescripcion->GetValue();
  Cas->Nombre=TextNombre->GetValue();
  DialogoPropiedades dlg(&Cas->Generalidades,this, Ayuda);
  dlg.ShowModal();
//  llenarCuadro();
}

void DialogoCaso::cerrarOk(wxCommandEvent&)
{
  Cas->Descripcion=TextDescripcion->GetValue();
  wxString cad2;
  cad2=TextNombre->GetValue();
  Cas->Nombre=cad2;
  Close();
}

void DialogoCaso::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición de Casos"));
}

void DialogoCaso::librerias(wxCommandEvent&)
{
  Canvas->NoPintar=TRUE;
  wxString dirActual;
  dirActual=wxGetCwd();
  DialogoLibreria dlg(NULL,Cas,NULL,this,wxT("Librerías de Fuzzynet"), Ayuda);
  dlg.ShowModal();
  wxSetWorkingDirectory(dirActual);
  Canvas->NoPintar=FALSE;
  Canvas->Ver=VER_RED;
  Canvas->llenarRegiones();
  Canvas->Refresh();
}

