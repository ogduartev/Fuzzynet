/***************************************************************************
                          listacolores.cpp  -  description
                             -------------------
    begin                : vie mar 5 2004
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

#include "listacolores.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ListaDeColores);

ListaColores::ListaColores()
{
}

ListaColores::~ListaColores()
{
  Nombres.Clear();
  Colores.Clear();
}

void ListaColores::adicionarColor(wxString N, wxColour C)
{
  if(Nombres.Index(N)==wxNOT_FOUND)
  {
    Nombres.Add(N);
    Colores.Add(C);
  }
}

void ListaColores::limpiar()
{
  Nombres.Clear();
  Colores.Clear();
}


wxColour* ListaColores::Color(wxString N)
{
  int it;
  if((it=Nombres.Index(N))!=wxNOT_FOUND)
  {
    return &Colores.Item(it);
  }
//  return wxWHITE;
  return &Colores.Item(0);
}
