/***************************************************************************
                          dialogoimportar.cpp  -  description
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

#include "dialogoimportar.h"

BEGIN_EVENT_TABLE(DialogoImportar, wxDialog)
    EVT_BUTTON(DLG_IMPORTAR_BTN_ARCHIVO, DialogoImportar::seleccionarArchivo)
    EVT_BUTTON(DLG_IMPORTAR_BTN_IMPORTAR, DialogoImportar::importar)
    EVT_BUTTON(DLG_IMPORTAR_BTN_APLICAR, DialogoImportar::aplicar)
    EVT_BUTTON(DLG_IMPORTAR_BTN_OK, DialogoImportar::cerrarOk)
    EVT_BUTTON(DLG_IMPORTAR_BTN_CANCEL, DialogoImportar::cancelar)
    EVT_BUTTON(DLG_IMPORTAR_BTN_AYUDA, DialogoImportar::ayuda)
    EVT_LISTBOX(DLG_IMPORTAR_LISTBOX_ITEMS, DialogoImportar::cambiaSel)
END_EVENT_TABLE()

DialogoImportar::DialogoImportar(Proyecto *proy,
                   wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda)
                  :wxDialog(parent,-1,title)
{
  Proy=proy;
  Ayuda=ayuda;
  SetTitle(wxT("Importar a un archivo de texto"));

  ButtonOK                       =new wxButton(this,DLG_IMPORTAR_BTN_OK, wxT("OK"));
  ButtonCancelar                 =new wxButton(this,DLG_IMPORTAR_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda                    =new wxButton (this,DLG_IMPORTAR_BTN_AYUDA, wxT("Ayuda"));
  ButtonArchivo                  =new wxButton (this,DLG_IMPORTAR_BTN_ARCHIVO, wxT("Seleccionar"));
  ButtonImportar                  =new wxButton (this,DLG_IMPORTAR_BTN_IMPORTAR, wxT("Importar"));
  StaticArchivo                  =new wxStaticText (this,DLG_IMPORTAR_STATIC_ARCHIVO, wxT("Archivo"));
  StaticOpciones                 =new wxStaticText (this,DLG_IMPORTAR_STATIC_OPCIONES, wxT("Opciones"));
  TextArchivo                   =new wxTextCtrl (this,DLG_IMPORTAR_TEXT_ARCHIVO);
  ListBoxItems                  =new wxListBox(this,DLG_IMPORTAR_LISTBOX_ITEMS);
  ComboSel                     =new wxComboBox(this,DLG_IMPORTAR_COMBOBOX_SEL);
  ButtonAplicar                =new wxButton(this,DLG_IMPORTAR_BTN_APLICAR,wxT("Aplicar"));

  TextArchivo->SetMinSize(wxSize(300,20));
  TextArchivo->SetEditable(FALSE);
  ListBoxItems->SetMinSize(wxSize(200,150));
  ComboSel->SetMinSize(wxSize(200,60));

    DirectorioActual=::wxGetCwd();;
    ArchivoActual=wxT("Exportar.txt");

    wxBoxSizer *sizerArch = new wxBoxSizer(wxHORIZONTAL);
    sizerArch->Add(StaticArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerArch->Add(TextArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerArch->Add(ButtonArchivo, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerList = new wxBoxSizer(wxVERTICAL);
    sizerList->Add(StaticOpciones, 0, wxALIGN_CENTER | wxALL, 5);
    sizerList->Add(ListBoxItems, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButOp = new wxBoxSizer(wxVERTICAL);
    sizerButOp->Add(ComboSel, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButOp->Add(ButtonAplicar, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerMed = new wxBoxSizer(wxHORIZONTAL);
    sizerMed->Add(sizerList, 0, wxALIGN_CENTER | wxALL, 5);
    sizerMed->Add(sizerButOp, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerArch, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerMed, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(ButtonImportar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();
}

DialogoImportar::~DialogoImportar()
{
}

void DialogoImportar::llenarCuadro()
{
  TextArchivo->SetValue(ArchivoActual);

  wxArrayString arr;
  arr.Clear();
  arr.Add(wxT("Distinguir May-Min"));arr.Add(wxT("No Distinguir"));
  ListaSel.adicionarSeleccion(wxT("Comparación de cadenas"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Crear Caso"));arr.Add(wxT("Ignorar Información"));
  ListaSel.adicionarSeleccion(wxT("Caso Leido Inexistente"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Actualizar Información"));arr.Add(wxT("Borrar Información Previa"));
  ListaSel.adicionarSeleccion(wxT("Caso Leido Existente"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("No Importar Información"));arr.Add(wxT("Importar Información"));
  ListaSel.adicionarSeleccion(wxT("Nodos Calculados"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Ajustar a Etiqueta"));arr.Add(wxT("Interpretación Detallada"));
  ListaSel.adicionarSeleccion(wxT("Interpretación"),wxArrayString(arr),0);
//  arr.Clear();
//  arr.Add(wxT("Crear Propiedad"));arr.Add(wxT("Ignorar"));
//  ListaSel.adicionarSeleccion("Nodos Inexistentes",wxArrayString(arr),0);
//  arr.Clear();
//  arr.Add(wxT("Crear Propiedad"));arr.Add(wxT("Ignorar"));
//  ListaSel.adicionarSeleccion("Propiedades Inexistentes",wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Crear Variable"));arr.Add(wxT("Ignorar"));
  ListaSel.adicionarSeleccion(wxT("Variables Inexistentes"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Tabulador"));arr.Add(wxT(";"));arr.Add(wxT("$"));arr.Add(wxT("%"));
  ListaSel.adicionarSeleccion(wxT("Separador"),wxArrayString(arr),0);

  int i,tam;
  tam=ListaSel.Nombres.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxItems->Append(ListaSel.Nombres.Item(i));
  }
  if(tam>0)
  {
    ListBoxItems->SetSelection(0);
  }
  wxCommandEvent ev;
  cambiaSel(ev);
}

void DialogoImportar::cambiaSel(wxCommandEvent&)
{
  int item=0;
  item=ListBoxItems->GetSelection();
  if(item<0){return;}
  ComboSel->Clear();
  int i,tam;
  tam=ListaSel.Opciones.Item(item).GetCount();
  for(i=0;i<tam;i++)
  {
    ComboSel->Append(ListaSel.Opciones.Item(item).Item(i));
  }
  if(tam>0 && tam > ListaSel.Selecciones.Item(item))
  {
    ComboSel->SetSelection(ListaSel.Selecciones.Item(item));
  }


}

void DialogoImportar::aplicar(wxCommandEvent&)
{
  int item;
  item=ListBoxItems->GetSelection();
  if(item<0){return;}
  int d;
  d=ComboSel->GetSelection();
  ListaSel.Selecciones.Item(item)=d;
}

void DialogoImportar::seleccionarArchivo(wxCommandEvent&)
{
    wxFileDialog Dial(this,wxT("Archivo de exportación"),DirectorioActual,ArchivoActual,wxT("Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*"),wxFD_OPEN|wxFD_CHANGE_DIR);
    if(Dial.ShowModal()==wxID_OK)
    {
      ArchivoActual=Dial.GetFilename();
      DirectorioActual=Dial.GetDirectory();
      TextArchivo->SetValue(ArchivoActual);
    }
}

void DialogoImportar::importar(wxCommandEvent&)
{
  char Separador;
  switch(ListaSel.Seleccion(wxT("Separador")))
  {
    case 0 : Separador='\t';break;
    case 1 : Separador=';';break;
    case 2 : Separador='$';break;
    case 3 : Separador='%';break;
    default : Separador='\t';break;
  }
  wxBeginBusyCursor();
  Proy->importar(ArchivoActual,ListaSel,Separador);
  wxEndBusyCursor();
  Proy->ProyectoModificado=TRUE;
  wxMessageBox(wxT("Importación Concluida"),wxT("Mensaje"));
}

void DialogoImportar::cerrarOk(wxCommandEvent&)
{
  Close();
}

void DialogoImportar::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoImportar::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Importar Archivos de Texto"));
}

