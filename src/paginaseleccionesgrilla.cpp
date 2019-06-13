/***************************************************************************
                          paginaseleccionesgrilla.cpp  -  description
                             -------------------
    begin                : dom abr 18 2004
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

#include "paginaseleccionesgrilla.h"

BEGIN_EVENT_TABLE(PaginaSeleccionesGrilla, wxPanel)
//    EVT_GRID_CELL_LEFT_CLICK(PaginaSeleccionesGrilla::cambiaSeleccion)
//    EVT_CHOICE(-1,PaginaSeleccionesGrilla::leeContenido)
END_EVENT_TABLE()

PaginaSeleccionesGrilla::PaginaSeleccionesGrilla(ListaSelecciones *lista,
          wxWindow *parent,const wxString& title)
          :wxPanel(parent,-1)
{
  ListaSel=lista;
//  SetTitle(_T("Configuración de Reportes"));

  crearPagSelecciones();
}

PaginaSeleccionesGrilla::~PaginaSeleccionesGrilla()
{
}

void PaginaSeleccionesGrilla::crearPagSelecciones()
{
  Grilla=new wxGrid(this,DLG_PAGSELGRILLA_GRILLA,wxPoint(0,0),wxSize(340,200));
//  Grilla->SetEditable(FALSE);
  Grilla->HideCellEditControl();
  Grilla->ForceRefresh();


// Falta darle tamaño a la grilla y llenarla de datos
  int i,tam;
  tam=ListaSel->Selecciones.GetCount();
  Grilla->CreateGrid(tam,1);
  Grilla->SetRowLabelSize(200);
  Grilla->SetColLabelSize(20);
  Grilla->SetColLabelValue(0,_T("Opciones"));
  Grilla->SetColSize(0,100);
  for(i=0;i<tam;i++)
  {
    Grilla->SetRowLabelValue(i,ListaSel->Nombres.Item(i));
    int j,tam2;
    tam2=ListaSel->Opciones.Item(i).GetCount();
    wxString *c;
    c=new wxString[tam2];
    for(j=0;j<tam2;j++)
    {
      c[j]=ListaSel->Opciones.Item(i).Item(j);
    }
    wxGridCellChoiceEditor *editor;
    editor=new wxGridCellChoiceEditor(tam2,c);
    delete[] c;
    Grilla->SetCellEditor(i,0,editor);
    wxString cad;
    cad << ListaSel->Opciones.Item(i).Item(ListaSel->Seleccion(ListaSel->Nombres.Item(i)));
    Grilla->SetCellValue(i,0,cad);
  }


  wxSizer *sizerTotal = new wxBoxSizer(wxVERTICAL);
  sizerTotal->Add(Grilla,0,wxALIGN_CENTER |wxALL, 5);

  SetAutoLayout(TRUE);
  SetSizer(sizerTotal);

  sizerTotal->SetSizeHints(this);
  sizerTotal->Fit(this);

}

void PaginaSeleccionesGrilla::cambiaSeleccion(wxGridEvent &ev)
{
  int fil,col;
  fil=ev.GetRow();
  col=ev.GetCol();
  if(col==0)
  {
    if(fil>=0 < ListaSel->Opciones.GetCount())
    {
      wxString sel;
      sel=Grilla->GetCellValue(fil,col);
      int i,tam;
      tam=ListaSel->Opciones.Item(fil).GetCount();
      for(i=0;i<tam;i++)
      {
        if(sel == ListaSel->Opciones.Item(fil).Item(i))
        {
          ListaSel->Selecciones.Item(fil)=i;
          i=tam;
        }
      }
    }
  }
}

void PaginaSeleccionesGrilla::leeContenido()
{
  Grilla->SaveEditControlValue();
  Grilla->HideCellEditControl();
  int fil,tam2;
  tam2=ListaSel->Opciones.GetCount();
  for(fil=0; fil<tam2; fil++ )
  {
    wxString sel;
    sel=Grilla->GetCellValue(fil,0);
    int i,tam;
    tam=ListaSel->Opciones.Item(fil).GetCount();
    for(i=0;i<tam;i++)
    {
      if(sel == ListaSel->Opciones.Item(fil).Item(i))
      {
        ListaSel->Selecciones.Item(fil)=i;
        i=tam;
      }
    }
  }

}
