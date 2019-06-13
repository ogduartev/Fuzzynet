/***************************************************************************
                          libreria.cpp  -  description
                             -------------------
//     begin                : abr 21 2004
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

#include "libreria.h"

Libreria::Libreria()
{
}

Libreria::~Libreria()
{
}

void Libreria::datos(wxArrayString *Nom, wxArrayString *Des,int caso)
{
  int i,tam;
  switch(caso)
  {
    case 1: // Estrategias
          tam=Estrategias.GetCount();
          for(i=0;i<tam;i++)
          {
            Nom->Add(Estrategias.Item(i).Nombre);
            Des->Add(Estrategias.Item(i).Descripcion);
          }
          break;
    case 2: // Casos
          tam=Casos.GetCount();
          for(i=0;i<tam;i++)
          {
            Nom->Add(Casos.Item(i).Nombre);
            Des->Add(Casos.Item(i).Descripcion);
          }
          break;
    case 3: // Variables
          tam=Variables.GetCount();
          for(i=0;i<tam;i++)
          {
            Nom->Add(Variables.Item(i).Nombre);
            Des->Add(Variables.Item(i).Descripcion);
          }
    default:
          break;
  }
}

void Libreria::write(Mi_ofpstream &str)
{
  int i,tam;
  tam=Estrategias.GetCount();
  str << tam;
  for(i=0;i<tam;i++)
  {
    Estrategias.Item(i).write(str);
  }
  tam=Casos.GetCount();
  str << tam;
  for(i=0;i<tam;i++)
  {
    Casos.Item(i).write(str);
  }
  tam=Variables.GetCount();
  str << tam;
  for(i=0;i<tam;i++)
  {
    Variables.Item(i).write(str);
  }
}

void Libreria::read(Mi_ifpstream &str)
{
  int i,tam;
  Estrategias.Clear();
  str >> tam;
  for(i=0;i<tam;i++)
  {
    Estrategia *Est;
    Est=new Estrategia;
    Est->read(str);

    Estrategias.Add(Est);
  }
  Casos.Clear();
  str >> tam;
  for(i=0;i<tam;i++)
  {
    Caso* Cas;
    Cas=new Caso;
    Cas->read(str);
    Casos.Add(Cas);
  }
  Variables.Clear();
  str >> tam;
  for(i=0;i<tam;i++)
  {
    VariableLinguistica* Var;
    Var=new VariableLinguistica;
    Var->read(str);
    Variables.Add(Var);
  }
}

