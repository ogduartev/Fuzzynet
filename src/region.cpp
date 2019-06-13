/***************************************************************************
                          region.cpp  -  description
                             -------------------
    begin                : lun jul 14 2003
    copyright            : (C) 2003 by 
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

#include "region.h"

Region::Region(NodoCalculo *n)
{
  Nodo=n;
  Variable=NULL;
  Propiedad=-1;
  Numero=NULL;
  PosX=0;
  PosY=0;
  Tipo=0;
}

Region::~Region(){
  Variable=NULL;
  Propiedad=-1;
  Nodo=NULL;
  if(Numero!=NULL)
  {
    delete Numero;
    Numero=NULL;
  }
}
