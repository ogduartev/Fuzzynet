/***************************************************************************
                          region.h  -  description
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

#ifndef REGION_H
#define REGION_H


/**
  *@author 
  */

#include "proyecto.h"

/**
 *  Una Región es un rectángulo que tiene asociados apuntadores de diversos tipos
 * Se emplea para reconocer los evento de ratón
 */
class Region {
public: 
/**
 * constructor. n es el apuntador asociado
 */
	Region(NodoCalculo *n);
	~Region();
/**
 * Región rectangular asociado
 */
  wxRegion Rect;
/**
 * apuntador asociado a NodoCalculo
 */
  NodoCalculo *Nodo;
/**
 * apuntador asociado a VariableLinguistica
 */
  VariableLinguistica *Variable;
/**
 *índice asociado a Propiedades (los arreglos de Propiedades son protegidos)
 */
  int Propiedad;
/**
 * apuntador asociado a NumeroDifuso
 */
  NumeroDifuso *Numero;
/**
 * Posición horizontal en la matrix
 */
  int PosX;
/**
 * Posición vertical en la matrix
 */
  int PosY;
/**
 * Tipo de comportamiento asociado al ratón. Igual a MiCanvas::Ver
 */
  int Tipo;
};

#endif
