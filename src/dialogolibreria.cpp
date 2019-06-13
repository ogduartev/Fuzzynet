/***************************************************************************
                          dialogolibreria.cpp  -  description
                             -------------------
    begin                : abr 21 2004
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

#include "dialogolibreria.h"

BEGIN_EVENT_TABLE(DialogoLibreria, wxDialog)
    EVT_BUTTON(DLG_LIBRERIA_BTN_OK, DialogoLibreria::cerrarOk)
//    EVT_BUTTON(DLG_LIBRERIA_BTN_CANCEL, DialogoLibreria::cancelar)
    EVT_BUTTON(DLG_LIBRERIA_BTN_AYUDA, DialogoLibreria::ayuda)
    EVT_BUTTON(DLG_LIBRERIA_BTN_ARCHIVO, DialogoLibreria::archivo)
    EVT_BUTTON(DLG_LIBRERIA_BTN_ADICIONAR, DialogoLibreria::adicionar)
    EVT_BUTTON(DLG_LIBRERIA_BTN_LEER, DialogoLibreria::leer)
    EVT_BUTTON(DLG_LIBRERIA_BTN_BORRAR, DialogoLibreria::borrar)
    EVT_BUTTON(DLG_LIBRERIA_BTN_SALVAR, DialogoLibreria::salvar)
    EVT_LISTBOX(DLG_LIBRERIA_LIST_ITEMS, DialogoLibreria::seleccionaItem)
END_EVENT_TABLE()


DialogoLibreria::DialogoLibreria(Estrategia *est,Caso *cas, VariableLinguistica *var,
                  wxWindow* parent,const wxString& title, wxHtmlHelpController *ayuda)
                  :wxDialog(parent,-1,title)
{
  Ayuda=ayuda;
  Est=est;
  Cas=cas;
  Var=var;
  if(Est!=NULL)
  {
    Tipo=1;
  }else if(Cas!=NULL)
  {
    Tipo=2;
  }else if(Var != NULL)
  {
    Tipo=3;
  }else
  {
    Tipo=-1;
  }

  ButtonOK                       =new wxButton(this,DLG_LIBRERIA_BTN_OK, wxT("OK"));
  ButtonAyuda                    =new wxButton (this,DLG_LIBRERIA_BTN_AYUDA, wxT("Ayuda"));
  ButtonArchivo                  =new wxButton (this,DLG_LIBRERIA_BTN_ARCHIVO, wxT("Seleccionar"));
  ButtonSalvar                   =new wxButton (this,DLG_LIBRERIA_BTN_SALVAR, wxT("Salvar"));
  ButtonAdicionar                =new wxButton (this,DLG_LIBRERIA_BTN_ADICIONAR, wxT("Adicionar"));
  ButtonLeer                     =new wxButton (this,DLG_LIBRERIA_BTN_LEER, wxT("Leer"));
  ButtonBorrar                   =new wxButton(this,DLG_LIBRERIA_BTN_BORRAR, wxT("Borrar"));
  StaticArchivo                  =new wxStaticText (this,DLG_LIBRERIA_STATIC_ARCHIVO, wxT("Archivo"));
  TextArchivo                   =new wxTextCtrl (this,DLG_LIBRERIA_TEXT_ARCHIVO);
  ListBoxItems                  =new wxListBox (this,DLG_LIBRERIA_LIST_ITEMS);
  StaticItems                   =new wxStaticText (this,DLG_LIBRERIA_STATIC_ITEMS, wxT("Disponibles"));
  StaticDesc                    =new wxStaticText (this,DLG_LIBRERIA_STATIC_DESC, wxT("Descripción"));
  TextDesc                      =new wxTextCtrl (this,DLG_LIBRERIA_TEXT_DESC,wxT(""),wxDefaultPosition,wxDefaultSize,wxTE_MULTILINE);
  StaticActual                  =new wxStaticText (this,DLG_LIBRERIA_STATIC_ACTUAL, wxT("Actual:"));
  TextActual                    =new wxTextCtrl (this,DLG_LIBRERIA_TEXT_ACTUAL);

  TextArchivo->SetMinSize(wxSize(300,20));
  TextArchivo->SetEditable(FALSE);

  ListBoxItems->SetMinSize(wxSize(100,100));
  TextDesc->SetMinSize(wxSize(250,100));
  TextDesc->SetEditable(FALSE);
  TextActual->SetMinSize(wxSize(150,20));
  TextActual->SetEditable(FALSE);

    wxBoxSizer *sizerButArch = new wxBoxSizer(wxVERTICAL);
    sizerButArch->Add(ButtonArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButArch->Add(ButtonSalvar, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerArch = new wxBoxSizer(wxHORIZONTAL);
    sizerArch->Add(StaticArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerArch->Add(TextArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerArch->Add(sizerButArch, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerItem = new wxBoxSizer(wxVERTICAL);
    sizerItem->Add(StaticItems, 0, wxALIGN_CENTER | wxALL, 5);
    sizerItem->Add(ListBoxItems, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerDesc = new wxBoxSizer(wxVERTICAL);
    sizerDesc->Add(StaticDesc, 0, wxALIGN_CENTER | wxALL, 5);
    sizerDesc->Add(TextDesc, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerOpc = new wxBoxSizer(wxHORIZONTAL);
    sizerOpc->Add(sizerItem, 0, wxALIGN_CENTER | wxALL, 5);
    sizerOpc->Add(sizerDesc, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerAct = new wxBoxSizer(wxHORIZONTAL);
    sizerAct->Add(StaticActual, 0, wxALIGN_CENTER | wxALL, 5);
    sizerAct->Add(TextActual, 0, wxALIGN_CENTER | wxALL, 5);
    sizerAct->Add(ButtonAdicionar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerAct->Add(ButtonLeer, 0, wxALIGN_CENTER | wxALL, 5);
    sizerAct->Add(ButtonBorrar, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
//    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerArch, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerOpc, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerAct, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->FitInside(this);

    llenarCuadro();
}

DialogoLibreria::~DialogoLibreria()
{
}

void DialogoLibreria::cerrarOk(wxCommandEvent&)
{
  wxSetWorkingDirectory(DirectorioInicial);
  Close();
}

//void DialogoLibreria::cancelar()
//{
//  wxSetWorkingDirectory(DirectorioInicial);
//  Close();
//}

void DialogoLibreria::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Administración de Librerías"));
}

void DialogoLibreria::archivo(wxCommandEvent&)
{
    wxString cad;

    cad =wxT("Librerías de Fuzzynet (*.lfz)|*.lfz|Todos los archivos (*.*)|*.*");

    wxFileDialog Dial(this,wxT("Archivo de librería"),DirectorioActual,ArchivoActual,cad,wxFD_OPEN|wxFD_CHANGE_DIR);
    if(Dial.ShowModal()==wxID_OK)
    {
      ArchivoActual=Dial.GetFilename();
      DirectorioActual=Dial.GetDirectory();
      TextArchivo->SetValue(ArchivoActual);
      Mi_ifpstream ifile(ArchivoActual);
      wxBeginBusyCursor();
      Lib.read(ifile);
      wxEndBusyCursor();
      llenarCuadro();
    }
}

void DialogoLibreria::llenarCuadro()
{
  int i,tam;
  ListBoxItems->Clear();
  Nom.Clear();
  Desc.Clear();
  Lib.datos(&Nom,&Desc,Tipo);
  tam=Nom.GetCount();
  for(i=0;i<tam;i++)
  {
    ListBoxItems->Append(Nom.Item(i));
  }
  if(tam>0)
  {
    ListBoxItems->SetSelection(0);
    wxCommandEvent ev;
    seleccionaItem(ev);
  }
  switch(Tipo)
  {
    case 1: TextActual->SetValue(Est->Nombre);break;
    case 2: TextActual->SetValue(Cas->Nombre);break;
    case 3: TextActual->SetValue(Var->Nombre);break;
  }
}

void DialogoLibreria::seleccionaItem(wxCommandEvent&)
{
  int sel;
  sel=ListBoxItems->GetSelection();
  if((sel>=0) & (Desc.GetCount() > sel))
  {
    TextDesc->SetValue(Desc.Item(sel));
  }
}

void DialogoLibreria::adicionar(wxCommandEvent&)
{
  wxString cad;
  cad = wxT("Desea adicionar ");
  switch(Tipo)
  {
    case 1: cad << wxT("la Metodología"); break;
    case 2: cad << wxT("el Caso"); break;
    case 3: cad << wxT("La Variable"); break;
  }
  cad << wxT(" actual a la librería? No olvide salvarla.");
  if(wxMessageBox(cad,wxT("Atención"),wxYES_NO | wxCANCEL)==wxYES)
  {
    Mi_ofpstream *ofile;
    ofile=new Mi_ofpstream(wxT("__Fzn_tmp"));
    Mi_ifpstream *ifile;
    wxBeginBusyCursor();
    switch(Tipo)
    {
      case 1:
            Est->write(*ofile);
            delete ofile;
            Estrategia *nEst;
            nEst=new Estrategia;
            ifile=new Mi_ifpstream(wxT("__Fzn_tmp"));
            nEst->read(*ifile);
            delete ifile;
            Lib.Estrategias.Add(nEst);
            llenarCuadro();
            ListBoxItems->SetSelection(Lib.Estrategias.GetCount());
            break;
      case 2:
            Cas->write(*ofile);
            delete ofile;
            Caso *nCas;
            nCas=new Caso;
            ifile=new Mi_ifpstream(wxT("__Fzn_tmp"));
            nCas->read(*ifile);
            delete ifile;
            Lib.Casos.Add(nCas);
            llenarCuadro();
            ListBoxItems->SetSelection(Lib.Casos.GetCount());
            break;
      case 3:
            Var->write(*ofile);
            delete ofile;
            VariableLinguistica *nVar;
            nVar=new VariableLinguistica;
            ifile=new Mi_ifpstream(wxT("__Fzn_tmp"));
            nVar->read(*ifile);
            delete ifile;
            Lib.Variables.Add(nVar);
            llenarCuadro();
            ListBoxItems->SetSelection(Lib.Variables.GetCount());
            break;
    }
    wxEndBusyCursor();
  }
}

void DialogoLibreria::leer(wxCommandEvent&)
{
  int sel;
  sel=ListBoxItems->GetSelection();
  if(sel<0){return;}
  wxString cad;
  cad = wxT("Desea copiar ");
  switch(Tipo)
  {
    case 1: cad << wxT("la Metodología"); break;
    case 2: cad << wxT("el Caso"); break;
    case 3: cad << wxT("La Variable"); break;
  }
  cad << wxT(" de la librería la actual?.");
  if(wxMessageBox(cad,wxT("Atención"),wxYES_NO | wxCANCEL)==wxYES)
  {
    Mi_ofpstream *ofile;
    ofile=new Mi_ofpstream(wxT("__Fzn_tmp"));
    Mi_ifpstream *ifile;
    wxBeginBusyCursor();
    switch(Tipo)
    {
      case 1:
            Lib.Estrategias.Item(sel).write(*ofile);
            delete ofile;
            ifile=new Mi_ifpstream(wxT("__Fzn_tmp"));
            Est->read(*ifile);
            delete ifile;
            llenarCuadro();
            ListBoxItems->SetSelection(sel);
            break;
      case 2:
            Lib.Casos.Item(sel).write(*ofile);
            delete ofile;
            ifile=new Mi_ifpstream(wxT("__Fzn_tmp"));
            Cas->read(*ifile);
            delete ifile;
            llenarCuadro();
            ListBoxItems->SetSelection(sel);
            break;
      case 3:
            Lib.Variables.Item(sel).write(*ofile);
            delete ofile;
            ifile=new Mi_ifpstream(wxT("__Fzn_tmp"));
            Var->read(*ifile);
            delete ifile;
            llenarCuadro();
            ListBoxItems->SetSelection(sel);
            break;
    }
    wxEndBusyCursor();
  }
}

void DialogoLibreria::borrar(wxCommandEvent&)
{
  int sel;
  sel=ListBoxItems->GetSelection();
  if(sel<0){return;}
  wxString cad;
  cad = wxT("Desea borrar ");
  switch(Tipo)
  {
    case 1: cad << wxT("la Metodología"); break;
    case 2: cad << wxT("el Caso"); break;
    case 3: cad << wxT("La Variable"); break;
  }
  cad << wxT(" de la librería?. No olvide salvarla.");
  if(wxMessageBox(cad,wxT("Atención"),wxYES_NO | wxCANCEL)==wxYES)
  {
    switch(Tipo)
    {
      case 1:
            Lib.Estrategias.RemoveAt(sel);
            llenarCuadro();
            if(sel>Lib.Estrategias.GetCount())
            {
              sel=Lib.Estrategias.GetCount();
            }
            if(sel>=0)
            {
              ListBoxItems->SetSelection(sel);
            }else
            {
              TextDesc->SetValue(wxT(""));
            }
            break;
      case 2:
            Lib.Casos.RemoveAt(sel);
            llenarCuadro();
            if(sel>Lib.Casos.GetCount())
            {
              sel=Lib.Casos.GetCount();
            }
            if(sel>=0)
            {
              ListBoxItems->SetSelection(sel);
            }else
            {
              TextDesc->SetValue(wxT(""));
            }
            break;
      case 3:
            Lib.Variables.RemoveAt(sel);
            llenarCuadro();
            if(sel>Lib.Variables.GetCount())
            {
              sel=Lib.Variables.GetCount();
            }
            if(sel>=0)
            {
              ListBoxItems->SetSelection(sel);
            }else
            {
              TextDesc->SetValue(wxT(""));
            }
            break;
    }
  }
}

void DialogoLibreria::salvar(wxCommandEvent&)
{
    wxString cad;

    cad =wxT("Librerías de Fuzzynet (*.lfz)|*.lfz|Todos los archivos (*.*)|*.*");

    wxFileDialog Dial(this,wxT("Archivo de librería"),DirectorioActual,ArchivoActual,cad,wxFD_SAVE|wxFD_CHANGE_DIR);
    if(Dial.ShowModal()==wxID_OK)
    {
      ArchivoActual=Dial.GetFilename();
      DirectorioActual=Dial.GetDirectory();
      TextArchivo->SetValue(ArchivoActual);
      Mi_ofpstream ofile(ArchivoActual);
      wxBeginBusyCursor();
      Lib.write(ofile);
      wxEndBusyCursor();
      llenarCuadro();
    }
}

