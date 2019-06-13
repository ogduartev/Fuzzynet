/***************************************************************************
                          dialogonumeromostrar.cpp  -  description
                             -------------------
    begin                : jue abr 8 2004
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

#include "dialogonumeromostrar.h"

BEGIN_EVENT_TABLE(DialogoNumeroMostrar, wxDialog)
    EVT_PAINT(DialogoNumeroMostrar::OnPaint)
    EVT_BUTTON(DLG_NUMERO_MOSTRAR_BTN_OK, DialogoNumeroMostrar::cerrarOk)
    EVT_BUTTON(DLG_NUMERO_MOSTRAR_BTN_CANCEL, DialogoNumeroMostrar::cancelar)
    EVT_BUTTON(DLG_NUMERO_MOSTRAR_BTN_AYUDA, DialogoNumeroMostrar::ayuda)
    EVT_LISTBOX(DLG_NUMERO_MOSTRAR_LISTBOX_ETIQUETAS,DialogoNumeroMostrar::seleccionarEtiqueta)
END_EVENT_TABLE()

DialogoNumeroMostrar::DialogoNumeroMostrar(VariableLinguistica *var,
          NumeroDifuso *num,wxWindow *parent,const wxString& title, wxHtmlHelpController *ayuda)
          :wxDialog(parent,-1,title)
{
    Var=var;
    Num=num;
    Ayuda=ayuda;

    SetTitle(wxT("Número Difuso Calculado"));

     ButtonOK                         =new wxButton(this,DLG_NUMERO_MOSTRAR_BTN_OK, wxT("OK"));
     ButtonCancelar                 =new wxButton(this,DLG_NUMERO_MOSTRAR_BTN_CANCEL, wxT("Cancelar"));
     ButtonAyuda                    =new wxButton (this,DLG_NUMERO_MOSTRAR_BTN_AYUDA, wxT("Ayuda"));
     StaticNombre                    =new wxStaticText(this,DLG_NUMERO_MOSTRAR_STATIC_NOMBRE, wxT("Nombre"));
     StaticMinimo                     =new wxStaticText(this,DLG_NUMERO_MOSTRAR_STATIC_MINIMO, wxT("Mínimo"));
     StaticMaximo                    =new wxStaticText(this,DLG_NUMERO_MOSTRAR_STATIC_MAXIMO, wxT("Máximo"));
     StaticUnidades                  =new wxStaticText(this,DLG_NUMERO_MOSTRAR_STATIC_UNIDADES, wxT("Unidades"));
     StaticEtiquetas                  =new wxStaticText(this,DLG_NUMERO_MOSTRAR_STATIC_ETIQUETAS, wxT("Etiquetas"));
     StaticValorCalculado          =new wxStaticText(this,DLG_NUMERO_MOSTRAR_STATIC_VALORCALCULADO, wxT("El Valor es..."));
    TextNombre                       =new wxTextCtrl(this,DLG_NUMERO_MOSTRAR_TEXT_NOMBRE,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    TextMinimo                        =new wxTextCtrl(this,DLG_NUMERO_MOSTRAR_TEXT_MINIMO,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    TextMaximo                       =new wxTextCtrl(this,DLG_NUMERO_MOSTRAR_TEXT_MAXIMO,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    TextUnidades                     =new wxTextCtrl(this,DLG_NUMERO_MOSTRAR_TEXT_UNIDADES,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_READONLY);
    ListBoxEtiquetas                 =new wxListBox(this,DLG_NUMERO_MOSTRAR_LISTBOX_ETIQUETAS,wxPoint(0,0),wxSize(150, 80), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);

/*    ButtonOK                          ->SetSize(80,20);
    ButtonCancelar                  ->SetSize(80,20);
    ButtonAyuda                      ->SetSize(80,20);*/
    StaticValorCalculado           ->SetMinSize(wxSize(180,20));
    TextNombre                       ->SetMinSize(wxSize(300,20));
    TextMinimo                        ->SetMinSize(wxSize(40,20));
    TextMaximo                       ->SetMinSize(wxSize(40,20));
    TextUnidades                     ->SetMinSize(wxSize(40,20));
    ListBoxEtiquetas                ->SetMinSize(wxSize(100,80));

    SizerDibujo=new wxBoxSizer(wxHORIZONTAL);
    SizerDibujo->Add(200,80, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerNombre = new wxBoxSizer(wxHORIZONTAL);
    sizerNombre->Add(StaticNombre, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerNombre->Add(TextNombre, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerMinMax = new wxBoxSizer(wxHORIZONTAL);
    sizerMinMax->Add(StaticMinimo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerMinMax->Add(TextMinimo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerMinMax->Add(StaticMaximo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerMinMax->Add(TextMaximo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerMinMax->Add(StaticUnidades, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerMinMax->Add(TextUnidades, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerEtiDib = new wxBoxSizer(wxVERTICAL);
    sizerEtiDib->Add(StaticEtiquetas, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerEtiDib->Add(SizerDibujo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerEtiqueta = new wxBoxSizer(wxHORIZONTAL);
    sizerEtiqueta->Add(sizerEtiDib, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);
    sizerEtiqueta->Add(ListBoxEtiquetas, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerValCombo = new wxBoxSizer(wxVERTICAL);
    sizerValCombo->Add(StaticValorCalculado, 0, wxALIGN_LEFT | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerValor = new wxBoxSizer(wxHORIZONTAL);
    sizerValor->Add(sizerValCombo, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerNombre, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerMinMax, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerEtiqueta, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerValor, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoNumeroMostrar::~DialogoNumeroMostrar()
{
}

void DialogoNumeroMostrar::llenarCuadro()
{
  wxString cad;
  cad=wxT(""); cad << Var->Nombre;TextNombre->SetValue(cad);
  cad=wxT(""); cad << Var->Minimo;TextMinimo->SetValue(cad);
  cad=wxT(""); cad << Var->Maximo;TextMaximo->SetValue(cad);
  cad=wxT(""); cad << Var->Unidades;TextUnidades->SetValue(cad);

  int i,tam;
  ListBoxEtiquetas->Clear();
  tam=Var->Etiquetas.GetCount();
  for(i=0;i<tam;i++)
  {
    cad=wxT(""); cad << Var->Etiquetas.Item(i).Label;
    ListBoxEtiquetas->Append(cad);
  }
  ListBoxEtiquetas->SetSelection(0);

  Refresh();

//  cad=Var->strEntrada();
  cad = wxT("Valor: ");
  cad << Num->valorRepresentativo(0.5,1);
  cad << wxT(" / ");
  cad << Num->ambiguedad();
  StaticValorCalculado->SetLabel(cad);
}


void DialogoNumeroMostrar::OnPaint(wxPaintEvent&)
{
  wxPaintDC dc(this);
//  PrepareDC(dc);
  pintar(dc);
}

void DialogoNumeroMostrar::pintar(wxPaintDC &dc)
{
//  wxPaintDC dc(this);
  wxPoint Origen;
  wxSize Tamano;
  Origen=SizerDibujo->GetPosition();
  Tamano=SizerDibujo->GetSize();
  dc.SetPen(* wxBLACK_PEN);
//  dc.DrawRectangle(Origen.x,Origen.y,Tamano.GetWidth(),Tamano.GetHeight());
  dc.DrawRectangle(Origen,Tamano);
// un pequeño offset
  Origen.x+=5;
  Origen.y+=5;
  Tamano.SetWidth(Tamano.GetWidth()-10);
  Tamano.SetHeight(Tamano.GetHeight()-5);
  int i,tam;
  tam=Var->Etiquetas.GetCount();
  for(i=0;i<tam;i++)
  {
    if (i == ListBoxEtiquetas->GetSelection())
    {
      dc.SetPen(* wxRED_PEN);
    }else
    {
      dc.SetPen(* wxBLUE_PEN);
    }
    NumeroDifuso *n;
    n=Var->Etiquetas.Item(i).ND;
    int j,tam2;
    tam2=n->Tamano;
    float xLo,xLf,xRo,xRf,yo,yf;
    for(j=0;j<tam2-1;j++)
    {
      yo=j*n->intervalo();
      yf=(j+1)*n->intervalo();
      xLo=n->L[j];
      xLf=n->L[j+1];
      xRo=n->R[j];
      xRf=n->R[j+1];
      xLo = Origen.x + (xLo - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xLf = Origen.x + (xLf - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xRo = Origen.x + (xRo - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xRf = Origen.x + (xRf - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      // y aumenta hacia abajo !!!
      yo = Origen.y + Tamano.GetHeight() - (yo - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      yf = Origen.y + Tamano.GetHeight() - (yf - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      dc.DrawLine(xLo,yo,xLf,yf);
      dc.DrawLine(xRo,yo,xRf,yf);
    }
    dc.DrawLine(xLf,yf,xRf,yf);
  }
//  if(CheckValor->GetValue())
  {
    dc.SetPen(* wxBLACK_PEN);
    NumeroDifuso *n;
//    n=Var->valor();
    n=Num;
    int j,tam2;
    tam2=n->Tamano;
    float xLo,xLf,xRo,xRf,yo,yf;
    for(j=0;j<tam2-1;j++)
    {
      yo=j*n->intervalo();
      yf=(j+1)*n->intervalo();
      xLo=n->L[j];
      xLf=n->L[j+1];
      xRo=n->R[j];
      xRf=n->R[j+1];
      xLo = Origen.x + (xLo - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xLf = Origen.x + (xLf - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xRo = Origen.x + (xRo - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      xRf = Origen.x + (xRf - Var->Minimo)*(Tamano.GetWidth())/(Var->Maximo-Var->Minimo);
      // y aumenta hacia abajo !!!
      yo = Origen.y + Tamano.GetHeight() - (yo - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      yf = Origen.y + Tamano.GetHeight() - (yf - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      dc.DrawLine(xLo,yo,xLf,yf);
      dc.DrawLine(xRo,yo,xRf,yf);
    }
    dc.DrawLine(xLf,yf,xRf,yf);
  }
}

void DialogoNumeroMostrar::seleccionarEtiqueta(wxCommandEvent&)
{
  if(Var->TipoDeValor==4)
  {
    Var->EtiquetaSeleccionada=ListBoxEtiquetas->GetSelection();
    llenarCuadro();
    ListBoxEtiquetas->SetSelection(Var->EtiquetaSeleccionada);
  }else
  {
    Refresh();
  }
}

void DialogoNumeroMostrar::cerrarOk(wxCommandEvent&)
{
  Close();
}

void DialogoNumeroMostrar::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoNumeroMostrar::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Presentación de Números Difusos"));
}



