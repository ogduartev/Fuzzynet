/***************************************************************************
                          dialogonodo.cpp  -  description
                             -------------------
    begin                : mar ago 5 2003
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

#include "dialogonodo.h"

BEGIN_EVENT_TABLE(DialogoNodo, wxDialog)
    EVT_BUTTON(DLG_NODO_BTN_EDITAR_HIJO , DialogoNodo::editarHijo)
    EVT_BUTTON(DLG_NODO_BTN_NUEVO_HIJO, DialogoNodo::nuevoHijo)
    EVT_BUTTON(DLG_NODO_BTN_BORRAR_HIJO, DialogoNodo::borrarHijo)
    EVT_BUTTON(DLG_NODO_BTN_EDITAR_VARIABLE , DialogoNodo::editarVariable)
//    EVT_BUTTON(DLG_NODO_BTN_EDITAR_PARFIJOS , DialogoNodo::editarParFijo)
    EVT_BUTTON(DLG_NODO_BTN_OK, DialogoNodo::cerrarOk)
    EVT_BUTTON(DLG_NODO_BTN_CANCEL, DialogoNodo::cancelar)
    EVT_BUTTON(DLG_NODO_BTN_AYUDA, DialogoNodo::ayuda)
//    EVT_GRID_EDITOR_HIDDEN(DialogoNodo::cambiaCelda)
    EVT_GRID_CELL_CHANGE(DialogoNodo::cambiaCelda)
//    EVT_CHECKBOX(DLG_NODO_CHECKBOX_FORMAVARIABLE,DialogoNodo::clickVariable)
//    EVT_CHECKBOX(DLG_NODO_CHECKBOX_FORMANODOS,DialogoNodo::clickNodos)
    EVT_CHOICE(DLG_NODO_CHOICE_FORMACALCULO,DialogoNodo::cambiarFormaCalculo)
    EVT_CHOICE(DLG_NODO_CHOICE_FUNCION,DialogoNodo::cambiarFuncion)
    EVT_SPINCTRL(DLG_NODO_SPIN_HORIZONTAL,DialogoNodo::cambiaSpinH)
    EVT_SPINCTRL(DLG_NODO_SPIN_VERTICAL,DialogoNodo::cambiaSpinV)
    EVT_LISTBOX_DCLICK(DLG_NODO_LISTBOX_PARFIJOS,DialogoNodo::editarParFijo)
END_EVENT_TABLE()

DialogoNodo::DialogoNodo(NodoCalculo *nod,
          Proyecto *proy, wxWindow *parent,const wxString& title, wxHtmlHelpController *ayuda)
          :wxDialog(parent,-1,title)
{
  Proy=proy;

  NodTemp=nod;
  Nod=NodTemp;
//  Nod=*VarTemp;
  Ayuda=ayuda;

  SetTitle(wxT("Nodo de Cálculo"));

    ButtonVariable               =new wxButton(this,DLG_NODO_BTN_EDITAR_VARIABLE, wxT("Variable"));
    ButtonEditarHijo             =new wxButton(this,DLG_NODO_BTN_EDITAR_HIJO, wxT("Editar"));
    if(!ESPECIFICO)
    {
      ButtonNuevoHijo              =new wxButton(this,DLG_NODO_BTN_NUEVO_HIJO, wxT("Nuevo"));
      ButtonBorrarHijo             =new wxButton(this,DLG_NODO_BTN_BORRAR_HIJO, wxT("Borrar"));
    }
    ButtonOK                     =new wxButton(this,DLG_NODO_BTN_OK, wxT("OK"));
//    ButtonCancelar               =new wxButton(this,DLG_NODO_BTN_CANCEL, wxT("Cancelar"));
    ButtonAyuda                  =new wxButton (this,DLG_NODO_BTN_AYUDA, wxT("Ayuda"));
//    ButtonEditarParFijos         =new wxButton(this,DLG_NODO_BTN_EDITAR_PARFIJOS, wxT("Editar"));
    StaticNombre                 =new wxStaticText(this,DLG_NODO_STATIC_NOMBRE, wxT("Nombre"));
    StaticPadres                 =new wxStaticText(this,DLG_NODO_STATIC_PADRES, wxT("Padres"));
    StaticHijos                  =new wxStaticText(this,DLG_NODO_STATIC_HIJOS, wxT("Hijos"));
    StaticParFijos               =new wxStaticText(this,DLG_NODO_STATIC_PARFIJOS, wxT("Parámetros"));
    StaticParVariables           =new wxStaticText(this,DLG_NODO_STATIC_PARVARIABLES, wxT("Coeficientes"));
    StaticFuncion                =new wxStaticText(this,DLG_NODO_STATIC_FUNCION, wxT("Función"));
    StaticSpinH                  =new wxStaticText(this,DLG_NODO_STATIC_SPINH, wxT("Offset Horizontal"));
    StaticSpinV                  =new wxStaticText(this,DLG_NODO_STATIC_SPINV, wxT("Offset Vertical"));
    StaticFormaCalculo           =new wxStaticText(this,DLG_NODO_STATIC_FORMACALCULO, wxT("Forma de Cálculo"));
    ListBoxPadres                =new wxListBox(this,DLG_NODO_LISTBOX_PADRES, wxDefaultPosition, wxSize(150,100));
    ListBoxHijos                 =new wxListBox(this,DLG_NODO_LISTBOX_HIJOS, wxDefaultPosition, wxSize(150,100));
    ListBoxParFijos              =new wxListBox(this,DLG_NODO_LISTBOX_PARFIJOS, wxDefaultPosition, wxDefaultSize);
    ChoiceFormaCalculo         =new wxChoice(this,DLG_NODO_CHOICE_FORMACALCULO);
    ChoiceFuncion              =new wxChoice(this,DLG_NODO_CHOICE_FUNCION);
//    CheckBoxFormaVariable        =new wxCheckBox(this,DLG_NODO_CHECKBOX_FORMAVARIABLE,wxT("Forzar como Entrada"));
//    CheckBoxFormaNodos           =new wxCheckBox(this,DLG_NODO_CHECKBOX_FORMANODOS,wxT("Cálculo con Nodos Hijos"));
    SpinOffsetHorizontal         =new wxSpinCtrl(this,DLG_NODO_SPIN_HORIZONTAL);
    SpinOffsetVertical           =new wxSpinCtrl(this,DLG_NODO_SPIN_VERTICAL);
    GrillaParVariables           =new wxGrid(this,DLG_NODO_GRID_GRILLAPARVARIABLES,wxPoint(20,20),wxSize(200,100));
    StaticDescripcion            = new wxStaticText(this,DLG_NODO_STATIC_DESCRIPCION,wxT("Descripción"));
    TextDescripcion             = new wxTextCtrl(this,DLG_NODO_TEXT_DESCRIPCION,wxT(""),wxDefaultPosition,wxDefaultSize, wxTE_MULTILINE);
    StaticExtendido            = new wxStaticText(this,DLG_NODO_STATIC_EXTENDIDO,wxT("Nombre Extendido"));
    TextExtendido             = new wxTextCtrl(this,DLG_NODO_TEXT_EXTENDIDO,wxT(""),wxDefaultPosition,wxDefaultSize);

    TextDescripcion->SetMinSize(wxSize(300,80));
    TextExtendido->SetMinSize(wxSize(300,25));

  int i,j,tam,tam2;
  tam=Nod->FuncionCalculo->Orden+1;
  tam2=Nod->FuncionCalculo->NombreParametrosVariables.GetCount()+1;
  GrillaParVariables->CreateGrid(tam,tam2);
  GrillaParVariables->SetColLabelSize(0);
  GrillaParVariables->SetRowLabelSize(0);
  for(i=0;i<tam;i++)
  {
   for(j=0;j<tam2;j++)
   {
     GrillaParVariables->SetReadOnly(i,j);
   }
  }
//  GrillaParVariables->SetColLabelValue(0,"L");
//  GrillaParVariables->SetColLabelValue(1,"R");
    ChoiceFuncion->Append(wxT("Combinación Lineal"));
    ChoiceFuncion->Append(wxT("Supremo"));
    ChoiceFuncion->Append(wxT("Infimo"));
    ChoiceFuncion->Append(wxT("Combinación Lineal Acotada"));
    ChoiceFuncion->Append(wxT("Suma-Producto"));
    ChoiceFuncion->Append(wxT("Producto-Suma"));
    ChoiceFuncion->Append(wxT("Polinomio"));
    ChoiceFuncion->Append(wxT("Ranking"));
    ChoiceFuncion->Append(wxT("Ranking OWA"));
    ChoiceFuncion->Append(wxT("OWA Faulhaber"));
    ChoiceFuncion->Append(wxT("Producto"));
    ChoiceFuncion->SetMinSize(wxSize(150,25));

    int anchoListas=150;
//    ButtonEditarHijo->SetSize(80,20);
//    ButtonNuevoHijo->SetSize(80,20);
//    ButtonBorrarHijo->SetSize(80,20);
    ListBoxPadres->SetSize(anchoListas,80);
    ListBoxHijos->SetSize(anchoListas,80);
    ChoiceFormaCalculo->SetMinSize(wxSize(150,25));

    SpinOffsetHorizontal->SetMinSize(wxSize(40,25));
    SpinOffsetVertical->SetMinSize(wxSize(40,25));
    SpinOffsetHorizontal->SetRange(0,1000);
    SpinOffsetVertical->SetRange(0,1000);

    StaticNombre->SetMinSize(wxSize(anchoListas*2+30,20));

    wxBoxSizer *sizerExtendido = new wxBoxSizer(wxHORIZONTAL);
    sizerExtendido->Add(StaticExtendido, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerExtendido->Add(TextExtendido, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerButHijos = new wxBoxSizer(wxVERTICAL);
    sizerButHijos->Add(ButtonEditarHijo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    if(!ESPECIFICO)
    {
      sizerButHijos->Add(ButtonNuevoHijo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
      sizerButHijos->Add(ButtonBorrarHijo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    }

    wxBoxSizer *sizerListaPadres = new wxBoxSizer(wxVERTICAL);
    sizerListaPadres->Add(StaticPadres, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerListaPadres->Add(ListBoxPadres, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerListaHijos = new wxBoxSizer(wxVERTICAL);
    sizerListaHijos->Add(StaticHijos, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerListaHijos->Add(ListBoxHijos, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerListas = new wxBoxSizer(wxHORIZONTAL);
    sizerListas->Add(sizerListaPadres, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerListas->Add(sizerListaHijos, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerListas->Add(sizerButHijos, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerSuperior = new wxBoxSizer(wxHORIZONTAL);
    sizerSuperior->Add(StaticNombre, 0, wxALIGN_LEFT | wxLEFT |wxRIGHT, 5);
    sizerSuperior->Add(ButtonVariable, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerListaParFijos = new wxBoxSizer(wxVERTICAL);
    sizerListaParFijos->Add(StaticFuncion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerListaParFijos->Add(ChoiceFuncion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT |wxBOTTOM, 5);
    sizerListaParFijos->Add(StaticParFijos, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerListaParFijos->Add(ListBoxParFijos, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerListaParVar = new wxBoxSizer(wxVERTICAL);
    sizerListaParVar->Add(StaticParVariables, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerListaParVar->Add(GrillaParVariables, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxGridSizer *sizerSpin = new wxGridSizer(2,2,5,10);
    sizerSpin->Add(StaticSpinH, 0, wxALIGN_TOP | wxLEFT |wxRIGHT, 5);
    sizerSpin->Add(SpinOffsetHorizontal, 0, wxALIGN_TOP | wxLEFT |wxRIGHT, 5);
    sizerSpin->Add(StaticSpinV, 0, wxALIGN_TOP | wxLEFT |wxRIGHT, 5);
    sizerSpin->Add(SpinOffsetVertical, 0, wxALIGN_TOP | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerFormaCalculo = new wxBoxSizer(wxVERTICAL);
    sizerFormaCalculo->Add(StaticFormaCalculo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT , 5);
    sizerFormaCalculo->Add(ChoiceFormaCalculo, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT , 5);

    wxBoxSizer *sizerPar = new wxBoxSizer(wxHORIZONTAL);
    sizerPar->Add(sizerFormaCalculo, 0, wxALIGN_TOP | wxLEFT |wxRIGHT, 5);
    sizerPar->Add(sizerListaParFijos, 0, wxALIGN_TOP | wxLEFT |wxRIGHT, 5);
    sizerPar->Add(sizerListaParVar, 0, wxALIGN_TOP | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
//    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerDescr = new wxBoxSizer(wxVERTICAL);
    sizerDescr->Add(StaticDescripcion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerDescr->Add(TextDescripcion, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);

    wxBoxSizer *sizerDs = new wxBoxSizer(wxHORIZONTAL);
    sizerDs->Add(sizerSpin, 0, wxALIGN_CENTER |wxRIGHT, 10);
    sizerDs->Add(sizerDescr, 0, wxALIGN_CENTER |wxRIGHT, 10);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerSuperior, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerExtendido, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerListas, 0, wxALIGN_CENTER | wxLEFT |wxRIGHT, 5);
    sizerTotal->Add(sizerPar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerDs, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoNodo::~DialogoNodo()
{
}

void DialogoNodo::llenarCuadro()
{
  TextDescripcion->SetValue(Nod->Descripcion);
  int i,j,tam,tam2;
  wxString cad;
  cad= wxT("Nombre: ") + Nod->VarCalculada.Nombre;
  StaticNombre->SetLabel(cad);

  TextExtendido->SetValue(Nod->NombreExtendido);

  ListBoxPadres->Clear();
  tam=Nod->NodosPadre.GetCount();
  for(i=0;i<tam;i++)
  {
    cad=Nod->NodosPadre.Item(i).VarCalculada.Nombre;
    ListBoxPadres->Append(cad);
  }
  if(tam>0)
  {
    ListBoxPadres->SetSelection(0);
  }

  ListBoxHijos->Clear();
  tam=Nod->NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    cad=Nod->NodosDeCalculo.Item(i).VarCalculada.Nombre;
    ListBoxHijos->Append(cad);
  }
  if(tam>0)
  {
    ListBoxHijos->SetSelection(0);
  }

  ChoiceFuncion->SetStringSelection(Nod->FuncionCalculo->Tipo);

/*
  if(Nod->FormaDeCalculo==0)
  {
    CheckBoxFormaVariable->SetValue(TRUE);
//    CheckBoxFormaNodos->SetValue(FALSE);
  }else
  {
    CheckBoxFormaVariable->SetValue(FALSE);
//    CheckBoxFormaNodos->SetValue(TRUE);
  }
*/
  ChoiceFormaCalculo->Clear();
  cad=wxT("Forzar como Entrada");
  ChoiceFormaCalculo->Append(cad);
  cad=wxT("Con Nodos Hijos");
  ChoiceFormaCalculo->Append(cad);
  tam=Proy->Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    cad=Proy->Estrategias.Item(i).Nombre;
    ChoiceFormaCalculo->Append(cad);
  }
  if(Nod->FormaDeCalculo<2)
  {
    ChoiceFormaCalculo->SetSelection(Nod->FormaDeCalculo);
  }else
  {
    ChoiceFormaCalculo->SetStringSelection(Nod->EstrategiaCalculo);
  }

  ListBoxParFijos->Clear();
  tam=Nod->FuncionCalculo->NombreParametrosFijos.GetCount();
  for(i=0;i<tam;i++)
  {
    cad=Nod->FuncionCalculo->NombreParametrosFijos.Item(i);
    cad << wxT(": ") << Nod->FuncionCalculo->ParametrosFijos[i];
    ListBoxParFijos->Append(cad);
  }
  if(tam>0)
  {
    ListBoxParFijos->SetSelection(0);
  }
  //////////  SpinCtrl
  // la clase wxSpinCtrl tiene un bug: no `putde escrobir el dato 0
  // este parche escribe una N en lugar del 0
  int Off;
  Off=Nod->OffsetPosicionEnNivel;
  if(Off==0)
  {
    SpinOffsetHorizontal->SetValue(wxT("N"));
  }else
  {
    SpinOffsetHorizontal->SetValue(Off);
  }
  Off=Nod->OffsetNivel;
  if(Off==0)
  {
    SpinOffsetVertical->SetValue(wxT("N"));
  }else
  {
    SpinOffsetVertical->SetValue(Off);
  }
  ////////// Grilla
  // OJO: eliminar columnas y filas
  tam=GrillaParVariables->GetNumberRows();
  tam2=GrillaParVariables->GetNumberCols();
  GrillaParVariables->DeleteRows(0,tam);
  GrillaParVariables->DeleteCols(0,tam2);
  //y crear las filas y columnas necesarias!!!!
  tam=Nod->FuncionCalculo->Orden;
  tam2=Nod->FuncionCalculo->NombreParametrosVariables.GetCount();
  GrillaParVariables->InsertRows(0,tam+1);
  GrillaParVariables->InsertCols(0,tam2+1);
  for(i=0;i<tam;i++)
  {
    cad = Nod->NodosDeCalculo.Item(i).VarCalculada.Nombre;
    GrillaParVariables->SetCellValue(i+1,0,cad);
    for(j=0;j<tam2;j++)
    {
      cad =wxT("");
      cad << Nod->FuncionCalculo->ParametrosVariables[i][j];
      GrillaParVariables->SetCellValue(i+1,j+1,cad);
      if(!ESPECIFICO)
      {
        GrillaParVariables->SetReadOnly(i+1,j+1,FALSE);
      }else
      {
        GrillaParVariables->SetReadOnly(i+1,j+1,TRUE);
      }
    }
  }
  for(j=0;j<tam2;j++)
  {
    cad = Nod->FuncionCalculo->NombreParametrosVariables.Item(j);
    GrillaParVariables->SetCellValue(0,j+1,cad);
  }
}

void DialogoNodo::editarVariable(wxCommandEvent&)
{
  wxString NombreTmp,NombrePropuesto;
  NombreTmp=Nod->VarCalculada.Nombre;
  DialogoVariable dlg(&Nod->VarCalculada,Proy,this,wxT("PRUEBA"), Ayuda);
  dlg.ShowModal();
  NombrePropuesto=Nod->VarCalculada.Nombre;
  Nod->VarCalculada.Nombre=NombreTmp;
  if(Nod->arbol()->buscarNodo(NombrePropuesto)==NULL)
  {
    Nod->VarCalculada.Nombre=NombrePropuesto;
  }
  Nod->Descripcion=TextDescripcion->GetValue();
  Nod->NombreExtendido=TextExtendido->GetValue();
  llenarCuadro();
  if(wxMessageBox(wxT("Desea cambiar esta variable en todos los casos"),wxT("Alerta"),wxICON_QUESTION | wxYES_NO,this)==wxYES)
  {
    int i,tam;
    tam=Proy->Casos.GetCount();
    for(i=0;i<tam;i++)
    {
      Caso *cas;
      cas=&Proy->Casos.Item(i);
      int tam2,j;
      tam2=cas->Variables.GetCount();
      for(j=0;j<tam2;j++)
      {
        VariableLinguistica *var;
        var=&cas->Variables.Item(j);
        if(Nod->VarCalculada.Nombre==var->Nombre)
        {
          *var=Nod ->VarCalculada;
        }
      }
    }
  }
}

void DialogoNodo::editarHijo(wxCommandEvent&)
{
  int loc;
  NodoCalculo *nod;
  loc=ListBoxHijos->GetSelection();
  if(loc<0){return;}
  nod=&Nod->NodosDeCalculo.Item(loc);
  DialogoNodo dlg(nod,Proy,this,wxT("PRUEBA"), Ayuda);
  dlg.ShowModal();
  Nod->Descripcion=TextDescripcion->GetValue();
  Nod->NombreExtendido=TextExtendido->GetValue();
  llenarCuadro();
}

void DialogoNodo::nuevoHijo(wxCommandEvent&)
{
  wxTextEntryDialog dlg(this,wxT("Nombre del Nodo"));
  if(dlg.ShowModal()==wxID_OK)
  {
    wxString cad;
    cad=dlg.GetValue();
    NodoCalculo *NodHijo;
    if(Nod->arbol()->buscarNodo(cad)==NULL)
    {
      NodHijo=new NodoCalculo;
      NodHijo->VarCalculada.Nombre=cad;
    }else
    {
      NodHijo=Nod->arbol()->buscarNodo(cad);
    }
    int n=ListBoxHijos->GetSelection();
    int flag;
    flag= Nod->adicionarNodo(NodHijo,n);
    switch(flag)
    {
      case 0:
            cad =wxT("Nodo adicionado exitosamente");
            break;
      case 1:
            cad =wxT("No se ha podido crear el nodo");
            break;
      case 2:
            cad =wxT("Error: Este nodo cierra un ciclo");
            break;
      case 3:
            cad =wxT("Se ha adicionado un nodo ya existente");
            break;
      case 4:
            cad =wxT("Ya estaba adicionado el nodo");
            break;
      default:
            cad =wxT("Se ha adicionado un nodo ya existente");
            break;
    }
    wxMessageBox(cad, GENERAL_ADVERTENCIA, wxOK | wxICON_INFORMATION, this);
    Nod->Descripcion=TextDescripcion->GetValue();
    Nod->NombreExtendido=TextExtendido->GetValue();
    llenarCuadro();
  }
}

void DialogoNodo::borrarHijo(wxCommandEvent&)
{
  int loc;
  loc=ListBoxHijos->GetSelection();
  wxString cad;
  cad << wxT("Desea borrar el Nodo '") << ListBoxHijos->GetStringSelection() << wxT("'?");
  if(wxMessageBox(cad,wxT("Alerta"),wxICON_QUESTION | wxYES_NO,this)==wxYES)
  {
    Nod->eliminarNodoInferior(loc);
  }
  Nod->Descripcion=TextDescripcion->GetValue();
  Nod->NombreExtendido=TextExtendido->GetValue();
  llenarCuadro();
}

void DialogoNodo::editarParFijo(wxCommandEvent&)
{
  if(ESPECIFICO)
  {
    return;
  }
  if(ListBoxParFijos->GetCount()>0)
  {
    int loc;
    loc=ListBoxParFijos->GetSelection();
    if(loc>=0)
    {
      wxString cad1,cad2;
      cad1=Nod->FuncionCalculo->NombreParametrosFijos[loc];
      cad2 << Nod->FuncionCalculo->ParametrosFijos[loc];
      wxTextEntryDialog dlg(this,cad1,wxT("Editar Parámetro"),cad2);
      if(dlg.ShowModal()==wxID_OK)
      {
        cad2=dlg.GetValue();
        float f;
	double F;
    	cad2.ToDouble(&F);
    	f=(float)F;
        Nod->FuncionCalculo->cambiarParametroFijo(loc,f);
        Nod->Descripcion=TextDescripcion->GetValue();
        Nod->NombreExtendido=TextExtendido->GetValue();
        llenarCuadro();
      }
    }
  }
}

void DialogoNodo::cambiaCelda(wxGridEvent &ev)
{
  int fil,col;
  fil=ev.GetRow();
  col=ev.GetCol();
  if( fil >0 & col >0)
  {
    wxString cad;
    cad=GrillaParVariables->GetCellValue(fil,col);
    float f;
    double F;
    cad.ToDouble(&F);
    f=(float)F;
    Nod->FuncionCalculo->cambiarParametroVariables(fil-1,col-1,f);
    Nod->Descripcion=TextDescripcion->GetValue();
    Nod->NombreExtendido=TextExtendido->GetValue();
//    llenarCuadro();
  }
}

/*
void DialogoNodo::clickVariable()
{
  if(CheckBoxFormaVariable->GetValue())
  {
//    CheckBoxFormaNodos->SetValue(FALSE);
    Nod->FormaDeCalculo=0;
  }else
  {
//    CheckBoxFormaNodos->SetValue(TRUE);
    Nod->FormaDeCalculo=1;
  }
}        */

//void DialogoNodo::clickNodos()
//{
//  if(CheckBoxFormaNodos->GetValue())
//  {
//    CheckBoxFormaVariable->SetValue(FALSE);
//    Nod->FormaDeCalculo=1;
//  }else
//  {
//    CheckBoxFormaVariable->SetValue(TRUE);
//    Nod->FormaDeCalculo=0;
//  }
//}

void DialogoNodo::cambiarFuncion(wxCommandEvent&)
{
  if(ESPECIFICO)
  {
    ChoiceFuncion->SetStringSelection(Nod->FuncionCalculo->Tipo);
    return;
  }
  wxString cad;
  cad = ChoiceFuncion->GetStringSelection();
  if(cad != Nod->FuncionCalculo->Tipo )
  {
      int loc,i,tam;
      loc=ChoiceFuncion->GetSelection();
      tam=Nod->FuncionCalculo->Orden;
      float *x;
      x=new float[tam];
      for(i=0;i<tam;i++)
      {
        x[i]=1.0;
      }
      Funcion *F;
      switch(loc)
      {
        case 0:
              F=new CombinacionLineal(x,tam,0.0);
              break;
        case 1:
              F=new Supremo(tam);
              break;
        case 2:
              F=new Infimo(tam);
              break;
        case 3:
              F=new CombinacionLinealAcotada(x,tam,0.0);
              break;
        case 4:
              F=new SumaProd(x,tam,0.0);
              break;
        case 5:
              F=new ProdSuma(x,tam,0.0);
              break;
        case 6:
              F=new Polinomio(x,x,tam);
              break;
        case 7:
              F=new Ranking(tam,-1.0);
              break;
        case 8:
              F=new RankingOWA(tam,-1.0);
              break;
        case 9:
              F=new OWAfaulhaber(tam,-1.0);
              break;
        case 10:
              F=new Producto(x,tam,0.0);
              break;
        default:
              F=new CombinacionLineal(x,tam,0.0);
              break;
      }
    if(wxMessageBox(wxT("Desea cambiar la función del Nodo?"),wxT("Alerta"),wxICON_QUESTION | wxYES_NO,this)==wxYES)
    {
      Nod->asignarFuncion(F);
    }else
    {
      delete F;
    }
    Nod->Descripcion=TextDescripcion->GetValue();
    Nod->NombreExtendido=TextExtendido->GetValue();
    llenarCuadro();
  }
}

void DialogoNodo::cambiarFormaCalculo(wxCommandEvent&)
{
  if(ESPECIFICO)
  {
    if(Nod->FormaDeCalculo<2)
    {
      ChoiceFormaCalculo->SetSelection(Nod->FormaDeCalculo);
    }else
    {
      ChoiceFormaCalculo->SetStringSelection(Nod->EstrategiaCalculo);
    }
    return;
  }
  int sel;
  sel=ChoiceFormaCalculo->GetSelection();
  if(sel<2)
  {
    Nod->FormaDeCalculo=sel;
  }else
  {
    // Verificar Integridad!!!!!!!
    wxString cad;
    cad=ChoiceFormaCalculo->GetStringSelection();
    if(Nod->evaluarEnlace(cad))
    {
      Nod->FormaDeCalculo=2;
      Nod->EstrategiaCalculo=cad;
    }else
    {
      wxMessageBox(wxT("Ese enlace cierra un lazo. No es permitido"),wxT("Error"));
      llenarCuadro();
    }
  }
}

void DialogoNodo::cambiaSpinH(wxSpinEvent&)
{
  int H;
  H=SpinOffsetHorizontal->GetValue();
  Nod->OffsetPosicionEnNivel=H;
}

void DialogoNodo::cambiaSpinV(wxSpinEvent&)
{
  int V;
  V=SpinOffsetVertical->GetValue();
  Nod->OffsetNivel=V;
}

void DialogoNodo::cerrarOk(wxCommandEvent&)
{
//  leerTextos();
//  *NodTemp=Nod;
  Nod->Descripcion=TextDescripcion->GetValue();
  Nod->NombreExtendido=TextExtendido->GetValue();
  Close();
}

void DialogoNodo::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoNodo::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Edición de Nodos de Cálculo"));
}

