/***************************************************************************
                          reportehtml.h  -  description
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

#ifndef REPORTEHTML_H
#define REPORTEHTML_H

#include "reporte.h"

/**Genera Reportes en formato HTML
  *@author 
  */

class ReporteHTML : public Reporte  {
public: 
	ReporteHTML();
	~ReporteHTML();

  void encabezado(wxTextFile *f, wxString Tit);
  void cierre(wxTextFile *f);
  void seccion(wxTextFile *f,wxString Sec);
  void parrafo(wxTextFile *f, wxString Par);
  void lista(wxTextFile *f, wxArrayString Nom, wxArrayString Des);
  wxString enlace(wxString Dir, wxString Dato);
  wxString enlaceTabla(int Tab);
  wxString enlaceFigura(int Fig);
  wxString enlaceExterno(wxString Dir, wxString Dato);
  wxString destino(wxString Dir, wxString Dato);
  wxString crearCadenaArchivo(wxString Dir);
  void abrirArchivo(wxTextFile* f);
  void cerrarArchivo(wxTextFile* f);
  void incluirArchivo(wxTextFile *f, wxString Origen);
  void tablaContenido();
  void postProceso(wxString arch,wxString Nombre);
  void tabla(wxTextFile *f,wxArrayString *lista, int tam, wxString Nombre);
  bool figuraVariable(VariableLinguistica *Var,NumeroDifuso *Num,int entrada=1);
  void incluirFigura(wxTextFile *f,wxString Nom);
};

#endif
