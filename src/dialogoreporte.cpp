/***************************************************************************
                          dialogoreporte.cpp  -  description
                             -------------------
    begin                : lun abr 19 2004
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

#include "dialogoreporte.h"


BEGIN_EVENT_TABLE(DialogoReporte, wxDialog)
    EVT_BUTTON(DLG_REPORTE_BTN_OK, DialogoReporte::cerrarOk)
    EVT_BUTTON(DLG_REPORTE_BTN_CANCEL, DialogoReporte::cancelar)
    EVT_BUTTON(DLG_REPORTE_BTN_AYUDA, DialogoReporte::ayuda)
    EVT_BUTTON(DLG_REPORTE_BTN_LEERCONFIGURA, DialogoReporte::leerConfigura)
    EVT_BUTTON(DLG_REPORTE_BTN_ESCRIBIRCONFIGURA, DialogoReporte::escribirConfigura)
    EVT_BUTTON(DLG_REPORTE_BTN_DEFECTO, DialogoReporte::defecto)
    EVT_BUTTON(DLG_REPORTE_BTN_GENERAR, DialogoReporte::generar)
    EVT_BUTTON(DLG_REPORTE_BTN_ARCHIVO, DialogoReporte::archivo)
END_EVENT_TABLE()


DialogoReporte::DialogoReporte(Proyecto *proy, int con, int tip,
          wxWindow *parent,const wxString& title, wxHtmlHelpController *ayuda)
          :wxDialog(parent,-1,title)
{
  Proy=proy;
  Tipo=tip;
  Contenido=con;
  Ayuda=ayuda;
  SetTitle(wxT("Generación de Reportes"));

  ButtonOK                       =new wxButton(this,DLG_REPORTE_BTN_OK, wxT("OK"));
  ButtonCancelar                 =new wxButton(this,DLG_REPORTE_BTN_CANCEL, wxT("Cancelar"));
  ButtonAyuda                    =new wxButton (this,DLG_REPORTE_BTN_AYUDA, wxT("Ayuda"));
  ButtonLeerConfigura            =new wxButton (this,DLG_REPORTE_BTN_LEERCONFIGURA, wxT("Leer Predeterminado"));
  ButtonEscribirConfigura        =new wxButton (this,DLG_REPORTE_BTN_ESCRIBIRCONFIGURA, wxT("Escribir Predeterminado"));
  ButtonDefecto                 =new wxButton (this,DLG_REPORTE_BTN_DEFECTO, wxT("Configuración por defecto"));
  ButtonGenerar                  =new wxButton (this,DLG_REPORTE_BTN_GENERAR, wxT("Generar el reporte"));
  GaugeAvance                   = new wxGauge(this, DLG_REPORTE_GAUGE_AVANCE,100);
  ButtonArchivo                  =new wxButton (this,DLG_REPORTE_BTN_ARCHIVO, wxT("Seleccionar"));
  StaticArchivo                  =new wxStaticText (this,DLG_REPORTE_STATIC_ARCHIVO, wxT("Archivo"));
  TextArchivo                   =new wxTextCtrl (this,DLG_REPORTE_TEXT_ARCHIVO);
  Notebook                       =new wxNotebook(this,DLG_REPORTE_NOTEBOOK);

  TextArchivo->SetMinSize(wxSize(300,20));
  TextArchivo->SetEditable(FALSE);
  DirectorioInicial=wxGetCwd();
  wxString cad=DirectorioInicial;
  cad << wxT("/reporte");
  if(!wxDirExists(cad))
  {
    wxMkdir(cad);
  }
  switch(Tipo)
  {
    case 1: cad << wxT("/txt");break;
    case 2: cad << wxT("/latex");break;
    case 3: cad << wxT("/html");break;
    default: Tipo=1;cad << wxT("/txt");break;
  }
  if(!wxDirExists(cad))
  {
    wxMkdir(cad);
  }
  DirectorioActual=cad;
  wxSetWorkingDirectory(DirectorioActual);

  switch(Tipo)
  {
    case 1: ArchivoActual=wxT("reporte.txt");break;
    case 2: ArchivoActual=wxT("reporte.tex");break;
    case 3: ArchivoActual=wxT("index.html");break;
    default: Tipo=1;ArchivoActual=wxT("reporte.txt");break;
  }
  TextArchivo->SetValue(ArchivoActual);

  NumPag=Rep.Selecciones.GetCount();
  PagSelecciones= new PaginaSeleccionesGrilla*[NumPag];
  GaugeAvance->SetMinSize(wxSize(100,10));
  GaugeAvance->SetValue(0);

  Rep.readConfigura();

  llenarNotebook();

    wxBoxSizer *sizerArch = new wxBoxSizer(wxHORIZONTAL);
    sizerArch->Add(StaticArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerArch->Add(TextArchivo, 0, wxALIGN_CENTER | wxALL, 5);
    sizerArch->Add(ButtonArchivo, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButPre = new wxBoxSizer(wxVERTICAL);
    sizerButPre->Add(ButtonLeerConfigura, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButPre->Add(ButtonEscribirConfigura, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButPre->Add(ButtonDefecto, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerGen = new wxBoxSizer(wxHORIZONTAL);
    sizerGen->Add(ButtonGenerar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerGen->Add(GaugeAvance, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerButInf = new wxBoxSizer(wxHORIZONTAL);
    sizerButInf->Add(ButtonOK, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonCancelar, 0, wxALIGN_CENTER | wxALL, 5);
    sizerButInf->Add(ButtonAyuda, 0, wxALIGN_CENTER | wxALL, 5);

    wxBoxSizer *sizerNote = new wxBoxSizer(wxVERTICAL);
    sizerNote->Add(Notebook, 0, wxALIGN_CENTER | wxALL, 5);

    sizerNote->SetDimension(0,0,200,200);

    wxBoxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
    sizerTotal->Add(sizerArch, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerNote, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButPre, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerGen, 0, wxALIGN_CENTER | wxALL, 5);
    sizerTotal->Add(sizerButInf, 0, wxALIGN_CENTER | wxALL, 5);

    SetAutoLayout(TRUE);
    SetSizer(sizerTotal);

    sizerTotal->SetSizeHints(this);
    sizerTotal->FitInside(this);

}

DialogoReporte::~DialogoReporte()
{
}

void DialogoReporte::llenarNotebook()
{
  int i,tam;
  tam=NumPag;
  for(i=0;i<tam;i++)
  {
    PaginaSeleccionesGrilla *Pag;
    Pag= new PaginaSeleccionesGrilla(&Rep.Selecciones.Item(i),Notebook,Rep.NombreSelecciones.Item(i));
    PagSelecciones[i]=Pag;
    Notebook->AddPage(Pag,Rep.NombreSelecciones.Item(i),FALSE );
  }
}

void DialogoReporte::cerrarOk(wxCommandEvent&)
{
  for(int i=0;i<NumPag;i++)
  {
    PagSelecciones[i]->leeContenido();
  }
//  aplicar();
  wxSetWorkingDirectory(DirectorioInicial);
  Close();
}

void DialogoReporte::cancelar(wxCommandEvent&)
{
  wxSetWorkingDirectory(DirectorioInicial);
  Close();
}

void DialogoReporte::ayuda(wxCommandEvent&)
{
  Ayuda->Display(wxT("Generación de Reportes"));
}

void DialogoReporte::leerConfigura(wxCommandEvent&)
{
  for(int i=0;i<NumPag;i++)
  {
    PagSelecciones[i]->leeContenido();
  }
  Rep.readConfigura();
//  Refresh();
}

void DialogoReporte::escribirConfigura(wxCommandEvent&)
{
  for(int i=0;i<NumPag;i++)
  {
    PagSelecciones[i]->leeContenido();
  }
  Rep.writeConfigura();
}

void DialogoReporte::defecto(wxCommandEvent&)
{
  for(int i=0;i<NumPag;i++)
  {
    PagSelecciones[i]->leeContenido();
  }
  Rep.definirSelecciones();
}

void DialogoReporte::generar(wxCommandEvent&)
{
  int i;
  for(i=0;i<NumPag;i++)
  {
    PagSelecciones[i]->leeContenido();
  }
  Reporte *rep;
  switch(Tipo)
  {
    case 1: rep=new ReporteTexto;break;
    case 2: rep=new ReporteLatex;break;
    case 3: rep=new ReporteHTML;break;
    default: return;
  }
  rep->Selecciones=Rep.Selecciones;
  rep->GaugeAvance=GaugeAvance;
  wxBeginBusyCursor();
  int tam;
  wxString DirectorioEstActual;
  switch(Contenido)
  {
    case 1: rep->reporteProyecto(DirectorioActual,ArchivoActual,Proy);break;
    case 2: rep->reporteEstrategia(DirectorioActual,ArchivoActual,&Proy->Estrategias.Item(Proy->NumEstrategia));break;
    case 3: rep->reporteTodosEstrategia(DirectorioActual,ArchivoActual,Proy);break;
    case 4: rep->reporteCaso(DirectorioActual,ArchivoActual,&Proy->Casos.Item(Proy->NumCaso),Proy);break;
    case 5: rep->reporteTodosCaso(DirectorioActual,ArchivoActual,Proy);break;
    case 6: rep->reporteResultados(DirectorioActual,ArchivoActual,Proy);break;
    default: return;
  }
  wxEndBusyCursor();
  GaugeAvance->SetValue(100);
  wxMessageBox(wxT("El Reporte ha sido generado exitósamente"),wxT("Aviso"));
}

void DialogoReporte::archivo(wxCommandEvent&)
{
  for(int i=0;i<NumPag;i++)
  {
    PagSelecciones[i]->leeContenido();
  }

  wxString cad;
  switch(Tipo)
  {
    case 1: cad =wxT("Archivos de texto (*.txt)|*.txt|Todos los archivos (*.*)|*.*");break;
    case 2: cad =wxT("Archivos de LaTex (*.tex)|*.tex|Todos los archivos (*.*)|*.*");break;
    case 3: cad =wxT("Archivos HTML (*.htm*)|*.htm*|Todos los archivos (*.*)|*.*");break;
    default: return;
  }

    wxFileDialog Dial(this,wxT("Archivo de reporte"),DirectorioActual,ArchivoActual,cad,wxFD_SAVE|wxFD_CHANGE_DIR);
    if(Dial.ShowModal()==wxID_OK)
    {
      ArchivoActual=Dial.GetFilename();
      DirectorioActual=Dial.GetDirectory();
      TextArchivo->SetValue(ArchivoActual);
    }
}
