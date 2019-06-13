/***************************************************************************
                          reportelatex.h  -  description
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

#ifndef REPORTELATEX_H
#define REPORTELATEX_H

#include "reporte.h"

/**Genera Reportes en formato LaTex
  *@author 
  */

class ReporteLatex : public Reporte  {
public: 
	ReporteLatex();
	~ReporteLatex();

  wxString remplazo(wxString c);
  
  void encabezado(wxTextFile *f, wxString Tit);
  void cierre(wxTextFile *f);
  void seccion(wxTextFile *f,wxString Sec);
  void parrafo(wxTextFile *f, wxString Par);
  void lista(wxTextFile *f, wxArrayString Nom, wxArrayString Des);
  wxString enlace(wxString Dir, wxString Dato);
  wxString enlaceTabla(int Tab);
  wxString enlaceFigura(int Fig);
  wxString destino(wxString Dir, wxString Dato);
  wxString crearCadenaArchivo(wxString Dir);
  void incluirArchivo(wxTextFile *f, wxString Origen);
  void tablaContenido();
  void escribirFuncion(wxTextFile *f,Funcion *F);
  void tabla(wxTextFile *f,wxArrayString *lista, int tam, wxString Nombre);
  bool figuraVariable(VariableLinguistica *Var,NumeroDifuso *Num,int entrada=1);
  void incluirFigura(wxTextFile *f,wxString Nom);

};

#endif
