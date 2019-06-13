/***************************************************************************
                          listaselecciones.cpp  -  description
                             -------------------
    begin                : jue mar 25 2004
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

#include "listaselecciones.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ListaDeOpciones);
WX_DEFINE_OBJARRAY(ListaDeSelecciones);

ListaSelecciones::ListaSelecciones()
{
}

ListaSelecciones::~ListaSelecciones()
{
  Nombres.Clear();
  Opciones.Clear();
  Selecciones.Clear();
}


void ListaSelecciones::adicionarSeleccion(wxString N, wxArrayString C, int S)
{
  if(Nombres.Index(N)==wxNOT_FOUND)
  {
    Nombres.Add(N);
    Opciones.Add(C);
    Selecciones.Add(S);
  }
}

void ListaSelecciones::limpiar()
{
  Nombres.Clear();
  Selecciones.Clear();
}


wxArrayString* ListaSelecciones::Opcion(wxString N)
{
  int it;
  if((it=Nombres.Index(N))!=wxNOT_FOUND)
  {
    return &Opciones.Item(it);
  }
  return NULL;
}

int ListaSelecciones::Seleccion(wxString N)
{
  int it;
  if((it=Nombres.Index(N))!=wxNOT_FOUND)
  {
    return Selecciones.Item(it);
  }
  return 0;
}

void ListaSelecciones::seleccion(wxString N,int S)
{
  int it;
  if((it=Nombres.Index(N))!=wxNOT_FOUND)
  {
    if( S >= 0 && S < Opciones.Item(it).GetCount())
    {
      Selecciones.Item(it)=S;
    }
  }
}
