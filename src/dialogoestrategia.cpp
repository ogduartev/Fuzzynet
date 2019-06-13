/***************************************************************************
                          dialogoestrategia.cpp  -  description
                             -------------------
    begin                : mar abr 6 2004
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

#include "dialogoestrategia.h"

BEGIN_EVENT_TABLE(DialogoEstrategia, wxDialog)
    EVT_BUTTON(DLG_EST_BTN_GRAFO, DialogoEstrategia::grafo)
    EVT_BUTTON(DLG_EST_BTN_PROPIEDADES, DialogoEstrategia::propiedades)
    EVT_BUTTON(DLG_EST_BTN_OK, DialogoEstrategia::cerrarOk)
//    EVT_BUTTON(DLG_EST_BTN_CANCELAR, DialogoCaso::noImplementada)
    EVT_BUTTON(DLG_EST_BTN_AYUDA, DialogoEstrategia::ayuda)
    EVT_BUTTON(DLG_EST_BTN_LIBRERIAS, DialogoEstrategia::librerias)
END_EVENT_TABLE()


DialogoEstrategia::DialogoEstrategia(
        Estrategia *est,Proyecto *proy,MiCanvas *canvas, wxWindow *parent,wxHtmlHelpController *ayuda)
        :wxDialog(parent,wxID_ANY,wxString(wxT("Prueba")))
{
  Est=est;
  Proy=proy;
  Canvas=canvas;
  Ayuda=ayuda;

    ButtonGrafo             =new wxButton (this,DLG_EST_BTN_GRAFO, wxT("Nodo Principal"));
    ButtonPropiedades       =new wxButton (this,DLG_EST_BTN_PROPIEDADES, wxT("Propiedades"));
    ButtonOK                =new wxButton (this,DLG_EST_BTN_OK, wxT("OK"));
//    ButtonCancelar          =new wxButton (this,DLG_EST_BTN_CANCEL, wxT("Cancelar"));
    ButtonAyuda             =new wxButton (this,DLG_EST_BTN_AYUDA, wxT("Ayuda"));
    ButtonLibrerias          =new wxButton (this,DLG_EST_BTN_LIBRERIAS, wxT("Librerías"));
    TextNombre              =new wxTextCtrl(this,DLG_EST_TEXT_NOMBRE);
    StaticNombre            =new wxStaticText (this,DLG_EST_STATIC_NOMBRE, wxT("Nombre"));
    StaticDescripcion      = new wxStaticText(this,DLG_EST_STATIC_DESCRIPCION,wxT("Descripción"));
    TextDescripcion        = new wxTextCtrl(this,DLG_EST_TEXT_DESCRIPCION,wxT(""),wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE);

    TextDescripcion->SetMinSize(wxSize(300,80));
    TextNombre->SetMinSize(wxSize(200,20));
    ButtonGrafo->SetMinSize(wxSize(120,30));
    ButtonPropiedades->SetMinSize(wxSize(120,30));

    wxBoxSizer *sizerNombre = new wxBoxSizer(wxHORIZONTAL);
    sizerNombre->Add(StaticNombre, 0, wxALIGN_RIGHT | wxLEFT |wxRIGHT, 5);
    sizerNombre->Add(TextNombre, 0, wxALIGN_LEFT | wxLEFT |wxRIGHT, 5);


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
    sizerTotal->Add(ButtonGrafo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(ButtonPropiedades, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerDescr, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoEstrategia::~DialogoEstrategia()
{
}

void DialogoEstrategia::llenarCuadro()
{
  TextNombre->SetValue(Est->Nombre);
  TextDescripcion->SetValue(Est->Descripcion);
}

void DialogoEstrategia::grafo(wxCommandEvent&)
{
  Est->Nombre=TextNombre->GetValue();
  DialogoNodo dlg(&Est->Grafo,Proy,this,wxT("PRUEBA"), Ayuda);
  dlg.ShowModal();
  llenarCuadro();
  Proy->calcularTodo();
  Canvas->llenarRegiones();
  Canvas->Refresh();
}

void DialogoEstrategia::propiedades(wxCommandEvent&)
{
  Est->Descripcion=TextDescripcion->GetValue();
  Est->Nombre=TextNombre->GetValue();
  DialogoPropiedades dlg(&Est->Generalidades,this, Ayuda);
  dlg.ShowModal();
  llenarCuadro();
}

void DialogoEstrategia::cerrarOk(wxCommandEvent&)
{
  Est->Descripcion=TextDescripcion->GetValue();
  Est->Nombre=TextNombre->GetValue();
  Close();
}

void DialogoEstrategia::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición de Metodologías"));
}

void DialogoEstrategia::librerias(wxCommandEvent&)
{
  Canvas->NoPintar=TRUE;
  wxString dirActual;
  dirActual=wxGetCwd();
  DialogoLibreria dlg(Est,NULL,NULL,this,wxT("Librerías de Fuzzynet"), Ayuda);
  dlg.ShowModal();
  wxSetWorkingDirectory(dirActual);
  Canvas->NoPintar=FALSE;
  Canvas->Ver=VER_RED;
  Canvas->llenarRegiones();
  Canvas->Refresh();
}
