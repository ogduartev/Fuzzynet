/***************************************************************************
                          listafuentes.cpp  -  description
                             -------------------
    begin                : mar 10 2004
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

#include "listafuentes.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ListaDeFuentes);

ListaFuentes::ListaFuentes()
{
}

ListaFuentes::~ListaFuentes()
{
  Nombres.Clear();
  Fuentes.Clear();
}

void ListaFuentes::adicionarFuente(wxString N, wxFont F)
{
  if(Nombres.Index(N)==wxNOT_FOUND)
  {
    Nombres.Add(N);
    Fuentes.Add(F);
  }
}

void ListaFuentes::limpiar()
{
  Nombres.Clear();
  Fuentes.Clear();
}


wxFont* ListaFuentes::Fuente(wxString N)
{
  int it;
  if((it=Nombres.Index(N))!=wxNOT_FOUND)
  {
    return &Fuentes.Item(it);
  }
  return &Fuentes.Item(0);
//  return wxNORMAL_FONT;
}
