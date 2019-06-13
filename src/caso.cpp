/***************************************************************************
                          caso.cpp  -  description
                             -------------------
    begin                : mar abr 15 2003
    copyright            : (C) 2003 by Oscar G. Duarte V.
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   Este programa ha sido diseñado por Oscar G. Duarte V. por encargo del *
 *   Departamento de Ciencias de la Computación e Inteligencia             *
 *   Artificial de la Universidad de Granada.                              *      
 *                                                                         *
 ***************************************************************************/

#include "caso.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ListaVariables);

Caso::Caso()
{
  Nombre=wxT("Sin Nombre");
}

Caso::~Caso()
{
}

void Caso::write(Mi_ofpstream &str)
{
  str << Nombre;
  str << Descripcion;
  int i,tam;
  tam=Variables.GetCount();
  str << tam;
  for(i=0;i<tam;i++)
  {
    Variables.Item(i).write(str);
  }
  Generalidades.write(str);
}

void Caso::read(Mi_ifpstream &str)
{
  str >> Nombre;
  str >> Descripcion;
  int i,tam;
  Variables.Clear();
  str >> tam;
  for(i=0;i<tam;i++)
  {
    VariableLinguistica *Var;
    Var=new VariableLinguistica;
    Var->read(str);
    Variables.Add(Var);
  }
  Generalidades.read(str);
}
