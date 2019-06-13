/***************************************************************************
                          dialogoexportar.cpp  -  description
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

#include "dialogoexportar.h"

BEGIN_EVENT_TABLE(DialogoExportar, wxDialog)
    EVT_BUTTON(DLG_EXPORTAR_BTN_ARCHIVO, DialogoExportar::seleccionarArchivo)
    EVT_BUTTON(DLG_EXPORTAR_BTN_EXPORTAR, DialogoExportar::exportar)
    EVT_BUTTON(DLG_EXPORTAR_BTN_OK, DialogoExportar::cerrarOk)
    EVT_BUTTON(DLG_EXPORTAR_BTN_CANCEL, DialogoExportar::cancelar)
    EVT_BUTTON(DLG_EXPORTAR_BTN_AYUDA, DialogoExportar::ayuda)
END_EVENT_TABLE()

DialogoExportar::DialogoExportar(Proyecto *proy,
                   wxWindow* parent,const wxString& title,wxHtmlHelpController *ayuda)
                  :wxDialog(parent,-1,title)
{
  Proy=proy;
  Ayuda=ayuda;
  SetTitle(wxT("Exportar a un archivo de texto"));

  Notebook                       =new wxNotebook(this,DLG_EXPORTAR_NOTEBOOK);
  ButtonOK                       =new wxButton(this,DLG_EXPORTAR_BTN_OK, wxT("OK"));
  ButtonCancelar                 =new wxButton(this,DLG_EXPORTAR_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda                    =new wxButton (this,DLG_EXPORTAR_BTN_AYUDA, wxT("Ayuda"));
  ButtonArchivo                  =new wxButton (this,DLG_EXPORTAR_BTN_ARCHIVO, wxT("Seleccionar"));
  ButtonExportar                  =new wxButton (this,DLG_EXPORTAR_BTN_EXPORTAR, wxT("Exportar"));
  StaticArchivo                  =new wxStaticText (this,DLG_EXPORTAR_STATIC_ARCHIVO, wxT("Archivo"));
  StaticOpciones                =new wxStaticText (this,DLG_EXPORTAR_STATIC_OPCIONES, wxT("Opciones"));
  StaticSeparador                =new wxStaticText (this,DLG_EXPORTAR_STATIC_SEPARADOR, wxT("Separador"));
  TextArchivo                   =new wxTextCtrl (this,DLG_EXPORTAR_TEXT_ARCHIVO);
  ComboOpciones             =new wxComboBox (this,DLG_EXPORTAR_COMBOBOX_OPCIONES,wxT(""),wxDefaultPosition,wxDefaultSize, 0,0,wxCB_DROPDOWN);
  ComboSeparador              =new wxComboBox (this,DLG_EXPORTAR_COMBOBOX_SEPARADOR,wxT(""),wxDefaultPosition,wxDefaultSize,0,0,wxCB_DROPDOWN);
  CheckTodo                   =new wxCheckBox (this,DLG_EXPORTAR_CHECKBOX_TODO,wxT("Exportar Todos los Nodos"));
  CheckPropiedades            =new wxCheckBox (this,DLG_EXPORTAR_CHECKBOX_PROPIEDADES,wxT("Exportar Propiedades de Casos"));

  TextArchivo->SetSize(300,20);
  TextArchivo->SetEditable(FALSE);
  ComboOpciones->SetSize(200,25);
  ComboSeparador->SetSize(100,25);

    DirectorioActual=::wxGetCwd();;
    ArchivoActual=wxT("Exportar.txt");

  llenarNoteBook();

    wxBoxSizer *sizerArch = new wxBoxSizer(wxHORIZONTAL);
    sizerArch->Add(StaticArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerArch->Add(TextArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerArch->Add(ButtonArchivo, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerNote = new wxBoxSizer(wxVERTICAL);
    sizerNote->Add(Notebook, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerOp = new wxBoxSizer(wxVERTICAL);
    sizerOp->Add(StaticOpciones, 0, wxALIGN_CENTER | wxALL, 0);
    sizerOp->Add(ComboOpciones, 0, wxALIGN_CENTER | wxALL, 0);

    wxBoxSizer *sizerSep = new wxBoxSizer(wxVERTICAL);
    sizerSep->Add(StaticSeparador, 0, wxALIGN_CENTER | wxALL, 0);
    sizerSep->Add(ComboSeparador, 0, wxALIGN_CENTER | wxALL, 0);

    wxBoxSizer *sizerCheck = new wxBoxSizer(wxVERTICAL);
    sizerCheck->Add(CheckTodo, 0, wxALIGN_LEFT | wxALL, 0);
    sizerCheck->Add(CheckPropiedades, 0, wxALIGN_LEFT | wxALL, 0);

    wxBoxSizer *sizerSel = new wxBoxSizer(wxHORIZONTAL);
    sizerSel->Add(sizerCheck, 0, wxALIGN_BOTTOM | wxALL, 5);
    sizerSel->Add(sizerOp, 0, wxALIGN_CENTER | wxALL, 5);
    sizerSel->Add(sizerSep, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerArch, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerNote, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerSel, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(ButtonExportar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->Fit(this);

    llenarCuadro();

}

DialogoExportar::~DialogoExportar()
{
}

void DialogoExportar::llenarNoteBook()
{
  int i,tam;

  NumPaginas=Proy->Estrategias.GetCount()+1;

  Paginas=new PaginaListados*[NumPaginas];
  Origen=new wxArrayString[NumPaginas];

  tam=Proy->Casos.GetCount();
  for(i=0;i<tam;i++)
  {
    Origen[0].Add(Proy->Casos.Item(i).Nombre);
  }
  Paginas[0]=new PaginaListados(Origen[0],Notebook);
  Notebook->AddPage(Paginas[0],wxT("Casos"),TRUE );
  for(i=1;i<NumPaginas;i++)
  {
    wxString cad;
    cad = Proy->Estrategias.Item(i-1).Nombre;
    ListaNodos Nodos;
    Proy->Estrategias.Item(i-1).Grafo.llenarArreglo(&Nodos);
    int j,tam2;
    tam2=Nodos.GetCount();
    for(j=0;j<tam2;j++)
    {
      Origen[i].Add(Nodos.Item(0).VarCalculada.Nombre);
      Nodos.Detach(0);
    }
    Paginas[i]=new PaginaListados(Origen[i],Notebook);
    Notebook->AddPage(Paginas[i],cad,FALSE );
  }

}

void DialogoExportar::llenarCuadro()
{
  TextArchivo->SetValue(ArchivoActual);

  ComboOpciones->Clear();
  ComboOpciones->Append(wxT("Valor Representativo"));
  ComboOpciones->Append(wxT("Ambigûedad"));
  ComboOpciones->Append(wxT("Valor / Ambigedad"));
  ComboOpciones->Append(wxT("Interpretación Corta"));
  ComboOpciones->Append(wxT("Interpretación Larga"));
  ComboOpciones->SetSelection(0);

  ComboSeparador->Clear();
  ComboSeparador->Append(wxT("Tabulador"));
  ComboSeparador->Append(wxT(";"));
  ComboSeparador->Append(wxT("$"));
  ComboSeparador->Append(wxT("%"));
  ComboSeparador->SetSelection(0);

  CheckTodo->SetValue(TRUE);
}

void DialogoExportar::seleccionarArchivo(wxCommandEvent&)
{
//    Esta línea tiene verificación de sobreescritura, pero en inglés...
//    Las cadenas están definidas en filedlg.cpp vale la pena cambiarlas?
//    wxFileDialog Dial(this,wxT("Archivo de exportación"),DirectorioActual,ArchivoActual,wxT("Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*"),wxSAVE|wxCHANGE_DIR|wxOVERWRITE_PROMPT);
    wxFileDialog Dial(this,wxT("Archivo de exportación"),DirectorioActual,ArchivoActual,wxT("Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*"),wxFD_SAVE|wxFD_CHANGE_DIR);
    if(Dial.ShowModal()==wxID_OK)
    {
      ArchivoActual=Dial.GetFilename();
      DirectorioActual=Dial.GetDirectory();
      TextArchivo->SetValue(ArchivoActual);
    }
}

void DialogoExportar::exportar(wxCommandEvent&)
{
  int i,j,tam,tam2;
  ListaSelecciones NombresEst;
  wxArrayString NombresNod;
  wxArrayString NombresCas;
  wxString Separador;
  int Opcion;
  bool Prop;

  if(CheckTodo->GetValue())
  {
    tam=Proy->Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      ListaNodos Nodos;
      NombresNod.Clear();
      Proy->Estrategias.Item(i).Grafo.llenarArreglo(&Nodos);
      tam2=Nodos.GetCount();
      for(j=0;j<tam2;j++)
      {
        NombresNod.Add(Nodos.Item(0).VarCalculada.Nombre);
        Nodos.Detach(0);
      }
      NombresEst.adicionarSeleccion(Proy->Estrategias.Item(i).Nombre,NombresNod,0);
    }
    tam=Proy->Casos.GetCount();
    for(i=0;i<tam;i++)
    {
      NombresCas.Add(Proy->Casos.Item(i).Nombre);
    }
  }else
  {
    NombresCas=Paginas[0]->Destino;
    tam=NumPaginas;
    for(i=1;i<tam;i++)
    {
      NombresNod=Paginas[i]->Destino;
      NombresEst.adicionarSeleccion(Proy->Estrategias.Item(i-1).Nombre,NombresNod,0);
    }
  }

  Opcion=ComboOpciones->GetSelection();
  if(ComboSeparador->GetSelection()==0)
  {
    Separador=wxT('\t');
  }else
  {
    Separador=ComboSeparador->GetValue();
  }
  Prop=CheckPropiedades->GetValue();
  wxBeginBusyCursor();
  Proy->exportar(ArchivoActual,NombresCas,NombresEst,Separador,Opcion,Prop);
  wxEndBusyCursor();
  wxMessageBox(wxT("Exportación Concluida"),wxT("Mensaje"));
}


void DialogoExportar::cerrarOk(wxCommandEvent&)
{
  Close();
}

void DialogoExportar::cancelar(wxCommandEvent&)
{
  Close();
}

void DialogoExportar::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Exportar Archivos de texto"));
}

