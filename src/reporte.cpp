/***************************************************************************
                          reporte.cpp  -  description
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

#include "reporte.h"
#include <wx/dcps.h>
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ListaDeListaSelecciones);


Reporte::Reporte()
{
  wxInitAllImageHandlers();
  Nivel=0;
  definirSelecciones();
  GaugeAvance=NULL;
  Progreso=0;
  ProgresoTotal=0;

}

Reporte::~Reporte()
{
}

void Reporte::reporteProyecto(wxString dir, wxString arch, Proyecto *Proy)
{
  ProgresoTotal=calcularProgresoTotalProyecto(Proy);
  NivelMaxTOC=seleccion(wxT("Proyecto"),wxT("Profundidad Tabla de Contenido"));
  wxSetWorkingDirectory(dir);
  ArchivoPrincipal=arch;
  wxTextFile f(arch);
  f.Create();
  wxString titulo=wxT("Reporte de Proyecto");
  encabezado(&f,titulo);
  estructuraProyecto(&f,Proy);
  cierre(&f);
  f.Write();
  postProceso(arch,titulo);
}

void Reporte::reporteEstrategia(wxString dir, wxString arch, Estrategia *Est,bool solo)
{
  if(solo)
  {
    ProgresoTotal=calcularProgresoTotalEstrategia(Est);
  }
  NivelMaxTOC=seleccion(wxT("Proyecto"),wxT("Profundidad Tabla de Contenido"));
  wxSetWorkingDirectory(dir);
  ArchivoPrincipal=arch;
  wxTextFile f(arch),faux(wxT("_tmp"));
  f.Create();
  faux.Create();
  wxString titulo=wxT("Reporte de Metodología - ");
  titulo << remplazo(Est->Nombre);
  encabezado(&f,titulo);
  escribirEstrategia(&faux,Est);
  tablaContenido();
  wxString cadTOC=wxT("toc");
  incluirArchivo(&f,cadTOC);
  int i,tam;
  tam=faux.GetLineCount();
  for(i=0;i<tam;i++)
  {
    f.AddLine(faux.GetLine(i));
  }
  faux.Close();
  cierre(&f);
  f.Write();
  postProceso(arch,titulo);
}

void Reporte::reporteTodosEstrategia(wxString dir, wxString arch, Proyecto *Proy)
{
  ProgresoTotal=calcularProgresoTotalTodosEstrategia(Proy);
  wxSetWorkingDirectory(dir);
  ArchivoPrincipal=arch;
  int i,tam;
  tam=Proy->Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString DirectorioEstActual;
    DirectorioEstActual=dir;
    DirectorioEstActual << wxT("/") << Proy->Estrategias.Item(i).Nombre;
    if(!wxDirExists(DirectorioEstActual))
    {
      wxMkdir(DirectorioEstActual);
    }
    reporteEstrategia(DirectorioEstActual,ArchivoPrincipal,&Proy->Estrategias.Item(i),FALSE);
    wxSetWorkingDirectory(dir);
  }
}


void Reporte::reporteCaso(wxString dir, wxString arch, Caso *Cas,Proyecto *Proy,bool solo)
{
  if(solo)
  {
    ProgresoTotal=calcularProgresoTotalCaso(Cas,Proy);
  }
  NivelMaxTOC=seleccion(wxT("Proyecto"),wxT("Profundidad Tabla de Contenido"));
  wxSetWorkingDirectory(dir);
  ArchivoPrincipal=arch;
  wxTextFile f(arch),faux(wxT("_tmp"));
  f.Create();
  faux.Create();
  wxString titulo=wxT("Reporte de Caso - ");
  titulo << remplazo(Cas->Nombre);
  encabezado(&f,titulo);
  escribirCaso(&faux,Cas,Proy);
  tablaContenido();
  wxString cadTOC=wxT("toc");
  incluirArchivo(&f,cadTOC);
  int i,tam;
  tam=faux.GetLineCount();
  for(i=0;i<tam;i++)
  {
    f.AddLine(faux.GetLine(i));
  }
  faux.Close();
  cierre(&f);
  f.Write();
  postProceso(arch,titulo);
}

void Reporte::reporteTodosCaso(wxString dir, wxString arch, Proyecto *Proy)
{
  ProgresoTotal=calcularProgresoTotalTodosCaso(Proy);
  wxSetWorkingDirectory(dir);
  ArchivoPrincipal=arch;
  int i,tam;
  tam=Proy->Casos.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString DirectorioEstActual;
    DirectorioEstActual=dir;
    DirectorioEstActual << wxT("/") << Proy->Casos.Item(i).Nombre;
    if(!wxDirExists(DirectorioEstActual))
    {
      wxMkdir(DirectorioEstActual);
    }
    reporteCaso(DirectorioEstActual,ArchivoPrincipal,&Proy->Casos.Item(i),Proy,FALSE);
    wxSetWorkingDirectory(dir);
  }

}

void Reporte::reporteResultados(wxString dir, wxString arch, Proyecto *Proy)
{
  ProgresoTotal=calcularProgresoTotalResultados(Proy);
  NivelMaxTOC=seleccion(wxT("Proyecto"),wxT("Profundidad Tabla de Contenido"));
  wxSetWorkingDirectory(dir);
  ArchivoPrincipal=arch;
  wxTextFile f(arch),faux(wxT("_tmp"));
  f.Create();
  faux.Create();
  wxString titulo=wxT("Resultados del Proyecto");

  encabezado(&f,titulo);
  escribirResultados(&faux,Proy);
  tablaContenido();
  wxString cadTOC=wxT("toc");
  incluirArchivo(&f,cadTOC);
  int i,tam;
  tam=faux.GetLineCount();
  for(i=0;i<tam;i++)
  {
    f.AddLine(faux.GetLine(i));
  }
  faux.Close();
  cierre(&f);
  f.Write();
  postProceso(arch,titulo);
}

void Reporte::abreNivel()
{
  Nivel ++;
  int i,tam;
  tam=Contadores.GetCount();
  for(i=tam;i<Nivel;i++)
  {
    Contadores.Add(0);
  }
  Contadores.Item(Nivel-1)=0;
}

void Reporte::cierraNivel()
{
  Nivel --;
  int i,tam;
  tam=Contadores.GetCount();
  for(i=tam;i>Nivel;i--)

  {
    Contadores.RemoveAt(i-1);
  }
}

wxString Reporte::cadenaNivelActual()
{
  wxString cad;
  int i,tam;
  tam=Contadores.GetCount();
  for(i=0;i<tam;i++)
  {
    cad << Contadores.Item(i) << wxT(".");
  }
  return cad;
}

wxString Reporte::cadenaNivelSiguiente()
{
  wxString cad;
  int i,tam;
  tam=Contadores.GetCount();
  for(i=0;i<tam-1;i++)
  {
    cad << Contadores.Item(i);
    cad << wxT(".");
  }
  cad << (Contadores.Item(tam-1)+1);
  cad << wxT(".");
  return cad;
}


wxTextFile* Reporte::crearArchivo(wxString Dir)
{
  wxTextFile *f;
  wxString cad;
  cad=crearCadenaArchivo(Dir);
  return new wxTextFile(cad);
}

void Reporte::listaEnlaceExterno(wxTextFile *f, wxArrayString Nom, wxArrayString Des, wxArrayString Dest)
{
  wxArrayString link;
  int i,tam;
  tam=Nom.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=enlaceExterno(Dest.Item(i),Nom.Item(i));
    link.Add(cad);
  }
  lista(f,link,Des);
}

void Reporte::listaEnlaceInterno(wxTextFile *f, wxArrayString Nom, wxArrayString Des, wxArrayString Dest)
{
  wxArrayString link;
  int i,tam;
  tam=Nom.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString cad;
    cad=enlace(Dest.Item(i),Nom.Item(i));
    link.Add(cad);
  }
  lista(f,link,Des);
}


void Reporte::estructuraProyecto(wxTextFile *f, Proyecto *Proy)
{
  int i,tam;
  wxString cad,cadp;
  wxString cadProyecto,cadEstrategias,cadCasos,cadResultados,cadTOC;
  wxTextFile *fp;

  abreNivel();

///////// EL PROYECTO
  if(seleccion(wxT("Proyecto"),wxT("Presentación"))==0)
  {
    // abriendo
    cadp=cadenaNivelSiguiente();
    cadp.Replace(wxT("."),wxT("_"));
    fp=crearArchivo(cadp);
    abrirArchivo(fp);
    seccion(fp,wxT("El Proyecto"));
    // contenido

    escribirProyecto(fp,Proy);

    // cerrando
    cerrarArchivo(fp);
    cadProyecto=cadp;
    //  incluirArchivo(f,cadp);
    delete fp;
  }
///////// LAS ESTRATEGIAS
  if(seleccion(wxT("Proyecto"),wxT("Metodologías"))==0)
  {

  // abriendo
    cadp=cadenaNivelSiguiente();
    cadp.Replace(wxT("."),wxT("_"));
    fp=crearArchivo(cadp);
    abrirArchivo(fp);
    seccion(fp,wxT("Metodologías"));
  // contenido
    abreNivel();
    tam=Proy->Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      Estrategia *Est;
      Est=&Proy->Estrategias.Item(i);

      wxString cade;
      wxTextFile *fe;
      cade=cadenaNivelSiguiente();
      cade.Replace(wxT("."),wxT("_"));
      fe=crearArchivo(cade);
      abrirArchivo(fe);
      seccion(fe,Est->Nombre);
    // contenido

      escribirEstrategia(fe,Est);

    // cerrando
      cerrarArchivo(fe);
      incluirArchivo(fp,cade);
      delete fe;
    }
    cierraNivel();
  // cerrando
    cerrarArchivo(fp);
    cadEstrategias=cadp;
  //  incluirArchivo(f,cadp);
    delete fp;
  }
///////// LOS CASOS

  if(seleccion(wxT("Proyecto"),wxT("Casos"))==0)
  {
  // abriendo
    cadp=cadenaNivelSiguiente();
    cadp.Replace(wxT("."),wxT("_"));
    fp=crearArchivo(cadp);
    abrirArchivo(fp);
    seccion(fp,wxT("Casos"));
  // contenido
    abreNivel();
    tam=Proy->Casos.GetCount();
    for(i=0;i<tam;i++)
    {
      Caso *Cas;
      Cas=&Proy->Casos.Item(i);

      wxString cade;
      wxTextFile *fe;
      cade=cadenaNivelSiguiente();
      cade.Replace(wxT("."),wxT("_"));
      fe=crearArchivo(cade);
      abrirArchivo(fe);
      seccion(fe,Cas->Nombre);
    // contenido

      escribirCaso(fe,Cas,Proy);

    // cerrando
      cerrarArchivo(fe);
      incluirArchivo(fp,cade);
      delete fe;
    }
    cierraNivel();
  // cerrando
    cerrarArchivo(fp);
    cadCasos=cadp;
  //  incluirArchivo(f,cadp);
    delete fp;
  }
///////// LOS RESULTADOS

  if(seleccion(wxT("Proyecto"),wxT("Resultados"))==0)
  {
  // abriendo
    cadp=cadenaNivelSiguiente();
    cadp.Replace(wxT("."),wxT("_"));
    fp=crearArchivo(cadp);
    abrirArchivo(fp);
    seccion(fp,wxT("Resultados"));
  // contenido
    escribirResultados(fp,Proy);
    cerrarArchivo(fp);
    cadResultados=cadp;
    delete fp;
  }
  cierraNivel();

  tablaContenido();
  cadTOC=wxT("toc");
  incluirArchivo(f,cadTOC);
  if(seleccion(wxT("Proyecto"),wxT("Presentación"))==0)
  {
    incluirArchivo(f,cadProyecto);
  }
  if(seleccion(wxT("Proyecto"),wxT("Metodologías"))==0)
  {
    incluirArchivo(f,cadEstrategias);
  }
  if(seleccion(wxT("Proyecto"),wxT("Casos"))==0)
  {
    incluirArchivo(f,cadCasos);
  }
  if(seleccion(wxT("Proyecto"),wxT("Resultados"))==0)
  {
    incluirArchivo(f,cadResultados);
  }
}

void Reporte::escribirProyecto(wxTextFile *f, Proyecto *Proy)
{
  abreNivel();
  wxString cad,cadaux;
  wxTextFile *faux;
  int i,tam;
  wxArrayString nom,desc,dest;

// DESCRIPCION
  if(seleccion(wxT("Proyecto"),wxT("Descripción"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Descripción"));
    cad=Proy->Descripcion;
    if(cad==wxT(""))
    {
      cad=wxT("No hay descripción disponible");
    }
    parrafo(faux,cad);
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
  }
// PROPIEDADES

  if(seleccion(wxT("Proyecto"),wxT("Propiedades"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Propiedades Generales"));
    tam=Proy->Generalidades.tamano();
    if(tam>0)
    {
      cad=wxT("Las siguientes son las propiedades generales del proyecto:");
      parrafo(faux,cad);

      lista(faux,Proy->Generalidades.listaNombres(),Proy->Generalidades.listaValores());
    }else
    {
      cad=wxT("No hay Propiedades Generales definidas en el Proyecto");
      parrafo(faux,cad);
     }
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
   }
// LISTADO DE ESTRATEGIAS

  if(seleccion(wxT("Proyecto"),wxT("Metodologías"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Metodologías"));

    cad=wxT("En el proyecto se han definido las siguientes Metodologías:");
    parrafo(faux,cad);
    tam=Proy->Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      wxString dir=wxT("2_");
      nom.Add(Proy->Estrategias.Item(i).Nombre);
      desc.Add(Proy->Estrategias.Item(i).Descripcion);
      dir << (i+1) << wxT("_");
      dest.Add(dir);
    }
    listaEnlaceExterno(faux,nom,desc,dest);

    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
   }
// LISTADO DE CASOS

  if(seleccion(wxT("Proyecto"),wxT("Casos"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Casos"));

    nom.Clear();
    desc.Clear();
    dest.Clear();
    cad=wxT("En el proyecto se han estudiado los siguientes Casos:");
    parrafo(faux,cad);
    tam=Proy->Casos.GetCount();
    for(i=0;i<tam;i++)
    {
      wxString dir=wxT("3_");
      nom.Add(Proy->Casos.Item(i).Nombre);
      desc.Add(Proy->Casos.Item(i).Descripcion);
      dir << (i+1) << wxT("_");
      dest.Add(dir);
    }
    listaEnlaceExterno(faux,nom,desc,dest);

    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
   }
///////////// Fin Proyecto
  cierraNivel();
}


void Reporte::escribirEstrategia(wxTextFile *f, Estrategia *Est)
{
  abreNivel();
  wxString cad,cadaux;
  wxTextFile *faux;
  int i,tam;

// DESCRIPCION
  if(seleccion(wxT("Metodología"),wxT("Descripción"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Descripción"));
    cad=Est->Descripcion;
    if(cad==wxT(""))
    {
      cad=wxT("No hay descripción disponible");
    }
    parrafo(faux,cad);
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
  }
// PROPIEDADES

  if(seleccion(wxT("Metodología"),wxT("Propiedades"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Propiedades Generales"));
    tam=Est->Generalidades.tamano();
    if(tam>0)
    {
      cad=wxT("Las siguientes son las propiedades generales de la Metodología:");
      parrafo(faux,cad);
      lista(faux,Est->Generalidades.listaNombres(),Est->Generalidades.listaValores());
    }else
    {
      cad=wxT("No hay Propiedades Generales definidas en la Metodología");
      parrafo(faux,cad);

     }
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
  }
// NODOS DEL ARBOL
  if(seleccion(wxT("Metodología"),wxT("Nodos"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Nodos de Cálculo"));

    ListaNodos Nodos;
    Est->Grafo.llenarArreglo(&Nodos);
    wxArrayString nom,desc,dest;
    tam=Nodos.GetCount();
    for(i=0;i<tam;i++)
    {
      wxString dir=cadenaNivelActual();
      dir.Replace(wxT("."),wxT("_"));
      nom.Add(Nodos.Item(i).VarCalculada.Nombre+wxT(" - ")+Nodos.Item(i).NombreExtendido);
      desc.Add(Nodos.Item(i).Descripcion);
      dir << (i+1) << wxT("_");
      dest.Add(dir);
    }
    if(seleccion(wxT("Metodología"),wxT("Lista de Nodos"))==0)
    {
      cad=wxT("Los siguientes son los Nodos de Cálculo definidos en la Metodología:");
      parrafo(faux,cad);
      listaEnlaceExterno(faux,nom,desc,dest);
    }
    tam=Nodos.GetCount();
    abreNivel();
    for(i=0;i<tam;i++)

    {
      // deben crearse los archivos de cada nodo...
      NodoCalculo *Nod;
      Nod=&Nodos.Item(i);

      wxString cade;
      wxTextFile *fe;
      cade=cadenaNivelSiguiente();
      cade.Replace(wxT("."),wxT("_"));
      fe=crearArchivo(cade);
      abrirArchivo(fe);
      seccion(fe,Nod->VarCalculada.Nombre+wxT(" - ")+Nodos.Item(i).NombreExtendido);
    // contenido

      escribirNodo(fe,Nod,&Nodos);

    // cerrando
      cerrarArchivo(fe);
      incluirArchivo(faux,cade);
      delete fe;
    }
    cierraNivel();
    tam=Nodos.GetCount();
    for(i=0;i<tam;i++)
    {
      Nodos.Detach(0);
    }
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
  }
///////////// Fin Estrategia
  cierraNivel();
}


void Reporte::escribirCaso(wxTextFile *f, Caso *Cas,Proyecto *Proy)
{
  abreNivel();
  wxString cad,cadaux;
  wxTextFile *faux;
  int i,tam;

// DESCRIPCION

  if(seleccion(wxT("Caso"),wxT("Descripción"))==0)
  {
    cadaux=cadenaNivelSiguiente();

    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Descripción"));
    cad=Cas->Descripcion;
    if(cad==wxT(""))
    {
      cad=wxT("No hay descripción disponible");
    }
    parrafo(faux,cad);
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);

    delete faux;
  }
// PROPIEDADES

  if(seleccion(wxT("Caso"),wxT("Descripción"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Propiedades Generales"));
    tam=Cas->Generalidades.tamano();
    if(tam>0)
    {
      cad=wxT("Las siguientes son las propiedades generales del Caso:");
      parrafo(faux,cad);
      lista(faux,Cas->Generalidades.listaNombres(),Cas->Generalidades.listaValores());
    }else
    {
      cad=wxT("No hay Propiedades Generales definidas en el Caso");

      parrafo(faux,cad);
     }
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
  }
///////////// ENTRADAS
  if(seleccion(wxT("Caso"),wxT("Variables de Entrada"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Variables de Entrada"));
    tam=Cas->Variables.GetCount();
    if(tam>0)
    {
      abreNivel();
      for(i=0;i<tam;i++)

      {
        VariableLinguistica *Var;
        Var=&Cas->Variables.Item(i);
        NumeroDifuso *Num;
        Num=Var->valor();
        wxString cade;
        wxTextFile *fe;
        cade=cadenaNivelSiguiente();
        cade.Replace(wxT("."),wxT("_"));
        fe=crearArchivo(cade);
        abrirArchivo(fe);
	wxString cccad=wxT("");
	int iii,tttam;
	tttam=(Proy->Estrategias.GetCount());
	for(iii=0;iii<tttam;iii++)
	{
	  NodoCalculo *NNN;
	  NNN=Proy->Estrategias.Item(iii).Grafo.buscarNodo(Var->Nombre);
	  if(NNN!=NULL)
	  {
	    cccad=NNN->NombreExtendido;
	    iii=tttam;
	  }
	}
        seccion(fe,Var->Nombre+wxT(" - ")+cccad);
        escribirNumero(fe,Num,Var,Proy->Optimismo,Proy->Representatividad,Cas,0);
        cerrarArchivo(fe);
        incluirArchivo(faux,cade);
        delete fe;


      }
      cierraNivel();
    }else
    {
      cad=wxT("No hay Variables de Entrada definidas en el Caso");
      parrafo(faux,cad);
     }
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
  }

///////////// SALIDAS

  if(seleccion(wxT("Caso"),wxT("Variables Calculadas"))==0)
  {
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(faux,wxT("Variables Calculadas"));

    abreNivel();
    tam=Proy->Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      Estrategia *Est;
      Est=&Proy->Estrategias.Item(i);
      wxString cadest;
      wxTextFile *fest;

      cadest=cadenaNivelSiguiente();
      cadest.Replace(wxT("."),wxT("_"));
      fest=crearArchivo(cadest);
      abrirArchivo(fest);
      seccion(faux,Est->Nombre);
      abreNivel();
      ListaNodos Nodos;
      Est->Grafo.llenarArreglo(&Nodos);
      int j,tam2;
      tam2=Nodos.GetCount();
      for(j=0;j<tam2;j++)
      {
        NodoCalculo *Nod;
        Nod=&Nodos.Item(0);
        if((Nod->FormaDeCalculo!=0))  // y se es entrada del caso ?????
        {
          NumeroDifuso *Num;
          Num=Nod->calcularCaso(Cas);

          VariableLinguistica *Var;
          Var=&Nod->VarCalculada;
          wxString cade;
          wxTextFile *fe;
          cade=cadenaNivelSiguiente();
          cade.Replace(wxT("."),wxT("_"));
          fe=crearArchivo(cade);
          abrirArchivo(fe);
          seccion(fe,Var->Nombre+wxT(" - ")+Nod->NombreExtendido);
          escribirNumero(fe,Num,Var,Proy->Optimismo,Proy->Representatividad,Cas,0);
          cerrarArchivo(fe);
          incluirArchivo(fest,cade);
          delete fe;
        }
        Nodos.Detach(0);
      }
      cerrarArchivo(fest);
      incluirArchivo(faux,cadest);
      delete fest;
      cierraNivel();
    }
    cierraNivel();


    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
  }
  cierraNivel();
}

void Reporte::escribirNodo(wxTextFile *f,NodoCalculo *Nod,ListaNodos *Nodos)
{
  wxString cad;
  abreNivel();
//// Descripción
  if(seleccion(wxT("Nodos"),wxT("Descripción"))==0)
  {
    seccion(f,wxT("Descripción"));
    cad=Nod->Descripcion;
    if(cad==wxT(""))
    {
      cad=wxT("No hay descripción disponible");
    }
    parrafo(f,cad);

    if(Nod->FormaDeCalculo==2)
    {
      cad=wxT("ATENCIÓN: Este nodo es un enlace con la Metodologia ");
      cad << Nod->EstrategiaCalculo;
      parrafo(f,cad);
    }
  }

//// VarCalculada

  if(seleccion(wxT("Nodos"),wxT("Semántica"))==0)
  {
    seccion(f,wxT("Contenido semántico"));
    escribirVariable(f,&Nod->VarCalculada);
  }
//// NodosDeCalculo
  int i,tam;

  if(seleccion(wxT("Nodos"),wxT("Nodos Hijos"))==0)
  {
    seccion(f,wxT("Nodos Hijos"));
    tam=Nod->NodosDeCalculo.GetCount();
    if(tam>0)
    {

       wxArrayString nom,desc,dest;
       for(i=0;i<tam;i++)
       {
         nom.Add(Nod->NodosDeCalculo.Item(i).VarCalculada.Nombre+wxT(" - ")+Nod->NodosDeCalculo.Item(i).NombreExtendido);
         desc.Add(Nod->NodosDeCalculo.Item(i).Descripcion);
         wxString destino;
         destino=cadenaNivelActual();
         destino=destino.BeforeLast('.');
         destino=destino.BeforeLast('.');
         destino=destino.BeforeLast('.');
         destino << '.';
         int j,tam2;
         tam2=Nodos->GetCount();
         for(j=0;j<tam2;j++)
         {

           if(Nod->NodosDeCalculo.Item(i).VarCalculada.Nombre==Nodos->Item(j).VarCalculada.Nombre)
           {
             destino << (j+1) << wxT(".");
             j=tam2;
           }
         }
         destino.Replace(wxT("."),wxT("_"));
         dest.Add(destino);
       }
     cad=wxT("Para el cálculo de ");
     cad << Nod->VarCalculada.Nombre << wxT(" se emplea información proveniente de los siguientes nodos:");
     parrafo(f,cad);
     listaEnlaceExterno(f,nom,desc,dest);
     if(seleccion(wxT("Nodos"),wxT("Función"))==0)
     {
        seccion(f,wxT("Función de cálculo"));
        if(Nod->FormaDeCalculo==1)
        {
          escribirFuncion(f,Nod->FuncionCalculo);
          escribirParametrosFuncion(f,Nod->FuncionCalculo,Nod);
        }else
        {
          cad=wxT("El Nodo ");
          cad << Nod->VarCalculada.Nombre << wxT(" es Forzado como nodo de entrada.");
          parrafo(f,cad);
        }
       }
     }else
     {
        cad=wxT("El Nodo ");
        cad << Nod->VarCalculada.Nombre << wxT(" es un nodo de entrada. No tiene Nodos Hijos");
        parrafo(f,cad);
     }
    }

//// NodosPadre
  if(seleccion(wxT("Nodos"),wxT("Nodos Padre"))==0)
  {
    tam=Nod->NodosPadre.GetCount();
    if(tam>0)
    {
       seccion(f,wxT("Nodos Padre"));

       wxArrayString nom,desc,dest;

       for(i=0;i<tam;i++)
       {
         nom.Add(Nod->NodosPadre.Item(i).VarCalculada.Nombre);
         desc.Add(Nod->NodosPadre.Item(i).Descripcion);
         wxString destino;
         destino=cadenaNivelActual();
         destino=destino.BeforeLast('.');
         destino=destino.BeforeLast('.');
         destino=destino.BeforeLast('.');
         destino << '.';
         int j,tam2;
         tam2=Nodos->GetCount();
         for(j=0;j<tam2;j++)
         {
           if(Nod->NodosPadre.Item(i).VarCalculada.Nombre==Nodos->Item(j).VarCalculada.Nombre)
           {
             destino << (j+1) << wxT(".");
             j=tam2;
           }
         }
         destino.Replace(wxT("."),wxT("_"));
         dest.Add(destino);
       }
       cad=wxT("La información calculada en ");
       cad << Nod->VarCalculada.Nombre << wxT(" se emplea en el cálculo de los siguientes nodos:");
       parrafo(f,cad);
       listaEnlaceExterno(f,nom,desc,dest);
    }
  }

//////////////////////
  cierraNivel();
}

void Reporte::escribirVariable(wxTextFile *f,VariableLinguistica *Var)
{
   wxString linea=wxT("");

// Párrafo resumen

  linea << wxT("La variable ") << Var->Nombre;
  linea << wxT(" est definida sobre el intervalo [ ") << Var->Minimo << wxT(" , ") << Var->Maximo << wxT(" ]; ");
  linea << wxT(" tiene ") << Var->Etiquetas.GetCount() << wxT(" etiquetas");
  if(seleccion(wxT("Variables"),wxT("Tabla de Semántica"))==0)
  {
    linea << wxT(" caracterizadas en la ") << enlaceTabla(ContadorTablas+1);
  }
  bool bandera=figuraVariable(Var);
  if(seleccion(wxT("Variables"),wxT("Figura de Semántica"))!=0)
  {
    bandera=FALSE;
  }
  if(bandera)
  {
    linea << wxT(" y en la ") << enlaceFigura(ContadorFiguras);
  }
  if(seleccion(wxT("Variables"),wxT("Valor por Defecto"))==0)
  {
    linea << wxT(". El valor asignado por defecto es: ") << Var->strEntrada();
    switch(Var->TipoDeValor)
    {
      case 0: break;
      case 1: linea << wxT("(Número Crisp)") ;break;
      case 2: linea << wxT("(Intervalo)") ;break;
      case 3: linea << wxT("(Nímero Difuso)") ;break;
      case 4: linea << wxT("Etiqueta") ;break;
      default: break;
    }
    parrafo(f,linea);
  }
// Tabla de las etiquetas
  wxString cad;
  if(seleccion(wxT("Variables"),wxT("Tabla de Semántica"))==0)
  {
    int i,tam;
    tam=Var->Etiquetas.GetCount();
    wxArrayString *lista;
    lista = new wxArrayString[tam+1];
    lista[0].Add(wxT(" "));
    lista[0].Add(wxT("Etiquetas"));
    lista[0].Add(wxT("Valor"));
    lista[0].Add(wxT("Ambigüedad"));
    switch(seleccion(wxT("Variables"),wxT("Soporte")))
    {
      default:
      case 0:break;
      case 1:lista[0].Add(wxT("Soporte"));break;
    }
    switch(seleccion(wxT("Variables"),wxT("Núcleo")))
    {
      default:
      case 0:break;
      case 1:lista[0].Add(wxT("Núcleo"));break;
    }
    for(i=0;i<tam;i++)
    {
      NumeroDifuso *N;
      N=Var->Etiquetas.Item(i).ND;
      cad =wxT(""); cad << i+1;
      lista[i+1].Add(cad);
      lista[i+1].Add(Var->Etiquetas.Item(i).Label);
      cad =wxT(""); cad << N->valorRepresentativo(0.5,1.0);
      lista[i+1].Add(cad);
      cad =wxT(""); cad << N->ambiguedad();
      lista[i+1].Add(cad);
      switch(seleccion(wxT("Variables"),wxT("Soporte")))
      {
        default:
        case 0:break;
        case 1:
               cad =wxT("["); cad << N->d(0.0,1) << wxT(" , ") << N->d(0.0,-1) << wxT(" ]");
               lista[i+1].Add(cad);
               break;
      }
      switch(seleccion(wxT("Variables"),wxT("Núcleo")))
      {
        default:
        case 0:break;
        case 1:
               cad =wxT("["); cad << N->d(1.0,1) << wxT(" , ") << N->d(1.0,-1) << wxT(" ]");
               lista[i+1].Add(cad);
               break;
      }
    }
    cad = wxT("Etiquetas de la Variable Lingüística ");
    cad << Var->Nombre;
    tabla(f,lista,tam + 1,cad);
  }
  if(bandera )
  {
    if(seleccion(wxT("Variables"),wxT("Valor por Defecto"))==0)
    {
      cad << wxT(". En rojo el valor por defecto");
    }
    incluirFigura(f,cad);
  }
}

void Reporte::escribirFuncion(wxTextFile *f,Funcion *F)
{
  wxString cad;
  cad = F->descripcion();
  parrafo(f,cad);
}

void Reporte::escribirParametrosFuncion(wxTextFile *f,Funcion *F,NodoCalculo *Nod)
{
  wxString cadT;
  int i,tam;
  tam=F->NombreParametrosFijos.GetCount();
  wxArrayString *listaF;
  listaF=new wxArrayString[tam+1];

  int j,tam2;
  tam2=F->Orden;
  wxArrayString *listaV;
  listaV=new wxArrayString[tam2+1];

  if(tam>0)
  {
    cadT =wxT("");
    cadT << wxT("Los parámetros fijos de la función se muestran en la ") << enlaceTabla(ContadorTablas+1) << wxT(" .");
    wxString cad=wxT("");
    cad=wxT("Parámetro");
    listaF[0].Add(cad);
    cad=wxT("Valor");
    listaF[0].Add(cad);
    for(i=0;i<tam;i++)
    {
      cad=F->NombreParametrosFijos.Item(i);
      listaF[i+1].Add(cad);
      cad=wxT("");
      cad << F->ParametrosFijos[i];
      listaF[i+1].Add(cad);
    }
  }

  int tam3=F->NombreParametrosVariables.GetCount();
  if(tam3>0)
  {
    cadT << wxT(" Los parámetros variables de la función se muestran en la ") << enlaceTabla(ContadorTablas+2) << wxT(" .");
    wxString cad=wxT("");
    cad=wxT("Nodo");
    listaV[0].Add(cad);
    for(i=0;i<tam3;i++)
    {
      cad=F->NombreParametrosVariables.Item(i);
      listaV[0].Add(cad);
    }
    for(j=0;j<tam2;j++)
    {
      cad=Nod->NodosDeCalculo.Item(j).VarCalculada.Nombre;
      listaV[j+1].Add(cad);
      for(i=0;i<tam3;i++)
      {
        cad=wxT("");
        cad << F->ParametrosVariables[j][i];
        listaV[j+1].Add(cad);
      }
    }
  }

  f->AddLine(cadT);
  if(tam>0)
  {
   cadT = wxT("Tabla de Parámetros Fijos de ");
   cadT << Nod->VarCalculada.Nombre;
   tabla(f,listaF,tam+1,cadT);
  }
  if(tam3>0)
  {
    cadT = wxT("Tabla de Parámetros Variables de ");
    cadT << Nod->VarCalculada.Nombre;
    tabla(f,listaV,tam2+1,cadT);
  }
}

void Reporte::escribirNumero(wxTextFile *f, NumeroDifuso *Num, VariableLinguistica *Var,float opt, float rep,Caso *Cas,int entrada)
{
  wxString linea,cad;
  if(entrada)
  {

    linea =wxT("La variable ");
    linea << Var->Nombre << wxT(" es una entrada del tipo ");
    switch(Var->TipoDeValor)
    {
      case 0 : linea << wxT("Indefinido");break;
      case 1 : linea << wxT("Número Crisp");break;
      case 2 : linea << wxT("Intervalo");break;
      case 3 : linea << wxT("Número Difuso");break;
      case 4 : linea << wxT("Etiqueta Lingüística");break;
    }
    linea << wxT(" para el caso ");
    linea << Cas->Nombre << wxT(", que se caracteriza asi:");
    parrafo(f, linea);
  }else
  {
    linea =wxT("La variable ");
    linea << Var->Nombre << wxT(" ha sido calculada para el caso ");
    linea << Cas->Nombre << wxT(", y el resultado se caracteriza asi:");
    parrafo(f, linea);
  }
  wxArrayString Carac, Valor;
  if(seleccion(wxT("Valor de Variable"),wxT("Valor Representativo"))==0)
  {
    Carac.Add(wxT("Valor Representativo"));
    cad =wxT(""); cad << Num->valorRepresentativo(opt,rep);
    Valor.Add(cad);
  }
  if(seleccion(wxT("Valor de Variable"),wxT("Ambigüedad"))==0)
  {
   Carac.Add(wxT("Ambigüedad"));
   cad =wxT(""); cad << Num->ambiguedad();
   Valor.Add(cad);
  }
  if(seleccion(wxT("Valor de Variable"),wxT("Interpretación Corta"))==0)
  {
    Carac.Add(wxT("Interpretación Corta"));
    cad =wxT(""); Var->interpretacionMaxima(&cad,Num);
    Valor.Add(cad);
  }
  if(seleccion(wxT("Valor de Variable"),wxT("Interpretación Larga"))==0)
  {
    Carac.Add(wxT("Interpretación Larga"));
    cad =wxT("");
    wxArrayString larga;
    Var->interpretacion(&larga,Num);
    int i,tam;
    tam=larga.GetCount();
    for(i=0;i<tam;i++)

    {
      cad << larga.Item(i) << wxT("; ");
    }
    cad.BeforeLast(';');
    Valor.Add(cad);
  }
  lista(f,Carac,Valor);
  bool bandera=figuraVariable(Var,Num,entrada);
  if(seleccion(wxT("Valor de Variable"),wxT("Figura"))!=0)
  {
    bandera=FALSE;
  }
  if(bandera)
  {
    linea=wxT("");
    linea << wxT(" La ") << enlaceFigura(ContadorFiguras) << wxT(" muestra el resultado, y la variable lingüística respecto a la cual se ha interpretado.");
    parrafo(f,linea);
    cad = wxT("Etiquetas de la Variable Lingüística ");
    cad << Var->Nombre;
      if(entrada)
      {
        cad << wxT(". En rojo el valor de entrada para el caso ");
      }else
      {
        cad << wxT(". En rojo el valor calculado para el caso ");
      }
      cad << Cas->Nombre;
    incluirFigura(f,cad);
  }
}

void Reporte::escribirResultados(wxTextFile *f, Proyecto *Proy)
{

  abreNivel();

// Un análisis por estrategias...

  int i,tam;
  tam=Proy->Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
// para cada estrategia se hace:

    Estrategia *Est;
    Est = &Proy->Estrategias.Item(i);

    wxString cadaux;
    wxTextFile *faux;

    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(f,Est->Nombre);

    abreNivel();

// 1) Interpretación corta
//     Para cada nodo de la estrategia se hace una tabla de interpretación corta:
//       Filas: Los Casos
//       Cols: Las etiquetas de VarCalculada
//       En cada celda se marca la Interpretación máxima del caso (una X)
    wxString cadaux2;
    wxTextFile *faux2;
    if(seleccion(wxT("Resultados"),wxT("Interpretaciones Cortas"))==0)
    {
      cadaux2=cadenaNivelSiguiente();
      cadaux2.Replace(wxT("."),wxT("_"));
      faux2=crearArchivo(cadaux2);
      abrirArchivo(faux2);
      seccion(faux2,wxT("Interpretaciones Corta"));
      escribirResultadosInterpretacionCorta(faux2,Proy,Est);
      Estrategia *Est;
      Est = &Proy->Estrategias.Item(i);
      cerrarArchivo(faux2);

      incluirArchivo(faux,cadaux2);
      delete faux2;
    }
// 2) Interpretación corta ordenada
//     Para cada nodo de la estrategia se hace una tabla de interpretación corta:
//       Filas: Los Casos, ordenando por etiquetas...
//       Cols: Las etiquetas de VarCalculada
//       En cada celda se marca la Interpretación máxima del caso (una X)

    if(seleccion(wxT("Resultados"),wxT("Interpretaciones Cortas Ordenadas"))==0)
    {
      cadaux2=cadenaNivelSiguiente();
      cadaux2.Replace(wxT("."),wxT("_"));
      faux2=crearArchivo(cadaux2);
      abrirArchivo(faux2);
      seccion(faux2,wxT("Interpretaciones Cortas Ordenadas"));
      escribirResultadosInterpretacionOrdenada(faux2,Proy,Est);
      cerrarArchivo(faux2);
      incluirArchivo(faux,cadaux2);
      delete faux2;
    }
// 3) Interpretación Lingüìstica
//     Para cada nodo de la estrategia se hace una tabla de interpretación:
//       Filas: Los Casos
//       Cols: Las etiquetas de VarCalculada
//       En cada celda se escribe la consistencia del caso com la etiqueta

    if(seleccion(wxT("Resultados"),wxT("Interpretaciones Largas"))==0)
    {
      cadaux2=cadenaNivelSiguiente();
      cadaux2.Replace(wxT("."),wxT("_"));
      faux2=crearArchivo(cadaux2);
      abrirArchivo(faux2);
      seccion(faux2,wxT("Interpretaciones Largas"));
      escribirResultadosInterpretacionLarga(faux2,Proy,Est);
      cerrarArchivo(faux2);
      incluirArchivo(faux,cadaux2);
      delete faux2;
    }
// 4) Análisis de Sensibilidad, usando el optimismo
//     Para cada nodo de la red se hace una tabla:
//       Filas: Los casos
//       Cols: 0, .1, ...., 1.0 ( el optimismo) y una figura pequeña??
//               siempre estará la columna del valor actual de Optimismo,
//               destacado de alguna manera (color, negrita?)
//       En cada caso se escribe el valor representativo

    if(seleccion(wxT("Resultados"),wxT("Sensibilidad al Optimismo"))==0)
    {
      cadaux2=cadenaNivelSiguiente();
      cadaux2.Replace(wxT("."),wxT("_"));
      faux2=crearArchivo(cadaux2);
      abrirArchivo(faux2);
      seccion(faux2,wxT("Análisis de Sensibilidad al Optimismo"));

      escribirResultadosInterpretacionSensibilidad(faux2,Proy,Est);
      cerrarArchivo(faux2);
      incluirArchivo(faux,cadaux2);
      delete faux2;
    }
     cierraNivel();

    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;

  }
  cierraNivel();
}

void Reporte::escribirResultadosInterpretacionCorta(wxTextFile *f, Proyecto *Proy, Estrategia *Est)
{
  abreNivel();

  ListaNodos Nodos;

  Est->Grafo.llenarArreglo(&Nodos);

  int i,tam;
  tam=Nodos.GetCount();
  for(i=0;i<tam;i++)
  {
    NodoCalculo *Nod;
    Nod=&Nodos.Item(0);

    wxString cadaux;
    wxTextFile *faux;
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(f,Nod->VarCalculada.Nombre+wxT(" - ")+Nod->NombreExtendido);


    wxArrayString *Tabla;
    int j,m,tam2,tam3;
    tam2=Proy->Casos.GetCount();
    Tabla=new wxArrayString[tam2+1];
    Tabla[0].Add(wxT("Caso"));
    tam3=Nod->VarCalculada.Etiquetas.GetCount();
    for(m=0;m<tam3;m++)
    {
      Tabla[0].Add(Nod->VarCalculada.Etiquetas.Item(m).Label);
    }
    for(j=0;j<tam2;j++)
    {
      wxString etMax;
      NumeroDifuso *Num;
      Tabla[j+1].Add(Proy->Casos.Item(j).Nombre);
      Num=Nod->calcularCaso(&Proy->Casos.Item(j));
      Nod->VarCalculada.interpretacionMaxima(&etMax,Num);
      for(m=0;m<tam3;m++)
      {
        if(Nod->VarCalculada.Etiquetas.Item(m).Label == etMax)
        {
          Tabla[j+1].Add(wxT(" X "));
        }else
        {
          Tabla[j+1].Add(wxT(""));
        }
      }
      delete Num;
    }

    wxString linea=wxT("La ");
    linea << enlaceTabla(ContadorTablas+1)  << wxT(" muestra la interpretación lingüística corta del valor calculado en la variable ") ;
    linea << Nod->VarCalculada.Nombre << wxT(" en cada uno de los casos definidos en el proyecto");
    parrafo(faux,linea);
    wxString cad;
    cad = wxT("Tabla de Interpretaciones cortas para la variable ");
    cad << Nod->VarCalculada.Nombre;
    tabla(faux,Tabla,tam2+1,cad);
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
    Nodos.Detach(0);
  }
  cierraNivel();
}

void Reporte::escribirResultadosInterpretacionOrdenada(wxTextFile *f, Proyecto *Proy, Estrategia *Est)
{
  abreNivel();

  ListaNodos Nodos;


  Est->Grafo.llenarArreglo(&Nodos);

  int i,tam;
  tam=Nodos.GetCount();
  for(i=0;i<tam;i++)
  {
    NodoCalculo *Nod;
    Nod=&Nodos.Item(0);

    wxString cadaux;
    wxTextFile *faux;
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(f,Nod->VarCalculada.Nombre+wxT(" - ")+Nod->NombreExtendido);

    wxArrayString *Tabla,*TablaOrdenada;
    int j,m,tam2,tam3;
    tam2=Proy->Casos.GetCount();
    Tabla=new wxArrayString[tam2+1];
    TablaOrdenada=new wxArrayString[tam2+1];
    Tabla[0].Add(wxT("Caso"));
    tam3=Nod->VarCalculada.Etiquetas.GetCount();

    for(m=0;m<tam3;m++)
    {
      Tabla[0].Add(Nod->VarCalculada.Etiquetas.Item(m).Label);
    }
    for(j=0;j<tam2;j++)
    {
      wxString etMax;
      NumeroDifuso *Num;
      Tabla[j+1].Add(Proy->Casos.Item(j).Nombre);
      Num=Nod->calcularCaso(&Proy->Casos.Item(j));
      Nod->VarCalculada.interpretacionMaxima(&etMax,Num);
      for(m=0;m<tam3;m++)
      {
        if(Nod->VarCalculada.Etiquetas.Item(m).Label == etMax)
        {
          Tabla[j+1].Add(wxT(" X "));
        }else
        {
          Tabla[j+1].Add(wxT(""));
        }
      }

      delete Num;
    }
// ordenamiento de la tabla
    TablaOrdenada[0]=Tabla[0];
    int Contador=1;
    for(m=0;m<tam3;m++)
    {
      int k;
      for(k=0;k<tam2;k++)
      {
        if(Tabla[k+1].Item(m+1)==wxT(" X "))
        {
          TablaOrdenada[Contador]=Tabla[k+1];
          Contador++;
          if(Contador>tam2)
          {
            k=tam2;
            m=tam3;
          }
        }
      }
    }

// fin del ordenamiento
    wxString linea=wxT("La ");
    linea << enlaceTabla(ContadorTablas+1)  << wxT(" muestra la interpretación lingüística corta del valor calculado en la variable ") ;
    linea << Nod->VarCalculada.Nombre << wxT(" en cada uno de los casos definidos en el proyecto, ordenada por cada etiqueta");
    parrafo(faux,linea);
    wxString cad;
    cad = wxT("Tabla de Interpretaciones cortas ordenadas para la variable ");
    cad << Nod->VarCalculada.Nombre;
    tabla(faux,TablaOrdenada,tam2+1,cad);
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
    Nodos.Detach(0);
  }
  cierraNivel();
}

void Reporte::escribirResultadosInterpretacionLarga(wxTextFile *f, Proyecto *Proy, Estrategia *Est)
{
  abreNivel();

  ListaNodos Nodos;

  Est->Grafo.llenarArreglo(&Nodos);

  int i,tam;
  tam=Nodos.GetCount();
  for(i=0;i<tam;i++)
  {
    NodoCalculo *Nod;
    Nod=&Nodos.Item(0);

    wxString cadaux;
    wxTextFile *faux;
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));
    faux=crearArchivo(cadaux);

    abrirArchivo(faux);
    seccion(f,Nod->VarCalculada.Nombre+wxT(" - ")+Nod->NombreExtendido);

    wxArrayString *Tabla;
    int j,m,tam2,tam3;
    tam2=Proy->Casos.GetCount();
    Tabla=new wxArrayString[tam2+1];
    Tabla[0].Add(wxT("Caso"));
    tam3=Nod->VarCalculada.Etiquetas.GetCount();
    for(m=0;m<tam3;m++)
    {
      Tabla[0].Add(Nod->VarCalculada.Etiquetas.Item(m).Label);
    }
    for(j=0;j<tam2;j++)
    {
      wxString etMax;
      NumeroDifuso *Num;
      Tabla[j+1].Add(Proy->Casos.Item(j).Nombre);
      Num=Nod->calcularCaso(&Proy->Casos.Item(j));
      for(m=0;m<tam3;m++)
      {
        float cons;
        cons=Nod->VarCalculada.Etiquetas.Item(m).ND->consistencia(Num);
        if(cons > 0.0)
        {
          wxString celda;
          celda << cons;
          Tabla[j+1].Add(celda);
        }else
        {
          Tabla[j+1].Add(wxT(""));
        }
      }
      delete Num;
    }

    wxString linea=wxT("La ");
    linea << enlaceTabla(ContadorTablas+1)  << wxT(" muestra la consistencia entre el valor calculado en la variable ") ;
    linea << Nod->VarCalculada.Nombre << wxT(" y todas las etiquetas del Nodo, en cada uno de los casos definidos en el proyecto");
    parrafo(faux,linea);
    wxString cad;
    cad = wxT("Tabla de consistencias (Interpretaciones largas) para la variable ");
    cad << Nod->VarCalculada.Nombre;
    tabla(faux,Tabla,tam2+1,cad);
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
    Nodos.Detach(0);
  }
  cierraNivel();
}

void Reporte::escribirResultadosInterpretacionSensibilidad(wxTextFile *f, Proyecto *Proy, Estrategia *Est)
{
  abreNivel();

  ListaNodos Nodos;

  Est->Grafo.llenarArreglo(&Nodos);

  int i,tam;
  tam=Nodos.GetCount();
  for(i=0;i<tam;i++)
  {
    NodoCalculo *Nod;
    Nod=&Nodos.Item(0);

    wxString cadaux;
    wxTextFile *faux;
    cadaux=cadenaNivelSiguiente();
    cadaux.Replace(wxT("."),wxT("_"));

    faux=crearArchivo(cadaux);
    abrirArchivo(faux);
    seccion(f,Nod->VarCalculada.Nombre+wxT(" - ")+Nod->NombreExtendido);

    wxArrayString *Tabla;
    int j,m,tam2,tam3;
    tam2=Proy->Casos.GetCount();
    Tabla=new wxArrayString[tam2+1];
    Tabla[0].Add(wxT("Caso"));
    float opt[15];
    tam3=0;
    int bandera=0;
    for(int o=0;o<5;o++)
    {
      opt[o+bandera]=0.25*(float)o;
      tam3++;
      if ((0.25*o < Proy->Optimismo)  && (Proy->Optimismo < 0.25*(o+1)))
      {
        tam3++;
        opt[o+bandera+1]=Proy->Optimismo;
        bandera=1;
      }
    }
    for(m=0;m<tam3;m++)
    {
      wxString celda;
      celda << opt[m]*100.0;
      Tabla[0].Add(celda);
    }
    for(j=0;j<tam2;j++)
    {
      NumeroDifuso *Num;
      Num=Nod->calcularCaso(&Proy->Casos.Item(j));
      Tabla[j+1].Add(Proy->Casos.Item(j).Nombre);
      for(m=0;m<tam3;m++)
      {
        float vr;
        vr=Num->valorRepresentativo(opt[m],Proy->Representatividad);
        wxString celda;
        celda << vr;
        Tabla[j+1].Add(celda);
      }
      delete Num;
    }


    wxString linea=wxT("La ");
    linea << enlaceTabla(ContadorTablas+1)  << wxT(" muestra la variación del valor representativo calculado en la variable ") ;
    linea << Nod->VarCalculada.Nombre << wxT(" en función del optimismo del decisor, en cada uno de los casos definidos en el proyecto");
    parrafo(faux,linea);
    wxString cad;
    cad = wxT("Tabla de Análisis de Sensibilidad para la variable ");
    cad << Nod->VarCalculada.Nombre;
    tabla(faux,Tabla,tam2+1,cad);
    cerrarArchivo(faux);
    incluirArchivo(f,cadaux);
    delete faux;
    Nodos.Detach(0);
  }
  cierraNivel();
}

/**
 * Llena el Listado de Selecciones
 */
void Reporte::definirSelecciones()
{
  Selecciones.Clear();
  ListaSelecciones *Sel;
  NombreSelecciones.Clear();
//// Proyecto
  NombreSelecciones.Add(wxT("Proyecto"));
  Sel=new ListaSelecciones;

  Selecciones.Add(Sel);
  wxArrayString arr;
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Presentación"),wxArrayString(arr),0);
  arr.Clear();


  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Descripción"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Propiedades"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Metodologías"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Casos"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Resultados"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("1"));arr.Add(wxT("2"));arr.Add(wxT("3"));arr.Add(wxT("4"));arr.Add(wxT("5"));
  Sel->adicionarSeleccion(wxT("Profundidad Tabla de Contenido"),wxArrayString(arr),3);
//// Estrategia
  NombreSelecciones.Add(wxT("Metodología"));
  Sel=new ListaSelecciones;
  Selecciones.Add(Sel);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Descripción"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Propiedades"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Lista de Nodos"),wxArrayString(arr),1);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Nodos"),wxArrayString(arr),0);
//// Nodos
  NombreSelecciones.Add(wxT("Nodos"));
  Sel=new ListaSelecciones;

  Selecciones.Add(Sel);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Descripción"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Semántica"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Nodos Hijos"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Función"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Nodos Padre"),wxArrayString(arr),0);
//// Variables Lingüísticas
  NombreSelecciones.Add(wxT("Variables"));
  Sel=new ListaSelecciones;
  Selecciones.Add(Sel);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Tabla de Semántica"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Figura de Semántica"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Valor por Defecto"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("PNG"));arr.Add(wxT("JPEG"));arr.Add(wxT("BMP"));
  Sel->adicionarSeleccion(wxT("Formato de Figuras HTML"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Pstricks"));arr.Add(wxT("Pdftricks"));
  Sel->adicionarSeleccion(wxT("Formato de Figuras Latex"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Nombre"));arr.Add(wxT("Número"));
  Sel->adicionarSeleccion(wxT("Etiqueta en Figuras"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Soporte de Etiquetas"),wxArrayString(arr),1);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Núcleo de Etiquetas"),wxArrayString(arr),1);
//// Caso
  NombreSelecciones.Add(wxT("Caso"));
  Sel=new ListaSelecciones;
  Selecciones.Add(Sel);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Descripción"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Propiedades"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Variables de Entrada"),wxArrayString(arr),0);
  arr.Clear();

  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Variables Calculadas"),wxArrayString(arr),0);
//// Número
  NombreSelecciones.Add(wxT("Valor de Variable"));
  Sel=new ListaSelecciones;
  Selecciones.Add(Sel);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Valor Representativo"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Ambigüedad"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Interpretación Corta"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Interpretación Larga"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Figura de Semántica"),wxArrayString(arr),0);
//// Resultados
  NombreSelecciones.Add(wxT("Resultados"));
  Sel=new ListaSelecciones;
  Selecciones.Add(Sel);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Interpretaciones Cortas"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Interpretaciones Cortas Ordenadas"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Interpretaciones Largas"),wxArrayString(arr),0);
  arr.Clear();
  arr.Add(wxT("Si"));arr.Add(wxT("No"));
  Sel->adicionarSeleccion(wxT("Sensibilidad al Optimismo"),wxArrayString(arr),0);
}

void Reporte::writeConfigura()
{

  wxConfig *Configura;
  switch(ESPECIFICO)
  {
    case 0:Configura = new wxConfig(wxT("fuzzynet"));break;
    case 1:Configura = new wxConfig(wxT("ediav"));break;
    case 5:Configura = new wxConfig(wxT("eviave"));break;
    default:Configura = new wxConfig(wxT("fuzzynet"));break;
  }
  Configura->SetPath(wxT("/Reporte"));
  int i,tam;
  tam=Selecciones.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString path=wxT("/Reporte");
    path << NombreSelecciones.Item(i);
    Configura->SetPath(path);
    int j,tam2;
    tam2=Selecciones.Item(i).Selecciones.GetCount();
    for(j=0;j<tam2;j++)
    {
      wxString nom;
      nom=Selecciones.Item(i).Nombres.Item(j);nom << wxT("_Sel");
      int dim=Selecciones.Item(i).Selecciones.Item(j);
      Configura->Write(nom,dim);
    }
  }
  delete Configura;
}

void Reporte::readConfigura()
{
  wxConfig *Configura;
  switch(ESPECIFICO)
  {
    case 0:Configura = new wxConfig(wxT("fuzzynet"));break;
    case 1:Configura = new wxConfig(wxT("ediav"));break;
    case 5:Configura = new wxConfig(wxT("eviave"));break;
    default:Configura = new wxConfig(wxT("fuzzynet"));break;
  }
  int i,tam;
  Configura->SetPath(wxT("/Reporte"));
  tam=Selecciones.GetCount();
  for(i=0;i<tam;i++)
  {
    wxString path=wxT("/Reporte");
    path << NombreSelecciones.Item(i);
    Configura->SetPath(path);
    int j,tam2;
    tam2=Selecciones.Item(i).Selecciones.GetCount();
    for(j=0;j<tam2;j++)
    {
      wxString nom;
      int dim;
      nom=Selecciones.Item(i).Nombres.Item(j);nom << wxT("_Sel");
      if(Configura->Read(nom,&dim))

      {
        Selecciones.Item(i).Selecciones.Item(j)=dim;
      }
    }
  }
  delete Configura;
}

int Reporte::seleccion(wxString Bloque, wxString Nombre)
{
  int sel,opcion=-1;
  sel=NombreSelecciones.Index(Bloque);
  if((sel != wxNOT_FOUND) & (sel < Selecciones.GetCount()))
  {
    opcion=Selecciones.Item(sel).Seleccion(Nombre);
  }


  return opcion;
}

void Reporte::avance()
{
  Progreso++;
  if(Progreso>ProgresoTotal)
  {
    Progreso=ProgresoTotal;
  }
  int av;
  if(ProgresoTotal==0)
  {
    av=100;
  }else
  {
    av=(int)((Progreso*100.0)/ProgresoTotal);
  }
  if(GaugeAvance!=NULL)
  {
    GaugeAvance->SetValue(av);

    GaugeAvance->Refresh();
  }
}

int Reporte::calcularProgresoTotalProyecto(Proyecto *Proy)
{
  int prg=0;
  if(seleccion(wxT("Proyecto"),wxT("Presentación"))==0)
  {
    prg++;
   if(seleccion(wxT("Proyecto"),wxT("Descripción"))==0)
   {
     prg++;
   }
   if(seleccion(wxT("Proyecto"),wxT("Propiedades"))==0)
   {
     prg++;
   }

   if(seleccion(wxT("Proyecto"),wxT("Metodologías"))==0)
   {
     prg+=Proy->Estrategias.GetCount();
   }
   if(seleccion(wxT("Proyecto"),wxT("Casos"))==0)
   {
     prg+=Proy->Casos.GetCount();
   }
  }
  if(seleccion(wxT("Proyecto"),wxT("Metodologías"))==0)
  {
    prg++;
    int i,tam;
    tam=Proy->Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      prg++;
      prg+=calcularProgresoTotalEstrategia(&Proy->Estrategias.Item(i));
    }
  }
  if(seleccion(wxT("Proyecto"),wxT("Casos"))==0)
  {
    prg++;
    int i,tam;
    tam=Proy->Casos.GetCount();
    for(i=0;i<tam;i++)
    {
      prg++;
      prg+=calcularProgresoTotalCaso(&Proy->Casos.Item(i),Proy);
    }
  }
  if(seleccion(wxT("Proyecto"),wxT("Resultados"))==0)
  {
    prg++;
    prg+=calcularProgresoTotalResultados(Proy);
  }
  return prg;
}

int Reporte::calcularProgresoTotalEstrategia(Estrategia *Est)
{
  int prg=0;
  if(seleccion(wxT("Metodología"),wxT("Descripción"))==0)
  {
    prg++;
  }
  if(seleccion(wxT("Metodología"),wxT("Propiedades"))==0)
  {
    prg++;
  }
  if(seleccion(wxT("Metodología"),wxT("Nodos"))==0)
  {
    prg++;
    int i,tam;
    ListaNodos Nodos;
    Est->Grafo.llenarArreglo(&Nodos);
    tam=Nodos.GetCount();
    for(i=0;i<tam;i++)
    {
      Nodos.Detach(0);
    }
    if(seleccion(wxT("Nodos"),wxT("Descripción"))==0)

    {
      prg+=tam;
    }

    if(seleccion(wxT("Nodos"),wxT("Semántica"))==0)
    {
      prg+=tam;
    }
    if(seleccion(wxT("Nodos"),wxT("Nodos Hijos"))==0)
    {
      prg+=tam;
    }
    if(seleccion(wxT("Nodos"),wxT("Función"))==0)
    {
      prg+=tam;
    }
    if(seleccion(wxT("Nodos"),wxT("Nodos Padre"))==0)
    {
      prg+=tam;

    }
  }
  return prg;
}

int Reporte::calcularProgresoTotalTodosEstrategia(Proyecto *Proy)
{
  int prg=0;
  int i,tam;
  tam=Proy->Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    prg+=calcularProgresoTotalEstrategia(&Proy->Estrategias.Item(i));
  }
  return prg;
}

int Reporte::calcularProgresoTotalCaso(Caso *Cas,Proyecto *Proy)
{
  int prg=0;

  if(seleccion(wxT("Caso"),wxT("Descripción"))==0)
  {
    prg++;
  }
  if(seleccion(wxT("Caso"),wxT("Propiedades"))==0)
  {
    prg++;
  }
  if(seleccion(wxT("Caso"),wxT("Variables de Entrada"))==0)
  {

    int i,tam;
    tam=Cas->Variables.GetCount();
    prg+=tam;
  }
  if(seleccion(wxT("Caso"),wxT("Variables Calculadas"))==0)
  {
    int i,tam;
    tam=Proy->Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      prg++;
      Estrategia *Est;
      Est=&Proy->Estrategias.Item(i);
      ListaNodos Nodos;
      Est->Grafo.llenarArreglo(&Nodos);
      int j,tam2;
      tam2=Nodos.GetCount();
      for(j=0;j<tam2;j++)
      {
        NodoCalculo *Nod;
        Nod=&Nodos.Item(0);
        if((Nod->FormaDeCalculo!=0))  // y se es entrada del caso ?????
        {
          prg++;
        }
        Nodos.Detach(0);
      }
    }
  }
  return prg;
}

int Reporte::calcularProgresoTotalTodosCaso(Proyecto *Proy)
{
  int prg=0;
  int i,tam;
  tam=Proy->Casos.GetCount();
  for(i=0;i<tam;i++)
  {
    prg+=calcularProgresoTotalCaso(&Proy->Casos.Item(i),Proy);
  }
  return prg;
}

int Reporte::calcularProgresoTotalResultados(Proyecto *Proy)
{
  int prg=0;
  int i,tam,total=0;
  tam=Proy->Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    total++;

    Estrategia *Est;
    Est = &Proy->Estrategias.Item(i);
    ListaNodos Nodos;

    Est->Grafo.llenarArreglo(&Nodos);

    int j,tam2;
    tam2=Nodos.GetCount();
    for(j=0;j<tam2;j++)
    {
      Nodos.Detach(0);
    }
    total+=tam2;
  }

  if(seleccion(wxT("Resultados"),wxT("Interpretaciones Cortas"))==0)
  {
    prg+=total;
  }
  if(seleccion(wxT("Resultados"),wxT("Interpretaciones Cortas Ordenadas"))==0)
  {
    prg+=total;
  }
  if(seleccion(wxT("Resultados"),wxT("Interpretaciones Largas"))==0)
  {
    prg+=total;
  }
  if(seleccion(wxT("Resultados"),wxT("Sensibilidad al Optimismo"))==0)
  {
    prg+=total;
  }
  return prg;
}


