/***************************************************************************
                          proyecto.cpp  -  description
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

#include "proyecto.h"
#include <wx/arrimpl.cpp>

WX_DEFINE_OBJARRAY(ListaEstrategias);
WX_DEFINE_OBJARRAY(ListaCasos);

Proyecto::Proyecto()
{
    ProyectoModificado=FALSE;
    Estrategias.Empty();
    Casos.Empty();

    Optimismo=0.5;
    Representatividad=0.5;

    iniciar(ESPECIFICO);
    NumEstrategia=0;
    NumCaso=0;
    calcularTodo();
}

void Proyecto::iniciar(int Opcion=0)
{
    Generalidades.limpiarPropiedades();
    Generalidades.adicionarPropiedad(wxT("Descripción"));
    Generalidades.modificarValor(wxT("Descripción del Proyecto"),0);
    Generalidades.adicionarPropiedad(wxT("Autores"));
    Generalidades.modificarValor(wxT("Autores del Proyecto"),1);

    Estrategias.Empty();
    Casos.Empty();

    Optimismo=0.5;
    Representatividad=0.5;

    Estrategia *Est;
    Caso *Cas;
    switch(Opcion)
    {
      case 0: // Vacío
              Est=new Estrategia;
              Estrategias.Add(Est);
              Est->Nombre=wxT("Nueva Metodología");
              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Nuevo Caso");
              break;
      case 1: // Vertederos 1 (Diputación)
              Est=new Estrategia;
              Est->crearVertedero1();
              Estrategias.Add(Est);
              Est->Nombre=wxT("EDIAV");

              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Nuevo Caso");
              Est->llenarCasoIndefinido(Cas,1);
              break;
      case 2: // Vertederos 2 (Monserrat)
              Est=new Estrategia;
              Est->crearVertedero2();
              Estrategias.Add(Est);
              Est->Nombre=wxT("Monserrat");

              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Huetor");
              Est->llenarCasoIndefinido(Cas,1);
              break;
      case 3: // QFD
              Est=new Estrategia;
              Est->crearRed1();
              Estrategias.Add(Est);
              Est->Nombre=wxT("Metodología 1");
              Est=new Estrategia;
              Est->crearRed2();
              Estrategias.Add(Est);
              Est->Nombre=wxT("Metodología 2");

              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Caso 1");
              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Caso 2");

              Estrategias.Item(0).llenarCasoIndefinido(&Casos.Item(0),1);
              Estrategias.Item(1).llenarCasoIndefinido(&Casos.Item(1),1);
              break;
      case 4: // Links Simples
              Est=new Estrategia;
              Est->crearRedLink1();
              Estrategias.Add(Est);
              Est->Grafo.ProyectoTotal=this;
              Est->Nombre=wxT("Metodología 1");
              Est=new Estrategia;
              Est->crearRedLink2();
              Estrategias.Add(Est);
              Est->Grafo.ProyectoTotal=this;
              Est->Nombre=wxT("Metodología 2");

              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Caso 1");
              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Caso 2");

              Estrategias.Item(0).llenarCasoIndefinido(&Casos.Item(0),1);
              Estrategias.Item(1).llenarCasoIndefinido(&Casos.Item(1),1);
              break;
      case 5: // Montserrat Versión seprada en redes con enlaces
      /*
              Est=new Estrategia;Est->Grafo.ProyectoTotal=this;Est->crearMFinal();

              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre="Caso 1";

              int i,tam;
              tam=Estrategias.GetCount();
              for(i=0;i<tam;i++)
              {
                Estrategias.Item(i).llenarCasoIndefinido(&Casos.Item(0),1);
              }
              break;*/
              Est=new Estrategia;
	      Est->Grafo.ProyectoTotal=this;
              //Estrategias.Add(Est);
              Est->crearMontse1();
              Est->Nombre=wxT("EVIAVE");
              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Nuevo Caso");
              int i,tam;
              tam=Estrategias.GetCount();
              for(i=0;i<tam;i++)
              {
                Estrategias.Item(i).llenarCasoIndefinido(&Casos.Item(0),1);
              }
              break;

      default: //
              Est=new Estrategia;
              Estrategias.Add(Est);
              Est->Nombre=wxT("Nueva Metodología");
              Cas=new Caso;
              Casos.Add(Cas);
              Cas->Nombre=wxT("Nuevo Caso");
              break;
    }
}

Proyecto::~Proyecto()
{
}

/**
 * aplica todas las estrategias a todos los casos
 */
void Proyecto::calcularTodo()
{
  int i,j,tam,tam2;
  tam=Estrategias.GetCount();
  tam2=Casos.GetCount();
  for(i=0;i<tam;i++)
  {
    for(j=0;j<tam2;j++)
    {
      Estrategias.Item(i).calcular(&Casos.Item(j));
    }
  }
}


NumeroDifuso* Proyecto::calcularCasoEstrategia(wxString C,wxString E)
{
  NumeroDifuso *Num;
  Num=new NumeroDifuso;
  int i,tam;
  int EstIt=-1;
  int CasIt=-1;
  tam=Estrategias.GetCount();
  for(i=0;i<tam;i++)
  {
    if(Estrategias.Item(i).Nombre==E)
    {
      EstIt=i;
      i=tam;
    }
  }
  tam=Casos.GetCount();
  for(i=0;i<tam;i++)
  {
    if(Casos.Item(i).Nombre==C)
    {
      CasIt=i;
      i=tam;
    }
  }
  if(EstIt<0 || CasIt < 0)
  {
    return Num;
  }
  Num=Estrategias.Item(EstIt).calcular(&Casos.Item(CasIt));
  return Num;
}

/**
 * Ordena los casos alfabéticamente utilizando la propiedad pr de generalidades
 */
void Proyecto::ordenNombre(int desc)
{
  int i,tam;
  tam=Casos.GetCount();
  wxString *valores;valores=new wxString[tam];
  wxString min,max;
  int *orden;orden=new int[tam];
  int ubicaMin,ubicaMax;
  min=(wxChar)255;max=(wxChar)0;
//  min="zzz";max="A";
  for(i=0;i<tam;i++)
  {
    valores[i]=Casos.Item(i).Nombre;
    if (valores[i].Cmp(min)<0){min=valores[i];ubicaMin=i;orden[0]=i;}
    if (valores[i].Cmp(max)>0){max=valores[i];ubicaMax=i;}
  }
  valores[ubicaMin]=max+wxT("z");
  for(i=1;i<tam;i++)
  {
    min=(wxChar)255;
//    min="zzz";
    for(int j=0;j<tam;j++)
    {
      if (valores[j].Cmp(min)<0){min=valores[j];ubicaMin=j;orden[i]=j;}
    }
    valores[ubicaMin]=max+wxT("z");
  }

  if(desc)

  {
    int *tmp;tmp=new int[tam];
    for(i=0;i<tam;i++)
    {
      tmp[i]=orden[tam-i-1];
    }
    for(i=0;i<tam;i++)
    {
      orden[i]=tmp[i];
    }
    delete [] tmp;
  }

  ListaCasos CasoTemp;
  for(i=0;i<tam;i++)
  {
    CasoTemp.Add(Casos.Item(orden[i]));
  }
  for(i=0;i<tam;i++)
  {
    Casos.Detach(0);
  }
  for(i=0;i<tam;i++)
  {
    Casos.Add(CasoTemp.Item(i));
  }
  for(i=0;i<tam;i++)
  {
    CasoTemp.Detach(0);
  }
  delete [] valores;
  delete [] orden;
}
/**
 * Ordena los casos alfabéticamente utilizando la propiedad pr de generalidades
 */
void Proyecto::ordenGeneralidad(wxString pr,int desc)
{
  int i,tam;
  tam=Casos.GetCount();
  wxString *valores;valores=new wxString[tam];
  wxString min,max;
  int *orden;orden=new int[tam];
  int ubicaMin,ubicaMax;
  min=(wxChar)255;max=(wxChar)0;
//  min="zzz";max="A";
  for(i=0;i<tam;i++)
  {
    valores[i]=Casos.Item(i).Generalidades.valor(pr);
    if (valores[i].Cmp(min)<0){min=valores[i];ubicaMin=i;orden[0]=i;}
    if (valores[i].Cmp(max)>0){max=valores[i];ubicaMax=i;}
  }
  valores[ubicaMin]=max+wxT("z");
  for(i=1;i<tam;i++)
  {
    min=(wxChar)255;

//    min="zzz";
    for(int j=0;j<tam;j++)
    {
      if (valores[j].Cmp(min)<0){min=valores[j];ubicaMin=j;orden[i]=j;}
    }
    valores[ubicaMin]=max+wxT("z");
  }

  if(desc)
  {
    int *tmp;tmp=new int[tam];
    for(i=0;i<tam;i++)
    {
      tmp[i]=orden[tam-i-1];
    }
    for(i=0;i<tam;i++)
    {
      orden[i]=tmp[i];
    }
    delete [] tmp;
  }

  ListaCasos CasoTemp;
  for(i=0;i<tam;i++)
  {
    CasoTemp.Add(Casos.Item(orden[i]));
  }
  for(i=0;i<tam;i++)
  {
    Casos.Detach(0);
  }
  for(i=0;i<tam;i++)
  {

    Casos.Add(CasoTemp.Item(i));
  }
  for(i=0;i<tam;i++)
  {
    CasoTemp.Detach(0);
  }
  delete [] valores;
  delete [] orden;
}

/** Ordena numéricamente los casos segn el valor que hay en el
 * en el Nodo nod con optimismo opt y exponente r
 */
void Proyecto::ordenValor(NodoCalculo *nod, float opt,float r,int desc)
{
  int i,tam;
  tam=Casos.GetCount();
  float *valores;valores=new float[tam];
  float min,max;
  int *orden;orden=new int[tam];
  int ubicaMin,ubicaMax;
  min=1e20;max=-1e20;

  for(i=0;i<tam;i++)
  {
    NumeroDifuso *N;
    N=nod->calcularCaso(&Casos.Item(i));
    valores[i]=N->valorRepresentativo(opt,r);
    if (valores[i]<min){min=valores[i];ubicaMin=i;orden[0]=i;}
    if (valores[i]>max){max=valores[i];ubicaMax=i;}
    delete N;
  }
  valores[ubicaMin]=2.0*max;
  for(i=1;i<tam;i++)
  {
    min=1e20;
    for(int j=0;j<tam;j++)
    {
      if (valores[j]<min){min=valores[j];ubicaMin=j;orden[i]=j;}
    }
    valores[ubicaMin]=2.0*max;
  }
  if(desc)
  {
    int *tmp;tmp=new int [tam];
    for(i=0;i<tam;i++)
    {
      tmp[i]=orden[tam-i-1];
    }
    for(i=0;i<tam;i++)
    {
      orden[i]=tmp[i];
    }
    delete [] tmp;
  }

  ListaCasos CasoTemp;
  for(i=0;i<tam;i++)
  {
    CasoTemp.Add(Casos.Item(orden[i]));
  }
  for(i=0;i<tam;i++)
  {
    Casos.Detach(0);
  }
  for(i=0;i<tam;i++)
  {
    Casos.Add(CasoTemp.Item(i));
  }
  for(i=0;i<tam;i++)
  {
    CasoTemp.Detach(0);
  }
  delete [] valores;
  delete [] orden;
}

void Proyecto::exportar(wxString nom,wxArrayString NombresCas,ListaSelecciones NombresEst,wxString Separador,int Opcion,bool Prop)
{
  wxTextFile f(nom);
  f.Create();
  int i,j,k,tam,tam2,tam3;

  wxArrayString NombreProp;
  wxArrayString ValorProp;
  if(Prop)
  {
    tam=Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      wxArrayString nombresPropiedad= Estrategias.Item(i).Generalidades.listaNombres();
      tam2=Estrategias.Item(i).Generalidades.tamano();
      for(j=0;j<tam2;j++)
      {
        wxString cad;
        cad=nombresPropiedad.Item(j);
        if(NombreProp.Index(cad)==wxNOT_FOUND)
        {
          NombreProp.Add(cad);
        }
      }
    }
  }

// Encabezado
  wxString linea=Separador;
  // Generalidades
  tam2=NombreProp.GetCount();
  for(j=0;j<tam2;j++)
  {
    linea << NombreProp.Item(j) << Separador;
  }
  // Nodos
  tam2=NombresEst.Opciones.GetCount();
  for(j=0;j<tam2;j++)
  {
    tam3=NombresEst.Opciones.Item(j).GetCount();
    for(k=0;k<tam3;k++)
    {
      linea << NombresEst.Opciones.Item(j).Item(k) << Separador;
    }
  }
  f.AddLine(linea);

// Los Casos
  tam=NombresCas.GetCount();
  for(i=0;i<tam;i++)
  {
    Caso *Cas=NULL;
    tam3=Casos.GetCount();
    for(int m=0;m<tam3;m++)
    {
      if(Casos.Item(m).Nombre==NombresCas.Item(i))
      {
        Cas=&Casos.Item(m);
      }
    }
    if(Cas!=NULL)
    {
      linea= NombresCas.Item(i);
      linea << Separador;
      // Generalidades
      tam2=NombreProp.GetCount();
      for(j=0;j<tam2;j++)
      {
        wxString cad;
        cad=Cas->Generalidades.valor(NombreProp.Item(j));
        if(cad==wxT("")){cad=wxT("N.N.");}
        linea << cad << Separador;
      }
      // Casos
      tam2=NombresEst.Opciones.GetCount();
      for(j=0;j<tam2;j++)
      {
        tam3=NombresEst.Opciones.Item(j).GetCount();
        for(k=0;k<tam3;k++)
        {
          NodoCalculo *Nd=NULL;
          Nd=Estrategias.Item(j).Grafo.buscarNodo(NombresEst.Opciones.Item(j).Item(k));
          if(Nd == NULL)
          {
            linea << wxT("N.N.") << Separador;
          }else
          {
            wxString cad;
            wxArrayString inter;
            NumeroDifuso *N;
            N=Nd->calcularCaso(Cas);
            int m;
            switch(Opcion)
            {
              case 0 : // valor Representativo
                    linea << N->valorRepresentativo(Optimismo,Representatividad) << Separador;
                    break;
              case 1 : // ambiguedad
                    linea << N->ambiguedad() << Separador;
                    break;
              case 2 : // valor Representativo y ambiguedad
                    linea << N->valorRepresentativo(Optimismo,Representatividad) << wxT(" / ") << Nd->calcular()->ambiguedad()<< Separador;
                    break;
              case 3 : // Interpretacion Corta
                    Nd->VarCalculada.interpretacionMaxima(&cad,N);
                    linea << cad << Separador;
                    break;
              case 4 : // Interpretacion Larga
                    Nd->VarCalculada.interpretacion(&inter,N);
                    for(m=0;m<inter.GetCount();m++)
                    {
                      linea << inter.Item(m);
                      if(m<inter.GetCount()-1)
                      {
                        linea << wxT(", ");
                      }
                    }
                    linea << Separador;
                    break;
              default : // valor Representativo
                    linea << Nd->calcular()->valorRepresentativo(Optimismo,Representatividad) << Separador;
                    break;
            }
          }
        }
      }
    }
    f.AddLine(linea);
  }
  f.Write();
}

void Proyecto::importar(wxString nom,ListaSelecciones Opciones,char Separador)
{
  wxTextFile f(nom);
  f.Open();
  int i,tam;
  tam=f.GetLineCount();
  if(tam<1){return;}

  wxArrayString NombreNodos;
  wxString NombreCaso;
  wxArrayString DatosEnLinea;
  wxString Linea;
  Linea=f.GetLine(0);
  NombreNodos.Clear();
  while(!Linea.IsEmpty()>0)
  {
    wxString cad;
    cad=Linea.BeforeFirst(Separador);
    Linea=Linea.AfterFirst(Separador);
    NombreNodos.Add(cad);
  };

  if(NombreNodos.GetCount()<1){return;}
  NombreNodos.RemoveAt(0);
  NombreCaso=wxT("");
  tam=f.GetLineCount();
  for(i=1;i<tam;i++)
  {
    Linea=f.GetLine(i);
    DatosEnLinea.Clear();
    while(!Linea.IsEmpty()>0)
    {
      wxString cad;
      cad=Linea.BeforeFirst(Separador);
      Linea=Linea.AfterFirst(Separador);
      DatosEnLinea.Add(cad);
    };
    if(DatosEnLinea.GetCount()>0)
    {
      NombreCaso=DatosEnLinea.Item(0);
      DatosEnLinea.RemoveAt(0);
      importaLinea(NombreCaso,NombreNodos,DatosEnLinea,Opciones);
    }
  }
  f.Close();
}

void Proyecto::importaLinea(wxString NombreCaso,wxArrayString NombreNodos,wxArrayString DatosEnLinea,ListaSelecciones Opciones)
{
 // Debe limpiar Caso?

 // buscar Caso
 Caso *Cas=NULL;
 int i,tam;
 tam=Casos.GetCount();

 for(i=0;i<tam;i++)
 {
   // como de be ser la comparación (case sensitive)?
  int cmp;
  switch(Opciones.Seleccion(wxT("Comparación de cadenas")))
  {
    default:
    case 0:
            cmp=Casos.Item(i).Nombre.Cmp(NombreCaso);
            break;
    case 1:
            cmp=Casos.Item(i).Nombre.CmpNoCase(NombreCaso);
            break;
  }
   if(cmp==0)
   {
    Cas=&Casos.Item(i);
    i=tam;
   }
 }
// Si no encuentra el caso debe crearlo o ignorarlo?
 if(Cas==NULL)
 {
   switch(Opciones.Seleccion(wxT("Caso Leido Inexistente")))
   {
     default:
     case 0:
           Cas=new Caso;
           Cas->Nombre=NombreCaso;
           Casos.Add(Cas);
           break;
     case 1:

            return;
   }
 }else  // Ya exist el caso... se borra su información?
 {
   switch(Opciones.Seleccion(wxT("Caso Leido Existente")))
   {
     default:
     case 0: break;
     case 1: Cas->Variables.Clear();
            break;
   }
 }
// ahora con los datos:
// primero se crea un arreglo con todos los nodos de todas las estrategias
 ListaNodos NodosDisponibles;
 wxArrayString NombreNodosDisponibles;
 tam=Estrategias.GetCount();
 for(i=0;i<tam;i++)
 {
   Estrategias.Item(i).Grafo.llenarArreglo(&NodosDisponibles);
 }
 tam=NodosDisponibles.GetCount();
 for(i=0;i<tam;i++)
 {
   NombreNodosDisponibles.Add(NodosDisponibles.Item(i).VarCalculada.Nombre);
 }
// ahora se evala cada dato de la linea
 tam=DatosEnLinea.GetCount();
 for(i=0;i<tam;i++)
 {
   wxString Dato,NombreNodo;
   Dato=DatosEnLinea.Item(i);
   if(i<NombreNodos.GetCount())  // datos contra nombres de la primera línea
   {
      NombreNodo=NombreNodos.Item(i);
   }else
   {
     // Hay más datos que nombres. Se adiciona un nombre ficticio
     NombreNodo=wxT("Sin Nombre");
     NombreNodo << i-NombreNodos.GetCount();
   }
   // busca el nombre en la lista de nodos disponibles
   // bsqueda Case sensitive?
   int cmp;
   switch(Opciones.Seleccion(wxT("Comparación de cadenas")))
   {
     default:
     case 0:
            cmp=NombreNodosDisponibles.Index(NombreNodo,TRUE);
            break;
     case 1:
            cmp=NombreNodosDisponibles.Index(NombreNodo,FALSE);
            break;
   }
   if(cmp==wxNOT_FOUND)
   {
     // No es un nodo disponible... qué hacer?
     // Se trata como una generalidad del caso   "Nodos Inexistentes"
     wxArrayString nombresPropiedad=Cas->Generalidades.listaNombres();
     int cmp2;
     switch(Opciones.Seleccion(wxT("Comparación de cadenas")))
     {
       default:
       case 0:
              cmp2=nombresPropiedad.Index(NombreNodo,TRUE);
              break;
       case 1:
               cmp2=nombresPropiedad.Index(NombreNodo,FALSE);
               break;
     }
     if(cmp2==wxNOT_FOUND)
     {
       // si no está la propiedad se adiciona debería ignorarse?
       Cas->Generalidades.adicionarPropiedad(NombreNodo);
     }
     Cas->Generalidades.modificarValor(Dato,NombreNodo);
   }else
   {
     // Si es un nodo disponible. Debe tratarse como una
     // variable del caso
     // Es variable o se calcula?
     int variable;
     if(NodosDisponibles.Item(cmp).NodosDeCalculo.GetCount()==0 || NodosDisponibles.Item(cmp).FormaDeCalculo==0)
     {
       // Es Variable
       variable=1;
     }else
     {
       // Deben ignorarse los nodos que se calculan?
       switch(Opciones.Seleccion(wxT("Nodos Calculados")))
       {
          default:
          case 0: variable=0;break;
          case 1: variable=1;break;
       }
     }
     if(variable)
     {

       // ahora buscamos en las variables del Caso
       int flag=-1;
       int j,tam2;
       tam2=Cas->Variables.GetCount();
       for(j=0;j<tam2;j++)
       {
         wxString Nom;
         Nom=Cas->Variables.Item(j).Nombre;
         int cmp2;
         // comparación sensitiva o no?
         switch(Opciones.Seleccion(wxT("Comparación de cadenas")))
         {
           default:
           case 0:
                 cmp2=Nom.Cmp(NombreNodo);
                 break;
           case 1:
                 cmp2=Nom.CmpNoCase(NombreNodo);
                 break;
         }
         if(cmp2==0)
         {
           flag=j;
           j=tam2;
         }
       }
       VariableLinguistica *Var=NULL;
       if(flag>-1)  // encontramos la variable
       {
         Var=&Cas->Variables.Item(flag);
       }else
       {    // No se encontró debe crearse? "Variables Inexistentes"
        switch(Opciones.Seleccion(wxT("Variables Inexistentes")))
        {
          default:
          case 0:
               Var=new VariableLinguistica(NombreNodo);
               Cas->Variables.Add(Var);
               // Es necesario copiar la semántica del nodo
               *Var=NodosDisponibles.Item(cmp).VarCalculada;
               break;
          case 1: break;
        }
       }
       // Debe asignarse el valor Dato a la variable Var cómo?
       // Se resuelve en VariableLinguistica
       if(Var !=NULL)
       {
        Var->importarCadena(Dato,Opciones);
       }
     }
   }
 }
 tam=NodosDisponibles.GetCount();
 for(i=0;i<tam;i++)
 {
   NodosDisponibles.Detach(0);
 }
}

void Proyecto::write(Mi_ofpstream &str)
{
  wxString CadenaControl;
  switch(ESPECIFICO)
  {
    case 0 : CadenaControl=wxT("FUZZYNET 1.0");break;
    case 1 : CadenaControl=wxT("EDIAV 1.0");break;
    case 5 : CadenaControl=wxT("EVIAVE 1.0");break;
    default : CadenaControl=wxT("FUZZYNET 1.0");break;
  }
  str << CadenaControl;
  str << Descripcion;
  Generalidades.write(str);

  int i,tam;
  tam=Estrategias.GetCount();
  str << tam;
  for(i=0;i<tam;i++)
  {
    Estrategias.Item(i).write(str);
  }
  tam=Casos.GetCount();
  str << tam;
  for(i=0;i<tam;i++)
  {
    Casos.Item(i).write(str);
  }
//  str << Optimismo;
//  str << Representatividad;
}

bool Proyecto::read(Mi_ifpstream &str)
{
  wxArrayString CadenasControl;
  switch(ESPECIFICO)
  {
    case 0 : CadenasControl.Add(wxT("FUZZYNET 1.0"));
             CadenasControl.Add(wxT("EDIAV 1.0"));
	     CadenasControl.Add(wxT("EVIAVE 1.0"));
             break;
    case 1 : CadenasControl.Add(wxT("EDIAV 1.0"));break;
    case 5 : CadenasControl.Add(wxT("EVIAVE 1.0"));break;
    default :CadenasControl.Add(wxT("FUZZYNET 1.0"));
             CadenasControl.Add(wxT("EDIAV 1.0"));
	     CadenasControl.Add(wxT("EVIAVE 1.0"));
             break;
  }
  wxString cad;
  str >> cad;
  int i,tam;
  int flag=0;
  tam=CadenasControl.GetCount();
  for(i=0;i<tam;i++)
  {
    if(cad==CadenasControl.Item(i))
    {
      flag=1;
      i=tam;
    }
  }
  if(flag==0)
  {
    return false;
  }
  str >> Descripcion;
  Generalidades.read(str);
  Estrategias.Clear();
  str >> tam;
  for(i=0;i<tam;i++)
  {
    Estrategia *Est;
    Est=new Estrategia;
    Est->read(str);

    Estrategias.Add(Est);
    Est->Grafo.ProyectoTotal=this;
  }
  Casos.Clear();
  str >> tam;
  for(i=0;i<tam;i++)
  {
    Caso* Cas;
    Cas=new Caso;
    Cas->read(str);
    Casos.Add(Cas);
  }
//  str >> Optimismo;
//  str >> Representatividad;
  return true;
}

