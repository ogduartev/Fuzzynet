/***************************************************************************
                          proyecto.h  -  description
                             -------------------
    begin                : vie abr 25 2003
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

#ifndef PROYECTO_H
#define PROYECTO_H

#include "estrategia.h"
#include "listaselecciones.h"
WX_DECLARE_OBJARRAY(Estrategia, ListaEstrategias);
WX_DECLARE_OBJARRAY(Caso, ListaCasos);


/**
 * Encapsula todo el proyecto. Tiene un arreglo de Estartegias y un arreglo de Casos
  */
class Proyecto {
public: 
	Proyecto();
	~Proyecto();
  void iniciar(int Opcion);
  void calcularTodo();
  NumeroDifuso* calcularCasoEstrategia(wxString C,wxString E);
  void ordenNombre(int desc=0);
  void ordenGeneralidad(wxString pr,int desc=0);
  void ordenValor(NodoCalculo *nod,float opt=0.5, float r=0,int desc=0);
  void exportar(wxString nom,wxArrayString NombresCas,ListaSelecciones NombresEst,wxString Separador,int Opcion,bool Prop);
  void importar(wxString nom,ListaSelecciones Opciones,char Separador);
  void importaLinea(wxString NombreCaso,wxArrayString NombreNodos,wxArrayString DatosEnLinea,ListaSelecciones Opciones);

//  void crearRed1(Estrategia *est);
//  void crearRed2(Estrategia *est);

/**
 * Listado de Estrategias del Proyecto
 */
  ListaEstrategias Estrategias;
/**
 * Listado de Casos del Proyecto
 */
  ListaCasos Casos;
/**
 * Listado de Propiedades del Proyecto
 */
  Propiedades Generalidades;
/**
 * Descripcion del Proyecto
 */
  wxString Descripcion;
/**
 * Nmero de estrategia que se está visualizando
 */
  int NumEstrategia;
/**
 *  Numero del caso que se está visualizando
 */
  int NumCaso;
/**
 * Optimismo del decisor.
  */
  float Optimismo;
/**
 * Representatividad de cada alfa corte.
  */
  float Representatividad;
/**
 * Bandera para ssaber si debe salvarsae
  */
  bool ProyectoModificado;

  void write(Mi_ofpstream &str);
  bool read(Mi_ifpstream &str);

};

#endif
