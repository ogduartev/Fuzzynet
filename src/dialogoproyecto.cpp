/***************************************************************************
                          dialogoproyecto.cpp  -  description
                             -------------------
    begin                : jue jul 24 2003
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

#include "dialogoproyecto.h"

BEGIN_EVENT_TABLE(DialogoProyecto, wxDialog)
    EVT_BUTTON(DLG_PROYECTO_BTN_EDITAR_ESTRATEGIA, DialogoProyecto::editarEstrategia)
    EVT_BUTTON(DLG_PROYECTO_BTN_NUEVA_ESTRATEGIA, DialogoProyecto::nuevaEstrategia)
    EVT_BUTTON(DLG_PROYECTO_BTN_BORRAR_ESTRATEGIA, DialogoProyecto::borrarEstrategia)
//    EVT_BUTTON(DLG_PROYECTO_BTN_ORDENAR_ESTRATEGIA, DialogoProyecto::noImplementada)
    EVT_BUTTON(DLG_PROYECTO_BTN_EDITAR_CASO, DialogoProyecto::editarCaso)
    EVT_BUTTON(DLG_PROYECTO_BTN_NUEVO_CASO, DialogoProyecto::nuevoCaso)
    EVT_BUTTON(DLG_PROYECTO_BTN_BORRAR_CASO, DialogoProyecto::borrarCaso)
    EVT_BUTTON(DLG_PROYECTO_BTN_ORDENAR_CASO, DialogoProyecto::ordenarCasos)
    EVT_BUTTON(DLG_PROYECTO_BTN_PROPIEDADES, DialogoProyecto::propiedades)
    EVT_BUTTON(DLG_PROYECTO_BTN_OK, DialogoProyecto::cerrarOK)
//    EVT_BUTTON(DLG_PROYECTO_BTN_CANCELAR, DialogoProyecto::noImplementada)
    EVT_BUTTON(DLG_PROYECTO_BTN_AYUDA, DialogoProyecto::ayuda)
    EVT_LISTBOX(DLG_PROYECTO_LISTBOX_ESTRATEGIAS,DialogoProyecto::seleccionEstrategia)
    EVT_LISTBOX(DLG_PROYECTO_LISTBOX_CASOS,DialogoProyecto::seleccionCaso)
END_EVENT_TABLE()

DialogoProyecto::DialogoProyecto(
      Proyecto *pr, MiCanvas *canvas,wxWindow *parent, const wxString& title, wxHtmlHelpController *ayuda)
      :wxDialog(parent,-1,title)
{
    Proy=pr;
    Canvas=canvas;
    Ayuda=ayuda;
    
    SetTitle(wxT("Proyecto"));

    if(!ESPECIFICO)
    {
      ButtonEditarEstrategia = new wxButton(this,DLG_PROYECTO_BTN_EDITAR_ESTRATEGIA, wxT("Editar"));
      ButtonNuevaEstrategia = new wxButton(this,DLG_PROYECTO_BTN_NUEVA_ESTRATEGIA, wxT("Nueva"));
      ButtonBorrarEstrategia = new wxButton(this,DLG_PROYECTO_BTN_BORRAR_ESTRATEGIA, wxT("Borrar"));
      ListBoxEstrategias = new wxListBox(this,DLG_PROYECTO_LISTBOX_ESTRATEGIAS,wxPoint(0,0),wxSize(150, 80), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
      StaticEstrategias = new wxStaticText(this,DLG_PROYECTO_STATIC_ESTRATEGIAS,wxT("Metodologías"));
      ListBoxEstrategias->SetMinSize(wxSize(150,100));
    }
//    ButtonOrdenarEstrategia = new wxButton(this,DLG_PROYECTO_BTN_ORDENAR_ESTRATEGIA, wxT("Ordenar"));
    ButtonEditarCaso = new wxButton(this,DLG_PROYECTO_BTN_EDITAR_CASO, wxT("Editar"));
    ButtonNuevoCaso = new wxButton(this,DLG_PROYECTO_BTN_NUEVO_CASO, wxT("Nuevo"));
    ButtonBorrarCaso = new wxButton(this,DLG_PROYECTO_BTN_BORRAR_CASO, wxT("Borrar"));
    ButtonOrdenarCaso = new wxButton(this,DLG_PROYECTO_BTN_ORDENAR_CASO, wxT("Ordenar"));
    ButtonPropiedades = new wxButton(this,DLG_PROYECTO_BTN_PROPIEDADES, wxT("Propiedades"));
    ButtonOK = new wxButton(this,DLG_PROYECTO_BTN_OK, wxT("OK"));
//    ButtonCancelar = new wxButton(this,DLG_PROYECTO_BTN_CANCELAR, wxT("Cancelar"));
    ButtonAyuda = new wxButton(this,DLG_PROYECTO_BTN_AYUDA, wxT("Ayuda"));
    ListBoxCasos = new wxListBox(this,DLG_PROYECTO_LISTBOX_CASOS,wxPoint(0,0),wxSize(150, 80), 0, 0, wxLB_SINGLE|wxLB_ALWAYS_SB);
    StaticCasos = new wxStaticText(this,DLG_PROYECTO_STATIC_ESTRATEGIAS,wxT("Casos"));
    StaticOptimismo = new wxStaticText(this,DLG_PROYECTO_STATIC_OPTIMISMO,wxT("Optimismo (%)"));
    StaticRepresentatividad = new wxStaticText(this,DLG_PROYECTO_STATIC_REPRESENTATIVIDAD,wxT("Representatividad"));
    StaticDescripcion = new wxStaticText(this,DLG_PROYECTO_STATIC_DESCRIPCION,wxT("Descripción"));
    TextDescripcion = new wxTextCtrl(this,DLG_PROYECTO_TEXT_DESCRIPCION,wxT(""),wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE);
    TextOptimismo = new wxTextCtrl(this,DLG_PROYECTO_TEXT_OPTIMISMO);
    TextRepresentatividad = new wxTextCtrl(this,DLG_PROYECTO_TEXT_REPRESENTATIVIDAD);

    TextDescripcion->SetMinSize(wxSize(300,80));
    ListBoxCasos->SetMinSize(wxSize(150,100));
    
    wxBoxSizer *sizerButEst;
    if(!ESPECIFICO)
    {
      sizerButEst = new wxBoxSizer(wxVERTICAL);
      sizerButEst->Add(ButtonEditarEstrategia, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 0);
      sizerButEst->Add(ButtonNuevaEstrategia, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 0);
      sizerButEst->Add(ButtonBorrarEstrategia, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 0);
    }

    wxBoxSizer *sizerButCas = new wxBoxSizer(wxVERTICAL);
    sizerButCas->Add(ButtonEditarCaso, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 0);
    sizerButCas->Add(ButtonNuevoCaso, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 0);
    sizerButCas->Add(ButtonBorrarCaso, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 0);
    sizerButCas->Add(ButtonOrdenarCaso, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 0);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerListEst;
    if(!ESPECIFICO)
    {
      sizerListEst = new wxBoxSizer(wxVERTICAL);
      sizerListEst->Add(StaticEstrategias, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
      sizerListEst->Add(ListBoxEstrategias, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    }

    wxBoxSizer *sizerListCas = new wxBoxSizer(wxVERTICAL);
    sizerListCas->Add(StaticCasos, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerListCas->Add(ListBoxCasos, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerGrilla1;
    if(!ESPECIFICO)
    {
      sizerGrilla1 = new wxBoxSizer(wxHORIZONTAL);
      sizerGrilla1->Add(sizerListEst, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);
      sizerGrilla1->Add(sizerButEst, 0, wxALIGN_BOTTOM| wxLEFT |wxRIGHT, 5);
    }

    wxBoxSizer *sizerGrilla2 = new wxBoxSizer(wxHORIZONTAL);
    sizerGrilla2->Add(sizerListCas, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);
    sizerGrilla2->Add(sizerButCas, 0, wxALIGN_BOTTOM | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerOpt = new wxBoxSizer(wxVERTICAL);
    sizerOpt->Add(StaticOptimismo, 0, wxALIGN_RIGHT | wxLEFT |wxRIGHT, 5);
    sizerOpt->Add(StaticRepresentatividad, 0, wxALIGN_RIGHT | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerRep = new wxBoxSizer(wxVERTICAL);
    sizerRep->Add(TextOptimismo, 0, wxALIGN_LEFT | wxLEFT |wxRIGHT, 5);
    sizerRep->Add(TextRepresentatividad, 0, wxALIGN_LEFT | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerTexto = new wxBoxSizer(wxHORIZONTAL);
    sizerTexto->Add(sizerOpt, 0, wxALIGN_RIGHT | wxLEFT |wxRIGHT, 5);
    sizerTexto->Add(sizerRep, 0, wxALIGN_LEFT | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerDescr = new wxBoxSizer(wxVERTICAL);
    sizerDescr->Add(StaticDescripcion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerDescr->Add(TextDescripcion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    if(!ESPECIFICO)
    {
      sizerTotal->Add(sizerGrilla1, 0, wxALIGN_CENTER | wxALL, 5);
    }
    sizerTotal->Add(sizerGrilla2, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerTexto, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(ButtonPropiedades, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerDescr, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoProyecto::~DialogoProyecto()
{
}  

void DialogoProyecto::cerrarOK(wxCommandEvent&)
{
  leerCuadro();
  Close();
}

void DialogoProyecto::llenarCuadro()
{
  TextDescripcion->SetValue(Proy->Descripcion);
  int i,tam;
  if(!ESPECIFICO)
  {
    ListBoxEstrategias->Clear();
    tam=Proy->Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      ListBoxEstrategias->Append(Proy->Estrategias.Item(i).Nombre);
    }
    ListBoxEstrategias->SetSelection(Proy->NumEstrategia);
  }
  
  ListBoxCasos->Clear();
  tam=Proy->Casos.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxCasos->Append(Proy->Casos.Item(i).Nombre);
  }
  ListBoxCasos->SetSelection(Proy->NumCaso);

  wxString cad=wxT("");
  cad << Proy->Optimismo*100.0;
  TextOptimismo->SetValue(cad);
  cad = wxT("");
  cad << Proy->Representatividad;
  TextRepresentatividad->SetValue(cad);
}

void DialogoProyecto::leerCuadro()
{
  Proy->ProyectoModificado=TRUE;
  Proy->Descripcion=TextDescripcion->GetValue();
  wxString cad;
  double d;
  cad=TextOptimismo->GetValue();
  cad.ToDouble(&d);
  Proy->Optimismo=(float)d/100.0;
  cad=TextRepresentatividad->GetValue();
  cad.ToDouble(&d);
  Proy->Representatividad=(float)d;
}

void DialogoProyecto::nuevaEstrategia(wxCommandEvent&)
{
  leerCuadro();
  wxTextEntryDialog dlg(this,wxT("Nombre de la Metodología"));
  if(dlg.ShowModal()==wxID_OK)
  {
    wxString cad;
    cad=dlg.GetValue();

    if(ListBoxEstrategias->FindString(cad)!=-1)
    {
      wxMessageBox(wxT("Ya existe una Metodología con ese nombre"),wxT("Alerta"),wxOK,this);
    }else
    {
      Estrategia *Est;
      Est= new Estrategia;
      Est->Nombre=cad;
      Est->Grafo.ProyectoTotal=Proy;
      int n=ListBoxEstrategias->GetSelection();
      Proy->Estrategias.Insert(Est,n+1);
      Proy->NumEstrategia=n+1;

      llenarCuadro();
    }
  }
}

void DialogoProyecto::nuevoCaso(wxCommandEvent&)
{
  leerCuadro();
  wxTextEntryDialog dlg(this,wxT("Nombre del Caso"));
  if(dlg.ShowModal()==wxID_OK)
  {
    wxString cad;
    cad=dlg.GetValue();
    if(ListBoxCasos->FindString(cad)!=-1)
    {
      wxMessageBox(wxT("Ya existe un Caso con ese nombre"),wxT("Alerta"),wxOK,this);
    }else
    {
      Caso *Cas;
      Cas= new Caso;
      Cas->Nombre=cad;
      int n=ListBoxCasos->GetSelection();
      Proy->Casos.Insert(Cas,n+1);
      Proy->NumCaso=n+1;
    }
    llenarCuadro();
  }
}

void DialogoProyecto::borrarEstrategia(wxCommandEvent&)
{
  leerCuadro();
  int tam;
  tam=Proy->Estrategias.GetCount();
  if(tam<2)
  {
    wxMessageBox(wxT("Debe haber al menos una Metodología"),wxT("Alerta"),wxOK,this);
  }else
  {
    int n;
    n=ListBoxEstrategias->GetSelection();
    wxString cad;
    cad << wxT("Desea borrar la Metodología '") <<ListBoxEstrategias->GetStringSelection() << wxT("'?");
    if(wxMessageBox(cad,wxT("Alerta"),wxICON_QUESTION | wxYES_NO,this)==wxYES)
    {
      Proy->Estrategias.RemoveAt(n);
      if(Proy->Estrategias.GetCount()-1 < n)
      {
        Proy->NumEstrategia=n-1;
      }
      llenarCuadro();
    }
  }
}

void DialogoProyecto::borrarCaso(wxCommandEvent&)
{
  leerCuadro();
  int tam;
  tam=Proy->Casos.GetCount();
  if(tam<2)
  {
    wxMessageBox(wxT("Debe haber al menos un Caso"),wxT("Alerta"),wxOK,this);
  }else
  {
    int n;
    n=ListBoxCasos->GetSelection();
    wxString cad;
    cad << wxT("Desea borrar el Caso '") <<ListBoxCasos->GetStringSelection() << wxT("'?");
    if(wxMessageBox(cad,wxT("Alerta"),wxICON_QUESTION | wxYES_NO,this)==wxYES)
    {
      Proy->Casos.RemoveAt(n);
      if(Proy->Casos.GetCount()-1 < n)
      {
        Proy->NumCaso=n-1;
      }
      llenarCuadro();
    }
  }
}

void DialogoProyecto::editarEstrategia(wxCommandEvent&)
{
  leerCuadro();
  Estrategia *Est;
  Est=&Proy->Estrategias.Item(ListBoxEstrategias->GetSelection());
  DialogoEstrategia dlg(Est, Proy, Canvas, this, Ayuda);
  dlg.ShowModal();
  llenarCuadro();
}


void DialogoProyecto::editarCaso(wxCommandEvent&)
{
  leerCuadro();
  int n;
  n=ListBoxCasos->GetSelection();
  Caso *cas;
  cas=&Proy->Casos.Item(n);
  DialogoCaso dlg(Canvas,cas, Proy,this, Ayuda);
  dlg.ShowModal();
  llenarCuadro();
}

void DialogoProyecto::seleccionEstrategia(wxCommandEvent&)
{
  int n;
  n=ListBoxEstrategias->GetSelection();
  Proy->NumEstrategia=n;
}

void DialogoProyecto::seleccionCaso(wxCommandEvent&)
{
  int n;
  n=ListBoxCasos->GetSelection();
  Proy->NumCaso=n;
}


void DialogoProyecto::ordenarCasos(wxCommandEvent&)
{
  leerCuadro();
  DialogoOrdenarCasos dlg(Proy,this, Ayuda);
  dlg.ShowModal();
  llenarCuadro();
}

void DialogoProyecto::propiedades(wxCommandEvent&)
{
  leerCuadro();
  DialogoPropiedades dlg(&Proy->Generalidades,this, Ayuda);
  dlg.ShowModal();
  llenarCuadro();
}

void DialogoProyecto::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición del Proyecto"));
}
