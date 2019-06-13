/***************************************************************************
                          dialogovariable.cpp  -  description
                             -------------------
    begin                : mar jul 22 2003
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

#include "dialogovariable.h"


BEGIN_EVENT_TABLE(DialogoVariable, wxDialog)
    EVT_PAINT(DialogoVariable::OnPaint)
    EVT_BUTTON(DLG_VARIABLE_BTN_EDITAR_ETIQUETA , DialogoVariable::editarEtiqueta)
    EVT_BUTTON(DLG_VARIABLE_BTN_NUEVA_ETIQUETA, DialogoVariable::nuevaEtiqueta)
    EVT_BUTTON(DLG_VARIABLE_BTN_BORRAR_ETIQUETA, DialogoVariable::borrarEtiqueta)
    EVT_BUTTON(DLG_VARIABLE_BTN_AUTODEFINIR, DialogoVariable::autodefinir)
    EVT_BUTTON(DLG_VARIABLE_BTN_EDITAR_VALOR, DialogoVariable::editarValor)
    EVT_BUTTON(DLG_VARIABLE_BTN_OK, DialogoVariable::cerrarOk)
    EVT_BUTTON(DLG_VARIABLE_BTN_CANCEL, DialogoVariable::cancelar)
    EVT_BUTTON(DLG_VARIABLE_BTN_AYUDA, DialogoVariable::ayuda)
    EVT_BUTTON(DLG_VARIABLE_BTN_LIBRERIAS, DialogoVariable::librerias)
    EVT_CHECKBOX(DLG_VARIABLE_CHECKBOX_VALOR,DialogoVariable::verValor)
    EVT_LISTBOX(DLG_VARIABLE_LISTBOX_ETIQUETAS,DialogoVariable::seleccionarEtiqueta)
    EVT_CHOICE(DLG_VARIABLE_CHOICE_TIPODEVALOR,DialogoVariable::seleccionarTipoDeValor)
END_EVENT_TABLE()

DialogoVariable::DialogoVariable(VariableLinguistica *var,
          Proyecto *proy, wxWindow *parent,const wxString& title, wxHtmlHelpController *ayuda)
          :wxDialog(parent,-1,title)
{
  Proy=proy;

    VarTemp=var;
    Var=*VarTemp;

    Ayuda=ayuda;

    SetTitle(wxT("Variable Lingüística"));

     ButtonEditarEtiqueta         =new wxButton(this,DLG_VARIABLE_BTN_EDITAR_ETIQUETA, wxT("Editar"));
     ButtonNuevaEtiqueta        =new wxButton(this,DLG_VARIABLE_BTN_NUEVA_ETIQUETA, wxT("Nueva"));
     ButtonBorrarEtiqueta         =new wxButton(this,DLG_VARIABLE_BTN_BORRAR_ETIQUETA, wxT("Borrar"));
     ButtonAutodefinir              =new wxButton(this,DLG_VARIABLE_BTN_AUTODEFINIR, wxT("Autodefinir"));
     ButtonEditarValor              =new wxButton(this,DLG_VARIABLE_BTN_EDITAR_VALOR, wxT("Editar"));
     ButtonOK                         =new wxButton(this,DLG_VARIABLE_BTN_OK, wxT("OK"));
     ButtonCancelar                 =new wxButton(this,DLG_VARIABLE_BTN_CANCEL, wxT("Cancelar"));
     ButtonAyuda                    =new wxButton (this,DLG_VARIABLE_BTN_AYUDA, wxT("Ayuda"));
     ButtonLibrerias                =new wxButton (this,DLG_VARIABLE_BTN_LIBRERIAS, wxT("Librerías"));
     StaticNombre                    =new wxStaticText(this,DLG_VARIABLE_STATIC_NOMBRE, wxT("Nombre"));
     StaticMinimo                     =new wxStaticText(this,DLG_VARIABLE_STATIC_MINIMO, wxT("Mínimo"));
     StaticMaximo                    =new wxStaticText(this,DLG_VARIABLE_STATIC_MAXIMO, wxT("Máximo"));
     StaticUnidades                  =new wxStaticText(this,DLG_VARIABLE_STATIC_UNIDADES, wxT("Unidades"));
     StaticEtiquetas                  =new wxStaticText(this,DLG_VARIABLE_STATIC_ETIQUETAS, wxT("Etiquetas"));
     CheckValor                        =new wxCheckBox(this,DLG_VARIABLE_CHECKBOX_VALOR, wxT("Ver Valor"));
     StaticValorCalculado          =new wxStaticText(this,DLG_VARIABLE_STATIC_VALORCALCULADO, wxT("El Valor es..."));
    TextNombre                       =new wxTextCtrl(this,DLG_VARIABLE_TEXT_NOMBRE);
    TextMinimo                        =new wxTextCtrl(this,DLG_VARIABLE_TEXT_MINIMO);
    TextMaximo                       =new wxTextCtrl(this,DLG_VARIABLE_TEXT_MAXIMO);
    TextUnidades                     =new wxTextCtrl(this,DLG_VARIABLE_TEXT_UNIDADES);
    ListBoxEtiquetas                 =new wxListBox(this,DLG_VARIABLE_LISTBOX_ETIQUETAS,wxPoint(0,0),wxSize(150, 80), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
    ChoiceTipoDeValor       =new wxChoice(this,DLG_VARIABLE_CHOICE_TIPODEVALOR);
    StaticDescripcion          = new wxStaticText(this,DLG_VARIABLE_STATIC_DESCRIPCION,wxT("Descripción"));
    TextDescripcion            = new wxTextCtrl(this,DLG_VARIABLE_TEXT_DESCRIPCION,wxT(""),wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE);

    TextDescripcion->SetMinSize(wxSize(300,80));

/*    ButtonEditarEtiqueta          ->SetSize(80,20);
    ButtonNuevaEtiqueta         ->SetSize(80,20);
    ButtonBorrarEtiqueta          ->SetSize(80,20);
    ButtonAutodefinir               ->SetSize(80,20);
    ButtonEditarValor               ->SetSize(80,20);
    ButtonOK                          ->SetSize(80,20);
    ButtonCancelar                  ->SetSize(80,20);
    ButtonAyuda                      ->SetSize(80,20);*/
    StaticValorCalculado           ->SetMinSize(wxSize(180,20));
    TextNombre                       ->SetMinSize(wxSize(300,20));
    TextMinimo                        ->SetMinSize(wxSize(40,20));
    TextMaximo                       ->SetMinSize(wxSize(40,20));
    TextUnidades                     ->SetMinSize(wxSize(40,20));
    ListBoxEtiquetas                ->SetMinSize(wxSize(100,80));
    ChoiceTipoDeValor       ->SetMinSize(wxSize(120,25));

    CheckValor->SetValue(TRUE);

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

    wxBoxSizer *sizerButEti = new wxBoxSizer(wxVERTICAL);
    sizerButEti->Add(ButtonEditarEtiqueta, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerButEti->Add(ButtonNuevaEtiqueta, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerButEti->Add(ButtonBorrarEtiqueta, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerButEti->Add(ButtonAutodefinir, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerEtiDib = new wxBoxSizer(wxVERTICAL);
    sizerEtiDib->Add(StaticEtiquetas, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerEtiDib->Add(SizerDibujo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerEtiqueta = new wxBoxSizer(wxHORIZONTAL);
    sizerEtiqueta->Add(sizerEtiDib, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);
    sizerEtiqueta->Add(ListBoxEtiquetas, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);
    sizerEtiqueta->Add(sizerButEti, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerValCombo = new wxBoxSizer(wxVERTICAL);
    sizerValCombo->Add(StaticValorCalculado, 0, wxALIGN_LEFT | wxLEFT |wxRIGHT, 5);
    sizerValCombo->Add(ChoiceTipoDeValor, 0, wxALIGN_CENTER |  wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerValor = new wxBoxSizer(wxHORIZONTAL);
    sizerValor->Add(sizerValCombo, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);
    sizerValor->Add(CheckValor, 0, wxALIGN_CENTER |  wxLEFT |wxRIGHT, 5);
    sizerValor->Add(ButtonEditarValor, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonLibrerias, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerDescr = new wxBoxSizer(wxVERTICAL);
    sizerDescr->Add(StaticDescripcion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerDescr->Add(TextDescripcion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerNombre, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerMinMax, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerEtiqueta, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerValor, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerDescr, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoVariable::~DialogoVariable()
{
}

void DialogoVariable::llenarCuadro()
{
  TextDescripcion->SetValue(Var.Descripcion);
  wxString cad;
  cad=wxT(""); cad << Var.Nombre;TextNombre->SetValue(cad);
  cad=wxT(""); cad << Var.Minimo;TextMinimo->SetValue(cad);
  cad=wxT(""); cad << Var.Maximo;TextMaximo->SetValue(cad);
  cad=wxT(""); cad << Var.Unidades;TextUnidades->SetValue(cad);

  int i,tam;
  ListBoxEtiquetas->Clear();
  tam=Var.Etiquetas.GetCount();
  for(i=0;i<tam;i++)
  {
    cad=wxT(""); cad << Var.Etiquetas.Item(i).Label;
    ListBoxEtiquetas->Append(cad);
  }
  ListBoxEtiquetas->SetSelection(0);

  ChoiceTipoDeValor->Clear();
  ChoiceTipoDeValor->Append(wxT("Indefinido"));
  ChoiceTipoDeValor->Append(wxT("Crisp"));
  ChoiceTipoDeValor->Append(wxT("Intervalo"));
  ChoiceTipoDeValor->Append(wxT("Número Difuso"));
  ChoiceTipoDeValor->Append(wxT("Etiqueta"));
  ChoiceTipoDeValor->SetSelection(Var.TipoDeValor);


  Refresh();

  cad=Var.strEntrada();
  cad = wxT("Valor: ") + cad;
  StaticValorCalculado->SetLabel(cad);
}


void DialogoVariable::OnPaint(wxPaintEvent&)
{
  wxPaintDC dc(this);
//  PrepareDC(dc);
  pintar(dc);
}

void DialogoVariable::pintar(wxPaintDC &dc)
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
  tam=Var.Etiquetas.GetCount();
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
    n=Var.Etiquetas.Item(i).ND;
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
      xLo = Origen.x + (xLo - Var.Minimo)*(Tamano.GetWidth())/(Var.Maximo-Var.Minimo);
      xLf = Origen.x + (xLf - Var.Minimo)*(Tamano.GetWidth())/(Var.Maximo-Var.Minimo);
      xRo = Origen.x + (xRo - Var.Minimo)*(Tamano.GetWidth())/(Var.Maximo-Var.Minimo);
      xRf = Origen.x + (xRf - Var.Minimo)*(Tamano.GetWidth())/(Var.Maximo-Var.Minimo);
      // y aumenta hacia abajo !!!
      yo = Origen.y + Tamano.GetHeight() - (yo - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      yf = Origen.y + Tamano.GetHeight() - (yf - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      dc.DrawLine(xLo,yo,xLf,yf);
      dc.DrawLine(xRo,yo,xRf,yf);
    }
    dc.DrawLine(xLf,yf,xRf,yf);
  }
  if(CheckValor->GetValue())
  {
    dc.SetPen(* wxBLACK_PEN);
    NumeroDifuso *n;
    n=Var.valor();
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
      xLo = Origen.x + (xLo - Var.Minimo)*(Tamano.GetWidth())/(Var.Maximo-Var.Minimo);
      xLf = Origen.x + (xLf - Var.Minimo)*(Tamano.GetWidth())/(Var.Maximo-Var.Minimo);
      xRo = Origen.x + (xRo - Var.Minimo)*(Tamano.GetWidth())/(Var.Maximo-Var.Minimo);
      xRf = Origen.x + (xRf - Var.Minimo)*(Tamano.GetWidth())/(Var.Maximo-Var.Minimo);
      // y aumenta hacia abajo !!!
      yo = Origen.y + Tamano.GetHeight() - (yo - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      yf = Origen.y + Tamano.GetHeight() - (yf - 0.0)*(Tamano.GetHeight())/(1.0-0.0);
      dc.DrawLine(xLo,yo,xLf,yf);
      dc.DrawLine(xRo,yo,xRf,yf);
    }
    dc.DrawLine(xLf,yf,xRf,yf);
  }
}

void DialogoVariable::leerTextos()
{
  if(!ESPECIFICO)
  {
    Var.Nombre=TextNombre->GetValue();
    wxString cad;
    double tmp;
    cad=TextMinimo->GetValue();
    if(cad.ToDouble(&tmp))
    {
      Var.Minimo=(float)tmp;
    }
    cad=TextMaximo->GetValue();
    if(cad.ToDouble(&tmp))
    {
      Var.Maximo=(float)tmp;
    }
    Var.Unidades=TextUnidades->GetValue();
  }
  Var.Descripcion=TextDescripcion->GetValue();
}

void DialogoVariable::editarEtiqueta(wxCommandEvent&)
{
  int et;
  et=ListBoxEtiquetas->GetSelection();
  if(et>=0)
  {
    Etiqueta *Et;
    Et=&Var.Etiquetas.Item(et);
    DialogoNumeroEditar dlg(1,Et, Var.Minimo,Var.Maximo,Proy,this, Ayuda);
    dlg.ShowModal();
    llenarCuadro();
    ListBoxEtiquetas->SetSelection(et);
  }
}

void DialogoVariable::nuevaEtiqueta(wxCommandEvent&)
{
  Etiqueta *Et;
  Et=new Etiqueta;
  Et->Label=wxT("Sin Nombre");
  float x=(Var.Maximo+Var.Minimo)/2.0;
  Et->ND->trapecio(x,x,x,x);
  int n=ListBoxEtiquetas->GetSelection();
  Var.Etiquetas.Insert(Et,n+1);
  llenarCuadro();
  ListBoxEtiquetas->SetSelection(n+1);
  Refresh();
}

void DialogoVariable::borrarEtiqueta(wxCommandEvent&)
{
  int tam;
  tam=Var.Etiquetas.GetCount();
  if(tam<2)
  {
    wxMessageBox(wxT("Debe haber al menos una Etiqueta"),wxT("Alerta"),wxOK,this);
  }else
  {
    int n;
    n=ListBoxEtiquetas->GetSelection();
    wxString cad;
    cad << wxT("Desea borrar la Etiqueta '") <<ListBoxEtiquetas->GetStringSelection() << wxT("'?");
    if(wxMessageBox(cad,wxT("Alerta"),wxICON_QUESTION | wxYES_NO,this)==wxYES)
    {
      Var.Etiquetas.RemoveAt(n);
      llenarCuadro();
      if(Var.Etiquetas.GetCount()-1 < n)
      {
        ListBoxEtiquetas->SetSelection(n-1);
      }
      Refresh();
    }
  }
}

void DialogoVariable::autodefinir(wxCommandEvent&)
{
  leerTextos();
  DialogoAutodefinirVariable dlg(&Var,Proy,this,wxT("PRUEBA"), Ayuda);
  dlg.ShowModal();
  llenarCuadro();
}

void DialogoVariable::editarValor(wxCommandEvent&)
{
  wxString cad;
  wxTextEntryDialog *dlgTxt;
  wxDialog *dlg;
  Etiqueta Et;
  switch (Var.TipoDeValor)
  {
    case 0 : // Indefinido
              wxMessageBox(wxT("Seleccione primero un Tipo de Valor"),wxT("Atención"), wxOK | wxICON_INFORMATION, this);
              break;
    case 1 : // Crisp
              cad << Var.Crisp;
              dlgTxt=new wxTextEntryDialog(this,cad,wxT("Número Crisp"));
              if(dlgTxt->ShowModal()==wxID_OK)
              {
                cad=dlgTxt->GetValue();
                double F;
                cad.ToDouble(&F);
                Var.Crisp=(float)F;
              }
              delete dlgTxt;
              break;
    case 2 : // Intervalo
              dlg=new DialogoIntervalo(&Var.IntA,&Var.IntB,Proy,this, Ayuda);
              dlg->ShowModal();
              delete dlg;
              break;
    case 3 : // Nmero difuso
              *Et.ND=Var.NumDif;
              dlg=new DialogoNumeroEditar(0,&Et, Var.Minimo,Var.Maximo,Proy,this, Ayuda);
              dlg->ShowModal();
              delete dlg;
              Var.NumDif=*Et.ND;
              break;
    case 4 : // Etiqueta
              dlg = new DialogoModificador(&Var,Proy,this,wxT("PRUEBA"), Ayuda);
              dlg->ShowModal();
              break;
    default : //
//              noImplementada();
              break;
  }
  llenarCuadro();
}

void DialogoVariable::seleccionarEtiqueta(wxCommandEvent&)
{
  if(Var.TipoDeValor==4)
  {
    Var.EtiquetaSeleccionada=ListBoxEtiquetas->GetSelection();
    llenarCuadro();
    ListBoxEtiquetas->SetSelection(Var.EtiquetaSeleccionada);
  }else
  {
    Refresh();
  }
}

void DialogoVariable::verValor(wxCommandEvent&)
{
  Refresh();
}

void DialogoVariable::seleccionarTipoDeValor(wxCommandEvent&)
{
  Var.TipoDeValor=ChoiceTipoDeValor->GetSelection();
//  llenarCuadro();
  Refresh();
  wxString cad;
  cad=Var.strEntrada();
  cad = wxT("Valor: ") + cad;
  StaticValorCalculado->SetLabel(cad);
}

void DialogoVariable::cerrarOk(wxCommandEvent&)
{
  leerTextos();
  *VarTemp=Var;
  Close();
}

void DialogoVariable::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoVariable::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición de Variables Lingüísticas"));
}

void DialogoVariable::librerias(wxCommandEvent&)
{
  wxString dirActual;
  dirActual=wxGetCwd();
  DialogoLibreria dlg(NULL,NULL,&Var,this,wxT("Librerías de Fuzzynet"), Ayuda);
  dlg.ShowModal();
  wxSetWorkingDirectory(dirActual);
}

