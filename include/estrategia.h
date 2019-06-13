/***************************************************************************
                          estrategia.h  -  description
                             -------------------
    begin                : dom abr 13 2003
    copyright            : (C) 2003 by Oscar Germán Duarte Velasco
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   Este programa ha sido diseñado por Oscar G. Duarte V. por encargo del *
 *   Departamento de Ciencias de la Computación e Inteligencia             *
 *   Artificial de la Universidad de Granada.                              *      
 *                                                                         *
 ***************************************************************************/

#ifndef _ESTRATEGIA_H
#define _ESTRATEGIA_H

#include "caso.h"
#include "nodocalculo.h"

/**Implementa la Estrategia de cálculo de Impacto en vertederos como un grafo
  * de funciones simples que calculan diferentes variables.
  *@author Oscar Germán Duarte Velasco
  */

class Estrategia
{
public: 
  Estrategia();
  ~Estrategia();

  NumeroDifuso *calcular(Caso *caso);
  NumeroDifuso *calcularNodo(Caso *caso,wxString nom);
  void llenarCasoIndefinido(Caso *caso,int Flag=0);
  void copiarPropiedades(Caso *caso);

  void write(Mi_ofpstream &str);
  void read(Mi_ifpstream &str);

  void crearVertedero1();
  void crearVertedero2();
  void crearRed1();
  void crearRed2();
  void crearRedLink1();
  void crearRedLink2();

  
  void crearMontse1();
  void ajustarVariable(VariableLinguistica *V,float r,wxString E1,wxString E2,wxString E3,wxString E4,wxString E5);
  NodoCalculo* crearMontseIRA(NodoCalculo *IRA,wxString cad1,wxString cad2);
  void crearMontsePBCs();
  void crearMontsePBC(wxString n,wxString ex,wxString tipo,wxArrayString nom,float *P);
  void crearMontseVarIRC_C(wxString n,NodoCalculo *N_IRC,NodoCalculo *N_C,float p);

  NodoCalculo Grafo;
  Propiedades Generalidades;
  wxString Nombre;
  wxString Descripcion;
};

#endif
