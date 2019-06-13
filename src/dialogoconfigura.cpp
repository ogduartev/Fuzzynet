/***************************************************************************
                          dialogoconfigura.cpp  -  description
                             -------------------
    begin                : mar 17 2004
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

#include "dialogoconfigura.h"


BEGIN_EVENT_TABLE(DialogoConfigura, wxDialog)
//    EVT_PAINT(DialogoConfigura::OnPaint)
    EVT_BUTTON(DLG_CONFIGURA_BTN_OK, DialogoConfigura::cerrarOk)
    EVT_BUTTON(DLG_CONFIGURA_BTN_CANCEL, DialogoConfigura::cancelar)
    EVT_BUTTON(DLG_CONFIGURA_BTN_AYUDA, DialogoConfigura::ayuda)
    EVT_BUTTON(DLG_CONFIGURA_BTN_LEERCONFIGURA, DialogoConfigura::leerConfigura)
    EVT_BUTTON(DLG_CONFIGURA_BTN_ESCRIBIRCONFIGURA, DialogoConfigura::escribirConfigura)
    EVT_BUTTON(DLG_CONFIGURA_BTN_DEFECTO, DialogoConfigura::defecto)
END_EVENT_TABLE()


DialogoConfigura::DialogoConfigura(MiCanvas *canvas,
          wxWindow *parent,const wxString& title,wxHtmlHelpController *ayuda)
          :wxDialog(parent,-1,title)
{
  Canvas=canvas;
  Ayuda=ayuda;
  SetTitle(wxT("Configuración de la Interfaz"));

  ButtonOK                       =new wxButton(this,DLG_CONFIGURA_BTN_OK, wxT("OK"));
  ButtonCancelar                 =new wxButton(this,DLG_CONFIGURA_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda                    =new wxButton (this,DLG_CONFIGURA_BTN_AYUDA, wxT("Ayuda"));
  ButtonLeerConfigura            =new wxButton (this,DLG_CONFIGURA_BTN_LEERCONFIGURA, wxT("Leer Predeterminado"));
  ButtonEscribirConfigura        =new wxButton (this,DLG_CONFIGURA_BTN_ESCRIBIRCONFIGURA, wxT("Escribir Predeterminado"));
  ButtonDefecto                 =new wxButton (this,DLG_CONFIGURA_BTN_DEFECTO, wxT("Configuración por defecto"));
  Notebook                       =new wxNotebook(this,DLG_CONFIGURA_NOTEBOOK);

  llenarNotebook();

    wxBoxSizer *sizerButPre = new wxBoxSizer(wxVERTICAL);
    sizerButPre->Add(ButtonLeerConfigura, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButPre->Add(ButtonEscribirConfigura, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButPre->Add(ButtonDefecto, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerNote = new wxBoxSizer(wxVERTICAL);

    sizerNote->Add(Notebook, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerNote, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButPre, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

}

DialogoConfigura::~DialogoConfigura()
{
}

void DialogoConfigura::llenarNotebook()
{
  PagColores=new PaginaColores(Canvas,Notebook,wxT("Colores"));
  Notebook->AddPage(PagColores,wxT("Colores"),TRUE );
  PagFuentes=new PaginaFuentes(Canvas,Notebook,wxT("Fuentes"));
  Notebook->AddPage(PagFuentes,wxT("Fuentes"),FALSE );
  PagDimensiones=new PaginaDimensiones(Canvas,Notebook,wxT("Dimensiones"));
  Notebook->AddPage(PagDimensiones,wxT("Dimensiones"),FALSE );
  PagSelecciones=new PaginaSelecciones(Canvas,Notebook,wxT("Selecciones"));
  Notebook->AddPage(PagSelecciones,wxT("Selecciones"),FALSE );
}

void DialogoConfigura::OnPaint(wxPaintEvent&)
{
}

void DialogoConfigura::cerrarOk(wxCommandEvent&)
{
//  aplicar();
  Close();
}

void DialogoConfigura::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoConfigura::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Configuración de la Interfaz Gráfica"));
}


void DialogoConfigura::leerConfigura(wxCommandEvent&)
{
  Canvas->readConfigura();
  PagColores->recargar();
  PagColores->Refresh();
  PagFuentes->recargar();
  PagFuentes->Refresh();
  PagDimensiones->recargar();
  PagDimensiones->Refresh();
  PagSelecciones->recargar();
  PagSelecciones->pintarSel();
  Canvas->Refresh();
  Refresh();
}

void DialogoConfigura::escribirConfigura(wxCommandEvent&)
{
  Canvas->writeConfigura();
}

void DialogoConfigura::defecto(wxCommandEvent&)
{
  Canvas->defecto();
  PagColores->recargar();
  PagColores->Refresh();
  PagFuentes->recargar();
  PagFuentes->Refresh();
  PagDimensiones->recargar();
  PagDimensiones->Refresh();
  PagSelecciones->recargar();
  PagSelecciones->pintarSel();
  Canvas->Refresh();
  Refresh();
}
