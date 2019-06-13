/***************************************************************************
                          dialogonumeroeditar.cpp  -  description
                             -------------------
    begin                : lun jul 28 2003
    copyright            : (C) 2003 by
    email                :
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "dialogonumeroeditar.h"

BEGIN_EVENT_TABLE(DialogoNumeroEditar, wxDialog)
    EVT_PAINT(DialogoNumeroEditar::OnPaint)
    EVT_LISTBOX(DLG_NUMEROEDITAR_LISTBOX_GRILLA_ALFA,DialogoNumeroEditar::clickListaAlfa)
//    EVT_GRID_SELECT_CELL(DialogoNumeroEditar::OnPaint)
    EVT_SPINCTRL(DLG_NUMEROEDITAR_SPIN_ALFA, DialogoNumeroEditar::spinAlfa)
    EVT_BUTTON(DLG_NUMEROEDITAR_BTN_COPIARRESULTADO, DialogoNumeroEditar::copiarResultado)
    EVT_BUTTON(DLG_NUMEROEDITAR_BTN_DEFINICIONRAPIDA, DialogoNumeroEditar::definir)
    EVT_CHECKBOX(DLG_NUMEROEDITAR_CHECK_TRAPECIO, DialogoNumeroEditar::clickTrapecio)
    EVT_CHECKBOX(DLG_NUMEROEDITAR_CHECK_CAMPANA, DialogoNumeroEditar::clickCampana)
    EVT_BUTTON(DLG_NUMEROEDITAR_BTN_OK, DialogoNumeroEditar::cerrarOk)
    EVT_BUTTON(DLG_NUMEROEDITAR_BTN_CANCEL, DialogoNumeroEditar::cancelar)
    EVT_BUTTON(DLG_NUMEROEDITAR_BTN_AYUDA, DialogoNumeroEditar::ayuda)
END_EVENT_TABLE()

DialogoNumeroEditar::DialogoNumeroEditar(int etiflag, Etiqueta *e, float min, float max,
            Proyecto *proy, wxWindow* parent, wxHtmlHelpController *ayuda)
            :wxDialog(parent,wxID_ANY,wxString(wxT("Prueba")))
{
  Proy=proy;
  Ayuda=ayuda;

  EtiFlag=etiflag;
  EtiTemp=e;
  Label=e->Label;
  Num=*e->ND;
  Min=min;
  Max=max;
  Opt=Proy->Optimismo;
  Rep=Proy->Representatividad;

  SetTitle(wxT("Número Difuso"));

  ButtonCopiarResultado        =new wxButton (this,DLG_NUMEROEDITAR_BTN_COPIARRESULTADO, wxT("Copiar Resultado"));
  ButtonDefinicionRapida       =new wxButton (this,DLG_NUMEROEDITAR_BTN_DEFINICIONRAPIDA, wxT("Definición Rápida"));
  ButtonOK                         =new wxButton(this,DLG_NUMEROEDITAR_BTN_OK, wxT("OK"));
  ButtonCancelar                 =new wxButton(this,DLG_NUMEROEDITAR_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda                    =new wxButton (this,DLG_NUMEROEDITAR_BTN_AYUDA, wxT("Ayuda"));
  ListBoxAlfa                      =new wxListBox (this,DLG_NUMEROEDITAR_LISTBOX_GRILLA_ALFA,wxPoint(20,20),wxSize(200,100), 0, 0, wxLB_MULTIPLE|wxLB_ALWAYS_SB);
//  GrillaAlfa                          =new wxGrid (this,DLG_NUMEROEDITAR_GRID_GRILLA_ALFA,wxPoint(20,20),wxSize(200,100));
  StaticValor                       =new wxStaticText (this,DLG_NUMEROEDITAR_STATIC_VALOR, wxT("Valor"));
  StaticAmbiguedad             =new wxStaticText (this,DLG_NUMEROEDITAR_STATIC_AMBIGUEDAD,wxT("Ambigûedad"));
  StaticA                             =new wxStaticText (this,DLG_NUMEROEDITAR_STATIC_A,wxT("a"));
  StaticB                             =new wxStaticText (this,DLG_NUMEROEDITAR_STATIC_B,wxT("b"));
  StaticC                             =new wxStaticText (this,DLG_NUMEROEDITAR_STATIC_C,wxT("c"));
  StaticD                             =new wxStaticText (this,DLG_NUMEROEDITAR_STATIC_D,wxT("d"));
  StaticSpinAlfa                   =new wxStaticText (this,DLG_NUMEROEDITAR_STATIC_SPIN_ALFA,wxT("Número de Alfa-Cortes"));
  SpinAlfa                            =new wxSpinCtrl (this,DLG_NUMEROEDITAR_SPIN_ALFA);
  TextA                                =new wxTextCtrl (this,DLG_NUMEROEDITAR_TEXT_A);
  TextB                                =new wxTextCtrl (this,DLG_NUMEROEDITAR_TEXT_B);
  TextC                                =new wxTextCtrl (this,DLG_NUMEROEDITAR_TEXT_C);
  TextD                                =new wxTextCtrl (this,DLG_NUMEROEDITAR_TEXT_D);
  CheckTrapecio                   =new wxCheckBox (this,DLG_NUMEROEDITAR_CHECK_TRAPECIO,wxT("Trapecio"));
  CheckCampana                  =new wxCheckBox (this,DLG_NUMEROEDITAR_CHECK_CAMPANA,wxT("Campana"));

  if(EtiFlag)
  {
    StaticLabel                       =new wxStaticText (this,DLG_NUMEROEDITAR_STATIC_LABEL, wxT("Etiqueta:"));
    TextLabel                         =new wxTextCtrl (this,DLG_NUMEROEDITAR_TEXT_LABEL);
    TextLabel->SetMinSize(wxSize(180,20));
    TextLabel->SetValue(Label);
  }


/*  ButtonCopiarResultado->SetSize(120,20);
  ButtonDefinicionRapida->SetSize(120,20);
  ButtonOK->SetSize(80,20);
  ButtonCancelar->SetSize(80,20);
  ButtonAyuda->SetSize(80,20);*/
  SpinAlfa->SetMinSize(wxSize(60,20));
  TextA->SetMinSize(wxSize(40,20));
  TextB->SetMinSize(wxSize(40,20));
  TextC->SetMinSize(wxSize(40,20));
  TextD->SetMinSize(wxSize(40,20));
  StaticValor->SetMinSize(wxSize(180,20));
  StaticAmbiguedad->SetMinSize(wxSize(180,20));

  CheckTrapecio->SetValue(TRUE);
  CheckCampana->SetValue(FALSE);
  SpinAlfa->SetRange(2,100);

//  GrillaAlfa->CreateGrid(Num.Tamano,2);
//  GrillaAlfa->SetColLabelSize(20);
//  GrillaAlfa->SetRowLabelSize(20);
//  GrillaAlfa->SetColLabelValue(0,"L");
//  GrillaAlfa->SetColLabelValue(1,"R");

  SizerDibujo=new wxBoxSizer(wxHORIZONTAL);
  SizerDibujo->Add(200,80, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

  wxBoxSizer *sizerAlfaH = new wxBoxSizer(wxHORIZONTAL);
  sizerAlfaH->Add(StaticSpinAlfa, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 5);
  sizerAlfaH->Add(SpinAlfa, 0, wxALIGN_CENTER |  wxTOP | wxBOTTOM, 5);

  wxBoxSizer *sizerAlfaV = new wxBoxSizer(wxVERTICAL);
  sizerAlfaV->Add(ListBoxAlfa, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
//  sizerAlfaV->Add(GrillaAlfa, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
  sizerAlfaV->Add(sizerAlfaH, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

  wxBoxSizer *sizerDatos = new wxBoxSizer(wxHORIZONTAL);
  sizerDatos->Add(SizerDibujo, 0, wxALIGN_CENTER | wxALL, 5);
  sizerDatos->Add(sizerAlfaV, 0, wxALIGN_CENTER | wxALL, 5);

  wxBoxSizer *sizerValor = new wxBoxSizer(wxVERTICAL);
  sizerValor->Add(StaticValor, 0, wxALIGN_LEFT | wxLEFT | wxRIGHT, 5);
  sizerValor->Add(StaticAmbiguedad, 0, wxALIGN_RIGHT | wxLEFT | wxRIGHT, 5);
  sizerValor->Add(40,20, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
  sizerValor->Add(ButtonCopiarResultado, 0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

  wxBoxSizer *sizerEditABCD = new wxBoxSizer(wxHORIZONTAL);
  sizerEditABCD->Add(StaticA,0, wxALIGN_CENTER, 5);
  sizerEditABCD->Add(TextA,0, wxALIGN_CENTER , 5);
  sizerEditABCD->Add(StaticB,0, wxALIGN_CENTER | wxLEFT , 5);
  sizerEditABCD->Add(TextB,0, wxALIGN_CENTER , 5);
  sizerEditABCD->Add(StaticC,0, wxALIGN_CENTER | wxLEFT, 5);
  sizerEditABCD->Add(TextC,0, wxALIGN_CENTER , 5);
  sizerEditABCD->Add(StaticD,0, wxALIGN_CENTER | wxLEFT, 5);
  sizerEditABCD->Add(TextD,0, wxALIGN_CENTER , 5);

  wxBoxSizer *sizerCheck = new wxBoxSizer(wxHORIZONTAL);
  sizerCheck->Add(CheckTrapecio,0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
  sizerCheck->Add(CheckCampana,0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

  wxBoxSizer *sizerEditar = new wxBoxSizer(wxVERTICAL);
  sizerEditar->Add(sizerEditABCD,0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
  sizerEditar->Add(sizerCheck,0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);
  sizerEditar->Add(ButtonDefinicionRapida,0, wxALIGN_CENTER | wxLEFT | wxRIGHT, 5);

  wxBoxSizer *sizerDatosInf = new wxBoxSizer(wxHORIZONTAL);
  sizerDatosInf->Add(sizerValor,0, wxALIGN_CENTER | wxALIGN_BOTTOM | wxLEFT | wxRIGHT, 5);
  sizerDatosInf->Add(sizerEditar,0, wxALIGN_CENTER | wxALIGN_BOTTOM | wxLEFT | wxRIGHT, 5);

  wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
  sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
  sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
  sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

  wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
  if(EtiFlag)
  {
    wxBoxSizer *sizerLabel = new wxBoxSizer(wxHORIZONTAL);
    sizerLabel->Add(StaticLabel, 0, wxALIGN_CENTER | wxALL, 5);
    sizerLabel->Add(TextLabel, 0, wxALIGN_CENTER | wxALL, 5);

    sizerTotal->Add(sizerLabel, 0, wxALIGN_CENTER | wxALL, 5);
  }
  sizerTotal->Add(sizerDatos, 0, wxALIGN_CENTER | wxALL, 5);
  sizerTotal->Add(sizerDatosInf, 0, wxALIGN_CENTER | wxALL, 5);
  sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoNumeroEditar::~DialogoNumeroEditar()
{
}

void DialogoNumeroEditar::OnPaint(wxPaintEvent&)
{
  wxPaintDC dc(this);
//  PrepareDC(dc);
  pintar(dc);
}

void DialogoNumeroEditar::spinAlfa(wxSpinEvent&)
{
  int t;
  t=SpinAlfa->GetValue();
  Num.tamano(t);
  llenarCuadro();
  Refresh();
}

void DialogoNumeroEditar::clickListaAlfa(wxCommandEvent&)
{
  Refresh();
}

void DialogoNumeroEditar::pintar(wxPaintDC &dc)
{
  wxArrayInt AlfaSel;
  ListBoxAlfa->GetSelections(AlfaSel);
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

    int j,tam2;
    tam2=Num.Tamano;
    float xLo,xLf,xRo,xRf,yo,yf;
    for(j=0;j<tam2-1;j++)
    {
      yo=j*Num.intervalo();
      yf=(j+1)*Num.intervalo();
      xLo=Num.L[j];
      xLf=Num.L[j+1];
      xRo=Num.R[j];
      xRf=Num.R[j+1];
      xLo = Origen.x + (xLo - Min)*(Tamano.GetWidth())/(Max-Min);
      xLf = Origen.x + (xLf - Min)*(Tamano.GetWidth())/(Max-Min);
      xRo = Origen.x + (xRo - Min)*(Tamano.GetWidth())/(Max-Min);
      xRf = Origen.x + (xRf - Min)*(Tamano.GetWidth())/(Max-Min);
      // y aumenta hacia abajo !!!
      yo = Origen.y + Tamano.GetHeight() - (yo - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      yf = Origen.y + Tamano.GetHeight() - (yf - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      dc.SetPen(* wxBLUE_PEN);
      dc.DrawLine(xLo,yo,xLf,yf);
      dc.DrawLine(xRo,yo,xRf,yf);
      if(AlfaSel.Index(tam2-j-1) != wxNOT_FOUND)
      {
        dc.SetPen(* wxRED_PEN); dc.SetBrush(* wxRED_BRUSH);
      }else
      {
        dc.SetPen(* wxBLACK_PEN); dc.SetBrush(* wxBLACK_BRUSH);
      }
      dc.DrawCircle(xLo,yo,2);
      dc.DrawCircle(xRo,yo,2);
//      if(GrillaAlfa->IsInSelection(j,0))
//      {
//        dc.SetPen(* wxRED_PEN); dc.SetBrush(* wxRED_BRUSH);
//        dc.DrawCircle(xLo,yo,2);
//      }
//      if(GrillaAlfa->IsInSelection(j,1))
//      {
//        dc.SetPen(* wxRED_PEN); dc.SetBrush(* wxRED_BRUSH);
//        dc.DrawCircle(xRo,yo,2);
//      }
    }
    dc.SetPen(* wxBLUE_PEN);
    dc.DrawLine(xLf,yf,xRf,yf);
    if(AlfaSel.Index(tam2-j-1) != wxNOT_FOUND)
    {
      dc.SetPen(* wxRED_PEN); dc.SetBrush(* wxRED_BRUSH);
    }else
    {
      dc.SetPen(* wxBLACK_PEN); dc.SetBrush(* wxBLACK_BRUSH);
    }
    dc.DrawCircle(xLf,yf,2);
    dc.DrawCircle(xRf,yf,2);
//    if(GrillaAlfa->IsInSelection(j,0))
//    {
//      dc.SetPen(* wxRED_PEN); dc.SetBrush(* wxRED_BRUSH);
//      dc.DrawCircle(xLf,yf,2);
//    }
//    if(GrillaAlfa->IsInSelection(j,1))
//    {
//      dc.SetPen(* wxRED_PEN); dc.SetBrush(* wxRED_BRUSH);
//      dc.DrawCircle(xRf,yf,2);
//    }
}

void DialogoNumeroEditar::copiarResultado(wxCommandEvent&)
{
  leerCuadro();
  DialogoCopiarNumero dlg(&Num, Proy,this,Ayuda);
  dlg.ShowModal();
  llenarCuadro();
}

void DialogoNumeroEditar::llenarCuadro()
{
  int i,tam;
  wxString cad;
  ListBoxAlfa->Clear();
  tam=Num.Tamano;
  for(i=tam-1;i>-1;i--)
  {
    cad = wxT("");
    cad  << Num.intervalo()*(float)i << wxT(": ") << Num.L[i] << wxT(" , ") << Num.R[i];
    ListBoxAlfa->Append(cad);
  }
  SpinAlfa->SetValue(tam);
  cad = wxT("");cad << Num.d(0.0,1);
  TextA->SetValue(cad);
  cad = wxT("");cad << Num.d(1.0,1);
  TextB->SetValue(cad);
  cad = wxT("");cad << Num.d(1.0,-1);
  TextC->SetValue(cad);
  cad = wxT("");cad << Num.d(0.0,-1);
  TextD->SetValue(cad);
  cad = wxT("Valor: ");cad << Num.valorRepresentativo(Opt,Rep);
  StaticValor->SetLabel(cad);
  cad = wxT("Ambigüedad: ");cad << Num.ambiguedad();
  StaticAmbiguedad->SetLabel(cad);
}

void DialogoNumeroEditar::definir(wxCommandEvent&)
{
  float a,b,c,d;
  wxString cad;
  cad=TextA->GetValue();
  double F;
  cad.ToDouble(&F);
  a=(float)F;
  cad=TextB->GetValue();
  cad.ToDouble(&F);
  b=(float)F;
  cad=TextC->GetValue();
  cad.ToDouble(&F);
  c=(float)F;
  cad=TextD->GetValue();
  cad.ToDouble(&F);
  d=(float)F;
  if(Min <= a & a <= b & b <=c & c <= d & d <= Max)
  {
    if(CheckTrapecio->GetValue())
    {
      Num.trapecio(a,b,c,d);
    }else
    {
      Num.campana(a,b,c,d);
    }
    Refresh();
  }else
  {
    wxMessageBox(wxT("Valores Ilógicos"),wxT("Atención"), wxOK | wxICON_INFORMATION, this);
  }
  llenarCuadro();
}

void DialogoNumeroEditar::clickTrapecio(wxCommandEvent&)
{
  if(CheckTrapecio->GetValue())
  {
    CheckCampana->SetValue(FALSE);
  }else
  {
    CheckCampana->SetValue(TRUE);
  }
}

void DialogoNumeroEditar::clickCampana(wxCommandEvent&)
{
  if(CheckCampana->GetValue())
  {
    CheckTrapecio->SetValue(FALSE);
  }else
  {
    CheckTrapecio->SetValue(TRUE);
  }
}


void DialogoNumeroEditar::leerCuadro()
{
  if(EtiFlag)
  {
    Label=TextLabel->GetValue();
  }
}

void DialogoNumeroEditar::cerrarOk(wxCommandEvent&)
{
  leerCuadro();
  EtiTemp->Label=Label;
  *EtiTemp->ND=Num;
  Close();
}

void DialogoNumeroEditar::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoNumeroEditar::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición de Números Difusos"));
}


