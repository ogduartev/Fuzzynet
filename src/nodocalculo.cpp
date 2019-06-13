/***************************************************************************
                          nodocalculo.cpp  -  description
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

#include "proyecto.h"
#include "nodocalculo.h"
#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(ListaNodos);

/**
 * Fija FormaDeCalculo=0 y construye FuncionCalculo como x[0]+x[1]
 */
NodoCalculo::NodoCalculo()
{
  ProyectoTotal=NULL;
  FormaDeCalculo=1;
  float x;
  FuncionCalculo=new CombinacionLineal(&x,0,0.0);
  Nivel=1;
  PosicionEnNivel=1;
  OffsetNivel=0;
  OffsetPosicionEnNivel=0;
  NombreExtendido=wxT("");
}

/**
 * Destruye FuncionCalculo
 */
NodoCalculo::~NodoCalculo()
{
//  eliminarNodosAbajo(arbol());    // si se necesita debe llamarse antes del destructor
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Detach(0);
  }
  tam=NodosPadre.GetCount();
  for(i=0;i<tam;i++)
  {
    NodosPadre.Detach(0);
  }
  delete FuncionCalculo;
}

/**
 * Calcula el valor del Nodo segn FormaDeCalculo,
 * 0:Con el Valor de VarCalculada;  1: Aplicando FuncionCalculo a las variable de NodosDeCalculo
 *
 * Debe asegurarse que el nmero de Hijos almacenados en NodosDecalculo
 * sea igual al Orden de FuncionCalculo. Si no son Iguales el resultado
 * se toma como el valor de VarCalculada, independientemente de FormaDeCalculo
 */
NumeroDifuso* NodoCalculo::calcular()
{
  NumeroDifuso *Num;
  int i,tam,tam2;
  switch(FormaDeCalculo)
  {
    case 0 : Num=VarCalculada.valor();
            break;
    case 1 :
            tam=NodosDeCalculo.GetCount();
            tam2=FuncionCalculo->Orden;
            if(tam==0||!(tam==tam2))
            {
              Num=VarCalculada.valor();
            }else
            {
              Num=new NumeroDifuso;
              NumeroDifuso **X;
              X=new NumeroDifuso*[tam];
              for(i=0;i<tam;i++)
              {
                X[i]=NodosDeCalculo.Item(i).calcular();
              }
              FuncionCalculo->directaDifusa(Num,X);
              for(i=0;i<tam;i++)
              {
                delete X[i];
              }
              delete X;
            }
            break;
    case 2:
            Proyecto* Pry;
            Pry=getProyecto();
            if(Pry==NULL)
            {
              Num=VarCalculada.valor();
            }else
            {
              Num=Pry->calcularCasoEstrategia(CasoCalculo,EstrategiaCalculo);
            }
            break;
    default : Num=VarCalculada.valor();
            break;
  }
  return Num;
}


/**
 * Produce una copia de varCalculada en VarTemporal.Se ejecuta en sus hijos
 */
void NodoCalculo::copiaTemporal(wxString C)
{
  VarTemporal=VarCalculada;
  CasoCalculo=C;
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Item(i).copiaTemporal(C);
  }
}

/**
 * Restaura varCalculada a partir de VarTemporal.Se ejecuta en sus hijos
 */
void NodoCalculo::restauraCopiaTemporal()
{
  VarCalculada=VarTemporal;
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Item(i).restauraCopiaTemporal();
  }



}

/**
 * fija VarCalculada.TipoDeValor=0. .Se ejecuta en sus hijos
 */
void NodoCalculo::fijarIndefinido()
{
  VarCalculada.TipoDeValor=0;
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Item(i).fijarIndefinido();
  }
}

void NodoCalculo::copiarVariableLinguistica(ListaVariables *Modelo)
{
  int i,tam;
  tam=Modelo->GetCount();
  for(i=0;i<tam;i++)
  {
    if(VarCalculada.Nombre==Modelo->Item(i).Nombre)
    {
      VarCalculada=Modelo->Item(i);
      i=tam;
    }
  }
  tam=NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Item(i).copiarVariableLinguistica(Modelo);
  }
}

void  NodoCalculo::asignarFuncion(Funcion *f)
{
  if(f!=NULL)
  {
    if (FuncionCalculo!=NULL)
    {
      delete FuncionCalculo;
    }
    FuncionCalculo=f;
    FormaDeCalculo=1;
  }
}

/**
 * Asigna a caso un conjunto de variables liguisticas iguales a aquellas variables
 * de la estrategia que deban conocerse para efectuar el cálculo, es decir, aquellas
 * que no tienen nodos hijos, o aquellas que no se calculan con los hijos.
 */
void NodoCalculo::llenarCasoIndefinido(Caso *caso)
{
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  if(tam==0 || FormaDeCalculo==0)
  {
    int j,tam2,flag=0;;
    tam2=caso->Variables.GetCount();
    for(j=0;j<tam2;j++)
    {
      if(caso->Variables.Item(j).Nombre==VarCalculada.Nombre)
      {
        flag=1;
        j=tam2;
      }
    }
    if(flag==0)
    {
       VariableLinguistica *Var;
       Var=new VariableLinguistica;
       *Var=VarCalculada;
       Var->TipoDeValor=0;
       caso->Variables.Add(Var);
    }
    tam=0;
  }
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Item(i).llenarCasoIndefinido(caso);
  }
}

/**
 * Adiciona un nodo hijo. verifica que no sea NULL y le asigna un NodoPadre
 * Devuelve 0 si éxito, 1 si NULL, 2 si cierra ciclo, 3 si hay otro nodo (diferente) cuya

 * Variable calculada tenga el mismo nombre.
 * 4 si ya hay otro nodo que sea hijo directo con el mismo nombre
 * En el ltimo caso se crea un enlace al nodo ya existente, no se enlaza nod.
 */
int NodoCalculo::adicionarNodo(NodoCalculo *nod,int loc)
{
  int res;

// cálculo necesario para verificar si res==3;

  NodoCalculo* NodTemp;
  if(nod!=NULL)
  {
    NodTemp=arbol()->buscarNodo(nod->VarCalculada.Nombre);
  }else
  {
    NodTemp=NULL;
  }

// verificaciones

  if(nod==NULL)
  {
    res=1;
  }else if(nod->buscarNodo(this)!=NULL)

  {
    res=2;
  }else if(nod->buscarNodo(this->VarCalculada.Nombre)!=NULL)
  {
    res=2;
  }else if(NodTemp!=NULL && NodTemp!=nod)
  {
    NodTemp->NodosPadre.Add(this);
    NodosDeCalculo.Add(NodTemp);
    FuncionCalculo->adicionarOrden(FuncionCalculo->Orden+1);
    res=3;
  }else
  {
    int i,tam,flag4=0;
    tam=NodosDeCalculo.GetCount();
    for(i=0;i<tam;i++)
    {
      if(&NodosDeCalculo.Item(i)==nod)
      {
        flag4=1;


        i=tam;
      }
    }
    if(flag4==1)
    {
      res=4;
    }else
    {
     nod->NodosPadre.Add(this);
      if(loc<0 || loc >NodosDeCalculo.GetCount())
      {
        NodosDeCalculo.Add(nod);
        FuncionCalculo->adicionarOrden(FuncionCalculo->Orden+1);
      }else
      {
        NodosDeCalculo.Insert(nod,loc);
        FuncionCalculo->adicionarOrden(loc);
      }
      res=0;
    }
  }
  NodTemp=NULL;
  return res;
}

/**
 * Elimina y destruye todos los nodos inferiores
 * La rutina se ha diseñado para el nodo superior del árbol
 */
void NodoCalculo::eliminarNodosAbajoTodos()
{
  int i,prof=profundidad();
  for(i=prof-1;i>1;i--)
  {
    ListaNodos ListaTmp;
    llenarArreglo(&ListaTmp,i);
    ListaTmp.Clear();
  }
}

/**
 * Elimina y destruye todos los nodos inferiores que no dependan del nodo nod
 */
void NodoCalculo::eliminarNodosAbajo(NodoCalculo *nod)
{
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  for(i=tam-1;i>=0;i--)
  {
    int j,tam2;

    tam2=NodosDeCalculo.Item(i).NodosPadre.GetCount();
    if(tam2==1 && NodosDeCalculo.Item(i).NodosDeCalculo.GetCount()==0)
    {
//      FuncionCalculo->eliminarOrden(i);
      NodosDeCalculo.RemoveAt(i);
    }else
    {
      for(j=tam2-1;j>=0;j--)
      {
        if(&(NodosDeCalculo.Item(i).NodosPadre.Item(j))==this)
        {
          NodoCalculo *NodTemp;



          NodTemp=&NodosDeCalculo.Item(i);
          NodosDeCalculo.Item(i).NodosPadre.RemoveAt(j);
          NodosDeCalculo.Detach(i);
          FuncionCalculo->eliminarOrden(i);
          if(NodTemp->buscarNodoArriba(nod)==0)
          {
            NodTemp->eliminarNodosAbajo(nod);
            delete NodTemp;
          }
          j=0;
        }
      }
    }
  }
}

/**
 * Elimina el nodo inferior de la posición i.
 * Verifica si debe destruirse o mantenerse
 */
void NodoCalculo::eliminarNodoInferior(int loc)
{
  if (loc >= NodosDeCalculo.GetCount()){return;}
  NodoCalculo *NodInf;
  NodInf=&NodosDeCalculo.Item(loc);
  int i,tam;
  tam=NodInf->NodosPadre.GetCount();
  for(i=0;i<tam;i++)
  {
    if(&NodInf->NodosPadre.Item(i)==this)
    {
      NodInf->NodosPadre.Detach(i);
      i--;
      tam--;
    }
  }
  NodosDeCalculo.Detach(loc);
  FuncionCalculo->eliminarOrden(loc);
  if(arbol()->buscarNodo(NodInf)==NULL)
  {
    tam=NodInf->NodosDeCalculo.GetCount();
    for(i=0;i<tam;i++)
    {
      int j,tam2;
      tam2=NodInf->NodosDeCalculo.Item(i).NodosPadre.GetCount();
      if(tam>0)
      {
        for(j=0;j<tam2;j++)
        {
          if(&NodInf->NodosDeCalculo.Item(i).NodosPadre.Item(j)==NodInf)
          {
            NodInf->NodosDeCalculo.Item(i).NodosPadre.Detach(j);
            j--;
            tam2--;
          }
        }
      }
    }
    delete NodInf;
  }
}

/**
 * encuentra el nodo superior del arbol

 */
NodoCalculo* NodoCalculo:: arbol()
{
  if(NodosPadre.GetCount()==0)
  {
    return this;
  }else
  {
    return NodosPadre.Item(0).arbol();
  }
}

/**
 * Calcula el valor del Nodo para el caso especificado por caso
 */
NumeroDifuso * NodoCalculo::calcularCaso(Caso *caso)
{
  NumeroDifuso *Num;
  copiaTemporal(caso->Nombre);
  fijarIndefinido();
  copiarVariableLinguistica(&caso->Variables);
  Num=calcular();
  restauraCopiaTemporal();
  return Num;
}

/**
 * Busca dentro del árbol un nodo cuya variable calculada tenga
 * por nombre nom VarCalculada.Nombre==nom. retorna NULL si no lo encuentra
 */
NodoCalculo* NodoCalculo::buscarNodo(wxString nom)
{
  NodoCalculo* Nod=NULL;
  NodoCalculo* Nod2=NULL;
  if(VarCalculada.Nombre==nom)
  {
    Nod=this;
  }else
  {
    int i,tam;
    tam=NodosDeCalculo.GetCount();
    for(i=0;i<tam;i++)
    {
      Nod2=NodosDeCalculo.Item(i).buscarNodo(nom);
      if(Nod2!=NULL)
      {
        Nod=Nod2;
        i=tam;
      }
    }
  }
  return Nod;
}

/**

 * Busca dentro del árbol un nodo cuyo apuntador sea nod
 */
NodoCalculo* NodoCalculo::buscarNodo(NodoCalculo* nod)
{
  NodoCalculo* Nod=NULL;
  NodoCalculo* Nod2;
  if(nod==this)
  {
    Nod=this;
  }else
  {
    int i,tam;
    tam=NodosDeCalculo.GetCount();
    for(i=0;i<tam;i++)
    {
      Nod2=NodosDeCalculo.Item(i).buscarNodo(nod);
      if(Nod2!=NULL)
      {
        Nod=Nod2;
      }
    }
  }
  return Nod;
}

/**
 * retorna 0: si nod no es padre,  1 si es padre
 */
int NodoCalculo::buscarNodoArriba(NodoCalculo* nod)
{
  if(NodosPadre.GetCount()==0)
  {

    return 0;
  }else
  {
    int i,tam,r;
    tam=NodosPadre.GetCount();
    for(i=0;i<tam;i++)
    {
      if(&NodosPadre.Item(i)==nod)
      {
        return 1;
      }
    }
    for(i=0;i<tam;i++)
    {
      {
        r=NodosPadre.Item(i).buscarNodoArriba(nod);
        if(r==1)
        {
          return 1;
        }
      }
    }
    return 0;
  }
}

/**
 * Hace Nivel=0 en el nodo y en todos los nodos hijos
 */
void NodoCalculo::limpiarNivel()
{
  Nivel=0;
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Item(i).limpiarNivel();
  }
}

/**
 * Calcula Nivel en el Nodo y en todos los nodos hijos. Esta función debe
 * ejecutarla el Nodo Padre. Se asume que todos los valores de Nivel son cero
 * \see limpiarNivel
 */
void NodoCalculo::calcularNivel()
{
  if(NodosPadre.GetCount()==0)
  {
    Nivel=1;
  }
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    if(NodosDeCalculo.Item(i).Nivel < Nivel+1)
    {
//      NodosDeCalculo.Item(i).Nivel = Nivel+1;
      NodosDeCalculo.Item(i).Nivel = Nivel+1+NodosDeCalculo.Item(i).OffsetNivel;
    }








    NodosDeCalculo.Item(i).calcularNivel();
  }

}

/**
 * Llena Lista con todos los nodos de nivel Niv. Si Niv < 1  (por defecto) llena
 * con todos los nodos
 */
void NodoCalculo::llenarArreglo(ListaNodos *Lista,int Niv)
{
  if(Niv < 1 || Niv==Nivel)
  {
    // revisar si ya está salvado
    int i,tam,flag=0;
    tam=Lista->GetCount();

    for(i=0;i<tam;i++)
    {

      if (&Lista->Item(i)==this)

      {
        flag=1;
        i=tam;
      }
    }
    if(flag==0)

    {
      Lista->Add(this);
    }
  }
  int i,tam;
  tam=NodosDeCalculo.GetCount();
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Item(i).llenarArreglo(Lista,Niv);
  }
}

/**
 * Calcula el número de niveles del árbol desde este Nodo
 */
int NodoCalculo::profundidad()
{
  ListaNodos Lista;
  llenarArreglo(&Lista,-1);
  int i,tam,prof=-1;
  tam=Lista.GetCount();
  for(i=0;i<tam;i++)
  {

    if (Lista.Item(i).Nivel>prof)
    {
      prof=Lista.Item(i).Nivel;
    }
  }
  for(i=0;i<tam;i++)

  {
    Lista.Detach(0);
  }
  return prof-Nivel;  // sólo se calcula la profundidad desde este Nodo
}

/**
 * Actualiza PosicionEnNivel parael nodo y para cada nodo debajo del actual
 * Supone que Nivel está actualizado
 */
void NodoCalculo::calcularPosicionEnNivel()
{

  int i,tam,prof=profundidad();
  tam=prof+1;
  for(i=0;i<tam;i++)
  {
    ListaNodos Lista;
    llenarArreglo(&Lista,Nivel+i);

    int acumulado=0;
    int j,tam2;
    tam2=Lista.GetCount();
    for(j=0;j<tam2;j++)
    {
      acumulado=acumulado+1+Lista.Item(0).OffsetPosicionEnNivel;
//      Lista.Item(0).PosicionEnNivel=j+1;
      Lista.Item(0).PosicionEnNivel=acumulado;
      Lista.Detach(0);
    }
  }
}

Proyecto* NodoCalculo::getProyecto()
{
  return arbol()->ProyectoTotal;
}

/**
 * evalua si se puede registrar un enlace a la estrategia de nombre Est
 * retorna true si es permitido y false si no es permitido.
 */
bool NodoCalculo::evaluarEnlace(wxString Est)
{
  NodoCalculo *Arbol,*ArbolEnlace=NULL;
  Arbol=arbol();
  Proyecto *Pry;
  Pry=getProyecto();
  if(Pry==NULL)
  {
    return false;
  }else
  {
    int i,tam;
    tam=Pry->Estrategias.GetCount();
    for(i=0;i<tam;i++)
    {
      if(Pry->Estrategias.Item(i).Nombre==Est)
      {
        ArbolEnlace=&Pry->Estrategias.Item(i).Grafo;
        i=tam;
      }
    }
    if(ArbolEnlace==NULL)
    {
      return NULL;
    }else
    {
      return ArbolEnlace->verificarEnlace(Arbol);
    }
  }
  
}

/*
 * busca el Nodo Arbol Origen dentro de los enlaces de sus hijos
 * si no lo encuentra retorna true. si lo encuentra retorna false
 */
bool NodoCalculo::verificarEnlace(NodoCalculo *ArbolOrigen)
{
  if(this==ArbolOrigen)
  {
    return false;
  }
  if(NodosDeCalculo.GetCount()==0 && FormaDeCalculo!=2)
  {
    return true;
  }
  bool f=true;
  ListaNodos Lista;
  llenarArreglo(&Lista);
  int i,tam;
  tam=Lista.GetCount();
  for(i=0;i<tam;i++)
  {
    NodoCalculo *Nod;
    Nod=&Lista.Item(0);
    Lista.Detach(0);
    if(Nod!=this && Nod->FormaDeCalculo==2)
    {
      int j,tam2;
      Proyecto *Pry;
      Pry=getProyecto();
      if (Pry==NULL)
      {
        f=false;
      }
      if(f)
      {
        tam2=Pry->Estrategias.GetCount();
        for(j=0;j<tam2;j++)
        {
          if(Pry->Estrategias.Item(j).Nombre==Nod->EstrategiaCalculo)
          {
            f=Pry->Estrategias.Item(j).Grafo.verificarEnlace(ArbolOrigen);
            if(!f)
            {
              j=tam2;
            }
          }
        }
      }
      if(!f)
      {
        i=tam;
      }
    }
  }
  tam=Lista.GetCount();
  for(i=0;i<tam;i++)
  {
    Lista.Detach(0);
  }
  return f;
}


void NodoCalculo::write(Mi_ofpstream &str)
{
  str << VarCalculada.Nombre;
  str << NombreExtendido;
  str << Descripcion;
  str << Nivel;
  str << PosicionEnNivel;
  str << OffsetNivel;
  str << OffsetPosicionEnNivel;
  str << EstrategiaCalculo;


  str << FormaDeCalculo;

  VarCalculada.write(str);

  int i,tam;
  tam=NodosDeCalculo.GetCount();
  str << tam;
  for(i=0;i<tam;i++)
  {
    NodosDeCalculo.Item(i).write(str);
  }
  FuncionCalculo->write(str);
}

/**
 * Rutina para leer un Grafo. Se crean más nodos de los necesarios, porque puede haber
 * múltiples padres. Se necesita una rutina externa que verifique esto. el arreglo ListaTmp
 * acumula apuntadores a todos los nodos creados para posibilitar esa verificación. La
 * verificación está implementada en Estrategia::read()
 * @see Estrategia::read()
 */

void NodoCalculo::read(Mi_ifpstream &str,ListaNodos* ListaTmp)
{
  str >> VarCalculada.Nombre;
  str >> NombreExtendido;
  str >> Descripcion;
  str >> Nivel;
  str >> PosicionEnNivel;
  str >> OffsetNivel;
  str >> OffsetPosicionEnNivel;
  str >> EstrategiaCalculo;

  int temp;
  str >> temp;    // se emplea porque asignarFuncion() redefine FormaDeCalculo

  FormaDeCalculo=temp;

  
  VarCalculada.read(str);

  int i,tam;
  NodosDeCalculo.Clear();
  str >> tam;
  for(i=0;i<tam;i++)
  {
    NodoCalculo *Nod;
    Nod=new NodoCalculo;
    Nod->NodosPadre.Add(this);  //OJO solución fuera de adicionarNodo.... no usa verifica.... debe arreglarse
    Nod->read(str,ListaTmp);
//    NodoCalculo *NodTemp=NULL;
//    NodTemp=arbol()->buscarNodo(Nod->VarCalculada.Nombre);
    adicionarNodo(Nod);
    ListaTmp->Add(Nod);
  }
  
  for(i=0;i<NodosPadre.GetCount();i++)
  {
    int j;
    for(j=i;NodosPadre.GetCount();j++)
    {
      if(&NodosPadre.Item(i)==&NodosPadre.Item(j))
      {
        NodosPadre.Detach(j);
        j--;
      }
    }
    
  }
  Funcion *Ftmp;
  Ftmp=FuncionCalculo->read(str);
  asignarFuncion(Ftmp);
  Ftmp=NULL;
  while(FuncionCalculo->Orden > NodosDeCalculo.GetCount())
  {
    FuncionCalculo->eliminarOrden(FuncionCalculo->Orden);
  };
  while(FuncionCalculo->Orden < NodosDeCalculo.GetCount())
  {
    FuncionCalculo->adicionarOrden(FuncionCalculo->Orden);

  };
  FormaDeCalculo=temp;

}

