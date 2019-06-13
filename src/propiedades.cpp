/***************************************************************************
                          propiedades.cpp  -  description
                             -------------------
    begin                : jue abr 24 2003
    copyright            : (C) 2003 by Oscar G. Duarte V.
    email                : ogduarte@ing.unal.edu.co
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   Este programa ha sido diseñdo por Oscar G. Duarte V. por encargo del *
 *   Departamento de Ciencias de la Computación e Inteligencia             *
 *   Artificial de la Universidad de Granada.                              *      
 *                                                                         *
 ***************************************************************************/

#include "propiedades.h"

Propiedades::Propiedades()
{
}

Propiedades::~Propiedades()
{
  limpiarPropiedades();
}

/**
 * Adiciona la propiedad cad, de valor "" en la posición loc.
 * si loc < 0 se ubica al final del arreglo
 */
void Propiedades::adicionarPropiedad(const wxString &cad,int loc)
{
  wxString Nombre,Valor;
  Nombre=cad;
  Valor=wxT("");
  if(loc <0 || loc > tamano())
  {
    NombresPropiedad.Add(Nombre);
    ValoresPropiedad.Add(Valor);
  }
  else
  {
    NombresPropiedad.Insert(Nombre,loc);
    ValoresPropiedad.Insert(Valor,loc);
  }
}

/**
 * Elimina la propiedad de la posición loc, y su valor
 */
void Propiedades::eliminarPropiedad(int loc)
{
  if(loc>=0 && loc < tamano())
  {
    NombresPropiedad.RemoveAt(loc);
    ValoresPropiedad.RemoveAt(loc);
  }
}

/**
 * Cambia el valor de la propiedad ubicada en loc. el nuevo valor es cad
 */
void Propiedades::modificarValor(const wxString cad,int loc)
{
  if(loc>=0 && loc < tamano())
  {
    ValoresPropiedad.Item(loc)=cad;
  }
}

/**
 * Cambia el valor de la propiedad de nombre prop. El nuevo valor es cad
 */
void Propiedades::modificarValor(const wxString cad, const wxString prop)
{
  int i,tam;
  tam=tamano();
  for(i=0;i<tam;i++)
  {
    if(nombre(i)==prop)
    {
      modificarValor(cad,i);
      i=tam;
    }
  }
}

/**
 * Cambia el nombre de la propiedad ubicada en loc. el nuevo valor es cad
 */
void Propiedades::modificarNombre(const wxString cad,int loc)
{
  if(loc>=0 && loc < tamano())
  {
    NombresPropiedad.Item(loc)=cad;
  }
}

/**
 * Cambia el nombre de la propiedad de nombre prop. El nuevo valor es cad
 */
void Propiedades::modificarNombre(const wxString cad, const wxString prop)
{
  int i,tam;
  tam=tamano();
  for(i=0;i<tam;i++)
  {
    if(nombre(i)==prop)
    {
      modificarNombre(cad,i);
      i=tam;
    }
  }
}

/**
 * Devuelve el nombre de la propiedad ubicada en loc
 */
wxString Propiedades::nombre(int loc)
{
  wxString cad=NombresPropiedad.Item(loc);
  return cad;
}

/**
 * Devuelve el valor de la propiedad pr
 */
wxString Propiedades::valor(wxString pr)
{
  wxString cad=wxT("");
  int i,tam;
  tam=tamano();
  for(i=0;i<tam;i++)
  {
    if (nombre(i)==pr)
    {
      cad=valor(i);
    }
  }
  return cad;
}

/**
 * Devuelve el valor de la propiedad ubicada en loc
 */
wxString Propiedades::valor(int loc)
{
  wxString cad;
  if(loc<0)
  {
    cad=wxT("MM");
  }else
  {
    cad=ValoresPropiedad.Item(loc);
  }
  return cad;
}

/**
 * Devuelve el número de propiedades
 */
int Propiedades::tamano()
{
  return NombresPropiedad.GetCount();
}

/**
 * Destruye todas las propiedades y sus valores
 */
void Propiedades::limpiarPropiedades()
{
  NombresPropiedad.Clear();
  ValoresPropiedad.Clear();
}

wxArrayString Propiedades::listaNombres()
{
  wxArrayString lista;
  int i,tam;
  tam=NombresPropiedad.GetCount();
  for(i=0;i<tam;i++)
  {
    lista.Add(NombresPropiedad.Item(i));
  }
  return lista;
}

wxArrayString Propiedades::listaValores()
{
  wxArrayString lista;
  int i,tam;
  tam=ValoresPropiedad.GetCount();
  for(i=0;i<tam;i++)
  {
    lista.Add(ValoresPropiedad.Item(i));
  }
  return lista;
}
  

void Propiedades::write(Mi_ofpstream &str)
{
  int i,tam;
  tam=tamano();
  str << tam;
  for(i=0;i<tam;i++)
  {
	  str << nombre(i);
	  str << valor(i);
  }
}

void Propiedades::read(Mi_ifpstream &str)
{
  limpiarPropiedades();
  int i,tam;
  str >> tam;
  for(i=0;i<tam;i++)
  {
    wxString nom,val;
	  str >> nom;
	  str >> val;
    adicionarPropiedad(nom);
    modificarValor(val,i);
  }
}

void Propiedades::operator=(Propiedades& other)
{
  limpiarPropiedades();
  int i,tam;
  tam=other.tamano();
  for(i=0;i<tam;i++)
  {
    wxString nom,val;
	  nom=other.nombre(i);
	  val=other.valor(i);
    adicionarPropiedad(nom);
    modificarValor(val,i);
  }
}
