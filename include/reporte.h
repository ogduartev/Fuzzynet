/***************************************************************************
                          reporte.h  -  description
                             -------------------
    begin                : jue abr 8 2004
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

#ifndef REPORTE_H
#define REPORTE_H

#include <wx/config.h>
#include  <wx/textfile.h>
#include  <wx/image.h>
#include "proyecto.h"
#include "listaselecciones.h"

#include <wx/dynarray.h>

WX_DECLARE_OBJARRAY(ListaSelecciones, ListaDeListaSelecciones);

/**Esta clase se encarga de generar los reportes. es una clase virtual
  *@author 
  */

class Reporte {
public: 
	Reporte();
	~Reporte();

  void reporteProyecto(wxString dir, wxString arch, Proyecto *Proy);
  void reporteEstrategia(wxString dir, wxString arch, Estrategia *Est,bool solo=TRUE);
  void reporteTodosEstrategia(wxString dir, wxString arch, Proyecto *Proy);
  void reporteCaso(wxString dir, wxString arch, Caso *Cas,Proyecto *Proy,bool solo=TRUE);
  void reporteTodosCaso(wxString dir, wxString arch,Proyecto *Proy);
  void reporteResultados(wxString dir, wxString arch, Proyecto *Proy);

  void abreNivel();
  void cierraNivel();
  wxString cadenaNivelActual();
  wxString cadenaNivelSiguiente();
  void listaEnlaceExterno(wxTextFile *f, wxArrayString Nom, wxArrayString Des, wxArrayString Dest);
  void listaEnlaceInterno(wxTextFile *f, wxArrayString Nom, wxArrayString Des, wxArrayString Dest);

  virtual wxString remplazo(wxString c){return c;}
  
  virtual void encabezado(wxTextFile *f, wxString Tit)=0;
  virtual void cierre(wxTextFile *f)=0;
  virtual void seccion(wxTextFile *f,wxString Sec)=0;
  virtual void parrafo(wxTextFile *f, wxString Par)=0;
  virtual void lista(wxTextFile *f, wxArrayString Nom, wxArrayString Des)=0;
  virtual wxString enlace(wxString Dir, wxString Dato)=0;
  virtual wxString enlaceTabla(int Tab)=0;
  virtual wxString enlaceFigura(int Fig)=0;
  virtual wxString enlaceExterno(wxString Dir, wxString Dato){return enlace(Dir,Dato);}
  virtual wxString destino(wxString Dir, wxString Dato)=0;
  virtual wxString crearCadenaArchivo(wxString Dir)=0;
  virtual wxTextFile* crearArchivo(wxString Dir);
  virtual void abrirArchivo(wxTextFile* f){f->Create();};
  virtual void cerrarArchivo(wxTextFile* f){f->Write();};
  virtual void incluirArchivo(wxTextFile *f, wxString Origen)=0;
  virtual void tablaContenido()=0;
  virtual void postProceso(wxString arch,wxString Nombre){}
  virtual void tabla(wxTextFile *f,wxArrayString *lista, int tam, wxString Nombre)=0;
  virtual bool figuraVariable(VariableLinguistica *Var,NumeroDifuso *Num=NULL,int entrada=1)=0;
  virtual void incluirFigura(wxTextFile *f,wxString Nom)=0;

  void estructuraProyecto(wxTextFile *f, Proyecto *Proy);
  void escribirProyecto(wxTextFile *f, Proyecto *Proy);
  void escribirEstrategia(wxTextFile *f, Estrategia *Est);
  void escribirCaso(wxTextFile *f, Caso *Cas,Proyecto *Proy);
  void escribirNodo(wxTextFile *f,NodoCalculo *Nod,ListaNodos *Nodos);
  void escribirVariable(wxTextFile *f,VariableLinguistica *Var);
  virtual void escribirFuncion(wxTextFile *f,Funcion *F);
  void escribirParametrosFuncion(wxTextFile *f,Funcion *F,NodoCalculo *Nod);
  void escribirNumero(wxTextFile *f, NumeroDifuso *Num, VariableLinguistica *Var,float opt, float rep,Caso *Cas,int entrada);
  void escribirResultados(wxTextFile *f, Proyecto *Proy);
  void escribirResultadosInterpretacionCorta(wxTextFile *f, Proyecto *Proy, Estrategia *Est);
  void escribirResultadosInterpretacionOrdenada(wxTextFile *f, Proyecto *Proy, Estrategia *Est);
  void escribirResultadosInterpretacionLarga(wxTextFile *f, Proyecto *Proy, Estrategia *Est);
  void escribirResultadosInterpretacionSensibilidad(wxTextFile *f, Proyecto *Proy, Estrategia *Est);

  void definirSelecciones();
  int seleccion(wxString Bloque, wxString Nombre);
  void writeConfigura();
  void readConfigura();
  void avance();
  int calcularProgresoTotalProyecto(Proyecto *Proy);
  int calcularProgresoTotalEstrategia(Estrategia *Est);
  int calcularProgresoTotalTodosEstrategia(Proyecto *Proy);
  int calcularProgresoTotalCaso(Caso *Cas,Proyecto *Proy);
  int calcularProgresoTotalTodosCaso(Proyecto *Proy);
  int calcularProgresoTotalResultados(Proyecto *Proy);

  ListaDeListaSelecciones Selecciones;
  wxArrayString NombreSelecciones;

  wxGauge *GaugeAvance;
protected:
  int Progreso;
  int ProgresoTotal;

  int Nivel;
  int NivelMaxTOC;

  int ContadorTablas;
  int ContadorFiguras;

  wxString ArchivoPrincipal;
  wxArrayInt Contadores;
  wxArrayString IndiceContador;
  wxArrayString IndiceContenido;


};

#endif
