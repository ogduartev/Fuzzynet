/***************************************************************************
                          diputacion.cpp  -  description
                             -------------------
    begin                : mar abr 20 2004
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

#include "estrategia.h"
 
 /**
 * Implementación de la primera estrategia de cálculo de impacto en vertederos
 */
void Estrategia::crearVertedero1()
{

  // Generalidades

  Generalidades.adicionarPropiedad(wxT("Municipios"));
  Generalidades.modificarValor(wxT("Municipios"),wxT("Núcleos poblacionales incluidos."));
  Generalidades.adicionarPropiedad(wxT("Otros vertederos"));
  Generalidades.modificarValor(wxT("Otros vertederos"),wxT("Otros vertederos del municipio."));
  Generalidades.adicionarPropiedad(wxT("Evaluadores"));
  Generalidades.modificarValor(wxT("Evaluadores"),wxT("Nombre de los evaluadores del vertedero."));
  Generalidades.adicionarPropiedad(wxT("No. Ficha"));
  Generalidades.modificarValor(wxT("No. Ficha"),wxT("Número de Ficha de Campo."));
  Generalidades.adicionarPropiedad(wxT("Fecha"));
  Generalidades.modificarValor(wxT("Fecha"),wxT("Fecha en la que se realizó la visita al vertedero."));
  Generalidades.adicionarPropiedad(wxT("Estado"));
  Generalidades.modificarValor(wxT("Estado"),wxT("Estado Acttivo, Clausurado, Inactivo, etc. del vertedero."));
  Generalidades.adicionarPropiedad(wxT("Otros"));
  Generalidades.modificarValor(wxT("Otros"),wxT("Otras consideraciones sobre el vertedero."));

  // Declaración y construcción de los nodos del árbol
  NodoCalculo *PSP,*PSB,*PSU,*PAT,*PNA,*PSA;
  NodoCalculo *VSP,*VSB,*VSU,*VAT,*VNA,*VSA;
  NodoCalculo *ISP,*ISB,*ISU,*IAT,*INA,*ISA,*IPA;
  NodoCalculo *TSP,*TSB,*TSU,*TAT,*TNA,*TSA,*TPA;
  NodoCalculo *NE,*RI,*VL,*PI,*PL,*OT;
  NodoCalculo *LIX,*NA,*CO,*INS,*RE,*PE,*DV;
  NodoCalculo *C1,*CT,*CS,*IE,*CUB,*CP,*CPTMP,*P2,*P1,*P3,*POB; 

  PSP=new NodoCalculo();PSB=new NodoCalculo();PSU=new NodoCalculo();PAT=new NodoCalculo();PNA=new NodoCalculo();PSA=new NodoCalculo();
  VSP=new NodoCalculo();VSB=new NodoCalculo();VSU=new NodoCalculo();VAT=new NodoCalculo();VNA=new NodoCalculo();VSA=new NodoCalculo();
  ISP=new NodoCalculo();ISB=new NodoCalculo();ISU=new NodoCalculo();IAT=new NodoCalculo();INA=new NodoCalculo();ISA=new NodoCalculo();IPA=new NodoCalculo();
  TSP=new NodoCalculo();TSB=new NodoCalculo();TSU=new NodoCalculo();TAT=new NodoCalculo();TNA=new NodoCalculo();TSA=new NodoCalculo();TPA=new NodoCalculo();
  NE=new NodoCalculo();RI=new NodoCalculo();VL=new NodoCalculo();PI=new NodoCalculo();PL=new NodoCalculo();OT=new NodoCalculo();
  LIX=new NodoCalculo();NA=new NodoCalculo();CO=new NodoCalculo();INS=new NodoCalculo();RE=new NodoCalculo();PE=new NodoCalculo();DV=new NodoCalculo();
  C1=new NodoCalculo();CT=new NodoCalculo();CS=new NodoCalculo();IE=new NodoCalculo();CUB=new NodoCalculo();CP=new NodoCalculo();CPTMP=new NodoCalculo();P2=new NodoCalculo();P3=new NodoCalculo();P1=new NodoCalculo();POB=new NodoCalculo();

//  Definición de Variables

  Grafo.VarCalculada.Nombre=wxT("CFIN");
  Etiqueta *Et; VariableLinguistica *Var;

  Var=&(Grafo.VarCalculada);
  Var->limpiarListaEtiquetas();
  Var->nuevoRango(0,1000);
  Et=new Etiqueta; Et->Label=wxT("Bajo");Et->ND->trapecio(0,0,30,70);Et->ND->tamano(2);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(30,70,80,120);Et->ND->tamano(2);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Alto");Et->ND->trapecio(80,120,250,350);Et->ND->tamano(2);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Alto");Et->ND->trapecio(250,350,1000,1000);Et->ND->tamano(2);Var->Etiquetas.Add(Et);
  Var->Descripcion=wxT("Puede tomar valores entre 0 y 600, si bien su distribución queda muy desplazada hacia valores bajos, coincidiendo con la tipología de los ncleos de población predominantes en la provincia de Granada, que genera vertederos pequeños con residuos eminentemente domésticos. Esto hace que su calificación establecida relativamente sea la que se ha definido.\n");
// V: semántica provisional. revisar pag. 8

  PSP->VarCalculada.Nombre=wxT("PSP");
  Var=&(PSP->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,.75,1.25);Et->ND->tamano(2); Et->Label=wxT("Nula");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.75,1.25,1.25,1.75);Et->ND->tamano(2); Et->Label=wxT("Baja");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.25,1.75,1.75,2);Et->ND->tamano(2); Et->Label=wxT("Alta");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(1.75,2,2,2);Et->ND->tamano(2); Et->Label=wxT("Inminente");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  PSB->VarCalculada.Nombre=wxT("PSB");
  Var=&(PSB->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,.75,1.25);Et->ND->tamano(2); Et->Label=wxT("Nula");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.75,1.25,1.25,1.75);Et->ND->tamano(2); Et->Label=wxT("Baja");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.25,1.75,1.75,2);Et->ND->tamano(2); Et->Label=wxT("Alta");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(1.75,2,2,2);Et->ND->tamano(2); Et->Label=wxT("Inminente");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  PSU->VarCalculada.Nombre=wxT("PSU");
  Var=&(PSU->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,.75,1.25);Et->ND->tamano(2); Et->Label=wxT("Nula");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.75,1.25,1.25,1.75);Et->ND->tamano(2); Et->Label=wxT("Baja");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.25,1.75,1.75,2);Et->ND->tamano(2); Et->Label=wxT("Alta");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(1.75,2,2,2);Et->ND->tamano(2); Et->Label=wxT("Inminente");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  PAT->VarCalculada.Nombre=wxT("PAT");
  Var=&(PAT->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,.75,1.25);Et->ND->tamano(2); Et->Label=wxT("Nula");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.75,1.25,1.25,1.75);Et->ND->tamano(2); Et->Label=wxT("Baja");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.25,1.75,1.75,2);Et->ND->tamano(2); Et->Label=wxT("Alta");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(1.75,2,2,2);Et->ND->tamano(2); Et->Label=wxT("Inminente");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  PNA->VarCalculada.Nombre=wxT("PNA");
  Var=&(PNA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,.75,1.25);Et->ND->tamano(2); Et->Label=wxT("Nula");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.75,1.25,1.25,1.75);Et->ND->tamano(2); Et->Label=wxT("Baja");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.25,1.75,1.75,2);Et->ND->tamano(2); Et->Label=wxT("Alta");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(1.75,2,2,2);Et->ND->tamano(2); Et->Label=wxT("Inminente");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  PSA->VarCalculada.Nombre=wxT("PSA");
  Var=&(PSA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,.75,1.25);Et->ND->tamano(2); Et->Label=wxT("Nula");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.75,1.25,1.25,1.75);Et->ND->tamano(2); Et->Label=wxT("Baja");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.25,1.75,1.75,2);Et->ND->tamano(2); Et->Label=wxT("Alta");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(1.75,2,2,2);Et->ND->tamano(2); Et->Label=wxT("Inminente");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

// V: semántica provisional. revisar pag. 8

  VSP->VarCalculada.Nombre=wxT("VSP");
  Var=&(VSP->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,5);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,1.5,2.5);Et->ND->tamano(2); Et->Label=wxT("Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1.5,2.5,3.5,4.5);Et->ND->tamano(2); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(3.5,4.5,4.5,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(4.5,5,5,5);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  VSB->VarCalculada.Nombre=wxT("VSB");
  Var=&(VSB->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,5);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,1.5,2.5);Et->ND->tamano(2); Et->Label=wxT("Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1.5,2.5,3.5,4.5);Et->ND->tamano(2); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(3.5,4.5,4.5,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(4.5,5,5,5);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  VSU->VarCalculada.Nombre=wxT("VSU");
  Var=&(VSU->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,5);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,1.5,2.5);Et->ND->tamano(2); Et->Label=wxT("Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1.5,2.5,3.5,4.5);Et->ND->tamano(2); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(3.5,4.5,4.5,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(4.5,5,5,5);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  VAT->VarCalculada.Nombre=wxT("VAT");
  Var=&(VAT->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,5);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,1.5,2.5);Et->ND->tamano(2); Et->Label=wxT("Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1.5,2.5,3.5,4.5);Et->ND->tamano(2); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(3.5,4.5,4.5,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(4.5,5,5,5);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  VNA->VarCalculada.Nombre=wxT("VNA");
  Var=&(VNA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,5);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,1.5,2.5);Et->ND->tamano(2); Et->Label=wxT("Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1.5,2.5,3.5,4.5);Et->ND->tamano(2); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(3.5,4.5,4.5,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(4.5,5,5,5);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  VSA->VarCalculada.Nombre=wxT("VSA");
  Var=&(VSA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,5);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,1.5,2.5);Et->ND->tamano(2); Et->Label=wxT("Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1.5,2.5,3.5,4.5);Et->ND->tamano(2); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(3.5,4.5,4.5,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(4.5,5,5,5);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

// I: semántica provisional. revisar pag. 9

  ISP->VarCalculada.Nombre=wxT("ISP");
  Var=&(ISP->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,2,3);Et->ND->tamano(2); Et->Label=wxT("Bajo/Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(2,3,4,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(4,5,6,7);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(6,7,10,10);Et->ND->tamano(2); Et->Label=wxT("Muy Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  ISB->VarCalculada.Nombre=wxT("ISB");
  Var=&(ISB->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,2,3);Et->ND->tamano(2); Et->Label=wxT("Bajo/Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(2,3,4,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(4,5,6,7);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(6,7,10,10);Et->ND->tamano(2); Et->Label=wxT("Muy Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  ISU->VarCalculada.Nombre=wxT("ISU");
  Var=&(ISU->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,2,3);Et->ND->tamano(2); Et->Label=wxT("Bajo/Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(2,3,4,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(4,5,6,7);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(6,7,10,10);Et->ND->tamano(2); Et->Label=wxT("Muy Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  IAT->VarCalculada.Nombre=wxT("IAT");
  Var=&(IAT->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,2,3);Et->ND->tamano(2); Et->Label=wxT("Bajo/Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(2,3,4,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(4,5,6,7);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(6,7,10,10);Et->ND->tamano(2); Et->Label=wxT("Muy Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  INA->VarCalculada.Nombre=wxT("INA");
  Var=&(INA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,2,3);Et->ND->tamano(2); Et->Label=wxT("Bajo/Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(2,3,4,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(4,5,6,7);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(6,7,10,10);Et->ND->tamano(2); Et->Label=wxT("Muy Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  ISA->VarCalculada.Nombre=wxT("ISA");
  Var=&(ISA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,2,3);Et->ND->tamano(2); Et->Label=wxT("Bajo/Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(2,3,4,5);Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(4,5,6,7);Et->ND->tamano(2); Et->Label=wxT("Alto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(6,7,10,10);Et->ND->tamano(2); Et->Label=wxT("Muy Alto");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  IPA->VarCalculada.Nombre=wxT("IPA");
  Var=&(IPA->VarCalculada);
  Var->autodefinirRecto(2);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,0,0);Et->ND->tamano(2);  Et->Label=wxT("Bajo/Nulo");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(10,10,10,10);Et->ND->tamano(2);  Et->Label=wxT("Con Impacto");

// T: semántica provisional. revisar pag. 13

  TSP->VarCalculada.Nombre=wxT("TSP");
  Var=&(TSP->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(.5,.75,.75,1);Et->ND->tamano(2); Et->Label=wxT("Quema");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1.5,1.75,2,2);Et->ND->tamano(2); Et->Label=wxT("Recubrimiento");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Mixto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Nada");
  Var->Descripcion=wxT("El índice de tratamiento tendrá un valor que oscila entre 0 y 2, de modo que los tratamientos que aumentan el impacto tendrán un valor mayor que uno y los que disminuyen el impacto tendrán un valor menor que uno.");

  TSB->VarCalculada.Nombre=wxT("TSB");
  Var=&(TSB->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(.5,.75,.75,1);Et->ND->tamano(2); Et->Label=wxT("Quema");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Recubrimiento");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Mixto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Nada");
  Var->Descripcion=wxT("El índice de tratamiento tendrá un valor que oscila entre 0 y 2, de modo que los tratamientos que aumentan el impacto tendrán un valor mayor que uno y los que disminuyen el impacto tendrán un valor menor que uno.");

  TSU->VarCalculada.Nombre=wxT("TSU");
  Var=&(TSU->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Quema");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1,1.25,1.25,1.5);Et->ND->tamano(2); Et->Label=wxT("Recubrimiento");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1,1.25,1.25,1.5);Et->ND->tamano(2); Et->Label=wxT("Mixto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Nada");
  Var->Descripcion=wxT("El índice de tratamiento tendrá un valor que oscila entre 0 y 2, de modo que los tratamientos que aumentan el impacto tendrán un valor mayor que uno y los que disminuyen el impacto tendrán un valor menor que uno.");

  TAT->VarCalculada.Nombre=wxT("TAT");
  Var=&(TAT->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(1.5,1.75,2,2);Et->ND->tamano(2); Et->Label=wxT("Quema");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.25,.5,.5,.75);Et->ND->tamano(2); Et->Label=wxT("Recubrimiento");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.5,1.75,2,2);Et->ND->tamano(2); Et->Label=wxT("Mixto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Nada");
  Var->Descripcion=wxT("El índice de tratamiento tendrá un valor que oscila entre 0 y 2, de modo que los tratamientos que aumentan el impacto tendrán un valor mayor que uno y los que disminuyen el impacto tendrán un valor menor que uno.");

  TNA->VarCalculada.Nombre=wxT("TNA");
  Var=&(TNA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(1.5,1.75,2,2);Et->ND->tamano(2); Et->Label=wxT("Quema");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(1.5,1.75,2,2);Et->ND->tamano(2); Et->Label=wxT("Recubrimiento");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.5,1.75,2,2);Et->ND->tamano(2); Et->Label=wxT("Mixto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Nada");
  Var->Descripcion=wxT("El índice de tratamiento tendrá un valor que oscila entre 0 y 2, de modo que los tratamientos que aumentan el impacto tendrán un valor mayor que uno y los que disminuyen el impacto tendrán un valor menor que uno.");

  TSA->VarCalculada.Nombre=wxT("TSA");
  Var=&(TSA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(1.25,1.5,1.5,1.75);Et->ND->tamano(2); Et->Label=wxT("Quema");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.5,.75,.75,1);Et->ND->tamano(2); Et->Label=wxT("Recubrimiento");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(.5,.75,.75,1);Et->ND->tamano(2); Et->Label=wxT("Mixto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Nada");
  Var->Descripcion=wxT("El índice de tratamiento tendrá un valor que oscila entre 0 y 2, de modo que los tratamientos que aumentan el impacto tendrán un valor mayor que uno y los que disminuyen el impacto tendrán un valor menor que uno.");

  TPA->VarCalculada.Nombre=wxT("TPA");
  Var=&(TPA->VarCalculada);
  Var->autodefinirRecto(4);
  Var->nuevoRango(0,2);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(1.5,1.75,2,2);Et->ND->tamano(2); Et->Label=wxT("Quema");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(.5,.75,.75,1);Et->ND->tamano(2); Et->Label=wxT("Recubrimiento");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(1.5,1.75,2,2);Et->ND->tamano(2); Et->Label=wxT("Mixto");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(.75,1,1,1.25);Et->ND->tamano(2); Et->Label=wxT("Nada");
  Var->Descripcion=wxT("El índice de tratamiento tendrá un valor que oscila entre 0 y 2, de modo que los tratamientos que aumentan el impacto tendrán un valor mayor que uno y los que disminuyen el impacto tendrán un valor menor que uno.");

// X: semántica provisional. revisar pag. 11

  NE->VarCalculada.Nombre=wxT("NE");
  Var=&(NE->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,5);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  RI->VarCalculada.Nombre=wxT("RI");
  Var=&(RI->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,25);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  VL->VarCalculada.Nombre=wxT("VL");
  Var=&(VL->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,30);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  PL->VarCalculada.Nombre=wxT("PL");
  Var=&(PL->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  PI->VarCalculada.Nombre=wxT("PI");
  Var=&(PI->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  OT->VarCalculada.Nombre=wxT("OT");
  Var=&(OT->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,20);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  LIX->VarCalculada.Nombre=wxT("LIX");
  Var=&(LIX->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,30);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  NA->VarCalculada.Nombre=wxT("NA");
  Var=&(NA->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,25);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  CO->VarCalculada.Nombre=wxT("CO");
  Var=&(CO->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,30);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  INS->VarCalculada.Nombre=wxT("INS");
  Var=&(INS->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  RE->VarCalculada.Nombre=wxT("RE");
  Var=&(RE->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,20);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  PE->VarCalculada.Nombre=wxT("PE");
  Var=&(PE->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,25);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  DV->VarCalculada.Nombre=wxT("DV");
  Var=&(DV->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Pocos");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Algunos");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Muchos");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

// X: semántica provisional, no asignada en el texto

  C1->VarCalculada.Nombre=wxT("C1");
  Var=&(C1->VarCalculada);
  Var->autodefinirRecto(5);
  Var->nuevoRango(0,10);
//  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,100,300);Et->ND->tamano(2); Et->Label=wxT("Adecuado");
//  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(10,300,300,500);Et->ND->tamano(2); Et->Label=wxT("Soportable");
//  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(300,500,700,900);Et->ND->tamano(2); Et->Label=wxT("Desfavorable");
//  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(700,900,1300,1500);Et->ND->tamano(2); Et->Label=wxT("Muy Desfavorable");
//  Et=&Var->Etiquetas.Item(4); Et->ND->trapecio(1300,1500,2000,2000);Et->ND->tamano(2); Et->Label=wxT("Alto Riesgo");
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Adecuado");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Soportable");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Desfavorable");
  Et=&Var->Etiquetas.Item(3); Et->ND->tamano(2); Et->Label=wxT("Muy Desfavorable");
  Et=&Var->Etiquetas.Item(4); Et->ND->tamano(2); Et->Label=wxT("Alto Riesgo");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea;. se ha tomado de CT");

  CT->VarCalculada.Nombre=wxT("CT");
  Var=&(CT->VarCalculada);
  Var->autodefinirRecto(5);
  Var->nuevoRango(0,200);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,10,30);Et->ND->tamano(2); Et->Label=wxT("Adecuado");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(10,30,30,50);Et->ND->tamano(2); Et->Label=wxT("Soportable");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(30,50,70,90);Et->ND->tamano(2); Et->Label=wxT("Desfavorable");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(70,90,130,150);Et->ND->tamano(2); Et->Label=wxT("Muy Desfavorable");
  Et=&Var->Etiquetas.Item(4); Et->ND->trapecio(130,150,200,200);Et->ND->tamano(2); Et->Label=wxT("Alto Riesgo");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea;. se ha tomado de CUB");

  CS->VarCalculada.Nombre=wxT("CS");
  Var=&(CS->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alto");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  IE->VarCalculada.Nombre=wxT("IE");
  Var=&(IE->VarCalculada);
  Var->autodefinirRecto(3);
  Var->nuevoRango(0,15);
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alto");
  Var->Descripcion=wxT("Contenido semántico definido de forma homogénea.");

  CUB->VarCalculada.Nombre=wxT("CUB");
  Var=&(CUB->VarCalculada);
  Var->autodefinirRecto(5);
  Var->nuevoRango(0,100);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,5,15);Et->ND->tamano(2); Et->Label=wxT("Adecuado");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(5,15,15,25);Et->ND->tamano(2); Et->Label=wxT("Soportable");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(15,25,35,45);Et->ND->tamano(2); Et->Label=wxT("Desfavorable");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(35,45,65,75);Et->ND->tamano(2); Et->Label=wxT("Muy Desfavorable");
  Et=&Var->Etiquetas.Item(4); Et->ND->trapecio(65,75,100,100);Et->ND->tamano(2); Et->Label=wxT("Alto Riesgo");
  Var->Descripcion=wxT("La valoración de la probabilidad no es homogénea");

  P1->VarCalculada.Nombre=wxT("P1");
  Var=&(P1->VarCalculada);
  Var->autodefinirRecto(5);
  Var->nuevoRango(0,1000);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,50,150);Et->ND->tamano(2); Et->Label=wxT("Adecuado");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(50,150,150,250);Et->ND->tamano(2); Et->Label=wxT("Soportable");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(150,250,350,450);Et->ND->tamano(2); Et->Label=wxT("Desfavorable");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(350,450,650,750);Et->ND->tamano(2); Et->Label=wxT("Muy Desfavorable");
  Et=&Var->Etiquetas.Item(4); Et->ND->trapecio(650,750,1000,1000);Et->ND->tamano(2); Et->Label=wxT("Alto Riesgo");
  Var->Descripcion=wxT("La descripción semántica se ha tomado de CUB");

  P2->VarCalculada.Nombre=wxT("P2");
  Var=&(P2->VarCalculada);
  Var->autodefinirRecto(5);
  Var->nuevoRango(0,250);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Muy Bajo");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(3); Et->ND->tamano(2); Et->Label=wxT("Alto");
  Et=&Var->Etiquetas.Item(4); Et->ND->tamano(2); Et->Label=wxT("Muy Alto");
  Var->Descripcion=wxT("La descripción semántica se ha asignado de forma homogénea");

  P3->VarCalculada.Nombre=wxT("P3");
  Var=&(P3->VarCalculada);
  Var->autodefinirRecto(5);
  Var->nuevoRango(0,0.8);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Muy Bajo");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(3); Et->ND->tamano(2); Et->Label=wxT("Alto");
  Et=&Var->Etiquetas.Item(4); Et->ND->tamano(2); Et->Label=wxT("Muy Alto");
  Var->Descripcion=wxT("La descripción semántica se ha asignado de forma homogénea");

// semántica provisional, pag 14

  POB->VarCalculada.Nombre=wxT("POB");
  Var=&(POB->VarCalculada);
  Var->autodefinirRecto(6);
  Var->nuevoRango(0,50000);
  Et=&Var->Etiquetas.Item(0); Et->ND->trapecio(0,0,250,750); Et->ND->tamano(2); Et->Label=wxT("Muy Pequeña");
  Et=&Var->Etiquetas.Item(1); Et->ND->trapecio(250,750,750,1250); Et->ND->tamano(2); Et->Label=wxT("Pequeña");
  Et=&Var->Etiquetas.Item(2); Et->ND->trapecio(750,1250,4000,6000); Et->ND->tamano(2); Et->Label=wxT("Media");
  Et=&Var->Etiquetas.Item(3); Et->ND->trapecio(4000,6000,8000,12000); Et->ND->tamano(2); Et->Label=wxT("Grande");
  Et=&Var->Etiquetas.Item(4); Et->ND->trapecio(8000,12000,20000,30000); Et->ND->tamano(2); Et->Label=wxT("Muy Grande");
  Et=&Var->Etiquetas.Item(5); Et->ND->trapecio(20000,30000,50000,50000); Et->ND->tamano(2); Et->Label=wxT("Ciudad");
  Var->Descripcion=wxT("Esta clasificación de los tamaños de población se ha ajustado al caso de la provincia de Granada. ");

  CPTMP->VarCalculada.Nombre=wxT("CPTMP");
  Var=&(CPTMP->VarCalculada);
  Var->autodefinirRecto(6);
  Var->nuevoRango(0,12);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Muy Pequeña");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Pequeña");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Media");
  Et=&Var->Etiquetas.Item(3); Et->ND->tamano(2); Et->Label=wxT("Grande");
  Et=&Var->Etiquetas.Item(4); Et->ND->tamano(2); Et->Label=wxT("Muy Grande");
  Et=&Var->Etiquetas.Item(5); Et->ND->tamano(2); Et->Label=wxT("Ciudad");
  Var->Descripcion=wxT("La clasificación del tamaño de población es homogénea (lineal) en esta variable. Debe acotarse al rango 0-10");

  CP->VarCalculada.Nombre=wxT("CP");
  Var=&(CP->VarCalculada);
  Var->autodefinirRecto(6);
  Var->nuevoRango(0,10);
  Et=&Var->Etiquetas.Item(0); Et->ND->tamano(2); Et->Label=wxT("Muy Pequeña");
  Et=&Var->Etiquetas.Item(1); Et->ND->tamano(2); Et->Label=wxT("Pequeña");
  Et=&Var->Etiquetas.Item(2); Et->ND->tamano(2); Et->Label=wxT("Media");
  Et=&Var->Etiquetas.Item(3); Et->ND->tamano(2); Et->Label=wxT("Grande");
  Et=&Var->Etiquetas.Item(4); Et->ND->tamano(2); Et->Label=wxT("Muy Grande");
  Et=&Var->Etiquetas.Item(5); Et->ND->tamano(2); Et->Label=wxT("Ciudad");
  Var->Descripcion=wxT("La clasificación del tamaño de población es homogénea (lineal) en esta variable. Este nodo acota al rango 0-10");

  // asignación de los nodos y funciones
  Funcion *F;
  float x[20];

  Grafo.Descripcion=wxT("Este coeficiente pretende articular todos los coeficientes parciales que se generan a lo largo de la valoración, de manera que su magnitud queda condicionada por ellos de acuerdo con las siguientes premisas:\n");
  Grafo.Descripcion << wxT("- Los diferentes riesgos de afección al medio natural definen el coeficiente de ubicación, el cual interviene de modo decisivo en el valor del coeficiente final\n");
  Grafo.Descripcion << wxT("- El tratamiento que recibe el vertedero limita las posibles afecciones que puede ocasionar al medio natural\n");
  Grafo.Descripcion << wxT("- El tamaño del vertedero es el que limita mayormente el impacto causado");
  Grafo.Descripcion << wxT("Aunque se trata del coeficiente final, no es por ello el único, ni más importante, determinante en la valoración del vertedero; sino, más bien una magnitud globalizadora de la información, que permite discernir cuando otros indicadores de afecciones puntuales entran en discordia. Este coeficiente es más bien un indicador de la potencialidad futura del vertedero en virtud a su tamaño, emplazamiento, tipología de los residuos y tratamiento.");
        
  Grafo.adicionarNodo(P3);
  Grafo.adicionarNodo(P1);
  Grafo.adicionarNodo(P2);
  x[0]=1;x[1]=1;x[2]=1;
  F=new ProdSuma(x,3,0.0);
  Grafo.asignarFuncion(F);

  P1->adicionarNodo(CUB);
  x[0]=10;
  F=new CombinacionLineal(x,1,0.0);
  P1->asignarFuncion(F);
  P1->Descripcion=wxT("Esta función es tan sólo un cambio de escala sobre el valor de CUB");

  P3->adicionarNodo(CP);
  x[0]=0.08;
  F=new CombinacionLineal(x,1,0.0);
  P3->asignarFuncion(F);
  P3->Descripcion=wxT("Esta función es tan sólo un cambio de escala sobre el valor de CP");

/*  CP->adicionarNodo(CPTMP);
  x[0]=1.0;
  F=new CombinacionLinealAcotada(x,1.0,0.0,0.0,10.0);
  CP->asignarFuncion(F);
  CP->Descripcion=wxT("Coeficiente de magnitud del vertedero, acotado al rango 0-10.\n");

  CPTMP->adicionarNodo(POB);
  x[0]=0.292;x[1]=0.352;
  // ajustada con las parejas:
  // 250    2
  // 750    3
  // 3000   5
  // 7500   7
  // 17500  9
  // 25000  10
  // La función vale > 10 para CP > 22946
  // por esta razón hay que acotarla.
  F=new Polinomio(x,x+1,1);
  CPTMP->asignarFuncion(F);
  CPTMP->Descripcion=wxT("Coeficiente de magnitud del vertedero, definido en virtud de la población vertedora. Se han establecido unos rangos de población que permiten valorar el tamaño del vertedero en relación al volumen del mismo, parámetro que se considera más significativo que la superficie afectada, ya que ésta depende de la morfología.\n");
  CPTMP->Descripcion << wxT("Nota: La función se ha ajustado a partir de la tabla de cálculo de CP, empleando mínmos cuadrados para una aproximación polinomial.");
*/
  CUB->adicionarNodo(ISP);
  CUB->adicionarNodo(ISB);
  CUB->adicionarNodo(ISU);
  CUB->adicionarNodo(IAT);
  CUB->adicionarNodo(INA);
  CUB->adicionarNodo(ISA);
  CUB->adicionarNodo(IPA);
  x[0]=2;x[1]=3;x[2]=1;x[3]=.5;x[4]=1.5;x[5]=1.5;x[6]=.5;
  F=new CombinacionLineal(x,7,0.0);
  CUB->asignarFuncion(F);

  C1->adicionarNodo(CT);
  x[0]=0.05;
  F=new CombinacionLineal(x,1,0);
  C1->asignarFuncion(F);
  C1->Descripcion=wxT("cambio de escala sobre CT");

  P2->adicionarNodo(C1);
  P2->adicionarNodo(CS);
  P2->adicionarNodo(IE);
  x[0]=1;x[1]=1;x[2]=1;
  F=new ProdSuma(x,3,0.0);
  P2->asignarFuncion(F);
  P2->Descripcion=wxT("Nodo sin descripción");

  CT->adicionarNodo(ISP);
  CT->adicionarNodo(TSP);
  CT->adicionarNodo(ISB);
  CT->adicionarNodo(TSB);
  CT->adicionarNodo(ISU);
  CT->adicionarNodo(TSU);
  CT->adicionarNodo(IAT);
  CT->adicionarNodo(TAT);
  CT->adicionarNodo(INA);
  CT->adicionarNodo(TNA);
  CT->adicionarNodo(ISA);
  CT->adicionarNodo(TSA);
  CT->adicionarNodo(IPA);
  CT->adicionarNodo(TPA);
  x[0]=2;x[2]=3;x[4]=1;x[6]=.5;x[8]=1.5;x[10]=1.5;x[12]=.5;
  x[1]=1;x[3]=1;x[5]=1;x[7]=1;x[9]=1;x[11]=1;x[13]=1;
  F=new SumaProd(x,14,0.0);
  CT->asignarFuncion(F);
  CT->Descripcion =wxT("Coeficiente de Tratamiento: El tipo de tratamiento que estos vertederos reciben es, en la mayor parte de los casos inadecuado, ya que generalmente se trata de quema incontrolada o recubrimiento con escombros, lo cual, más que minimizar el impacto del vertido lo incrementa.\n");
  CT->Descripcion<<wxT("A la hora de incluir este factor en la evaluación del impacto, se analiza el efecto que tiene cada tipo de tratamiento sobre cada uno de los elementos del medio evaluados, estableciento un índice de tratamiento que, al multiplicarse por el índice de afección, grava o minimiza su impacto\n");
  CT->Descripcion<<wxT("Así la quema se puede considerar una práctica positiva para las aguas superficiales o subterráneas, ya que se presupone una eliminación de lixiviados; pero por otra parte, grava la afección negativa a la atmósfera, salud o paisaje además del riesgo de incendio que se supone en vertederos situados en zonas de cierto valior natural.\n");
  CT->Descripcion<<wxT("Por su parte, el recubrimiento, realizado con escombros y de modo no controlado, se puede considerar como un vertido adicional, con el consiguiente riesgo de afección a los recursos hídricos por contaminación con metales pesados. Además, esta práctica aumenta la probabilidad de una combustión espontánea y por tanto incendio; si bien disminuye el impacto sobre la salud pública, paisaje y atmósfera pues evita olores, y el contacto directo con animales domésticos y personas.\n");
  CT->Descripcion<<wxT("En los vertederos en los que no se realiza tratamiento, el valor de este coeficiente coincide con el Coeficiente de Ubicación.\n");

  TSP->Descripcion=wxT("Índice de Tratamiento para las Aguas superficiales.");
  TSB->Descripcion=wxT("Índice de Tratamiento para las Aguas subterráneas.");
  TSU->Descripcion=wxT("Índice de Tratamiento para los Suelos.");
  TAT->Descripcion=wxT("Índice de Tratamiento para la Atmósfera.");
  TNA->Descripcion=wxT("Índice de Tratamiento para los Espacios naturales.");
  TSA->Descripcion=wxT("Índice de Tratamiento para la Salud pública.");
  TPA->Descripcion=wxT("Índice de Tratamiento para el Paisaje.");
  IPA->Descripcion=wxT("Índice de afección paisajística, indica el impacto visual del vertedero, su tipo de tratamiento y la sensibilidad de la zona donde se ubica. Su determinación se realiza de modo distinto a los demás Índices de afección.");

  ISP->adicionarNodo(PSP);
  ISP->adicionarNodo(VSP);
  x[0]=1;x[1]=1;
  F=new Producto(x,2,0.0);
  ISP->asignarFuncion(F);
  ISP->Descripcion=wxT("Índice de afección a aguas superficiales, define el riesgo de afección a las aguas superficiales, en función de vertidos a cauces o proximidades y el aprovechamiento que de sus aguas se realizan");
  PSP->Descripcion=wxT("Probabilidad de ocurrencia del impacto sobre aguas superficiales.");
  VSP->Descripcion=wxT("Valor del Impacto sobre aguas superficiales.");

  ISB->adicionarNodo(PSB);
  ISB->adicionarNodo(VSB);
  x[0]=1;x[1]=1;
  F=new Producto(x,2,0.0);
  ISB->asignarFuncion(F);
  ISB->Descripcion=wxT("Índice de afección a aguas subterráneas, define el riesgo de afección a las aguas subterráneas por vertidos sobre sustratos de diversa permeabilidad con o sin aprovechamiento del agua subterránea");
  PSB->Descripcion=wxT("Probabilidad de ocurrencia del impacto sobre aguas subterráneas.");
  VSB->Descripcion=wxT("Valor del Impacto sobre aguas subterráneas.");

  ISU->adicionarNodo(PSU);
  ISU->adicionarNodo(VSU);
  x[0]=1;x[1]=1;
  F=new Producto(x,2,0.0);
  ISU->asignarFuncion(F);
  ISU->Descripcion=wxT("Índice de afección a suelos, indica el riesgo de afección a suelos por vertidos especialmente contaminantes, dispersión de residuos, uso de suelos colindantes, etc.");
  PSU->Descripcion=wxT("Probabilidad de ocurrencia del impacto sobre suelos.");
  VSU->Descripcion=wxT("Valor del Impacto sobre aguas suelos.");

  IAT->adicionarNodo(PAT);
  IAT->adicionarNodo(VAT);
  x[0]=1;x[1]=1;
  F=new Producto(x,2,0.0);
  IAT->asignarFuncion(F);
  IAT->Descripcion=wxT("Índice de afección por contamnación atmosférica, determina el riesgo de contaminación atmosférica por quema de residuos, olores, humo etc. ,y la posibilidad de impacto a poblaciones o transeuntes");
  PAT->Descripcion=wxT("Probabilidad de ocurrencia del impacto por contaminación atmosférica.");
  VAT->Descripcion=wxT("Valor del Impacto por contaminación atmosférica.");

  INA->adicionarNodo(PNA);
  INA->adicionarNodo(VNA);
  x[0]=1;x[1]=1;
  F=new Producto(x,2,0.0);
  INA->asignarFuncion(F);
  INA->Descripcion=wxT("Índice de afección al patrimonio cultural, definido en virtud del riesgo de afección a habitats y ecosistemas de cierto valor natural o cultural");
  PNA->Descripcion=wxT("Probabilidad de ocurrencia del impacto a patrimonio cultural.");
  VNA->Descripcion=wxT("Valor del Impacto a patrimonio cultural.");

  ISA->adicionarNodo(PSA);
  ISA->adicionarNodo(VSA);
  x[0]=1;x[1]=1;
  F=new Producto(x,2,0.0);
  ISA->asignarFuncion(F);
  ISA->Descripcion=wxT("Índice de afección a la salud, definido en virtud del riesgo de afección a la salud o poblaciones como consecuencia de la proximidad de zonas o elementos urbanos, presencia de vallado, etc.");
  PSA->Descripcion=wxT("Probabilidad de ocurrencia del impacto a la salud.");
  VSA->Descripcion=wxT("Valor del Impacto a la salud.");

  CS->adicionarNodo(NE);
  CS->adicionarNodo(RI);
  CS->adicionarNodo(VL);
  CS->adicionarNodo(PL);
  CS->adicionarNodo(PI);
  CS->adicionarNodo(OT);
  x[0]=.1;x[1]=.1;x[2]=.1;x[3]=.1;x[4]=.1;x[5]=.1;
  F=new CombinacionLineal(x,6,0.0);
  CS->asignarFuncion(F);
  CS->Descripcion=wxT("Coeficiente de Circunstancias Singulares, que pretende resumir aquellos aspectos singulares relacionados con la composición del vertido, o sea, la presencia de componentes distintos de los residuos domésticos.");
  NE->Descripcion=wxT("Existencia de neumáticos.");
  RI->Descripcion=wxT("Residuos Industriales.");
  VL->Descripcion=wxT("Vertidos Líquidos.");
  PI->Descripcion=wxT("Acumulación de Pilas.");
  PL->Descripcion=wxT("Plaguicidas.");
  OT->Descripcion=wxT("Otros.");

  IE->adicionarNodo(LIX);
  IE->adicionarNodo(NA);
  IE->adicionarNodo(CO);
  IE->adicionarNodo(INS);
  IE->adicionarNodo(RE);
  IE->adicionarNodo(PE);
  IE->adicionarNodo(DV);
  x[0]=.1;x[1]=.1;x[2]=.1;x[3]=.1;x[4]=.1;x[5]=.1;x[6]=.1;
  F=new CombinacionLineal(x,7,0.0);
  IE->asignarFuncion(F);
  IE->Descripcion=wxT("Coeficiente de Impactos Evidentes, que se define en base a los datos aportados por las fichas de campo en relación a los impactos detectables a simple vista.");
  LIX->Descripcion=wxT("Presencia de Lixiviados.");
  NA->Descripcion=wxT("Quema de neumáticos.");
  CO->Descripcion=wxT("Combustión incontrolada.");
  INS->Descripcion=wxT("Abundancia de insectos o roedores.");
  RE->Descripcion=wxT("Rebusca o transeuntes.");
  PE->Descripcion=wxT("Sustrato permeable.");
  DV->Descripcion=wxT("Dispersión por vientos.");

///// Offsets del Grafo
  Grafo.OffsetPosicionEnNivel=8;
  P1->OffsetPosicionEnNivel=5;
  P2->OffsetPosicionEnNivel=13;
  CUB->OffsetPosicionEnNivel=5;
  CS->OffsetPosicionEnNivel=6;
  IE->OffsetPosicionEnNivel=5;
  C1->OffsetPosicionEnNivel=6;
  CT->OffsetPosicionEnNivel=13;
  NE->OffsetPosicionEnNivel=3;
  LIX->OffsetPosicionEnNivel=1;
  ISP->OffsetPosicionEnNivel=2;
  ISB->OffsetPosicionEnNivel=1;
  ISU->OffsetPosicionEnNivel=1;
  IAT->OffsetPosicionEnNivel=1;
  INA->OffsetPosicionEnNivel=1;
  ISA->OffsetPosicionEnNivel=1;
  IPA->OffsetPosicionEnNivel=1;
  TSP->OffsetPosicionEnNivel=1;
  POB->OffsetNivel=1;
  PSP->OffsetPosicionEnNivel=1;
  
}
