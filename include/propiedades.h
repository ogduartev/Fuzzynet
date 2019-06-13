/***************************************************************************
                          propiedades.h  -  description
                             -------------------
    begin                : jue abr 24 2003
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

#ifndef PROPIEDADES_H
#define PROPIEDADES_H

#include <wx/wx.h>
#include "mi_fstream.h"

/**
 *Implementa parejas de cadenas de caracteres, para ser usados como propiedaes genéricas de Casos y/o Estrategias
 * ATENCION : Falta documentar
 * ATENCION : Falta manejo de archivos.
 */

class Propiedades {
public: 
	Propiedades();
	~Propiedades();

  void adicionarPropiedad(const wxString &cad,int loc=-1);
  void eliminarPropiedad(int loc);
  void modificarValor(const wxString cad,int loc);
  void modificarValor(const wxString cad, const wxString prop);
  void modificarNombre(const wxString cad,int loc);
  void modificarNombre(const wxString cad, const wxString prop);
  wxString nombre(int loc);
  wxString valor(wxString pr);
  wxString valor(int loc);
  int tamano();
  void limpiarPropiedades();
  wxArrayString listaNombres();
  wxArrayString listaValores();

	void write(Mi_ofpstream &str);
	void read(Mi_ifpstream &str);

	void operator=(Propiedades& other);

protected:
  wxArrayString NombresPropiedad;
  wxArrayString ValoresPropiedad;

};

#endif
