/***************************************************************************
                          nodocalculo.h  -  description
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

#ifndef _NODOCALCULO_H
#define _NODOCALCULO_H

#include "fuzzyvar.h"
#include "caso.h"

class Proyecto;
class NodoCalculo;

WX_DECLARE_OBJARRAY(NodoCalculo,ListaNodos);

/** Implementa cada nodo de un grafo para calcular variables difusas
 * Dos nodos diferentes no pueden tener una Variable del mismo Nombre
 */
class NodoCalculo
{
//////////////////
////// ATENCION : Hay que asegurar que
////// Funcion.Orden==NodosDeCalculo.GetItemsInContainer()
//////////////////
public: 
	NodoCalculo();
	~NodoCalculo();

  NumeroDifuso* calcular();

  void copiaTemporal(wxString C);
  void restauraCopiaTemporal();
  void fijarIndefinido();
  void copiarVariableLinguistica(ListaVariables *Modelo);
  void asignarFuncion(Funcion *f);
  void llenarCasoIndefinido(Caso *caso);
  int adicionarNodo(NodoCalculo *nod,int loc=-1);
  void eliminarNodosAbajoTodos();
  void eliminarNodosAbajo(NodoCalculo *nod);
  void eliminarNodoInferior(int loc);
  NodoCalculo* arbol();
  NumeroDifuso* calcularCaso(Caso *caso);
  NodoCalculo * buscarNodo(wxString);
  NodoCalculo * buscarNodo(NodoCalculo*);
  int buscarNodoArriba(NodoCalculo*);
  void limpiarNivel();
  void calcularNivel();
  void llenarArreglo(ListaNodos *Lista,int Niv=0);
  int profundidad();
  void calcularPosicionEnNivel();
  Proyecto * getProyecto();
  bool evaluarEnlace(wxString Est);
  bool verificarEnlace(NodoCalculo *ArbolOrigen);

  void write(Mi_ofpstream &str);
  void read(Mi_ifpstream &str,ListaNodos* ListaTmp);
/**
 * Descripción del Nodo de Cálculo
 */
 wxString Descripcion;
/**
 * Esta es la representación Lingüística de la Variable calculada
 */
  VariableLinguistica VarCalculada;
/**
 * Copia temporal de VarCalculada
 */
  VariableLinguistica VarTemporal;
/**
 * Establece la Estrategia de Calculo
 *    0: Con el Valor de VarCalculada;
 *    1: Aplicando FuncionCalculo a las variable de NodosDeCalculo
 *    2: Con la evaluación de otra estrategia
 */
  int FormaDeCalculo;
/**
 * Nombre de la estrategia usado si FormaDeCalculo=2
 */
 wxString EstrategiaCalculo;
/**
 * Nombre de caso usado si FormaDeCalculo=2
 */
 wxString CasoCalculo;
/**
 * Función de Calculo del Nodo. Se aplica a la Variables de NodosDeCalculo
 */
  Funcion *FuncionCalculo;
/**
 * Vector que contiene las variables con las que se calcula VarCalculada
 */
  ListaNodos NodosDeCalculo;
/**
 * Apuntador al Nodo Padre. Si es el superior es NULL
 */
  ListaNodos NodosPadre;
/**
 * Nivel que ocupa en el árbol
 */
  int Nivel;
/**
 * Posición que ocupa en el nivel del árbol
 */
  int PosicionEnNivel;
/**
 * Offset de la Posición que ocupa en el nivel del árbol
 */
  int OffsetNivel;
/**
 * Offset de la Posición que ocupa en el nivel del árbol
 */
  int OffsetPosicionEnNivel;
/**
 * Apuntador al Proyecto. Sólo está definido a través del nodo inicial
 * Debe consultarse a través de la función getProyecto()
 */
 Proyecto* ProyectoTotal;
/**
 * Nombre alternativo a la Variable Linguistica
 */
 wxString NombreExtendido;
};


#endif
