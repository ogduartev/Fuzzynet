/***************************************************************************
                          montse.cpp  -  description
                             -------------------
    begin                : jue jun 23 2005
    copyright            : (C) 2005 by Oscar G. Duarte
    email                : ogduartev@unal.edu.co
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
#include "proyecto.h"

void Estrategia::ajustarVariable(VariableLinguistica *V,float r,wxString E1,wxString E2,wxString E3,wxString E4,wxString E5)
{
  Etiqueta *Et;
  V->limpiarListaEtiquetas();
  V->nuevoRango(0,r);
  Et=new Etiqueta; Et->Label=E1;Et->ND->trapecio(.0*r,.0*r,.2*r,.4*r);   Et->ND->tamano(2);V->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=E2;Et->ND->trapecio(.2*r,.4*r,.4*r,.6*r);   Et->ND->tamano(2);V->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=E3;Et->ND->trapecio(.4*r,.6*r,.6*r,.8*r);   Et->ND->tamano(2);V->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=E4;Et->ND->trapecio(.6*r,.8*r,.8*r,1.0*r);  Et->ND->tamano(2);V->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=E5;Et->ND->trapecio(.8*r,1.0*r,1.0*r,1.0*r);Et->ND->tamano(2);V->Etiquetas.Add(Et);

}


void Estrategia::crearMontse1()
{
  Funcion *F;
  float x[20];
  
  Nombre=wxT("IMV");
  // Generalidades
  Generalidades.adicionarPropiedad(wxT("Ubicación"));

  // Declaración  y construcción  de los nodos del árbol
  NodoCalculo *IRA_ASP,*IRA_ASB,*IRA_ATM,*IRA_SUE,*IRA_SAL;

  IRA_ASP=new NodoCalculo();
  IRA_ASB=new NodoCalculo();
  IRA_ATM=new NodoCalculo();
  IRA_SUE=new NodoCalculo();
  IRA_SAL=new NodoCalculo();

  Grafo.VarCalculada.Nombre=wxT("IMV");
  Grafo.NombreExtendido=wxT("Índice de Interacción Medio-Vertedero");
  Grafo.Descripcion=wxT("Este Índice evalúa de forma conjunta las diferentes afecciones a cada elemento del medio, con el objetivo de ser representativo del estado ambiental existente entre la interacción del punto de vertido y el entorno ambiental");
  ajustarVariable(&Grafo.VarCalculada,25,wxT("Muy Bajo"),wxT("Bajo"),wxT("Medio"),wxT("Alto"),wxT("Muy Alto"));
  Grafo.VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 25, uniformemente espaciados.\n");

  NodoCalculo* VA_ASP,*VA_ASB,*VA_ATM,*VA_SUE,*VA_SAL;
  
  VA_ASP=crearMontseIRA(IRA_ASP,wxT("ASP"),wxT("Aguas Superficiales"));
  VA_ASB=crearMontseIRA(IRA_ASB,wxT("ASB"),wxT("Aguas Subterráneas"));
  VA_ATM=crearMontseIRA(IRA_ATM,wxT("ATM"),wxT("Atmósfera"));
  VA_SUE=crearMontseIRA(IRA_SUE,wxT("SUE"),wxT("Suelo"));
  VA_SAL=crearMontseIRA(IRA_SAL,wxT("SAL"),wxT("Salud"));
  VA_SAL->VarCalculada.limpiarListaEtiquetas();
  VA_SAL->VarCalculada.nuevoRango(4.9999,5.0001);
  Etiqueta *Et;
  Et=new Etiqueta;Et->Label=wxT("Único");Et->ND->trapecio(5,5,5,5);Et->ND->tamano(2);
  VA_SAL->VarCalculada.Etiquetas.Add(Et);
  VA_SAL->VarCalculada.Descripcion=wxT("Sólo puede tomar el valor 5");
  
  Grafo.adicionarNodo(IRA_ASP);
  Grafo.adicionarNodo(IRA_ASB);
  Grafo.adicionarNodo(IRA_ATM);
  Grafo.adicionarNodo(IRA_SUE);
  Grafo.adicionarNodo(IRA_SAL);
  x[0]=1.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;x[4]=1.0;
  F=new CombinacionLineal(x,5,0.0);
  Grafo.asignarFuncion(F);
  
  Grafo.OffsetPosicionEnNivel=4;
  IRA_ASB->OffsetPosicionEnNivel=1;
  IRA_ATM->OffsetPosicionEnNivel=1;
  IRA_SUE->OffsetPosicionEnNivel=1;
  IRA_SAL->OffsetPosicionEnNivel=1;
  
  NodoCalculo *N;
  N=new NodoCalculo;
  N->VarCalculada.Nombre =wxT("A1");
  N->NombreExtendido=wxT("Usos del Agua");
  N->Descripcion = wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("Sin uso para el hombre"),wxT("Uso hidroeléctrico, navegación y otros"),wxT("Industria"),wxT("Agricultura"),wxT("Abastecimiento humano y recreactivo"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_ASP->adicionarNodo(N);
  N=new NodoCalculo;
  N->VarCalculada.Nombre = wxT("A2");
  N->NombreExtendido=wxT("Tipo de Masa de Agua");
  N->Descripcion = wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("Canales, acequias, estanques"),wxT("ríos de tercer orden o más: ríos, arroyyos y ramblas"),wxT("Lagunas y embalses"),wxT("Aguas marinas y ríos de primer y segundo orden"),wxT("Masas de agua permanante"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_ASP->adicionarNodo(N);
  N=new NodoCalculo;
  N->VarCalculada.Nombre =wxT("A3");
  N->NombreExtendido=wxT("Calidad");
  N->Descripcion =wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("Calidad deficiente o mala"),wxT("Estado aceptable"),wxT("Buen estado"),wxT("Muy buen estado sin especies protegidas"),wxT("Muy buen estado con especies protegidas"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_ASP->adicionarNodo(N);
  
  x[0]=1.0/3.0;x[1]=1.0/3.0;x[2]=1.0/3.0;
  F=new CombinacionLineal(x,3,0.0);
  VA_ASP->asignarFuncion(F);
  
  
  N=new NodoCalculo;
  N->VarCalculada.Nombre =wxT("B1");
  N->NombreExtendido=wxT("Usos del Agua");
  N->Descripcion =wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("Sin uso para el hombre"),wxT("Otros usos no contemplados"),wxT("Industria"),wxT("Agricultura"),wxT("Abastecimiento humano"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_ASB->adicionarNodo(N);
  N=new NodoCalculo;
  N->VarCalculada.Nombre =wxT("B2");
  N->NombreExtendido=wxT("Calidad del Agua");
  N->Descripcion =wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("Muy deficientes"),wxT("Deficientes o malas"),wxT("Estado aceptable"),wxT("Buen estado"),wxT("Muy buen estado"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_ASB->adicionarNodo(N);
  
  x[0]=1.0/2.0;x[1]=1.0/2.0;
  F=new CombinacionLineal(x,2,0.0);
  VA_ASB->asignarFuncion(F);
  
  N=new NodoCalculo;
  N->VarCalculada.Nombre =wxT("C1");
  N->NombreExtendido=wxT("Calidad del Aire");
  N->Descripcion =wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("Muy mala"),wxT("Mala"),wxT("Admisible"),wxT("Buena"),wxT("Muy Buena"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_ATM->adicionarNodo(N);
  
  x[0]=1.0;
  F=new CombinacionLineal(x,1,0.0);
  VA_ATM->asignarFuncion(F);
  
  N=new NodoCalculo;
  N->VarCalculada.Nombre =wxT("D1");
  N->NombreExtendido=wxT("usos del Suelo");
  N->Descripcion =wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("No urbanizable"),wxT("Urbanizable industrial"),wxT("Urbanizable Residencial"),wxT("Urbano industrial y urbanizable turón tico"),wxT("Urbano turístico y urbano residencial"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_SUE->adicionarNodo(N);
  N=new NodoCalculo;
  N->VarCalculada.Nombre =wxT("D2");
  N->NombreExtendido=wxT("Tipo de Vegetación");
  N->Descripcion =wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("Espacios abiertos con escasa cobertura vegetal o erial"),wxT("Formación arbustiva y herbórea sin arbolado o cultivos de secana"),wxT("Formación arbustiva y herbórea con arbolado, cultivos de regadón  o secano con ón boles aislados"),wxT("Formación matorral con arbolado, montes de población joven"),wxT("Formaciones de arbolado denso, monte autóntono o de repoblación bien asentado"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_SUE->adicionarNodo(N);
  N=new NodoCalculo;
  N->VarCalculada.Nombre =wxT("D3");
  N->NombreExtendido=wxT("Cobertura Vegetal");
  N->Descripcion =wxT("");
  ajustarVariable(&N->VarCalculada,5,wxT("1-5%"),wxT("6-25%"),wxT("26-50%"),wxT("51-75%"),wxT("76-100%"));
  N->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  VA_SUE->adicionarNodo(N);
  
  x[0]=1.0/3.0;x[1]=1.0/3.0;x[2]=1.0/3.0;
  F=new CombinacionLineal(x,3,0.0);
  VA_SUE->asignarFuncion(F);
  
  Estrategia *Est;
  Proyecto *ProyTot;
  ProyTot=this->Grafo.ProyectoTotal;
  ProyTot->Estrategias.Add(this);
  
 
  crearMontsePBCs();

}

NodoCalculo* Estrategia::crearMontseIRA(NodoCalculo *IRA,wxString cad1,wxString cad2)
{
  wxString cad;
  cad=wxT("");cad << wxT("IRA ") << cad1;
  IRA->VarCalculada.Nombre = cad;
  cad=wxT("");cad << wxT("Índice de Riesgo de Afección Ambiental para el elemento ") << cad2;
  IRA->NombreExtendido=cad;
  cad=wxT("");cad << wxT("Pretende conocer cual es el potencial de afección del elemento ") << cad2;
  IRA->Descripcion = cad;
  ajustarVariable(&IRA->VarCalculada,5,wxT("Muy Bajo"),wxT("Bajo"),wxT("Medio"),wxT("Alto"),wxT("Muy Alto"));
  IRA->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  
  NodoCalculo *PBC,*VA;
  PBC=new NodoCalculo();
  VA=new NodoCalculo();

  cad=wxT("");cad << wxT("PBC ") << cad1;
  PBC->VarCalculada.Nombre = cad;
  cad=wxT("");cad << wxT("Probabilidad de Contaminación para el elemento ") << cad2;
  PBC->NombreExtendido=cad;
  cad=wxT("");cad << wxT("Mide la probabilidad de contaminación del elemento ") << cad2;
  PBC->Descripcion = cad;
  ajustarVariable(&PBC->VarCalculada,1,wxT("Muy Bajo"),wxT("Bajo"),wxT("Medio"),wxT("Alto"),wxT("Muy Alto"));
  PBC->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 1, uniformemente espaciados.\n");
  PBC->FormaDeCalculo=2;
  PBC->EstrategiaCalculo=wxT("PBC ");
  PBC->EstrategiaCalculo << cad1 ;


  cad=wxT("");cad << wxT("VA ") << cad1;
  VA->VarCalculada.Nombre = cad;
  cad=wxT("");cad << wxT("Valor Ambiental del elemento ") << cad2;
  VA->NombreExtendido=cad;
  cad=wxT("");cad << wxT("Valor del elemento ") << cad2 << wxT(" frente a la dinámica del vertedero");
  VA->Descripcion = cad;
  ajustarVariable(&VA->VarCalculada,5,wxT("Muy Bajo"),wxT("Bajo"),wxT("Medio"),wxT("Alto"),wxT("Muy Alto"));
  VA->VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");

  Funcion *F;
  float x[20];
  
  IRA->adicionarNodo(PBC);
  IRA->adicionarNodo(VA);
  x[0]=1.0;x[1]=1.0;
  F=new Producto(x,2,0.0);
  IRA->asignarFuncion(F);
  
  return VA;
}


void Estrategia::crearMontsePBCs()
{
  wxArrayString nom;
  float P[50];
  
  //////////////// ASP-o
  P[0]=1.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
//  P[]=.0 ;nom.Add(wxT("GAS"));
  P[3]=2.0 ;nom.Add(wxT("LIX"));
  P[4]=1.0 ;nom.Add(wxT("EDV"));
//  P[]=.0 ;nom.Add(wxT("CAM"));
  P[5]=2.0 ;nom.Add(wxT("IMP"));
  P[6]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("SEG"));
  P[7]=2.0 ;nom.Add(wxT("DRN"));
  P[9]=1.0 ;nom.Add(wxT("TAL"));
  P[8]=1.0 ;nom.Add(wxT("TAM"));
  P[10]=2.0;nom.Add(wxT("MOR"));
  crearMontsePBC(wxT("ASP-o"),wxT("Aguas Superficiales"),wxT("Explotación y Diseño"),nom,P);

  //////////////// ASB-o
  nom.Clear();
  P[0]=1.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
//  P[]=.0 ;nom.Add(wxT("GAS"));
  P[3]=2.0 ;nom.Add(wxT("LIX"));
  P[4]=1.0 ;nom.Add(wxT("EDV"));
//  P[]=.0 ;nom.Add(wxT("CAM"));
  P[5]=2.0 ;nom.Add(wxT("IMP"));
  P[6]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("SEG"));
  P[7]=2.0 ;nom.Add(wxT("DRN"));
  P[8]=1.0 ;nom.Add(wxT("TAL"));
  P[9]=1.0 ;nom.Add(wxT("TAM"));
  P[10]=2.0;nom.Add(wxT("MOR"));
  crearMontsePBC(wxT("ASB-o"),wxT("Aguas Subterráneas"),wxT("Explotación y Diseño"),nom,P);

  //////////////// ATM-o
  nom.Clear();
  P[0]=1.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
  P[3]=2.0 ;nom.Add(wxT("GAS"));
//  P[]=2.0 ;nom.Add(wxT("LIX"));
  P[4]=1.0 ;nom.Add(wxT("EDV"));
  P[5]=1.0 ;nom.Add(wxT("CAM"));
//  P[]=2.0 ;nom.Add(wxT("IMP"));
  P[6]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("SEG"));
//  P[]=2.0 ;nom.Add(wxT("DRN"));
  P[7]=1.0 ;nom.Add(wxT("TAL"));
  P[8]=1.0 ;nom.Add(wxT("TAM"));
  P[9]=2.0;nom.Add(wxT("MOR"));
  crearMontsePBC(wxT("ATM-o"),wxT("Atmósfera"),wxT("Explotación y Diseño"),nom,P);

  //////////////// SUE-o
  nom.Clear();
  P[0]=2.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
  P[3]=1.0 ;nom.Add(wxT("GAS"));
  P[4]=2.0 ;nom.Add(wxT("LIX"));
  P[5]=1.0 ;nom.Add(wxT("EDV"));
//  P[]=.0 ;nom.Add(wxT("CAM"));
  P[6]=1.0 ;nom.Add(wxT("IMP"));
  P[7]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("SEG"));
//  P[]=2.0 ;nom.Add(wxT("DRN"));
  P[8]=2.0 ;nom.Add(wxT("TAL"));
  P[9]=1.0 ;nom.Add(wxT("TAM"));
  P[10]=2.0;nom.Add(wxT("MOR"));
  crearMontsePBC(wxT("SUE-o"),wxT("Suelo"),wxT("Explotación y Diseño"),nom,P);

  //////////////// SAL-o
  nom.Clear();
  P[0]=1.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
  P[3]=1.0 ;nom.Add(wxT("GAS"));
  P[4]=2.0 ;nom.Add(wxT("LIX"));
  P[5]=1.0 ;nom.Add(wxT("EDV"));
//  P[]=.0 ;nom.Add(wxT("CAM"));
//  P[]=2.0 ;nom.Add(wxT("IMP"));
  P[6]=2.0 ;nom.Add(wxT("MCB"));
  P[7]=2.0 ;nom.Add(wxT("SEG"));
//  P[]=2.0 ;nom.Add(wxT("DRN");
  P[8]=1.0 ;nom.Add(wxT("TAL"));
  P[9]=1.0 ;nom.Add(wxT("TAM"));
  P[10]=2.0;nom.Add(wxT("MOR"));
  crearMontsePBC(wxT("SAL-o"),wxT("Salud"),wxT("Explotación y Diseño"),nom,P);

//////////////////////////////////////////////////////
    
  //////////////// ASP-u
  nom.Clear();
//  P[]=.0 ;nom.Add(wxT("ACU"));
//  P[]=.0 ;nom.Add(wxT("DIN"));
//  P[]=.0 ;nom.Add(wxT("DNP"));
  P[0]=2.0 ;nom.Add(wxT("DMA"));
//  P[]=.0 ;nom.Add(wxT("ERO"));
//  P[]=.0 ;nom.Add(wxT("FAL"));
  P[1]=2.0 ;nom.Add(wxT("MCB"));
  P[2]=2.0 ;nom.Add(wxT("PAS"));
  P[3]=2.0 ;nom.Add(wxT("PLU"));
  P[4]=2.0 ;nom.Add(wxT("PAI"));
  P[5]=2.0 ;nom.Add(wxT("PZE"));
  P[6]=1.0 ;nom.Add(wxT("SIS"));
  P[7]=1.0 ;nom.Add(wxT("TAM"));
//  P[]=.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("ASP-u"),wxT(""),wxT("Ubicación"),nom,P);
  
  //////////////// ASB-u
  nom.Clear();
  P[0]=2.0 ;nom.Add(wxT("ACU"));
//  P[]=.0 ;nom.Add(wxT("DIN"));
//  P[]=.0 ;nom.Add(wxT("DNP"));
//  P[]=.0 ;nom.Add(wxT("DMA"));
//  P[]=.0 ;nom.Add(wxT("ERO"));
  P[1]=1.0 ;nom.Add(wxT("FAL"));
  P[2]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("PAS"));
  P[3]=2.0 ;nom.Add(wxT("PLU"));
  P[4]=2.0 ;nom.Add(wxT("PAI"));
  P[5]=1.0 ;nom.Add(wxT("PZE"));
  P[6]=1.0 ;nom.Add(wxT("SIS"));
  P[7]=1.0 ;nom.Add(wxT("TAM"));
//  P[]=.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("ASB-u"),wxT(""),wxT("Ubicación"),nom,P);
  
  //////////////// ATM-u
  nom.Clear();
//  P[]=.0 ;nom.Add(wxT("ACU"));
//  P[]=.0 ;nom.Add(wxT("DIN"));
//  P[]=.0 ;nom.Add(wxT("DNP"));
//  P[]=.0 ;nom.Add(wxT("DMA"));
//  P[]=.0 ;nom.Add(wxT("ERO"));
//  P[]=.0 ;nom.Add(wxT("FAL"));
  P[0]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("PAS"));
  P[1]=2.0 ;nom.Add(wxT("PLU"));
//  P[]=.0 ;nom.Add(wxT("PAI"));
//  P[]=.0 ;nom.Add(wxT("PZE"));
  P[2]=1.0 ;nom.Add(wxT("SIS"));
  P[3]=1.0 ;nom.Add(wxT("TAM"));
  P[4]=2.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("ATM-u"),wxT(""),wxT("Ubicación"),nom,P);
  
  //////////////// SUE-u
  nom.Clear();
//  P[]=.0 ;nom.Add(wxT("ACU"));
//  P[]=.0 ;nom.Add(wxT("DIN"));
//  P[]=.0 ;nom.Add(wxT("DNP"));
//  P[]=.0 ;nom.Add(wxT("DMA"));
  P[0]=2.0 ;nom.Add(wxT("ERO"));
//  P[]=.0 ;nom.Add(wxT("FAL"));
  P[1]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("PAS"));
//  P[]=.0 ;nom.Add(wxT("PLU"));
  P[2]=2.0 ;nom.Add(wxT("PAI"));
//  P[]=.0 ;nom.Add(wxT("PZE"));
  P[3]=1.0 ;nom.Add(wxT("SIS"));
  P[4]=1.0 ;nom.Add(wxT("TAM"));
//  P[]=.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("SUE-u"),wxT(""),wxT("Ubicación"),nom,P);
  
  //////////////// SAL-u
  nom.Clear();
//  P[]=.0 ;nom.Add(wxT("ACU"));
  P[0]=2.0 ;nom.Add(wxT("DIN"));
  P[1]=2.0 ;nom.Add(wxT("DNP"));
//  P[]=.0 ;nom.Add(wxT("DMA"));
//  P[]=.0 ;nom.Add(wxT("ERO"));
//  P[]=.0 ;nom.Add(wxT("FAL"));
  P[2]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("PAS"));
//  P[]=.0 ;nom.Add(wxT("PLU"));
//  P[]=.0 ;nom.Add(wxT("PAI"));
//  P[]=.0 ;nom.Add(wxT("PZE"));
  P[3]=1.0 ;nom.Add(wxT("SIS"));
  P[4]=1.0 ;nom.Add(wxT("TAM"));
  P[5]=2.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("SAL-u"),wxT(""),wxT("Ubicación"),nom,P);
  
////////////////////////////////// Totales
  //////////////// ASP
  nom.Clear();
  P[0]=1.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
//  P[]=.0 ;nom.Add(wxT("GAS"));
  P[3]=2.0 ;nom.Add(wxT("LIX"));
  P[4]=1.0 ;nom.Add(wxT("EDV"));
//  P[]=.0 ;nom.Add(wxT("CAM"));
  P[5]=2.0 ;nom.Add(wxT("IMP"));
  P[6]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("SEG"));
  P[7]=2.0 ;nom.Add(wxT("DRN"));
  P[9]=1.0 ;nom.Add(wxT("TAL"));
  P[8]=1.0 ;nom.Add(wxT("TAM"));
  P[10]=2.0;nom.Add(wxT("MOR"));
//  P[]=.0 ;nom.Add(wxT("ACU"));
//  P[]=.0 ;nom.Add(wxT("DIN"));
//  P[]=.0 ;nom.Add(wxT("DNP"));
  P[11]=2.0 ;nom.Add(wxT("DMA"));
//  P[]=.0 ;nom.Add(wxT("ERO"));
//  P[]=.0 ;nom.Add(wxT("FAL"));
//  P[1]=2.0 ;nom.Add(wxT("MCB"));
  P[12]=2.0 ;nom.Add(wxT("PAS"));
  P[13]=2.0 ;nom.Add(wxT("PLU"));
  P[14]=2.0 ;nom.Add(wxT("PAI"));
  P[15]=2.0 ;nom.Add(wxT("PZE"));
  P[16]=1.0 ;nom.Add(wxT("SIS"));
//  P[7]=1.0 ;nom.Add(wxT("TAM"));
//  P[]=.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("ASP"),wxT("Aguas Superficiales"),wxT("Total"),nom,P);

  //////////////// ASB
  nom.Clear();
  P[0]=1.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
//  P[]=.0 ;nom.Add(wxT("GAS"));
  P[3]=2.0 ;nom.Add(wxT("LIX"));
  P[4]=1.0 ;nom.Add(wxT("EDV"));
//  P[]=.0 ;nom.Add(wxT("CAM"));
  P[5]=2.0 ;nom.Add(wxT("IMP"));
  P[6]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("SEG"));
  P[7]=2.0 ;nom.Add(wxT("DRN"));
  P[8]=1.0 ;nom.Add(wxT("TAL"));
  P[9]=1.0 ;nom.Add(wxT("TAM"));
  P[10]=2.0;nom.Add(wxT("MOR"));
  P[11]=2.0 ;nom.Add(wxT("ACU"));
//  P[]=.0 ;nom.Add(wxT("DIN"));
//  P[]=.0 ;nom.Add(wxT("DNP"));
//  P[]=.0 ;nom.Add(wxT("DMA"));
//  P[]=.0 ;nom.Add(wxT("ERO"));
  P[12]=1.0 ;nom.Add(wxT("FAL"));
//  P[2]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("PAS"));
  P[13]=2.0 ;nom.Add(wxT("PLU"));
  P[14]=2.0 ;nom.Add(wxT("PAI"));
  P[15]=1.0 ;nom.Add(wxT("PZE"));
  P[16]=1.0 ;nom.Add(wxT("SIS"));
//  P[7]=1.0 ;nom.Add(wxT("TAM"));
//  P[]=.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("ASB"),wxT("Aguas Subterráneas"),wxT("Explotación y Diseño"),nom,P);

  //////////////// ATM
  nom.Clear();
  P[0]=1.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
  P[3]=2.0 ;nom.Add(wxT("GAS"));
//  P[]=2.0 ;nom.Add(wxT("LIX"));
  P[4]=1.0 ;nom.Add(wxT("EDV"));
  P[5]=1.0 ;nom.Add(wxT("CAM"));
//  P[]=2.0 ;nom.Add(wxT("IMP"));
  P[6]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("SEG"));
//  P[]=2.0 ;nom.Add(wxT("DRN"));
  P[7]=1.0 ;nom.Add(wxT("TAL"));
  P[8]=1.0 ;nom.Add(wxT("TAM"));
  P[9]=2.0;nom.Add(wxT("MOR"));
//  P[]=.0 ;nom.Add(wxT("ACU"));
//  P[]=.0 ;nom.Add(wxT("DIN"));
//  P[]=.0 ;nom.Add(wxT("DNP"));
//  P[]=.0 ;nom.Add(wxT("DMA"));
//  P[]=.0 ;nom.Add(wxT("ERO"));
//  P[]=.0 ;nom.Add(wxT("FAL"));
//  P[0]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("PAS"));
  P[10]=2.0 ;nom.Add(wxT("PLU"));
//  P[]=.0 ;nom.Add(wxT("PAI"));
//  P[]=.0 ;nom.Add(wxT("PZE"));
  P[11]=1.0 ;nom.Add(wxT("SIS"));
//  P[3]=1.0 ;nom.Add(wxT("TAM"));
  P[12]=2.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("ATM"),wxT("Atmósfera"),wxT("Explotación y Diseño"),nom,P);
  
  //////////////// SUE
  nom.Clear();
  P[0]=2.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
  P[3]=1.0 ;nom.Add(wxT("GAS"));
  P[4]=2.0 ;nom.Add(wxT("LIX"));
  P[5]=1.0 ;nom.Add(wxT("EDV"));
//  P[]=.0 ;nom.Add(wxT("CAM"));
  P[6]=1.0 ;nom.Add(wxT("IMP"));
  P[7]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("SEG"));
//  P[]=2.0 ;nom.Add(wxT("DRN"));
  P[8]=2.0 ;nom.Add(wxT("TAL"));
  P[9]=1.0 ;nom.Add(wxT("TAM"));
  P[10]=2.0;nom.Add(wxT("MOR"));
//  P[]=.0 ;nom.Add(wxT("ACU"));
//  P[]=.0 ;nom.Add(wxT("DIN"));
//  P[]=.0 ;nom.Add(wxT("DNP"));
//  P[]=.0 ;nom.Add(wxT("DMA"));
  P[11]=2.0 ;nom.Add(wxT("ERO"));
//  P[]=.0 ;nom.Add(wxT("FAL"));
//  P[1]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("PAS"));
//  P[]=.0 ;nom.Add(wxT("PLU"));
  P[12]=2.0 ;nom.Add(wxT("PAI"));
//  P[]=.0 ;nom.Add(wxT("PZE"));
  P[13]=1.0 ;nom.Add(wxT("SIS"));
  //P[4]=1.0 ;nom.Add(wxT("TAM"));
//  P[]=.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("SUE"),wxT("Suelo"),wxT("Explotación y Diseño"),nom,P);

  //////////////// SAL
  nom.Clear();
  P[0]=1.0 ;nom.Add(wxT("AMR"));
  P[1]=2.0 ;nom.Add(wxT("COB"));
  P[2]=2.0 ;nom.Add(wxT("COM"));
  P[3]=1.0 ;nom.Add(wxT("GAS"));
  P[4]=2.0 ;nom.Add(wxT("LIX"));
  P[5]=1.0 ;nom.Add(wxT("EDV"));
//  P[]=.0 ;nom.Add(wxT("CAM"));
//  P[]=2.0 ;nom.Add(wxT("IMP"));
  P[6]=2.0 ;nom.Add(wxT("MCB"));
  P[7]=2.0 ;nom.Add(wxT("SEG"));
//  P[]=2.0 ;nom.Add(wxT("DRN"));
  P[8]=1.0 ;nom.Add(wxT("TAL"));
  P[9]=1.0 ;nom.Add(wxT("TAM"));
  P[10]=2.0;nom.Add(wxT("MOR"));
//  P[]=.0 ;nom.Add(wxT("ACU"));
  P[11]=2.0 ;nom.Add(wxT("DIN"));
  P[12]=2.0 ;nom.Add(wxT("DNP"));
//  P[]=.0 ;nom.Add(wxT("DMA"));
//  P[]=.0 ;nom.Add(wxT("ERO"));
//  P[]=.0 ;nom.Add(wxT("FAL"));
//  P[2]=2.0 ;nom.Add(wxT("MCB"));
//  P[]=.0 ;nom.Add(wxT("PAS"));
//  P[]=.0 ;nom.Add(wxT("PLU"));
//  P[]=.0 ;nom.Add(wxT("PAI"));
//  P[]=.0 ;nom.Add(wxT("PZE"));
  P[13]=1.0 ;nom.Add(wxT("SIS"));
//  P[4]=1.0 ;nom.Add(wxT("TAM"));
  P[14]=2.0 ;nom.Add(wxT("VIE"));
  crearMontsePBC(wxT("SAL"),wxT("Salud"),wxT("Explotación y Diseño"),nom,P);
}

void Estrategia::crearMontsePBC(wxString n,wxString ex,wxString tipo,wxArrayString nom,float *P)
{
  
  Estrategia *Est;
  Est=new Estrategia;
  Proyecto *ProyTot;
  ProyTot=this->Grafo.ProyectoTotal;
  ProyTot->Estrategias.Add(Est);
  
  Funcion *F;
  float x[50];
  
  wxString cad;
  cad=wxT("");cad << wxT("PBC ") << n;
  Est->Nombre=cad;
  Est->Grafo.VarCalculada.Nombre=cad;
  cad=wxT(""); cad << wxT("Probabilidad de Contaminación debida a ") << tipo << wxT(" del elemento ") << ex;
  Est->Grafo.NombreExtendido=cad;
  cad=wxT(""); cad << wxT("Probabilidad de Contaminación debida a ") << tipo << wxT(" del elemento ") << ex;
  Est->Grafo.Descripcion=cad;
  ajustarVariable(&Est->Grafo.VarCalculada,1,wxT("Muy Bajo"),wxT("Bajo"),wxT("Medio"),wxT("Alto"),wxT("Muy Alto"));
  Est->Grafo.VarCalculada.Descripcion=wxT("Puede tomar valores entre 0 y 1, uniformemente espaciados.\n");

  int i,tam;
  tam=nom.GetCount();
  float SP=0.0;
  for(i=0;i<tam;i++)
  {
    NodoCalculo *IRC,*C;
    IRC=new NodoCalculo;
    C=new NodoCalculo;
        
    crearMontseVarIRC_C(nom[i],IRC,C,P[i]);
       
    IRC->adicionarNodo(C);
    Est->Grafo.adicionarNodo(IRC);
    
    Funcion *G;
    float y[5];
    y[0]=P[i];
    G=new CombinacionLineal(y,1,0.0);
    IRC->asignarFuncion(G);
    
    SP=SP+5.0*P[i];
  }
  for(i=0;i<tam;i++)
  {
    x[i]=1.0/SP;
  }
  F=new CombinacionLineal(x,tam,0.0);
  Est->Grafo.asignarFuncion(F);
  
  Est->Grafo.OffsetPosicionEnNivel=tam/2;
  
}

void Estrategia::crearMontseVarIRC_C(wxString n,NodoCalculo *N_IRC,NodoCalculo *N_C,float p)
{
  VariableLinguistica *V;
  V=&N_C->VarCalculada;
  
  wxString ext=wxT("");
  if(n==wxT("AMR"))
  {
    ajustarVariable(V,5,wxT("Muy Alto"),wxT("Alto"),wxT("Medio"),wxT("Bajo"),wxT("Muy Bajo"));
    ext=wxT("Asentamiento de la Masa de Residuos");
  }else if(n==wxT("COB"))
  {
    ajustarVariable(V,5,wxT("Muy Adecuada"),wxT("Adecuada"),wxT("Media"),wxT("Deficiente"),wxT("Muy Deficiente"));
    ext=wxT("Cobertura Final");
  }else if(n==wxT("COM"))
  {
    ajustarVariable(V,5,wxT("Muy Alta"),wxT("Alta"),wxT("Media"),wxT("Baja"),wxT("Nula"));
    ext=wxT("Compactación");
  }else if(n==wxT("GAS"))
  {
    ajustarVariable(V,5,wxT("Muy Adecuado"),wxT("Adecuado"),wxT("Regular"),wxT("Bajo"),wxT("Nulo"));
    ext=wxT("Control de Gases");
  }else if(n==wxT("LIX"))
  {
    ajustarVariable(V,5,wxT("Muy Adecuado"),wxT("Adecuado"),wxT("Regular"),wxT("Bajo"),wxT("Nulo"));
    ext=wxT("Control de Lixiviados");
  }else if(n==wxT("EDV"))
  {
    ajustarVariable(V,5,wxT("Viejo"),wxT("Maduro"),wxT("Edad Media"),wxT("Joven"),wxT("Muy Joven"));
    ext=wxT("Edad del Vertedero");
  }else if(n==wxT("CAM"))
  {
    ajustarVariable(V,5,wxT("Muy Adecuado"),wxT("Adecuado"),wxT("Regular"),wxT("Deficiente"),wxT("Inadecuado"));
    ext=wxT("Estado de Caminos Internos");
  }else if(n==wxT("IMP"))
  {
    ajustarVariable(V,5,wxT("Muy Alta"),wxT("Alta"),wxT("Regular"),wxT("Baja"),wxT("Muy Baja"));
    ext=wxT("Impermeabilización del Punto de Vertido");
  }else if(n==wxT("MCB"))
  {
    ajustarVariable(V,5,wxT("Muy Satisfactorio"),wxT("Satisfactorio"),wxT("Regular"),wxT("Deficiente"),wxT("Inadecuado"));
    ext=wxT("Material de Cobertura");
  }else if(n==wxT("SEG"))
  {
    ajustarVariable(V,5,wxT("Muy Alta"),wxT("Alta"),wxT("Regular"),wxT("Baja"),wxT("Muy Baja"));
    ext=wxT("Seguridad y Vectores Asociados");
  }else if(n==wxT("DRN"))
  {
    ajustarVariable(V,5,wxT("Muy adecuado"),wxT("Adecuado"),wxT("Regular"),wxT("Deficiente"),wxT("Muy Deficiente"));
    ext=wxT("Sistema de Drenaje Superficial");
  }else if(n==wxT("TAL"))
  {
    ajustarVariable(V,5,wxT("Pendiente Muy Adecuada"),wxT("Pendiente Adecuada"),wxT("Pendiente Media"),wxT("Pendiente Baja"),wxT("Pendiente No adecuada"));
    ext=wxT("Taludes de Residuos");
  }else if(n==wxT("TAM"))
  {
    ajustarVariable(V,5,wxT("Muy Baja"),wxT("Baja"),wxT("Media"),wxT("Alta"),wxT("Muy Alta"));
    ext=wxT("Tamaón  de la Población");
  }else if(n==wxT("MOR"))
  {
    ajustarVariable(V,5,wxT("Muy Bajo Poder Contaminante"),wxT("Bajo Poder Contaminante"),wxT("Medio Poder Contaminante"),wxT("Alto Poder Contaminante"),wxT("Muy Alto Poder Contaminante"));
    ext=wxT("Tipo de Residuos y porcentaje de Materia Orgón ica"); ////////Inicio Ubicación
  }else if(n==wxT("ACU"))
  {
    ajustarVariable(V,5,wxT("Clasificación GOD Muy Baja"),wxT("Clasificación GOD Baja"),wxT("Clasificación GOD Media"),wxT("Clasificación GOD Alta"),wxT("Clasificación GOD Muy Alta"));
    ext=wxT("Características del Acuífero");
  }else if(n==wxT("DIN"))
  {
    ajustarVariable(V,5,wxT("Muy Alta"),wxT("Alta"),wxT("Media"),wxT("Baja"),wxT("Muy Baja"));
    ext=wxT("Distancia a Infraestructuras");
  }else if(n==wxT("DNP"))
  {
    ajustarVariable(V,5,wxT("Muy Alta"),wxT("Alta"),wxT("Media"),wxT("Baja"),wxT("Muy Baja"));
    ext=wxT("Distancia a Núcleos Poblados");
  }else if(n==wxT("DMA"))
  {
    ajustarVariable(V,5,wxT("Muy Alta"),wxT("Alta"),wxT("Media"),wxT("Cercana"),wxT("Contacto Directo"));
    ext=wxT("Distancia a Masas de Aguas Superficiales");
  }else if(n==wxT("ERO"))
  {
    ajustarVariable(V,5,wxT("Muy Baja"),wxT("Baja"),wxT("Media"),wxT("Marcada"),wxT("Avanzada"));
    ext=wxT("Erosión ");
  }else if(n==wxT("FAL"))
  {
    ajustarVariable(V,5,wxT("Muy Lejanas"),wxT("Lejanas e Inactivas"),wxT("Lejanas y Activas"),wxT("En el Vaso e Inactivas"),wxT("En el Vaso y Activas"));
    ext=wxT("Fallas");
  }else if(n==wxT("PAS"))
  {
    ajustarVariable(V,5,wxT("Muy Baja"),wxT("Baja"),wxT("Media"),wxT("Alta"),wxT("Muy Alta"));
    ext=wxT("Pendiente hacia Masas de Aguas Superficiales");
  }else if(n==wxT("PLU"))
  {
    ajustarVariable(V,5,wxT("Muy Baja"),wxT("Baja"),wxT("Media"),wxT("Alta"),wxT("Muy Alta"));
    ext=wxT("Pluviometría");
  }else if(n==wxT("PAI"))
  {
    ajustarVariable(V,5,wxT("Riesgo Inundación Muy Bajo"),wxT("Riesgo Inundación Bajo"),wxT("Riesgo Inundación Medio"),wxT("Riesgo Inundación Alto"),wxT("Riesgo Inundación Muy Alto"));
    ext=wxT("Punto Situado en área Inundable");
  }else if(n==wxT("PZE"))
  {
    ajustarVariable(V,5,wxT("Potencial Muy Bajo"),wxT("Potencial Bajo"),wxT("Potencial Medio"),wxT("Potencial Alto"),wxT("Potencial Muy Alto"));
    ext=wxT("Punto Situado en Zona de Escorrentía");
  }else if(n==wxT("SIS"))
  {
    ajustarVariable(V,5,wxT("Muy Bajo"),wxT("Bajo"),wxT("Medio"),wxT("Alto"),wxT("Muy Alto"));
    ext=wxT("Riesgo Sísmico");
  }else if(n==wxT("VIE"))
  {
    ajustarVariable(V,5,wxT("Muy Favorable"),wxT("Favorable"),wxT("Medio"),wxT("Desfavirable"),wxT("Muy Desfavorable"));
    ext=wxT("Viento");
  }
  
  wxString cad;
  
  cad=wxT("");cad << wxT("IRC ") << n;
  N_IRC->VarCalculada.Nombre=cad;
  cad=wxT("");cad << wxT("Índice de Riesgo de Contaminación para la variable ") << ext;
  N_IRC->NombreExtendido=cad;
  cad=wxT("");cad << wxT("Índice de Riesgo de Contaminación para la variable ") << ext;
  N_IRC->Descripcion=cad;
  ajustarVariable(&N_IRC->VarCalculada,5*p,wxT("Muy Baja"),wxT("Baja"),wxT("Media"),wxT("Alta"),wxT("Muy Alta"));
  cad=wxT("");cad << wxT("Puede tomar valores entre 0 y ") << 5*p << wxT(", uniformemente espaciados.\n");
  N_IRC->VarCalculada.Descripcion=cad;

  
  N_C->VarCalculada.Nombre=n;
  cad=wxT("");cad << wxT("Condición para la variable ") << ext;
  N_C->NombreExtendido=cad;
  cad=wxT("");cad << wxT("Condición para la variable ") << ext;
  N_C->Descripcion=cad;
  cad=wxT("");cad << wxT("Puede tomar valores entre 0 y 5, uniformemente espaciados.\n");
  N_C->VarCalculada.Descripcion=cad;

}
  
