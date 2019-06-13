/***************************************************************************
                          listadimensiones.cpp  -  description
                             -------------------
    begin                : mar 24 2004
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

#include "listadimensiones.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ListaDeDimensiones);

ListaDimensiones::ListaDimensiones()
{
}

ListaDimensiones::~ListaDimensiones()
{
  Nombres.Clear();
  Dimensiones.Clear();
}

void ListaDimensiones::adicionarDimension(wxString N, int d)
{
  if(Nombres.Index(N)==wxNOT_FOUND)
  {
    Nombres.Add(N);
    Dimensiones.Add(d);
  }
}

void ListaDimensiones::limpiar()
{
  Nombres.Clear();
  Dimensiones.Clear();
}


int ListaDimensiones::Dimension(wxString N)
{
  int it;
  if((it=Nombres.Index(N))!=wxNOT_FOUND)
  {
    return Dimensiones.Item(it);
  }
  return 0;
}

