/***************************************************************************
                          estrategia.cpp  -  description
                             -------------------
    begin                : abr 13 2003
    copyright            : (C) 2003 by Oscar GermánDuarte Velasco
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   Este programa ha sido diseñado por Oscar G. Duarte V. por encargo del *
 *   Departamento de Ciencias de la Computación e Inteligencia             *
 *   Artificial de la Universidad de Granada.                              *
 *                                                                         *
 ***************************************************************************/

#include "estrategia.h"

Estrategia::Estrategia()
{
  Nombre=wxT("Sin Nombre");
}

Estrategia::~Estrategia()
{
  Grafo.eliminarNodosAbajoTodos();
}

/**
 * La estrategia de calculo sigue los siguientes pasos
 *
 * a) Crea una copia temporal de VarCalculada en Cada Nodo del Grafo
 *
 * b) Asigna TipoDeValor=0 (Indefinido) a VarCalculada en Cada Nodo del Grafo
 *
 * c) Busca si alguna VariableLinguistica del Caso tiene el mismo Nombre que
 *    VarCalculada en Cada Nodo del Grafo. En caso afirmativo, la copia en el Nodo
 *
 * d) Calcula el resultado del Grafo
 *
 * e) Restaura VarCalculada de la copia temporal en Cada Nodo del Grafo
 */
NumeroDifuso* Estrategia::calcular(Caso *caso)
{
  return Grafo.calcularCaso(caso);
}

/**
 * Calcula el resultado de aplicar la estrategia al Caso caso, en el nodo
 * cuya variable Calculada tiene por nombre nom. Si no existe tal Nodo
 * retorna un trapecio T(0,0,0,0)
 */
NumeroDifuso* Estrategia::calcularNodo(Caso *caso,wxString nom)
{
  NumeroDifuso *Num;
  NodoCalculo *Nod;
  Nod=Grafo.buscarNodo(nom);
  if(Nod!=NULL)
  {
    Num=Nod->calcularCaso(caso);
  }else
  {
    Num=new NumeroDifuso;
    Num->trapecio(0,0,0,0);
  }

  return Num;
}

/**
 * Asigna a caso un conjunto de variables liguisticas iguales a aquellas variables
 * de la estrategia que deban conocerse para efectuar el cálculo, es decir, aquellas
 * que no tienen nodos hijos, o aquellas que no se calculan con los hijos.
 */
void Estrategia::llenarCasoIndefinido(Caso *caso,int Flag)
{
//  caso->Variables.Clear();
  Grafo.llenarCasoIndefinido(caso);
  if(Flag)
  {
    // copiar generalidades
    wxArrayString nombresEst=Generalidades.listaNombres();
    int i,tam;
    tam=Generalidades.tamano();
    for(i=0;i<tam;i++)
    {
      wxArrayString nombresCaso=caso->Generalidades.listaNombres();
      wxString cad;
      cad=nombresEst.Item(i);
      if(nombresCaso.Index(cad)==wxNOT_FOUND)
      {
        caso->Generalidades.adicionarPropiedad(cad);
      }
    }
  }
}

/**
 * Adiciona las propiedades de Estrategia a Caso (sólo las que no están previamente definidas).
 */
void Estrategia::copiarPropiedades(Caso *caso)
{
  int i,tam,j,tam2;
  tam=Generalidades.tamano();
  for(i=0;i<tam;i++)
  {
    tam2=caso->Generalidades.tamano();
    int flag=0;
    for(j=0;j<tam2;j++)
    {
      if(Generalidades.nombre(i)==caso->Generalidades.nombre(j))
      {
        flag=1;
        j=tam2;
      }
    }
    if(flag==0)
    {
      caso->Generalidades.adicionarPropiedad(Generalidades.nombre(i));
    }
  }
}

void Estrategia::write(Mi_ofpstream &str)
{
  str << Nombre;
  str << Descripcion;
  Grafo.write(str);
  Generalidades.write(str);
}

void Estrategia::read(Mi_ifpstream &str)
{
  str >> Nombre;
  str >> Descripcion;
  ListaNodos ListaTmp,ListaArbol;
  ListaTmp.Add(&Grafo);
  Grafo.read(str,&ListaTmp);

//////////////////////////////////
//  Estas líneas permiten verificar qué nodos están repetidos y deben eliminarse

  Grafo.llenarArreglo(&ListaArbol,-1);
  int i,j,tam,tam2;
  tam=ListaTmp.GetCount();
  tam2=ListaArbol.GetCount();
  for(i=0;i<tam;i++)
  {
    int flag=0;
    for(j=0;j<tam2;j++)
    {
      if(&ListaTmp.Item(0)==&ListaArbol.Item(j))
      {
        flag=1;
        j=tam2;
      }
    }
   if(flag==0)  // No se encontró!!!
   {
      int k,tam3;
      tam3=ListaTmp.Item(0).NodosDeCalculo.GetCount();
      for(k=0;k<tam3;k++)
      {
        int ind=ListaTmp.Item(0).NodosDeCalculo.Item(0).NodosPadre.Index(ListaTmp.Item(0));
        ListaTmp.Item(0).NodosDeCalculo.Item(0).NodosPadre.Detach(ind);
        ListaTmp.Item(0).NodosDeCalculo.Detach(0);
      }
      tam3=ListaTmp.Item(0).NodosPadre.GetCount();
      for(k=0;k<tam3;k++)
      {
        ListaTmp.Item(0).NodosPadre.Detach(0);
      }
      ListaTmp.RemoveAt(0);
   }else  // si se encontró {
   {
     ListaTmp.Detach(0);
   }
  }
  for(j=0;j<tam2;j++)
  {
    ListaArbol.Detach(0);
  }

///////////
////// Aqui se verifica si hay dos nodos de igual nombre
  int flagCiclo;
  do
  {
   flagCiclo=0;
   Grafo.llenarArreglo(&ListaArbol,-1);
   tam=ListaArbol.GetCount();
   for(i=0;i<tam;i++)
   {
     for(j=i+1;j<tam;j++)
     {
       // si los nombres son iguales
       if(ListaArbol.Item(i).VarCalculada.Nombre==ListaArbol.Item(j).VarCalculada.Nombre)
       {
         // el problema está si los apuntadores son diferentes
         if(&ListaArbol.Item(i)!=&ListaArbol.Item(j))
         {
           // qué hacer?
           // quitamos los hijos del repetido...

          //////////////////////////////

           // OJO: la siguiente lpinea fue comentada para que el programa no hiciera crash al abrir una red compleja (DSM / SMTG)
           // REVISAR
//           ListaArbol.Item(j).eliminarNodosAbajoTodos();
					//////////////////////////////////


           // cambiamos los apuntadores en los padres del repetido
           int k,tam3;
           tam3=ListaArbol.Item(j).NodosPadre.GetCount();
           for(k=0;k<tam3;k++)
           {
             // este es un padre
             NodoCalculo  *nodpad=&ListaArbol.Item(j).NodosPadre.Item(k);
             int m,tam4;
             // buscamos cuál hijo es el nodo repetido y lo cambiamos
             tam4=nodpad->NodosDeCalculo.GetCount();
             for(m=0;m<tam4;m++)
             {
               // este es el nodo a remplazar
               if(&nodpad->NodosDeCalculo.Item(m)==&ListaArbol.Item(j))
               {
                 nodpad->NodosDeCalculo.Detach(m);
                 nodpad->NodosDeCalculo.Insert(&ListaArbol.Item(i),m);
               }
             }
             // adicionamos apuntadores a padre del original
             ListaArbol.Item(i).NodosPadre.Add(nodpad);
           }
           // eliminamos el nodo repetido..
           ListaArbol.Detach(j);  // deberá hacerse delete !!!
           j=tam;
           flagCiclo=1;
           // salimos del ciclo...
         }
       }
     }
   }
   tam=ListaArbol.GetCount();
   for(i=0;i<tam;i++)
   {
     ListaArbol.Detach(0);
   }
  }while(flagCiclo==1);

////////////////////  Fin de la verificación

  Generalidades.read(str);
}


/**
 * Implementación de la segunda estrategia de cálculo de impacto en vertederos (Monserrat Zambrano)
 */
void Estrategia::crearVertedero2()
{

  // Generalidades

  Generalidades.adicionarPropiedad(wxT("Ubicación"));


  // Declaración y construcción de los nodos del árbol
  NodoCalculo *IMVASP,*IMVAST,*IMVAT,*IMVSL,*IMVSP;
  NodoCalculo *IRAASP,*IRAAST,*IRAAT,*IRASL,*IRASP;
  NodoCalculo *CPAASP,*CPAAST,*CPAAT,*CPASL,*CPASP;
  NodoCalculo *PBCASP,*PBCAST,*PBCAT,*PBCSL,*PBCSP;
  NodoCalculo *VAASP, *VAAST, *VAAT, *VASL,*VASP;
  NodoCalculo *A1,*A2,*A3,*A4,*A5;
  NodoCalculo *B1,*B2;
  NodoCalculo *C1,*C2,*C3,*C4,*C5,*C6;
  NodoCalculo *UsoAgricola,*UsoRecreacional,*UsoResidencial;
  NodoCalculo *DAG,*DRC,*DRS;
  NodoCalculo *D1,*D2,*D3,*D4,*D5,*D6;
  NodoCalculo *a,*b,*c,*d,*e,*f,*g,*h,*i,*j,*k,*l,*m,*n,*o,*p,*q,*r,*s,*t,*u,*v,*w,*xx,*y;
  NodoCalculo *mo;
  NodoCalculo *res;
  NodoCalculo *IASP,*IAST,*IAT,*ISL,*ISP;
  NodoCalculo *RASP,*RAST,*RAT,*RSL,*RSP;
  NodoCalculo *DASP,*DAST,*DAT,*DSL,*DSP;
  NodoCalculo *EASP,*EAST,*EAT,*ESL,*ESP;

  IMVASP=new NodoCalculo(); IMVAST=new NodoCalculo(); IMVAT=new NodoCalculo(); IMVSL=new NodoCalculo(); IMVSP=new NodoCalculo();
  IRAASP=new NodoCalculo(); IRAAST=new NodoCalculo(); IRAAT=new NodoCalculo(); IRASL=new NodoCalculo(); IRASP=new NodoCalculo();
  CPAASP=new NodoCalculo(); CPAAST=new NodoCalculo(); CPAAT=new NodoCalculo(); CPASL=new NodoCalculo(); CPASP=new NodoCalculo();
  PBCASP=new NodoCalculo(); PBCAST=new NodoCalculo(); PBCAT=new NodoCalculo(); PBCSL=new NodoCalculo(); PBCSP=new NodoCalculo();
   VAASP=new NodoCalculo();  VAAST=new NodoCalculo();  VAAT=new NodoCalculo();  VASL=new NodoCalculo();  VASP=new NodoCalculo();

  A1=new NodoCalculo();A2=new NodoCalculo();A3=new NodoCalculo();A4=new NodoCalculo();A5=new NodoCalculo();
  B1=new NodoCalculo();B2=new NodoCalculo();
  C1=new NodoCalculo();C2=new NodoCalculo();C3=new NodoCalculo();C4=new NodoCalculo();C5=new NodoCalculo();C6=new NodoCalculo();
  UsoAgricola=new NodoCalculo();UsoRecreacional=new NodoCalculo();UsoResidencial=new NodoCalculo();
  DAG=new NodoCalculo();DRC=new NodoCalculo();DRS=new NodoCalculo();
  D1=new NodoCalculo();D2=new NodoCalculo();D3=new NodoCalculo();D4=new NodoCalculo();D5=new NodoCalculo();D6=new NodoCalculo();

  a=new NodoCalculo();b=new NodoCalculo();c=new NodoCalculo();d=new NodoCalculo();e=new NodoCalculo();
  f=new NodoCalculo();g=new NodoCalculo();h=new NodoCalculo();i=new NodoCalculo();j=new NodoCalculo();
  k=new NodoCalculo();l=new NodoCalculo();m=new NodoCalculo();n=new NodoCalculo();o=new NodoCalculo();
  p=new NodoCalculo();q=new NodoCalculo();r=new NodoCalculo();s=new NodoCalculo();t=new NodoCalculo();
  u=new NodoCalculo();v=new NodoCalculo();w=new NodoCalculo();xx=new NodoCalculo();y=new NodoCalculo();

  mo=new NodoCalculo();res=new NodoCalculo();

  IASP=new NodoCalculo(); IAST=new NodoCalculo(); IAT=new NodoCalculo(); ISL=new NodoCalculo(); ISP=new NodoCalculo();
  RASP=new NodoCalculo(); RAST=new NodoCalculo(); RAT=new NodoCalculo(); RSL=new NodoCalculo(); RSP=new NodoCalculo();
  DASP=new NodoCalculo(); DAST=new NodoCalculo(); DAT=new NodoCalculo(); DSL=new NodoCalculo(); DSP=new NodoCalculo();
  EASP=new NodoCalculo(); EAST=new NodoCalculo(); EAT=new NodoCalculo(); ESL=new NodoCalculo(); ESP=new NodoCalculo();

//  Definición de Variables

  Grafo.VarCalculada.Nombre=wxT("IMV");
  Etiqueta *Et; VariableLinguistica *Var;

  Var=&(Grafo.VarCalculada);
  Var->autodefinirRecto(5);

  IMVASP->VarCalculada.Nombre=wxT("IMVASP");
  Var=&(IMVASP->VarCalculada);
  Var->autodefinirRecto(5);

  IMVAST->VarCalculada.Nombre=wxT("IMVAST");
  Var=&(IMVAST->VarCalculada);
  Var->autodefinirRecto(5);

  IMVAT->VarCalculada.Nombre=wxT("IMVAT");
  Var=&(IMVAT->VarCalculada);
  Var->autodefinirRecto(5);

  IMVSL->VarCalculada.Nombre=wxT("IMVSL");
  Var=&(IMVSL->VarCalculada);
  Var->autodefinirRecto(5);

  IMVSP->VarCalculada.Nombre=wxT("IMVSP");
  Var=&(IMVSP->VarCalculada);
  Var->autodefinirRecto(5);

  IRAASP->VarCalculada.Nombre=wxT("IRAASP");
  Var=&(IRAASP->VarCalculada);
  Var->autodefinirRecto(5);

  IRAAST->VarCalculada.Nombre=wxT("IRAAST");
  Var=&(IRAAST->VarCalculada);
  Var->autodefinirRecto(5);

  IRAAT->VarCalculada.Nombre=wxT("IRAAT");
  Var=&(IRAAT->VarCalculada);
  Var->autodefinirRecto(5);

  IRASL->VarCalculada.Nombre=wxT("IRASL");
  Var=&(IRASL->VarCalculada);
  Var->autodefinirRecto(5);

  IRASP->VarCalculada.Nombre=wxT("IRASP");
  Var=&(IRASP->VarCalculada);
  Var->autodefinirRecto(5);

  CPAASP->VarCalculada.Nombre=wxT("CPAASP");
  Var=&(CPAASP->VarCalculada);
  Var->autodefinirRecto(5);

  CPAAST->VarCalculada.Nombre=wxT("CPAAST");
  Var=&(CPAAST->VarCalculada);
  Var->autodefinirRecto(5);

  CPAAT->VarCalculada.Nombre=wxT("CPAAT");
  Var=&(CPAAT->VarCalculada);
  Var->autodefinirRecto(5);

  CPASL->VarCalculada.Nombre=wxT("CPASL");
  Var=&(CPASL->VarCalculada);
  Var->autodefinirRecto(5);

  CPASP->VarCalculada.Nombre=wxT("CPASP");
  Var=&(CPASP->VarCalculada);
  Var->autodefinirRecto(5);

  PBCASP->VarCalculada.Nombre=wxT("PBCASP");
  Var=&(PBCASP->VarCalculada);
  Var->autodefinirRecto(5);

  PBCAST->VarCalculada.Nombre=wxT("PBCAST");
  Var=&(PBCAST->VarCalculada);
  Var->autodefinirRecto(5);

  PBCAT->VarCalculada.Nombre=wxT("PBCAT");
  Var=&(PBCAT->VarCalculada);
  Var->autodefinirRecto(5);

  PBCSL->VarCalculada.Nombre=wxT("PBCSL");
  Var=&(PBCSL->VarCalculada);
  Var->autodefinirRecto(5);

  PBCSP->VarCalculada.Nombre=wxT("PBCSP");
  Var=&(PBCSP->VarCalculada);
  Var->autodefinirRecto(5);

  VAASP->VarCalculada.Nombre=wxT("VAASP");
  Var=&(VAASP->VarCalculada);
  Var->autodefinirRecto(5);

  VAAST->VarCalculada.Nombre=wxT("VAAST");
  Var=&(VAAST->VarCalculada);
  Var->autodefinirRecto(5);

  VAAT->VarCalculada.Nombre=wxT("VAAT");
  Var=&(VAAT->VarCalculada);
  Var->autodefinirRecto(5);

  VASL->VarCalculada.Nombre=wxT("VASL");
  Var=&(VASL->VarCalculada);
  Var->autodefinirRecto(5);

  VASP->VarCalculada.Nombre=wxT("VASP");
  Var=&(VASP->VarCalculada);
  Var->autodefinirRecto(5);

  A1->VarCalculada.Nombre=wxT("A1");
  Var=&(A1->VarCalculada);
  Var->autodefinirRecto(5);

  A2->VarCalculada.Nombre=wxT("A2");
  Var=&(A2->VarCalculada);
  Var->autodefinirRecto(5);

  A3->VarCalculada.Nombre=wxT("A3");
  Var=&(A3->VarCalculada);
  Var->autodefinirRecto(5);

  A4->VarCalculada.Nombre=wxT("A4");
  Var=&(A4->VarCalculada);
  Var->autodefinirRecto(5);

  A5->VarCalculada.Nombre=wxT("A5");
  Var=&(A5->VarCalculada);
  Var->autodefinirRecto(5);

  B1->VarCalculada.Nombre=wxT("B1");
  Var=&(B1->VarCalculada);
  Var->autodefinirRecto(5);

  B2->VarCalculada.Nombre=wxT("B2");
  Var=&(B2->VarCalculada);
  Var->autodefinirRecto(5);

  C1->VarCalculada.Nombre=wxT("C1");
  Var=&(C1->VarCalculada);
  Var->autodefinirRecto(5);

  C2->VarCalculada.Nombre=wxT("C2");
  Var=&(C2->VarCalculada);
  Var->autodefinirRecto(5);

  C3->VarCalculada.Nombre=wxT("C3");
  Var=&(C3->VarCalculada);
  Var->autodefinirRecto(5);

  C4->VarCalculada.Nombre=wxT("C4");
  Var=&(C4->VarCalculada);
  Var->autodefinirRecto(5);

  C5->VarCalculada.Nombre=wxT("C5");
  Var=&(C5->VarCalculada);
  Var->autodefinirRecto(5);

  C6->VarCalculada.Nombre=wxT("C6");
  Var=&(C6->VarCalculada);
  Var->autodefinirRecto(5);

  UsoAgricola->VarCalculada.Nombre=wxT("Uso Agricola");
  Var=&(UsoAgricola->VarCalculada);
  Var->autodefinirRecto(2);

  UsoRecreacional->VarCalculada.Nombre=wxT("Uso Recreacional");
  Var=&(UsoRecreacional->VarCalculada);
  Var->autodefinirRecto(2);

  UsoResidencial->VarCalculada.Nombre=wxT("Uso Residencial");
  Var=&(UsoResidencial->VarCalculada);
  Var->autodefinirRecto(2);

  DAG->VarCalculada.Nombre=wxT("DAG");
  Var=&(DAG->VarCalculada);
  Var->autodefinirRecto(5);

  DRC->VarCalculada.Nombre=wxT("DRS");
  Var=&(DRC->VarCalculada);
  Var->autodefinirRecto(5);

  DRS->VarCalculada.Nombre=wxT("DRC");
  Var=&(DRS->VarCalculada);
  Var->autodefinirRecto(5);

  D1->VarCalculada.Nombre=wxT("D1");
  Var=&(D1->VarCalculada);
  Var->autodefinirRecto(5);

  D2->VarCalculada.Nombre=wxT("D2");
  Var=&(D2->VarCalculada);
  Var->autodefinirRecto(5);

  D3->VarCalculada.Nombre=wxT("D3");
  Var=&(D3->VarCalculada);
  Var->autodefinirRecto(5);

  D4->VarCalculada.Nombre=wxT("D4");
  Var=&(D4->VarCalculada);
  Var->autodefinirRecto(5);

  D5->VarCalculada.Nombre=wxT("D5");
  Var=&(D5->VarCalculada);
  Var->autodefinirRecto(5);

  D6->VarCalculada.Nombre=wxT("D6");
  Var=&(D6->VarCalculada);
  Var->autodefinirRecto(5);

  a->VarCalculada.Nombre=wxT("Compactación");
  Var=&(a->VarCalculada);
  Var->autodefinirRecto(5);

  b->VarCalculada.Nombre=wxT("Residuos y m.o.");
  Var=&(b->VarCalculada);
  Var->autodefinirRecto(5);

  c->VarCalculada.Nombre=wxT("Edad");
  Var=&(c->VarCalculada);
  Var->autodefinirRecto(5);

  d->VarCalculada.Nombre=wxT("Cobertura");
  Var=&(d->VarCalculada);
  Var->autodefinirRecto(5);

  e->VarCalculada.Nombre=wxT("Gases");
  Var=&(e->VarCalculada);
  Var->autodefinirRecto(5);

  f->VarCalculada.Nombre=wxT("Caminos");
  Var=&(f->VarCalculada);
  Var->autodefinirRecto(5);

  g->VarCalculada.Nombre=wxT("Pluviometría");
  Var=&(g->VarCalculada);
  Var->autodefinirRecto(5);

  h->VarCalculada.Nombre=wxT("Lixiviados");
  Var=&(h->VarCalculada);
  Var->autodefinirRecto(5);

  i->VarCalculada.Nombre=wxT("Cobertura Final");
  Var=&(i->VarCalculada);
  Var->autodefinirRecto(5);

  j->VarCalculada.Nombre=wxT("Operatividad");
  Var=&(j->VarCalculada);
  Var->autodefinirRecto(5);

  k->VarCalculada.Nombre=wxT("Pendiente a cauces");
  Var=&(k->VarCalculada);
  Var->autodefinirRecto(5);

  l->VarCalculada.Nombre=wxT("Permeabilidad");
  Var=&(l->VarCalculada);
  Var->autodefinirRecto(5);

  m->VarCalculada.Nombre=wxT("Drenaje");
  Var=&(m->VarCalculada);
  Var->autodefinirRecto(5);

  n->VarCalculada.Nombre=wxT("Aguas superficiales");
  Var=&(n->VarCalculada);
  Var->autodefinirRecto(5);

  o->VarCalculada.Nombre=wxT("Impermeabilización");
  Var=&(o->VarCalculada);
  Var->autodefinirRecto(5);

  p->VarCalculada.Nombre=wxT("Área inundable");
  Var=&(p->VarCalculada);
  Var->autodefinirRecto(5);

  q->VarCalculada.Nombre=wxT("Escorrentía superficial");
  Var=&(q->VarCalculada);
  Var->autodefinirRecto(5);

  r->VarCalculada.Nombre=wxT("Profundidad aguas subterráneas");
  Var=&(r->VarCalculada);
  Var->autodefinirRecto(5);

  s->VarCalculada.Nombre=wxT("Fallas cercanas");
  Var=&(s->VarCalculada);
  Var->autodefinirRecto(5);

  t->VarCalculada.Nombre=wxT("Edad y m.o.");
  Var=&(t->VarCalculada);
  Var->autodefinirRecto(5);

  u->VarCalculada.Nombre=wxT("Taludes");
  Var=&(u->VarCalculada);
  Var->autodefinirRecto(5);

  v->VarCalculada.Nombre=wxT("Distancia a Infraestructuras");
  Var=&(v->VarCalculada);
  Var->autodefinirRecto(5);

  w->VarCalculada.Nombre=wxT("Control Ambiental");
  Var=&(w->VarCalculada);
  Var->autodefinirRecto(5);

  xx->VarCalculada.Nombre=wxT("Distancia a poblados");
  Var=&(xx->VarCalculada);
  Var->autodefinirRecto(5);

  y->VarCalculada.Nombre=wxT("Equipamiento Personal");
  Var=&(y->VarCalculada);
  Var->autodefinirRecto(5);

  mo->VarCalculada.Nombre=wxT("Materia Orgánica");
  Var=&(mo->VarCalculada);
  Var->autodefinirRecto(5);

  res->VarCalculada.Nombre=wxT("Residuos");
  Var=&(res->VarCalculada);
  Var->autodefinirRecto(5);

  IASP->VarCalculada.Nombre=wxT("Intensidad ASP");
  Var=&(IASP->VarCalculada);
  Var->autodefinirRecto(5);

  IAST->VarCalculada.Nombre=wxT("Intensidad AST");
  Var=&(IAST->VarCalculada);
  Var->autodefinirRecto(5);

  IAT->VarCalculada.Nombre=wxT("Intensidad AT");
  Var=&(IAT->VarCalculada);
  Var->autodefinirRecto(5);

  ISL->VarCalculada.Nombre=wxT("Intensidad SL");
  Var=&(ISL->VarCalculada);
  Var->autodefinirRecto(5);

  ISP->VarCalculada.Nombre=wxT("Intensidad SP");
  Var=&(ISP->VarCalculada);
  Var->autodefinirRecto(5);

  RASP->VarCalculada.Nombre=wxT("Reversibilidad ASP");
  Var=&(RASP->VarCalculada);
  Var->autodefinirRecto(5);

  RAST->VarCalculada.Nombre=wxT("Reversibilidad AST");
  Var=&(RAST->VarCalculada);
  Var->autodefinirRecto(5);

  RAT->VarCalculada.Nombre=wxT("Reversibilidad AT");
  Var=&(RAT->VarCalculada);
  Var->autodefinirRecto(5);

  RSL->VarCalculada.Nombre=wxT("Reversibilidad SL");
  Var=&(RSL->VarCalculada);
  Var->autodefinirRecto(5);

  RSP->VarCalculada.Nombre=wxT("Reversibilidad SP");
  Var=&(RSP->VarCalculada);
  Var->autodefinirRecto(5);

  DASP->VarCalculada.Nombre=wxT("Duración ASP");
  Var=&(DASP->VarCalculada);
  Var->autodefinirRecto(5);

  DAST->VarCalculada.Nombre=wxT("Duración AST");
  Var=&(DAST->VarCalculada);
  Var->autodefinirRecto(5);

  DAT->VarCalculada.Nombre=wxT("Duración AT");
  Var=&(DAT->VarCalculada);
  Var->autodefinirRecto(5);

  DSL->VarCalculada.Nombre=wxT("Duración SL");
  Var=&(DSL->VarCalculada);
  Var->autodefinirRecto(5);

  DSP->VarCalculada.Nombre=wxT("Duración SP");
  Var=&(DSP->VarCalculada);
  Var->autodefinirRecto(5);

  EASP->VarCalculada.Nombre=wxT("Extensión ASP");
  Var=&(EASP->VarCalculada);
  Var->autodefinirRecto(5);

  EAST->VarCalculada.Nombre=wxT("Extensión AST");
  Var=&(EAST->VarCalculada);
  Var->autodefinirRecto(5);

  EAT->VarCalculada.Nombre=wxT("Extensión AT");
  Var=&(EAT->VarCalculada);
  Var->autodefinirRecto(5);

  ESL->VarCalculada.Nombre=wxT("Extensión SL");
  Var=&(ESL->VarCalculada);
  Var->autodefinirRecto(5);

  ESP->VarCalculada.Nombre=wxT("Extensión SP");
  Var=&(ESP->VarCalculada);
  Var->autodefinirRecto(5);

// INCOMPLETO

// asignación de los nodos y funciones
  Funcion *F;
  float x[20];

  Grafo.adicionarNodo(IMVASP);
  Grafo.adicionarNodo(IMVAST);
  Grafo.adicionarNodo(IMVAT);
  Grafo.adicionarNodo(IMVSL);
  Grafo.adicionarNodo(IMVSP);
  x[0]=1.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;x[4]=1.0;
  F=new CombinacionLineal(x,5,0.0);
  Grafo.asignarFuncion(F);

  IMVASP->adicionarNodo(IRAASP);
  IMVASP->adicionarNodo(CPAASP);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IMVASP->asignarFuncion(F);

  IMVAST->adicionarNodo(IRAAST);
  IMVAST->adicionarNodo(CPAAST);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IMVAST->asignarFuncion(F);

  IMVAT->adicionarNodo(IRAAT);
  IMVAT->adicionarNodo(CPAAT);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IMVAT->asignarFuncion(F);

  IMVSL->adicionarNodo(IRASL);
  IMVSL->adicionarNodo(CPASL);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IMVSL->asignarFuncion(F);

  IMVSP->adicionarNodo(IRASP);
  IMVSP->adicionarNodo(CPASP);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IMVSP->asignarFuncion(F);

  IRAASP->adicionarNodo(PBCASP);
  IRAASP->adicionarNodo(VAASP);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IRAASP->asignarFuncion(F);

  IRAAST->adicionarNodo(PBCAST);
  IRAAST->adicionarNodo(VAAST);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IRAAST->asignarFuncion(F);

  IRAAT->adicionarNodo(PBCAT);
  IRAAT->adicionarNodo(VAAT);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IRAAT->asignarFuncion(F);

  IRASL->adicionarNodo(PBCSL);
  IRASL->adicionarNodo(VASL);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IRASL->asignarFuncion(F);

  IRASP->adicionarNodo(PBCSP);
  IRASP->adicionarNodo(VASP);
  x[0]=1.0;x[1]=1.0;
  F=new SumaProd(x,2,0.0);
  IRASP->asignarFuncion(F);

  VAASP->adicionarNodo(A1);
  VAASP->adicionarNodo(A2);
  VAASP->adicionarNodo(A3);
  VAASP->adicionarNodo(A4);
  VAASP->adicionarNodo(A5);
  x[0]=1.0;x[1]=1.0;x[2]=2.0;x[3]=1.0;x[4]=1.0;
  F=new CombinacionLineal(x,5,0.0);
  VAASP->asignarFuncion(F);

  VAAST->adicionarNodo(B1);
  VAAST->adicionarNodo(B2);
  x[0]=1.0;x[1]=2.0;
  F=new CombinacionLineal(x,2,0.0);
  VAAST->asignarFuncion(F);

  VAAT->adicionarNodo(C1);
  VAAT->adicionarNodo(C2);
  VAAT->adicionarNodo(C3);
  VAAT->adicionarNodo(C4);
  VAAT->adicionarNodo(C5);
  VAAT->adicionarNodo(C6);
  x[0]=2.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;x[4]=1.0;x[5]=1.0;
  F=new CombinacionLineal(x,6,0.0);
  VAAT->asignarFuncion(F);

  VASL->adicionarNodo(UsoAgricola);
  VASL->adicionarNodo(DAG);
  VASL->adicionarNodo(UsoRecreacional);
  VASL->adicionarNodo(DRC);
  VASL->adicionarNodo(UsoResidencial);
  VASL->adicionarNodo(DRS);
  x[0]=1.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;x[4]=1.0;x[5]=1.0;
  F=new SumaProd(x,6,0.0);
  VASL->asignarFuncion(F);

  DAG->adicionarNodo(D1);
  DAG->adicionarNodo(D2);
  DAG->adicionarNodo(D3);
  DAG->adicionarNodo(D4);
  x[0]=1.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;
  F=new CombinacionLineal(x,4,0.0);
  DAG->asignarFuncion(F);

  DRC->adicionarNodo(D1);
  DRC->adicionarNodo(D2);
  DRC->adicionarNodo(D4);
  x[0]=1.0;x[1]=1.0;x[2]=1.0;
  F=new CombinacionLineal(x,5,0.0);
  DRC->asignarFuncion(F);

  DRS->adicionarNodo(D1);
  DRS->adicionarNodo(D2);
  DRS->adicionarNodo(D4);
  DRS->adicionarNodo(D5);
  DRS->adicionarNodo(D6);
  x[0]=1.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;x[4]=1.0;
  F=new CombinacionLineal(x,5,0.0);
  DRS->asignarFuncion(F);

  PBCAT->adicionarNodo(a);
  PBCAT->adicionarNodo(b);
  PBCAT->adicionarNodo(c);
  PBCAT->adicionarNodo(d);
  PBCAT->adicionarNodo(e);
  PBCAT->adicionarNodo(f);
  PBCAT->adicionarNodo(g);
  PBCAT->adicionarNodo(h);
  PBCAT->adicionarNodo(i);
  PBCAT->adicionarNodo(j);
  x[0]=2.0/10.0;x[1]=2.0/10.0;x[2]=1.0/10.0;x[3]=2.0/10.0;x[4]=2.0/10.0;
  x[5]=1.0/10.0;x[6]=2.0/10.0;x[7]=1.0/10.0;x[8]=2.0/10.0;x[9]=1.0/10.0;
  F=new CombinacionLineal(x,10,0.0);
  PBCAT->asignarFuncion(F);

  PBCASP->adicionarNodo(a);
  PBCASP->adicionarNodo(b);
  PBCASP->adicionarNodo(c);
  PBCASP->adicionarNodo(d);
  PBCASP->adicionarNodo(k);
  PBCASP->adicionarNodo(l);
  PBCASP->adicionarNodo(m);
  PBCASP->adicionarNodo(n);
  PBCASP->adicionarNodo(g);
  PBCASP->adicionarNodo(o);
  PBCASP->adicionarNodo(h);
  PBCASP->adicionarNodo(i);
  PBCASP->adicionarNodo(p);
  PBCASP->adicionarNodo(q);
  PBCASP->adicionarNodo(j);
  x[0]=2.0/15.0;x[1]=2.0/15.0;x[2]=1.0/15.0;x[3]=2.0/15.0;x[4]=1.0/15.0;
  x[5]=1.0/15.0;x[6]=1.0/15.0;x[7]=2.0/15.0;x[8]=2.0/15.0;x[9]=2.0/15.0;

x[10]=2.0/15.0;x[11]=2.0/15.0;x[12]=2.0/15.0;x[13]=2.0/15.0;x[14]=1.0/15.0;
  F=new CombinacionLineal(x,15,0.0);
  PBCASP->asignarFuncion(F);

  PBCAST->adicionarNodo(a);
  PBCAST->adicionarNodo(b);
  PBCAST->adicionarNodo(c);
  PBCAST->adicionarNodo(d);
  PBCAST->adicionarNodo(r);
  PBCAST->adicionarNodo(s);
  PBCAST->adicionarNodo(m);
  PBCAST->adicionarNodo(g);
  PBCAST->adicionarNodo(o);
  PBCAST->adicionarNodo(h);
  PBCAST->adicionarNodo(i);
  PBCAST->adicionarNodo(p);
  PBCAST->adicionarNodo(q);
  PBCAST->adicionarNodo(j);
  x[0]=2.0/14.0;x[1]=2.0/14.0;x[2]=1.0/14.0;x[3]=2.0/14.0;x[4]=2.0/14.0;
  x[5]=1.0/14.0;x[6]=1.0/14.0;x[7]=2.0/14.0;x[8]=2.0/14.0;x[9]=2.0/14.0;
  x[10]=2.0/14.0;x[11]=2.0/14.0;x[12]=2.0/14.0;x[13]=1.0/14.0;
  F=new CombinacionLineal(x,14,0.0);
  PBCAST->asignarFuncion(F);

  PBCSL->adicionarNodo(a);
  PBCSL->adicionarNodo(t);
  PBCSL->adicionarNodo(d);
  PBCSL->adicionarNodo(e);
  PBCSL->adicionarNodo(u);
  PBCSL->adicionarNodo(o);
  PBCSL->adicionarNodo(p);
  PBCSL->adicionarNodo(h);
  PBCSL->adicionarNodo(i);
  PBCSL->adicionarNodo(q);
  PBCSL->adicionarNodo(j);
  x[0]=2.0/11.0;x[1]=2.0/11.0;x[2]=2.0/11.0;x[3]=1.0/11.0;x[4]=2.0/11.0;
  x[5]=1.0/11.0;x[6]=2.0/11.0;x[7]=1.0/11.0;x[8]=2.0/11.0;x[9]=2.0/11.0;
  x[10]=1.0/11.0;
  F=new CombinacionLineal(x,11,0.0);
  PBCSL->asignarFuncion(F);

  PBCSP->adicionarNodo(a);
  PBCSP->adicionarNodo(b);
  PBCSP->adicionarNodo(c);
  PBCSP->adicionarNodo(d);
  PBCSP->adicionarNodo(v);
  PBCSP->adicionarNodo(e);
  PBCSP->adicionarNodo(w);
  PBCSP->adicionarNodo(h);
  PBCSP->adicionarNodo(i);
  PBCSP->adicionarNodo(xx);
  PBCSP->adicionarNodo(y);
  PBCSP->adicionarNodo(j);
  x[0]=2.0/12.0;x[1]=2.0/12.0;x[2]=1.0/12.0;x[3]=1.0/12.0;x[4]=2.0/12.0;
  x[5]=1.0/12.0;x[6]=1.0/12.0;x[7]=1.0/12.0;x[8]=2.0/12.0;x[9]=2.0/12.0;
  x[10]=2.0/12.0;x[11]=1.0/12.0;
  F=new CombinacionLineal(x,12,0.0);
  PBCSP->asignarFuncion(F);

  t->adicionarNodo(c);
  t->adicionarNodo(mo);
  x[0]=1.0;x[1]=1.0;
  F=new CombinacionLineal(x,2,0.0);
  t->asignarFuncion(F);

  b->adicionarNodo(res);
  b->adicionarNodo(mo);
  x[0]=1.0;x[1]=1.0;
  F=new CombinacionLineal(x,2,0.0);
  b->asignarFuncion(F);

  CPAASP->adicionarNodo(IASP);
  CPAASP->adicionarNodo(RASP);
  CPAASP->adicionarNodo(DASP);
  CPAASP->adicionarNodo(EASP);
  x[0]=1.0/3.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;
  F=new CombinacionLineal(x,4,0.0);
  CPAASP->asignarFuncion(F);

  CPAAST->adicionarNodo(IAST);
  CPAAST->adicionarNodo(RAST);
  CPAAST->adicionarNodo(DAST);
  CPAAST->adicionarNodo(EAST);
  x[0]=1.0/3.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;
  F=new CombinacionLineal(x,4,0.0);
  CPAAST->asignarFuncion(F);

  CPAAT->adicionarNodo(IAT);
  CPAAT->adicionarNodo(RAT);
  CPAAT->adicionarNodo(DAT);
  CPAAT->adicionarNodo(EAT);
  x[0]=1.0/3.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;
  F=new CombinacionLineal(x,4,0.0);
  CPAAT->asignarFuncion(F);

  CPASL->adicionarNodo(ISL);
  CPASL->adicionarNodo(RSL);
  CPASL->adicionarNodo(DSL);
  CPASL->adicionarNodo(ESL);
  x[0]=1.0/3.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;
  F=new CombinacionLineal(x,4,0.0);
  CPASL->asignarFuncion(F);

  CPASP->adicionarNodo(ISP);
  CPASP->adicionarNodo(RSP);
  CPASP->adicionarNodo(DSP);
  CPASP->adicionarNodo(ESP);
  x[0]=1.0/3.0;x[1]=1.0;x[2]=1.0;x[3]=1.0;
  F=new CombinacionLineal(x,4,0.0);
  CPASP->asignarFuncion(F);

}


//////////////////////////////////////////
void Estrategia::crearRed1()
{
/**
 * Implementación de la primera estrategia de cálculo para la Casa de la Calidad
 */

  // Generalidades
  Generalidades.adicionarPropiedad(wxT("Ubicación"));
//  Generalidades.modificarValor("xxx","Ubicación");

  // Declaración y construcción de los nodos del árbol
  NodoCalculo *bi0,*mi,*ti0,*RankingPosicion;
  NodoCalculo *gi,*vi,*wi,*RankingOrden;                 //Estas faltan *xi,*yj, Faltan las var de salida

  NodoCalculo *bi1;                                    // Competencia bik
  NodoCalculo *bi2;                                    // Competencia bik
  NodoCalculo *ti1;                                    // tik
  NodoCalculo *ti2;                                    // tik

  bi0=new NodoCalculo();
  mi=new NodoCalculo();
  ti0=new NodoCalculo();
  RankingPosicion=new NodoCalculo();
  gi=new NodoCalculo();
  vi=new NodoCalculo();
  wi=new NodoCalculo();
  RankingOrden=new NodoCalculo();

  bi1=new NodoCalculo();    // SON 2 Competidores
  bi2=new NodoCalculo();    // SON 2 Competidores
  ti1=new NodoCalculo();    // SON 2 Competidores
  ti2=new NodoCalculo();    // SON 2 Competidores

//  Definición de Variables

  Grafo.VarCalculada.Nombre=wxT("zi");            // corresponde al nodo superior en la Red1
  Etiqueta *Et; VariableLinguistica *Var;

  Var=&(Grafo.VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Nulo");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Indiferente");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Recomendado");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

// V: semántica provisional.

  bi0->VarCalculada.Nombre=wxT("bi0");
  Var=&(bi0->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);        //  Et->ND->trapecio(.1,.2,.3,.4)
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

  mi->VarCalculada.Nombre=wxT("mi");
  Var=&(mi->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Meta");Et->ND->trapecio(.4,.5,.5,.6);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Meta Ideal");Et->ND->trapecio(.6,.7,.7,.8);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Meta Fisiologica");Et->ND->trapecio(.8,1,1,1);Var->Etiquetas.Add(Et);


  bi1->VarCalculada.Nombre=wxT("bi-1");
  Var=&(bi1->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);        //  Et->ND->trapecio(.1,.2,.3,.4)
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

  bi2->VarCalculada.Nombre=wxT("bi-2");
  Var=&(bi2->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);        //  Et->ND->trapecio(.1,.2,.3,.4)
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

  ti0->VarCalculada.Nombre=wxT("ti0");
  Var=&(ti0->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

  // vector de ti

  ti1->VarCalculada.Nombre=wxT("ti-1");
  Var=&(ti1->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

  ti2->VarCalculada.Nombre=wxT("ti-2");
  Var=&(ti2->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

  RankingPosicion->VarCalculada.Nombre=wxT("RankingPosicion");
  Var=&(RankingPosicion->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Ultimo");Et->ND->trapecio(0,0,0,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Primero");Et->ND->trapecio(.7,1,1,1);Var->Etiquetas.Add(Et);


  gi->VarCalculada.Nombre=wxT("gi");
  Var=&(gi->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Nulo");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Indiferente");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Recomendado");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);


  vi->VarCalculada.Nombre=wxT("vi");
  Var=&(vi->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Poco Importante");Et->ND->trapecio(0,0,0,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1,1,1);Var->Etiquetas.Add(Et);


  wi->VarCalculada.Nombre=wxT("wi");
  Var=&(wi->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Nulo");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Indiferente");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Recomendado");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

  RankingOrden->VarCalculada.Nombre=wxT("RankingOrden");
  Var=&(RankingOrden->VarCalculada);
  Var->autodefinirRecto(4);
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Nula");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Baja");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alta");
  Et=&Var->Etiquetas.Item(3); Et->Label=wxT("Inminente");

//////////////////////////////////////////////////////////////////////////////

  // asignación de los nodos y funciones
  Funcion *F;
  float x[20];

  Grafo.adicionarNodo(RankingPosicion);
  Grafo.adicionarNodo(RankingOrden);
  x[0]=0.5;x[1]=0.5;
  F=new CombinacionLineal(x,2,0.0);
  Grafo.asignarFuncion(F);

  RankingPosicion->adicionarNodo(ti0);
  RankingPosicion->adicionarNodo(ti1);
  RankingPosicion->adicionarNodo(ti2);
  x[0]=0.5;x[0]=0.3;x[0]=0.2;
  F=new CombinacionLineal(x,2+1,0.0);
  RankingPosicion->asignarFuncion(F);

  ti0->adicionarNodo(bi0);
  ti0->adicionarNodo(mi);
  x[0]= .5;x[1]=.5;
  F=new CombinacionLineal(x,2,0.0);
  ti0->asignarFuncion(F);

   ti1->adicionarNodo(mi);
   ti1->adicionarNodo(bi1);
   x[0]=0.5;x[1]=0.5;
   F=new CombinacionLineal(x,2,0.0);
   ti1->asignarFuncion(F);

   ti2->adicionarNodo(mi);
   ti2->adicionarNodo(bi2);
   x[0]=0.5;x[1]=0.5;
   F=new CombinacionLineal(x,2,0.0);
   ti2->asignarFuncion(F);

  RankingOrden->adicionarNodo(wi);
  x[0]= 1;
  F=new CombinacionLineal(x,1,0.0);
  RankingOrden->asignarFuncion(F);

  wi->adicionarNodo(gi);
  wi->adicionarNodo(vi);
  wi->adicionarNodo(ti0);
  x[0]= .5;x[1]=.3;x[2]=.2;
  F=new CombinacionLineal(x,3,0.0);
  wi->asignarFuncion(F);

 }

void Estrategia::crearRed2()
{
/**
 * Implementación de la primera estrategia de cálculo para la Casa de la Calidad
 */

  // Generalidades
  Generalidades.adicionarPropiedad(wxT("Ubicación"));
//  Generalidades.modificarValor("xxx","Ubicación");



 // Declaración y construcción de los nodos del árbol
  NodoCalculo *bj0,*mj,*tj0,*RankingPosicionj;
  NodoCalculo *sjj,*wj,*RankingOrdenj;                 //Estas faltan *xi,*yj, Faltan las var de salida

  NodoCalculo *bj1;                                       // Competencia bjk
  NodoCalculo *bj2;
  NodoCalculo *tj1;
  NodoCalculo *tj2;
  NodoCalculo **cij;
  NodoCalculo **wi;
  NodoCalculo *zi;

  bj0=new NodoCalculo(); mj=new NodoCalculo(); tj0=new NodoCalculo();
  RankingPosicionj=new NodoCalculo();sjj=new NodoCalculo();
  wj=new NodoCalculo();RankingOrdenj=new NodoCalculo();

  bj1=new NodoCalculo();       // SON 2 Competidores
  bj2=new NodoCalculo();
  tj1=new NodoCalculo();      // SON 2 Competidores
  tj2=new NodoCalculo();
  cij=new NodoCalculo*[32];   // SON 23 Caracteristicas de Calidad
  wi=new NodoCalculo*[32];   // SON 23 Caracteristicas de Calidad
  zi=new NodoCalculo();       // Es el valor resultante de la Red1



//  Definición de Variables

  Grafo.VarCalculada.Nombre=wxT("zj");            // corresponde al nodo superior zj en la Red
  Etiqueta *Et; VariableLinguistica *Var;

  Var=&(Grafo.VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Nulo");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Indiferente");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Recomendado");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1.000);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);



// V: semántica provisional.

  bj0->VarCalculada.Nombre=wxT("bj0");
  Var=&(bj0->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);        //  Et->ND->trapecio(.1,.2,.3,.4)
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);


  mj->VarCalculada.Nombre=wxT("mj");
  Var=&(mj->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Meta");Et->ND->trapecio(.4,.5,.5,.6);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Meta Ideal");Et->ND->trapecio(.6,.7,.7,.8);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Meta Fisiologica");Et->ND->trapecio(.8,1,1,1);Var->Etiquetas.Add(Et);


   // vector de bj

  bj1->VarCalculada.Nombre=wxT("bj1");
  Var=&(bj1->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);


  bj2->VarCalculada.Nombre=wxT("bj2");
  Var=&(bj2->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);



  tj0->VarCalculada.Nombre=wxT("tj0");
  Var=&(tj0->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);


  tj1->VarCalculada.Nombre=wxT("tj1");
  Var=&(tj1->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);


  tj2->VarCalculada.Nombre=wxT("tj2");
  Var=&(tj2->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Muy Cercano");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Cercano");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Lejano");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Muy Lejano");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);



  RankingPosicionj->VarCalculada.Nombre=wxT("RankingPosicionj");
  Var=&(RankingPosicionj->VarCalculada);
  Var->limpiarListaEtiquetas();
  Et=new Etiqueta; Et->Label=wxT("Ultimo");Et->ND->trapecio(0,0,0,.5);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Medio");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
  Et=new Etiqueta; Et->Label=wxT("Primero");Et->ND->trapecio(.7,1,1,1);Var->Etiquetas.Add(Et);


                                                                 // Valor de wi de la Red1
//  wi->VarCalculada.Nombre=wxT("wi");
//  Var=&(wi->VarCalculada);
//  Var->limpiarListaEtiquetas();
//  Et=new Etiqueta; Et->Label=wxT("Nulo");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
//  Et=new Etiqueta; Et->Label=wxT("Indiferente");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
//  Et=new Etiqueta; Et->Label=wxT("Recomendado");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
//  Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
//  Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);




  // vector de cij
  int i;
  for(i=0;i<32;i++)
  {
    cij[i]=new NodoCalculo();
    wxString tmp;
    tmp << wxT("cij-") << i+1;
    cij[i]->VarCalculada.Nombre=tmp;
    Var=&(cij[i]->VarCalculada);
    Var->limpiarListaEtiquetas();
    Et=new Etiqueta; Et->Label=wxT("Fuertemente Negativa");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Negativa");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Neutra");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Positiva");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Fuertemente Positiva");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);

    wi[i]=new NodoCalculo();
    tmp=wxT("");
    tmp << wxT("wi-") << i+1;
    wi[i]->VarCalculada.Nombre=tmp;
    Var=&(wi[i]->VarCalculada);
    Var->limpiarListaEtiquetas();
    Et=new Etiqueta; Et->Label=wxT("Nulo");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Indiferente");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Recomendado");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);
  }

  sjj->VarCalculada.Nombre=wxT("sjj");
    Var=&(sjj->VarCalculada);
    Var->limpiarListaEtiquetas();
    Et=new Etiqueta; Et->Label=wxT("Fuertemente Negativa");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Negativa");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Neutra");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Positiva");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Fuertemente Positiva");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);



  wj->VarCalculada.Nombre=wxT("wj");
    Var=&(wj->VarCalculada);
    Var->limpiarListaEtiquetas();
    Et=new Etiqueta; Et->Label=wxT("Nulo");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Indiferente");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Recomendado");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
    Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);



  RankingOrdenj->VarCalculada.Nombre=wxT("RankingOrdenj");
    Var=&(RankingOrdenj->VarCalculada);
    Var->autodefinirRecto(4);
    Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Nula");
    Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Baja");
    Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alta");
    Et=&Var->Etiquetas.Item(3); Et->Label=wxT("Inminente");




 zi->VarCalculada.Nombre=wxT("zi");                // corresponde al nodo superior en la Red1
   Var=&(zi->VarCalculada);
   Var->limpiarListaEtiquetas();
   Et=new Etiqueta; Et->Label=wxT("Nulo");Et->ND->trapecio(0,0,0,.3);Var->Etiquetas.Add(Et);
   Et=new Etiqueta; Et->Label=wxT("Indiferente");Et->ND->trapecio(0,.3,.3,.5);Var->Etiquetas.Add(Et);
   Et=new Etiqueta; Et->Label=wxT("Recomendado");Et->ND->trapecio(.3,.5,.5,.7);Var->Etiquetas.Add(Et);
   Et=new Etiqueta; Et->Label=wxT("Importante");Et->ND->trapecio(.5,.7,.7,1);Var->Etiquetas.Add(Et);
   Et=new Etiqueta; Et->Label=wxT("Muy Importante");Et->ND->trapecio(.7,1.000,1.000,1.000);Var->Etiquetas.Add(Et);



//////////////////////////////////////////////////////////////////////////////

   // asignación de los nodos y funciones
  Funcion *F;
  float x[100];

  Grafo.adicionarNodo(RankingPosicionj);
  Grafo.adicionarNodo(RankingOrdenj);
  Grafo.adicionarNodo(sjj);
  Grafo.adicionarNodo(zi);
  x[0]=0.08;x[1]=0.5;x[2]=0.5;x[2]=0.5;
  F=new CombinacionLineal(x,4,0);
  Grafo.asignarFuncion(F);


  RankingPosicionj->adicionarNodo(tj0);
  RankingPosicionj->adicionarNodo(tj1);
  RankingPosicionj->adicionarNodo(tj2);
  x[0]= .2;x[1]=.3;x[2]=.1;
  F=new CombinacionLineal(x,3,0);
  RankingPosicionj->asignarFuncion(F);


  tj0->adicionarNodo(mj);
  tj0->adicionarNodo(bj0);
  x[0]= .2;x[1]=.3;
  F=new CombinacionLineal(x,2,0);
  tj0->asignarFuncion(F);

  tj1->adicionarNodo(mj);
  tj1->adicionarNodo(bj1);
  x[0]= .2;x[1]=.3;
  F=new CombinacionLineal(x,2,0);
  tj1->asignarFuncion(F);

  tj2->adicionarNodo(mj);
  tj2->adicionarNodo(bj2);
  x[0]= .2;x[1]=.3;
  F=new CombinacionLineal(x,2,0);
  tj2->asignarFuncion(F);

  RankingOrdenj->adicionarNodo(wj);
  x[0]= .2;x[1]=.3;x[2]=.1;x[3]=.05;x[4]=.15;x[5]=.15;x[6]=.05;
  F=new CombinacionLineal(x,1,0);
  RankingOrdenj->asignarFuncion(F);

    for(i=0;i<32;i++)
    {
      wj->adicionarNodo(cij[i]);
      wj->adicionarNodo(wi[i]);
      x[i]=1.0/64.0;
      x[i+1]=1.0/64.0;
    }
//  x[0]= .2;x[1]=.3;x[2]=.1;x[3]=.05;x[4]=.15;x[5]=.15;x[6]=.05;
  F=new CombinacionLineal(x,64,0);
  wj->asignarFuncion(F);

 }

void Estrategia::crearRedLink1()
{
/**
 * Implementación de la primera estrategia de cálculo con links
 */

  // Generalidades

 // Declaración y construcción de los nodos del árbol
  NodoCalculo *N1_2,*N1_3;

  N1_2=new NodoCalculo();
  N1_3=new NodoCalculo();
//  Definición de Variables

  Grafo.VarCalculada.Nombre=wxT("N1_1");            // corresponde al nodo superior en la Red1
  Etiqueta *Et; VariableLinguistica *Var;

  Var=&(Grafo.VarCalculada);
  Var->autodefinirRecto(3);
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alto");

  Var=&(N1_2->VarCalculada);
  Var->autodefinirRecto(3);
  Var->Nombre=wxT("N1_2");
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alto");

  Var=&(N1_3->VarCalculada);
  Var->autodefinirRecto(3);
  Var->Nombre=wxT("N1_3");
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alto");

//////////////////////////////////////////////////////////////////////////////

   // asignación de los nodos y funciones
  Funcion *F;
  float x[10];

  Grafo.adicionarNodo(N1_2);
  Grafo.adicionarNodo(N1_3);
  x[0]=0.5;x[1]=0.5;
  F=new CombinacionLineal(x,2,0);
  Grafo.asignarFuncion(F);

}

void Estrategia::crearRedLink2()
{
/**
 * Implementación de la segunda estrategia de cálculo con links
 */

  // Generalidades

 // Declaración y construcción de los nodos del árbol
  NodoCalculo *N2_2,*N2_3;

  N2_2=new NodoCalculo();
  N2_3=new NodoCalculo();
//  Definición de Variables

  Grafo.VarCalculada.Nombre=wxT("N2_1");            // corresponde al nodo superior en la Red1
  Etiqueta *Et; VariableLinguistica *Var;

  Var=&(Grafo.VarCalculada);
  Var->autodefinirRecto(3);
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alto");

  Var=&(N2_2->VarCalculada);
  Var->autodefinirRecto(3);
  Var->Nombre=wxT("N2_2");
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alto");

  Var=&(N2_3->VarCalculada);
  Var->autodefinirRecto(3);
  Var->Nombre=wxT("N2_3");
  Et=&Var->Etiquetas.Item(0); Et->Label=wxT("Bajo");
  Et=&Var->Etiquetas.Item(1); Et->Label=wxT("Medio");
  Et=&Var->Etiquetas.Item(2); Et->Label=wxT("Alto");

//////////////////////////////////////////////////////////////////////////////

   // asignación de los nodos y funciones
  Funcion *F;
  float x[10];

  Grafo.adicionarNodo(N2_2);
  Grafo.adicionarNodo(N2_3);
  x[0]=0.5;x[1]=0.5;
  F=new CombinacionLineal(x,2,0);
  Grafo.asignarFuncion(F);

  N2_3->FormaDeCalculo=2;
  N2_3->EstrategiaCalculo=wxT("Metodología 1");

}

