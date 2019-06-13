/***************************************************************************
                          reportetexto.cpp  -  description
                             -------------------
    begin                : jue abr 8 2004
    copyright            : (C) 2004 by 
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

#include "reportetexto.h"

ReporteTexto::ReporteTexto()
{
}

ReporteTexto::~ReporteTexto()
{
}

void ReporteTexto::encabezado(wxTextFile *f, wxString Tit)
{
  wxString cad;
  cad =wxT(""); f->AddLine(cad);
  cad=Tit.Upper(); f->AddLine(cad);
}

void ReporteTexto::cierre(wxTextFile *f)
{
  wxString cad;
  cad =wxT("");  f->AddLine(cad);
}

void ReporteTexto::seccion(wxTextFile *f,wxString Sec)
{
  if(Nivel==1)
  {
   ContadorTablas=0;
  }
  Contadores.Item(Nivel-1)++;
  wxString cad=wxT("");
  cad=cadenaNivelActual();
  IndiceContador.Add(cad);
  IndiceContenido.Add(Sec);
  cad << wxT(" ") << Sec;
  f->AddLine(wxT(""));
  cad=destino(cadenaNivelActual(),Sec);
  f->AddLine(cad);
  avance();
}

void ReporteTexto::parrafo(wxTextFile *f, wxString Par)
{
  Par.Replace(wxT("\n"),wxT("\n\n"));
  wxString cad;
  cad=Par;
  f->AddLine(cad);
  cad=wxT("");
  f->AddLine(cad);
}

void ReporteTexto::lista(wxTextFile *f, wxArrayString Nom, wxArrayString Des)
{
  wxString cad;
  int i,tam,tam2;
  tam=Nom.GetCount();
  if(tam==0){return;}
  tam2=Des.GetCount();
  for(i=0;i<tam;i++)
  {
    cad = Nom.Item(i);
    cad << wxT(" :");
    f->AddLine(cad);
    if(i<tam2)
    {
      cad= wxT("   ");
      cad << Des.Item(i);
      f->AddLine(cad);
    }
  }
}

wxString ReporteTexto::enlace(wxString Dir, wxString Dato)
{
  wxString cad=wxT("");
  Dir.Replace(wxT("_"),wxT("."));
  cad << Dato << wxT("(ver ") << Dir << wxT(")");
  return cad;
}

wxString ReporteTexto::enlaceTabla(int Tab)
{
  wxString cad=wxT("");


  cad  << wxT("Tabla ") << cadenaNivelActual().BeforeFirst('.') << wxT(".") << Tab ;
  return cad;
}

wxString ReporteTexto::destino(wxString Dir, wxString Dato)
{
  wxString cad=wxT("");
  cad << Dir << wxT(": ") << Dato;
  return cad;
}

wxString ReporteTexto::crearCadenaArchivo(wxString Dir)
{
  wxString cad;
  cad  << wxT("sec_") << Dir << wxT(".txt");
  return cad;
}

void ReporteTexto::incluirArchivo(wxTextFile *f, wxString Origen)
{
  wxTextFile fo(crearCadenaArchivo(Origen));
  fo.Open();
  int i,tam;
  tam=fo.GetLineCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=fo.GetLine(i);
    f->AddLine(cad);
  }
  fo.Close();
  wxRemoveFile(crearCadenaArchivo(Origen));
}

void ReporteTexto::tablaContenido()
{
  int i,tam;
  wxString nom=wxT("toc");
  wxTextFile *f;
  f=new wxTextFile(crearCadenaArchivo(nom));
  f->Create();
  f->AddLine(wxT(""));
  f->AddLine(wxT("Tabla de Contenido"));
  f->AddLine(wxT(""));
  tam=IndiceContador.GetCount();
  for(i=0;i<tam;i++)
  {
    int nivel=0;
    wxString nom=IndiceContador.Item(i);
    while(!nom.IsEmpty()>0)
    {
      nom=nom.AfterFirst('.');
      nivel++;
    };
    if (nivel <  (NivelMaxTOC+2))
    {
      wxString cad;
      cad << IndiceContador.Item(i) << wxT(" ") << IndiceContenido.Item(i);
      f->AddLine(cad);
    }
  }
  f->Write();
}

void ReporteTexto::tabla(wxTextFile *f,wxArrayString *lista, int tam, wxString Nombre)
{
  int i;

  wxArrayInt Columnas;
  int c,col;
  col=lista[0].GetCount();
  for(c=0;c<col;c++)
  {
    int maxCol=0;
    for(i=0;i<tam;i++)
    {
      if(maxCol<lista[i][c].Len())
      {
        maxCol=lista[i][c].Len();
      }
    }
    Columnas.Add(maxCol);
  }

  f->AddLine(wxT(""));
  wxString cad=wxT("-");
  col=Columnas.GetCount();
  for(c=0;c<col;c++)
  {
    cad.Append('-',Columnas.Item(c)+3);
  }
  f->AddLine(cad);
  
  for(i=0;i<tam;i++)
  {
    wxString linea=wxT("| ");
    int j,tam2;
    tam2=lista[i].GetCount();
    for(j=0;j<tam2;j++)
    {
      linea << lista[i][j];
      if(j<Columnas.GetCount())
      {
        for(int k=lista[i][j].Len(); k<Columnas.Item(j);k++)
        {
          linea << wxT(" ");
        }
      }
      linea << wxT(" | ");
    }
    f->AddLine(linea);
  }
  cad=wxT("-");
  col=Columnas.GetCount();
  for(c=0;c<col;c++)
  {
    cad.Append('-',Columnas.Item(c)+3);
  }
  f->AddLine(cad);
  ContadorTablas++;
  cad =wxT("Tabla ");
  cad << cadenaNivelActual().BeforeFirst('.') << wxT(".") << ContadorTablas << wxT(" ")<< Nombre;
  f->AddLine(cad);
  f->AddLine(wxT(""));
}
