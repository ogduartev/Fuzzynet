/***************************************************************************
                          reportetexto.h  -  description
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

#ifndef REPORTETEXTO_H
#define REPORTETEXTO_H

#include "reporte.h"

/**Genera Reportes en formato ASCII
  *@author 
  */

class ReporteTexto : public Reporte  {
public: 
	ReporteTexto();
	~ReporteTexto();

  void encabezado(wxTextFile *f, wxString Tit);
  void cierre(wxTextFile *f);
  void seccion(wxTextFile *f,wxString Sec);
  void parrafo(wxTextFile *f, wxString Par);
  void lista(wxTextFile *f, wxArrayString Nom, wxArrayString Des);
  wxString enlace(wxString Dir, wxString Dato);
  wxString enlaceTabla(int Tab);
  wxString enlaceFigura(int){wxString cad; return cad;};
  wxString destino(wxString Dir, wxString Dato);
  wxString crearCadenaArchivo(wxString Dir);
  void incluirArchivo(wxTextFile *f, wxString Origen);
  void tablaContenido();
  void tabla(wxTextFile *f,wxArrayString *lista, int tam, wxString Nombre);
  bool figuraVariable(VariableLinguistica *Var,NumeroDifuso *Num=NULL,int entrada=1){return FALSE;}
  void incluirFigura(wxTextFile *f,wxString Nom){}

};

#endif
